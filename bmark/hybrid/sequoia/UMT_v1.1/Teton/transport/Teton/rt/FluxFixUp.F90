!***********************************************************************
!                        Version 1:  05/92, PFN                        *
!                                                                      *
!   FLUXFIXUP  - A conservative approach to removing negative          *
!                intensities at the end of a time step.  It is         *
!                called at the end of the time step so that the        *
!                iteration process will not be perturbed.              *
!                                                                      *
!   Input:   psir   - corner net emission source rate (group sum)      *
!                                                              (E/V/t) *
!            phir   - corner Planckian emission source         (E/A/t) *
!                                                                      *
!   Local:   etchic - scratch array                                    *
!                                                                      *
!   Output:  SRCC   - scalar group-dependent source            (E/V/t) *
!                                                                      *
!***********************************************************************
   subroutine FluxFixUp(Size, Geom, Quad, psir, phir)

   use kind_mod
   use mpi_param_mod
   use mpif90_mod
   use constant_mod
   use radconstant_mod
   use Size_mod
   use Geometry_mod
   use QuadratureList_mod
   use Quadrature_mod

   implicit none

!  Arguments - Types
                                                                                    
   type(MeshSize)            :: Size
   type(Geometry)            :: Geom
   type(QuadratureList)      :: Quad

!  Arguments

   real(adqt), intent(inout) :: psir(Size%ngr,Size%ncornr,Size%nangSN), &
                                phir(Size%ngr,Size%ncornr) 

!  Local

   type(Quadrature), pointer  :: QuadSet

   integer    :: i,ia,ic,ig,iz,ncornr,nzones,ngr

   real(adqt) :: preFixEnergy,postFixEnergy 

   real(adqt) :: sumpos,sumneg,sfactor,volpos

   real(adqt) :: PositiveEnergy,NegativeEnergy,PercentNegative,ECheck

!  Mesh Constants

   ncornr = Size% ncornr
   nzones = Size% nzones
   ngr    = Size% ngr

   QuadSet => getQuadrature(Quad, 1)

!  Cleanup negative intensities

   preFixEnergy = zero
   do ic=1,ncornr
     do ig=1,ngr
       preFixEnergy = preFixEnergy + Geom%volc(ic)*phir(ig,ic)
     enddo
   enddo

   preFixEnergy = preFixEnergy/speed_light

   phir(:,:) = zero


   ZoneLoop: do iz=1,nzones

     sumpos = zero
     sumneg = zero
     volpos = zero

!  For each energy/angle point, find out how much we need to
!  add and how much we have available.

     AngleLoop1: do ia=1,Size%nangSN

       CornerLoop1: do ic=Geom%CList(iz)+1,Geom%CList(iz+1)

         do ig=1,ngr
           if (psir(ig,ic,ia) >= zero) then
             sumpos = sumpos + Geom%volc(ic)*QuadSet%weight(ia)*psir(ig,ic,ia)
             volpos = volpos + Geom%volc(ic) 
           else
             sumneg = sumneg + Geom%volc(ic)*QuadSet%weight(ia)*psir(ig,ic,ia)
           endif
         enddo

       enddo CornerLoop1
     enddo AngleLoop1

!  Find the scaling factor for PSI

     if (volpos > zero) then
       sfactor = (sumpos + sumneg)/sumpos
     else
       sfactor = one 
     endif

!  Set all negative intensities to zero and scale the remaining
!  positive intensities by the same factor 

     AngleLoop2: do ia=1,Size%nangSN

       CornerLoop2: do ic=Geom%CList(iz)+1,Geom%CList(iz+1)

         do ig=1,ngr
           if (sfactor >= zero .and. volpos > zero) then
             if (psir(ig,ic,ia) > zero) then
               psir(ig,ic,ia) = sfactor*psir(ig,ic,ia)
             else
               psir(ig,ic,ia) = zero
             endif
           endif
           phir(ig,ic) = phir(ig,ic) + QuadSet% weight(ia)*psir(ig,ic,ia)
         enddo

       enddo CornerLoop2

     enddo AngleLoop2

   enddo ZoneLoop

!  Check Energy Conservation

   postFixEnergy = zero
   do ic=1,ncornr
     do ig=1,ngr
       postFixEnergy = postFixEnergy + Geom%volc(ic)*phir(ig,ic)
     enddo
   enddo

   postFixEnergy = postFixEnergy/speed_light


   PositiveEnergy = zero
   NegativeEnergy = zero
                                                                                      
   do ia=1,Size%nangSN
     do ic=1,ncornr
       do ig=1,ngr
         if (psir(ig,ic,ia) > zero) then
           PositiveEnergy = PositiveEnergy + Geom%volc(ic)*QuadSet%weight(ia)*psir(ig,ic,ia)
         else
           NegativeEnergy = NegativeEnergy + Geom%volc(ic)*QuadSet%weight(ia)*psir(ig,ic,ia)
         endif
       enddo
     enddo
   enddo

   PositiveEnergy = PositiveEnergy/speed_light
   NegativeEnergy = NegativeEnergy/speed_light

   call MPIAllReduceT(PositiveEnergy, "sum", MPI_COMM_WORLD)
   call MPIAllReduceT(NegativeEnergy, "sum", MPI_COMM_WORLD)
   call MPIAllReduceT(preFixEnergy,   "sum", MPI_COMM_WORLD)
   call MPIAllReduceT(postFixEnergy,  "sum", MPI_COMM_WORLD)
                                                                                      
   PercentNegative = 100.d0*abs( NegativeEnergy/(PositiveEnergy + NegativeEnergy) )
   ECheck          = preFixEnergy - postFixEnergy

   if (Size%my_node == 0) then
     write(6,100) PositiveEnergy,NegativeEnergy,PercentNegative,ECheck
   endif

 100 format("PositiveEnergy   = ",1pe12.4,/  &
            "NegativeEnergy   = ",1pe12.4,/  &
            "PercentNegative  = ",1pe12.4,/  &
            "EnergyCheck      = ",1pe12.4/)


 
   return
   end subroutine FluxFixUp 

