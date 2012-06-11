!***********************************************************************
!                        Version 1:  05/92, PFN                        *
!                                                                      *
!   RTMAINSN - Control program for SN radiation transport in 1D,       *
!              2D and 3D geometries.                                   *
!                                                                      *
!   Input:                                                             *
!                                                                      *
!   TYPES                                                              *
!          IterControls  - list of iteration controls                  *
!                                                                      *
!   INTEGER                                                            *
!                                                                      *
!   REAL*8                                                             *
!            dtrad       - time step (t)                               *
!                                                                      *
!   INTEGER Arrays                                                     *
!            nangr       - total angles by group (w/ starting dir)     *
!                          dim:  (ngr)                                 *
!            CToZone     - zone number for a corner                    *
!                          dim:  (ncornr)                              *
!            CToFace     - face numbers for a corner                   *
!                          dim:  (maxcf,ncornr)                        *
!            Connect     - (1,:,:) = corner across FP face             *
!                          (2,:,:) = local corner-face index of above  *
!                          (3,:,:) = corner across EZ face             *
!                          (4,:,:) = local corner-face index of above  *
!                          dim:  (4,maxcf,ncornr)                      *
!            BdyToC      - corner for a boundary element               *
!                          dim:  (2,nbelem)                            *
!            BdyToSrc    - profile number for a boundary element       *
!                          dim:  (nbelem)                              *
!            BdyToEdit   - edit number for a boundary element          *
!                          dim:  (nbelem)                              *
!                                                                      *
!   REAL*8 Arrays                                                      *
!            px          - point coordinates                           *
!                          dim:  (ndim,npnts), units:  (L)             *
!            phinc       - boundary radiation source                   *
!                          dim:  (nphinc,nangt), units:  (E/A/t)       *
!            sion        - external ion source                         *
!                          dim:  (nzones), units:  (E/m/t)             *
!            selec       - external electron source                    *
!                          dim:  (nzones), units:  (E/m/t)             *
!            qext        - external radiation source                   *
!                          dim:  (nzones,ngr), units:  (E/A/t)         *
!            siga        - absorption cross section                    *
!                          dim:  (nzones,ngr), units:  (1/L)           *
!            sigs        - scattering cross section                    *
!                          dim:  (nzones,ngr), units:  (1/L)           *
!            sigt        - total cross section                         *
!                          dim:  (nzones,ngr), units:  (1/L)           *
!            cve         - electron specific heat                      *
!                          dim:  (nzones), units:  (E/m/T)             *
!            cvi         - ion specific heat                           *
!                          dim:  (nzones), units:  (E/m/T)             *
!            xomei       - electron/ion coupling coefficient           *
!                          dim:  (nzones), units:  (E/m/T/t)           *
!            rho         - material density                            *
!                          dim:  (nzones), units:  (m/V)               *
!            gnu         - photon frequency group boundaries           *
!                          dim:  (ngr+1), units:  (e)                  *
!                                                                      *
!   CHARACTER*8 Arrays                                                 *
!            BdyToBC     - boundary condition flag                     *
!                          dim:  (nbelem)                              *
!                                                                      *
!   Output:                                                            *
!                                                                      *
!   TYPES                                                              *
!         IterControls   - update the number of temperature,           *
!                          intensity, scattering and acceleration      *
!                          iterations this cycle                       * 
!   REAL*8 Arrays                                                      *
!            PSIR        - corner angular photon intensity             *
!                          dim:  (npsi,ncornr), units:  (E/A/t/ster)   *
!            PHIR        - corner scalar intensity moments             *
!                          dim:  (nmomtr,ncornr), units:  (E/A/t)      *
!            TEC         - corner electron temperature                 *
!                          dim:  (ncornr), units:  (T)                 *
!            TIC         - corner ion temperature                      *
!                          dim:  (ncornr), units:  (T)                 *
!            DENEC       - corner electron energy change this cycle    *
!                          dim:  (ncornr), units:  (E/m)               *
!            DENIC       - corner ion energy change change this cycle  *
!                          dim:  (ncornr), units:  (E/m)               *
!            CURESC      - radiation energy escape rate                *
!                          dim:  (nbedit+1,ngr), units:  (E/A/t)       *
!            CURINC      - radiation energy incident rate              *
!                          dim:  (nbedit+1,ngr), units:  (E/A/t)       *
!            VOLC        - corner volume                               *
!                          dim:  (ncornr), units:  (V)                 *
!            VOLZ        - zone volume                                 *
!                          dim:  (nzones), units:  (V)                 *
!                                                                      *
!                                                                      *
!   Units:   E/e/T/m/L/A/V/t -                                         *
!        energy/photon energy/temperature/mass/length/area/volume/time *
!***********************************************************************

   subroutine rtmainsn(angleLoopTime, Size, Geom, Mat, IterControls, Quad,  &
                       RadEdit, nprof, dtrad, PSIR, PHIR, phinc)

   use kind_mod
   use iter_control_list_mod
   use iter_control_mod
   use Size_mod
   use Geometry_mod
   use Editor_mod
   use Material_mod
   use QuadratureList_mod
   use Quadrature_mod
   use constant_mod
   use radconstant_mod

   implicit none


!  Arguments

   type(IterControlList)     :: IterControls
   type(MeshSize)            :: Size
   type(Geometry)            :: Geom
   type(QuadratureList)      :: Quad
   type(Material)            :: Mat
   type(Editor)              :: RadEdit

   integer,    intent(in)    :: nprof

   real(adqt), intent(in)    :: dtrad

   real(adqt), intent(in)    :: phinc(Size%ngr,Size%nangSN,0:nprof)

   real(adqt), intent(inout) :: psir(Size%ngr,Size%ncornr,Size%nangSN), &
                                phir(Size%ngr,Size%ncornr),             &
                                angleLoopTime
!  Local

   type(IterControl), pointer :: temperatureControl,  &
                                 intensityControl,    &
                                 scatteringControl

   type(Quadrature), pointer  :: QuadSet

   integer    :: nzones, NumSnSets

   integer    :: noutrt, ninrt, intensityIter, izero
   integer    :: ndim, ncornr, nbelem, ngr, nangSN
   integer    :: i, ibatch, NumQuadSets, NumBin

   real(adqt) :: tau,erphmx,errtmp

   character(len=8) :: timeSrc

!  Dynamic Arrays
 
!  Source Variables
 
   real(adqt), allocatable :: snetc(:)
   real(adqt), allocatable :: asrcc(:,:,:)
   real(adqt), allocatable :: srcc(:,:)
 
!  Photon Intensities on the problem boundary

   real(adqt), allocatable :: psib(:,:,:)

!  Miscellaneous
 
   real(adqt), allocatable :: photzo(:)
 
!  Constants:

   parameter (izero=0)

!  Set some scalars used for dimensioning

   ndim     = Size%ndim
   ncornr   = Size%ncornr
   nzones   = Size%nzones
   nbelem   = Size%nbelem
   ngr      = Size%ngr
   nangSN   = Size%nangSN

   timeSrc  = Size%itimsrc

   NumSnSets = getNumSnSets(Quad)

!  Iteration Controls

   temperatureControl => getIterationControl(IterControls,"temperature")
   intensityControl   => getIterationControl(IterControls,"intensity")
   scatteringControl  => getIterationControl(IterControls,"scattering")

!  Initialize counters for this time step

   call setNumberOfIterations(temperatureControl,izero)
   call setNumberOfIterations(intensityControl,izero)
   call setNumberOfIterations(scatteringControl,izero)

!***********************************************************************
!                                                                      *
!     ALLOCATE MEMORY                                                  *
!                                                                      *
!***********************************************************************
 
!  Source variables
 
   allocate( snetc(ncornr) )
   allocate( srcc(ngr,ncornr) )

   if (timeSrc == 'exact') then
     allocate( asrcc(ngr,ncornr,nangSN) )
   endif
 
!  Photon Intensities on the problem boundary

   allocate( psib(ngr,nbelem,nangSN) )

!  Miscellaneous
 
   allocate( photzo(nzones) )

!***********************************************************************
!     PRELIMINARIES                                                    *
!***********************************************************************
 
!  Update time absorption cross section
 
   if (Size%ittyp == 'timedep') then
     tau = one/(speed_light*dtrad)
   else
     tau = zero
   endif

!***********************************************************************
!     SWEEP ORDER                                                      *
!***********************************************************************
 
   if (ndim >= 2) then

!  Find sets of reflecting boundary sides with the same outward normals

     call snbsets(Size, Geom)  

!  Calculate ordering for grid sweeps

     call rtorder(Size, Geom, Quad) 

   endif

!***********************************************************************
!     INITIALIZE COMMUNICATION                                         *
!***********************************************************************

!  Create an incident and exiting list for shared boundary elements

   call findexit(Size, Geom, Quad)

!***********************************************************************
!     SAVE PREVIOUS CYCLE INFORMATION AND BEGIN MATERIAL COUPLING      *
!***********************************************************************
 
!  Save various quantities from previous time step and calculate
!  the time-dependent source

   call rtstrtsn(Size, Geom, Mat,            &
                 nprof,tau,psir,phir,phinc,  &
                 ASRCC,PHOTZO,PSIB)

!  Energy Change due to Compton scattering

   call rtcompton(Size, Geom, Mat, phir) 

!  Calculate electron/ion coupling coefficient (XEICP) and
!  specific energy rate from direct matter sources (EMATC).
!  At this point, TEC and TIC are from the previous time step.
 
   call rtmatc(Size, Geom, Mat, dtrad) 
 
!***********************************************************************
!     EXCHANGE BOUNDARY FLUXES                                         *
!***********************************************************************

!  Establish angle order for transport sweeps

   call SweepScheduler(Size, Geom, Quad)

   QuadSet => getQuadrature(Quad, 1)

   call InitExchange(Size, QuadSet)

   call exchange(Size, QuadSet, PSIB, izero, izero) 

!  Initialize Absorption Rate

   call getAbsorptionRate(Size, Geom, Mat, phir) 

   call UpdateTemperature(Size, Geom, Mat, Quad, dtrad)

!***********************************************************************
!     BEGIN IMPLICIT ELECTRON/RADIATION COUPLING ITERATION (OUTER)     *
!***********************************************************************
 
   noutrt = 0
   ninrt  = 0
 
   TemperatureIteration: do
 
     noutrt = noutrt + 1

!***********************************************************************
!     BEGIN PHOTON INTENSITY ITERATION (INNER)                         *
!***********************************************************************

     intensityIter = 0
 
     IntensityIteration: do
 
       intensityIter = intensityIter + 1
 
!  Calculate net emission source
 
       call rtnete(Size, Geom, Mat, SNETC) 

!***********************************************************************
!     BEGIN LOOP OVER BATCHES                                          *
!***********************************************************************
 
       BatchLoop: do ibatch=1,NumSnSets

         QuadSet => getQuadrature(Quad, ibatch)

!  Compute scalar source (SSRC) for this group
 
         call rtgsrc(Size, Geom, Mat, QuadSet, dtrad, snetc, SRCC)

!  Sweep all angles in all groups in this "batch"
 
         if (ndim == 1) then

           call rswp1d(Size, Geom, Mat, QuadSet, IterControls,   &
                       asrcc, srcc, PSIB, PSIR, PHIR) 

         else

           call rswpmd(angleLoopTime, Size, Geom, Mat, QuadSet,  &
                       asrcc, srcc, PSIB, PSIR, PHIR)

         endif

       enddo BatchLoop
 
!***********************************************************************
!     END FREQUENCY GROUP LOOP                                         *
!***********************************************************************

!  Update Absorption Rate

       Mat%AbsorptionRateOld(:) = Mat%AbsorptionRate(:)

       call getAbsorptionRate(Size, Geom, Mat, phir)

!***********************************************************************
!     EXCHANGE BOUNDARY FLUXES                                         *
!***********************************************************************

       QuadSet => getQuadrature(Quad, 1)

       call InitExchange(Size, QuadSet)

       call exchange(Size, QuadSet, PSIB, izero, izero) 

!***********************************************************************
!     CHECK CONVERGENCE OF SCALAR INTENSITIES                          *
!***********************************************************************

       call rtconi(Size, Geom, IterControls, ERPHMX, PHOTZO, phir)
 
       if (erphmx < getEpsilonPoint(intensityControl) .or. &
           intensityIter >= getMaxNumberOfIterations(intensityControl)) then
         exit IntensityIteration
       else
         cycle IntensityIteration
       endif
 
     enddo IntensityIteration

     ninrt = ninrt + intensityIter
 
!***********************************************************************
!     END PHOTON INTENSITY ITERATION (INNER)                           *
!***********************************************************************
 
!  Calculate new electron temperature and energy change
 
     call UpdateTemperature(Size, Geom, Mat, Quad, dtrad)

!  Check convergence of electron temperature
 
     call rtconv(Size, Geom, Mat, IterControls, ERRTMP) 

     if ((errtmp <  getEpsilonPoint(temperatureControl) .and.  &
          erphmx <  getEpsilonPoint(intensityControl))  .or.   &
          noutrt >= getMaxNumberOfIterations(temperatureControl)) then

       exit TemperatureIteration

     else

       cycle TemperatureIteration

     endif
 
   enddo TemperatureIteration

!  Update Iteration Counts

   call setNumberOfIterations(temperatureControl,noutrt)
   call setNumberOfIterations(intensityControl,ninrt)
 
!***********************************************************************
!     END IMPLICIT ELECTRON/RADIATION COUPLING ITERATION (OUTER)       *
!***********************************************************************
 
!  Calculate new ion temperature and energy change
 
   call rtti(Size, Geom, Mat) 

!***********************************************************************
!     NEGATIVE FLUX FIXUP                                              *
!***********************************************************************

!   call FluxFixUp(Size, Geom, Quad, psir, phir)

!***********************************************************************
!     BOUNDARY EDITS                                                   *
!***********************************************************************

   call bdyedt(Size, Geom, Quad, RadEdit, psib)

!***********************************************************************
!     RELEASE MEMORY                                                   *
!***********************************************************************
 
!  Source variables
 
   deallocate( snetc )
   deallocate( srcc )

   if (Size%ittyp == 'timedep') then
     deallocate( asrcc )
   endif

!  Photon Intensities on thr problem boundary

   deallocate( psib )
 
!  Miscellaneous
 
   deallocate( photzo )

!  Structures for communicating boundary fluxes and sweeps

   NumQuadSets = getNumQuadSets(Quad)
   do i=1,NumQuadSets
     QuadSet => getQuadrature(Quad, i)
     call destructComm(QuadSet, Size)
   enddo

 

   return
   end subroutine rtmainsn



