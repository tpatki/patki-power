!***********************************************************************
!                        Version 1:  12/98, PFN                        *
!                                                                      *
!   FINDEXIT - Find the angles that are exiting for each boundary      *
!              element on a shared surface.                            *
!                                                                      *
!   Input:   A_bdy - outward normal vector for boundary elements   (A) *
!            omega - direction cosines                                 *
!                                                                      *
!   Output:  LASTINC/ - for each shared boundary element, points to    *
!            LASTEXIT   the last entry in LISTINC/LISTEXIT for that    *
!                       boundary element                               *
!            LISTINC  - ordered list (by boundary element) of all      *
!                       incident directions                            *
!            LISTEXIT - ordered list (by boundary element) of all      *
!                       exiting directions                             *
!            IBCOMM   - contains the following information for each    *
!                       communicator:                                  *
!                            1 = starting point in 'last' arrays       *
!                            2 = ending point in 'last' arrays         *
!                            3 = length of the send                    *
!                            4 = length of the receive                 *
!            NODEINDX - given a node number, returns the communicator  *
!                       number                                         *
!                                                                      *
!***********************************************************************

   subroutine findexit(Size, Geom, Quad)

   use kind_mod
   use constant_mod
   use Size_mod
   use Geometry_mod
   use Communicator_mod
   use QuadratureList_mod
   use Quadrature_mod

   implicit none

!  Include MPI

   include 'mpif.h'

!  Arguments - Types
                                                                                    
   type(MeshSize)            :: Size
   type(Geometry)            :: Geom
   type(QuadratureList)      :: Quad

!  Local

   type(Quadrature),   pointer :: QuadSet
   type(Communicator), pointer :: Comm

   integer    :: i,ia,ib,ii,ishared,iset,  &
                 nsend,nrecv,neighbor,HalfBdyElem,    &
                 istartL,ifinishL,istartN,ifinishN,   &
                 lensend,lenrecv,izero,ierr,ncount,   &
                 FirstBdyElem,LastBdyElem,NbdyElem,   &
                 angle1,angle2,bin,NbL 

   integer    :: my_node, ndim, ncomm, nbshare
   integer    :: NumQuadSets, NumAngles, NumBin, NangBin, Groups 

   integer    :: status(MPI_STATUS_SIZE,2),request(2)

   real(adqt) :: dot

!  Dynamic

   integer,  allocatable :: idot(:,:)
   integer,  allocatable :: ListSend(:,:)
   integer,  allocatable :: ListRecv(:,:) 

!  Constants

   parameter (izero=0)
   parameter (ncount=2)


   DecompTest: if (Size% decomp_s == 'on') then

     my_node  = Size%my_node
     ndim     = Size%ndim
     ncomm    = Size%ncomm
     nbshare  = Size%nbshare

!    Loop over angle sets

     NumQuadSets = getNumQuadSets(Quad)

     SetLoop: do iset=1,NumQuadSets

       QuadSet   => getQuadrature(Quad, iset)

       NumAngles = QuadSet% NumAngles
       NumBin    = QuadSet% NumBin
       Groups    = QuadSet% Groups

!      Allocate a buffer for communication

       allocate( idot(NumAngles,nbshare) )
       allocate( ListSend(2,NumAngles*nbshare) )
       allocate( ListRecv(2,NumAngles*nbshare) )

       idot(:,:) = izero

!      Wait for all nodes to arrive

       call MPI_Barrier(MPI_COMM_WORLD, ierr)

!  Loop over all shared boundary elements and decide  
!  which angles are exiting and which are incident on 
!  shared surfaces (we only need to check the unique 
!  angle set).  Each process on a shared surface computes
!  dot products for half of the boundary elements and then
!  the results are exchanged.


       FirstBdyElem = 1

       CommunicatorLoop1: do ishared=1,ncomm

         neighbor    = Geom% nodecomm(1,ishared)
         NbdyElem    = Geom% nodecomm(2,ishared)
         HalfBdyElem = NbdyElem/2
         LastBdyElem = FirstBdyElem + NbdyElem - 1

         if (my_node < neighbor) then
           istartL  = FirstBdyElem 
           istartN  = FirstBdyElem + HalfBdyElem 
           ifinishL = FirstBdyElem + HalfBdyElem - 1 
           ifinishN = LastBdyElem 
         else
           istartL  = FirstBdyElem + HalfBdyElem 
           istartN  = FirstBdyElem 
           ifinishL = LastBdyElem 
           ifinishN = FirstBdyElem + HalfBdyElem - 1 
         endif

         NbL        = ifinishL - istartL + 1
         lensend    = NumAngles*NbL
         lenrecv    = NumAngles*(NbdyElem - NbL) 

!  Start receives

         call MPI_Irecv(idot(1,istartN), lenrecv, MPI_INTEGER, &
                        neighbor, 400, MPI_COMM_WORLD, request(2), ierr)

!  Loop over boundary elements

         BoundaryElements1: do i=istartL,ifinishL

           ib = Geom% CbdyComm(i)

           AngleLoop1: do ia=1,NumAngles

             dot = zero 

             do ii=1,ndim
               dot = dot + QuadSet% omega(ii,ia)*Geom%A_bdy(ii,ib)
             enddo

             if (dot < zero) then
               idot(ia,i) = -1
             elseif (dot > zero) then
               idot(ia,i) =  1
             endif

           enddo AngleLoop1 

       enddo BoundaryElements1 

       call MPI_Isend(idot(1,istartL), lensend, MPI_INTEGER, &
                      neighbor, 400, MPI_COMM_WORLD, request(1), ierr)

       call MPI_Waitall(ncount, request, status, ierr)

!  Dot products received from neighbor have the opposite sign

       idot(:,istartN:ifinishN) = -idot(:,istartN:ifinishN)

       FirstBdyElem             = LastBdyElem + 1 

     enddo CommunicatorLoop1


!  Now create the lists of incident and exiting boundary elements 
!  for each angle in the quadrature set

     angle1 = 1

     AngleBin: do bin=1,NumBin

       NangBin      = QuadSet% NangBinList(bin) 
       angle2       = angle1 + NangBin - 1
       FirstBdyElem = 1

       CommunicatorLoop2: do ishared=1,ncomm

         Comm => getMessage(QuadSet, bin, ishared)

         NBdyElem    = Geom% nodecomm(2,ishared)
         LastBdyElem = FirstBdyElem + NBdyElem - 1

         nsend = 0
         nrecv = 0

         BoundaryElements2: do i=FirstBdyElem,LastBdyElem

           ib = Geom% CbdyComm(i)

           AngleLoop2: do ia=angle1,angle2

             if (idot(ia,i) < izero) then
               nrecv             = nrecv + 1
               ListRecv(1,nrecv) = ia
               ListRecv(2,nrecv) = ib
             elseif (idot(ia,i) > izero) then
               nsend             = nsend + 1
               ListSend(1,nsend) = ia
               ListSend(2,nsend) = ib
             endif

           enddo AngleLoop2

         enddo BoundaryElements2

!  Allocate send/receive buffers for this message
         call constructBuffer(Comm, nsend, nrecv, Groups)

         Comm%ListRecv(:,1:nrecv) = ListRecv(:,1:nrecv)
         Comm%ListSend(:,1:nsend) = ListSend(:,1:nsend)
 
         FirstBdyElem = FirstBdyElem + NBdyElem 

       enddo CommunicatorLoop2

       angle1 = angle1 + NangBin 

     enddo AngleBin

!  Initialize communication handles for persistent communicators
     call initcomm(Geom, QuadSet, ncomm)


!  Use an assertion here to check that neighboring nodes agree
!  on the incident and exiting angle lists

!  Release memory

       deallocate( idot )
       deallocate( ListSend )
       deallocate( ListRecv )

       call MPI_Barrier(MPI_COMM_WORLD, ierr)

     enddo SetLoop


   endif DecompTest


   return
   end subroutine findexit

