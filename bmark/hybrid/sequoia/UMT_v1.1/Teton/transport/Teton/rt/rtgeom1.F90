!***********************************************************************
!                        Version 1:  05/92, PFN                        *
!                                                                      *
!   RTGEOM1 - Calculates certain geometry factors for Sn radiation     *
!             transport in 1D.                                         *
!                                                                      *
!   Input:    px     - 1D outer radii (L)                              *
!             ratzm  - zone mass ratio (zm/zmold)  (0)                 *
!                                                                      *
!   Output:   AREAC  - corner area  (A)                                *
!             VOLC   - corner volume  (V)                              *
!             VOLZ   - zone volume    (V)                              *
!             RJ2    - square of position of zone center (L)           *
!             HJ     - zone width (L)                                  *
!             R2     - square of outer radii (A)                       *
!                                                                      *
!***********************************************************************
   subroutine rtgeom1(Size, Geom)

   use kind_mod
   use constant_mod
   use Size_mod
   use Geometry_mod

   implicit none

!  Arguments - Types
                                                                                  
   type(MeshSize)            :: Size
   type(Geometry)            :: Geom

!  Local

   integer    :: ic,iz,nzones

   real(adqt) :: p0,p1,rj

!  Mesh Constants

   nzones = Size%nzones

!  Calculate zone widths and midpoint
 
   do iz=1,nzones+1
     Geom% r2(iz) = Geom% px(1,iz)*Geom% px(1,iz)
   enddo
 
   do iz=1,nzones
     Geom% hj(iz) = Geom% px(1,iz+1) - Geom% px(1,iz)
   enddo
 
!  Half-cell volumes need to be multiplied by a factor of 2*pi
!  to be full cylinder volumes or 4*pi for spheres.  Note that
!  for cylinders the correct dimension of volumes and areas is
!  obtained by multiplying by dz (assumed to be 1).
 
!  Cylinders
 
   if (Size%igeom == 'cylinder') then
 
     do iz=1,nzones
       p0                  = Geom% px(1,iz)
       p1                  = Geom% px(1,iz+1)
       rj                  = half*( p0 + p1 )

       Geom% rj2(iz)       = rj
       Geom% areac(2*iz-1) = rj - p0
       Geom% areac(2*iz)   = p1 - rj
       Geom% volc(2*iz-1)  = half*( rj*rj - p0*p0 )
       Geom% volc(2*iz)    = half*( p1*p1 - rj*rj )
       Geom% volz(iz)      = Geom% volc(2*iz-1) + Geom% volc(2*iz)
     enddo
 
!  Spheres
 
   elseif (Size%igeom == 'sphere') then
 
     do iz=1,nzones
       p0                  = Geom% px(1,iz)
       p1                  = Geom% px(1,iz+1)
       rj                  = half*( p0 + p1 )

       Geom% rj2(iz)       = rj*rj
       Geom% areac(2*iz-1) = half*( rj*rj - Geom% r2(iz) )
       Geom% areac(2*iz)   = half*( Geom% r2(iz+1) - rj*rj )
       Geom% volc(2*iz-1)  = third*( rj*rj*rj - Geom% r2(iz)*p0 )
       Geom% volc(2*iz)    = third*( Geom% r2(iz+1)*p1 - rj*rj*rj )
       Geom% volz(iz)      = Geom% volc(2*iz-1) + Geom% volc(2*iz)
     enddo

!  Slabs
 
   elseif (Size%igeom == 'slab') then
 
     do iz=1,nzones
       p0                  = Geom% px(1,iz)
       p1                  = Geom% px(1,iz+1)
       rj                  = half*( p0 + p1 )

       Geom% rj2(iz)       = one
       Geom% areac(2*iz-1) = zero
       Geom% areac(2*iz)   = zero
       Geom% volc(2*iz-1)  = rj - p0
       Geom% volc(2*iz)    = p1 - rj
       Geom% volz(iz)      = Geom% volc(2*iz-1) + Geom% volc(2*iz)
     enddo
 
   endif
 
!  For cylinders and slabs only
 
   if (Size%igeom == 'cylinder') then
 
     Geom% r2(:) = Geom% px(1,:)

   elseif (Size%igeom == 'slab') then

     Geom% r2(:) = one
 
   endif

!  Set the outward normals on the problem boundary (only for fun in 1D)

   Geom% A_bdy(:,:) = one
 
 
   return
   end subroutine rtgeom1

