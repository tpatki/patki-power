!***********************************************************************
!                        Version 1:  05/92, PFN                        *
!                                                                      *
!   RTAVE - Calculates the volume-weighted average of a corner         *
!           variable.                                                  *
!                                                                      *
!   Input:  xc   - corner variable                                     *
!           volc - corner volumes         (V)                          *
!           volz - zone volume            (V)                          *
!                                                                      *
!   Output: AVE  - zone-average value of the corner variable           *
!                                                                      *
!***********************************************************************
 
   subroutine rtave(Size, Geom, xc, AVE)

   use kind_mod
   use constant_mod
   use Size_mod
   use Geometry_mod

   implicit none

!  Arguments - Types
                                                                                      
   type(MeshSize)            :: Size
   type(Geometry)            :: Geom

!  Arguments

   real(adqt), intent(in)    :: xc(Size%ncornr)

   real(adqt), intent(inout) :: ave(Size%nzones)

!  Local

   integer    :: ic,iz

   real(adqt) :: tempc

!  Compute zone-average value from corner values
 
   ave(:) = zero
 
   do ic=1,Size%ncornr
     iz      = Geom% CToZone(ic)
     tempc   = Geom% volc(ic)*xc(ic)/Geom% volz(iz)
     ave(iz) = ave(iz) + tempc
   enddo

 
   return
   end subroutine rtave

