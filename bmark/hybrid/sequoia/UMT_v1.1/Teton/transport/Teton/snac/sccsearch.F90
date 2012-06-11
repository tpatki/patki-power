!***********************************************************************
!                        Version 1:  03/02, PFN                        *
!                                                                      *
!   SCCSEARCH    - This recursive routine search the dependency graph  *
!                  for strongly-connected components (SCC).            *
!                                                                      *
!   Input:                                                             *
!                                                                      *
!   Output:                                                            *
!                                                                      *
!***********************************************************************
   recursive subroutine sccsearch(Size, Geom, ic,ncgraph,count, &
                                  stackindex,MeshCycles,        &
                                  need,DownStreamC,dfnum,       &
                                  lowlink,stack,new,onstack,    &
                                  LISTCYCLES)

   use kind_mod
   use Size_mod
   use Geometry_mod

   implicit none

!  Arguments - Types
                                                                                    
   type(MeshSize)            :: Size
   type(Geometry)            :: Geom 

!  Arguments

   integer,    intent(in)    :: ic,ncgraph

   integer,    intent(inout) :: count,stackindex,MeshCycles 

   integer,    intent(in)    :: need(Size%ncornr) 

   integer,    intent(inout) :: dfnum(Size%ncornr),    &
                                lowlink(Size%ncornr),  &
                                stack(ncgraph),        &
                                listcycles(3,*),       &
                                DownStreamC(Size%maxcf,2,Size%ncornr) 

   logical (kind=1), intent(inout) :: new(Size%ncornr),   &
                                      onstack(Size%ncornr)

!  Local Variables

   integer     :: i,ic2,id,ncornrp,cyclesize, &
                  icbreak,icface,iclowlink

   integer     :: list(ncgraph)

!  Mesh Constants

   ncornrp = Size%ncornr + 1

!  Start the search procedure

   count       = count + 1

   dfnum(ic)   = count
   lowlink(ic) = count
   new(ic)     = .FALSE.

!  Put corner "ic" on the stack

   stackindex        = stackindex + 1
   stack(stackindex) = ic
   onstack(ic)       = .TRUE. 

!  Loop over all downstream corners that have not been completed 

   do i=1,2

     do id=1,Geom%nfpc(ic)

       ic2 = DownStreamC(id,i,ic)

       if (ic2 /= ncornrp) then

         if ( new(ic2) ) then

           call sccsearch(Size, Geom, ic2,ncgraph,count, &
                          stackindex,MeshCycles,         &
                          need,DownStreamC,dfnum,        &
                          lowlink,stack,new,onstack,     &
                          LISTCYCLES)

           if (lowlink(ic2) < lowlink(ic)) then
             lowlink(ic) = lowlink(ic2)
           endif

         else

           if (dfnum(ic2) < dfnum(ic) .and.  &
               onstack(ic2)           .and.  &
               lowlink(ic2) < lowlink(ic)) then

             lowlink(ic) = lowlink(ic2)
           endif
 
         endif

       endif

     enddo

   enddo

!  Cycle Check

   CheckCycle: if (lowlink(ic) == dfnum(ic)) then

     ic2          = stack(stackindex)
     stackindex   = stackindex - 1
     onstack(ic2) = .FALSE. 

     DetectCycle: if (ic2 /= ic) then

       cyclesize  = 0

       do while (ic2 /= ic)
         cyclesize           = cyclesize + 1
         list(cyclesize)     = ic2 

         ic2                 = stack(stackindex)
         stackindex          = stackindex - 1
       enddo

       cyclesize           = cyclesize + 1
       list(cyclesize)     = ic2
       onstack(list(1))    = .TRUE.

!***********************************************************************
!  Now break all connections of corners on the stack to the lowest     *
!  link.                                                               *
!***********************************************************************

       iclowlink = list(cyclesize)

!  Loop over all neighbors for this corner and find the ones on the stack

       do id=1,Geom%nfpc(iclowlink)

!        EZ faces

         icbreak = Geom%Connect(3,id,iclowlink)
         icface  = Geom%Connect(4,id,iclowlink)

         if ( onstack(icbreak) .and.   &
              DownStreamc(icface,1,icbreak) == iclowlink ) then
           DownStreamc(icface,1,icbreak) = ncornrp
           MeshCycles = MeshCycles + 1
           listcycles(1,MeshCycles) = icbreak
           listcycles(2,MeshCycles) = iclowlink
           listcycles(3,MeshCycles) = id
         endif

!        FP faces

         icbreak = Geom%Connect(1,id,iclowlink)
         icface  = Geom%Connect(2,id,iclowlink)

         if (icbreak /= 0) then
           if ( onstack(icbreak) .and.   &
                DownStreamc(icface,2,icbreak) == iclowlink ) then
             DownStreamc(icface,2,icbreak) = ncornrp
             MeshCycles = MeshCycles + 1
             listcycles(1,MeshCycles) = icbreak
             listcycles(2,MeshCycles) = iclowlink
             listcycles(3,MeshCycles) = id
           endif
         endif

       enddo

!  Reset the stack

       do i=1,cyclesize
         icbreak          = list(i)
         onstack(icbreak) = .FALSE.
       enddo

     endif DetectCycle

   endif CheckCycle



   return
   end subroutine sccsearch 
 
