!***********************************************************************
!                        Version 1:  05/95, PFN                        *
!                                                                      *
!   SNRZAMMH - This routine, called by SNFLWRZA, puts the "m+1/2"      *
!              angular flux into psimmh, for each corner.  On input,   *
!              psimmh contains the "m-1/2" angular flux and psic       * 
!              contains the "m" angular flux.                          *
!                                                                      *
!                                                                      *
!   Input:   psic     - angular flux                   (E/A/t/ster)    *
!            tau      - angular differencing parameter          (0)    *
!                                                                      *
!   Output:  PSIMMH   - 'half-angle' angular flux      (E/A/t/ster)    *
!                                                                      *
!***********************************************************************

   subroutine snrzammh(angletype,ncornr,npart,tau,psic,PSIMMH)

   use kind_mod
   use constant_mod

   implicit none

!  Arguments

   integer,    intent(in)    :: angletype,ncornr,npart

   real(adqt), intent(in)    :: tau
 
   real(adqt), intent(in)    :: psic(npart,ncornr)

   real(adqt), intent(inout) :: psimmh(npart,ncornr)
 
!  Local

   integer    :: ic

   real(adqt) :: tauin,omtin


   if (angletype == -1) then

!  Starting direction

     psimmh(:,:) = psic(:,:)

   else

!  Regular directions
 
     tauin = one/tau
     omtin = (one - tau)/tau
 
     do ic=1,ncornr
       psimmh(:,ic) = tauin*psic(:,ic) - omtin*psimmh(:,ic)
     enddo

   endif

 
   return
   end subroutine snrzammh

