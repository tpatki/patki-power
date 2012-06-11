!***********************************************************************
!                        Version 1:  05/92, PFN                        *
!                                                                      *
!   ADVANCERT - Save zone-average quantities from previous cycle for   *
!               delta-t calculation.  Convert specific radiation       *
!               intensity (i.e. per unit mass) to intensity (per       *
!               unit volume) before the transport calculation.         *
!                                                                      *
!   Input:   tez,trz                                                   *
!                                                                      *
!   Output:  TEZN,TRZN                                                 *
!                                                                      *
!***********************************************************************
 
   subroutine advanceRT(Size, Geom, Mat, Quad, PSIR, PHIR) 


   use kind_mod
   use constant_mod
   use radconstant_mod
   use Size_mod
   use Geometry_mod
   use Material_mod
   use QuadratureList_mod
   use Quadrature_mod

   implicit none

!  Arguments - Types
                                                                                    
   type(MeshSize)            :: Size
   type(Geometry)            :: Geom
   type(Material)            :: Mat
   type(QuadratureList)      :: Quad

!  Arguments

   real(adqt), intent(inout) :: psir(Size%ngr,Size%ncornr,Size%nangSN), &
                                phir(Size%ngr,Size%ncornr)

!  Local

   type(Quadrature), pointer :: QuadSet 

   integer    :: ia, ic, ig, iz
   integer    :: ncornr, nzones, ngr, numAngles

   real(adqt) :: ac, tfloor, tr4min, density, ratio 
   real(adqt) :: quadwt(Size%nangSN)

!  Dynamic arrays

   real(adqt), allocatable :: Tstar(:)
   real(adqt), allocatable :: sphotc(:)
   real(adqt), allocatable :: photav(:)

!  Constants

   ncornr = Size%ncornr
   nzones = Size%nzones
   ngr    = Size%ngr

   tfloor = Size%tfloor


   allocate( Tstar(nzones) )
   allocate( sphotc(ncornr) )
   allocate( photav(nzones) )

   QuadSet => getQuadrature(Quad,1)
   numAngles = QuadSet%NumAngles

   quadwt(1:numAngles) = QuadSet%Weight(1:numAngles)

!***********************************************************************
!  Make corner temperatures consistent with zone averages obtained     *
!  from the host code.                                                 *
!***********************************************************************

   call rtave(Size, Geom, Mat%tec, Tstar)

   ZoneLoop: do iz=1,nzones

     Mat%tez(iz) = max( Mat%tez(iz), tfloor )
     Mat%trz(iz) = max( Mat%trz(iz), tfloor ) 
     ratio       = Mat%tez(iz)/Tstar(iz)

     do ic=Geom%CList(iz)+1,Geom%CList(iz+1)
       Mat%tec(ic) = max( ratio*Mat%tec(ic), tfloor )
     enddo

   enddo ZoneLoop

   if (Size%imatc == 'elec+ion') then

     call rtave(Size, Geom, Mat%tic, Tstar)

     ZoneLoop1: do iz=1,nzones
                           
       Mat%tiz(iz) = max( Mat%tiz(iz), tfloor )
       ratio       = Mat%tiz(iz)/Tstar(iz)

       do ic=Geom%CList(iz)+1,Geom%CList(iz+1)
         Mat%tic(ic) = max( ratio*Mat%tic(ic), tfloor )
       enddo
                             
     enddo ZoneLoop1

   endif

!***********************************************************************
!  Advance zone temperatures [set old = new]                           *
!***********************************************************************
 
   Mat%tezn(:) = Mat%tez(:)

!***********************************************************************
!  Convert specific energy density to intensity                        *
!***********************************************************************

   do ic=1,ncornr
     density  = Mat%rho(Geom%CToZone(ic))
     do ia=1,numAngles
       psir(:,ic,ia) = psir(:,ic,ia)*speed_light*density
     enddo
   enddo

   call rtscal(ngr,ncornr,numAngles,quadwt,psir,PHIR)

   sphotc(:) = zero

   do ic=1,ncornr
     do ig=1,ngr
       sphotc(ic) = sphotc(ic) + phir(ig,ic)
     enddo
   enddo

   call rtave(Size, Geom, sphotc, PHOTAV)

   tr4min = tfloor*tfloor*tfloor*tfloor
   ac     = rad_constant*speed_light

   do iz=1,nzones
     Mat%trzn(iz) = sqrt( sqrt( max(photav(iz)/ac, tr4min) ) )
   enddo
 
!  Release temporary array

   deallocate( Tstar )
   deallocate( sphotc )
   deallocate( photav )


   return
   end subroutine advanceRT



