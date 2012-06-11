!***********************************************************************
!                        Version 1:  07/01, PFN                        *
!                                                                      *
!   CYCLEBREAKER - This routine breaks cycles in the mesh by selecting *
!                  a corner that will use some old (i.e. previous      *
!                  iterate) incident fluxes.                           *
!                                                                      *
!   Input:                                                             *
!                                                                      *
!   Output:                                                            *
!                                                                      *
!***********************************************************************
   subroutine cyclebreaker(Size, Geom, ndone,MESHCYCLES, &
                           NSEED,need,DownStreamC,       &
                           LISTSEED,LISTCYCLES)

   use kind_mod
   use constant_mod
   use Size_mod
   use Geometry_mod

   implicit none

!  Arguments - Types
                                                                                    
   type(MeshSize)            :: Size
   type(Geometry)            :: Geom 

!  Arguments

   integer,    intent(in)    :: ndone

   integer,    intent(inout) :: meshcycles,nseed 

   integer,    intent(in)    :: DownStreamC(Size%maxcf,2,Size%ncornr) 

   integer,    intent(inout) :: need(Size%ncornr+1),   &
                                listseed(Size%ncornr), &
                                listcycles(3,*) 

!  Local Variables

   integer :: i,ic,icds,ncgraph,n,nleft,count,stackindex,ncornr

!  Dynamic

   integer, allocatable :: listc(:)
   integer, allocatable :: dfnum(:)
   integer, allocatable :: lowlink(:)
   integer, allocatable :: stack(:)

   logical (kind=1), allocatable :: new(:)
   logical (kind=1), allocatable :: onstack(:)

!  Mesh Constants

   ncornr = Size%ncornr

!  Allocate arrays for the number of corners in the graph (= ncornr - ndone)

   ncgraph = ncornr - ndone

   allocate( listc(ncgraph) )
   allocate( dfnum(ncornr) )
   allocate( lowlink(ncornr) )
   allocate( stack(ncgraph) )

   allocate( new(ncornr) )
   allocate( onstack(ncornr) )

!  Initialize arrays and counters

   new(:)     = .TRUE. 
   onstack(:) = .FALSE. 

   MeshCycles = 0
   count      = 0
   stackindex = 0

   stack(:)   = 0

!  Make a list of all remaining corners

   nleft = 0

   do ic=1,ncornr
     if (need(ic) == 0) then
       new(ic)      = .FALSE. 
     else
       nleft        = nleft + 1
       listc(nleft) = ic
     endif
   enddo

   if (nleft /= ncgraph) then
     call f90fatal("Miscount of remaining corners in CYCLEBREAKER")
   endif

!  Loop over the number of corners in the graph

   do i=1,ncgraph

     ic = listc(i)

     if ( new(ic) ) then

       call sccsearch(Size, Geom, ic,ncgraph,count, &
                      stackindex,MESHCYCLES,        &
                      need,DownStreamC,dfnum,       &
                      lowlink,stack,new,onstack,    &
                      LISTCYCLES)

     endif

   enddo


   if (MeshCycles == 0) then 

     call f90fatal("Cycle detection failed in CYCLEBREAKER!")

   else

     n = 0
     do i=1,MeshCycles
       icds       = listcycles(2,i)
       need(icds) = need(icds) - 1

       if ( need(icds) == 0 ) then
         n = n + 1
         listseed(nseed+n) = icds
       endif 
     enddo

     nseed = nseed + n

     if (n == 0) then
       call f90fatal("Cycles found, but not broken")
     endif

   endif

!  Release memory

   deallocate( listc )
   deallocate( dfnum )
   deallocate( lowlink )
   deallocate( stack )
   deallocate( new )
   deallocate( onstack )


   return
   end subroutine cyclebreaker
 
