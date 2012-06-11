!***********************************************************************
!                        Version 1:  05/92, PFN                        *
!                                                                      *
!   RTSWPSC - Transport sweep for spheres and cylinders for all        *
!             directions except the starting direction (mu=-1).        *
!                                                                      *
!   Input:   asrcc       - corner angle-group dependent source (E/V/t) *
!                                                                      *
!   Output:  PSIC        - corner angular photon intensity     (E/A/t) *
!                                                                      *
!   Local:   a0,b0,a1    - geometry/material coefficients      (A)     *
!            den         - geometry/material coefficient       (1/L^4) *
!            qc          - corner total volume source          (E/t)   *
!                                                                      *
!***********************************************************************

   subroutine rtswpsc(Size, Geom, Mat, QuadSet, mstdr, nAngLevel,  &
                      asrcc, srcc, qc, scscat, sigvol, psimmh,     &
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

   integer, intent(in)       :: mstdr, nAngLevel

   real(adqt), intent(in)    :: asrcc(QuadSet%Groups,Size%ncornr,QuadSet%NumAngles), &
                                srcc(QuadSet%Groups,Size%ncornr)

   real(adqt), intent(inout) :: qc(QuadSet%Groups,Size%ncornr),                      &
                                scscat(QuadSet%Groups,Size%ncornr),                  &
                                sigvol(QuadSet%Groups,Size%ncornr),                  &
                                psimmh(QuadSet%Groups,Size%ncornr)

   real(adqt), intent(inout) :: psib(QuadSet%Groups,Size%nbelem,QuadSet%NumAngles),  &
                                psic(QuadSet%Groups,Size%ncornr,QuadSet%NumAngles),  &
                                phic(QuadSet%Groups,Size%ncornr)

!  Local

   integer    :: ia,ic,ip,iz,mrefl,ncornr,nzones,npart,nAngLevelNeg,mfirst,mlast

   real(adqt) :: a0,a1,as,b0,bs,den,sedge
   real(adqt) :: omega, falpha, adweta, tau

   real(adqt) :: photin(QuadSet%Groups)

!  Constants

   ncornr       = Size% ncornr
   nzones       = Size% nzones
   npart        = QuadSet% Groups
   nAngLevelNeg = nAngLevel/2

!  Compute source from angle (m-1/2), starting direction is special
!  The scattering source is multiplied by 0.5 to make it per unit 
!  cosine.

   do ic=1,ncornr
     psimmh(:,ic)  = psic(:,ic,mstdr)
     scscat(:,ic) = zero
   enddo

   if (Size%iscat == 'on') then

     do ic=1,ncornr
       iz           = Geom%CToZone(ic)
       scscat(:,ic) = Size%wtiso*Mat%sigs(:,iz)*phic(:,ic)
     enddo

   endif
 
!***************
!    mu < 0    *
!***************

   mfirst = mstdr + 1
   mlast  = mstdr + nAngLevelNeg 
 
   AngleLoop1: do ia=mfirst,mlast

!  Angular coefficients

     omega   = QuadSet% omega(1,ia)
     falpha  = QuadSet% falpha(ia)
     adweta  = QuadSet% adweta(ia)
     tau     = QuadSet% tau(ia)

!  Compute total volume source (emission + scattering + 
!  old time step + ang deriv) times the corner volume.
!  (Angular derivative source is from angle m-1/2)

     if (Size%itimsrc == 'exact') then

       do ic=1,ncornr
         qc(:,ic) = Geom%volc(ic)*( srcc(:,ic) + scscat(:,ic) + asrcc(:,ic,ia) ) +  & 
                    falpha*Geom%areac(ic)*psimmh(:,ic)
       enddo

     elseif (Size%itimsrc == 'off') then

       do ic=1,ncornr
         qc(:,ic) = Geom%volc(ic)*( srcc(:,ic) + scscat(:,ic) ) +  &
                    falpha*Geom%areac(ic)*psimmh(:,ic)
       enddo

     endif

!  Coefficients of photon intensities for left half-cell
!  equation (a0, b0) and right half-cell equation (a1, -a0)

!  Perform sweep starting at outer boundary
 
     photin(:) = psib(:,2,ia)
 
     ZoneLoop1: do iz=nzones,1,-1

       ic = 2*iz 
       a0 = half*omega*Geom%rj2(iz)

       do ip=1,npart

         b0  =  sigvol(ip,ic-1) + adweta*Geom%areac(ic-1) + &
                a0 - Geom%r2(iz)*omega
         a1  =  sigvol(ip,ic) + adweta*Geom%areac(ic) - a0
         den = -one/(a0*a0 + b0*a1)

         bs  = -a0*qc(ip,ic-1) - b0*qc(ip,ic)
         as  =  a0*qc(ip,ic)   - a1*qc(ip,ic-1)

         sedge            = omega*Geom%r2(iz+1)*photin(ip)
         psic(ip,ic,ia)   = ( bs + b0*sedge )*den
         psic(ip,ic-1,ia) = ( as - a0*sedge )*den
         photin(ip)       = psic(ip,ic-1,ia)

       enddo

     enddo ZoneLoop1

     psib(:,1,ia) = photin(:)

!  Do reflection if appropriate; if the boundary condition is
!  not reflecting, PSIB has already been set.

     if (Geom%BdyToBC(1) == 'refl') then
       mrefl           = nAngLevel - ia - mstdr + 1
       psib(:,1,mrefl) = photin(:)
     endif
 
!  Compute (m+1/2) quantities
 
     do ic=1,ncornr
       psimmh(:,ic) = tau*psic(:,ic,ia) + (one - tau)*psimmh(:,ic) 
     enddo
 
   enddo AngleLoop1
 
!***************
!    mu > 0    *
!***************

   mfirst = mstdr + nAngLevelNeg + 1
   mlast  = mstdr + nAngLevel 

   AngleLoop2: do ia=mfirst,mlast

!  Angular coefficients

     omega   = QuadSet% omega(1,ia)
     falpha  = QuadSet% falpha(ia)
     adweta  = QuadSet% adweta(ia)
     tau     = QuadSet% tau(ia)

!  Compute total volume source (emission + scattering + 
!  old time step + ang deriv) times the corner volume.
!  (Angular derivative source is from angle m-1/2)

     if (Size%itimsrc == 'exact') then

        do ic=1,ncornr
          qc(:,ic) = Geom%volc(ic)*( srcc(:,ic) + scscat(:,ic) + asrcc(:,ic,ia) ) + & 
                     falpha*Geom%areac(ic)*psimmh(:,ic)
        enddo

     elseif (Size%itimsrc == 'off') then

        do ic=1,ncornr
          qc(:,ic) = Geom%volc(ic)*( srcc(:,ic) + scscat(:,ic) ) + &
                     falpha*Geom%areac(ic)*psimmh(:,ic)
        enddo

     endif

!  Coefficients of photon intensities for left half-cell
!  equation (a0, b0) and right half-cell equation (a1, -a0)

!  Perform sweep starting at inner reflecting boundary

     photin(:) = psib(:,1,ia)
 
     do iz=1,nzones

       ic = 2*iz
       a0 = half*omega*Geom%rj2(iz)

       do ip=1,npart

         b0  =  sigvol(ip,ic-1) + adweta*Geom%areac(ic-1) + a0
         a1  =  sigvol(ip,ic)   + adweta*Geom%areac(ic) +  &
                Geom%r2(iz+1)*omega - a0
         den = -one/(a0*a0 + b0*a1)

         bs  = -a0*qc(ip,ic-1) - b0*qc(ip,ic)
         as  =  a0*qc(ip,ic)   - a1*qc(ip,ic-1)

         sedge            = omega*Geom%r2(iz)*photin(ip)
         psic(ip,ic,ia)   = ( bs - a0*sedge )*den
         psic(ip,ic-1,ia) = ( as - a1*sedge )*den
         photin(ip)       = psic(ip,ic,ia)

       enddo

     enddo

     psib(:,2,ia) = photin(:)
 
!  Compute (m+1/2) quantities
 
     do ic=1,ncornr
       psimmh(:,ic) = tau*psic(:,ic,ia) + (one - tau)*psimmh(:,ic) 
     enddo
 
   enddo AngleLoop2
 

   return
   end subroutine rtswpsc

