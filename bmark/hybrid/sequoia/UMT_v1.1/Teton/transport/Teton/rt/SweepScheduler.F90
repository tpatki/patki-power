!***********************************************************************
!                        Version 1:  09/96, PFN                        *
!                                                                      *
!   SWEEPSCHEDULER - This routine determines the order in which the    *
!                    discrete ordinates will be solved.                *
!                                                                      *
!   Input:                                                             *
!                                                                      *
!   Output:                                                            *
!                                                                      *
!***********************************************************************
   subroutine SweepScheduler(Size, Geom, Quad)

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

!  Local Variables

   type(Quadrature),   pointer :: QuadSet
   type(Communicator), pointer :: Comm

   integer :: status(MPI_STATUS_SIZE,2),request(2*Size%ncomm)

   integer :: i, ia, ib, m, ndone, neighbor,        &
              iset, ishared, bin, maxdepend, nsend, &
              ierr, nleft, nbelem, ncomm, my_node

   integer :: NumQuadSets, NumBin, NangBin

   integer, dimension (1) :: imax

   real(adqt) :: dot

!  Dynamic

   integer,  allocatable :: depend(:)
   integer,  allocatable :: BinTally(:)
   integer,  allocatable :: Order(:)
   integer,  allocatable :: temp(:)
   integer,  allocatable :: buffer(:,:) 
   integer,  allocatable :: BinOffSet(:)

!  Mesh Constants

   nbelem      = Size%nbelem
   ncomm       = Size%ncomm
   my_node     = Size%my_node
   NumQuadSets = getNumQuadSets(Quad)

   AngleSetLoop: do iset=1,NumQuadSets

     QuadSet => getQuadrature(Quad, iset)
     NumBin  =  QuadSet% NumBin

!  Allocate temporaries

     allocate( depend(NumBin) )
     allocate( BinTally(NumBin) )
     allocate( Order(NumBin) )
     allocate( temp(NumBin) )
     allocate( buffer(NumBin,ncomm) )
     allocate( BinOffSet(NumBin) )

!  Tally message size by angle bin

     if (Size% decomp_s == 'on') then

       BinTally(:) = 0

       AngleBin: do bin=1,NumBin
         CommunicatorLoop: do ishared=1,ncomm
           Comm => getMessage(QuadSet, bin, ishared)

           BinTally(bin) = BinTally(bin) + Comm% nrecv 

         enddo CommunicatorLoop
       enddo AngleBin

     else

       BinTally(:) = 1

     endif

!  Tally dependencies for reflecting boundaries

     m = 0

     do bin=1,NumBin
       depend(bin) = 0
       NangBin     = QuadSet% NangBinList(bin)
       do i=1,NangBin
         m = m + 1
         do ib=1,nbelem
           if (Geom%BdyToBC(ib) == 'refl') then
             dot = DOT_PRODUCT( QuadSet%omega(:,m),Geom%A_bdy(:,ib) ) 
             if (dot < zero) then
               depend(bin) = depend(bin) + BinTally(bin) 
             endif
           endif
         enddo
       enddo
     enddo

     imax      = maxloc( depend(1:NumBin) )
     maxdepend = depend(imax(1))
     ndone     = 0 

     do while (maxdepend > 0)
       ndone             = ndone + 1
       Order(ndone)      = imax(1)
       BinTally(imax(1)) = -999 
       depend(imax(1))   = -999 

       imax      = maxloc( depend(1:NumBin) )
       maxdepend = depend(imax(1))
     enddo

     temp(:) = Order(:)

     do i=1,ndone
       Order(NumBin-i+1) = temp(i)
     enddo



     if (Size% decomp_s == 'off') then
 
       do i=1,NumBin-ndone
         imax            = maxloc( depend(1:NumBin) )
         Order(i)        = imax(1)
         depend(imax(1)) = -999
       enddo

     elseif (Size% decomp_s == 'on') then

!  Sort remaining bins from largest message to smallest

!  Post Receives

       do ishared=1,ncomm
         neighbor = Geom% nodecomm(1,ishared)
         nsend    = NumBin 

         call MPI_Irecv(buffer(1,ishared), nsend, MPI_INTEGER, &
                        neighbor, 500, MPI_COMM_WORLD,         &
                        request(2*ishared), ierr)
       enddo

!  Sort

       imax = maxloc( BinTally(1:NumBin) )

       nleft = NumBin - ndone
       do i=nleft,1,-1
         Order(i)          = imax(1)
         BinTally(imax(1)) = -999 
         imax              = maxloc( BinTally(1:NumBin) )
       enddo

!  Send my order to all neighbors

       do ishared=1,ncomm
         neighbor = Geom% nodecomm(1,ishared)
         nsend    = NumBin 

         call MPI_Isend(Order, nsend, MPI_INTEGER,      &
                        neighbor, 500, MPI_COMM_WORLD,  &
                        request(2*ishared-1), ierr)

         call MPI_Wait(request(2*ishared-1), status, ierr)
       enddo

       call MPI_Barrier(MPI_COMM_WORLD, ierr)


       do ishared=1,ncomm
         call MPI_Wait(request(2*ishared), status, ierr)
         do i=1,NumBin
           QuadSet% BinOrder(ishared,i) = buffer(i,ishared)
         enddo
       enddo

     endif

     BinOffSet(1) = 0
     do bin=2,NumBin
       BinOffSet(bin) = BinOffSet(bin-1) + QuadSet% NangBinList(bin-1)
     enddo

     do i=1,NumBin
       bin                   = Order(i)
       NangBin               = QuadSet% NangBinList(bin)
       QuadSet% SendOrder(i) = bin
       do ia=1,NangBin
         QuadSet% AngleOrder(ia,i) = BinOffSet(bin) + ia
       enddo
     enddo

!  Release Temporaries
     deallocate( depend )
     deallocate( BinTally )
     deallocate( Order )
     deallocate( temp )
     deallocate( buffer )
     deallocate( BinOffSet )

   enddo AngleSetLoop



   return
   end subroutine SweepScheduler 

