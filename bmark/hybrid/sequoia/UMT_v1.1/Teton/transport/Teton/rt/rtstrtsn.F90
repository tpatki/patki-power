!***********************************************************************
!                        Version 1:  05/92, PFN                        *
!                                                                      *
!   RTSTRTSN - Computes an angle-dependent source using the previous   *
!              time step angular intensity and saves copies of the     *
!              corner temperatures.                                    *
!                                                                      *
!   Input:   psir,tec                                                  *
!                                                                      *
!   Output:  ASRCC,TEZOLD,TECN                                         *
!                                                                      *
!***********************************************************************
 
   subroutine rtstrtsn(Size, Geom, Mat,            &
                       nphinc,tau,psir,phir,phinc, &
                       ASRCC,PHOTZO,PSIB)

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

   integer,    intent(in)    :: nphinc 

   real(adqt), intent(in)    :: tau

   real(adqt), intent(in)    :: psir(Size%ngr,Size%ncornr,Size%nangSN),  &
                                phir(Size%ngr,Size%ncornr),              &
                                phinc(Size%ngr,Size%nangSN,0:nphinc)
                                                                                       
   real(adqt), intent(inout) :: asrcc(Size%ngr,Size%ncornr,Size%nangSN), &
                                psib(Size%ngr,Size%nbelem,Size%nangSN),  &
                                photzo(Size%nzones)

!  Local Variables

   integer :: ic,ig,ncornr,nzones,ngr

!  Dynamic Arrays

   real*8,  allocatable :: solc(:)

!  Mesh Constants

   ncornr = Size%ncornr
   nzones = Size%nzones
   ngr    = Size%ngr

!  Allocate temporary arrays

   allocate( solc(ncornr) )

!  If this is a time-dependent problem compute the angle-dependent
!  source using the old time-step intensity

   if (Size%itimsrc == 'exact') then
     asrcc(:,:,:) = tau*psir(:,:,:)
   else
     asrcc(:,:,:) = zero
   endif

!  Initialize arrays

   do ic=1,ncornr
     Mat%tecn(ic)  = Mat%tec(ic)
     Mat%denec(ic) = zero
     solc(ic)      = zero
   enddo

!  Initialize the boundary flux array (PSIB)

   call setbdy(Size, Geom, nphinc, phinc, psir, PSIB)

!  Calculate zone-average grey radiation intensity for convergence test

   do ic=1,ncornr
     do ig=1,ngr
       solc(ic) = solc(ic) + phir(ig,ic)
     enddo
   enddo
 

   call rtave(Size, Geom, solc, PHOTZO)

!  Compute zone-average temperature for convergence test

   call rtave(Size, Geom, Mat%tec, Mat%TEZOLD)

!  Release temporary arrays

   deallocate( solc )
 

   return
   end subroutine rtstrtsn
 
