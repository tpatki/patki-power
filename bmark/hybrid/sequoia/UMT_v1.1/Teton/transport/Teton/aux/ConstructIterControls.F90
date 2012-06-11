!***********************************************************************
!                        Version 0:  02/02, MKN                        *
!                                                                      *
!   CINTERFACE  -   Wrapper for modules that can be called from C++    * 
!                   used to get IterControls pointer                   *
!                                                                      *
!***********************************************************************


   subroutine ConstructIterControls(noutmx, ninmx, ngdamx,  &
                                    epstmp, epsinr, epsgda, &
                                    CIterControls)

!  Include

   use kind_mod
   use iter_control_list_mod
   use iter_control_mod


   implicit none

!  Arguments

!  Iteration Controls
   integer,    intent(in)    :: ngdamx
   integer,    intent(in)    :: noutmx
   integer,    intent(in)    :: ninmx
   real(adqt), intent(in)    :: epsgda
   real(adqt), intent(in)    :: epstmp
   real(adqt), intent(in)    :: epsinr

!  CIterControls is really a pointer to IterControls in C++ 

   integer, intent(inout)    :: CIterControls

   type(IterControlList),  pointer  :: IterControls
   type(IterControl),      pointer  :: iControl

!  Interface to C routine to get address of IterControlList

   interface 
      subroutine getIterPointer(FIterPtr, CIterPtr)
        use iter_control_list_mod

        type(IterControlList)  :: FIterPtr

        integer :: CIterPtr

      end subroutine getIterPointer 
   end interface

!  Construct Iteration Controls

   allocate (IterControls)
   call construct(IterControls)
   call resetNumberOfIterations(IterControls)

   iControl => getIterationControl(IterControls, "grey")
   call setControls(iControl, epsilonPoint=epsgda,  &
                    maxNumberOfIterations=ngdamx)

   iControl => getIterationControl(IterControls, "temperature")
   call setControls(iControl, epsilonPoint=epstmp,  &
                    maxNumberOfIterations=noutmx)

   iControl => getIterationControl(IterControls, "intensity")
   call setControls(iControl, epsilonPoint=epsinr,  &
                    maxNumberOfIterations=ninmx)

!  Save addresses for F90 structures for use in C++
   call getIterPointer(IterControls, CIterControls)


   return
   end subroutine ConstructIterControls

