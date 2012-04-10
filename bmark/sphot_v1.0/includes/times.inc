c This is 'times.inc'.
c

       INTEGER maxMPItasks, maxThreadsPerMPItask
       PARAMETER( maxMPItasks = 16384 )
       PARAMETER( maxThreadsPerMPItask = 128 )
       real*8 tgen
       real*8 loopBeginTime, loopEndTime, loopWallClockTime
       real*8 loopTotalCPUTime, loopSpeedup
       real*8 progBeginTime, progEndTime, progWallClockTime
       real*8 progTotalCPUTime, progSpeedup
       real*8 allocateTime
       real*8 seedGenTime
       real*8 copyGlobTime(maxMPItasks)
c      common, shared /timecom/
       common /timecom/ tgen,
     .  loopBeginTime, loopEndTime, loopWallClockTime,
     .  loopTotalCPUTime, loopSpeedup,
     .  progBeginTime, progEndTime, progWallClockTime,
     .  progTotalCPUTime, progSpeedup,
     .  allocateTime,
     .  seedGenTime,
     .  copyGlobTime

