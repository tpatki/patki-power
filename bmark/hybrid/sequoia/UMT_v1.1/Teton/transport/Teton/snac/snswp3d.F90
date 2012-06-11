!***********************************************************************
!                        Version 1:  03/01, PFN                        *
!                                                                      *
!   SNSWP3D  - This routine calculates angular fluxes for a single     *
!              direction for an upstream corner-balance spatial        *
!              discretization in 3D.                                   *
!                                                                      *
!   Input:                                                             *
!                                                                      *
!   Output:                                                            *
!                                                                      *
!***********************************************************************

   subroutine snswp3d(Size, Geom, npart, storePsi,  &
                      next,omega,abdym,sigvol,qc,   &
                      TPSIC,PSIC,PSIB,PSIFP,SOURCE)

   use kind_mod
   use constant_mod
   use Size_mod
   use Geometry_mod

   implicit none

!  Arguments - Types
                                                                                    
   type(MeshSize)            :: Size
   type(Geometry)            :: Geom

!  Arguments

   integer,    intent(in)    :: npart

   integer,    intent(in)    :: next(Size%ncornr+1)

   real(adqt), intent(in)    :: omega(Size%ndim),          & 
                                abdym(Size%nbelem),        &
                                sigvol(npart,Size%ncornr), &
                                qc(npart,Size%ncornr)

   real(adqt), intent(inout) :: tpsic(npart,Size%ncornr),       &
                                psic(npart,Size%ncornr),        &
                                psib(npart,Size%nbelem),        &
                                psifp(npart,Size%maxcf,Size%ncornr), &
                                source(npart,Size%ncornr)

   character(len=8) :: storePsi

!  Local Variables

   integer    :: i,ib,ic,icez,icfp,icface,  &
                 id,ifp,ip,k,ncfaces,nxez

   integer    :: ncornr,nbelem

   integer    :: ic_exit(Size%maxcf)

   real(adqt) :: fouralpha,fouralpha4,aez,area_opp,sigv,sigv2,gtau,sez

   real(adqt) :: cur_opp(npart),coef(npart),src(npart),    &
                 afpm(Size%maxcf),aezm(Size%maxcf),        &
                 coefpsic(Size%maxcf)

!  Constants

   parameter (fouralpha=1.82d0)
   parameter (fouralpha4=5.82d0)

   ncornr = Size%ncornr
   nbelem = Size%nbelem

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

     ic      = next(i)
     ncfaces = Geom%nfpc(ic)

!  Calculate Area_CornerFace dot Omega

     do icface=1,ncfaces

       afpm(icface) = omega(1)*Geom%A_surf(1,icface,1,ic) + &
                      omega(2)*Geom%A_surf(2,icface,1,ic) + &
                      omega(3)*Geom%A_surf(3,icface,1,ic)

       aezm(icface) = omega(1)*Geom%A_surf(1,icface,2,ic) + &
                      omega(2)*Geom%A_surf(2,icface,2,ic) + &
                      omega(3)*Geom%A_surf(3,icface,2,ic)

     enddo

!  Flux calculation

!  Contributions from volume terms

     coef(:) = sigvol(:,ic)
     src(:)  = source(:,ic)

!  Contributions from external corner faces (FP faces)

     do icface=1,ncfaces
       if ( afpm(icface) >= zero ) then
         coef(:) = coef(:) + afpm(icface)
       else
         src(:)  = src(:)  - afpm(icface)*psifp(:,icface,ic)
       endif
     enddo

!  Contributions from interior corner faces (EZ faces)

     nxez = 0

     do icface=1,ncfaces

       aez = aezm(icface)

       if (aez > zero ) then

         area_opp       = zero
         cur_opp(:)     = zero

         nxez           = nxez + 1
         icez           = Geom%Connect(3,icface,ic)
         ic_exit(nxez)  = icez
         coefpsic(nxez) = aez

         ifp = icface

         do k=1,ncfaces-2

           ifp = mod(ifp,ncfaces) + 1

           if ( afpm(ifp) < zero ) then
             area_opp   = area_opp   - afpm(ifp)
             cur_opp(:) = cur_opp(:) - afpm(ifp)*psifp(:,ifp,ic)
           endif

         enddo

         TestOppositeFace: if (area_opp > zero) then

           do ip=1,npart

             sigv       = sigvol(ip,ic)
             sigv2      = sigv*sigv

             gtau       = aez*aez*( fouralpha*sigv2 +              &
                          aez*(four*sigv + three*aez) )/           &
                        ( four*sigv2*sigv2 + aez*(six*sigv*sigv2 + &
                          aez*(fouralpha4*sigv2 + aez*(six*sigv + three*aez))) ) 

             coef(ip)   = coef(ip) + aez
             sez        = gtau*sigv*( cur_opp(ip)/area_opp - qc(ip,ic) ) +  &
                          half*aez*(one - gtau)*( qc(ip,ic) - qc(ip,icez) )
             src(ip)    = src(ip) + sez
             source(ip,icez) = source(ip,icez) - sez

           enddo

         else

           do ip=1,npart
             coef(ip)        = coef(ip) + aez
             sez             = half*aez*( qc(ip,ic) - qc(ip,icez) )
             src(ip)         = src(ip)         + sez
             source(ip,icez) = source(ip,icez) - sez
           enddo

         endif TestOppositeFace

       endif

     enddo

!  Corner angular flux

     tpsic(:,ic) = src(:)/coef(:)

!  Calculate the angular flux exiting all "FP" surfaces
!  and the current exiting all "EZ" surfaces.
!  The downstream corner index is "ic_exit."

!  Zone Interior or "EZ" Faces

     do icface=1,nxez
       icez           = ic_exit(icface)
       source(:,icez) = source(:,icez) + coefpsic(icface)*tpsic(:,ic)
     enddo

!  Zone Exterior or "FP" Faces

     do icface=1,ncfaces

       if (afpm(icface) > zero) then

         icfp = Geom%Connect(1,icface,ic)
         id   = Geom%Connect(2,icface,ic)

         if (icfp == 0) then
           psib(:,id)       = tpsic(:,ic)
         else
           psifp(:,id,icfp) = tpsic(:,ic)
         endif

       endif

     enddo

   enddo CornerLoop

!  Copy temporary flux array into the global one

   if (storePsi == 'yes') then
     psic(:,:) = tpsic(:,:)
   endif


   return
   end subroutine snswp3d


