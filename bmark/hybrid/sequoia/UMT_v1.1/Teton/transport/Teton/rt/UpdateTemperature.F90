!***********************************************************************
!                        Version 1:  05/92, PFN                        *
!                                                                      *
!   RTTE   - Calculates electron temperature and energy change.        *
!                                                                      *
!   Input:   tecn   - corner electron temperature from previous time   *
!                     step                                   (T)       *
!            bc     - group Planckian emission source        (E/A/t)   *
!            etac   - grey weighting factor                  (0)       *
!            cve    - electron specific heat                 (E/m/t)   *
!            siga   - group absorption cross section         (1/L)     *
!            xeicp  - electron/ion coefficient               (0)       *
!            ematc  - specific energy rate from matter sources (E/m/t) *
!            CToZone- zone number for a given corner                   *
!            ncornr - number of corners                                *
!                                                                      *
!   Output:  TEC    - corner electron temperature            (T)       *
!            DENEC  - corner electron energy change          (E/m)     *
!                                                                      *
!***********************************************************************
   subroutine UpdateTemperature(Size, Geom, Mat, Quad, dtrad)

   use kind_mod
   use constant_mod
   use radconstant_mod
   use Size_mod
   use Geometry_mod
   use Material_mod
   use QuadratureList_mod

   implicit none

!  Arguments - Types
                                                                                    
   type(MeshSize)            :: Size
   type(Geometry)            :: Geom 
   type(Material)            :: Mat
   type(QuadratureList)      :: Quad

!  Arguments

   real(adqt), intent(in)    :: dtrad
 
!  Local

   integer    :: ic,ig,iz,iter,MaxIter,ngr,ngrp

   real(adqt) :: chi,chimin,ac,ccon,ex,temp,t3,t4,one_etac,  &
                 gnukt,dbdtc,sigdbdt,sum,tecOld,MaxError,error

   real(adqt) :: deltaE, echeck

   real(adqt) :: gnu(Size%ngr+1),x(Size%ngr+1),  &
                 dbex(Size%ngr+1),frac(Size%ngr+1)

!  Constants

   parameter (chimin=1.0d-12)
   parameter (MaxError=1.0e-8)
   parameter (MaxIter=50)

   ac     = rad_constant*speed_light
   ccon   = rad_constant2*speed_light
   ngr    = Size%ngr
   ngrp   = ngr + 1

   gnu(:) = getEnergyGroups(Quad,ngr)

!  Compute the fraction of the total emission in each energy group
!  This fraction is calculated for each corner.  The input for RTPLNK
!  is (h*nu)/(k*Te).  If this is a single group calculation the
!  emission source is ac*T^4 and the derivative is 4*ac*T^3.

!      if (ngr == 1) then
!
!        do ic=1,Size%ncornr
!          iz         = Geom%CToZone(ic)
!          bc(1,ic)   =      ac*tec(ic)*tec(ic)*tec(ic)*tec(ic)
!          dbdtc      = four*ac*tec(ic)*tec(ic)*tec(ic)
!          chic(1,ic) = one
!          sigdbdt    = Mat%siga(1,iz)*dbdtc*dtrad
!          etac(ic)   = sigdbdt/(Mat%rho(iz)*Mat%cve(iz) + sigdbdt)
!        enddo
!
!      else

!*********************************************
!* Begin outer loop over corners             *
!*********************************************

   CornerLoop: do ic=1,Size%ncornr


     iter = 0

     TeIteration: do 

     iter   = iter + 1
     tecOld = Mat%tec(ic)

!  Load powers of the corner temperature into scalars

     temp = Mat%tec(ic)
     t3   = ccon*temp*temp*temp
     t4   =   ac*temp*temp*temp*temp

!  Compute hnu/kt at upper energy boundary and
!  exponentials for Planckian Derivative

     do ig=1,ngr+1
       gnukt    = gnu(ig)/temp
       x(ig)    = gnukt
       ex       = exp(-gnukt)
       dbex(ig) = gnukt*gnukt*gnukt*gnukt*ex/(one - ex)
     enddo

     call rtplnk(ngrp,x,FRAC)

!  Use a lower bound of zero in calculating the Planckian

     frac(1)     = zero
     frac(ngr+1) = one
     dbex(1)     = zero

!  Compute the Planckian emission source for all groups

     do ig=1,ngr
       Mat%bc(ig,ic) = t4*(frac(ig+1) - frac(ig))
     enddo

!  Compute the spectral functions CHIC and ETAC using the
!  Planckian derivative (DBDTC  units:  E/A/t/T )

     iz  = Geom%CToZone(ic)
     sum = zero

     do ig=1,ngr
       dbdtc = t3*(dbex(ig) - dbex(ig+1)) + four*Mat%bc(ig,ic)/temp

       sum             = sum + Mat%siga(ig,iz)*dbdtc
       Mat%chic(ig,ic) = Mat%siga(ig,iz)*dbdtc
     enddo

!*********************************************
!* Complete the calculation of CHI & ETA     *
!*********************************************

     Mat%etac(ic) = dtrad*sum/(Mat%rho(iz)*Mat%cve(iz) + dtrad*sum)
     one_etac = Mat%rho(iz)*Mat%cve(iz)/(Mat%rho(iz)*Mat%cve(iz) + dtrad*sum)

     do ig=1,ngr
       chi = Mat%chic(ig,ic)/sum
       if (chi > chimin) then
         Mat%chic(ig,ic) = chi
       else
         Mat%chic(ig,ic) = zero
       endif
     enddo

!  Normalize CHI

     sum = zero

     do ig=1,ngr
       sum = sum + Mat%chic(ig,ic)
     enddo

     do ig=1,ngr
       Mat%chic(ig,ic) = Mat%chic(ig,ic)/sum
     enddo

!  The change in energy is the net specific energy deposited
!  during the cycle.  Electron/ion coupling term is treated
!  implicitly.

     sum = Mat%AbsorptionRate(ic)

     do ig=1,ngr
       sum = sum - Mat%siga(ig,iz)*Mat%bc(ig,ic)
     enddo

     deltaE        = dtrad*( Mat%ematc(ic) - Mat%decompton(ic) + sum/Mat%rho(iz) )
     Mat%denec(ic) = Mat%etac(ic)*Mat%denec(ic) + one_etac*deltaE
     Mat%tec(ic)   = max(Mat%tecn(ic) + Mat%denec(ic)/Mat%cve(iz),Size%tfloor)

     error  = abs( Mat%tec(ic) - tecOld )/Mat%tec(ic)
     echeck = abs( Mat%denec(ic) - deltaE )
     error  = max( error,echeck )

     if ( error < MaxError .or. iter >= MaxIter ) then
       exit TeIteration
     else
       cycle TeIteration
     endif


     enddo TeIteration

!*********************************************
!* End outer loop over corners               *
!*********************************************

   enddo CornerLoop

!      endif

 
   return
   end subroutine UpdateTemperature 

