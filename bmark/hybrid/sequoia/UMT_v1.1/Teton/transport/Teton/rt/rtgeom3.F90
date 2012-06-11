!***********************************************************************
!                        Version 1:  01/2001, PFN                      *
!                                                                      *
!   RTGEOM3 - Calculates geometry factors for Sn radiation transport   *
!             in 3D for a corner-based method.                         *
!                                                                      *
!   Input:   px     - point coordinates  (L)                           *
!                                                                      *
!   Output:  A_SURF - area vectors on corner faces (A)                 *
!            A_BDY  - area vectors on the problem boundary (A)         *
!            VOLC   - corner volume  (V)                               *
!            VOLZ   - zone volume    (V)                               *
!                                                                      *
!***********************************************************************

   subroutine rtgeom3(Size, Geom)

   use kind_mod
   use Size_mod
   use Geometry_mod
   use constant_mod

   implicit none

!  Arguments - Types

   type(MeshSize)            :: Size
   type(Geometry)            :: Geom

!  Local Variables

   integer    :: ic,icface1,icface2,icfp,icez1,icez2,  &
                 ib,ipnt0,ipnt1,ipnt2,iface,izone,ncfaces

   integer    :: ndim, ncornr, nzones, nfaces 

   real(adqt) :: tdl(3),tfl(3),tzl(3),tfz(3),tfe1(3),  &
                 tfe2(3),A_fep(3),A_fez1(3),A_fez2(3), &
                 pnt0(3),pnt1(3),pnt2(3)

!  Dynamic arrays

   real(adqt), allocatable :: fx(:,:)
   real(adqt), allocatable :: zx(:,:)

!  Mesh Constants

   ndim   = Size%ndim
   ncornr = Size%ncornr
   nzones = Size%nzones
   nfaces = Size%nfaces

!  Allocate temporary arrays

   allocate( fx(ndim,nfaces) )
   allocate( zx(ndim,nzones) )

!  Calculate the location of the face-centers (FX) and zone-centers (ZX)

   call face_coords(Size, Geom, FX) 
   call zone_coords(Size, Geom, ZX)

!  Compute Vectors from edge-center to point (TEL), face-center to
!  point (TFL) and zone-center to point (TZL).  These are used
!  to compute outward normals on corner faces.  The corner-face
!  area is the sum of two half-side areas. 

   Geom%A_surf(:,:,:,:) = zero
   Geom%volc(:)         = zero
   Geom%volz(:)         = zero


   CornerLoop: do ic=1,ncornr 

     izone   = Geom%CToZone(ic)
     ipnt0   = Geom%CToPoint(ic)
     ncfaces = Geom%nfpc(ic)

     CornerFaceLoop: do icface1=1,ncfaces

       icface2 = mod(icface1,ncfaces) + 1

       icfp    = Geom%Connect(1,icface1,ic)
       ib      = Geom%Connect(2,icface1,ic)

       icez1   = Geom%Connect(3,icface1,ic)
       icez2   = Geom%Connect(3,icface2,ic)

       ipnt1   = Geom%CToPoint(icez1)
       ipnt2   = Geom%CToPoint(icez2)

       iface   = Geom%CToFace(icface1,ic)

       pnt0(:) = Geom%px(:,ipnt0)
       pnt1(:) = Geom%px(:,ipnt1)
       pnt2(:) = Geom%px(:,ipnt2)


       tdl(:)  = half*(pnt1(:)     - pnt2(:))
       tfl(:)  =       fx(:,iface) - pnt0(:)
       tzl(:)  =       zx(:,izone) - pnt0(:)
       tfz(:)  =       fx(:,iface) - zx(:,izone)
       tfe1(:) =       fx(:,iface) - half*(pnt1(:) + pnt0(:))
       tfe2(:) =       fx(:,iface) - half*(pnt2(:) + pnt0(:))

!  Calculate the components of the outward normals on
!  "FP" corner faces; this is the sum of two tet area vectors

       A_fep(1) = half*( tfl(3)*tdl(2) - tfl(2)*tdl(3) )
       A_fep(2) = half*( tfl(1)*tdl(3) - tfl(3)*tdl(1) )
       A_fep(3) = half*( tfl(2)*tdl(1) - tfl(1)*tdl(2) )

       if (icfp /= 0) then

!  Ensure that outward normals on FP faces are equal and opposite

         if (icfp > ic) then
           Geom%A_surf(:,icface1,1,ic) =  A_fep(:)
           Geom%A_surf(:,ib,1,icfp)    = -A_fep(:)
         else
           A_fep(:) = Geom%A_surf(:,icface1,1,ic)
         endif

!  Set the outward normal on problem boundary

       elseif (icfp == 0) then
         Geom%A_surf(:,icface1,1,ic) = A_fep(:)
         Geom%A_bdy(:,ib)            = A_fep(:)
       endif

!  "EZ" corner faces; here we add the tet area vectors
!  to two different "EZ" faces

       A_fez1(1) = half*( tfz(3)*tfe1(2) - tfz(2)*tfe1(3) )
       A_fez1(2) = half*( tfz(1)*tfe1(3) - tfz(3)*tfe1(1) )
       A_fez1(3) = half*( tfz(2)*tfe1(1) - tfz(1)*tfe1(2) )

       A_fez2(1) = half*( tfz(2)*tfe2(3) - tfz(3)*tfe2(2) )
       A_fez2(2) = half*( tfz(3)*tfe2(1) - tfz(1)*tfe2(3) )
       A_fez2(3) = half*( tfz(1)*tfe2(2) - tfz(2)*tfe2(1) )

!  Accumulate corner surface areas on "EZ" faces

       Geom%A_surf(:,icface1,2,ic) = Geom%A_surf(:,icface1,2,ic) + A_fez1(:)
       Geom%A_surf(:,icface2,2,ic) = Geom%A_surf(:,icface2,2,ic) + A_fez2(:)

!  Accumulate corner volumes (VOLC)

       Geom%volc(ic) = Geom%volc(ic) + third*abs( tzl(1)*A_fep(1) +  &
                                                  tzl(2)*A_fep(2) +  &
                                                  tzl(3)*A_fep(3) )

     enddo CornerFaceLoop

!  Accumulate zone volumes (VOLZ)

     Geom%volz(izone) = Geom%volz(izone) + Geom%volc(ic)

   enddo CornerLoop

!  Ensure that outward normals on "EZ" faces are equal and opposite

   do ic=1,ncornr
     ncfaces = Geom%nfpc(ic)
     do icface1=1,ncfaces
       icez1 = Geom%Connect(3,icface1,ic)
       icez2 = Geom%Connect(4,icface1,ic)
       if (icez1 > ic) then
         Geom%A_surf(:,icez2,2,icez1) = -Geom%A_surf(:,icface1,2,ic)
       endif
     enddo
   enddo

!  Release temporary arrays

   deallocate( fx )
   deallocate( zx )


   return
   end subroutine rtgeom3

