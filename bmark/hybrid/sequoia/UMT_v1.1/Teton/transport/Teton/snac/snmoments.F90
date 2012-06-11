!***********************************************************************
!                        Version 1:  05/95, PFN                        *
!                                                                      *
!   SNMOMENTS - This routine, called by SNFLWRZA and SNFLWXYZ          *
!               calculates the required spherical harmonic moments     *
!               [phic] of the angular flux [psic]. It uses the array   *
!               ynm(n,m), whose definition is:                         * 
!                                                                      *
!               ynm(n,m) = real part of (l,k)th spherical harmonic,    *
!                          evaluated at the mth direction, where       *
!                                                                      *
!                             n = 1 + l*(l+1)/2 + k                    *
!                                                                      *
!            This routine is designed to accumulate moments as an      *
!            angle is calculated and does not require storage of the   *
!            full angular flux array.  It is assumed that the moment   *
!            array has been initialized before the loop over angles    *
!            in SNFLWRZA or SNFLWXYZ.                                  *
!                                                                      *
!                                                                      *
!   Input:   psic     - angular flux                   (E/A/t/ster)    *
!            quadwt   - quadrature weights                      (0)    *
!            ynm      - spherical harmonics                     (0)    *
!                                                                      *
!   Output:  PHIC     - flux moments                        (E/A/t)    *
!                                                                      *
!***********************************************************************

   subroutine snmoments(QuadSet,ncornr,m,tpsic,PHIC)

   use kind_mod
   use constant_mod
   use Quadrature_mod

   implicit none

!  Arguments

   type(Quadrature)          :: QuadSet

   integer,    intent(in)    :: ncornr, m
 
   real(adqt), intent(in)    :: tpsic(QuadSet%Groups,ncornr)

   real(adqt), intent(inout) :: phic(QuadSet%NumMoments*QuadSet%Groups,ncornr)

!  Local

   integer    :: ic,ig,n,noff,Groups

   real(adqt) :: wy, quadwt

!  Add this angles contribution to the flux moments

   noff   = 0
   quadwt = QuadSet% Weight(m)
   Groups = QuadSet% Groups

   do n=1,QuadSet% NumMoments

     wy = quadwt*QuadSet% Ynm(n,m)

     if (wy /= zero) then

       do ic=1,ncornr
         do ig=1,Groups
           phic(noff+ig,ic) = phic(noff+ig,ic) + wy*tpsic(ig,ic)
         enddo
       enddo

     endif

     noff = noff + Groups 

   enddo

 
   return
   end subroutine snmoments


