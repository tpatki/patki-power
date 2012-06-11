!***********************************************************************
!                        Version 1:  05/92, PFN                        *
!                                                                      *
!   RTINIT - Calculates an initial radiation distribution.  The        *
!            energy density is a*T^4 where T is the initial radiation  *
!            temperature.  The energy is placed in a Planck spectrum   *
!            with an isotropic angular distribution.  Electron energy, *
!            electron temperature and ion energy are also set.         *
!                                                                      *
!   Input:   tez    - zone-average electron temperature   (T)          *
!            tiz    - zone-average ion temperature        (T)          *
!            trz    - zone-average radiation temperature  (T)          *
!                                                                      *
!   Output:  PSIR   - corner angular photon intensity     (E/A/t)      *
!            TEC    - corner electron temperatures        (T)          *
!            TIC    - corner ion temperatures             (T)          *
!                                                                      *
!   Local:   a      - radiation constant    (E/V/T^4)                  *
!                                                                      *
!***********************************************************************
 
   subroutine rtinit(Size, Geom, Mat, RadEdit, Quad, PSIR, PHIR)

   use kind_mod
   use mpi_param_mod
   use mpif90_mod
   use constant_mod
   use radconstant_mod
   use Size_mod
   use Geometry_mod
   use Material_mod
   use Editor_mod
   use QuadratureList_mod

   implicit none

!  Arguments

   type(MeshSize)            :: Size
   type(Geometry)            :: Geom
   type(Material)            :: Mat
   type(Editor)              :: RadEdit
   type(QuadratureList)      :: Quad

   real(adqt), intent(inout) :: psir(Size%ngr,Size%ncornr,Size%nangSN), &
                                phir(Size%ngr,Size%ncornr)

!  Local

   integer    :: ia,ic,ig,iz,ngrp,nangles,ngr,ncornr,nzones

   real(adqt) :: erad,floor,ac,wtiso,temp,t4,density

!  Stack Arrays

   real(adqt) :: gnu(Size%ngr+1),frac(Size%ngr+1),  &
                   x(Size%ngr+1),planck(Size%ngr)

!  Constants

!   parameter (floor=1.0d-30)

   floor   = zero
   ac      = rad_constant*speed_light 

   ngr     = Size% ngr
   nzones  = Size% nzones
   ncornr  = Size% ncornr
   nangles = Size% nangSN
   wtiso   = Size% wtiso

   ngrp    = ngr + 1

   gnu(:)  = getEnergyGroups(Quad,ngr)

!  Initialize PHIR

   phir(:,:) = zero

!  Initialize the total radiation energy

   erad = zero

   do iz=1,nzones
     temp = Mat%trz(iz)
     erad = erad + rad_constant*Geom%volz(iz)*temp*temp*temp*temp 
   enddo

   call setEdits(RadEdit, EnergyRadiation=erad)

   call MPIAllReduceT(ERAD, "sum", MPI_COMM_WORLD)

!  Set corner temperatures

   if (Size%imatc == 'elec') then

     do ic=1,ncornr
       iz          = Geom%CToZone(ic)
       Mat%tec(ic) = Mat%tez(iz)
     enddo

   elseif (Size%imatc == 'elec+ion') then

     do ic=1,ncornr
       iz          = Geom%CToZone(ic)
       Mat%tec(ic) = Mat%tez(iz)
       Mat%tic(ic) = Mat%tiz(iz)
     enddo

   endif
 
!  Compute the fraction of the total emission in each energy group
!  The input for RTPLNK is (h*nu)/(k*Te).
 
!*********************************
!    OUTER LOOP OVER CORNERS     *
!*********************************

   CornerLoop: do ic=1,ncornr

     iz = Geom%CToZone(ic)

!  Load the 4th power of the corner radiation temperature into a scalar

     density = Mat%rho(iz)
     temp    = Mat%trz(iz)
     t4      = ac*temp*temp*temp*temp
 
!  Compute hnu/kt at upper energy boundary

     do ig=1,ngr+1
       x(ig) = gnu(ig)/temp
     enddo
 
     call rtplnk(ngrp,x,FRAC)

!  Use a lower bound of zero in calculating the Planckian

     frac(1) = zero
 
!  Compute the Planck function for all groups
 
     do ig=1,ngr
       planck(ig) = t4*(frac(ig+1) - frac(ig))
     enddo

!  Make sure sum of emission source over groups is acT^4.

     planck(ngr) = planck(ngr) + (one - frac(ngr+1))*t4
 
!  Loop over all angles in group

     do ia=1,nangles
       psir(:,ic,ia) = max(wtiso*planck(:),floor)/  &
                          (speed_light*density)
     enddo

     phir(:,ic) = max(planck(:),floor)/(speed_light*density)
 
   enddo CornerLoop
 
!*********************************
!      END LOOP OVER CORNERS     *
!*********************************
 
 
   return
   end subroutine rtinit

