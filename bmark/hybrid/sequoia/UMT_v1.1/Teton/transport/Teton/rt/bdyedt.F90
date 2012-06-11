!***********************************************************************
!                        Version 1:  08/94, PFN                        *
!                                                                      *
!   BDYEDT - Computes edits of escaping and incident currents on all   *
!            boundaries.                                               *
!                                                                      *
!   Input:                                                             *
!                                                                      *
!   Output:                                                            *
!***********************************************************************
   subroutine bdyedt(Size, Geom, Quad, RadEdit, psib) 

   use kind_mod
   use constant_mod
   use Size_mod
   use Geometry_mod
   use QuadratureList_mod
   use Quadrature_mod
   use Editor_mod

   implicit none

!  Arguments - Types
                                                                                    
   type(MeshSize)            :: Size
   type(Geometry)            :: Geom
   type(QuadratureList)      :: Quad
   type(Editor)              :: RadEdit

!  Arguments

   real(adqt), intent(in)    :: psib(Size%ngr,Size%nbelem,Size%nangSN)

!  Local Variables

   type(Quadrature), pointer  :: QuadSet

   integer    :: nbtot,ia,ib,ic,iedit,m1,ibatch,  &
                 ip,npart,ng,nangles,ndim,nbelem,icface

   integer    :: NumSnSets

   real(adqt) :: twopi,angdota,current,gfac

!  Constants

   twopi  = two*pi
   nbtot  = Size%nbedit + 1

   ndim   = Size%ndim
   nbelem = Size%nbelem

   NumSnSets = getNumSnSets(Quad)

!  Initialize partial current edits

   RadEdit% RadEnergyEscRate(:,:) = zero
   RadEdit% RadEnergyIncRate(:,:) = zero

!  Accumulate exiting and incoming partial currents for all
!  non-reflecting boundaries.  Partial currents are accumulated
!  by boundary-edit index (1 -> nbedit) and also for all
!  problem boundaries (nbedit+1).


   BoundaryLoop: do ib=1,nbelem

     iedit = Geom%BdyToEdit(ib)

     if ( (Geom%BdyToBC(ib) == 'refl') .or.      & 
          (Geom%BdyToBC(ib) == 'shared') ) then

     else

!  Compute (unit normal) dot (omega)*area and partial currents

!  Determine Incident and exiting currents

       ng  = 0

       if (ndim == 1 .or. ndim == 3) then
         gfac = one
       elseif (ndim == 2) then
         ic     = Geom%BdyToC(1,ib)
         icface = Geom%BdyToC(2,ib)
         gfac   = twopi*Geom%rbar(icface,1,ic)
       endif 

       if (iedit == 0) then

         BatchLoop1: do ibatch=1,NumSnSets

           QuadSet => getQuadrature(Quad, ibatch)

           npart   = QuadSet% Groups 
           nangles = QuadSet% NumAngles 

           AngleLoop1: do ia=1,nangles

             angdota = DOT_PRODUCT( QuadSet%omega(:,ia),Geom%A_bdy(:,ib) )

             if (angdota > zero) then
               do ip=1,npart
                 current = gfac*QuadSet%weight(ia)*angdota*psib(ip,ib,ia)
                 RadEdit% RadEnergyEscRate(nbtot,ng+ip) =   &
                 RadEdit% RadEnergyEscRate(nbtot,ng+ip) + current 
               enddo
             else
               do ip=1,npart
                 current = gfac*QuadSet%weight(ia)*angdota*psib(ip,ib,ia)
                 RadEdit% RadEnergyIncRate(nbtot,ng+ip) =   &
                 RadEdit% RadEnergyIncRate(nbtot,ng+ip) - current 
               enddo
             endif

           enddo AngleLoop1

           ng  = ng  + npart

         enddo BatchLoop1

       else

         BatchLoop2: do ibatch=1,NumSnSets

           QuadSet => getQuadrature(Quad, ibatch)

           npart   = QuadSet% Groups
           nangles = QuadSet% NumAngles

           AngleLoop2: do ia=1,nangles

             angdota = DOT_PRODUCT( QuadSet%omega(:,ia),Geom%A_bdy(:,ib) )

             if (angdota > zero) then
               do ip=1,npart
                 current = gfac*QuadSet%weight(ia)*angdota*psib(ip,ib,ia)
                 RadEdit% RadEnergyEscRate(nbtot,ng+ip) =   &
                 RadEdit% RadEnergyEscRate(nbtot,ng+ip) + current
                 RadEdit% RadEnergyEscRate(iedit,ng+ip) =   &
                 RadEdit% RadEnergyEscRate(iedit,ng+ip) + current 
               enddo
             else
               do ip=1,npart
                 current = gfac*QuadSet%weight(ia)*angdota*psib(ip,ib,ia)
                 RadEdit% RadEnergyIncRate(nbtot,ng+ip) =   &
                 RadEdit% RadEnergyIncRate(nbtot,ng+ip) - current 
                 RadEdit% RadEnergyIncRate(iedit,ng+ip) =   &
                 RadEdit% RadEnergyIncRate(iedit,ng+ip) - current 
               enddo
             endif

           enddo AngleLoop2

           ng  = ng  + npart

         enddo BatchLoop2

       endif

     endif

   enddo BoundaryLoop



   return
   end subroutine bdyedt


