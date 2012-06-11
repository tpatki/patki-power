!***********************************************************************
!                        Version 1:  09/96, PFN                        *
!                                                                      *
!   SNREFLECT - This routine, called by SNFLWXYZ and SNFLWRZA,         *
!               computes the boundary flux (PSIB) for angle m, on      *
!               reflecting boundaries for which angle m is incoming.   *
!                                                                      *
!   Input:                                                             *
!                                                                      *
!   Output:                                                            *
!                                                                      *
!***********************************************************************

   subroutine snreflect(Size, Geom, QuadSet, Minc, PSIB, DOT) 

   use kind_mod
   use constant_mod
   use Size_mod
   use Geometry_mod
   use Quadrature_mod

   implicit none

!  Arguments - Types
                                                                                  
   type(MeshSize)            :: Size
   type(Geometry)            :: Geom
   type(Quadrature)          :: QuadSet

!  Arguments

   integer,    intent(in)    :: Minc

   real(adqt), intent(inout) :: psib(QuadSet%Groups,Size%nbelem,  &
                                     QuadSet%NumAngles), dot(Size%nbelem) 

!  Local Variables

   integer    :: ia,ib,ibs,ib1,ig,ix,mref,  &
                 i1,i2,nreflect,ndim,nbelem,nbsets,Groups

   integer    :: ReflAngle(QuadSet% NumAngles)

   real(adqt) :: tol,Area(Size%ndim),cosratio(QuadSet% NumAngles)

!  Constants

   parameter (tol=1.d-15)

   ndim   = Size% ndim
   nbelem = Size% nbelem
   nbsets = Geom% nbsets
   Groups = QuadSet% Groups

!  Calculate omega*outward normal (DOT is used here and in SNXYZBC)

   do ib=1,nbelem
     dot(ib) = DOT_PRODUCT( QuadSet% omega(:,Minc),Geom%A_bdy(:,ib) )
   enddo 
 
!  Loop over reflecting-boundary sets:
 
   BoundarySetLoop: do ibs=1,nbsets
 
!  Get index of the first and last boundary element in set ibs:

     i1  = Geom% indexRefB(1,ibs)
     i2  = Geom% indexRefB(2,ibs)
 
     ib1 = Geom% listRefB(i1)
 
     if (dot(ib1) < -tol) then
 
!  If dot<0, angle m is incoming on this set. Here we test dot<-tol
!  to account for roundoff errors if the direction is parallel to
!  the reflecting surface (e.g. in Lobatto quadratures). The routine
!  SNMREF computes the angle, MREF, that reflects onto M.
!  It also computes a multiplier, cosrat, that makes our
!  reflection algorithm conservative (i.e., net flux=0).
!  AREA contains the components of the outward normal for this
!  boundary element.

       Area(:) = Geom% A_bdy(:,ib1)

       call snmref(QuadSet,ndim,Minc,NREFLECT,REFLANGLE,  &
                   Area,COSRATIO)
 
!  Put outgoing info (mref) into incoming array (Minc):

       do ix=i1,i2

         ib = Geom% listRefB(ix)

         psib(:,ib,Minc) = zero

         do ia=1,nreflect

           mref = ReflAngle(ia)

           psib(:,ib,Minc) = psib(:,ib,Minc) +  &
                             psib(:,ib,mref)*cosratio(ia)

         enddo

       enddo
 
     endif
 
   enddo BoundarySetLoop 
 
 
   return
   end subroutine snreflect

