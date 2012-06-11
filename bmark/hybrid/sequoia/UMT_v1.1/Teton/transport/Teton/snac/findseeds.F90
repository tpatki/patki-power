!***********************************************************************
!                        Version 1:  04/02, PFN                        *
!                                                                      *
!   FINDSEEDS    - This routine creates a list of starting points or   *
!                  "seeds" for the grid sweep.  The seeds are on the   *
!                  boundary of the grid and require no incident        *
!                  fluxes except from boundary conditions.  There may  *
!                  be situations where no seeds can be found; this     *
!                  will occur if there is a mesh cycle right at the    *
!                  boundary.  In this situation, we are forced to use  *
!                  some old information to get started.                * 
!                                                                      *
!   Input:                                                             *
!                                                                      *
!   Output:                                                            *
!                                                                      *
!***********************************************************************
   subroutine findseeds(Size, Geom, NSEED,MESHCYCLES,  &
                        need,DownStreamC, LISTSEED,    &
                        LISTCYCLES)

   use kind_mod
   use constant_mod
   use Size_mod
   use Geometry_mod

   implicit none

!  Arguments - Types
                                                                                    
   type(MeshSize)            :: Size
   type(Geometry)            :: Geom 

!  Arguments

   integer,    intent(inout) :: meshcycles,nseed 

   integer,    intent(inout) :: need(Size%ncornr+1),     &
                                listseed(Size%ncornr),   &
                                DownStreamC(Size%maxcf,2,Size%ncornr), &
                                listcycles(3,*) 

!  Local Variables

   integer          :: i,ic,ic2,id,id2,k,n,need1,ncornr

   logical (kind=1) :: noseed 

!  Dynamic

   integer, allocatable :: listneed1(:)

!  Mesh Constants

   ncornr = Size%ncornr

!  Allocate memory

   allocate( listneed1(ncornr) )

!  Create a list of corner "seeds"

   nseed      = 0
   need1      = 0
   MeshCycles = 0

   do ic=1,ncornr
     if (need(ic) == 0) then
       nseed            = nseed + 1
       listseed(nseed)  = ic
     elseif (need(ic) == 1) then
       need1            = need1 + 1
       listneed1(need1) = ic
     endif
   enddo

   noseed = .TRUE.

   if (nseed == 0) then

!  Find a corner on the boundary that needs only one incident flux

     do k=1,need1

       if (noseed) then

         ic = listneed1(k)
         n  = 0
         do i=1,Geom%nfpc(ic)
           if (Geom%Connect(1,i,ic) == 0) n = n + 1 
         enddo

         if (n > 1) then
           id = 0
           do i=1,Geom%nfpc(ic)
             if (DownStreamc(i,1,ic) > ncornr) id=i
           enddo
            
           if (id /= 0) then
             ic2 = Geom%Connect(3,id,ic)
             id2 = Geom%Connect(4,id,ic)
             DownStreamc(id2,1,ic2) = ncornr + 1

             MeshCycles = MeshCycles + 1
             listcycles(1,MeshCycles) = ic2
             listcycles(2,MeshCycles) = ic
             listcycles(3,MeshCycles) = id 

             nseed       = 1
             listseed(1) = ic
             need(ic)    = 0

             noseed = .FALSE.
           endif

         endif

       endif

     enddo

   else

     noseed = .FALSE.

   endif

!  Error Check

   if (noseed) then 
     call f90fatal("No seeds found in FINDSEEDS!")
   endif

!  Release memory

   deallocate( listneed1 )


   return
   end subroutine findseeds 

