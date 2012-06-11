!***********************************************************************
!                        Version 0:  01/97, PFN                        *
!                                                                      *
!   RADTR  - Control program for radiation transport. It initializes   *
!            arrays, controls timestep, calls the transport package    *
!            and performs edits.                                       *
!                                                                      *
!                                                                      *
!***********************************************************************

   subroutine radtr(ncycle, angleLoopTime,            &
                    IterControls, DtControls, Size,   &
                    Geom, Mat, Quad, RadEdit, Prof,   &
                    PSIR, PHIR, RADSPECIFICENERGY)

!  Include
#include "assert.h"

   use kind_mod
   use iter_control_list_mod
   use Size_mod
   use Geometry_mod
   use Editor_mod
   use Material_mod
   use TimeStepControls_mod
   use ProfileList_mod
   use QuadratureList_mod
   use constant_mod
   use radconstant_mod

   implicit none

   include 'mpif.h'
!  Arguments

!  Types
                                                                                         
   type(IterControlList)     :: IterControls
   type(TimeStepControls)    :: DtControls
   type(MeshSize)            :: Size
   type(Geometry)            :: Geom
   type(Material)            :: Mat
   type(QuadratureList)      :: Quad
   type(Editor)              :: RadEdit
   type(ProfileList)         :: Prof

   integer,    intent(in)    :: ncycle

   real(adqt), intent(inout) :: psir(Size%ngr,Size%ncornr,Size%nangSN),  &
                                phir(Size%ngr,Size%ncornr),              &
                                RadSpecificEnergy(Size%nzones,Size%ngr),  &
                                angleLoopTime

!  Local

   integer    :: nprof
   real(adqt) :: dtrad, tau

!  Allocate Memory 

   real(adqt), allocatable :: phinc(:,:,:)

   nprof = Prof%NumProfiles
   allocate( phinc(Size%ngr,Size%nangSN,0:nprof) )

!***********************************************************************
!     ASSERTIONS                                                       *
!***********************************************************************

#ifdef ASSERT
!      call assert_mesh(Size, Geom)
#endif

!***********************************************************************
!     ADD TIME-ABSORPTION TO THE TOTAL CROSS SECTION ARRAY             *
!***********************************************************************

   dtrad = getRadTimeStep(DtControls)

   if (Size%ittyp == 'timedep') then
     tau = one/(speed_light*dtrad)
   else
     tau = zero
   endif

   Mat%sigt(:,:) = Mat%sigt(:,:) + tau

!***********************************************************************
!     GEOMETRY                                                         *
!***********************************************************************

   if (Size%ndim == 3) then
     call rtgeom3(Size, Geom)
   else if (Size%ndim == 2) then
     call rtgeom2(Size, Geom)
   else if (Size%ndim == 1) then
     call rtgeom1(Size, Geom)
   endif

!***********************************************************************
!     INITIALIZE CORNER VARIABLES ON FIRST CYCLE                       *
!***********************************************************************

!  Provide initial radiation distribution; use a Planckian
!  energy distribution at the radiation temperature distributed
!  isotropically.  Set corner variables equal to the user specified
!  zonal variables.

   if (ncycle == 1) then

     call rtinit(Size, Geom, Mat, RadEdit, Quad, PSIR, PHIR)

   endif

!***********************************************************************
!     INTERPOLATE SOURCE PROFILES                                      *
!***********************************************************************

   call profint(Prof, Size, DtControls, Quad)
 
!***********************************************************************
!     BOUNDARY CONDITIONS                                              *
!***********************************************************************
 
   call rtbdry(Size, Geom, Prof, PHINC)

!***********************************************************************
!     VOLUME RADIATION SOURCES                                         *
!***********************************************************************

   call rtvsrc(Size, Geom, Mat, Prof)

!***********************************************************************
!     SAVE ZONE AVERAGE TEMPERATURES FOR TIME STEP CALCULATION         *
!*********************************************************************** 

   call advanceRT(Size, Geom, Mat, Quad, PSIR, PHIR)

!***********************************************************************
!     RADIATION TRANSPORT MODULE                                       *
!***********************************************************************

   call rtmainsn(angleLoopTime, Size, Geom, Mat, IterControls, Quad,    &
                 RadEdit, nprof, dtrad, PSIR, PHIR, phinc)

!***********************************************************************
!     ENERGY UPDATE                                                    *
!***********************************************************************
         
   call newenergy(Size, Geom, Mat, PSIR, PHIR)

!***********************************************************************
!     EDITS                                                            *
!***********************************************************************

   call rtedit(Size, Geom, Mat, RadEdit, dtrad, phir)

!***********************************************************************
!     TIME STEP CONTROL                                                *
!***********************************************************************

   call dtnew(Size, Geom, Mat, DtControls, IterControls)

!***********************************************************************
!     UPDATE RADIATION MOMENTS                                         *
!***********************************************************************

   call RadMoments(Size, Geom, phir, RadSpecificEnergy)

!***********************************************************************
!     RELEASE MEMORY                                                   *
!***********************************************************************

   deallocate( phinc )


   return
   end subroutine radtr

