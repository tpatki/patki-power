!***********************************************************************
!                        Version 1:  05/92, PFN                        *
!                                                                      *
!   RTVSRC - Calculates the radiation intensity for zonal sources.     *
!            Allowed sources are temperature or frequency dependent.   *
!            Volume source profile identifiers are in the integer      *
!            array ZoneToSrc.  For FDS, the frequency-dependent        *
!            intensity is specified by the user and is assumed to be   *
!            isotropic.  For a TEMP source, the temperature is         *
!            specified and the intensity is a Planckian in frequency   *
!            space and is isotropic.  Unlike sources on boundaries     *
!            which specify an incoming flux, volume sources dictate    *
!            the radiation intensity in a defined region of the        *
!            problem. The solution in the remainder of the spatial     *
!            domain is determined by the physics of the problem.       *
!                                                                      *
!   Input:   pintv     - interpolated profile intensities     (E/A/t)  *
!            ZoneToSrc - volume (zonal) source profile identifiers     *
!                                                                      *
!   Output:  QEXT      - external radiation source            (E/V/t)  *
!            SIGT      - total cross section                   (1/cm)  *
!                                                                      *
!***********************************************************************

   subroutine rtvsrc(Size, Geom, Mat, Prof) 

   use kind_mod
   use constant_mod
   use Size_mod
   use Geometry_mod
   use Material_mod
   use ProfileList_mod
   use Profile_mod

   implicit none

!  Arguments

   type(MeshSize)            :: Size
   type(Geometry)            :: Geom
   type(Material)            :: Mat
   type(ProfileList)         :: Prof

!  Local

   type(Profile), pointer    :: ProfID

   integer    :: ic,ip,ig,iz,ngr,nzones,ncornr 

   real(adqt) :: bignum

   character(len=8) :: Status, Type, Location

!  Constants

   parameter (bignum=1.0d20)

   ngr    = Size% ngr
   nzones = Size% nzones
   ncornr = Size% ncornr


!  Set QEXT for volume sources; note that the angular distribution
!  is isotropic for frequency-dependent and temperature sources.

!  Initialize QEXT (some sources may have been turned off since
!  the last cycle.)

   Mat%qext(:,:) = zero

!  We need to check each profile to see if it is
!  on (set to zero if off).

!********************************
!  Temperature or FDS 'sources' *
!********************************

   ProfileLoop: do ip=1,Prof%NumProfiles

     ProfID => getProfile(Prof, ip)

     Status   = ProfID% Status
     Location = ProfID% Location
     Type     = ProfID% Type

     CheckStatus: if (Status == 'on' .and. Location == 'region') then

       if (Type == 'temp' .or. Type == 'fds') then

         do iz=1,nzones
           if (Geom%ZoneToSrc(iz) == ip) then
             do ig=1,ngr
               Mat%qext(ig,iz) = ProfID% InterpValues(ig)
             enddo
           endif
         enddo

!********************************
!  Temperature or FDS 'drives'  *
!********************************

       elseif (Type == 'tempdriv' .or. Type == 'fdsdriv') then 

         do iz=1,nzones
           if (Geom%ZoneToSrc(iz) == ip) then
             do ig=1,ngr
               Mat%sigt(ig,iz) = bignum
               Mat%qext(ig,iz) = bignum*ProfID% InterpValues(ig)
             enddo
           endif
         enddo

!********************************
!  Energy Sources               *
!********************************

       elseif (Type == 'energy') then

         do ic=1,ncornr
           iz = Geom%CToZone(ic)
           if (Geom%ZoneToSrc(iz) == ip) then
             Mat%selec(ic) = Mat%selec(ic) + ProfID% InterpValues(1) 
           endif
         enddo

       endif


     endif CheckStatus

   enddo ProfileLoop


   return
   end subroutine rtvsrc

