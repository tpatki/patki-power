!***********************************************************************
!                        Version 1:  05/92, PFN                        *
!                                                                      *
!   RTMATC - Calculates electron/ion coupling terms and sources that   *
!            are only calculated once per radiation cycle.             *
!                                                                      *
!   Input:   tec     - corner electron temp. from previous cycle   (T) *
!            tic     - corner ion temperature from previous cycle  (T) *
!            xomei   - electron-ion recombination rate       (E/m/T/t) *
!            cvi     - ion specific heat                       (E/m/T) *
!            cve     - electron specific heat                  (E/m/T) *
!            sion    - ion specific energy source rate         (E/m/t) *
!            selec   - electron specific energy source rate    (E/m/t) *
!            CToZone - corner-to-zone connectivity                     *
!            dtrad   - current time step                           (t) *
!                                                                      *
!   Output:  EMATC - specific energy rate from matter sources  (E/m/t) *
!            XEICP - dimensionless electron/ion coefficient        (0) *
!                                                                      *
!***********************************************************************
   subroutine rtmatc(Size, Geom, Mat, dtrad) 

   use kind_mod
   use Size_mod
   use Geometry_mod
   use Material_mod

   implicit none

!  Arguments - Types
                                                                                    
   type(MeshSize)            :: Size
   type(Geometry)            :: Geom 
   type(Material)            :: Mat

!  Arguments

   real(adqt), intent(in)    :: dtrad

!  Local Variables

   integer :: ic,iz,ncornr,nzones

!  Mesh Constants

   ncornr = Size%ncornr
   nzones = Size%nzones 

!  Calculate the electron/ion coupling coefficient and the
!  energy deposition rate from external sources
 
   if (Size%imatc == 'elec+ion') then
 
     do iz=1,nzones
       Mat%xeicp(iz)  = dtrad*Mat%xomei(iz)*Mat%cvi(iz)/   &
                       (Mat%cve(iz)*(Mat%cvi(iz) + dtrad*Mat%xomei(iz)))
     enddo
 
     do ic=1,ncornr
       iz            = Geom%CToZone(ic)
       Mat%ematc(ic) = Mat%selec(iz) + Mat%cve(iz)*Mat%xeicp(iz)*   &
                    ( (Mat%tic(ic) - Mat%tec(ic))/dtrad +           &
                       Mat%sion(iz)/Mat%cvi(iz) )
     enddo
 
   elseif (Size%imatc == 'elec') then
 
     do ic=1,ncornr
       iz            = Geom%CToZone(ic)
       Mat%ematc(ic) = Mat%selec(iz)
     enddo
 
   endif
 

   return
   end subroutine rtmatc


