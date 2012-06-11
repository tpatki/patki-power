!***********************************************************************
!                         Version 0: 04/06 PFN                         *
!                                                                      *
!    SetTimeStep  -  Called from Teton.cc to update the radiation      *
!                    time and timestep before calling RADTR.           *
!                                                                      *
!    Input:   dtrad      - radiation timestep                          *
!             timerad    - radiation time                              *
!                                                                      *
!    Output:  DtControls - structure containing timestep information   *
!                                                                      *
!***********************************************************************
   subroutine setTimeStep(Size, DtControls, RadEdit, dtrad,   &
                          timerad, tfloor, tmin, erad, emat,  &
                          eradinct, eradesct, eextsrc, echeck)

   use kind_mod
   use Size_mod
   use TimeStepControls_mod
   use Editor_mod

   implicit none


!  Arguments

   type(MeshSize)            :: Size
   type(TimeStepControls)    :: DtControls
   type(Editor)              :: RadEdit

   real(adqt), intent(in)    :: dtrad, timerad, tfloor, tmin
   real(adqt), intent(in)    :: erad, emat, eradinct
   real(adqt), intent(in)    :: eradesct, eextsrc, echeck

!  Update controls
                                                                                             
   call setDtControls(DtControls,         &
                      RadTimeStep=dtrad,  &
                      RadTime=timerad     )

   Size%tfloor = tfloor
   Size%tmin   = tmin

   RadEdit% EnergyRadiation  = erad
   RadEdit% EnergyMaterial   = emat
   RadEdit% EnergyIncident   = eradinct
   RadEdit% EnergyEscaped    = eradesct
   RadEdit% EnergyExtSources = eextsrc
   RadEdit% EnergyCheck      = echeck


   return
   end subroutine setTimeStep 



