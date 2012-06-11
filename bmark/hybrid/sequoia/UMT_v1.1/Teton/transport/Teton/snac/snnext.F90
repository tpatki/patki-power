!***********************************************************************
!                        Version 1:  09/96, PFN                        *
!                                                                      *
!   SNNEXT - This routine builds the sweep ordering array NEXT for a   *
!            single direction.                                         *
!                                                                      *
!   Input:                                                             *
!                                                                      *
!   Output:                                                            *
!                                                                      *
!***********************************************************************
   subroutine snnext(Size, Geom, QuadSet, m, maxcorner) 

   use kind_mod
   use Size_mod
   use Geometry_mod
   use Quadrature_mod

   implicit none

!  Arguments - Types

   type(MeshSize)            :: Size
   type(Geometry)            :: Geom
   type(Quadrature)          :: QuadSet

!  Arguments

   integer,    intent(in)    :: m, maxcorner

!  Local Variables

   integer    :: i,ic,icface,icexit,ndone,nnext,nlast,ncornrp,   &
                 nseed,newcorner,lastcorner,nextseed,nextcorner, &
                 MeshCycles,ncornr,maxcf 

   real(adqt) :: omega(Size%ndim)

!  Dynamic

   integer, allocatable :: DownStreamC(:,:,:)
   integer, allocatable :: need(:)
   integer, allocatable :: listcorner(:)
   integer, allocatable :: listseed(:)
   integer, allocatable :: list_in_zone(:)

!  Constants

   ncornr   = Size% ncornr
   maxcf    = Size% maxcf
   omega(:) = QuadSet% Omega(:,m)

!  Allocate arrays

   allocate( DownStreamC(maxcf,2,ncornr) )
   allocate( need(ncornr+1) )
   allocate( listcorner(ncornr) )
   allocate( listseed(ncornr) )
   allocate( list_in_zone(maxcorner) )

!  Build NEED array by computing Outward_Normal dot Omega(m)

   call snneed(Size, Geom, omega, NEED, DOWNSTREAMC) 
 
!  Create a list of corner "seeds"

   call findseeds(Size, Geom, NSEED, MESHCYCLES, &
                  need, DownStreamC, LISTSEED,   &
                  QuadSet%LISTCYCLES(1,QuadSet%totcycles+1))

   QuadSet% numcycles(1,m) = QuadSet% numcycles(1,m) + MeshCycles
   QuadSet% totcycles      = QuadSet% totcycles      + MeshCycles

!  Create the "next" array. 

   nextseed   = 1
   ndone      = 0
   nextcorner = 0
   lastcorner = 0
   newcorner  = listseed(1)
   ncornrp    = ncornr + 1


   OuterIteration: do

!  Work within a zone until we get stopped

     nlast = 1
     nnext = 0
     list_in_zone(1) = newcorner

     ZoneIteration: do

       nnext                        = nnext + 1
       ic                           = list_in_zone(nnext)
       QuadSet% next(ndone+nnext,m) = ic

!  Decrement the NEED array for corners on exiting faces

!  Exit "EZ" faces 

       do icface=1,Geom%nfpc(ic)

         icexit = DownStreamC(icface,1,ic)

         if (icexit /= ncornrp) then
           need(icexit) = need(icexit) - 1

           if (need(icexit) == 0) then
             nlast               = nlast + 1
             list_in_zone(nlast) = icexit 
           elseif (need(icexit) < 0) then
             call f90fatal("need < 0 in SNNEXT!")
           endif

         endif

       enddo

       if (nnext == nlast) then
         exit ZoneIteration
       else
         cycle ZoneIteration
       endif

     enddo ZoneIteration

!  Loop over the corners we added to the zone list, decrementing
!  the need array for corners outside the current zone

     do i=1,nnext

       ic = list_in_zone(i)

!  Exit "FP" faces into a new corner in a new zone

       do icface=1,Geom%nfpc(ic)

         icexit = DownStreamC(icface,2,ic)

         if (icexit /= ncornrp) then
           need(icexit) = need(icexit) - 1

           if (need(icexit) == 0) then
             lastcorner             = lastcorner + 1
             listcorner(lastcorner) = icexit
           elseif (need(icexit) < 0) then
             call f90fatal("need < 0 in SNNEXT!")
           endif

         endif

       enddo

     enddo

!  Exit if done or pick the next corner using the following priorities:

!      1.  in the same zone   (EZ)
!      2.  in a new zone      (FP)
!      3.  pick a new seed

     ndone = ndone + nnext

     if (ndone == ncornr) then

       exit OuterIteration

     else

       if (nextcorner < lastcorner) then
         nextcorner = nextcorner + 1
         newcorner  = listcorner(nextcorner)
       else
         nextcorner = 0
         lastcorner = 0
         if (nextseed < nseed) then
           nextseed  = nextseed + 1
           newcorner = listseed(nextseed)
         else
           call cyclebreaker(Size, Geom, ndone, MESHCYCLES,      &
                             NSEED, need, DownStreamC, LISTSEED, &
                             QuadSet%LISTCYCLES(1,QuadSet%totcycles+1))

           QuadSet% numcycles(1,m) = QuadSet% numcycles(1,m) + MeshCycles
           QuadSet% totcycles      = QuadSet% totcycles      + MeshCycles
           nextseed                = nextseed + 1
           newcorner               = listseed(nextseed)
         endif
       endif

       cycle OuterIteration

     endif

!  End of Outer Loop

   enddo OuterIteration


!  Set the extra element of NEXT to 1 (in the sweep routines we
!  need to reference the ncornr+1 entry, but it is not used)

   QuadSet% next(ncornr+1,m) = 1
 
!  Final error check
 
   if (ndone /= ncornr) then
     call f90fatal("Wrong number of corners in SNNEXT!")
   endif

!  Release memory

   deallocate( DownStreamC )
   deallocate( need )
   deallocate( listcorner )
   deallocate( listseed )
   deallocate( list_in_zone )

 
   return
   end subroutine snnext

