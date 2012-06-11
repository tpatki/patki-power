!***********************************************************************
!                        Version 1:  07/97, PFN                        *
!                                                                      *
!   QUADRZ - Calculates group dependent quadrature sets for Sn         *
!            radiation transport in RZ geometry.                       *
!                                                                      *
!   Input:   nordr  - vector of group quadrature orders                *
!            nangt  - sum of quadrature orders for all groups          *
!            ngr    - number of frequency groups                       *
!                                                                      *
!   Output:  OMEGA  - group dependent direction cosines (mu,xi)        *
!            QUADWT - group dependent quadrature weights               *
!                                                                      *
!   Allowed values of "n" are:  2, 4, 6, 8, 12, 16                     *
!                                                                      *
!   Directions per quadrant:                                           *
!                                                                      *
!                             N   N(N+6)/8                             *
!                             2       2                                *
!                             4       5                                *
!                             6       9                                *
!                             8      14                                *
!                            12      27                                *
!                            16      44                                *
!                                                                      *
!   Angles are ordered by xi-level for parallelism:                    *
!                                                                      *
!  e.g.  S4                                                            *
!                                                                      *
!                                   xi+                                *
!                                  |                                   *
!                           17 18  |  19 20       level 4              *
!                                  |                                   *
!                                  |                                   *
!                      7  8     9  | 10    11 12  level 2              *
!                       -----------------------mu+                     *
!                      1  2     3  |  4     5  6  level 1              *
!                                  |                                   *
!                                  |                                   *
!                           13 14  | 15  16       level 3              *
!                                  |                                   *
!                                                                      *
!***********************************************************************

   subroutine quadrz(self)

   use kind_mod
   use constant_mod
   use Quadrature_mod

   implicit none

!  Arguments

   type(Quadrature) :: self

!  Local

   integer    :: i,il,nlevel,ns,nf,iquad,nangl,norder

   integer    :: iang(16)

   real(adqt) :: halfpi,xilev

   real(adqt) :: amu(77),axi(77),wgt(77)

!  Constants

   data amu/.5773503d0,                                             &
            .8688903d0,.3500212d0,.3500212d0,                       &
            .9261808d0,.6815076d0,.2666355d0,.6815076d0,.2666355d0, &
            .2666355d0,                                             &
            .9511897d0,.7867958d0,.5773503d0,.2182179d0,.7867958d0, &
            .5773503d0,.2182179d0,.5773503d0,.2182179d0,.2182179d0, &
            .9716377d0,.8722706d0,.7600210d0,.6280191d0,.4595476d0, &
            .1672126d0,.8722706d0,.7600210d0,.6280191d0,.4595476d0, &
            .1672126d0,.7600210d0,.6280191d0,.4595476d0,.1672126d0, &
            .6280191d0,.4595476d0,.1672126d0,.4595476d0,.1672126d0, &
            .1672126d0,                                             &
            .9805009d0,.9092855d0,.8319966d0,.7467506d0,.6504264d0, &
            .5370966d0,.3922893d0,.1389568d0,.9092855d0,.8319966d0, &
            .7467506d0,.6504264d0,.5370966d0,.3922893d0,.1389568d0, &
            .8319966d0,.7467506d0,.6504264d0,.5370966d0,.3922893d0, &
            .1389568d0,.7467506d0,.6504264d0,.5370966d0,.3922893d0, &
            .1389568d0,.6504264d0,.5370966d0,.3922893d0,.1389568d0, &
            .5370966d0,.3922893d0,.1389568d0,.3922893d0,.1389568d0, &
            .1389568d0/

   data axi/.5773503d0,                                             &
            .3500212d0,.3500212d0,.8688903d0,                       &
            .2666355d0,.2666355d0,.2666355d0,.6815076d0,.6815076d0, &
            .9261808d0,                                             &
            .2182179d0,.2182179d0,.2182179d0,.2182179d0,.5773503d0, &
            .5773503d0,.5773503d0,.7867958d0,.7867958d0,.9511897d0, &
            .1672126d0,.1672126d0,.1672126d0,.1672126d0,.1672126d0, &
            .1672126d0,.4595476d0,.4595476d0,.4595476d0,.4595476d0, &
            .4595476d0,.6280191d0,.6280191d0,.6280191d0,.6280191d0, &
            .7600210d0,.7600210d0,.7600210d0,.8722706d0,.8722706d0, &
            .9716377d0,                                             &
            .1389568d0,.1389568d0,.1389568d0,.1389568d0,.1389568d0, &
            .1389568d0,.1389568d0,.1389568d0,.3922893d0,.3922893d0, &
            .3922893d0,.3922893d0,.3922893d0,.3922893d0,.3922893d0, &
            .5370966d0,.5370966d0,.5370966d0,.5370966d0,.5370966d0, &
            .5370966d0,.6504264d0,.6504264d0,.6504264d0,.6504264d0, &
            .6504264d0,.7467506d0,.7467506d0,.7467506d0,.7467506d0, &
            .8319966d0,.8319966d0,.8319966d0,.9092855d0,.9092855d0, &
            .9805009d0/

   data wgt/1.d0,                                                   &
            .3333333d0,.3333333d0,.3333333d0,                       &
            .1761263d0,.1572071d0,.1761263d0,.1572071d0,.1572071d0, &
            .1761263d0,                                             &
            .1209877d0,.0907407d0,.0907407d0,.1209877d0,.0907407d0, &
            .0925926d0,.0907407d0,.0907407d0,.0907407d0,.1209877d0, &
            .0707626d0,.0558811d0,.0373377d0,.0373377d0,.0558811d0, &
            .0707626d0,.0558811d0,.0502819d0,.0258513d0,.0502819d0, &
            .0558811d0,.0373377d0,.0258513d0,.0258513d0,.0373377d0, &
            .0373377d0,.0502819d0,.0373377d0,.0558811d0,.0558811d0, &
            .0707626d0,                                             &
            .0489872d0,.0413296d0,.0212326d0,.0256207d0,.0256207d0, &
            .0212326d0,.0413296d0,.0489872d0,.0413296d0,.0360486d0, &
            .0144589d0,.0344958d0,.0144589d0,.0360486d0,.0413296d0, &
            .0212326d0,.0144589d0,.0085179d0,.0085179d0,.0144589d0, &
            .0212326d0,.0256207d0,.0344958d0,.0085179d0,.0344958d0, &
            .0256207d0,.0256207d0,.0144589d0,.0144589d0,.0256207d0, &
            .0212326d0,.0360486d0,.0212326d0,.0413296d0,.0413296d0, &
            .0489872d0/ 

   halfpi = half*pi

!  Angular weights sum to pi/2 in each quadrant

   iang(2)  = 1
   iang(4)  = 2
   iang(6)  = 5
   iang(8)  = 11
   iang(12) = 21
   iang(16) = 42

!  Angles are collected by xi-level and the
!  xi-levels are ordered from longest to shortest.  The xi-levels
!  come in pairs (i.e. xi<0 and xi>0 for a given set of mu) and
!  within a pair the xi<0 level comes first (this allows us to
!  easily treat a reflecting boundary on the z-axis).  Within a
!  xi-level, angles are ordered in increasing value of mu.

   norder  = self% order
   nlevel  = norder/2
   ns      = iang(norder)
   nf      = ns + norder/2  - 1
   iquad   = 0

!  Loop over pairs of xi-levels

   do il=1,nlevel

     xilev = axi(ns)
     nangl = nlevel - il + 1 

!  Starting direction

     self% omega(1,iquad+1) = -sqrt(one - xilev*xilev)
     self% omega(2,iquad+1) = -xilev
     self% weight(iquad+1)  =  zero

!  quadrant 3  mu<0, xsi<0

     do i=1,nangl
       self% omega(1,iquad+i+1)  = -amu(ns+i-1)
       self% omega(2,iquad+i+1)  = -xilev
       self% weight(iquad+i+1)   =  halfpi*wgt(ns+i-1)
     enddo

     iquad = iquad + nangl + 1

!  quadrant 4  mu>0, xsi<0

     do i=1,nangl
       self% omega(1,iquad+i)  =  amu(nf-i+1)
       self% omega(2,iquad+i)  = -xilev
       self% weight(iquad+i)   =  halfpi*wgt(nf-i+1)
     enddo

!  Finishing direction

     self% omega(1,iquad+nangl+1) =  sqrt(one - xilev*xilev)
     self% omega(2,iquad+nangl+1) = -xilev
     self% weight(iquad+nangl+1)  =  zero

     iquad = iquad + nangl + 1

!  Starting direction

     self% omega(1,iquad+1) = -sqrt(one - xilev*xilev)
     self% omega(2,iquad+1) =  xilev
     self% weight(iquad+1)  =  zero

!  quadrant 2  mu<0, xsi>0

     do i=1,nangl
       self% omega(1,iquad+i+1)  = -amu(ns+i-1)
       self% omega(2,iquad+i+1)  =  xilev
       self% weight(iquad+i+1)   =  halfpi*wgt(ns+i-1)
     enddo

     iquad = iquad + nangl + 1

!  quadrant 1  mu>0, xsi>0

     do i=1,nangl
       self% omega(1,iquad+i)  =  amu(nf-i+1)
       self% omega(2,iquad+i)  =  xilev
       self% weight(iquad+i)   =  halfpi*wgt(nf-i+1)
     enddo

!  Finishing direction

     self% omega(1,iquad+nangl+1) =  sqrt(one - xilev*xilev)
     self% omega(2,iquad+nangl+1) =  xilev
     self% weight(iquad+nangl+1)  =  zero

     iquad = iquad + nangl + 1

     ns = nf + 1
     nf = ns + nangl - 2

   enddo


   return
   end subroutine quadrz


