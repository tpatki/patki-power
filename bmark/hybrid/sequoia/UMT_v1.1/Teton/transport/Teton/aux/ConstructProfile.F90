!***********************************************************************
!                        Version 0:  02/02, MKN                        *
!                                                                      *
!   CINTERFACE  -   Wrapper for modules that can be called from C++    * 
!                   used to get IterControls pointer                   *
!                                                                      *
!***********************************************************************


   subroutine ConstructProfile(CProfile, maxprof)

!  Include

   use kind_mod
   use ProfileList_mod


   implicit none

!  Arguments


!  CProfile is really a pointer to Profile in C++ 

   integer, intent(in)          :: maxprof
   integer, intent(inout)       :: CProfile

   type(ProfileList),  pointer  :: Profile 

!  Interface to C routine to get address of ProfileList

   interface 
      subroutine getProfilePointer(FProfPtr, CProfPtr)
        use ProfileList_mod

        type(ProfileList)  :: FProfPtr

        integer :: CProfPtr

      end subroutine getProfilePointer 
   end interface

!  Construct the Source Profile Module 

   allocate (Profile)
   call construct(Profile, maxprof)

!  Save addresses for F90 structures for use in C++
   call getProfilePointer(Profile, CProfile)


   return
   end subroutine ConstructProfile

