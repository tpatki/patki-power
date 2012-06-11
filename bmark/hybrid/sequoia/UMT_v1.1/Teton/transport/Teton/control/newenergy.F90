!***********************************************************************
!                        Version 1:  03/02, PFN                        *
!                                                                      *
!   NEWENERGY - Updates the corner specific energies and converts      *
!               photon intensity to photon specific intensity.         *
!                                                                      *
!   Input:      denec,denic                                            *
!                                                                      *
!   Output:     ENEC,ENIC                                              *
!                                                                      *
!***********************************************************************
 
   subroutine newenergy(Size, Geom, Mat, PSIR, PHIR)

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

   real(adqt), intent(inout) :: psir(Size%ngr,Size%ncornr,Size%nangSN),  & 
                                phir(Size%ngr,Size%ncornr)

!  Local

   integer    :: ia, ic

   real(adqt) :: density, factor
 
!***********************************************************************
!     Update changes in zonal specific energy                          *
!***********************************************************************
 
   if (Size%imatc == 'elec') then

     call rtave(Size, Geom, Mat%denec, Mat%DENEZ)

   elseif (Size%imatc == 'elec+ion') then

     call rtave(Size, Geom, Mat%denec, Mat%DENEZ)
     call rtave(Size, Geom, Mat%denic, Mat%DENIZ)

   endif

!***********************************************************************
!     Convert intensity to specific intensity                          *
!***********************************************************************

   do ic=1,Size%ncornr
     density    = Mat%rho(Geom% CToZone(ic))
     factor     = one/(speed_light*density)
     phir(:,ic) = phir(:,ic)*factor

     do ia=1,Size%nangSN
       psir(:,ic,ia) = psir(:,ic,ia)*factor
     enddo
   enddo
 

   return
   end subroutine newenergy 


