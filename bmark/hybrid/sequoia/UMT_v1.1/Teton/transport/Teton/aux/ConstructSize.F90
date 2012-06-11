!***********************************************************************
!                        Version 0:  02/02, MKN                        *
!                                                                      *
!   CINTERFACE  -   Wrapper for modules that can be called from C++    * 
!                   used to get IterControls pointer                   *
!                                                                      *
!***********************************************************************

   subroutine ConstructSize(CSize,                               &
                            my_node, nzones, ncornr, nfaces,     &
                            npnts, nbelem, ndim, maxcf, ngr,     &
                            nangSN, npsi, ncomm, nbshare,        &
                            nbedit, tfloor, tmin, igeom, ittyp,  &
                            iaccel, imatc, iscat, itimsrc,       &
                            decomp_s)

!  Include

   use kind_mod
   use Size_mod


   implicit none

!  Arguments

!  Run Parameters
    
   integer,   intent(in) :: my_node
   integer,   intent(in) :: nzones
   integer,   intent(in) :: ncornr
   integer,   intent(in) :: nfaces
   integer,   intent(in) :: npnts
   integer,   intent(in) :: nbelem
   integer,   intent(in) :: ndim
   integer,   intent(in) :: maxcf
   integer,   intent(in) :: ngr
   integer,   intent(in) :: nangSN
   integer,   intent(in) :: npsi
   integer,   intent(in) :: ncomm
   integer,   intent(in) :: nbshare
   integer,   intent(in) :: nbedit
    
   real(adqt),        intent(in) :: tfloor
   real(adqt),        intent(in) :: tmin
    
   character(len=8),  intent(in) :: igeom
   character(len=8),  intent(in) :: ittyp
   character(len=8),  intent(in) :: iaccel
   character(len=8),  intent(in) :: imatc
   character(len=8),  intent(in) :: iscat
   character(len=8),  intent(in) :: itimsrc
   character(len=8),  intent(in) :: decomp_s

!  CSize is a pointer to the Size Module in C++ 

   integer, intent(inout)    :: CSize

   type(MeshSize),  pointer  :: Size

!  Interface to C routine to get address of Size 

   interface 
      subroutine getSizePointer(FSizePtr, CSizePtr)
        use Size_mod

        type(MeshSize)  :: FSizePtr
        integer         :: CSizePtr

      end subroutine getSizePointer 
   end interface

!  Construct Run Parameters

   allocate (Size)

   call construct(Size, my_node=my_node,                   &
                        nzones=nzones, ncornr=ncornr,      &
                        nfaces=nfaces, npnts=npnts,        &
                        nbelem=nbelem, ndim=ndim,          &
                        maxcf=maxcf, ngr=ngr,              &
                        nangSN=nangSN,                     &
                        npsi=npsi,                         &
                        ncomm=ncomm, nbshare=nbshare,      &
                        nbedit=nbedit, tfloor=tfloor,      &
                        tmin=tmin,                         &
                        igeom=igeom, ittyp=ittyp,          &
                        iaccel=iaccel, imatc=imatc,        &
                        iscat=iscat, itimsrc=itimsrc,      &
                        decomp_s=decomp_s)


!  Save addresses for F90 structures for use in C++
   call getSizePointer(Size, CSize)


   return
   end subroutine ConstructSize

