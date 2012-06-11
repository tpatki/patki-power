!***********************************************************************
!                        Version 1:  05/92, PFN                        *
!                                                                      *
!   RTGEOM2 - Calculates certain geometry factors for Sn radiation     *
!             transport in 2D.                                         *
!                                                                      *
!   Input:   r      - 1D outer radii (L)                               *
!                                                                      *
!   Output:                                                            *
!                                                                      *
!***********************************************************************
   subroutine rtgeom2(Size, Geom)

   use kind_mod
   use constant_mod
   use Size_mod
   use Geometry_mod

   implicit none

!  Arguments - Types
                                                                                  
   type(MeshSize)            :: Size
   type(Geometry)            :: Geom

!  Local

   integer    :: i,ib,ic,ic1,ic2,id,izone,  &
                 ipnt,ipnt1,ipnt2,nc,ncmax, &
                 ncornr,nzones,nbelem,nx

   real(adqt) :: r_zone,z_zone,r_point,z_point,        &
                 r_point1,z_point1,r_point2,z_point2,  &
                 r_edge1,z_edge1,r_edge2,z_edge2,      &
                 area1,area2,rbar1,rbar2

!  Dynamic arrays

   real(adqt),  allocatable :: zx(:,:)

!  Mesh Constants

   ncornr = Size%ncornr
   nzones = Size%nzones
   nbelem = Size%nbelem

!  Allocate temporary arrays

   allocate( zx(2,nzones) )

!  Calculate the location of the zone-centers (ZX)

   call zone_coords(Size, Geom, ZX)

!  Calculate the geometry factors for 2D r-z geometry;
!  all of our calculations with respect to corners 

   nc = 0

   ZoneLoop: do izone=1,nzones

     ncmax            = Geom% CList(izone+1) - Geom% CList(izone)
     Geom%volz(izone) = zero

     CornerLoop: do i=1,ncmax

!  For each corner "ic" find the neighboring corners (in the
!  same zone) "ic1" and "ic2"

       ic    = nc + i
       ic1   = Geom%Connect(3,1,ic)
       ic2   = Geom%Connect(3,2,ic)

       ipnt  = Geom% CToPoint(ic)
       ipnt1 = Geom% CToPoint(ic1)
       ipnt2 = Geom% CToPoint(ic2)

!  Load the necessary coordinates

       r_zone   = zx(1,izone)
       z_zone   = zx(2,izone)
       r_point  = Geom% px(1,ipnt)
       z_point  = Geom% px(2,ipnt)
       r_point1 = Geom% px(1,ipnt1)
       z_point1 = Geom% px(2,ipnt1)
       r_point2 = Geom% px(1,ipnt2)
       z_point2 = Geom% px(2,ipnt2)
       r_edge1  = half*( r_point + r_point1 )
       z_edge1  = half*( z_point + z_point1 )
       r_edge2  = half*( r_point + r_point2 )
       z_edge2  = half*( z_point + z_point2 )

!  This is one-half the average radius for the FP corner faces 

       Geom% rbar(1,1,ic) = half*( r_point + r_edge1 )
       Geom% rbar(2,1,ic) = half*( r_point + r_edge2 )

!  This is one-half the average radius for the EZ corner faces

       Geom% rbar(1,2,ic) = half*( r_zone  + r_edge1 )
       Geom% rbar(2,2,ic) = half*( r_zone  + r_edge2 ) 

!  Calculate components of the area vectors for the corner faces 

       Geom% A_surf(1,1,1,ic) = z_point - z_edge1
       Geom% A_surf(2,1,1,ic) = r_edge1 - r_point

       Geom% A_surf(1,2,1,ic) = z_edge2 - z_point
       Geom% A_surf(2,2,1,ic) = r_point - r_edge2

       Geom% A_surf(1,1,2,ic) = z_edge1 - z_zone
       Geom% A_surf(2,1,2,ic) = r_zone  - r_edge1

       Geom% A_surf(1,2,2,ic) = z_zone  - z_edge2
       Geom% A_surf(2,2,2,ic) = r_edge2 - r_zone

!  Compute the corner "area" (this is really an x-y area).  The
!  corner area is the sum of two half-side areas. The half-side
!  area is the one-half the dot product of the fp-outward normal
!  and the vector from point to zone-center.

       area1 = abs( (r_edge1 - r_point)*(z_zone - z_point) -  &
                    (z_edge1 - z_point)*(r_zone - r_point) )
        
       area2 = abs( (r_zone - r_point)*(z_edge2 - z_point) - &
                    (z_zone - z_point)*(r_edge2 - r_point) )

       Geom% areac(ic) = half*( area1 + area2 )

!  Compute the corner "volume" (this is really volume/2*pi).
!  Each half-side volume is its area multiplied by its average
!  radial coordinate.

       rbar1          = third*(r_point + r_edge1 + r_zone)
       rbar2          = third*(r_point + r_edge2 + r_zone)
       Geom% volc(ic) = half*( rbar1*area1 + rbar2*area2 )

!  Accumulate zone volume
 
       Geom% volz(izone) = Geom% volz(izone) + Geom% volc(ic)

     enddo CornerLoop

     nc = nc + ncmax

   enddo ZoneLoop
 
!  Load components of the area vectors for the half-sides on
!  the problem boundary (only FP corner-faces live on the boundary)

   do ib=1,nbelem
     ic                = Geom% BdyToC(1,ib)
     id                = Geom% BdyToC(2,ib)
     Geom% A_bdy(1,ib) = Geom% A_surf(1,id,1,ic)
     Geom% A_bdy(2,ib) = Geom% A_surf(2,id,1,ic)
   enddo

!  Release temporary arrays

   deallocate( zx )


   return
   end subroutine rtgeom2

