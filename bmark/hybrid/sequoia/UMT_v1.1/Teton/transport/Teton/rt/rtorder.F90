!***********************************************************************
!                        Version 1:  09/96, PFN                        *
!                                                                      *
!   RTORDER - This routine builds an ordered list of corners for each  *
!             unique direction.                                        *
!                                                                      *
!   Input:                                                             *
!                                                                      *
!   Output:                                                            *
!                                                                      *
!***********************************************************************
   subroutine rtorder(Size, Geom, Quad) 

   use kind_mod
   use constant_mod
   use Size_mod
   use Geometry_mod
   use QuadratureList_mod
   use Quadrature_mod

   implicit none

!  Arguments - Types
                                                                                    
   type(MeshSize)            :: Size
   type(Geometry)            :: Geom
   type(QuadratureList)      :: Quad

!  Local Variables

   type(Quadrature), pointer  :: QuadSet

   integer    :: i,ia,ib,ic,idim,iz,nc,maxcorner,m
   integer    :: ncornr,nzones,nbelem,ndim
   integer    :: NumQuadSets

   real(adqt) :: dot

!  Constants

   ncornr      = Size%ncornr
   nzones      = Size%nzones
   ndim        = Size%ndim
   nbelem      = Size%nbelem
   NumQuadSets = getNumQuadSets(Quad)

!  Find the maximum number of corners in a zone (used to
!  dimension an array in SNNEXT)

   maxcorner = 0

   do iz=1,nzones
     nc        = Geom% CList(iz+1) - Geom% CList(iz)
     maxcorner = max( maxcorner, nc )
   enddo

!  Build NEXT for all angle sets 

   AngleSetLoop: do i=1,NumQuadSets

     QuadSet => getQuadrature(Quad, i)

!  Initialize total number of cycles, cycle counter and offsets
!  per angle

     QuadSet% totcycles      = 0
     QuadSet% nbexit         = 0
     QuadSet% numcycles(:,:) = 0

     do ia=1,QuadSet% NumAngles

       if (QuadSet% AngleType(ia) /= 1) then
         QuadSet% numcycles(2,ia) = QuadSet% totcycles

         call snnext(Size, Geom, QuadSet, ia, maxcorner) 
       endif

!  Make a list of exiting angles on all boundaries

       do ib=1,nbelem
         ic  = Geom%BdyToC(1,ib)
         dot = zero

         do idim=1,ndim
           dot = dot + QuadSet% omega(idim,ia)*Geom%A_bdy(idim,ib)
         enddo

         if (dot > zero) then
           QuadSet% nbexit                       = QuadSet% nbexit + 1
           QuadSet% indexExit(1,QuadSet% nbexit) = ia
           QuadSet% indexExit(2,QuadSet% nbexit) = ib
           QuadSet% indexExit(3,QuadSet% nbexit) = ic
         endif

       enddo

     enddo

     if (QuadSet% totcycles > 2*ncornr) then
       call f90fatal("Need to dynamically allocate LISTCYCLES")
     endif

     if (QuadSet% nbexit > nbelem*(QuadSet% NumAngles/2)) then
       call f90fatal("Need to dynamically allocate IndexExit")
     endif


   enddo AngleSetLoop


   return
   end subroutine rtorder


