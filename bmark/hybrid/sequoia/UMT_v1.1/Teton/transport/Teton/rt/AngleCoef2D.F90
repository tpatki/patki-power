!***********************************************************************
!                        Version 2:  05/96, PFN                        *
!                                                                      *
!   AngleCoef2D - This routine computes the angle-dependent            *
!                 parameters that result from angular differencing.    *
!                 differencing.  This routine assumes that the         *
!                 angles, m=1,...,NumAngles, are grouped by xi-levels, *
!                 from xi-minimum to xi-maximum, with mu ordered       *
!                 min to max within each xi-level.                     *
!                                                                      *
!   Input:     ndir   - number of angles                               *
!                                                                      *
!   Output:    BETA   - parameters that appear in the discrete         *
!                       ordinates version of the angular derivative    *
!                       term                                           *
!              TAU    - weights that appear in the discrete-ordinates  *
!                       weighted-diamond relation in angle             *
!                                                                      *
!***********************************************************************

   subroutine AngleCoef2D(self)

   use kind_mod
   use constant_mod
   use Quadrature_mod

   implicit none

!  Arguments

   type(Quadrature)          :: self

!  Local

   integer    :: m,mm,mm1,mm2,NumAngles

   real(adqt) :: wtlev,xilev,phimh,phiph,umh,uph

   character(len=8) :: newlev,endlev

!  First set Alpha:  Alpha is zero for starting and finishing directions

   NumAngles = self% NumAngles

   do m=1,NumAngles
     self% Alpha(m) = zero
     self% Tau(m)   = zero

     if (self% angleType(m) == 0) then
       self% Alpha(m) = self% Alpha(m-1) - self% weight(m)*self% omega(1,m)
     endif
   enddo
 
!  Now tau, which is a bit more complicated.  (The complicated
!  part is figuring out what to use for u(m+1/2) and u(m-1/2).)
 
   wtlev = zero
   xilev = self% omega(2,1)
   mm1   = 1
 
   AngleLoop: do m=1,NumAngles

     if (self% omega(2,m) == xilev) then
       wtlev  = wtlev + self% weight(m)
       newlev = 'no'
     else
       newlev = 'yes'
     endif
 
     if (m == NumAngles) then
       endlev = 'yes'
     else
       endlev = 'no'
     endif
 
     if (newlev == 'yes' .or. endlev == 'yes') then
 
       if (newlev == 'yes') then
         mm2 = m - 1
       else
         mm2 = m
       endif
 
       XiLevelLoop: do mm=mm1,mm2

         if (self% angleType(mm) == -1) then

           if (mm == mm1) then
             phimh = pi
             umh   = self% omega(1,mm)
           else
             call f90fatal("Mu not increasing in xi-level, SNRZAANG")
           endif

         elseif (self% angleType(mm) == 1) then

           self% Tau(mm) = zero

         else

           phiph = phimh - self% weight(mm)*pi/wtlev
           uph   = sqrt(one - self% omega(2,mm)*self% omega(2,mm))*cos(phiph)

           if (self% omega(1,mm) < umh .or. self% omega(1,mm) > uph) then
             call f90fatal("Mu not between limits, SNRZAANG") 
           endif

           self% Tau(mm) = (self% omega(1,mm) - umh)/(uph - umh)
           phimh        = phiph
           umh          = uph

         endif

       enddo XiLevelLoop
 
       wtlev = zero
       xilev = self% omega(2,m)
       mm1   = m
 
     endif
 
   enddo AngleLoop

 
   return
   end subroutine AngleCoef2D 

