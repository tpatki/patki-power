!***********************************************************************
!                         Version 0: 04/06 PFN                         *
!                                                                      *
!    SetMaterialModule -  Called from Teton.cc to associate pointers   *
!                         in the MaterialModule with memory allocated  *   
!                         in C++.                                      *
!                                                                      *
!    Input:   Size  - structure containing mesh parameters             *
!             Mat   - structure containing material arrays             *
!                                                                      *
!    Output:                                                           *
!                                                                      *
!***********************************************************************
   subroutine setMaterialModule(SIZE, MAT,                        &
                                siga, sigs, sigt, cve, rho,       &
                                selec, denez, trz, tez, tec,      &
                                cvi, xomei, sion, deniz, tiz, tic)

   use kind_mod
   use Size_mod 
   use Material_mod

   implicit none


!  Arguments

   type(MeshSize),     intent(in)    :: Size 
   type(Material),     intent(inout) :: Mat 

   real(adqt), target, intent(in) :: siga(Size%ngr,Size%nzones) 
   real(adqt), target, intent(in) :: sigs(Size%ngr,Size%nzones)
   real(adqt), target, intent(in) :: sigt(Size%ngr,Size%nzones) 
   real(adqt), target, intent(in) :: cve(Size%nzones)
   real(adqt), target, intent(in) :: rho(Size%nzones)
   real(adqt), target, intent(in) :: selec(Size%nzones)
   real(adqt), target, intent(in) :: denez(Size%nzones)
   real(adqt), target, intent(in) :: trz(Size%nzones)
   real(adqt), target, intent(in) :: tez(Size%nzones)
   real(adqt), target, intent(in) :: tec(Size%ncornr)

   real(adqt), target, intent(in) :: cvi(Size%nzones)
   real(adqt), target, intent(in) :: xomei(Size%nzones)
   real(adqt), target, intent(in) :: sion(Size%nzones)
   real(adqt), target, intent(in) :: deniz(Size%nzones)
   real(adqt), target, intent(in) :: tiz(Size%nzones)
   real(adqt), target, intent(in) :: tic(Size%ncornr)

!  Material Properties 

   Mat%siga  => siga 
   Mat%sigs  => sigs 
   Mat%sigt  => sigt 
   Mat%cve   => cve 
   Mat%rho   => rho
   Mat%selec => selec
   Mat%denez => denez
   Mat%trz   => trz
   Mat%tez   => tez
   Mat%tec   => tec

   if (Size%imatc == 'elec+ion') then
     Mat%cvi   => cvi 
     Mat%xomei => xomei
     Mat%sion  => sion
     Mat%deniz => deniz
     Mat%tiz   => tiz
     Mat%tic   => tic
   endif


   return
   end subroutine setMaterialModule 



