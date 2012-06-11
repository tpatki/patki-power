!***********************************************************************
!                        Version 1:  05/92, PFN                        *
!                                                                      *
!   RSWP1D - Controls transport sweeps for 1D grids.                   *
!                                                                      *
!   Input:   see routines RTSTRT, RTSWPSC and RTSWPSLB                 *
!                                                                      *
!   Output:  PSIC  - corner angular photon intensity        (E/A/t)    *
!                                                                      *
!***********************************************************************
   subroutine rswp1d(Size, Geom, Mat, QuadSet, IterControls,   &
                     asrcc, srcc, PSIB, PSIR, PHIR)

   use kind_mod
   use constant_mod
   use Size_mod
   use Geometry_mod
   use Material_mod
   use Quadrature_mod
   use iter_control_list_mod
   use iter_control_mod

   implicit none

!  Arguments - Types

   type(MeshSize)            :: Size
   type(Geometry)            :: Geom
   type(Material)            :: Mat
   type(Quadrature)          :: QuadSet
   type(IterControlList)     :: iterControls

!  Arguments

   real(adqt), intent(in)    :: asrcc(QuadSet%Groups,Size%ncornr,QuadSet%NumAngles), &
                                srcc(QuadSet%Groups,Size%ncornr)

   real(adqt), intent(inout) :: psib(QuadSet%Groups,Size%nbelem,QuadSet%NumAngles),  &
                                psir(QuadSet%Groups,Size%ncornr,QuadSet%NumAngles),  &
                                phir(QuadSet%Groups,Size%ncornr)

!  Local

   type(IterControl), pointer :: scatteringControl

   integer    :: ic,iz,ixi,icmax,mstdr,nAngLevel,nStartDir,niters

   integer    :: ncornr, NumAngles, NumGroups 

   real(adqt) :: relerr,floor,errmax

   real(adqt) :: quadwt(QuadSet%NumAngles)

!  Dynamic

   real(adqt),  allocatable :: ophir(:)
   real(adqt),  allocatable :: qc(:,:)
   real(adqt),  allocatable :: scscat(:,:)
   real(adqt),  allocatable :: sigvol(:,:)
   real(adqt),  allocatable :: psimmh(:,:)

!  Constants

   parameter (floor=1.0d-30)

   ncornr              = Size%ncornr
   NumAngles           = QuadSet%NumAngles
   NumGroups           = QuadSet%Groups
   quadwt(1:NumAngles) = QuadSet%Weight(1:NumAngles)

!  Allocate space

   allocate( ophir(ncornr) )
   allocate( qc(NumGroups,ncornr) )
   allocate( scscat(NumGroups,ncornr) )
   allocate( sigvol(NumGroups,ncornr) )
   allocate( psimmh(NumGroups,ncornr) )

!  Perform Scattering Iteration

   niters = 0

!  Set the number of starting directions

   nStartDir = 0

   if (Size%igeom == 'sphere') then
     nStartDir = 1
   elseif (Size%igeom == 'cylinder') then
     nStartDir = QuadSet%Order/2
   endif

   do ic=1,ncornr
     iz           = Geom%CToZone(ic)
     sigvol(:,ic) = Mat%sigt(:,iz)*Geom%volc(ic)
   enddo

   ScatteringIteration: do 

     niters = niters + 1 

!  Save previous iterate

     ophir(:) = phir(1,:)

     if (Size%igeom == 'sphere' .or. Size%igeom == 'cylinder') then

!  Loop over XI levels (spheres have only 1 XI level while cylinders
!  have norder/2).  MSTDR gives the location of the starting direction
!  in two-dimensional arrays.
 
       mstdr = 1
 
       XiLevelLoop: do ixi=1,nStartDir
 
         nAngLevel = QuadSet%Order - 2*(ixi-1)
 
!  Solve starting direction equations

         call  rtstartdir(Size, Geom, Mat, QuadSet, mstdr,  &
                          asrcc, srcc, qc, scscat, sigvol,  &
                          PSIB, PSIR, PHIR)
 
!  Do remaining transport sweeps

         call rtswpsc(Size, Geom, Mat, QuadSet, mstdr, nAngLevel,  &
                      asrcc, srcc, qc, scscat, sigvol, psimmh,     &
                      PSIB, PSIR, PHIR)

         mstdr = mstdr + nAngLevel + 1
 
       enddo XiLevelLoop

     elseif (Size%igeom == 'slab') then

       call rtswpslb(Size, Geom, Mat, QuadSet,         &
                     asrcc, srcc, qc, scscat, sigvol,  &
                     PSIB, PSIR, PHIR)

     endif

!  Update scalar photon intensity
 
     call rtscal(NumGroups,ncornr,NumAngles,quadwt,psir,PHIR)

!  Find largest relative errors (ERRMAX) and location (ICMAX)

     icmax  = 0
     errmax = zero
 
     do ic=1,ncornr

       relerr = abs(phir(1,ic) - ophir(ic))/  &
               (abs(phir(1,ic)) + floor)

       if (relerr > errmax) then
         icmax  = ic 
         errmax = relerr
       endif

     enddo

!  Test for convergence:

     if (errmax <= getEpsilonPoint(scatteringControl) .or.  &
         niters >= getMaxNumberOfIterations(scatteringControl)) then
       exit ScatteringIteration
     else
       cycle ScatteringIteration
     endif

   enddo ScatteringIteration

!  Update the iteration count

   niters = niters + getNumberOfIterations(scatteringControl) 


   call setNumberOfIterations(scatteringControl,niters)

!  Release memory

   deallocate( ophir )
   deallocate( qc )
   deallocate( scscat )
   deallocate( sigvol )
   deallocate( psimmh )
 

   return
   end subroutine rswp1d

