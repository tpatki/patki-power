!***********************************************************************
!                        Version 1:  05/92, PFN                        *
!                                                                      *
!   getAbsorptionRate - Computes the total absorption rate.            *
!                                                                      *
!   Input:   snetc  - corner net emission source rate (group sum)      *
!                                                              (E/V/t) *
!                                                                      *
!   Local:   etchic - scratch array                                    *
!                                                                      *
!   Output:  SRCC   - scalar group-dependent source            (E/V/t) *
!                                                                      *
!***********************************************************************
   subroutine getAbsorptionRate(Size, Geom, Mat, phir) 

   use kind_mod
   use constant_mod
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

   integer    :: ic,ig,iz

   real(adqt) :: sumrad 

!  Calculate the total energy absorption rate density 

   do ic=1,Size%ncornr

     iz     = Geom%CToZone(ic)

     sumrad = zero

     do ig=1,Size%ngr
       sumrad = sumrad + Mat%siga(ig,iz)*phir(ig,ic)
     enddo

     Mat%AbsorptionRate(ic) = sumrad

   enddo

 
   return
   end subroutine getAbsorptionRate 

