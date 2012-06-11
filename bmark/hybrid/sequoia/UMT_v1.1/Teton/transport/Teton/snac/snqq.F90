!***********************************************************************
!                        Version 1:  05/92, PFN                        *
!                                                                      *
!   SNQQ   - This routine, called by SNFLWRZA and SNFLWXYZ calculate   *
!            the total source for the transport sweep of direction m.  *
!            Sources contributions may be external, from scattering    *
!            or due to time-dependence.  There are two options for     *
!            calculating the time-dependent contribution.  In the      *
!            'exact' treatment, all angular fluxes from the previous   *
!            timestep were stored and the time derivative is computed  *
!            rigorously.  In the 'moments' method, only angular        *
!            moments were saved from the previous timestep and are     *
!            used to construct the "old" timestep source.  The within  *
!            group scattering source is calculated using a moments     *
!            expansion (sum of sigs*phic*pnm).                         *
!                                                                      *
!   Input:   iggsct   - scattering source flag                         *
!            itimsrc  - time-dependent source treatment flag           *
!                                                                      *
!   Output:  QC       - total source for this angle         (E/t)      *
!                                                                      *
!***********************************************************************

   subroutine snqq(Size, Geom, QuadSet,               &
                   npart,nsig,m,ndir,itimsrc,iggsct,  &
                   asc,sc,phic,siginv,sigs,QC)

   use kind_mod
   use Size_mod
   use Geometry_mod
   use Quadrature_mod

   implicit none

!  Arguments - Types
                                                                                    
   type(MeshSize)            :: Size
   type(Geometry)            :: Geom 
   type(Quadrature)          :: QuadSet

!  Arguments

   integer,    intent(in)    :: npart,nsig,m,ndir

   real(adqt), intent(in)    :: asc(npart,Size%ncornr),        &
                                sc(npart,Size%ncornr),         &
                                phic(npart,Size%ncornr),       &
                                siginv(npart,Size%ncornr),     &
                                sigs(npart,nsig)

   real(adqt), intent(inout) :: qc(npart,Size%ncornr)

   character(len=8), intent(in) :: itimsrc,iggsct

!  Local

   integer    :: ic,iz,kp1,kmax,l,lp1,n,noff,  &
                 ndim,ncornr,nzones,isctp1

   real(adqt) :: pnm

!  Mesh Constants

   ndim   = Size%ndim
   ncornr = Size%ncornr
   nzones = Size%nzones
   isctp1 = 1

!************************************************ 
!  External + Time-dependent part if present    *
!************************************************

      if (itimsrc == 'exact') then

        do ic=1,ncornr
          qc(:,ic) = siginv(:,ic)*(sc(:,ic) + asc(:,ic))
        enddo

      elseif (itimsrc == 'zonal') then

        do ic=1,ncornr
          iz       = Geom%CToZone(ic)
          qc(:,ic) = siginv(:,ic)*( sc(:,ic) + asc(:,iz) )
        enddo

      elseif (itimsrc == 'off') then

        do ic=1,ncornr
          qc(:,ic) = siginv(:,ic)*sc(:,ic)
        enddo

      endif

!************************************************ 
!  Add the Inscatter Source                     *
!************************************************ 

!  Usually in 2D, moments are doubly indexed using l and k. 
!  We use a single index n given by n = 1 + l*(l+1)+ k.

      if (iggsct == 'on') then
 
        LScatIndex: do lp1=1,isctp1

          l = lp1 - 1

          if (ndim == 2) then
            kmax = lp1
            noff = ( l*lp1 )/2
          elseif (ndim == 3) then
            kmax = 2*lp1 - 1
            noff = l*l
          endif

          KScatIndex: do kp1=1,kmax

            n   = noff + kp1
            pnm = QuadSet%Pnm(n,m)

            if (nsig == nzones) then

              do ic=1,ncornr
                iz = Geom%CToZone(ic)
                qc(:,ic) = qc(:,ic) + siginv(:,ic)*pnm*sigs(:,iz)*phic(:,ic)
              enddo

            elseif (nsig == ncornr) then

              do ic=1,ncornr
                qc(:,ic) = qc(:,ic) + siginv(:,ic)*pnm*sigs(:,ic)*phic(:,ic)
              enddo

            else

              call f90fatal("Bad value for NSIG in SNQQ")

            endif

          enddo KScatIndex

        enddo LScatIndex

      endif
 

      return
      end subroutine snqq


