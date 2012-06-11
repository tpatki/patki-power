!***********************************************************************
!                        Version 1:  05/92, PFN                        *
!                                                                      *
!   RTSCAL - Calculates angular moments of the photon intensity        *
!                                                                      *
!   Input:   psir   - angle-depenedent photon intensity   (E/A/t/ster) *
!            quadwt - quadrature weights                           (0) *
!                                                                      *
!   Output:  PHIR   - angular moments of photon intensity      (E/A/t) *
!                                                                      *
!***********************************************************************
   subroutine rtscal(npart,ncornr,ndir,quadwt,psir,PHIR)

   use kind_mod
   use constant_mod

   implicit none

!  Arguments

   integer,    intent(in)    :: npart,ncornr,ndir
 
   real(adqt), intent(in)    :: quadwt(ndir),psir(npart,ncornr,ndir)

   real(adqt), intent(inout) :: phir(npart,ncornr)

!  Local

   integer :: ia

!  Calculate Intensity Moments
 
   phir(:,:) = zero
 
   AngleLoop: do ia=1,ndir
     phir(:,:) = phir(:,:) + quadwt(ia)*psir(:,:,ia) 
   enddo AngleLoop
 

   return
   end subroutine rtscal

