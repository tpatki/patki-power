!***********************************************************************
!                        Version 1:  05/92, PFN                        *
!                                                                      *
!   RTTI   - Calculates the change in ion energy; Ions are not         *
!            directly coupled to radiation so the ion energy is only   *
!            updated after the electron/radiation iteration is         *
!            converged.                                                *
!                                                                      *
!   Input:   tec    - corner electron temperature                  (T) *
!            ticn   - corner ion temp from previous time step      (T) *
!            sion   - external ion sources                     (E/m/t) *
!            cvi    - ion specific heat                        (E/m/T) *
!            cve    - electron specific heat                   (E/m/T) *
!            xeicp  - dimensionless electron-ion coefficient       (0) *
!            xomei  - electron-ion coefficient               (E/m/T/t) *
!            CToZone- zone number for a given corner                   *
!            imatc  - material coupling flag                           *
!            tfloor - temperature floor                            (T) *
!                                                                      *
!   Output:  DENIC  - corner ion specific energy change          (E/m) *
!            TIC    - corner ion temperature                       (T) *
!                                                                      *
!***********************************************************************
   subroutine rtti(Size, Geom, Mat) 

   use kind_mod
   use Size_mod
   use Geometry_mod
   use Material_mod

   implicit none

!  Arguments - Types
                                                                                    
   type(MeshSize)            :: Size
   type(Geometry)            :: Geom 
   type(Material)            :: Mat

!  Local

   integer    :: ic,iz 

   real(adqt) :: ticn

!  If no ions, just return

   if (Size%imatc == 'elec+ion') then
 
!  Find change in ion energies and update corner ion temperatures
 
     do ic=1,Size%ncornr

       iz = Geom%CToZone(ic)

!  Copy old ion temperature to TICN

       ticn          = Mat%tic(ic)
 
       Mat%denic(ic) = Mat%xeicp(iz)*Mat%cve(iz)*     &
                     ( Mat%tec(ic) - ticn + Mat%sion(iz)/Mat%xomei(iz) )
 
       Mat%tic(ic)   = max(ticn + Mat%denic(ic)/Mat%cvi(iz),Size%tfloor)

     enddo
 
   endif

 
   return
   end subroutine rtti

