!***********************************************************************
!                        Version 1:  07/01, PFN                        *
!                                                                      *
!   FIXCYCLES    - This routine fixes cycles in the mesh by setting    *
!                  the incident flux using the old value of the        *
!                  angular flux.                                       *
!                                                                      *
!   Input:                                                             *
!                                                                      *
!   Output:                                                            *
!                                                                      *
!***********************************************************************
   subroutine fixcycles(Size, Geom, QuadSet, npart, m, storePsi,  &
                        omega,sigvol,sigca,qc,psic,psib,PSIFP,SOURCE)

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

   real(adqt), intent(in)    :: omega(Size%ndim),           &
                                sigvol(npart,Size%ncornr),  &
                                sigca(npart,Size%ncornr),   &
                                qc(npart,Size%ncornr),      &
                                psic(npart,Size%ncornr),    &
                                psib(npart,Size%nbelem) 

   real(adqt), intent(inout) :: psifp(npart,Size%maxcf,Size%ncornr), &
                                source(npart,Size%ncornr)

   character(len=8), intent(in) :: storePsi 

!  Local Variables

   integer    :: i,ic,icp,icface,ifp,icfp,ip, &
                 k,moff,n,ncfaces,dsface,ib,ndim

   real(adqt) :: fouralpha,fouralpha4,aezm,afpm,area_opp,  &
                 sigv,sigv2,gtau,sez,R_aez,rr,sigA,sigA2

   real(adqt) :: cur_opp(npart)

!  Constants

   parameter (fouralpha=1.82d0)
   parameter (fouralpha4=5.82d0)

   ndim = Size%ndim

!  Correct cycles if present

   n    = QuadSet% numcycles(1,m)
   moff = QuadSet% numcycles(2,m)

!  For acceleration we do not store old angular fluxes so
!  set PSIFP, CUREZ to 0

   TestStorePsi: if (storePsi == 'no') then

     CycleLoop1: do i=1,n

       ic     = QuadSet% listcycles(1,moff+i)
       icp    = QuadSet% listcycles(2,moff+i)
       dsface = QuadSet% listcycles(3,moff+i)

       if ( Geom%CToZone(ic) /= Geom%CToZone(icp) ) then
         psifp(:,dsface,icp) = zero
       endif

     enddo CycleLoop1

   else

!  For regular sweeps use old angular fluxes to set PSIFP, CUREZ

     CycleLoop2: do i=1,n

       ic     = QuadSet% listcycles(1,moff+i)
       icp    = QuadSet% listcycles(2,moff+i)
       dsface = QuadSet% listcycles(3,moff+i) 

       if ( Geom%CToZone(ic) /= Geom%CToZone(icp) ) then

!      This is an FP face

         psifp(:,dsface,icp) = psic(:,ic) 

       else

!      This is an EZ face and requires a lot more work

         icface  = Geom%Connect(4,dsface,icp)
         ifp     = icface
         ncfaces = Geom%nfpc(ic)

         if (ndim == 3) then

!      Calculate Area_CornerFace dot Omega on the EZ face

           aezm   = omega(1)*Geom%A_surf(1,icface,2,ic) + &
                    omega(2)*Geom%A_surf(2,icface,2,ic) + &
                    omega(3)*Geom%A_surf(3,icface,2,ic)

!      Calculate the "opposite" current from incident FP faces
                                                
           area_opp   = zero
           cur_opp(:) = zero

           do k=1,ncfaces-2

             ifp  = mod(ifp,ncfaces) + 1
             icfp = Geom%Connect(1,ifp,ic)
             ib   = Geom%Connect(2,ifp,ic)

             afpm = omega(1)*Geom%A_surf(1,ifp,1,ic) + &
                    omega(2)*Geom%A_surf(2,ifp,1,ic) + &
                    omega(3)*Geom%A_surf(3,ifp,1,ic)

             if ( afpm < zero ) then

               area_opp = area_opp - afpm

               if (icfp == 0) then
                 cur_opp(:) = cur_opp(:) - afpm*psib(:,ib)
               else
                 cur_opp(:) = cur_opp(:) - afpm*psic(:,icfp)
               endif

             endif

           enddo

           TestOppositeFace: if (area_opp > zero) then

             do ip=1,npart

               sigv  = sigvol(ip,ic)
               sigv2 = sigv*sigv

               gtau  = aezm*aezm*( fouralpha*sigv2 +    &
                       aezm*(four*sigv + three*aezm) )/ &
                     ( four*sigv2*sigv2 + aezm*(six*sigv*sigv2 + &
                       aezm*(fouralpha4*sigv2 + aezm*(six*sigv + three*aezm))) )

               sez   = gtau*sigv*(cur_opp(ip)/area_opp - qc(ip,ic)) +  &
                       half*aezm*(one - gtau)*( qc(ip,ic) - qc(ip,icp) )

!              Compute the downstream current

               source(ip,icp) = source(ip,icp) + aezm*psic(ip,ic) - sez

             enddo

           else

             source(:,icp) = source(:,icp) + aezm*   &
                           ( psic(:,ic) - half*(qc(:,ic) - qc(:,icp)) )

           endif TestOppositeFace

         elseif (ndim == 2) then

           ifp   = mod(icface,ncfaces) + 1

           afpm  = omega(1)*Geom%A_surf(1,ifp,1,ic) +  &
                   omega(2)*Geom%A_surf(2,ifp,1,ic)

           aezm  = omega(1)*Geom%A_surf(1,icface,2,ic) + &
                   omega(2)*Geom%A_surf(2,icface,2,ic)

           R_aez = Geom%rbar(icface,2,ic)*aezm
           rr    = Geom%rbar(icface,2,ic)

           if (afpm < zero) then
             do ip=1,npart
               sigA    = sigca(ip,ic)
               sigA2   = sigca(ip,ic)*sigca(ip,ic)
                                                                                           
               gtau    = aezm*aezm*( fouralpha*sigA2 +              &
                         aezm*(four*sigA + three*aezm) )/           &
                       ( four*sigA2*sigA2 + aezm*(six*sigA*sigA2 +  &
                         aezm*(fouralpha4*sigA2 + aezm*             &
                        (six*sigA + three*aezm))) )
                                                                                           
               sez     = gtau*rr*sigA*( psifp(ip,ifp,ic) - qc(ip,ic) ) +  &
                         half*R_aez*(one - gtau)*( qc(ip,ic) - qc(ip,icp) )
                                                                                           
               source(ip,icp) = source(ip,icp) + R_aez*psic(ip,ic) - sez
             enddo
           else
             source(:,icp) = source(:,icp) + R_aez*       &
                           ( psic(:,ic) - half*(qc(:,ic) - qc(:,icp)) ) 
           endif

         endif

       endif

     enddo CycleLoop2

   endif TestStorePsi


   return
   end subroutine fixcycles 
 
