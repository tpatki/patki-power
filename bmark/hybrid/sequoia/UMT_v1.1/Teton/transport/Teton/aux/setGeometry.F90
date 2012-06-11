!***********************************************************************
!                        Version 1:  02/06, PFN                        *
!                                                                      *
!   setGeometry - This routine sets mesh connectivity in the geometry  *
!                 module.                                              *
!                                                                      *
!***********************************************************************

   subroutine setGeometry(Size, Geom,                             &
                          nodeComm,CbdyComm,                      &
                          Connect,CToZone,CToPoint,CToFace,nfpc,  &
                          BdyToC,BdyToSrc,BdyToEdit,BdyToBC,      &
                          ZoneToSrc,px) 

!  Include

   use kind_mod
   use Size_mod
   use Geometry_mod

   implicit none

!  Arguments

   type(MeshSize)            :: Size
   type(Geometry)            :: Geom

   integer,    intent(in)    :: nodeComm(2,Size%ncomm),             &
                                CbdyComm(Size%nbshare)

   integer,    intent(in)    :: Connect(4,Size%maxcf,Size%ncornr),  &
                                BdyToC(2,Size%nbelem),              &
                                BdyToSrc(Size%nbelem),              &
                                BdyToEdit(Size%nbelem),             &
                                CToZone(Size%ncornr),               &
                                CToPoint(Size%ncornr),              &
                                CToFace(Size%maxcf,Size%ncornr),    &
                                nfpc(Size%ncornr)

   integer,    intent(in)    :: ZoneToSrc(Size%nzones)

   real(adqt), target, intent(in) :: px(Size%ndim,Size%npnts)

   character(len=8), intent(in) :: BdyToBC(Size%nbelem)

!  Local 

   integer :: i,ic,iz,nzones,ncornr
   integer :: nerr_ez,nerr_fp,nerr_b,ic2,id2

!  Temporary Arrays 

   integer, allocatable :: ncorner_in_zone(:)

!  Allocate Memory

   nzones = Size% nzones
   ncornr = Size% ncornr

   allocate( ncorner_in_zone(nzones) )

!  Set the corner-based connectivity

   Geom% Connect(:,:,:) = Connect(:,:,:)
   Geom% BdyToC(:,:)    = BdyToC(:,:)
   Geom% BdyToSrc(:)    = BdyToSrc(:)
   Geom% BdyToEdit(:)   = BdyToEdit(:)
   Geom% BdyToBC(:)     = BdyToBC(:)
   Geom% CToZone(:)     = CToZone(:)
   Geom% CToPoint(:)    = CToPoint(:)
   Geom% nfpc(:)        = nfpc(:)

   Geom% ZoneToSrc(:)   = ZoneToSrc(:)

   Geom%px => px

   if (Size%ndim == 3) then
     Geom% CToFace(:,:) = CToFace(:,:) 
   endif

   if (Size%decomp_s == 'on') then
     Geom% CbdyComm(:)   = CbdyComm(:)
     Geom% nodecomm(:,:) = nodecomm(:,:)
   endif


!  Create CList

   ncorner_in_zone(:) = 0
                                                                                          
   do ic=1,ncornr
     iz                  = CToZone(ic)
     ncorner_in_zone(iz) = ncorner_in_zone(iz) + 1
   enddo

   Geom% CList(1) = 0
 
   do iz=1,nzones
     Geom% CList(iz+1) = Geom% CList(iz) + ncorner_in_zone(iz)
   enddo

!  Check for consistency in Connect

   nerr_ez = 0
   nerr_fp = 0
   nerr_b  = 0

   do ic=1,ncornr
     do i=1,nfpc(ic)
       ic2 = Geom% Connect(3,i,ic)
       id2 = Geom% Connect(4,i,ic)

       if (Geom% Connect(3,id2,ic2) /= ic .or.  &
           Geom% Connect(4,id2,ic2) /= i) then
         nerr_ez = nerr_ez + 1
       endif

       ic2 = Geom% Connect(1,i,ic)
       id2 = Geom% Connect(2,i,ic)

       if (ic2 == 0) then
         if (Geom% BdyToC(1,id2) /= ic .or.  &
             Geom% BdyToC(2,id2) /= i) then
           nerr_b = nerr_b + 1
         endif
       else

         if (Geom% Connect(1,id2,ic2) /= ic .or.  &
             Geom% Connect(2,id2,ic2) /= i ) then
           nerr_fp = nerr_fp + 1
         endif

       endif

     enddo
   enddo

   if (nerr_ez > 0 .or. nerr_b > 0 .or. nerr_fp > 0) then
     call f90fatal("Error creating Connect in setGeometry")
   endif

!  Release temporary arrays

   deallocate( ncorner_in_zone )


   return
   end subroutine setGeometry 


