!***********************************************************************
!                        Version 1:  12/94, PFN                        *
!                                                                      *
!   SETBDY - Sets boundary fluxes PSIB to specified incident boundary  *
!            fluxes.                                                   *
!                                                                      *
!   Input:   phinc - specified incident boundary intensities   (E/A/t) *
!                                                                      *
!   Output:  PSIB  - boundary intensities                      (E/A/t) *
!                                                                      *
!***********************************************************************

   subroutine setbdy(Size, Geom, nphinc, phinc, psir, PSIB) 

   use kind_mod
   use constant_mod
   use Size_mod
   use Geometry_mod

   implicit none

!  Arguments - Types
                                                                                    
   type(MeshSize)            :: Size
   type(Geometry)            :: Geom 

!  Arguments

   integer,    intent(in)    :: nphinc

   real(adqt), intent(in)    :: phinc(Size%ngr,Size%nangSN,0:nphinc), &
                                psir(Size%ngr,Size%ncornr,Size%nangSN)

   real(adqt), intent(inout) :: psib(Size%ngr,Size%nbelem,Size%nangSN)

!  Local

   integer :: ia,ib,ic,iprof,nbelem,nangSN,ngr

!  Constants

   nbelem = Size%nbelem
   nangSN = Size%nangSN
   ngr    = Size%ngr

!  Initialize the boundary flux array (PSIB)

   if (Size%itimsrc == 'off') then

     do ib=1,nbelem

       iprof = Geom%BdyToSrc(ib)
 
       do ia=1,nangSN
         psib(:,ib,ia) = phinc(:,ia,iprof)
       enddo

     enddo

   else

     do ib=1,nbelem

       iprof = Geom%BdyToSrc(ib)

       if ( (Geom%BdyToBC(ib) == 'refl') .or.     & 
            (Geom%BdyToBC(ib) == 'white') .or.    &
            (Geom%BdyToBC(ib) == 'shared') ) then

         ic  = Geom%BdyToC(1,ib)

         do ia=1,nangSN
           psib(:,ib,ia) = psir(:,ic,ia)
         enddo

       else

         do ia=1,nangSN
           psib(:,ib,ia) = phinc(:,ia,iprof)
         enddo

       endif
 
     enddo


   endif


   return
   end subroutine setbdy

