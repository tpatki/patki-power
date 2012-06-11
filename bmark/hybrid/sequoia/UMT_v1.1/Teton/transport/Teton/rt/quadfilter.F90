!***********************************************************************
!                        Version 1:  06/02, PFN                        *
!                                                                      *
!   QUADFILTER - Sets special quadratures for "filtering" used in TSA. *
!              radiation transport in slab geometry.                   *
!                                                                      *
!   Input:                                                             *
!                                                                      *
!   Output:  OMEGA  - direction cosines (mu,eta,xi)                    *
!            QUADWT - quadrature weights                               *
!                                                                      *
!                                                                      *
!***********************************************************************

   subroutine quadfilter(self, ndim)

   use kind_mod
   use constant_mod
   use Quadrature_mod

   implicit none

!  Arguments

   type(Quadrature)          :: self

   integer,    intent(in)    :: ndim 

!  Local

   integer    :: i

   real(adqt) :: filterWeight 
 
!  Set quadrature for 1D filtering sweeps

   if (ndim == 2) then
     filterWeight   = pi
     self% ynm(:,:) = one
     self% pnm(:,:) = one/(two*pi) 
   elseif (ndim == 3) then
     filterWeight   = two*pi
     self% ynm(:,:) = one
     self% pnm(:,:) = one/(four*pi) 
   endif
 
   self% omega(:,:) = zero
   self% weight(:)  = filterWeight 
 
   do i=1,ndim
     self% omega(i,2*i-1) =  one
     self% omega(i,2*i)   = -one
   enddo


   return
   end subroutine quadfilter
 
