!***********************************************************************
!                        Version 1:  11/98, PFN                        *
!                                                                      *
!   INITEXCHANGE - Posts receives for boundary fluxes.                 *
!                                                                      *
!   Input:                                                             *
!                                                                      *
!   Output:                                                            *
!                                                                      *
!***********************************************************************

   subroutine InitExchange(Size, QuadSet)


   use kind_mod
   use Size_mod
   use Quadrature_mod
   use Communicator_mod

   implicit none

!  Include MPI 

   include 'mpif.h'

!  Arguments Types
 
   type(MeshSize),     intent(inout) :: Size
   type(Quadrature),   intent(inout) :: QuadSet

!  Local

   type(Communicator),  pointer :: Comm

   integer    :: bin, NumBin, ishared, nrecv, ierr

   integer    :: status(MPI_STATUS_SIZE,2)


!  Wait for all nodes to arrive

   DecompTest: if (Size% decomp_s == 'on') then

     call MPI_Barrier(MPI_COMM_WORLD, ierr)


!  First, start all of the receives (receives use even numbered handles)

     NumBin = QuadSet% NumBin

     do bin=1,NumBin
       do ishared=1,Size%ncomm
         Comm => getMessage(QuadSet, bin, ishared)
         nrecv = Comm% nrecv
         if (nrecv > 0) then 
           call MPI_Start(Comm% irequest(2), ierr)
         endif
       enddo
     enddo

     call MPI_Barrier(MPI_COMM_WORLD, ierr)

   endif DecompTest



   return
   end subroutine InitExchange

