!***********************************************************************
!                        Version 1:  01/93, PFN                        *
!                                                                      *
!   QUADXYZ - Calculates group dependent quadrature sets for Sn        *
!             radiation transport in XYZ geometry.                     *
!                                                                      *
!   Input:   norder - quadrature order                                 *
!            nang   - number of angles                                 *
!                                                                      *
!   Output:  OMEGA  - group dependent direction cosines (mu,eta,xi)    *
!            QUADWT - group dependent quadrature weights               *
!                                                                      *
!   Allowed values of "n" are:  2, 4, 6, 8, 10, 12, 14, 16, 18, 20     *
!                                                                      *
!   Directions per Octant:                                             *
!                                                                      *
!                             N   N(N+2)/8                             *
!                             2       1                                *
!                             4       3                                *
!                             6       6                                *
!                             8      10                                *
!                            10      15                                *
!                            12      21                                *
!                            14      28                                *
!                            16      36                                *
!                            18      45                                *
!                            20      55                                *
!                                                                      *
!***********************************************************************

   subroutine quadxyz(self)

   use kind_mod
   use constant_mod
   use Quadrature_mod

   implicit none

!  Arguments

   type(Quadrature) :: self

!  Local

   integer    :: i,ns,nangoct,jcos,norder

   integer    :: iang(20),icoff(20),imu(220),ieta(220),  &
                 ixi(220),iwgt(220)

   real(adqt) :: halfpi

   real(adqt) :: dircos(58),weight(58),amu,aeta,axi,awgt

!  Constants

!  All quadrature sets are Level-Symmetric except for S20 which
!  is Fully-Symmetric (only sets with all positive points weights
!  are included).  The arrays DIRCOS and WEIGHT have been padded
!  with zeros to align the quadrature sets.

      data dircos/0.577350269189625d0,                     &
!  S4
                  0.868890300722201d0,0.350021174581540d0, &
!  S6
                  0.926180935517489d0,0.681507726536546d0, &
                  0.266635401516704d0,                     &
!  S8
                  0.951189731211341d0,0.786795792469443d0, &
                  0.577350269189625d0,0.218217890235992d0, &
!  S10 
                  0.963490981110468d0,0.839759962236684d0, &
                  0.694318887594384d0,0.508881755582618d0, &
                  0.189321326478010d0,                     &
!  S12
                  0.971637719251358d0,0.872270543025721d0, &
                  0.760021014833664d0,0.628019096642130d0, &
                  0.459547634642594d0,0.167212652822713d0, &
!  S14
                  0.976627152925770d0,0.893691098874356d0, &
                  0.802226255231412d0,0.698892086775901d0, &
                  0.577350269189625d0,0.422156982304796d0, &
                  0.151985861461031d0,                     &
!  S16
                  0.980500879011739d0,0.909285500943725d0, &
                  0.831996556910044d0,0.746750573614681d0, &
                  0.650426450628771d0,0.537096561300879d0, &
                  0.392289261444811d0,0.138956875067780d0, &
!  S18
                  0.983127661236087d0,0.920768021061018d0, &
                  0.853866206691488d0,0.781256199495913d0, &
                  0.701166884252161d0,0.610662549934881d0, &
                  0.504165151725164d0,0.368043816053393d0, &
                  0.129344504545924d0,0.d0,                &
!  S20 (Fully Symmetric)
                  0.985347485558646d0,0.929863938955324d0, &
                  0.870852583760463d0,0.807540401661143d0, &
                  0.738822561910371d0,0.663020403653288d0, &
                  0.577350269189625d0,0.476519266143665d0, &
                  0.347574292315847d0,0.120603343036693d0, &
                  0.d0               ,0.d0               /


      data weight /1.000000000000000d0,                     &
!  S4
                   0.333333333333333d0,0.d0,                &
!  S6
                   0.176126130863383d0,0.157207202469949d0, &
                   0.d0,                                    &
!  S8
                   0.120987654320987d0,0.090740740740740d0, &
                   0.092592592592592d0,0.d0,                &
!  S10
                   0.089303147984356d0,0.072529151712365d0, &
                   0.045043767436408d0,0.053928114487836d0, &
                   0.d0,                                    &
!  S12
                   0.070762589970091d0,0.055881101564888d0, &
                   0.037337673758828d0,0.050281901060057d0, &
                   0.025851291655750d0,0.d0,                &
!  S14
                   0.057997040896996d0,0.048900797636810d0, &
                   0.023547502053632d0,0.037905264970117d0, &
                   0.036591150519122d0,0.027347343266780d0, &
                   0.003745773097952d0,                     &
!  S16
                   0.048987239158038d0,0.041329597869844d0, &
                   0.020303200739365d0,0.026550075781349d0, &
                   0.037907440795600d0,0.013529504778675d0, &
                   0.032636937202685d0,0.010376957838539d0, &
!  S18
                   0.042264644884382d0,0.037612747382728d0, &
                   0.012269135163740d0,0.032418835255881d0, &
                   0.006644386146190d0,0.031209383843655d0, &
                   0.016012725269194d0,0.020048459530857d0, &
                   0.000111409402059d0,0.016379703852242d0, &
!  S20 (Fully Symmetric)
                   0.037021049060448d0,0.033284216537631d0, &
                   0.012942568580374d0,0.022287358265511d0, &
                   0.014054150411563d0,0.028265562625927d0, &
                   0.009085313444449d0,0.031556484065954d0, &
                   0.000982552577261d0,0.003031445199340d0, &
                   0.003161892186100d0,0.033866270661553d0/


      data iwgt/1,   &
!  S4
                1,1, &
                1,   &
!  S6
                1,2,1, &
                2,2,   &
                1,     &
!  S8 
                1,2,2,1, &
                2,3,2,   &
                2,2,     &
                1,       &
!  S10
                1,2,3,2,1, &
                2,4,4,2,   &
                3,4,3,     &
                2,2,       &
                1,         &
!  S12
                1,2,3,3,2,1, &
                2,4,5,4,2,   &
                3,5,5,3,     &
                3,4,3,       &
                2,2,         &
                1,           &
!  S14
                1,2,3,4,3,2,1, &
                2,5,6,6,5,2,   &
                3,6,7,6,3,     &
                4,6,6,4,       &
                3,5,3,         &
                2,2,           &
                1,             &
!  S16
                1,2,3,4,4,3,2,1, &
                2,5,6,7,6,5,2,   &
                3,6,8,8,6,3,     &
                4,7,8,7,4,       &
                4,6,6,4,         &
                3,5,3,           &
                2,2,             &
                1,               &
!  S18
                1, 2, 3, 4, 5, 4, 3, 2, 1, &
                2, 6, 7, 8, 8, 7, 6, 2,    &
                3, 7, 9,10, 9, 7, 3,       &
                4, 8,10,10, 8, 4,          &
                5, 8, 9, 8, 5,             &
                4, 7, 7, 4,                &
                3, 6, 3,                   &
                2, 2,                      &
                1,                         &                    
!  S20
                1, 2, 3, 4, 5, 5, 4, 3, 2, 1, &
                2, 6, 7, 8, 9, 8, 7, 6, 2,    &
                3, 7,10,11,11,10, 7, 3,       &
                4, 8,11,12,11, 8, 4,          &
                5, 9,11,11, 9, 5,             &
                5, 8,10, 8, 5,                &
                4, 7, 7, 4,                   &
                3, 6, 3,                      &
                2, 2,                         & 
                1/

      data imu/1,   &
!  S4
               1,2, &
               2,   &
!  S6
               1,2,3, &
               2,3,   &
               3,     &
!  S8
               1,2,3,4, &
               2,3,4,   &
               3,4,     &
               4,       &
!  S10
               1,2,3,4,5, &
               2,3,4,5,   &
               3,4,5,     &
               4,5,       &
               5,         &
!  S12
               1,2,3,4,5,6, &
               2,3,4,5,6,   &
               3,4,5,6,     &
               4,5,6,       &
               5,6,         &
               6,           &
!  S14
               1,2,3,4,5,6,7, &
               2,3,4,5,6,7,   &
               3,4,5,6,7,     &
               4,5,6,7,       &
               5,6,7,         &
               6,7,           &
               7,             &
!  S16
               1,2,3,4,5,6,7,8, &
               2,3,4,5,6,7,8,   &
               3,4,5,6,7,8,     &
               4,5,6,7,8,       &
               5,6,7,8,         &
               6,7,8,           &
               7,8,             &
               8,               &
!  S18
               1,2,3,4,5,6,7,8,9, &
               2,3,4,5,6,7,8,9,   &
               3,4,5,6,7,8,9,     &
               4,5,6,7,8,9,       &
               5,6,7,8,9,         &
               6,7,8,9,           &
               7,8,9,             &
               8,9,               &
               9,                 &
!  S20
               1,2,3,4,5,6,7,8,9,10, &
               2,3,4,5,6,7,8,9,10,   &
               3,4,5,6,7,8,9,10,     &
               4,5,6,7,8,9,10,       &
               5,6,7,8,9,10,         &
               6,7,8,9,10,           & 
               7,8,9,10,             &
               8,9,10,               &
               9,10,                 &
               10/

      data ieta/1,   &
!  S4
                2,2, &
                1,   &
!  S6
                3,3,3, &
                2,2,   &
                1,     &
!  S8
                4,4,4,4, &
                3,3,3,   &
                2,2,     &
                1,       &
!  S10
                5,5,5,5,5, &
                4,4,4,4,   &
                3,3,3,     &
                2,2,       &
                1,         &
!  S12
                6,6,6,6,6,6, &
                5,5,5,5,5,   &
                4,4,4,4,     &
                3,3,3,       &
                2,2,         &
                1,           &
!  S14
                7,7,7,7,7,7,7, &
                6,6,6,6,6,6,   &
                5,5,5,5,5,     &
                4,4,4,4,       &
                3,3,3,         &
                2,2,           &
                1,             &
!  S16
                8,8,8,8,8,8,8,8, &
                7,7,7,7,7,7,7,   &
                6,6,6,6,6,6,     &
                5,5,5,5,5,       &
                4,4,4,4,         &
                3,3,3,           &
                2,2,             &
                1,               &
!  S18
                9,9,9,9,9,9,9,9,9, &
                8,8,8,8,8,8,8,8,   &
                7,7,7,7,7,7,7,     &
                6,6,6,6,6,6,       &
                5,5,5,5,5,         &
                4,4,4,4,           &
                3,3,3,             &
                2,2,               &
                1,                 &
!  S20
                10,10,10,10,10,10,10,10,10,10, &
                9,9,9,9,9,9,9,9,9,             &
                8,8,8,8,8,8,8,8,               &
                7,7,7,7,7,7,7,                 &
                6,6,6,6,6,6,                   &
                5,5,5,5,5,                     &
                4,4,4,4,                       &
                3,3,3,                         &
                2,2,                           &
                1/

      data ixi/1,   &
!  S4
               2,1, &
               2,   &
!  S6
               3,2,1, &
               3,2,   &
               3,     &
!  S8
               4,3,2,1, &
               4,3,2,   &
               4,3,     &
               4,       &
!  S10
               5,4,3,2,1, &
               5,4,3,2,   &
               5,4,3,     &
               5,4,       &
               5,         &
!  S12
               6,5,4,3,2,1, &
               6,5,4,3,2,   &
               6,5,4,3,     &
               6,5,4,       &
               6,5,         &
               6,           &
!  S14
               7,6,5,4,3,2,1, &
               7,6,5,4,3,2,   &
               7,6,5,4,3,     &
               7,6,5,4,       &
               7,6,5,         &
               7,6,           &
               7,             &
!  S16
               8,7,6,5,4,3,2,1, &
               8,7,6,5,4,3,2,   &
               8,7,6,5,4,3,     &
               8,7,6,5,4,       &
               8,7,6,5,         &
               8,7,6,           &
               8,7,             &
               8,               &
!  S18
               9,8,7,6,5,4,3,2,1, &
               9,8,7,6,5,4,3,2,   &
               9,8,7,6,5,4,3,     &
               9,8,7,6,5,4,       &
               9,8,7,6,5,         & 
               9,8,7,6,           &
               9,8,7,             &
               9,8,               &
               9,                 &
!  S20
               10,9,8,7,6,5,4,3,2,1, &
               10,9,8,7,6,5,4,3,2,   &
               10,9,8,7,6,5,4,3,     &
               10,9,8,7,6,5,4,       &
               10,9,8,7,6,5,         &
               10,9,8,7,6,           &
               10,9,8,7,             &
               10,9,8,               &
               10,9,                 &
               10/       

!  Angular weights sum to pi/2 in each octant 

   halfpi = half*pi

!  Offsets into IMU, IETA, IXI and IWGT arrays

   iang(2)  = 1
   iang(4)  = 2
   iang(6)  = 5
   iang(8)  = 11
   iang(10) = 21
   iang(12) = 36 
   iang(14) = 57
   iang(16) = 85 
   iang(18) = 121 
   iang(20) = 166

!  Offsets into the DIRCOS and WEIGHT arrays

   icoff(2)  = 0
   icoff(4)  = 1
   icoff(6)  = 3
   icoff(8)  = 6
   icoff(10) = 10
   icoff(12) = 15
   icoff(14) = 21 
   icoff(16) = 28 
   icoff(18) = 36
   icoff(20) = 46

!  Set the direction cosines and weights; note that the
!  angles are numbered consecutively in an octant.
!  NANGOCT is the number of angles per octant and NS is
!  an offset to the first angle and weight for the set.

   norder  = self% order
   nangoct = norder*(norder + 2)/8
   ns      = iang(norder) - 1
   jcos    = icoff(norder)

   do i=1,nangoct

     amu  = dircos( imu(ns+i)  + jcos )
     aeta = dircos( ieta(ns+i) + jcos )
     axi  = dircos( ixi(ns+i)  + jcos )
     awgt = weight( iwgt(ns+i) + jcos )

!  Octant 1  mu>0, eta>0, xsi>0

     self% omega(1,i) = amu
     self% omega(2,i) = aeta
     self% omega(3,i) = axi
     self% weight(i)  = halfpi*awgt

!  Octant 2  mu<0, eta>0, xsi>0

     self% omega(1,nangoct+i)   = -amu
     self% omega(2,nangoct+i)   =  aeta
     self% omega(3,nangoct+i)   =  axi
     self% weight(nangoct+i)    =  halfpi*awgt

!  Octant 3  mu<0, eta<0, xsi>0

     self% omega(1,2*nangoct+i) = -amu
     self% omega(2,2*nangoct+i) = -aeta
     self% omega(3,2*nangoct+i) =  axi
     self% weight(2*nangoct+i)  =  halfpi*awgt

!  Octant 4  mu>0, eta<0, xsi>0

     self% omega(1,3*nangoct+i) =  amu
     self% omega(2,3*nangoct+i) = -aeta
     self% omega(3,3*nangoct+i) =  axi
     self% weight(3*nangoct+i)  =  halfpi*awgt

!  Octant 5  mu>0, eta>0, xsi<0

     self% omega(1,4*nangoct+i) =  amu
     self% omega(2,4*nangoct+i) =  aeta
     self% omega(3,4*nangoct+i) = -axi
     self% weight(4*nangoct+i)  =  halfpi*awgt

!  Octant 6  mu<0, eta>0, xsi<0

     self% omega(1,5*nangoct+i) = -amu
     self% omega(2,5*nangoct+i) =  aeta
     self% omega(3,5*nangoct+i) = -axi
     self% weight(5*nangoct+i)  =  halfpi*awgt

!  Octant 7  mu<0, eta<0, xsi<0

     self% omega(1,6*nangoct+i) = -amu
     self% omega(2,6*nangoct+i) = -aeta
     self% omega(3,6*nangoct+i) = -axi
     self% weight(6*nangoct+i)  =  halfpi*awgt

!  Octant 8  mu>0, eta<0, xsi<0

     self% omega(1,7*nangoct+i) =  amu
     self% omega(2,7*nangoct+i) = -aeta
     self% omega(3,7*nangoct+i) = -axi
     self% weight(7*nangoct+i)  =  halfpi*awgt

   enddo


   return
   end subroutine quadxyz


