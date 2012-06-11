!***********************************************************************
!                        Version 1:  09/96, PFN                        *
!                                                                      *
!   SNFLWXYZ - This routine, called by RSWPMD and RTACCELMD, solves    *
!              the fixed-source transport problem on an arbitrary      *
!              grid in either xyz-geometry or rz-geometry.             *
!              An upstream corner-balance spatial discretization is    *
!              used.                                                   *
!                                                                      *
!   Input:                                                             *
!                                                                      *
!   Output:                                                            *
!                                                                      *
!***********************************************************************

   subroutine snflwxyz(angleLoopTime, Size, Geom, QuadSet,   &
                       npart,nsig,ndir,                & 
                       itimsrc,iggsct,ipath,storePsi,  &
                       sigt,sigs,asc,sc,PSIB,PSIC,PHIC)


   use kind_mod
   use constant_mod
   use Size_mod
   use Geometry_mod
   use Quadrature_mod

#include "assert.h"

   implicit none

   include 'mpif.h'
!  Arguments - Types
                                                                                    
   type(MeshSize)            :: Size
   type(Geometry)            :: Geom
   type(Quadrature)          :: QuadSet

!  Arguments

   integer,    intent(in)    :: nsig,ndir,npart

   real(adqt), intent(in)    :: sigt(npart,nsig),             & 
                                sigs(npart,nsig),             &
                                asc(npart,Size%ncornr,ndir),  &
                                sc(npart,Size%ncornr)

   real(adqt), intent(inout) :: psib(npart,Size%nbelem,ndir),  &
                                psic(npart,Size%ncornr,ndir),  &
                                phic(npart,Size%ncornr),angleLoopTime

   character(len=8), intent(in) :: itimsrc,iggsct,ipath,storePsi

!  Local

   integer    :: ic,iz,m,mm,thnum,bin,binSend1,   &
                 binRecv1,nextBin,NumBin,NangBin,n_cpuL

   integer    :: ndim,ncornr,nzones,nbelem,maxcf
   real(adqt) :: startOMPLoopTime, endOMPLoopTime, theOMPLoopTime

!  Function

   integer :: OMP_GET_THREAD_NUM, OMP_GET_MAX_THREADS

!  Dynamic

   real(adqt), allocatable :: omega(:,:)
   real(adqt), allocatable :: abdym(:,:)
   real(adqt), allocatable :: siginv(:,:)
   real(adqt), allocatable :: sigvol(:,:)
   real(adqt), allocatable :: sigarea(:,:)
   real(adqt), allocatable :: psimmh(:,:,:)
   real(adqt), allocatable :: tphic(:,:,:)
   real(adqt), allocatable :: tpsic(:,:,:)
   real(adqt), allocatable :: qc(:,:,:)
   real(adqt), allocatable :: psifp(:,:,:,:)
   real(adqt), allocatable :: source(:,:,:)
   
#ifdef PROFILING_ON
   integer profiler(2)  / 0, 0 /
   save profiler
   integer ompProfiler(2) / 0, 0/
   save ompProfiler

   call TAU_PROFILE_TIMER(profiler,'TAU_USER>SNFLWXYZ')
   call TAU_PROFILE_START(profiler)
#endif
!  Set number of threads

   n_cpuL = 1

#ifdef NO_OPENMP
   n_cpuL = 1
#else
   n_cpuL = OMP_GET_MAX_THREADS()
#endif

   require(n_cpuL>0,   "Invalid Thread Count")
   require(n_cpuL<=32, "Invalid Thread Count") 

!  Mesh Constants

   ndim   = Size%ndim
   ncornr = Size%ncornr
   nzones = Size%nzones
   nbelem = Size%nbelem
   maxcf  = Size%maxcf

!  Allocate space:

   allocate( omega(ndim,n_cpuL) )
   allocate( abdym(nbelem,n_cpuL) )
   allocate( siginv(npart,ncornr) )
   allocate( sigvol(npart,ncornr) )
   allocate( tphic(npart,ncornr,n_cpuL) )
   allocate( tpsic(npart,ncornr,n_cpuL) )
   allocate( qc(npart,ncornr,n_cpuL) )
   allocate( psifp(npart,maxcf,ncornr,n_cpuL) )
   allocate( source(npart,ncornr,n_cpuL) )

   if (ndim == 2) then
     allocate( psimmh(npart,ncornr,n_cpuL) )
     allocate( sigarea(npart,ncornr) )
   endif

!  Intialize arrays - We NEED to do this because the logic used to
!  create the corner ordering is different than logic used during
!  the sweeps.  For cases in which OMEGA (dot) Outward Normal is very close
!  to zero, one method can compute the dot product as slightly positive
!  while the second computes it as slightly negative.  This opens up
!  the possiblity of using unitialized values of PSIFP during
!  the sweep.  Give that the dot product is almost zero, it doesn't matter
!  what the value is as long as it is not a NANQ or a very large number.

   psifp(:,:,:,:) = zero

!  Set corner sigt*volume (SIGVOL)

   call setsig(Size, Geom, nsig,npart,  &
               sigt,SIGVOL,SIGINV,SIGAREA)

!  We use the current solution (PHIC) for calculating
!  the scattering source in SNQQ; we accumulate the new 
!  scalar flux in TPHIC in routine SNMOMENTS.

   TPHIC(:,:,:) = zero

!  Post receives for all data

   call InitExchange(Size, QuadSet)

!  Loop over angle bins
                                                                                         
   NumBin = QuadSet% NumBin
   theOMPLoopTime = 0.0

   AngleBin: do bin=1,NumBin
     nextBin = QuadSet% SendOrder(bin)
     NangBin = QuadSet% NangBinList(nextBin)

!  Loop over angles, solving for each in turn:
     startOMPLoopTime = MPI_WTIME()
#ifdef PROFILING_ON
     call TAU_PROFILE_TIMER(ompProfiler,'TAU_USER>SNFLWXYZ>AngleLoop')
     call TAU_PROFILE_START(ompProfiler)
#endif

#ifndef NO_OPENMP
!$OMP PARALLEL DO  PRIVATE(m,mm,thnum)
#endif
     AngleLoop: do mm=1,NangBin

       m     = QuadSet% AngleOrder(mm,bin)
#ifdef NO_OPENMP
       thnum = 1
#else
       thnum = OMP_GET_THREAD_NUM() + 1 
#endif
       omega(:,thnum) = QuadSet% omega(:,m)

!  If m is a "finishing" direction, we needn't do any transport
!  to calculate psic(m), for it is the psimmh calculated on the
!  last pass.

       AngleType: if (QuadSet% AngleType(m) == 1) then

         if (ipath == 'sweep') then
           psic(:,:,m) = psimmh(:,:,thnum)
         endif

       else

!  For other directions (starting and usual), we have to do
!  lots more work...

!  Set the total source for this angle by adding the within-group
!  scattering source
 
         call snqq(Size, Geom, QuadSet,                  &
                   npart,nsig,m,ndir,itimsrc,iggsct,     &
                   asc(1,1,m),sc,phic,siginv,sigs,QC(1,1,thnum))

!  Set angular fluxes for reflected angles

         call snreflect(Size, Geom, QuadSet, m, PSIB, ABDYM(1,thnum))

!  Fix cycles in the mesh for this angle

         source(:,:,thnum) = sigvol(:,:)*qc(:,:,thnum) 

         call fixcycles(Size, Geom, QuadSet, npart, m, storePsi, &
                        omega(1,thnum),sigvol,sigarea,           &
                        qc(1,1,thnum),psic(1,1,m),psib(1,1,m),   &
                        PSIFP(1,1,1,thnum),SOURCE(1,1,thnum))

!  Sweep the mesh, calculating PSIC for each corner; the boundary
!  flux array PSIB is also updated here.

         if (ndim == 3) then

           call snswp3d(Size, Geom, npart, storePsi,               &
                        QuadSet%next(1,m),omega(1,thnum),          &
                        abdym(1,thnum),sigvol,qc(1,1,thnum),       &
                        TPSIC(1,1,thnum),PSIC(1,1,m),PSIB(1,1,m),  &
                        PSIFP(1,1,1,thnum),SOURCE(1,1,thnum))

         elseif (ndim == 2) then

           call snswp2d(Size, Geom, QuadSet,                          &
                        npart,m,storePsi,QuadSet%next(1,m),           &
                        abdym(1,thnum),sigvol,sigarea,qc(1,1,thnum),  &
                        PSIMMH(1,1,thnum),TPSIC(1,1,thnum),           &
                        PSIC(1,1,m),PSIB(1,1,m),PSIFP(1,1,1,thnum),   &
                        SOURCE(1,1,thnum))

         endif

       endif AngleType

!  Add this angle's contribution to the flux moments

       call snmoments(QuadSet,ncornr,m,tpsic(1,1,thnum),TPHIC(1,1,thnum))

     enddo AngleLoop
#ifdef PROFILING_ON
     call TAU_PROFILE_STOP(ompProfiler)
#endif
     endOMPLoopTime = MPI_WTIME()

     theOMPLoopTime = theOMPLoopTime + (endOMPLoopTime-startOMPLoopTime)

     binSend1 = QuadSet% SendOrder(bin)
     binRecv1 = bin

!  Exchange Boundary Fluxes

     call exchange(Size, QuadSet, PSIB, binSend1, binRecv1) 

   enddo AngleBin

!  Accumulate thread scalar fluxes into the global array

   phic(:,:) = tphic(:,:,1)

   if (ipath =='sweep') then
     do thnum=2,n_cpuL
       phic(:,:) = phic(:,:) + tphic(:,:,thnum)
     enddo
   endif


!  Release space:

   deallocate( omega  )
   deallocate( abdym  )
   deallocate( siginv )
   deallocate( sigvol )
   deallocate( tphic  )
   deallocate( tpsic  )
   deallocate( qc     )
   deallocate( psifp  )
   deallocate( source  )

   if (ndim == 2) then
     deallocate( psimmh )
     deallocate( sigarea )
   endif
   angleLoopTime = angleLoopTime + theOMPLoopTime

#ifdef PROFILING_ON
   call TAU_PROFILE_STOP(profiler)
#endif
   return
   end subroutine snflwxyz


