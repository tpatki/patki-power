!***********************************************************************
!                        Version 1:  05/92, PFN                        *
!                                                                      *
!   RTCONV - Checks convergence by finding the maximum relative error  *
!            between two vectors.  Used for temperature iteration.     *
!                                                                      *
!   Input:   xnew   - new solution      (n+1)                          *
!            xold   - previous solution (n)                            *
!                                                                      *
!   Output:  errmax - maximum relative error over all zones            *
!                                                                      *
!   Local:   relerr - relative errors                                  *
!                                                                      *
!***********************************************************************
 
   subroutine rtconv(Size, Geom, Mat, IterControls, ERRTMP)

   use kind_mod
   use mpi_param_mod
   use mpif90_mod
   use constant_mod
   use iter_control_list_mod
   use iter_control_mod
   use Size_mod
   use Geometry_mod
   use Material_mod

   implicit none

!  Arguments - Types
                                                                                    
   type(MeshSize)            :: Size
   type(Geometry)            :: Geom
   type(Material)            :: Mat
   type(IterControlList)     :: IterControls

!  Arguments

   real(adqt), intent(inout) :: errtmp

!  Local Variables

   type(IterControl), pointer :: temperatureControl

   integer    :: my_node, iz, izetmx, nodeID, ncornr, nzones

   real(adqt) :: relerr, AveTemp, sumTempVol, sumVol, threshold

!  Dynamic Arrays

   real(adqt),  allocatable :: teznew(:)

!  Mesh Constants

   ncornr  = Size%ncornr
   nzones  = Size%nzones
   my_node = Size%my_node

!  Iteration Controls
    
   temperatureControl => getIterationControl(IterControls,"temperature")

!  Compute zone average temperature

   allocate( teznew(nzones) )
 
   call rtave(Size, Geom, Mat%tec, TEZNEW)

!  Compute a threshold temperature for checking convergence

   sumTempVol = zero
   sumVol     = zero

   do iz=1,nzones
     sumTempVol = sumTempVol + Geom%volz(iz)*teznew(iz)
     sumVol     = sumVol     + Geom%volz(iz)
   enddo

   call MPIAllReduceT(sumTempVol, "sum", MPI_COMM_WORLD)
   call MPIAllReduceT(sumVol,     "sum", MPI_COMM_WORLD)

   AveTemp = sumTempVol/sumVol

   threshold = AveTemp/twenty     
 
!  Find maximum relative error in the zonal temperature
 
   izetmx = 0
   errtmp = zero

   do iz=1,nzones

     if (teznew(iz) > threshold) then

       relerr = abs(one - Mat%tezold(iz)/teznew(iz))

       if (relerr > errtmp) then

         izetmx = iz
         errtmp = relerr

       endif

     endif

   enddo

!  If spatial decomposition is on, find the largest error in the
!  entire mesh

   relerr = errtmp
   call MPIAllReduceT(ERRTMP, "max", MPI_COMM_WORLD)

   nodeID = -1
   if (relerr == errtmp) then
     nodeID = my_node
   endif
                                                                                   
   call MPIAllReduceT(nodeID, "max", MPI_COMM_WORLD)

   call setLocalError(temperatureControl,relerr)
   call setGlobalError(temperatureControl,errtmp)
   call setZoneOfMax(temperatureControl,izetmx)
   call setProcessOfMax(temperatureControl,nodeID)

!  Save latest solution in TEZOLD for next iteration
 
   Mat%tezold(:) = teznew(:)

!  Release Memory

   deallocate( teznew )

 
   return
   end subroutine rtconv

