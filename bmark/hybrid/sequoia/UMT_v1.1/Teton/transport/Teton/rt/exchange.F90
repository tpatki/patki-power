!***********************************************************************
!                        Version 1:  11/98, PFN                        *
!                                                                      *
!   EXCHANGE - Sends and receives boundary fluxes on shared surfaces.  *
!                                                                      *
!   Input:   PSIB  - boundary intensities                      (E/A/t) *
!                                                                      *
!   Output:  PSIB  - boundary intensities after communication  (E/A/t) *
!                                                                      *
!***********************************************************************

   subroutine exchange(Size, QuadSet, PSIB, binSend, binRecv) 

   use kind_mod
   use Size_mod
   use Quadrature_mod
   use Communicator_mod

   implicit none

!  Include MPI 

   include 'mpif.h'

!  Arguments Types
 
   type(MeshSize),     intent(in)    :: Size
   type(Quadrature),   intent(in)    :: QuadSet

!  Arguments

   integer, intent(in)       :: binSend, binRecv

   real(adqt), intent(inout) :: psib(QuadSet%Groups,Size%nbelem,QuadSet%NumAngles) 

!  Local

   type(Communicator),  pointer :: Comm 

   integer    :: i,ia,ib,ig,ishared,message,ncomm,ngroups,  &
                 ierr,bin,mybin,nsend,nrecv 

   integer    :: binSend1, binSend2, binRecv1, binRecv2

   integer    :: status(MPI_STATUS_SIZE,2)

!  Constants

   ncomm   = Size%ncomm
   ngroups = QuadSet%Groups

   if (binSend /= 0) then
      binSend1 = binSend
      binSend2 = binSend 
   else
      binSend1 = 1 
      binSend2 = QuadSet% NumBin 
   endif

   if (binRecv /= 0) then
      binRecv1 = binRecv
      binRecv2 = binRecv
   else
      binRecv1 = 1
      binRecv2 = QuadSet% NumBin
   endif

!  Exchange boundary information with neighbors
!  Loop over the number of angle bins (in most cases this is 1)

   DecompTest: if (Size% decomp_s == 'on') then


     AngleBin1: do bin=binSend1,binSend2

!  Loop over the number of shared surfaces; for each shared surface
!  we issue one send and one receive

       SendLoop: do ishared=1,ncomm

         Comm => getMessage(QuadSet, bin, ishared)
         nsend = Comm% nsend

!  Accumulate data to send

         if (nsend > 0) then

           message = 0 

!  Loop over exiting angle, boundary element pairs for this communicator 

           do i=1,nsend

             ia = Comm% ListSend(1,i)
             ib = Comm% ListSend(2,i)

             do ig=1,ngroups
               Comm% psibsend(message+ig) = psib(ig,ib,ia)
             enddo

             message = message + ngroups

           enddo

!  Start send for this communicator (odd numbered handle)

           call MPI_Start(Comm% irequest(1), ierr)

         endif

       enddo SendLoop

     enddo AngleBin1

!  Make sure all sends are complete

     do bin=binSend1,binSend2
       do ishared=1,ncomm
         Comm => getMessage(QuadSet, bin, ishared)
         nsend = Comm% nsend

         if (nsend > 0) then
           call MPI_Wait(Comm% irequest(1), status, ierr)
         endif
       enddo
     enddo

!  Process data we receive

     AngleBin2: do bin=binRecv1,binRecv2

       ReceiveLoop: do ishared=1,ncomm

         mybin = QuadSet% BinOrder(ishared,bin)
         Comm => getMessage(QuadSet, mybin, ishared)
         nrecv = Comm% nrecv

         if (nrecv > 0) then

!  Check for completion of the receive

           call MPI_Wait(Comm% irequest(2), status, ierr)

           message = 0 

!  Loop over incident angle, boundary element pairs for this communicator

           do i=1,nrecv

             ia = Comm% ListRecv(1,i)
             ib = Comm% ListRecv(2,i)

             do ig=1,ngroups
               psib(ig,ib,ia) = Comm% psibrecv(message+ig)
             enddo

             message = message + ngroups

           enddo

         endif

!  End loop over shared surfaces

       enddo ReceiveLoop

     enddo AngleBin2

   endif DecompTest



   return
   end subroutine exchange

