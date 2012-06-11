!***********************************************************************
!                        Version 0:  02/02, MKN                        *
!                                                                      *
!   CINTERFACE  -   Wrapper for modules that can be called from C++    * 
!                   used to get DtControls pointer                     *
!                                                                      *
!***********************************************************************


   subroutine ConstructDtControls(dtrad, dtrmn, dtrmx, delte, deltr, &
                                  CDtControls)

!  Include

   use kind_mod
   use TimeStepControls_mod


   implicit none

!  Arguments

!  Time Step Controls
   real(adqt), intent(in)    :: dtrad
   real(adqt), intent(in)    :: dtrmn
   real(adqt), intent(in)    :: dtrmx
   real(adqt), intent(in)    :: delte
   real(adqt), intent(in)    :: deltr

!  CDtControls is a pointer to DtControls in C++ 

   integer, intent(inout)    :: CDtControls

   type(TimeStepControls), pointer  :: DtControls

!  Interface to C routine to get address of DtControls

   interface 
      subroutine getDtPointer(FDtPtr, CDtPtr)
        use TimeStepControls_mod

        type(TimeStepControls) :: FDtPtr

        integer :: CDtPtr

      end subroutine getDtPointer 
   end interface

!  Construct Time Step Controls

   allocate (DtControls)

   call construct(DtControls, RadTimeStep=dtrad,  &
                              MaxChangeTe=delte,  &
                              MaxChangeTr4=deltr, &
                              MinTimeStep=dtrmn,  &
                              MaxTimeStep=dtrmx)

!  Save addresses for F90 structures for use in C++
   call getDtPointer(DtControls, CDtControls)


   return
   end subroutine ConstructDtControls

