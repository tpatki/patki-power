!***********************************************************************
!                        Version 2:  01/98, PFN                        *
!                                                                      *
!   SNBSETS - Finds sets of reflecting boundary elements that have     *
!             the same outward normal.  Boundary element indices are   *
!             stored, in order, in LCX.  The arrays IX1 and IX2 point  *
!             to the first and last locations in LCX for each set.     *
!                                                                      *
!   Input:   px     - point coordinates  (L)                           *
!            zx     - zone-center coordinate  (L)                      *
!                                                                      *
!   Output:  VOLC   - corner volume  (V)                               *
!            VOLZ   - zone volume    (V)                               *
!                                                                      *
!***********************************************************************

   subroutine snbsets(Size, Geom)

   use kind_mod
   use constant_mod
   use Size_mod
   use Geometry_mod

   implicit none

!  Arguments - Types
                                                                                    
   type(MeshSize)            :: Size
   type(Geometry)            :: Geom

!  Local Variables

   integer    :: izero,ib,ix,ibnext,ibindex,i1,ib1, &
                 idim,nrefb,loop,ndim,nbelem

   real(adqt) :: tol,A_set(3),Area(3),A_mag,delta_A

!  Dynamic arrays

   integer, allocatable :: idone(:)
   integer, allocatable :: listb(:)
 
!  Constants

   parameter (izero=0)
   parameter (tol=1.0d-6)

   ndim   = Size%ndim
   nbelem = Size%nbelem

!  Allocate memory
 
   allocate( idone(nbelem) )
   allocate( listb(nbelem) )

!  Find the number of reflecting boundary sides; initialize IDONE

   nrefb  = 0

   do ib=1,nbelem
     if (Geom%BdyToBC(ib) == 'refl') then
       nrefb        = nrefb + 1
       listb(nrefb) = ib
     endif
   enddo

   idone(:) = izero
 
!  Find the first reflecting side:
 
   Geom% nbsets = 0
   ix           = 0
   ibnext       = listb(1)
   ibindex      = 1

   if (nrefb > 0) then
 
!  Collect sets of sides that have the same outward normal:
 
     BoundaryLoop: do loop=1,nrefb
 
!  Until we have stored away each reflecting boundary (which
!  means ix=nrefb), we continue this loop:
 
       if (ibnext > nbelem) then

         exit BoundaryLoop 

       else
 
!  At this point, the side ibnext is the first member of
!  a new set:
 
         Geom% nbsets                     = Geom% nbsets + 1
         ix                               = ix+1
         Geom% indexRefB(1,Geom% nbsets) = ix
         Geom% indexRefB(2,Geom% nbsets) = ix
         Geom% listRefB(ix)              = ibnext
         idone(ibnext)                    = 1

         A_set(:) = Geom%A_bdy(:,ibnext)
         A_mag    = zero

         do idim=1,ndim
           A_mag = A_mag + A_set(idim)*A_set(idim)
         enddo

         A_set(:) = A_set(:)/sqrt(A_mag)
 
!  If there are any remaining sides, loop over them. For each
!  that hasn't already been done, check whether it belongs
!  to this new set.  Store the index of the first one
!  that doesn't belong -- it will form the next new set.
 
         i1      = ibindex + 1
         ibnext  = nbelem  + 1
         ibindex = nrefb   + 1

         if (i1 > nrefb) then

           cycle BoundaryLoop

         else 
 
           ReflectingLoop: do ib1=i1,nrefb

             ib = listb(ib1)

             if (idone(ib) == 0) then

               Area(:) = Geom%A_bdy(:,ib)
               A_mag   = zero

               do idim=1,ndim
                 A_mag = A_mag + Area(idim)*Area(idim)
               enddo

               Area(:) = Area(:)/sqrt(A_mag)

               delta_A = zero

               do idim=1,ndim
                 delta_A = delta_A + abs(A_set(idim) - Area(idim))
               enddo

               if ( delta_A <= tol ) then
                 ix                              = ix+1
                 Geom% indexRefB(2,Geom% nbsets) = ix
                 Geom% listRefB(ix)              = ib
                 idone(ib)                       = 1
               else
                 ibnext  = min(ibnext,ib)
                 ibindex = min(ibindex,ib1)
               endif

             endif

           enddo ReflectingLoop

           cycle BoundaryLoop

         endif
 
       endif
 
     enddo BoundaryLoop
 
!  Error check

     if (Geom% indexRefB(2,Geom%nbsets) < nrefb) then
       call f90fatal("Missed some sides in SNBSETS")
     elseif (Geom% indexRefB(2,Geom%nbsets) > nrefb) then
       call f90fatal("Multi-counted sides in SNBSETS")
     endif

   endif

!  Release memory

   deallocate( idone )
   deallocate( listb )
 

   return
   end subroutine snbsets


