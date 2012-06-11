!***********************************************************************
!                        Version 0:  02/02, MKN                        *
!                                                                      *
!   CINTERFACE  -   Wrapper for modules that can be called from C++    * 
!                   used to get IterControls pointer                   *
!                                                                      *
!***********************************************************************


   subroutine ConstructMaterial(Size, CMat)

!  Include

   use kind_mod
   use Material_mod
   use Size_mod


   implicit none

!  Arguments


!  CMat is a pointer to the Material Module in C++ 

   integer, intent(inout)    :: CMat

   type(Material),  pointer  :: Mat 
   type(MeshSize)            :: Size

!  Interface to C routine to get address of Material 

   interface 
      subroutine getMatPointer(FMatPtr, CMatPtr)
        use Material_mod

        type(Material)  :: FMatPtr
        integer         :: CMatPtr

      end subroutine getMatPointer 
   end interface

!  Construct Material Module 

   allocate (Mat)

   call construct(Mat, Size)

!  Save addresses for F90 structures for use in C++
   call getMatPointer(Mat, CMat)


   return
   end subroutine ConstructMaterial

