!***********************************************************************
!                        Version 1:  07/02, PFN                        *
!                                                                      *
!   SETSIG   - This routine computes several combinations of the total *
!              cross section and geometry factors.                     *
!                                                                      *
!   Input:                                                             *
!                                                                      *
!   Output:                                                            *
!                                                                      *
!***********************************************************************

   subroutine setsig(Size, Geom, nsig,npart,  &
                     sigt,SIGVOL,SIGINV,SIGAREA)

!  Modules

   use kind_mod
   use constant_mod
   use Size_mod
   use Geometry_mod

   implicit none

!  Arguments - Types
                                                                                    
   type(MeshSize)            :: Size
   type(Geometry)            :: Geom

!  Arguments

   integer,    intent(in)    :: nsig,npart

   real(adqt), intent(in)    :: sigt(npart,nsig) 

   real(adqt), intent(inout) :: sigvol(npart,Size%ncornr),   &
                                siginv(npart,Size%ncornr),   &
                                sigarea(npart,Size%ncornr) 

!  Local

   integer :: ic,ip,iz,ndim,ncornr,nzones

!  Mesh Constants

   ndim   = Size%ndim
   ncornr = Size%ncornr
   nzones = Size%nzones


!  Set corner sigt*volume (SIGVOL)

      if (nsig == nzones) then

        if (ndim == 3) then

          do ic=1,ncornr
            iz = Geom%CToZone(ic)
            do ip=1,npart
              sigvol(ip,ic) = Geom%volc(ic)*sigt(ip,iz)
              siginv(ip,ic) =           one/sigt(ip,iz)
            enddo
          enddo

        elseif (ndim == 2) then

          do ic=1,ncornr
            iz = Geom%CToZone(ic)
            do ip=1,npart
              sigvol(ip,ic)  = Geom%volc(ic) *sigt(ip,iz)
              sigarea(ip,ic) = Geom%areac(ic)*sigt(ip,iz)
              siginv(ip,ic)  =            one/sigt(ip,iz)
            enddo
          enddo

        endif

      elseif (nsig == ncornr) then

        if (ndim == 3) then

          do ic=1,ncornr
            do ip=1,npart
              sigvol(ip,ic) = Geom%volc(ic)*sigt(ip,ic)
              siginv(ip,ic) =           one/sigt(ip,ic)
            enddo
          enddo

        elseif (ndim == 2) then

          do ic=1,ncornr
            do ip=1,npart
              sigvol(ip,ic)  = Geom%volc(ic) *sigt(ip,ic)
              sigarea(ip,ic) = Geom%areac(ic)*sigt(ip,ic)
              siginv(ip,ic)  =            one/sigt(ip,ic)
            enddo
          enddo

        endif

      else

        call f90fatal("Bad value of NSIG in SETSIG")

      endif



      return
      end subroutine setsig 

