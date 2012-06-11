!***********************************************************************
!                        Version 1:  11/98, PFN                        *
!                                                                      *
!   INITCOMM - Initializes persistent communication objects that are   *
!              used to exchange boundary fluxes.                       *
!                                                                      *
!   Input:   psibsend - dedicated send buffer                          *
!            psibrecv - dedicated receive buffer                       *
!                                                                      *
!   Output:  IREQUEST - communication "handles"                        *
!                                                                      *
!***********************************************************************

   subroutine initcomm(Geom, QuadSet, ncomm)

   use kind_mod
   use Geometry_mod
   use Quadrature_mod
   use Communicator_mod

   implicit none

!  Include MPI   

   include 'mpif.h'

!  Arguments - Types
                                                                                    
   type(Geometry)            :: Geom
   type(Quadrature)          :: QuadSet

   integer,    intent(in)    :: ncomm

!  Local

   type(Communicator), pointer :: Comm

   integer :: bin,ishared,ierr,irecv,isend,tagRecv,tagSend, &
              tag,nrecv,nsend,NumBin,Groups

!  Wait for all nodes to arrive

     call MPI_Barrier(MPI_COMM_WORLD, ierr)

     NumBin = QuadSet% NumBin
     Groups = QuadSet% Groups
     tag    = 700

!  Each message is attached to an angle bin

     AngleBin: do bin=1,NumBin

!  Loop over the number of shared surfaces

       CommunicatorLoop: do ishared=1,ncomm

         irecv = Geom% nodecomm(1,ishared)
         isend = irecv
         Comm  => getMessage(QuadSet, bin, ishared)

!  Initialize Persistant Communication Objects (receives are "even"
!  requests and sends are "odd" requests)

         nsend = Comm% nsend*Groups 
         nrecv = Comm% nrecv*Groups 

         if (nrecv > 0) then
           tagRecv = tag + bin
           call MPI_Recv_init(Comm% psibrecv, nrecv, MPI_REAL8,  &
                              irecv,  tagRecv,  MPI_COMM_WORLD, &
                              Comm% irequest(2), ierr)
         endif

         if (nsend > 0) then
           tagsend = tag + bin
           call MPI_Send_init(Comm% psibsend, nsend, MPI_REAL8,  & 
                              isend,  tagSend,  MPI_COMM_WORLD, &
                              Comm% irequest(1), ierr)
         endif


       enddo CommunicatorLoop

     enddo AngleBin


   return
   end subroutine initcomm

