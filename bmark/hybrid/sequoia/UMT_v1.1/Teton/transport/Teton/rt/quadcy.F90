!***********************************************************************
!                        Version 1:  05/92, PFN                        *
!                                                                      *
!   QUADCY - calculates group dependent quadrature sets for Sn         *
!            radiation transport in cylinders                          *
!                                                                      *
!   Input:   nordr  - vector of group quadrature orders (no st. dir.)  *
!            nangt  - sum of quadrature orders for all groups (w/st d) *
!            ngr    - number of frequency groups                       *
!                                                                      *
!   Output:  OMEGA  - group dependent direction cosines (mu)           *
!            QUADWT - group dependent quadrature weights               *
!                                                                      *
!   Allowed values of "n" are:  2, 4, 6, 8, 12, 16                     *
!                                                                      *
!***********************************************************************

   subroutine quadcy(self)

   use kind_mod
   use constant_mod
   use Quadrature_mod

   implicit none

!  Arguments

   type(Quadrature) :: self

!  Local

   integer    :: i,ixi,isd,lpxi,n1,n2,ns,nf,np,nangxi, &
                 nordp1,nstdir,norder

   integer    :: iang(16)

   real(adqt) :: amu(77),wgt(77)

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

!  Angular weights sum to 2 for all mu (starting direction has a
!  weight of zero)
 
   iang(2)  = 1
   iang(4)  = 2
   iang(6)  = 5
   iang(8)  = 11
   iang(12) = 21
   iang(16) = 42
 
!  Set direction cosines and weights
 
   norder = self% order
   nstdir = norder/2
   ns     = iang(norder)
   lpxi   = 1
   n1     = ns
 
!  Loop over XI levels
 
   do ixi=1,nstdir
 
     nangxi = nstdir - ixi + 1
     isd    = ns + nstdir - ixi
     n2     = n1 + nstdir - ixi
     np     = n1 - 1
     nordp1 = 2*nangxi + 1
 
!  Starting Direction
 
      self% omega(1,lpxi) = -sqrt(one - amu(isd)*amu(isd))
     self% weight(lpxi)   =  zero
 
!  MU < 0
 
     do i=n1,n2
        self% omega(1,lpxi+i-np) = -amu(i)
       self% weight(lpxi+i-np)   =  wgt(i)
     enddo
 
!  MU > 0
 
     do i=nangxi,1,-1
        self% omega(1,lpxi+nordp1-i) = -self% omega(1,lpxi+i)
       self% weight(lpxi+nordp1-i)   =  self% weight(lpxi+i)
     enddo
 
     n1   = n1 + nangxi
     lpxi = lpxi + 2*nangxi + 1
 
   enddo
 
 
   return
   end subroutine quadcy

