!***********************************************************************
!                        Version 1:  06/94, PFN                        *
!                                                                      *
!   ZONE_COORDS  - This routine computes the zone center in an         *
!                  arbitrary grid with 1, 2 or 3 dimensions.           *
!                                                                      *
!                                                                      *
!***********************************************************************

   subroutine zone_coords(Size, Geom, ZX)

   use kind_mod
   use constant_mod
   use Size_mod
   use Geometry_mod

   implicit none

!  Types

   type(MeshSize)            :: Size
   type(Geometry)            :: Geom

!  Arguments

   real(adqt), intent(inout) :: zx(Size%ndim,Size%nzones)
 
!  Local

   integer :: idim, ic, iz, ipnt
   integer :: ndim, ncornr, nzones

!  Dynamic

   real(adqt), allocatable :: znc(:)

!  Mesh Constants

   ndim   = Size%ndim
   ncornr = Size%ncornr
   nzones = Size%nzones

!  Allocate space for temporary array, znc (# of corners in zone);
!  initialize arrays:
 
   allocate( znc(nzones) )
 
   zx(:,:)  = zero
 
!  Accumulate sum of coordinates and number of corners, each zone:

   do idim=1,ndim

     znc(:) = zero

     do ic=1,ncornr
       iz          = Geom%CToZone(ic)
       ipnt        = Geom%CToPoint(ic)
       zx(idim,iz) = zx(idim,iz) + Geom%px(idim,ipnt)
       znc(iz)     = znc(iz) + one
     enddo 

!  Divide by znc to get average coordinate:

     zx(idim,:) = zx(idim,:)/znc(:)

   enddo
 
!  Release allocated space:
 
   deallocate( znc )
 

   return
   end subroutine zone_coords 


