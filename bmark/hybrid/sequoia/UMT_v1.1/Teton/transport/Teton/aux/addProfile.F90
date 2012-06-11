!***********************************************************************
!                         Version 0: 04/06 PFN                         *
!                                                                      *
!    AddProfile   -  Called from Teton.cc to add a source profile      *
!                    to the profile list.                              *
!                                                                      *
!    Input:   dtrad      - radiation timestep                          *
!             timerad    - radiation time                              *
!                                                                      *
!    Output:  Profile    - structure containing source profiles        *
!                                                                      *
!***********************************************************************
   subroutine addProfile(Profile,                        &
                         ProfileID, NumTimes, NumValues, &
                         NumInterpValues, Multiplier,    &
                         Location, Type, Shape,          &
                         Times, Values) 

   use kind_mod
   use ProfileList_mod

   implicit none


!  Arguments

   type(ProfileList)            :: Profile 

   integer, intent(in)          :: ProfileID
   integer, intent(in)          :: NumTimes
   integer, intent(in)          :: NumValues
   integer, intent(in)          :: NumInterpValues
              
   real(adqt), intent(in)       :: Multiplier
              
   character(len=8), intent(in) :: Location
   character(len=8), intent(in) :: Type
   character(len=8), intent(in) :: Shape
              
   real(adqt), intent(in)       :: Times(NumTimes)
   real(adqt), intent(in)       :: Values(NumValues)

!  Add this profile to the list 

   call setProfile(Profile,         &
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


   return
   end subroutine addProfile 



