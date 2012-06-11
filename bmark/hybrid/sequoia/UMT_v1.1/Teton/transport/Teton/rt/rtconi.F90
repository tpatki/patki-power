!***********************************************************************
!                        Version 1:  05/92, PFN                        *
!                                                                      *
!   RTCONI - Checks convergence by finding the maximum relative error  *
!            between two vectors.  Used for inner (group) iteration.   *
!                                                                      *
!   Input:   phir   - new scalar intensity      (n+1)                  *
!            phiold - previous scalar intensity (n)                    *
!                                                                      *
!   Output:  ERPHMX - maximum relative error in zonal energy density   *
!                                                                      *
!   Local:   relerr - relative errors                                  *
!                                                                      *
!*********************************************************************** 
   subroutine rtconi(Size, Geom, IterControls, ERPHMX, PHIOLD, phir)

   use kind_mod
   use mpi_param_mod
   use mpif90_mod
   use constant_mod
   use iter_control_list_mod
   use iter_control_mod
   use Size_mod
   use Geometry_mod

   implicit none

!  Arguments - Types
                                                                                    
   type(MeshSize)            :: Size
   type(Geometry)            :: Geom
   type(IterControlList)     :: IterControls

!  Arguments

   real(adqt), intent(inout) :: erphmx

   real(adqt), intent(in)    :: phir(Size%ngr,Size%ncornr)

   real(adqt), intent(inout) :: phiold(Size%nzones)

!  Local

   type(IterControl), pointer :: intensityControl

   integer, dimension(1) :: izPhiMax

   integer    :: my_node,ic,ig,iz,izepmx,nodeID,ncornr,nzones

   real(adqt) :: relerr,cutoff,threshold,energy,EnergyMax

!  Dynamic Arrays

   real(adqt),  allocatable :: solc(:)
   real(adqt),  allocatable :: solz(:)

!  Constants

   parameter (cutoff=1.0d-6)

   ncornr  = Size%ncornr
   nzones  = Size%nzones
   my_node = Size%my_node
 
!  Compute the total energy density in a zone (SOLZ)

   allocate( solc(ncornr) )
   allocate( solz(nzones) )

!  Iteration Controls

   intensityControl => getIterationControl(IterControls,"intensity")
 
!  Find the zone-average solution

   solc(:) = zero

   do ic=1,ncornr
     do ig=1,Size%ngr
       solc(ic) = solc(ic) + phir(ig,ic)
     enddo
   enddo

   call rtave(Size, Geom, solc, SOLZ)

!  Find an energy threshold for convergence tests

   izPhiMax  = maxloc( solz(:) )
   EnergyMax = solz(izPhiMax(1))

   call MPIAllReduceT(EnergyMax, "max", MPI_COMM_WORLD)

   threshold = cutoff*EnergyMax

!  Compute relative errors in the total energy density in
!  a zone; eliminate zones from consideration if their zonal
!  energy is less than a threshold 

   izepmx = 0
   erphmx = zero
 
   do iz=1,nzones

     energy = solz(iz)

     if (energy > threshold) then

       relerr = abs( (solz(iz) - phiold(iz))/solz(iz) )

       if (relerr > erphmx) then

         izepmx = iz
         erphmx = relerr

       endif

     endif

   enddo

!  If spatial decomposition is on, find the largest error in the
!  entire mesh

   relerr = erphmx 
   call MPIAllReduceT(ERPHMX, "max", MPI_COMM_WORLD)

   nodeID = -1
   if (relerr == erphmx) then
     nodeID = my_node
   endif

   call MPIAllReduceT(nodeID, "max", MPI_COMM_WORLD)

   call setLocalError(intensityControl,relerr)
   call setGlobalError(intensityControl,erphmx)
   call setZoneOfMax(intensityControl,izepmx)
   call setProcessOfMax(intensityControl,nodeID)
 
!  Save latest solution in phiold for next iteration
 
   phiold(:) = solz(:)

!  Release Memory

   deallocate( solc )
   deallocate( solz )
 

   return
   end subroutine rtconi

