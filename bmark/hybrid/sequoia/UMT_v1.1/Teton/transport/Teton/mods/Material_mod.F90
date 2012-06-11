! Material Module:  material properties 
                                                                                 
module Material_mod
                                                                                 
  use kind_mod

  private

! public interfaces
                                                                                             
  public construct, destruct
                                                                                 
  type, public :: Material

     real(adqt), pointer :: siga(:,:)            ! siga(ngr,nzones) 
     real(adqt), pointer :: sigs(:,:)            ! sigs(ngr,nzones)
     real(adqt), pointer :: sigt(:,:)            ! sigt(ngr,nzones)
     real(adqt), pointer :: cve(:)               ! cve(nzones) 
     real(adqt), pointer :: rho(:)               ! rho(nzones)
     real(adqt), pointer :: selec(:)             ! selec(nzones)
     real(adqt), pointer :: qext(:,:)            ! qext(ngr,nzones)
     real(adqt), pointer :: denez(:)             ! denez(nzones)
     real(adqt), pointer :: trz(:)               ! trz(nzones)
     real(adqt), pointer :: tez(:)               ! tez(nzones)
     real(adqt), pointer :: trzn(:)              ! trzn(nzones)
     real(adqt), pointer :: tezn(:)              ! tezn(nzones)
     real(adqt), pointer :: denec(:)             ! denec(ncornr)
     real(adqt), pointer :: tec(:)               ! tec(ncornr)

     real(adqt), pointer :: ematc(:)             ! ematc(ncornr)
     real(adqt), pointer :: decompton(:)         ! decompton(ncornr)
     real(adqt), pointer :: bc(:,:)              ! bc(ngr,ncornr)
     real(adqt), pointer :: etac(:)              ! etac(ncornr)
     real(adqt), pointer :: chic(:,:)            ! chic(ngr,ncornr)
     real(adqt), pointer :: tecn(:)              ! tecn(ncornr)
     real(adqt), pointer :: tezold(:)            ! tezold(nzones)
     real(adqt), pointer :: AbsorptionRate(:)    ! AbsorptionRate(ncornr)
     real(adqt), pointer :: AbsorptionRateOld(:) ! AbsorptionRateOld(ncornr)

     real(adqt), pointer :: denic(:)             ! denic(ncornr)
     real(adqt), pointer :: tic(:)               ! tic(ncornr)
     real(adqt), pointer :: cvi(:)               ! cvi(nzones)
     real(adqt), pointer :: xomei(:)             ! xomei(nzones)
     real(adqt), pointer :: sion(:)              ! sion(nzones)
     real(adqt), pointer :: deniz(:)             ! deniz(nzones)
     real(adqt), pointer :: tiz(:)               ! tiz(nzones)
     real(adqt), pointer :: xeicp(:)             ! xeicp(nzones)

  end type Material

  interface construct
    module procedure Material_ctor
  end interface
 
  interface destruct
    module procedure Material_dtor
  end interface
 
contains
 
!=======================================================================
! construct interface
!=======================================================================

  subroutine Material_ctor(self, Size)
 
    use Size_mod
 
    implicit none
 
!   Passed variables
 
    type(Material),    intent(inout) :: self
    type(MeshSize)                   :: Size

    allocate( self % siga(Size%ngr,Size%nzones) )
    allocate( self % sigs(Size%ngr,Size%nzones) )
    allocate( self % sigt(Size%ngr,Size%nzones) )
    allocate( self % cve(Size%nzones) ) 
    allocate( self % rho(Size%nzones) )
    allocate( self % selec(Size%nzones) )
    allocate( self % qext(Size%ngr,Size%nzones) )
    allocate( self % denez(Size%nzones) ) 
    allocate( self % trz(Size%nzones) )
    allocate( self % tez(Size%nzones) )
    allocate( self % trzn(Size%nzones) )
    allocate( self % tezn(Size%nzones) )
    allocate( self % denec(Size%ncornr) )
    allocate( self % tec(Size%ncornr) ) 

    allocate( self % ematc(Size%ncornr) )
    allocate( self % decompton(Size%ncornr) )
    allocate( self % bc(Size%ngr,Size%ncornr) )
    allocate( self % etac(Size%ncornr) )
    allocate( self % chic(Size%ngr,Size%ncornr) )
    allocate( self % tecn(Size%ncornr) )
    allocate( self % tezold(Size%nzones) )
    allocate( self % AbsorptionRate(Size%ncornr) )
    allocate( self % AbsorptionRateOld(Size%ncornr) )

    if (Size%imatc == 'elec+ion') then
      allocate( self % denic(Size%ncornr) )
      allocate( self % tic(Size%ncornr) )
      allocate( self % cvi(Size%nzones) ) 
      allocate( self % xomei(Size%nzones) )
      allocate( self % sion(Size%nzones) )
      allocate( self % deniz(Size%nzones) )
      allocate( self % tiz(Size%nzones) )
      allocate( self % xeicp(Size%nzones) )
    endif
 

    return
 
  end subroutine Material_ctor

!=======================================================================
! destruct interface
!=======================================================================
                                                            
  subroutine Material_dtor(self, Size)
                                      
    use Size_mod
                
    implicit none
                 
!   Passed variables
                    
    type(Material),    intent(inout) :: self
    type(MeshSize)                   :: Size

    deallocate( self % siga )
    deallocate( self % sigs )
    deallocate( self % sigt )
    deallocate( self % cve )
    deallocate( self % rho )
    deallocate( self % selec )
    deallocate( self % qext )
    deallocate( self % denez )
    deallocate( self % trz )
    deallocate( self % tez )
    deallocate( self % trzn )
    deallocate( self % tezn )
    deallocate( self % denec )
    deallocate( self % tec )

    deallocate( self % ematc )
    deallocate( self % decompton )
    deallocate( self % bc )
    deallocate( self % etac )
    deallocate( self % chic )
    deallocate( self % tecn )
    deallocate( self % tezold )
    deallocate( self % AbsorptionRate )
    deallocate( self % AbsorptionRateOld )

    if (Size%imatc == 'elec+ion') then
      deallocate( self % denic )
      deallocate( self % tic )
      deallocate( self % cvi )
      deallocate( self % xomei )
      deallocate( self % sion )
      deallocate( self % deniz )
      deallocate( self % tiz )
      deallocate( self % xeicp )
    endif

    return
          
  end subroutine Material_dtor


                                                      
end module Material_mod

