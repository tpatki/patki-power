!***********************************************************************
!                        Version 1:  05/92, PFN                        *
!                                                                      *
!   RTSTARTDIR - starting direction calculation (mu = -1)              *
!                                                                      *
!   Input:   asrcc  - corner angle-group dependent source     (E/V/t)  *
!            volc   - corner volumes                          (V)      *
!            psib(ia,2)  - incoming intensity at outer problem         *
!                          boundary for all mu<0              (E/A/t)  *
!            psib(ia,1)  - incoming intensity at inner problem         *
!                          boundary for all mu>0              (E/A/t)  *
!            sigt   - total cross section                     (1/L)    *
!            rj2    - square of position of zone center       (A)      *
!            r2     - square of zone outer radius             (A)      *
!                                                                      *
!   Output:  PSIC   - corner angular photon intensity         (E/A/t)  *
!                                                                      *
!   Local:   a0,b0,a1 - geometry/material coefficients        (A)      *
!            den      - geometry/material coefficient         (1/L^4)  *
!            qc       - corner total volume source            (E/t)    *
!                                                                      *
!***********************************************************************

   subroutine rtstartdir(Size, Geom, Mat, QuadSet, mstdr,   &
                         asrcc, srcc, qc, scscat, sigvol,   &
                         PSIB, PSIC, PHIC)

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

   integer, intent(in)       :: mstdr

   real(adqt), intent(in)    :: asrcc(QuadSet%Groups,Size%ncornr,QuadSet%NumAngles), &
                                srcc(QuadSet%Groups,Size%ncornr)

   real(adqt), intent(inout) :: qc(QuadSet%Groups,Size%ncornr),                      &
                                scscat(QuadSet%Groups,Size%ncornr),                  &
                                sigvol(QuadSet%Groups,Size%ncornr)

   real(adqt), intent(inout) :: psib(QuadSet%Groups,Size%nbelem,QuadSet%NumAngles),  &
                                psic(QuadSet%Groups,Size%ncornr,QuadSet%NumAngles),  &
                                phic(QuadSet%Groups,Size%ncornr)

!  Local

   integer    :: ic,ip,iz,mrefl,ncornr,nzones,npart

   real(adqt) :: a0,a1,as,b0,bs,den,sedge

   real(adqt) :: photin(QuadSet%Groups)

!  Constants

   ncornr       = Size% ncornr
   nzones       = Size% nzones
   npart        = QuadSet% Groups

!  The index to the starting direction is "mstdr" (see RSWP1D)
 
!************************
!  STARTING DIRECTION   *
!************************
 
 
!  Compute total volume source (emission + scattering +
!  old time step) times the corner volume.  The scattering
!  source is multiplied by 0.5 to make it per unit cosine.

      if (Size%itimsrc == 'exact') then

        do ic=1,ncornr
          qc(:,ic) = Geom%volc(ic)*( srcc(:,ic) + asrcc(:,ic,mstdr) )
        enddo

      elseif (Size%itimsrc == 'off') then

        do ic=1,ncornr
          qc(:,ic) = Geom%volc(ic)*srcc(:,ic)
        enddo

      endif

      if (Size%iscat == 'on') then

        do ic=1,ncornr
          iz       = Geom%CToZone(ic)
          qc(:,ic) = qc(:,ic) + Size%wtiso*Geom%volc(ic)*Mat%sigs(:,iz)*phic(:,ic) 
        enddo

      endif

!  Coefficients of corner photon intensities (psic) for left
!  half-cell equation (a0, b0) and right half-cell equation (a1,-a0)
 
!  Perform sweep starting at outer boundary - incoming intensity
!  is specified in PSIB

      photin(:) = psib(:,2,mstdr)
 
      ZoneLoop: do iz=nzones,1,-1

        ic = 2*iz
        a0 = -half*Geom%rj2(iz)

        do ip=1,npart

          b0  = -a0 + sigvol(ip,ic-1)
          a1  =  a0 + sigvol(ip,ic) + Geom%r2(iz+1)
          den = -one/(a0*a0 + b0*a1)

          bs  = -a0*qc(ip,ic-1) - b0*qc(ip,ic)
          as  =  a0*qc(ip,ic)   - a1*qc(ip,ic-1)

          sedge               = Geom%r2(iz+1)*photin(ip)
          psic(ip,ic,mstdr)   = ( bs - b0*sedge )*den
          psic(ip,ic-1,mstdr) = ( as + a0*sedge )*den
          photin(ip)          = psic(ip,ic-1,mstdr)

        enddo

      enddo ZoneLoop

      psib(:,1,mstdr) = photin(:)
 

      return
      end subroutine rtstartdir

