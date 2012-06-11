! Communication Module:  Contains data structures that tell processors
!                        how to communicate with each other 
                                                                                 
module Communicator_mod 

  use kind_mod
  use constant_mod

  private

! public interfaces

  public constructBuffer, destructBuffer
                                                                                 
  type, public :: Communicator 

     integer             :: nsend
     integer             :: nrecv

     integer,    pointer :: ListRecv(:,:)    ! ListRecv(2,nrecv)
     integer,    pointer :: ListSend(:,:)    ! ListSend(2,nsend)
     integer,    pointer :: irequest(:)      ! irequest(2)

     real(adqt), pointer :: psibsend(:)      ! psibsend(nsend) - send buffer
     real(adqt), pointer :: psibrecv(:)      ! psibrecv(nrecv) - receive buffer

  end type Communicator 

  interface constructBuffer
    module procedure Communicator_ctor_buffer
  end interface

  interface destructBuffer
    module procedure Communicator_dtor
  end interface

contains

!=======================================================================
! constructBuffer interface
!=======================================================================
                                                                                    
  subroutine Communicator_ctor_buffer(self, nsend, nrecv, Groups)

    implicit none

!   Passed variables
                                                                                     
    type(Communicator),    intent(inout) :: self
    integer,               intent(in)    :: nsend, nrecv, Groups

    self%nsend = nsend
    self%nrecv = nrecv

    allocate( self% ListRecv(2,self%nrecv) )
    allocate( self% ListSend(2,self%nsend) )
    allocate( self% irequest(2) )

    allocate( self% psibsend(self%nsend*Groups) )
    allocate( self% psibrecv(self%nrecv*Groups) )

!    self% psibsend(:) = zero
!    self% psibrecv(:) = zero

    return

  end subroutine Communicator_ctor_buffer

!=======================================================================
! destruct interface
!=======================================================================
                                                                                    
  subroutine Communicator_dtor(self)

    use mpi_param_mod
    use mpif90_mod

    implicit none

!   Passed variables
                                                                                     
    type(Communicator), intent(inout)    :: self

!   Local

    integer  :: ierr

!   Free Communication Requests

    if (self% nsend > 0) then
      call MPI_Request_Free(self%irequest(1), ierr)
    endif
                                                                                    
    if (self% nrecv > 0) then
      call MPI_Request_Free(self%irequest(2), ierr)
    endif
                                                                                    

    deallocate( self% ListSend )
    deallocate( self% ListRecv )
    deallocate( self% irequest )
    deallocate( self% psibsend )
    deallocate( self% psibrecv )


    return

  end subroutine Communicator_dtor

end module Communicator_mod

