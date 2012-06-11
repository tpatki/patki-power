!***********************************************************************
!                        Version 1:  05/92, PFN                        *
!                                                                      *
!   RTSWPSLB - Transport sweep for all directions in slab geometry.    *
!                                                                      *
!   Input:   asrcc       - corner angle-group dependent source (E/V/t) *
!            volc        - corner volumes                      (V)     *
!            areac       - corner areas                        (A)     *
!            psib(ia,2)  - incoming intensity at outer problem         *
!                          boundary for all mu<0               (E/A/t) *
!            psib(ia,1)  - incoming intensity at inner problem         *
!                          boundary for all mu>0               (E/A/t) *
!            sigt        - total cross section                 (1/L)   *
!            omega       - direction cosine mu                         *
!                                                                      *
!   Output:  PSIC        - corner angular photon intensity     (E/A/t) *
!                                                                      *
!   Local:   a0,b0,a1    - geometry/material coefficients      (A)     *
!            den         - geometry/material coefficient       (1/L^4) *
!            qc          - corner total volume source          (E/t)   *
!                                                                      *
!***********************************************************************

   subroutine rtswpslb(Size, Geom, Mat, QuadSet,         &
                       asrcc, srcc, qc, scscat, sigvol,  &
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

   real(adqt), intent(in)    :: asrcc(QuadSet%Groups,Size%ncornr,QuadSet%NumAngles), &
                                srcc(QuadSet%Groups,Size%ncornr)

   real(adqt), intent(inout) :: qc(QuadSet%Groups,Size%ncornr),                      &
                                scscat(QuadSet%Groups,Size%ncornr),                  &
                                sigvol(QuadSet%Groups,Size%ncornr) 

   real(adqt), intent(inout) :: psib(QuadSet%Groups,Size%nbelem,QuadSet%NumAngles),  &
                                psic(QuadSet%Groups,Size%ncornr,QuadSet%NumAngles),  &
                                phic(QuadSet%Groups,Size%ncornr)

!  Local

   integer    :: ia,ic,ip,iz,mrefl,ncornr,npart,NumAngles,NumAnglesNeg

   real(adqt) :: a0,a1,as,b0,bs,den,sedge

   real(adqt) :: photin(QuadSet%Groups), omega

!  Constants

   ncornr       = Size% ncornr
   npart        = QuadSet% Groups
   NumAngles    = QuadSet% NumAngles
   NumAnglesNeg = NumAngles/2

!  The scattering source is multiplied by 0.5 to make
!  it per unit cosine.

   if (Size%iscat == 'on') then

     do ic=1,ncornr
       iz           = Geom%CToZone(ic)
       scscat(:,ic) = Size%wtiso*Mat%sigs(:,iz)*phic(:,ic)
     enddo

   else

     do ic=1,ncornr
       iz           = Geom%CToZone(ic)
       scscat(:,ic) = zero 
     enddo

   endif
 
!***************
!    mu < 0    *
!***************
 
   AngleLoop1: do ia=1,NumAnglesNeg

     omega = QuadSet% Omega(1,ia)
 
!  Compute total volume source (emission + scattering +
!  old time step) times the corner volume.

     if (Size%itimsrc == 'exact') then

       do ic=1,ncornr
         qc(:,ic) = Geom%volc(ic)*( srcc(:,ic) + scscat(:,ic) + asrcc(:,ic,ia) ) 
       enddo

     elseif (Size%itimsrc == 'off') then

       do ic=1,ncornr
         qc(:,ic) = Geom%volc(ic)*( srcc(:,ic) + scscat(:,ic) )
       enddo

     endif

!  Calculate the attenuation coefficients for left half-cell
!  equation (a0, b0) and right half-cell equation (a1, -a0)
 
 
!  Perform sweep starting at outer boundary
 
     photin(:) = psib(:,2,ia)
 
     CornerLoop1: do ic=ncornr,2,-2

       a0 = half*omega

       do ip=1,npart

         b0  =  sigvol(ip,ic-1) - a0
         a1  =  sigvol(ip,ic)   - a0
         den = -one/(a0*a0 + b0*a1)

         bs  = -a0*qc(ip,ic-1) - b0*qc(ip,ic)
         as  =  a0*qc(ip,ic)   - a1*qc(ip,ic-1)

         sedge            = omega*photin(ip)
         psic(ip,ic,ia)   = ( bs + b0*sedge )*den
         psic(ip,ic-1,ia) = ( as - a0*sedge )*den
         photin(ip)       = psic(ip,ic-1,ia)

       enddo

     enddo CornerLoop1
 
     psib(:,1,ia) = photin(:)

!  Do reflection if appropriate; if the boundary condition is
!  not reflecting, PSIB has already been set.

     if (Geom%BdyToBC(1) == 'refl') then
       mrefl           = NumAngles - ia + 1
       psib(:,1,mrefl) = photin(:)
     endif
 
   enddo AngleLoop1
 
!***************
!    mu > 0    *
!***************
 
   AngleLoop2: do ia=NumAnglesNeg+1,NumAngles

     omega = QuadSet% omega(1,ia)
 
!  Compute total volume source (emission + old time step)

     if (Size%itimsrc == 'exact') then

       do ic=1,ncornr
         qc(:,ic) = Geom%volc(ic)*( srcc(:,ic) + scscat(:,ic) + asrcc(:,ic,ia) ) 
       enddo

     elseif (Size%itimsrc == 'off') then

       do ic=1,ncornr
         qc(:,ic) = Geom%volc(ic)*( srcc(:,ic) + scscat(:,ic) )
       enddo

     endif

!  Calculate the attenuation coefficients for left half-cell
!  equation (a0, b0) and right half-cell equation (a1, -a0)
 
 
!  Perform sweep starting at inner boundary

     photin(:) = psib(:,1,ia)
 
     CornerLoop2: do ic=2,ncornr,2

       a0 = half*omega

       do ip=1,npart

         b0  =  sigvol(ip,ic-1) + a0
         a1  =  sigvol(ip,ic)   + a0
         den = -one/(a0*a0 + b0*a1)

         bs  = -a0*qc(ip,ic-1) - b0*qc(ip,ic)
         as  =  a0*qc(ip,ic)   - a1*qc(ip,ic-1)
 
         sedge            = omega*photin(ip)
         psic(ip,ic,ia)   = ( bs - a0*sedge )*den
         psic(ip,ic-1,ia) = ( as - a1*sedge )*den
         photin(ip)       = psic(ip,ic,ia)

       enddo

     enddo CornerLoop2

     psib(:,2,ia) = photin(:)
 
   enddo AngleLoop2

 
   return
   end subroutine rtswpslb

