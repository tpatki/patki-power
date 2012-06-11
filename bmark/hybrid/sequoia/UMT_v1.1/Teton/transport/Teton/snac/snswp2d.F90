!***********************************************************************
!                        Version 1:  05/96, PFN                        *
!                                                                      *
!   SNSWP2D -  Calculates mesh parameters and sources used in the 2D   *
!              upstream corner-balance spatial discretization for a    *
!              single direction (mu,xi).  These quantities are stored  *
!              in the order in which they will be used in the grid     *
!              sweep (SNSWP2D) to improve cache performance.           *
!                                                                      *
!   Input:                                                             *
!                                                                      *
!   Output:  PSIC   - corner angular photon intensity     (E/A/t)      *
!                                                                      *
!***********************************************************************

   subroutine snswp2d(Size, Geom, QuadSet,           &
                      npart,m,storePsi,              &
                      next,abdym,sigcv,sigca,qc,     &
                      PSIMMH,TPSIC,PSIC,PSIB,PSIFP,SOURCE)

   use kind_mod
   use constant_mod
   use Size_mod
   use Geometry_mod
   use Quadrature_mod

   implicit none

!  Arguments - Types
                                                                                           
   type(MeshSize)            :: Size
   type(Geometry)            :: Geom
   type(Quadrature)          :: QuadSet

!  Arguments

   integer,    intent(in)    :: npart,m

   integer,    intent(in)    :: next(Size%ncornr+1)

   real(adqt), intent(in)    :: abdym(Size%nbelem),        & 
                                sigcv(npart,Size%ncornr),  &
                                sigca(npart,Size%ncornr),  &
                                qc(npart,Size%ncornr)

   real(adqt), intent(inout) :: psimmh(npart,Size%ncornr),    &
                                tpsic(npart,Size%ncornr),     &
                                psic(npart,Size%ncornr),      &
                                psib(npart,Size%nbelem),      &
                                psifp(npart,2,Size%ncornr),   &
                                source(npart,Size%ncornr)

   character(len=8), intent(in) :: storePsi 

!  Local

   integer    :: i,ib,ic,ic1,ic2,id,iexit,ip,icface,iz

   integer    :: ncornr,nbelem,angletype

   real(adqt) :: fouralpha,fouralpha4,fac,quadwt,quadalpha,quadtau,  &
                 rr,sez,gtau,sigA,sigA2

   real(adqt) :: omega(2),aez(2),afp(2),R_aez(2),R_afp(2)

   real(adqt) :: coef(npart),src(npart)

!  Constants

   parameter (fouralpha=1.82d0)
   parameter (fouralpha4=5.82d0)

   ncornr    = Size%ncornr
   nbelem    = Size%nbelem

   omega(:)  = QuadSet% omega(:,m)
   quadwt    = QuadSet% weight(m)
   quadalpha = QuadSet% alpha(m)
   quadtau   = QuadSet% tau(m) 
   angletype = QuadSet% AngleType(m)

!  Constants

   if (angletype == -1) then
     fac = zero
   else
     fac = omega(1) + quadalpha/(quadwt*quadtau)
   endif

!  Set PSIFP on incident boundary surfaces

   do ib=1,nbelem

     if (abdym(ib) < zero ) then

       ic = Geom%BdyToC(1,ib)
       id = Geom%BdyToC(2,ib)

       psifp(:,id,ic) = psib(:,ib)

     endif

   enddo

!  Loop through all of the corners using the NEXT list

   CornerLoop: do i=1,ncornr

     ic    = next(i)
     iz    = Geom%CToZone(ic)
     ic1   = Geom%Connect(3,1,ic)
     ic2   = Geom%Connect(3,2,ic)

!  Calculate Area_CornerFace dot Omega

     do icface=1,2
       afp(icface)   = omega(1)*Geom%A_surf(1,icface,1,ic) +  &
                       omega(2)*Geom%A_surf(2,icface,1,ic)

       aez(icface)   = omega(1)*Geom%A_surf(1,icface,2,ic) +  &
                       omega(2)*Geom%A_surf(2,icface,2,ic)

       R_afp(icface) = Geom%rbar(icface,1,ic)*afp(icface) 
       R_aez(icface) = Geom%rbar(icface,2,ic)*aez(icface) 
     enddo

!  Contributions from volume terms (angletype = -1 is a starting direction)

     if (angletype == -1) then
       coef(:) = sigcv(:,ic)
       src(:)  = source(:,ic)
     else
       coef(:) = sigcv(:,ic)  + Geom%areac(ic)*fac
       src(:)  = source(:,ic) + Geom%areac(ic)*fac*psimmh(:,ic)
     endif

!  Contributions from external corner faces (FP faces)

     do icface=1,2
       if ( afp(icface) < zero ) then
         coef(:) = coef(:) - R_afp(icface)
         src(:)  = src(:)  - R_afp(icface)*psifp(:,icface,ic)
       endif
     enddo

!  Contributions from interior corner faces (EZ faces)

     if (aez(1) > zero) then

       rr = Geom%rbar(1,2,ic)

       if (afp(2) < zero) then
         do ip=1,npart
           sigA    = sigca(ip,ic) 
           sigA2   = sigca(ip,ic)*sigca(ip,ic)

           gtau    = aez(1)*aez(1)*( fouralpha*sigA2 +            &
                     aez(1)*(four*sigA + three*aez(1)) )/         &
                   ( four*sigA2*sigA2 + aez(1)*(six*sigA*sigA2 +  &
                     aez(1)*(fouralpha4*sigA2 + aez(1)*           &
                    (six*sigA + three*aez(1)))) )

           sez     = gtau*rr*sigA*( psifp(ip,2,ic) - qc(ip,ic) ) +  &
                     half*R_aez(1)*(one - gtau)*( qc(ip,ic) - qc(ip,ic1) )

           src(ip) = src(ip) + sez
           source(ip,ic1) = source(ip,ic1) - sez
         enddo
       else
         do ip=1,npart
           sez            = half*R_aez(1)*(qc(ip,ic) - qc(ip,ic1))
           src(ip)        = src(ip)        + sez 
           source(ip,ic1) = source(ip,ic1) - sez
         enddo 
       endif

     else

       coef(:) = coef(:) - R_aez(1)

     endif

     if (aez(2) > zero) then

       rr = Geom%rbar(2,2,ic)

       if (afp(1) < zero) then
         do ip=1,npart
           sigA    = sigca(ip,ic)
           sigA2   = sigca(ip,ic)*sigca(ip,ic)
                                                                                         
           gtau    = aez(2)*aez(2)*( fouralpha*sigA2 +            &
                     aez(2)*(four*sigA + three*aez(2)) )/         &
                   ( four*sigA2*sigA2 + aez(2)*(six*sigA*sigA2 +  &
                     aez(2)*(fouralpha4*sigA2 + aez(2)*           &
                    (six*sigA + three*aez(2)))) )
                                                                                         
           sez     = gtau*rr*sigA*( psifp(ip,1,ic) - qc(ip,ic) ) +  &
                     half*R_aez(2)*(one - gtau)*( qc(ip,ic) - qc(ip,ic2) )
                                                                                         
           src(ip) = src(ip) + sez
           source(ip,ic2) = source(ip,ic2) - sez
         enddo
       else
         do ip=1,npart
           sez            = half*R_aez(2)*(qc(ip,ic) - qc(ip,ic2))
           src(ip)        = src(ip)        + sez
           source(ip,ic2) = source(ip,ic2) - sez
         enddo
       endif

     else

       coef(:) = coef(:) - R_aez(2)

     endif

!  Corner angular flux
          
     tpsic(:,ic) = src(:)/coef(:)

!  Calculate fluxes on exiting faces

!    Zone Interior or "EZ" Faces

     if (aez(1) > zero) then
       source(:,ic1) = source(:,ic1) + R_aez(1)*tpsic(:,ic)
     endif

     if (aez(2) > zero) then
       source(:,ic2) = source(:,ic2) + R_aez(2)*tpsic(:,ic)
     endif

!   Zone Exterior or "FP" Faces

     do icface=1,2

       if (afp(icface) > zero) then
         iexit = Geom%Connect(1,icface,ic)
         id    = Geom%Connect(2,icface,ic)

         if (iexit == 0) then
           psib(:,id)        = tpsic(:,ic)
         else
           psifp(:,id,iexit) = tpsic(:,ic)
         endif

       endif

     enddo

   enddo CornerLoop

   if (storePsi == 'yes') then
     psic(:,:) = tpsic(:,:)
   endif

!  Set the m-1/2 array (psimmh) for the next angle

   call snrzammh(angletype,ncornr,npart,quadtau,tpsic,PSIMMH)
 

   return
   end subroutine snswp2d

