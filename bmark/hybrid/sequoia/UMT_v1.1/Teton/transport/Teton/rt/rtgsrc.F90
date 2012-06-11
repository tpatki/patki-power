!***********************************************************************
!                        Version 1:  05/92, PFN                        *
!                                                                      *
!   RTGSRC - Calculates the group dependent emission source (for one   *
!            group) for transport sweeps.                              *
!                                                                      *
!   Input:   snetc  - corner net emission source rate (group sum)      *
!                                                              (E/V/t) *
!            bc     - corner Planckian emission source         (E/A/t) *
!            qext   - external source to radiation             (E/V/t) *
!            chic   - corner spectral shape function               (0) *
!            etac   - corner grey weighting factor                 (0) *
!            ematc  - specific energy rate from matter sources (E/m/t) *
!            xeicp  - electron/ion coefficient                     (0) *
!            siga   - absorption cross section                   (1/L) *
!            rho    - density                                    (m/V) *
!            CToZone- corner-to-zone mapping                           *
!            dtrad  - time step                                    (t) *
!                                                                      *
!   Local:   etchic - scratch array                                    *
!                                                                      *
!   Output:  SRCC   - scalar group-dependent source            (E/V/t) *
!                                                                      *
!***********************************************************************
   subroutine rtgsrc(Size, Geom, Mat, QuadSet, dtrad, snetc, SRCC)

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

   real(adqt), intent(in)    :: dtrad
 
   real(adqt), intent(in)    :: snetc(Size%ncornr) 

   real(adqt), intent(inout) :: srcc(QuadSet%Groups,Size%ncornr)

!  Local

   integer    :: ic,ip,iz

   real(adqt) :: srcmat, wtiso

!  Calculate the group-dependent scalar source (SRCC)

   wtiso = Size% wtiso

!  Total source = emission + external + matter coupling
 
   if (Size%imatc == 'elec+ion') then
 
     do ic=1,Size%ncornr

       iz     = Geom%CToZone(ic)

       srcmat = Mat%etac(ic)*(snetc(ic) +                    &
                Mat%rho(iz)*( Mat%ematc(ic) - Mat%decompton(ic) -    &
                (one + Mat%xeicp(iz))*(Mat%denec(ic)/dtrad) ) )/ &
                (one + (one - Mat%etac(ic))*Mat%xeicp(iz))

       srcc(:,ic) = wtiso*( Mat%siga(:,iz)*Mat%bc(:,ic) + Mat%qext(:,iz) + & 
                    Mat%rho(iz)*Mat%decompton(ic) + Mat%chic(:,ic)*srcmat )

     enddo
 
   elseif (Size%imatc == 'elec') then

     do ic=1,Size%ncornr

       iz     = Geom%CToZone(ic)

       srcmat = Mat%etac(ic)*( snetc(ic) + Mat%rho(iz)*   &
                ( Mat%ematc(ic) - Mat%decompton(ic) - (Mat%denec(ic)/dtrad) ) )

       srcc(:,ic) = wtiso*( Mat%siga(:,iz)*Mat%bc(:,ic) + Mat%qext(:,iz) +  & 
                    Mat%rho(iz)*Mat%decompton(ic) + Mat%chic(:,ic)*srcmat )

     enddo

   endif

 
   return
   end subroutine rtgsrc

