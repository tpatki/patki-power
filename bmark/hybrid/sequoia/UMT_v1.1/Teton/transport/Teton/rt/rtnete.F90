!***********************************************************************
!                        Version 1:  05/92, PFN                        *
!                                                                      *
!   RTNETE - calculates the net emission source (absorb. - emission)   *
!            used in the transport sweeps and in updating the electron *
!            temperature.                                              *
!                                                                      *
!   Input:   bc    - corner Planckian emission source          (E/A/t) *
!            phir  - corner or point scalar photon intensity   (E/A/t) *
!            siga  - absorption cross section                    (1/L) *
!                                                                      *
!   Output:  SNETC - corner net emission source (sum over groups)      *
!                                                              (E/V/t) *
!                                                                      *
!***********************************************************************
   subroutine rtnete(Size, Geom, Mat, SNETC) 

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

   real(adqt), intent(inout) :: snetc(Size%ncornr)

!  Local Variables

   integer :: ic,ig,iz
 
!  SNETC is used to accumulate differences
!  between absorption and emission
 
!******************************
!    Outer loop over corners  *
!******************************

   do ic=1,Size%ncornr

     snetc(ic) = Mat%AbsorptionRate(ic) 
     iz        = Geom%CToZone(ic)

     do ig=1,Size%ngr
       snetc(ic) = snetc(ic) - Mat%siga(ig,iz)*Mat%bc(ig,ic)
     enddo

   enddo


   return
   end subroutine rtnete


