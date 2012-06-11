!***********************************************************************
!                        Version 0:  02/02, MKN                        *
!                                                                      *
!   CINTERFACE  -   Wrapper for modules that can be called from C++    * 
!                   used to get IterControls pointer                   *
!                                                                      *
!***********************************************************************


   subroutine ConstructEditor(Size, CEdit)

!  Include

   use kind_mod
   use Editor_mod
   use Size_mod


   implicit none

!  Arguments


!  CEdit is a pointer to the Edit Module in C++ 

   integer, intent(inout)   :: CEdit

   type(Editor),  pointer   :: Edit 
   type(MeshSize)           :: Size

!  Interface to C routine to get address of Edit

   interface 
      subroutine getEditPointer(FEditPtr, CEditPtr)
        use Editor_mod

        type(Editor)  :: FEditPtr
        integer       :: CEditPtr

      end subroutine getEditPointer 
   end interface

!  Construct Problem Edits 

   allocate (Edit)

   call construct(Edit, Size)

!  Save addresses for F90 structures for use in C++
   call getEditPointer(Edit, CEdit)


   return
   end subroutine ConstructEditor

