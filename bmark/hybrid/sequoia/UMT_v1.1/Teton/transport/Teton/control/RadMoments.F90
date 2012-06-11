!***********************************************************************
!                        Version 1:  03/02, PFN                        *
!                                                                      *
!   RadMoments - Calculate the radiative flux and pressure tensor for  *
!                each group and each zone.  These quantities will be   *
!                remapped and will be used to construct new corner     *
!                intensties after remap.                               *
!                                                                      *
!   Input:       psir   - radiation specific energy density   (E/m)    *
!                                                                      *
!   Output:      RadFlux        - radiative flux                       *
!                PressureTensor - radiation pressure tensor            *
!                                                                      *
!***********************************************************************
 
   subroutine RadMoments(Size, Geom, phir, RadSpecificEnergy) 

   use kind_mod
   use constant_mod
   use Size_mod
   use Geometry_mod

   implicit none 

!  Arguments

   type(MeshSize)            :: Size
   type(Geometry)            :: Geom

   real(adqt), intent(in)    :: phir(Size%ngr,Size%ncornr) 

   real(adqt), intent(inout) :: RadSpecificEnergy(Size%nzones,Size%ngr)

!  Local

   integer    :: ic, ig, iz, ngr, ncornr

   real(adqt) :: VolFrac

!***********************************************************************
!  Update Radiation Specific Energy                                    *
!***********************************************************************
 
   ngr                    = Size%ngr
   ncornr                 = Size%ncornr
   RadSpecificEnergy(:,:) = zero

   do ic=1,ncornr

     iz      = Geom%CToZone(ic)
     VolFrac = Geom%volc(ic)/Geom%volz(iz)
       
     do ig=1,ngr

       RadSpecificEnergy(iz,ig) = RadSpecificEnergy(iz,ig) +  &
                                  VolFrac*phir(ig,ic)

     enddo

   enddo



   return
   end subroutine RadMoments 


