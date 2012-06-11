!***********************************************************************
!                        Version 1:  07/2003, PFN                      *
!                                                                      *
!   QUADPRODUCT - Computes a product quadrature set based on the       *
!                 number of polar and azimuthal directions and the     *
!                 specified polar axis.                                *
!                                                                      *
!   Input:   nang       - number of angles                             *
!            npolar     - number of polar angles                       *
!            nazimuthal - number of azimuthal angles                   *
!            polaraxis  - polar axis                                   *
!                                                                      *
!   Output:  OMEGA  - group dependent direction cosines (mu,eta,xi)    *
!            QUADWT - group dependent quadrature weights               *
!                                                                      *
!   Allowed values:  1 <= npolar <= 7, 1 <= nazimuthal <= 7            *
!                                                                      *
!                                                                      *
!***********************************************************************

   subroutine quadProduct(self)

   use kind_mod
   use constant_mod
   use Quadrature_mod

   implicit none

!  Arguments

   type(Quadrature)          :: self

!  Local

   integer    :: i,iPhi,jTheta,m,Phi1,Phi2,Theta1,Theta2,nangoct

   integer    :: npolar,nazimuthal,polaraxis

   integer    :: first(7),last(7) 

   real(adqt) :: cosTheta

   real(adqt) :: sineTheta(28),sinePhi(28),wgtTheta(28),wgtPhi(28)

   real(adqt) :: omegaX(self% npolar*self% nazimuthal),  &
                 omegaY(self% npolar*self% nazimuthal),  &
                 omegaZ(self% npolar*self% nazimuthal),  &
                 weight(self% npolar*self% nazimuthal)

!  Constants

   data sineTheta/                                                   &
!  N=1
                  0.78539816339744830962d0,                          &
!  N=2
                  0.91444794846597529652d0,0.39937356388239564745d0, &
!  N=3
                  0.95449676734330672931d0,0.63997119623407528864d0, &
                  0.23115229612788473342d0,                          &
!  N=4
                  0.97184038388960596176d0,0.76571987518370649204d0, &
                  0.44521741340559928669d0,0.14924914657313399448d0, &
!  N=5            
                  0.98087661373267218037d0,0.83675749818626288158d0, &
                  0.59256413167240468953d0,0.32189976003062284270d0, &
                  0.10394690547502655425d0,                          &
!  N=6
                  0.98617175571615573920d0,0.88018873643097689420d0, &
                  0.69176378901922003237d0,0.46241493107711946758d0, &
                  0.24183802247064124945d0,0.07642225770189770128d0, &

!  N=7 
                  0.98953784621666489095d0,0.90849901890320575483d0, &
                  0.76007398923148997919d0,0.56914132986884449101d0, &
                  0.36738087383424054715d0,0.18767440992041978906d0, &
                  0.05849788427341291928d0  /

   data  wgtTheta/                                                   &
!  N=1
                  2.00000000000000000000d0,                          &
!  N=2
                  1.49890816188477551090d0,0.50109183811522448914d0, &
!  N=3
                  1.14648583618912154480d0,0.68291251586562472107d0, &
                  0.17060164794525373411d0,                          &
!  N=4
                  0.92001900147668547407d0,0.67767883313379918716d0, &
                  0.33020195674768538787d0,0.07210020864182995091d0, &
!  N=5            
                  0.76592763590452492787d0,0.62547195971639005921d0, &
                  0.39877206438856428625d0,0.17452600064179641958d0, &
                  0.03530233934872430709d0,                          &
!  N=6
                  0.65517114355836898074d0,0.56708942603179771094d0, &
                  0.41549493554107503800d0,0.24339440848003601915d0, &
                  0.09964572033500919023d0,0.01920436605371306093d0, &

!  N=7
                  0.57200900224011059058d0,0.51333899713635392791d0, &
                  0.40835903908312796583d0,0.27953568373499582842d0, &
                  0.15485770233502822831d0,0.06059668882540333022d0, &
                  0.01130288664498012874d0  /

   data  sinePhi/                                                    &
!  N=1
                  0.70710678118654752440d0,                          &
!  N=2
                  0.94437822542882369865d0,0.32886131930633898750d0, &
!  N=3
                  0.98372040906912566306d0,0.70710678118654752440d0, &
                  0.17970575055037072442d0,                          &
!  N=4
                  0.99371728570999428504d0,0.86659690871391831733d0, &
                  0.49900881536049112442d0,0.11191941780210254430d0, &
!  N=5
                  0.99710141659304158813d0,0.93298499937402718367d0, &
                  0.70710678118654752440d0,0.35991525522412424648d0, &
                  0.07608393410010899993d0,                          &
!  N=6
                  0.99848732466459216190d0,0.96323923893097961038d0, &
                  0.82449355807562840206d0,0.56587133934472275532d0, &
                  0.26864506059793314975d0,0.05498238339818786885d0, &
!  N=7
                  0.99913640643269553161d0,0.97833432629386338436d0, &
                  0.89058738977758683600d0,0.70710678118654752440d0, &
                  0.45481216031362290127d0,0.20703126815805493628d0, &
                  0.04155046739519842173d0  /

   data  wgtPhi/                                                     &
!  N=1
                  1.57079632679489661920d0,                          &
!  N=2
                  0.78539816339744830962d0,0.78539816339744830962d0, &
!  N=3
                  0.44149240880482295316d0,0.68781150918525071291d0, &
                  0.44149240880482295316d0,                          &
!  N=4
                  0.27904950926910706110d0,0.50634865412834124852d0, &
                  0.50634865412834124852d0,0.27904950926910706110d0, &
!  N=5
                  0.19132072470271307895d0,0.37485557661388630346d0, &
                  0.43844372416169785442d0,0.37485557661388630346d0, &
                  0.19132072470271307895d0,                          &
!  N=6
                  0.13899122710158582153d0,0.28498479759480649631d0, &
                  0.36142213870105599178d0,0.36142213870105599178d0, &
                  0.28498479759480649631d0,0.13899122710158582153d0, &
!  N=7
                  0.10540326271170086590d0,0.22257341924255361519d0, &
                  0.29665946619243169963d0,0.32152403050152425778d0, &
                  0.29665946619243169963d0,0.22257341924255361519d0, &
                  0.10540326271170086590d0  /

   data first /1,2,4, 7,11,16,22/
   data last  /1,3,6,10,15,21,28/

!  Constants

   npolar     = self% npolar
   nazimuthal = self% nazimuthal
   polaraxis  = self% polaraxis

   Phi1    = first(nazimuthal) 
   Phi2    =  last(nazimuthal) 
   Theta1  = first(npolar) 
   Theta2  =  last(npolar) 

   nangoct = npolar*nazimuthal

!  Set omegaX, omegaY, omegaZ based on the choice of polar axis

   m = 0
   do iPhi=Phi1,Phi2
     do jTheta=Theta1,Theta2

       cosTheta = sqrt( one - sineTheta(jTheta)*sineTheta(jTheta) )
       m = m + 1

       if (polaraxis == 1) then
         omegaX(m) = cosTheta
         omegaZ(m) = sineTheta(jTheta)*sinePhi(iPhi)
         omegaY(m) = sqrt( one - omegaZ(m)*omegaZ(m) - omegaX(m)*omegaX(m) )
       elseif (polaraxis == 2) then
         omegaY(m) = cosTheta
         omegaX(m) = sineTheta(jTheta)*sinePhi(iPhi)
         omegaZ(m) = sqrt( one - omegaX(m)*omegaX(m) - omegaY(m)*omegaY(m) )
       elseif (polaraxis == 3) then
         omegaZ(m) = cosTheta
         omegaY(m) = sineTheta(jTheta)*sinePhi(iPhi)
         omegaX(m) = sqrt( one - omegaZ(m)*omegaZ(m) - omegaY(m)*omegaY(m) )
       endif

       weight(m) = wgtTheta(jTheta)*wgtPhi(iPhi)

     enddo
   enddo

!  Set the direction cosines and weights; note that the
!  angles are numbered consecutively in an octant.
!  NANGOCT is the number of angles per octant.


   do i=1,nangoct

!  Octant 1  mu>0, eta>0, xsi>0

     self% omega(1,i) = omegaX(i) 
     self% omega(2,i) = omegaY(i) 
     self% omega(3,i) = omegaZ(i) 
     self% weight(i)  = weight(i) 

!  Octant 2  mu<0, eta>0, xsi>0

     self% omega(1,nangoct+i)   = -omegaX(i)
     self% omega(2,nangoct+i)   =  omegaY(i) 
     self% omega(3,nangoct+i)   =  omegaZ(i) 
     self% weight(nangoct+i)    =  weight(i) 

!  Octant 3  mu<0, eta<0, xsi>0

     self% omega(1,2*nangoct+i) = -omegaX(i)
     self% omega(2,2*nangoct+i) = -omegaY(i)
     self% omega(3,2*nangoct+i) =  omegaZ(i) 
     self% weight(2*nangoct+i)  =  weight(i) 

!  Octant 4  mu>0, eta<0, xsi>0

     self% omega(1,3*nangoct+i) =  omegaX(i) 
     self% omega(2,3*nangoct+i) = -omegaY(i)
     self% omega(3,3*nangoct+i) =  omegaZ(i) 
     self% weight(3*nangoct+i)  =  weight(i) 

!  Octant 5  mu>0, eta>0, xsi<0

     self% omega(1,4*nangoct+i) =  omegaX(i) 
     self% omega(2,4*nangoct+i) =  omegaY(i) 
     self% omega(3,4*nangoct+i) = -omegaZ(i)
     self% weight(4*nangoct+i)  =  weight(i) 

!  Octant 6  mu<0, eta>0, xsi<0

     self% omega(1,5*nangoct+i) = -omegaX(i)
     self% omega(2,5*nangoct+i) =  omegaY(i) 
     self% omega(3,5*nangoct+i) = -omegaZ(i)
     self% weight(5*nangoct+i)  =  weight(i) 

!  Octant 7  mu<0, eta<0, xsi<0

     self% omega(1,6*nangoct+i) = -omegaX(i)
     self% omega(2,6*nangoct+i) = -omegaY(i)
     self% omega(3,6*nangoct+i) = -omegaZ(i)
     self% weight(6*nangoct+i)  =  weight(i) 

!  Octant 8  mu>0, eta<0, xsi<0

     self% omega(1,7*nangoct+i) =  omegaX(i) 
     self% omega(2,7*nangoct+i) = -omegaY(i)
     self% omega(3,7*nangoct+i) = -omegaZ(i)
     self% weight(7*nangoct+i)  =  weight(i) 

   enddo


   return
   end subroutine quadProduct


