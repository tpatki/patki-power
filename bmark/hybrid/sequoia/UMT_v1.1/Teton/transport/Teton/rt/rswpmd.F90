!***********************************************************************
!                        Version 1:  05/92, PFN                        *
!                                                                      *
!   RSWPMD - Controls transport sweeps for 2D and 3D grids             *
!                                                                      *
!   Input:                                                             *
!                                                                      *
!   Output:  PSIR  - corner angular photon intensity      (E/A/t/ster) *
!            PHIR  - corner scalar photon intensity       (E/A/t)      *
!            PSIB  - angular photon intensity on boundary              *
!                    elements                             (E/A/t/ster) *
!                                                                      *
!***********************************************************************
   subroutine rswpmd(angleLoopTime, Size, Geom, Mat, QuadSet,  &
                     asrcc, srcc, PSIB, PSIR, PHIR)
 
   use kind_mod
   use constant_mod
   use Size_mod
   use Geometry_mod
   use Material_mod
   use Quadrature_mod

   implicit none

!  Arguments - Types
                                                                                    
   type(MeshSize)            :: Size
   type(Geometry)            :: Geom
   type(Material)            :: Mat
   type(Quadrature)          :: QuadSet

!  Arguments

   real(adqt), intent(in)    :: asrcc(QuadSet%Groups,Size%ncornr,QuadSet%NumAngles), & 
                                srcc(QuadSet%Groups,Size%ncornr)

   real(adqt), intent(inout) :: psib(QuadSet%Groups,Size%nbelem,QuadSet%NumAngles),  &
                                psir(QuadSet%Groups,Size%ncornr,QuadSet%NumAngles),  &
                                phir(QuadSet%Groups,Size%ncornr),angleLoopTime

!  Local

   integer          :: nsig,ncornr,nzones,npart,nangles

   character(len=8) :: ipath, storePsi

!  Constants

   parameter (ipath='sweep')
   parameter (storePsi='yes')

   ncornr = Size%ncornr
   nzones = Size%nzones

!  For Sn sweeps we use zonal opacities
 
   nsig    = nzones
   npart   = QuadSet% Groups
   nangles = QuadSet% NumAngles

!  Follow particles through the mesh:

   call snflwxyz(angleLoopTime, Size, Geom, QuadSet,      &
                 npart,nsig,nangles,                      &
                 Size%itimsrc,Size%iscat,ipath,storePsi,  &
                 Mat%sigt,Mat%sigs,asrcc,srcc,PSIB,PSIR,PHIR)



   return
   end subroutine rswpmd

