!***********************************************************************
!                        Version 1:  10/02, PFN                        *
!                                                                      *
!   ReConstructPsi - Reconstructs the angular intensities after remap. *
!                                                                      *
!   Input:       RadSpecificEnergy    - radiation specific energy      *
!                                       density after remap     (E/m)  *
!                OldRadSpecificEnergy - radiation specific energy      *
!                                       density before remap    (E/m)  *
!                                                                      *
!   Output:      PSIR   - radiation angular specific intensity  (E/m)  *
!                TRZ    - zonal radiation temperature           (T)    *
!                                                                      *
!***********************************************************************
 
   subroutine ReConstructPsi(Size, Geom,                                &
                             preRemapRadE,preRemapMatE,preRemapMass,    &
                             postRemapRadE,postRemapMatE,postRemapMass, &
                             rho,rhoOld,RadSpecificEnergy,              &
                             OldRadSpecificEnergy,phir,PSIR,TRZ)

   use kind_mod
   use mpi_param_mod
   use mpif90_mod
   use constant_mod
   use radconstant_mod
   use Size_mod
   use Geometry_mod

   implicit none 

!  Arguments

!  Types
                                                                                          
   type(MeshSize)            :: Size
   type(Geometry)            :: Geom

   real(adqt), intent(inout) :: preRemapRadE,preRemapMatE,  &
                                preRemapMass,postRemapRadE, & 
                                postRemapMatE,postRemapMass
 
   real(adqt), intent(in)    :: rho(Size%nzones),     & 
                                rhoOld(Size%nzones),  &
                                RadSpecificEnergy(Size%nzones,Size%ngr),    &
                                OldRadSpecificEnergy(Size%nzones,Size%ngr)

   real(adqt), intent(inout) :: psir(Size%ngr,Size%ncornr,Size%nangSN), &
                                phir(Size%ngr,Size%ncornr),             &
                                trz(Size%nzones)

!  Local

   integer    :: ia, ic, ig, iz, ndir

   integer    :: icface1,icface2,icez1,icez2,  &
                 ipnt0,ipnt1,ipnt2,iface,ncfaces

   integer    :: ndim, nfaces, nzones, ncornr, ngr

   real(adqt) :: sumrad, tr, tr4, tr4floor,  &
                 sum(Size%ngr), factor(Size%ngr) 

   real(adqt) :: tdl(3),tfl(3),tzl(3),A_fep(3)

   real(adqt) :: DRho,maxDRho,errorEnergy,       &
                 tolEnergy,floor,facMin,facMax,  &
                 RadECheck,MatECheck,MassCheck

!  Dynamic arrays

   real(adqt), allocatable :: volFrac(:)

   parameter (tolEnergy=1.0d-3)
   parameter (floor=1.0d-40)
   parameter (facMin=0.01d0)
   parameter (facMax=100.0d0)

   ndim   = Size% ndim
   nfaces = Size% nfaces
   nzones = Size% nzones
   ncornr = Size% ncornr
   ngr    = Size% ngr
   ndir   = Size% nangSN

   tr       = Size%tfloor
   tr4floor = tr*tr*tr*tr

!***********************************************************************
!  Recalculate the corner and zone volumes which may have changed      *
!  during the remap step.                                              * 
!***********************************************************************

!  Find largest density change

   maxDRho = -one
   do iz=1,nzones
     DRho = abs(rho(iz) - rhoOld(iz))/rho(iz)
     if (DRho > maxDRho) then
       maxDRho = DRho
     endif
   enddo

   call MPIAllReduceT(maxDRho, "max", MPI_COMM_WORLD)

   Reconstruct: if (maxDRho /= zero) then

     if (ndim == 3) then
       call rtgeom3(Size, Geom)
     else if (ndim == 2) then
       call rtgeom2(Size, Geom)
     else if (ndim == 1) then
       call rtgeom1(Size, Geom)
     endif

     allocate( volFrac(ncornr) )

     do iz=1,nzones
       do ic=Geom%CList(iz)+1,Geom%CList(iz+1)
         volFrac(ic) = Geom%volc(ic)/Geom%volz(iz)
       enddo
     enddo
 
!***********************************************************************
!  Adjust the discrete angular intensities to conserve energy          *
!***********************************************************************

     ZoneLoop: do iz=1,nzones

!  Compute multiplicative correction

       sum(:) = zero

       do ic=Geom% CList(iz)+1,Geom% CList(iz+1)
         sum(:) = sum(:) + volFrac(ic)*phir(:,ic)
       enddo

       do ig=1,ngr
         if (sum(ig) > floor) then
           factor(ig) = RadSpecificEnergy(iz,ig)/sum(ig)
           factor(ig) = min( factor(ig), facMax )
           factor(ig) = max( factor(ig), facMin )
         else
           factor(ig) =  one
         endif

       enddo

!  Apply correction uniformly 

       sumrad = zero

       do ic=Geom% CList(iz)+1,Geom% CList(iz+1)

         phir(:,ic) = factor(:)*phir(:,ic)

         do ia=1,ndir
           psir(:,ic,ia) = factor(:)*psir(:,ic,ia)
         enddo

         do ig=1,ngr
           sumrad = sumrad + volFrac(ic)*phir(ig,ic)
         enddo

       enddo

!  Update radiation temperature from the remapped specific energy 

       tr4     = max( rho(iz)*sumrad/rad_constant, tr4floor )
       trz(iz) = sqrt( sqrt( tr4 ) )

     enddo ZoneLoop

!***********************************************************************
!  Check energy conservation of the remapped fields                    *
!***********************************************************************

   call MPIAllReduceT(preRemapRadE   , "sum", MPI_COMM_WORLD)
   call MPIAllReduceT(postRemapRadE  , "sum", MPI_COMM_WORLD)
   call MPIAllReduceT(preRemapMatE   , "sum", MPI_COMM_WORLD)
   call MPIAllReduceT(postRemapMatE  , "sum", MPI_COMM_WORLD)
   call MPIAllReduceT(preRemapMass   , "sum", MPI_COMM_WORLD)
   call MPIAllReduceT(postRemapMass  , "sum", MPI_COMM_WORLD)

     if (postRemapRadE == zero) then
       errorEnergy = zero
     else
       errorEnergy = abs( postRemapRadE - preRemapRadE )/postRemapRadE
       if (errorEnergy > tolEnergy) then
!         call f90fatal(" Energy not conserved during remap ")
       endif
     endif

     RadECheck = postRemapRadE - preRemapRadE
     MatECheck = postRemapMatE - preRemapMatE
     MassCheck = postRemapMass - preRemapMass

     if (Size%my_node == 0) then
       write(6,100)
       write(6,200) postRemapRadE,RadECheck, &
                    postRemapMatE,MatECheck, &
                    postRemapMass,MassCheck 
     endif

 100 format('Conservation Check After Remap')
 200 format('RadEnergy = ',1pe14.6,' RadEnergyCheck = ',1pe14.6/,  &
            'MatEnergy = ',1pe14.6,' MatEnergyCheck = ',1pe14.6/,  &
            'Mass      = ',1pe14.6,' MassCheck      = ',1pe14.6/)

!  Release temporary arrays

     deallocate( volFrac )

   endif Reconstruct


   return
   end subroutine ReConstructPsi 


