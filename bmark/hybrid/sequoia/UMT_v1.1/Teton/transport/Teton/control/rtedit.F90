!***********************************************************************
!                        Version 1:  05/92, PFN                        *
!                                                                      *
!   RTEDIT  - Computes zone average temperatures and energies at the   *
!             conclusion of the radiation cycle as an edit.            *
!                                                                      *
!   Input:   phir  - corner scalar photon intensity      (E/A/t)       *
!            tec   - corner electron temperatures        (T)           *
!            tic   - corner ion temperatures             (T)           *
!            denec - corner electron energy change       (E/m)         *
!            denic - corner ion energy change            (E/m)         *
!            volc  - corner volumes                      (V)           *
!                                                                      *
!   Output:  TRZ   - zone average radiation temperature  (T)           *
!            TEZ   - zone average electron temperature   (T)           *
!            TIZ   - zone average ion temperature        (T)           *
!            ENEZ  - zone average electron energy        (E/m)         *
!            ENIZ  - zone average ion energy             (E/m)         *
!                                                                      *
!***********************************************************************
   subroutine rtedit(Size, Geom, Mat, RadEdit, dtrad, phir) 


   use kind_mod
   use mpi_param_mod
   use mpif90_mod
   use constant_mod
   use radconstant_mod
   use Size_mod
   use Geometry_mod
   use Material_mod
   use Editor_mod

   implicit none

!  Arguments - Types

   type(MeshSize)            :: Size
   type(Geometry)            :: Geom
   type(Material)            :: Mat
   type(Editor)              :: RadEdit

!  Arguments

   real(adqt), intent(in)    :: dtrad

   real(adqt), intent(in)    :: phir(Size%ngr,Size%ncornr)

!  Local

   integer, dimension (1) :: iztrmx
   integer, dimension (1) :: iztemx

   integer    :: ib,ic,ig,iz,ncornr,nzones,ngr,nbtot
   integer    :: nodeTr, nodeTe

   real(adqt) :: gfac,tr,trn,tr4min,tr4new,tr4old,  &
                 deelec,deion,density,mass,tfloor

   real(adqt) :: my_trmax,my_temax,trmax,temax
   real(adqt) :: derad,demat,desrc,deradinc,deradesc,decheck
   real(adqt) :: erad,emat,eextsrc,eradinc,eradesc,echeck

!  Dynamic arrays

   real(adqt),  allocatable :: sphotc(:)
   real(adqt),  allocatable :: photav(:)

!  Allocate Temporary Storage

   ncornr = Size%ncornr
   nzones = Size%nzones
   ngr    = Size%ngr

   allocate( sphotc(ncornr) )
   allocate( photav(nzones) )

!  Geometry factor for true 3D volume

   gfac   = one
   tfloor = Size%tfloor

   if (Size%igeom == 'rz') then
     gfac = two*pi
   endif
 
!  Sum photon energy densities over groups
!  At this point, "phir" has units of energy/mass

   sphotc(:) = zero
 
   do ic=1,ncornr
     iz      = Geom%CToZone(ic)
     density = Mat%rho(iz)
     do ig=1,ngr
       sphotc(ic) = sphotc(ic) + density*phir(ig,ic)
     enddo
   enddo

!  Find zone-average grey-energy density and radiation temperature
 
   call rtave(Size, Geom, sphotc, PHOTAV)

   tr4min = tfloor*tfloor*tfloor*tfloor
 
   do iz=1,nzones
     Mat%trz(iz) = sqrt(sqrt(max(photav(iz)/rad_constant,tr4min)))
   enddo
 
!  Find zone-average material temperatures and
!  Add corner energy changes to zone energy

   call rtave(Size, Geom, Mat%tec, Mat%TEZ)

!  Find total radiation energy and the radiation converted
!  to matter energy

   derad  = zero
   deelec = zero
   deion  = zero
   desrc  = zero

   do iz=1,nzones
     tr     = Mat%trz(iz)
     trn    = Mat%trzn(iz)
     tr4new = tr*tr*tr*tr
     tr4old = trn*trn*trn*trn 
     mass   = Mat%rho(iz)*Geom%volz(iz)

     deelec = deelec + gfac*mass*Mat%denez(iz)
     derad  = derad  + gfac*rad_constant*Geom%volz(iz)*(tr4new - tr4old)
     desrc  = desrc  + gfac*dtrad*mass*Mat%selec(iz)
   enddo

!  Find incident/escaping energy on problem boundaries

   deradinc = zero
   deradesc = zero
                                                                                          
   nbtot = Size% nbedit + 1
                                                                                          
   do ib=1,nbtot
     do ig=1,Size%ngr
       RadEdit%RadEnergyIncident(ib,ig) =   &
       RadEdit%RadEnergyIncident(ib,ig) + dtrad*RadEdit%RadEnergyIncRate(ib,ig)
       RadEdit%RadEnergyEscaped(ib,ig)  =   &
       RadEdit%RadEnergyEscaped(ib,ig)  + dtrad*RadEdit%RadEnergyEscRate(ib,ig)
     enddo
   enddo
 
   do ig=1,Size%ngr
     deradinc = deradinc + dtrad*RadEdit%RadEnergyIncRate(nbtot,ig)
     deradesc = deradesc + dtrad*RadEdit%RadEnergyEscRate(nbtot,ig)
   enddo

   if (Size%imatc == 'elec+ion') then

     call rtave(Size, Geom, Mat%tic, Mat%TIZ)

     do iz=1,nzones
       deion = deion + gfac*Mat%rho(iz)*Geom%volz(iz)*Mat%deniz(iz)
       desrc = desrc + gfac*dtrad*Mat%rho(iz)*Geom%volz(iz)*Mat%sion(iz)
     enddo

   endif

   demat = deelec + deion

!  Maximum temperatures

   iztrmx    = maxloc( Mat%trz(:) )
   trmax     = Mat%trz(iztrmx(1))
   my_trmax  = trmax

   iztemx   = maxloc( Mat%tez(:) )
   temax    = Mat%tez(iztemx(1))
   my_temax = temax

   call MPIAllReduceT(TRMAX,    "max", MPI_COMM_WORLD)
   call MPIAllReduceT(TEMAX,    "max", MPI_COMM_WORLD)
   call MPIAllReduceT(DERAD,    "sum", MPI_COMM_WORLD)
   call MPIAllReduceT(DEMAT,    "sum", MPI_COMM_WORLD)
   call MPIAllReduceT(DESRC,    "sum", MPI_COMM_WORLD)
   call MPIAllReduceT(DERADINC, "sum", MPI_COMM_WORLD)
   call MPIAllReduceT(DERADESC, "sum", MPI_COMM_WORLD)

   if (my_trmax == trmax) then
     nodeTr = Size%my_node
   else
     nodeTr = -1
     iztrmx = -1
   endif

   if (my_temax == temax) then
     nodeTe = Size%my_node
   else
     nodeTe = -1
     iztemx = -1
   endif
                                                                                       
   call MPIAllReduceT(nodeTr, "max", MPI_COMM_WORLD)
   call MPIAllReduceT(nodeTe, "max", MPI_COMM_WORLD)
   call MPIAllReduceT(iztrmx, "max", MPI_COMM_WORLD)
   call MPIAllReduceT(iztemx, "max", MPI_COMM_WORLD)

   decheck = deradinc + desrc - deradesc - derad - demat

!  Update Edit module

   erad    = getEnergyRadiation(RadEdit)  + derad
   emat    = getEnergyMaterial(RadEdit)   + demat
   eradinc = getEnergyIncident(RadEdit)   + deradinc
   eradesc = getEnergyEscaped(RadEdit)    + deradesc
   eextsrc = getEnergyExtSources(RadEdit) + desrc
   echeck  = getEnergyCheck(RadEdit)      + decheck

   call setEdits(RadEdit,                  &
                 TrMaxZone=iztrmx,         & 
                 TeMaxZone=iztemx,         &
                 TrMaxNode=nodeTr,         &
                 TeMaxNode=nodeTe,         &
                 TrMax=trmax,              &
                 TeMax=temax,              &
                 EnergyRadiation=erad,     &
                 EnergyMaterial=emat,      &
                 EnergyIncident=eradinc,   &
                 EnergyEscaped=eradesc,    &
                 EnergyExtSources=eextsrc, &
                 EnergyCheck=echeck,       &
                 DeltaEnergyRad=derad,     &
                 DeltaEnergyMat=demat,     &
                 DeltaEnergyInc=deradinc,  &
                 DeltaEnergyEsc=deradesc,  &
                 DeltaEnergyExtSrc=desrc,  &
                 DeltaEnergyCheck=decheck)


!  Release Temporary Storage

   deallocate( sphotc )
   deallocate( photav )

 
   return
   end subroutine rtedit

