! Geometry Modules:  geometry and connectivity information used by Sn
                                                                                 
module Geometry_mod 

  use kind_mod

  private

! public interfaces
                                                                                             
  public construct, destruct
                                                                                 
                                                                                 
  type, public :: Geometry 

     integer :: nbsets                        ! number of reflecting boundary sets

     real(adqt), pointer :: px(:,:)           ! px(ndim,npnts) - coordinates of zone vertices
     real(adqt), pointer :: volc(:)           ! volc(ncornr)   - corner volumes
     real(adqt), pointer :: volz(:)           ! volz(nzones)   - zone volumes
     real(adqt), pointer :: A_surf(:,:,:,:)   ! A_surf(ndim,maxcf,2,ncornr) - corner area vectors
     real(adqt), pointer :: A_bdy(:,:)        ! A_bdy(ndim,nbelem) - boundary element area vectors

!    1D & 2D Specific Arrays
     real(adqt), pointer :: areac(:)          ! areac(ncornr)
     real(adqt), pointer :: rbar(:,:,:)       ! rbar(2,2,ncornr)
     real(adqt), pointer :: rj2(:)            ! rj2(nzones)
     real(adqt), pointer :: r2(:)             ! r2(nzones+1)
     real(adqt), pointer :: hj(:)             ! hj(nzones)

     integer, pointer :: Connect(:,:,:)       ! Connect(4,maxcf,ncornr)
     integer, pointer :: CToFace(:,:)         ! CToFace(maxcf,ncornr)
     integer, pointer :: CToZone(:)           ! CToZone(ncornr)
     integer, pointer :: CToPoint(:)          ! CToPoint(ncornr)
     integer, pointer :: CList(:)             ! CList(nzones+1)
     integer, pointer :: BdyToC(:,:)          ! BdyToC(2,nbelem)
     integer, pointer :: BdyToSrc(:)          ! BdyToSrc(nbelem)
     integer, pointer :: BdyToEdit(:)         ! BdyToEdit(nbelem)
     integer, pointer :: ZoneToSrc(:)         ! ZoneToSrc(nzones)
     integer, pointer :: nfpc(:)              ! nfpc(ncornr)

     integer, pointer :: indexRefB(:,:)       ! indexRefB(2,nbelem)
     integer, pointer :: listRefB(:)          ! listRefB(nbelem)

!    Global communication
     integer, pointer :: nodecomm(:,:)        ! nodecomm(2,ncomm)
     integer, pointer :: CbdyComm(:)          ! CbdyComm(nbshare)

     character(len=8), pointer :: BdyToBC(:)  ! BdyToBC(nbelem)
  end type Geometry

  interface construct
    module procedure Geometry_ctor
  end interface

  interface destruct
    module procedure Geometry_dtor
  end interface

contains

!=======================================================================
! construct interface
!=======================================================================

  subroutine Geometry_ctor(self, Size)

    use Size_mod

    implicit none

!   Passed variables

    type(Geometry),  intent(inout) :: self
    type(MeshSize)                 :: Size

    self % nbsets = 0

    allocate( self % px(Size%ndim,Size%npnts) )
    allocate( self % volc(Size%ncornr) )
    allocate( self % volz(Size%nzones) )
    allocate( self % A_surf(Size%ndim,Size%maxcf,2,Size%ncornr) )
    allocate( self % A_bdy(Size%ndim,Size%nbelem) )

!   Geometry Specific Arrays

    if (Size%ndim == 1) then
      allocate( self % rj2(Size%nzones) )
      allocate( self % r2(Size%nzones+1) )
      allocate( self % hj(Size%nzones) )
    endif

    if (Size%ndim == 2) then
      allocate( self % areac(Size%ncornr) )
      allocate( self % rbar(2,2,Size%ncornr) )
    endif

    if (Size%ndim == 3) then
      allocate( self % CToFace(Size%maxcf,Size%ncornr) )
    endif

!   Mesh Connectivity

    allocate( self % Connect(4,Size%maxcf,Size%ncornr) )
    allocate( self % CToZone(Size%ncornr) )
    allocate( self % CToPoint(Size%ncornr) )
    allocate( self % CList(Size%nzones+1) )
    allocate( self % BdyToC(2,Size%nbelem) )
    allocate( self % BdyToSrc(Size%nbelem) )
    allocate( self % BdyToEdit(Size%nbelem) )
    allocate( self % ZoneToSrc(Size%nzones) )
    allocate( self % nfpc(Size%ncornr) )

    if (Size%ndim >= 2) then
      allocate( self% indexRefB(2,Size%nbelem) )
      allocate( self% listRefB(Size%nbelem) )
    endif

    if (Size%decomp_s == 'on') then
      allocate( self% nodecomm(2,Size%ncomm) )
      allocate( self% CbdyComm(Size%nbshare) )
    endif

    allocate( self % BdyToBC(Size%nbelem) )


    return
                                                                                             
  end subroutine Geometry_ctor
                                                                                             
!=======================================================================
! destruct interface
!=======================================================================

  subroutine Geometry_dtor(self, Size)

    use Size_mod

    implicit none

!   Passed variables

    type(Geometry),  intent(inout) :: self
    type(MeshSize)                 :: Size


    deallocate( self % px )
    deallocate( self % volc )
    deallocate( self % volz )
    deallocate( self % A_surf )
    deallocate( self % A_bdy )

!   Geometry Specific Arrays

    if (Size%ndim == 1) then
      deallocate( self % rj2 )
      deallocate( self % r2 )
      deallocate( self % hj )
    endif

    if (Size%ndim == 2) then
      deallocate( self % areac )
      deallocate( self % rbar )
    endif

    if (Size%ndim == 3) then
      deallocate( self % CToFace )
    endif

!   Mesh Connectivity

    deallocate( self % Connect )
    deallocate( self % CToZone )
    deallocate( self % CToPoint )
    deallocate( self % CList )
    deallocate( self % BdyToC )
    deallocate( self % BdyToSrc )
    deallocate( self % BdyToEdit )
    deallocate( self % ZoneToSrc )
    deallocate( self % nfpc )

    if (Size%ndim >= 2) then
      deallocate( self% indexRefB )
      deallocate( self% listRefB )
    endif

    if (Size%decomp_s == 'on') then
      deallocate( self% nodecomm )
      deallocate( self% CbdyComm )
    endif

    deallocate( self % BdyToBC )

    return

  end subroutine Geometry_dtor

                                                      
end module Geometry_mod

