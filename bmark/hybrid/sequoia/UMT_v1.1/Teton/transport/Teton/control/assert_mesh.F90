subroutine assert_mesh(kkcz,kkcp,kktc,kktz,kktf,kktp,konnect, &
  ksbdy,ksbr,px,nzones,ncornr,nsides,nelem,npnts,nfaces,nbelem,ndim)

!=======================================================================
!                        Version 1: 01/99, MRZ
!-----------------------------------------------------------------------
! assert_connect
!   This subroutine performs assertion checking for the mesh
! description.
!
! nzones       number of spatial zones
! ncornr       number of corners
! nsides       number of sides
! nelem        number of tets
! npnts        number of points
! nfaces       number of faces
! nbelem       number of boundary tets
! ndim         number of spatial dimensions
!
! kkcz(ic)     corner --> zone
! kkcp(ic)     corner --> point
! kktc(it)     tet --> corner
! kktz(it)     tet --> zone (3D-only)
! kktf(it)     tet --> face (3D-only)
! kktp(it)     tet --> point
! konnect(id,it)  tet-to-connectivity:
!                 3D definition:
!                   konnect(1,it)  tet --> tet across facelet FEP
!                   konnect(2,it)  tet --> tet across facelet FPZ
!                   konnect(3,it)  tet --> tet across facelet PEZ
!                 2D definition:
!                   konnect(1,it)  tri --> tri across facelet EP
!                   konnect(2,it)  tri --> tri across facelet PZ
! ksbdy(ib)    boundary tet --> interior tet
! ksbr(ib)     boundary tet --> boundary source flag
! px(:,ip)     coordinates of point ip
! fx(:,iface)  coordinates of face center iface
!-----------------------------------------------------------------------

#include "assert.h"
   use kind_mod
   use constant_mod

!  variable declarations
   implicit none

!  passed variables
   integer,      intent(in) :: nzones, ncornr, nsides, nelem, npnts, &
                                 nfaces, nbelem, ndim, &
                               kkcz(ncornr), kkcp(ncornr), &
                               kktc(nelem), kktz(nelem), kktf(nelem), &
                               kktp(nelem), ksbdy(nbelem)
   character(8), intent(in) :: ksbr(nbelem)
   real(adqt),   intent(in) :: px(ndim,npnts)

   integer, intent(in), target :: konnect(ndim,nelem)

!  local variables
   integer :: id, jd, iz, is, ip, ic, it, ib, iface, &
              nbs, ns, ntet, alloc_stat

   integer      :: ielem(nelem)
   real(adqt)   :: zmax(ndim,nzones), zmin(ndim,nzones), &
                   pmax(ndim,npnts), pmin(ndim,npnts), &
                   v_fp1(3), v_fp2(3), v_p1xp2(3), v_zf(3)
   character(8) :: bcs(5)
   logical      :: pbdy(npnts)

   integer,      allocatable :: tets(:), &
                                kkts(:), kkttfez(:), kktb(:)
   real(adqt),   allocatable :: fx(:,:), dot_prod(:)
   character(8), allocatable :: fbc(:)
   logical,      allocatable :: bool(:)

!-----------------------------------------------------------------------

#ifdef ASSERT_MESH

!  build a temporary list of elements
   ielem(:) = (/ (it,it=1,nelem) /)

!  build a temporary list of allowed boundary conditions
   bcs(:) = (/ "refl  ", "vac   ", "temp  ", "fds   ", "shared" /)

!  build a temporary tet --> side connectivity
   allocate(kkts(nelem))
   kkts(:nsides)   = (/ (is,is=1,nsides) /)
   kkts(nsides+1:) = (/ (is,is=1,nsides) /)

!  build a temporary tet --> tet across FEZ facelet (3D), or
!  triangle --> triangle across EZ facelet (2D)
   allocate(kkttfez(nelem))
   kkttfez(:nsides)   = (/ (is+nsides,is=1,nsides) /)
   kkttfez(nsides+1:) = (/ (is,is=1,nsides) /)

   require(modulo(nelem,2)==0, "Bad connectivity")
   require(modulo(nbelem,2)==0, "Bad connectivity")
   require(nelem==2*nsides, "Bad connectivity")

!  connectivity must be all positive
   require(all(kkcz(:)>0), "Bad connectivity")
   require(all(kkcp(:)>0), "Bad connectivity")
   require(all(kktc(:)>0), "Bad connectivity")
   require(all(kktp(:)>0), "Bad connectivity")
   require(all(kkts(:)>0), "Bad connectivity")
   if (ndim == 3) then
      require(all(kktf(:)>0), "Bad connectivity")
      require(all(kktz(:)>0), "Bad connectivity")
   endif
   require(all(konnect(:,:)>0), "Bad connectivity")
   require(all(kkttfez(:)>0), "Bad connectivity")
   require(all(ksbdy(:)>0), "Bad connectivity")

!  connectivity is bounded by what it points to (assumes no holes)
   require(all(kkcz(:)<=nzones), "Bad connectivity")
   require(all(kkcp(:)<=npnts), "Bad connectivity")
   require(all(kktc(:)<=ncornr), "Bad connectivity")
   require(all(kktp(:)<=npnts), "Bad connectivity")
   require(all(kkts(:)<=nsides), "Bad connectivity")
   if (ndim == 3) then
      require(all(kktf(:)<=nfaces), "Bad connectivity")
      require(all(kktz(:)<=nzones), "Bad connectivity")
   endif
   require(all(konnect(1,:)<=nelem+nbelem), "Bad connectivity")
   require(all(konnect(2:,:)<=nelem), "Bad connectivity")
   require(all(kkttfez(:)<=nelem), "Bad connectivity")
   require(all(ksbdy(:)<=nelem), "Bad connectivity")

!  two points associated with a side are unique
   require(all(kksp1(:)/=kksp2(:)), "Bad connectivity")

!  tet --> point must equal tet --> corner --> point
   require(all(kktp(:)==kkcp(kktc(:))), "Bad connectivity")

!  tet --> zone must equal tet --> corner --> zone
   if (ndim == 3) then
      require(all(kktz(:)==kkcz(kktc(:))), "Bad connectivity")
   endif

!  consistent connectivity to points
   ns = nsides
   require(all(kksp1(:)==kktp(:nsides)), "Bad connectivity")
   require(all(kksp2(:)==kktp(nsides+1:)), "Bad connectivity")
   do is = 1, nsides
      if (konnect(1,is) <= nelem) then
         require(kksp1(konnect(1,is)-ns)==kksp2(is),"Bad connectivity")
         require(kksp2(konnect(1,is)-ns)==kksp1(is),"Bad connectivity")
      endif
   enddo

!  crossing each facelet leads to a unique tet
   do id = 1, ndim
      do jd = id+1, ndim
         require(all(konnect(id,:)/=konnect(jd,:)), "Bad connectivity")
      enddo
      require(all(konnect(id,:)/=kkttfez(:)), "Bad connectivity")
   enddo

!  each tet exists in the konnect(:,:) and kkttfez(:) arrays only once.
!  Exception: crossing FEP facelet may indicate a boundary.
   select case (ndim)
   case (2)
      do it = 1, nelem
         ntet = count(konnect(1,:)==it)
         require(ntet==1 .or. ntet==0, "Bad connectivity")
         require(count(konnect(2,:)==it) == 1, "Bad connectivity")
         require(count( kkttfez(:) ==it) == 1, "Bad connectivity")
      enddo
      do ib = 1, nbelem
         require(count(konnect(1,:)==nelem+ib) == 1, "Bad connectivity")
      enddo
   case (3)
      do it = 1, nelem
         ntet = count(konnect(1,:)==it)
         require(ntet==1 .or. ntet==0, "Bad connectivity")
         require(count(konnect(2,:)==it) == 1, "Bad connectivity")
         require(count(konnect(3,:)==it) == 1, "Bad connectivity")
         require(count( kkttfez(:) ==it) == 1, "Bad connectivity")
      enddo
      do ib = 1, nbelem
         require(count(konnect(1,:)==nelem+ib) == 1, "Bad connectivity")
      enddo
   end select

!  check the reciprocity of the tet --> tet (triangle --> triangle)
!  connectivities.  Crossing a facelet and then re-entering via that
!  facelet must result in the original tet (triangle).
   select case (ndim)
   case (2)
      do it = 1, nelem
         if (konnect(1,it) <= nelem) then
            require(konnect(1,konnect(1,it))==it, "Bad connectivity")
         else
            require(ksbdy(konnect(1,it)-nelem)==it, "Bad connectivity")
         endif
         require(konnect(2,konnect(2,it))==it, "Bad connectivity")
         require(  kkttfez( kkttfez(it) )==it, "Bad connectivity")
      enddo
   case (3)
      do it = 1, nelem
         if (konnect(1,it) <= nelem) then
            require(konnect(1,konnect(1,it))==it, "Bad connectivity")
         else
            require(ksbdy(konnect(1,it)-nelem)==it, "Bad connectivity")
         endif
         require(konnect(2,konnect(2,it))==it, "Bad connectivity")
         require(konnect(3,konnect(3,it))==it, "Bad connectivity")
         require(  kkttfez( kkttfez(it) )==it, "Bad connectivity")
      enddo
   end select

!  cross FEP facelet: same point, different face, side, corner & zone
   select case (ndim)
   case (2)
      do it = 1, nelem
         if (konnect(1,it) <= nelem) then
            require(kktp(konnect(1,it))==kktp(it), "Bad connecitvity")
            require(kkts(konnect(1,it))/=kkts(it), "Bad connecitvity")
            require(kktc(konnect(1,it))/=kktc(it), "Bad connectivity")
         endif
      enddo
   case (3)
      do it = 1, nelem
         if (konnect(1,it) <= nelem) then
            require(kktf(konnect(1,it))/=kktf(it), "Bad connectivity")
            require(kktp(konnect(1,it))==kktp(it), "Bad connecitvity")
            require(kkts(konnect(1,it))/=kkts(it), "Bad connecitvity")
            require(kktc(konnect(1,it))/=kktc(it), "Bad connectivity")
            require(kktz(konnect(1,it))/=kktz(it), "Bad connectivity")
         endif
      enddo
   end select

!  cross FPZ facelet: same face, point, corner & zone, different side
   select case (ndim)
   case (2)
      require(all(kktp(konnect(2,:))==kktp(:)), "Bad connectivity")
      require(all(kkts(konnect(2,:))/=kkts(:)), "Bad connectivity")
      require(all(kktc(konnect(2,:))==kktc(:)), "Bad connectivity")
   case (3)
      require(all(kktf(konnect(2,:))==kktf(:)), "Bad connectivity")
      require(all(kktp(konnect(2,:))==kktp(:)), "Bad connectivity")
      require(all(kkts(konnect(2,:))/=kkts(:)), "Bad connectivity")
      require(all(kktc(konnect(2,:))==kktc(:)), "Bad connectivity")
      require(all(kktz(konnect(2,:))==kktz(:)), "Bad connectivity")
   end select

!  cross PEZ facelet: same point, corner & zone, different face & side
   select case (ndim)
   case (3)
      require(all(kktf(konnect(3,:))/=kktf(:)), "Bad connectivity")
      require(all(kktp(konnect(3,:))==kktp(:)), "Bad connectivity")
      require(all(kkts(konnect(3,:))/=kkts(:)), "Bad connectivity")
      require(all(kktc(konnect(3,:))==kktc(:)), "Bad connectivity")
      require(all(kktz(konnect(3,:))==kktz(:)), "Bad connectivity")
   end select

!  cross FEZ facelet: same face, side & zone, different point & corner
   select case (ndim)
   case (2)
      require(all(kktp(kkttfez(:))/=kktp(:)), "Bad connectivity")
      require(all(kkts(kkttfez(:))==kkts(:)), "Bad connectivity")
      require(all(kktc(kkttfez(:))/=kktc(:)), "Bad connectivity")
   case (3)
      require(all(kktf(kkttfez(:))==kktf(:)), "Bad connectivity")
      require(all(kktp(kkttfez(:))/=kktp(:)), "Bad connectivity")
      require(all(kkts(kkttfez(:))==kkts(:)), "Bad connectivity")
      require(all(kktc(kkttfez(:))/=kktc(:)), "Bad connectivity")
      require(all(kktz(kkttfez(:))==kktz(:)), "Bad connectivity")
   end select

!  each boundary tet must be unique
   do it = 1, nelem
      ntet = count(ksbdy(:)==it)
      require(ntet==1 .or. ntet==0, "Bad connectivity")
   enddo

!  consistent connectivity from boundary tets to interior tets
   nbs = nbelem/2
   require(all(ksbdy(:nbs)<=nsides), "Bad connectivity")
   require(all(ksbdy(nbs+1:)>nsides), "Bad connectivity")
   require(all(ksbdy(nbs+1:)==ksbdy(:nbs)+nsides), "Bad connectivity")

!  each boundary condition must match an allowed boundary condition
   do ib = 1, nbelem
      require(any(ksbr(ib)==bcs(:)), "Bad boundary condition")
   enddo

!  build maximum and minimum zonal coordinates from zone's points
   zmax(:,:) = minval(px(:,:)) ; zmin(:,:) = maxval(px(:,:))
   do ic = 1, ncornr
      zmax(:,kkcz(ic)) = max(zmax(:,kkcz(ic)),px(:,kkcp(ic)))
      zmin(:,kkcz(ic)) = min(zmin(:,kkcz(ic)),px(:,kkcp(ic)))
   enddo

!  zonal coordinates must be contained by zone's point coordinates
   require(all(zx(:,:)>zmin(:,:)), "Bad coordinates")
   require(all(zx(:,:)<zmax(:,:)), "Bad coordinates")

!  build a list of boundary points
   pbdy(:) = .false.
   do is = 1, nsides
      if (konnect(1,is)        > nelem) pbdy(kksp1(is)) = .true.
      if (konnect(1,is+nsides) > nelem) pbdy(kksp2(is)) = .true.
   enddo

!  build maximum and minimum point coordinates from point's zones
   pmax(:,:) = minval(zx(:,:)) ; pmin(:,:) = maxval(zx(:,:))
   do ic = 1, ncornr
      pmax(:,kkcp(ic)) = max(pmax(:,kkcp(ic)),zx(:,kkcz(ic)))
      pmin(:,kkcp(ic)) = min(pmin(:,kkcp(ic)),zx(:,kkcz(ic)))
   enddo

!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
!  This is currently not general enough.  Point coordinates are
!  contained within the dual _cell's_ coordinates.  The dual cell is
!  composed of the union of zone _and_ edge coordinates of all corners
!  touching the point.
!
!  For now, comment out the assertion.  This should be cleaned up and
!  generalized to account for the edge coordinate (perhaps when a mesh
!  class is available).
!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
!  point coordinate must be contained by dual's zone coordinates
!  (except for boundary points)
   do ip = 1, npnts
!     require(all(px(:,ip)>pmin(:,ip)).or.pbdy(ip), "Bad connectivity")
!     require(all(px(:,ip)<pmax(:,ip)).or.pbdy(ip), "Bad connectivity")
   enddo
!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

!  check that the points are ordered correctly (3D only: requires kktf)
   if (ndim == 3) then

!     build a temporary array of face center coordinates
      allocate(fx(ndim,nfaces))
      call face_coords(kktf,kksp1,px,fx,nelem,nsides,nfaces,npnts,ndim)

!     the face-center (f), point one (p1), and point two (p2) must be
!     walked in a counter-clockwise sense when the face is viewed from
!     outside the zone.  Thus, the normal to each side's facelet should
!     lie in the same half-space as the vector from zone-center to
!     face-center.

      allocate(dot_prod(nsides))
      do is = 1, nsides

!        form vectors:  face-center -> p1 ; face-center -> p2
         v_fp1(:) = px(:,kksp1(is)) - fx(:,kktf(is))
         v_fp2(:) = px(:,kksp2(is)) - fx(:,kktf(is))

!        the face normal is the cross product (f->p1) X (f->p2)
         v_p1xp2(1) = v_fp1(2)*v_fp2(3) - v_fp1(3)*v_fp2(2)
         v_p1xp2(2) = v_fp1(3)*v_fp2(1) - v_fp1(1)*v_fp2(3)
         v_p1xp2(3) = v_fp1(1)*v_fp2(2) - v_fp1(2)*v_fp2(1)
         v_p1xp2(:) = v_p1xp2(:) / sqrt(sum(v_p1xp2(:)**2))

!        form vector: zone-center -> face-center
         v_zf(:) = fx(:,kktf(is)) - zx(:,kktz(is))
         v_zf(:) = v_zf(:) / sqrt(sum(v_zf(:)**2))

!        the cosine of the angle formed by these two vectors is given
!        by their dot product
         dot_prod(is) = sum(v_p1xp2(:)*v_zf(:))
      enddo

!     all angles must lie between 0 and pi/2
      require(all(dot_prod(:)<=one+ten*epsilon(one)),"Bad connectivity")
      require(all(dot_prod(:)>=zero), "Bad connectivity")
   endif

!  check the boundary conditions (3D only: requires kktf)
   if (ndim == 3) then
      do iface = 1, nfaces
         ntet = count(kktf(:)==iface)
         allocate(tets(ntet), bool(ntet), fbc(ntet))
         tets(:) = pack(ielem(:),kktf(:)==iface)  ! tets on face iface
         do it = 1, ntet
            bool(it) = any(ksbdy(:)==tets(it))    ! is tet boundary tet?
         enddo

!        all BC's on a face must be the same
         if (all(bool(:))) then
            fbc(:) = ksbr(konnect(1,tets(:))-nelem)  ! BC's on a face
            require(all(fbc(:)==fbc(1)), "Bad connectivity")
         endif

!        all tets on a face are either boundary tets or not
         require(all(bool(:)).or.all(.not.bool(:)), "Bad connectivity")
         deallocate(tets, bool, fbc)
      enddo
   endif

!-----------------------------------------------------------------------
!  free memory
!-----------------------------------------------------------------------
   deallocate(tets, stat=alloc_stat)
   deallocate(kktp, stat=alloc_stat)
   deallocate(kkts, stat=alloc_stat)
   deallocate(kkttfez, stat=alloc_stat)
   deallocate(kktb, stat=alloc_stat)
   deallocate(fx, stat=alloc_stat)
   deallocate(dot_prod, stat=alloc_stat)
   deallocate(fbc, stat=alloc_stat)
   deallocate(bool, stat=alloc_stat)

#endif

!-----------------------------------------------------------------------
   return
end subroutine assert_mesh
