!***********************************************************************
!                        Version 1:  09/96, PFN                        *
!                                                                      *
!   SNNEED - This routine builds the NEED array which indicates the    *
!            number of incoming fluxes required to compute the         *
!            outgoing flux for a particular direction (this is the     *
!            number of incoming sides or faces the corner has for      *
!            this direction).  This routine is a decendant of SNRZANEE *
!            by MLA.                                                   *
!                                                                      *
!   Input:                                                             *
!                                                                      *
!   Output:                                                            *
!                                                                      *
!***********************************************************************

   subroutine snneed(Size, Geom, omega, NEED, DOWNSTREAMC) 

   use kind_mod
   use constant_mod
   use Size_mod
   use Geometry_mod

   implicit none

!  Arguments - Types
                                                                                   
   type(MeshSize)            :: Size
   type(Geometry)            :: Geom

!  Arguments

   integer,    intent(inout) :: need(Size%ncornr+1),  &
                                DownStreamC(Size%maxcf,2,Size%ncornr)

   real(adqt), intent(in)    :: omega(Size%ndim)

!  Local Variables

   integer    :: ic,icez,icfp,id,idez,idfp,izero,ncornr,ndim

   real(adqt) :: afpm,aezm 

!  Constants

   parameter (izero=0)

   ncornr = Size%ncornr
   ndim   = Size%ndim
 
!  For incoming corner-faces we increment the need array; for outgoing
!  corner-faces we put the downstream corner number into an index list.

   need(:)            = izero
   DownStreamC(:,:,:) = ncornr + 1


   CornerLoop: do ic=1,ncornr

     CornerFaceLoop: do id=1,Geom%nfpc(ic)

!  Get downstream corner number

       icfp = Geom%Connect(1,id,ic)
       idfp = Geom%Connect(2,id,ic)
       icez = Geom%Connect(3,id,ic)
       idez = Geom%Connect(4,id,ic)

!  Omega dot Outward normal - IMPORTANT: the dot product must be
!  coded this way to be compatible with the coding in SNSWP3D and SNSWP2D.
!  Failure to comply results in wrong answers!

       if (ndim == 3) then

         afpm = omega(1)*Geom%A_surf(1,id,1,ic) +  &
                omega(2)*Geom%A_surf(2,id,1,ic) +  &
                omega(3)*Geom%A_surf(3,id,1,ic) 

         aezm = omega(1)*Geom%A_surf(1,id,2,ic) +  &
                omega(2)*Geom%A_surf(2,id,2,ic) +  &
                omega(3)*Geom%A_surf(3,id,2,ic)

       elseif (ndim == 2) then

         afpm = omega(1)*Geom%A_surf(1,id,1,ic) +  &
                omega(2)*Geom%A_surf(2,id,1,ic)

         aezm = omega(1)*Geom%A_surf(1,id,2,ic) +  &
                omega(2)*Geom%A_surf(2,id,2,ic)

       endif 

!  Corner Face EZ (neighboring corner, same zone)

       if (icez > ic) then

         if (aezm < zero) then
           need(ic)                 = need(ic) + 1
           DownStreamC(idez,1,icez) = ic
         elseif (aezm > zero) then
           need(icez)               = need(icez) + 1
           DownStreamC(id,1,ic)     = icez
         endif

       endif

!  Corner Face FP (neighboring corner, neighboring zone)

       if (icfp > ic) then

         if (afpm < zero) then
           need(ic)                 = need(ic) + 1
           DownStreamC(idfp,2,icfp) = ic

         elseif (afpm > zero) then
           need(icfp)               = need(icfp) + 1
           DownStreamC(id,2,ic)     = icfp
         endif

       endif


     enddo CornerFaceLoop

   enddo CornerLoop

!  By adding an additional index to NEED, we can save some
!  "if" tests.  Set need(ncornr+1) to a large number so that it
!  is never less than or equal to zero.

   need(ncornr+1) = 10*ncornr 

 
   return
   end subroutine snneed

