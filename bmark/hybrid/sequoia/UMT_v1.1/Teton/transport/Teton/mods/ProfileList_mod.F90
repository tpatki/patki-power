! ProfileList Module:  Contains a list of source profiles

module ProfileList_mod

  use kind_mod
  use Profile_mod

  private

! public interfaces

  public construct, setProfile, getProfile, destruct

  type, public :: ProfileList

     integer                :: NumProfiles       ! number of profiles
     integer                :: MaxProfiles       ! maximum number of profiles
     type(Profile), pointer :: iProfile(:)       ! profile pointers

  end type ProfileList

  interface construct
    module procedure ProfileList_ctor
  end interface

  interface setProfile 
    module procedure ProfileList_set
  end interface

  interface getProfile
    module procedure ProfileList_getProf
  end interface

  interface destruct
    module procedure ProfileList_dtor
  end interface

contains

!=======================================================================
! construct interface
!=======================================================================

  subroutine ProfileList_ctor(self, MaxProfiles)

    implicit none

!   Passed variables

    type(ProfileList), intent(inout)    :: self
    integer, intent(in)                 :: MaxProfiles


    self % NumProfiles = 0
    self % MaxProfiles = MaxProfiles

    allocate( self % iProfile(self % MaxProfiles) )

    return

  end subroutine ProfileList_ctor

!=======================================================================
! set interface
!=======================================================================

  subroutine ProfileList_set(self,            &
                             ProfileID,       &
                             NumTimes,        &
                             NumValues,       &
                             NumInterpValues, &
                             Multiplier,      &
                             Location,        &
                             Type,            &
                             Shape,           &
                             Times,           &
                             Values) 

    implicit none

!   Passed variables

    type(ProfileList), intent(inout)       :: self
    integer, intent(in)                    :: ProfileID
    integer, intent(in)                    :: NumTimes
    integer, intent(in)                    :: NumValues
    integer, intent(in)                    :: NumInterpValues

    real(adqt), optional, intent(in)       :: Multiplier

    character(len=8), intent(in)           :: Location
    character(len=8), intent(in)           :: Type
    character(len=8), optional, intent(in) :: Shape
                                                    
    real(adqt), intent(in)                 :: Times(NumTimes)
    real(adqt), intent(in)                 :: Values(NumValues)


    self % NumProfiles = ProfileID

    call construct(self % iProfile(ProfileID), &
                          NumTimes,            &
                          NumValues,           &
                          NumInterpValues,     &
                          Multiplier,          &
                          Location,            &
                          Type,                &
                          Shape,               &
                          Times,               &
                          Values)

    return

  end subroutine ProfileList_set

!=======================================================================
! destruct interface
!=======================================================================

  subroutine ProfileList_dtor(self)

    implicit none

!   Passed variables

    type(ProfileList),  intent(inout) :: self

!   Local

    integer :: i

!    do i=1,self % MaxProfiles
!      deallocate( self % iProfile(i) )
!    enddo

    return

  end subroutine ProfileList_dtor

!-----------------------------------------------------------------------
  function ProfileList_getProf(self,ProfileID) result(iProfile)

!    Return a pointer to a profile
!      ProfileID   profile ID number 
!      iProfile    pointer to the profile 

!    variable declarations
     implicit none

!    passed variables
     type(ProfileList), intent(in) :: self
     integer,           intent(in) :: ProfileID 
     type(Profile),     pointer    :: iProfile

            
     iProfile => self % iProfile(ProfileID)
            
     return

  end function ProfileList_getProf 

end module ProfileList_mod

