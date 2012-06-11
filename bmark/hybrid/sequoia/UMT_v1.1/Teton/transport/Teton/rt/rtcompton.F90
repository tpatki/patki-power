!***********************************************************************
!                        Version 1:  11/98, PFN                        *
!                                                                      *
!   RTCOMPTON  - Performs the energy exchange between electrons and    *
!                photons due to Compton scattering.                    *
!                                                                      *
!   Input:   phinc - specified incident boundary intensities           *
!                                                                      *
!   Output:  DECOMPTON - energy change rate due to Compton             *
!                        scattering   (E/m/t)                          *
!                                                                      *
!***********************************************************************

   subroutine rtcompton(Size, Geom, Mat, phir)

   use kind_mod
   use constant_mod
   use radconstant_mod
   use Size_mod
   use Geometry_mod
   use Material_mod

   implicit none

!  Arguments - Types
                                                                                    
   type(MeshSize)            :: Size
   type(Geometry)            :: Geom 
   type(Material)            :: Mat

!  Arguments

   real(adqt), intent(in)    :: phir(Size%ngr,Size%ncornr) 

!  Local

   integer    :: ic,ig,iz,ncornr,ngr

   real(adqt) :: ac,trad,sumrad,sumSigsPhi,tr4min,tfloor

!  Constants:

   tfloor = Size%tfloor
   ac     = rad_constant*speed_light 
   tr4min = tfloor*tfloor*tfloor*tfloor
   ncornr = Size%ncornr
   ngr    = Size%ngr


   if (ngr == 1) then

     do ic=1,ncornr

       iz = Geom%CToZone(ic)

!  First compute a radiation temperature

       sumrad     = zero
       sumSigsPhi = zero

       do ig=1,ngr
         sumrad     = sumrad     + phir(ig,ic)
         sumSigsPhi = sumSigsPhi + phir(ig,ic)*Mat%sigs(ig,iz)
       enddo

       trad = sqrt( sqrt( max(sumrad/ac,tr4min) ) )

!       Mat%decompton(ic) = (Mat%tec(ic) - trad)*sumSigsPhi/  &
!                           ( pi*electronMass*Mat%rho(iz) ) 
       Mat%decompton(ic) = zero
          
     enddo

   else

     Mat%decompton(:) = zero

   endif



   return
   end subroutine rtcompton


