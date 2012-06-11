!***********************************************************************
!                        Version 0:  02/02, MKN                        *
!                                                                      *
!   CINTERFACE  -   Wrapper for modules that can be called from C++    * 
!                   used to get IterControls pointer                   *
!                                                                      *
!***********************************************************************


   subroutine ConstructGeometry(Size, CGeom)

!  Include

   use kind_mod
   use Geometry_mod
   use Size_mod


   implicit none

!  Arguments


!  CGeometry is a pointer to the Geometry Module in C++ 

   integer, intent(inout)    :: CGeom

   type(Geometry),  pointer  :: Geom 
   type(MeshSize)            :: Size

!  Interface to C routine to get address of Geometry

   interface 
      subroutine getGeomPointer(FGeomPtr, CGeomPtr)
        use Geometry_mod

        type(Geometry)  :: FGeomPtr
        integer         :: CGeomPtr

      end subroutine getGeomPointer 
   end interface

!  Construct Run Parameters

   allocate (Geom)

   call construct(Geom, Size)

!  Save addresses for F90 structures for use in C++
   call getGeomPointer(Geom, CGeom)


   return
   end subroutine ConstructGeometry

