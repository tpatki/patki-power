!***********************************************************************
!                        Version 0:  02/02, MKN                        *
!                                                                      *
!   CINTERFACE  -   Wrapper for modules that can be called from C++    * 
!                   used to get IterControls pointer                   *
!                                                                      *
!***********************************************************************


   subroutine ConstructQuadrature(CQuadrature, ngr, QuadDef)

!  Include

   use kind_mod
   use QuadratureList_mod


   implicit none

!  Arguments


!  CQuadrature is really a pointer to Quadrature in C++ 

   integer,    intent(in)    :: ngr
   integer,    intent(in)    :: QuadDef(6,ngr+1)
   integer,    intent(inout) :: CQuadrature

   type(QuadratureList),  pointer  :: Quadrature 

!  Local

   integer :: ig, NumQuadSets, type, type_set, norder, norder_set

!  Interface to C routine to get address of QuadratureList

   interface 
      subroutine getQuadPointer(FQuadPtr, CQuadPtr)
        use QuadratureList_mod

        type(QuadratureList)  :: FQuadPtr

        integer :: CQuadPtr

      end subroutine getQuadPointer 
   end interface

!  Construct the Quadrature Module 

   allocate (Quadrature)

!  Find the number of angle sets 

   NumQuadSets =  0 
   type_set    = -1 
   norder_set  = -1 

   do ig=1,ngr
     type   = QuadDef(1,ig)
     norder = QuadDef(2,ig)
    
     if (   type == type_set   .and.   &
          norder == norder_set ) then 

!  This group belongs to the current batch

     else

       NumQuadSets = NumQuadSets + 1
       type_set    = type
       norder_set  = norder

     endif
   enddo

!  Add one more set for GTA

   NumQuadSets = NumQuadSets + 1 

   call construct(Quadrature, NumQuadSets)

!  Save addresses for F90 structures for use in C++
   call getQuadPointer(Quadrature, CQuadrature)


   return
   end subroutine ConstructQuadrature

