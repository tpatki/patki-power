! Quadrature Module:  Contains data structures describing angular quadrature 

module Quadrature_mod 

  use kind_mod
  use constant_mod
  use Communicator_mod

  private

! public interfaces

  public construct, getMessage, destruct, destructComm
                                                                                 
  type, public :: Quadrature 

     integer              :: Groups            ! number of energy groups 
     integer              :: NumAngles         ! number of angles 
     integer              :: NumMoments        ! number of angular moments
     integer              :: Order             ! quadrature order 
     integer              :: NPolar            ! number of polar angles
     integer              :: NAzimuthal        ! number of azimuthal angles
     integer              :: PolarAxis         ! polar axis (1,2 or 3)

     character(len=8)     :: TypeName          ! quadrature type

     real(adqt), pointer  :: Gnu(:)            ! energy group boundaries
     integer,    pointer  :: AngleType(:)      ! AngleType(NumAngles)
     real(adqt), pointer  :: Omega(:,:)        ! direction cosines 
     real(adqt), pointer  :: Weight(:)         ! quadrature weights 

!    Spherical Harmonics
     real(adqt), pointer  :: Ynm(:,:)          ! Ynm(NumMoments,NumAngles)
     real(adqt), pointer  :: Pnm(:,:)          ! Pnm(NumMoments,NumAngles)

!    Angular coefficients used in 1D and 2D
     real(adqt), pointer  :: Alpha(:)          ! Alpha(NumAngles)
     real(adqt), pointer  :: Tau(:)            ! Tau(NumAngles)
     real(adqt), pointer  :: Falpha(:)         ! Falpha(NumAngles)
     real(adqt), pointer  :: Adweta(:)         ! Adweta(NumAngles)

!    Sweep and communication data structures
     integer             :: totcycles          ! total number of mesh cycles
     integer             :: nbexit             ! number of exiting angles all boundaries
     integer             :: NumBin             ! number of angle bins for communication
     integer             :: NangBin            ! maximun number of angles per bin

     integer,    pointer :: NangBinList(:)     ! NangBinList(NumBin)
     integer,    pointer :: next(:,:)          ! next(ncornr+1,NumAngles)
     integer,    pointer :: AngleOrder(:,:)    ! AngleOrder(NangBin,NumBin)
     integer,    pointer :: BinOrder(:,:)      ! BinOrder(ncomm,NumBin)
     integer,    pointer :: SendOrder(:)       ! SendOrder(NumBin)
     integer,    pointer :: numcycles(:,:)     ! numcycles(2,NumAngles)
     integer,    pointer :: listcycles(:,:)    ! listcycles(3,totcycles)
     integer,    pointer :: indexExit(:,:)     ! indexExit(3,nbexit)

     type(Communicator), pointer :: iComms(:,:) ! Pointers to communicators

  end type Quadrature 

  interface construct
    module procedure Quadrature_ctor
  end interface

  interface getMessage 
    module procedure Quadrature_getComm
  end interface

  interface destruct
    module procedure Quadrature_dtor
  end interface

  interface destructComm
    module procedure Quadrature_dtorComm
  end interface

contains

!=======================================================================
! construct interface
!=======================================================================
                                                                                   
  subroutine Quadrature_ctor(self,       &
                             Size,       &
                             Groups,     &
                             NumAngles,  &
                             NumMoments, &
                             Order,      &
                             NPolar,     &
                             NAzimuthal, &
                             PolarAxis,  &
                             TypeName,   &
                             Gnu) 

    use Size_mod

    implicit none

!   Passed variables

    type(Quadrature), intent(inout)    :: self
    type(MeshSize)                     :: Size

    integer, intent(in)                :: Groups       
    integer, intent(in)                :: NumAngles
    integer, intent(in)                :: NumMoments
    integer, intent(in)                :: Order 
    integer, intent(in)                :: NPolar
    integer, intent(in)                :: NAzimuthal
    integer, intent(in)                :: PolarAxis
    character(len=8), intent(in)       :: TypeName
    real(adqt), intent(in)             :: Gnu(Groups+1)

!   Local

    integer          :: i, isctp1, Ndim, nlevel, nang
    character(len=8) :: igeom

!   Set Properties

    self % Groups     = Groups 
    self % NumAngles  = NumAngles 
    self % NumMoments = NumMoments
    self % Order      = Order 
    self % NPolar     = NPolar
    self % NAzimuthal = NAzimuthal
    self % PolarAxis  = PolarAxis
    self % TypeName   = TypeName

    isctp1            = 1
    Ndim              = Size% ndim
    igeom             = Size% igeom


    allocate( self % Gnu(self % Groups + 1) )
    allocate( self % AngleType(self % NumAngles) )
    allocate( self % Omega(Ndim,self % NumAngles) )
    allocate( self % Weight(self % NumAngles) )
    allocate( self % Ynm(self % NumMoments,self % NumAngles) )
    allocate( self % Pnm(self % NumMoments,self % NumAngles) )


    self % Gnu(:) = Gnu(:)

    call rtquad(self, Ndim, igeom)
    call snynmset(self, Ndim, isctp1)
    call snpnmset(self, Ndim, isctp1)

!   Space for sweep data structures

    self% totcycles = 0
    self% nbexit    = 0 

    if (Ndim == 1) then
      self% NumBin  = 2
      self% NangBin = self% NumAngles/self% NumBin
    elseif (Ndim == 2) then
      self% NumBin  = self% Order 
      self% NangBin = self% Order + 2
    elseif (Ndim == 3) then
!      self% NumBin  = self% NumAngles
!      self% NumBin  = 2**Ndim
      self% NumBin  = 1
      self% NangBin = self% NumAngles/self% NumBin 
    endif

    if (Ndim > 1) then
      allocate( self% NangBinList(self% NumBin) )
      allocate( self% next(Size%ncornr+1,self % NumAngles) )
      allocate( self% AngleOrder(self% NangBin,self% NumBin) )
      allocate( self% BinOrder(Size% ncomm,self% NumBin) )
      allocate( self% SendOrder(self% NumBin) )
      allocate( self% numcycles(2,self % NumAngles) )
      allocate( self% listcycles(3,2*Size%ncornr) )
      allocate( self% indexExit(3,(self % NumAngles/2)*Size%nbelem) )

      allocate( self % iComms(Size% ncomm,self% NumBin) )
    endif

!   Allow for a variable number of angles per bin

    if (Ndim == 2) then

      nlevel = self% Order/2
      nang   = self% NangBin

      do i=1,nlevel
        self% NangBinList(2*i-1) = nang
        self% NangBinList(2*i)   = nang
        nang                     = nang - 2
      enddo

    elseif (Ndim == 3) then
      self% NangBinList(:) = self% NangBin
    endif

!   Space for angular coefficients

    if (Ndim == 1) then
      allocate( self % Alpha(self % NumAngles) )
      allocate( self % Tau(self % NumAngles) )
      allocate( self % Falpha(self % NumAngles) )
      allocate( self % Adweta(self % NumAngles) )

      call AngleCoef1D(self, igeom)

    else if (Ndim == 2) then
      allocate( self % Alpha(self % NumAngles) )
      allocate( self % Tau(self % NumAngles) )

      call AngleCoef2D(self)

    endif


    return

  end subroutine Quadrature_ctor

!-----------------------------------------------------------------------
  function Quadrature_getComm(self,bin,ishared) result(iComm)

!    Return a pointer to a communicator for this quadrature set
!      bin      angle bin number
!      ishared  number of neighbor
!      iComm    pointer to a communicator

!    variable declarations
     implicit none

!    passed variables
     type(Quadrature),  intent(in)   :: self
     integer,           intent(in)   :: bin, ishared 
     type(Communicator),   pointer   :: iComm

     iComm => self % iComms(ishared,bin)

     return

  end function Quadrature_getComm
                                                      
!=======================================================================
! destruct interface
!=======================================================================
                                                                                    
  subroutine Quadrature_dtor(self, Ndim)


    implicit none

!   Passed variables
                                                                                     
    type(Quadrature),  intent(inout) :: self
    integer,           intent(in)    :: Ndim

!   Local

    deallocate( self % Gnu )
    deallocate( self % AngleType )
    deallocate( self % Omega )
    deallocate( self % Weight )
    deallocate( self % Ynm )
    deallocate( self % Pnm )

!   Space for sweep data structures
    if (Ndim > 1) then
      deallocate( self% NangBinList )
      deallocate( self% next )
      deallocate( self% AngleOrder )
      deallocate( self% BinOrder )
      deallocate( self% SendOrder )
      deallocate( self% numcycles )
      deallocate( self% listcycles )
      deallocate( self% indexExit )
      deallocate( self% iComms )
    endif

!   Space for angular coefficients
    if (Ndim == 1 .or. Ndim == 2) then
      deallocate( self % Alpha )
      deallocate( self % Tau )
      deallocate( self % Falpha )
      deallocate( self % Adweta )
    else if (Ndim == 2) then
      deallocate( self % Alpha )
      deallocate( self % Tau )
    endif


    return

  end subroutine Quadrature_dtor

!=======================================================================
! destruct communicator interface
!=======================================================================
  subroutine Quadrature_dtorComm(self, Size)
                                                                                            
    use Size_mod
                                                                                            
    implicit none
                                                                                            
!   Passed variables
    type(Quadrature),  intent(inout) :: self
    type(MeshSize)                   :: Size
                                                                                            
!   Local
    type(Communicator), pointer :: Comm
    integer                     :: i, bin
                                                                                            
!   Free Communication Requests
                                                                                            
    if (Size% decomp_s == 'on') then
                                                                                            
      do bin=1,self% NumBin
        do i=1,Size% ncomm
          Comm => getMessage(self, bin, i)
          call destructBuffer(Comm)
        enddo
      enddo
                                                                                            
    endif
                                                                                            
    return

  end subroutine Quadrature_dtorComm
                                                                                            


end module Quadrature_mod

