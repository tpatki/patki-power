      program sphot
c***********************************************************************
c     sphot - scalar photon transport
c
c     this program is a scalar version of the vectorized monte carlo
c     code vphot which is used to solve photon transport problems in
c     spherical geometry.  this version INCLUDEs a plankian source,
c     thomson scattering, russian roulette/splitting and time census.
c     there are two options for russian roulette, one is based on photon
c     weight (culling) and the other is based on cell importances.
c***********************************************************************
c     * * * *  sphot - I/O units * * * *
c     
c     4  = 'opac.txt' - ASCII formatted opacity library
c          'input.dat'- Input File
c     6  = sdtout
c***********************************************************************

 
      INCLUDE 'params.inc'
      INCLUDE 'globals.inc'
      INCLUDE 'shared.inc'
      INCLUDE 'geomz.inc'
      INCLUDE 'randseed.inc'
      INCLUDE 'times.inc'
      INCLUDE 'mpif.h'


      INTEGER mySeed(IRandNumSize)
      INTEGER*4 nescgp(negrps)
      REAL*8 enesc(negrps)
      REAL*8 wcut, wmin, wmax
      REAL*8 wlost, wesc, wrr
      REAL*8 wabs, wcen, epgain, etot
      REAL*8 ranf
      EXTERNAL ranf

      REAL*8 enescSum(maxruns), t_enescSum, g_enescSum, avg_enescSum, tmp_wesc
      REAL*8 del_diff, g_del_diff, std_dev, tmp_var


      INTEGER*4 npart, nphtot, nploss
      INTEGER*4 nlost, nesc, nrr, nabs, ncen
      INTEGER*4 nscat, nsplt, ntrac

      INTEGER runCount

      REAL*8  ntracSum, g_ntracSum


      INTEGER nout3
      parameter (nout3=13)

c.....Variables needed for MPI and OpenMP

      LOGICAL srFlag
      INTEGER OMP_GET_NUM_THREADS, OMP_GET_THREAD_NUM
      EXTERNAL OMP_GET_NUM_THREADS, OMP_GET_THREAD_NUM
      INTEGER ierr, numMPItasks, MPIid, thrID, numThreads, 
     &        numThreadsSave, nRunsPerMPItask, offset,
     &        statArray(MPI_STATUS_SIZE, maxMPItasks),
     &        req(maxMPItasks),
     &        ibuf(maxThreadsPerMPItask*11), 
     &        jbuf(maxThreadsPerMPItask*11, maxMPItasks),
     &        lescbuf(maxThreadsPerMPItask*negrps), 
     &        nescbuf(maxThreadsPerMPItask*negrps, maxMPItasks)
      REAL*8  t1, t2, t3, r1, 
     &        loopbuf(maxThreadsPerMPItask*4, maxMPItasks),
     &        rbuf(maxThreadsPerMPItask*7), 
     &        sbuf(maxThreadsPerMPItask*7, maxMPItasks),
     &        lenbuf(maxThreadsPerMPItask*negrps), 
     &        enbuf(maxThreadsPerMPItask*negrps, maxMPItasks),
     &        thrBuf(maxThreadsPerMPItask*4), 
     &        fRanBuf(maxThreadsPerMPItask),
     &        depArray(nzmax), depBuff(nzmax)

c......

      CALL MPI_INIT( ierr )
      CALL MPI_COMM_RANK( MPI_COMM_WORLD, MPIid, ierr )
      CALL MPI_COMM_SIZE( MPI_COMM_WORLD, numMPItasks, ierr )


      CALL msecond(progBeginTime)
      CALL allocdyn
      CALL msecond(t1)
      allocateTime = t1 - progBeginTime

      CALL rdinput(NRuns)

c.....If the number of runs < the number of MPI tasks, just quit
      IF( nRuns .lt. numMPItasks ) THEN
         IF( MPIid .eq. 0 ) THEN
            PRINT *, "numMPItasks > nRuns, reset numMPItasks"
            PRINT *, "exiting..."
         END IF
         goto 1001
      END IF

c.....If the number of runs > maxruns then quit
      IF( nRuns .gt. maxruns ) THEN
         IF( MPIid .eq. 0 ) THEN
            PRINT *, "nRuns > maxruns.  Need to modify maxruns in
     & params.inc file and recompile."
            PRINT *, "exiting..."
         END IF
         goto 1001
      END IF

c.....Set the number of runs per MPI task
      nRunsPerMPItask = nRuns/numMPItasks

c.....If the number of MPI tasks > 1, then we need to send/receive,
c.....otherwise, we don't
      IF( numMPItasks .gt. 1 ) THEN
         srFlag = .TRUE.
      else
         srFlag = .FALSE.
      END IF

c.... Zero out timing arays.....
      DO 5 i = 1, nRuns
         g_texec(i) = 0.0
         g_overheadTime(i) = 0.0
 5    CONTINUE


      CALL msecond(t2)
      CALL seedranf(nRuns+1)
      CALL msecond(seedGenTime)
      seedGenTime = seedGenTime - t2

      CALL genmesh
      CALL genxsec
      CALL msecond(tgen)
      tgen = tgen - t1
      CALL msecond(loopBeginTime)

      CALL copyglob

      nRunsSum  = 0
c     n         = nRuns
      ithRun = MPIid*nRunsPerMPItask 

      DO i = 1, nzones
         depArray(i) = 0.D0
         depBuff(i)  = 0.D0
      END do

      runCount = 0

      ntracSum = 0.0
      t_enescSum = 0.0

c......Begin the OpenMP parallel region.  Only variables required
c......to be PRIVATE are explicitly scoped.  All other variables
c......are assumed to be SHARED.

!$OMP  PARALLEL  DEFAULT( SHARED )
!$OMP+ PRIVATE( thrID, ithRun, myStream, nescgp,
!$OMP+         enesc, wcut, wmin, wmax, wlost, wesc, wrr,
!$OMP+         wabs, wcen, epgain, etot, npart, nphtot, nploss,
!$OMP+         nlost, nesc, nrr, nabs, ncen, nscat, nsplt, ntrac, 
!$OMP+         t1, t2, t3, r1, offset,
!$OMP+         numThreads, nThrRuns,tmp_wesc )
!$OMP+ FIRSTPRIVATE( mySeed )
!$OMP+ REDUCTION(+:runCount)

      thrID = OMP_GET_THREAD_NUM() + 1
      numThreads = OMP_GET_NUM_THREADS()
      nThrRuns = nRunsPerMPItask / numThreads
      ithRun = MPIid*nRunsPerMPItask + thrID
      myStream = -1

      DO 1000 ict = 1, nThrRuns 

         CALL msecond(t1)

         CALL execute(ithRun, myStream, mySeed, nescgp, enesc, wcut, 
     &        wmin, wmax, wlost, wesc, wrr, wabs, wcen, epgain, etot,
     &        npart, nphtot, nploss, nlost, nesc, nrr, nabs, ncen,
     &        nscat, nsplt, ntrac, fRanBuf(thrID), depArray )

         g_firstRanf(ithRun) = fRanBuf(thrID)

         CALL msecond (t2)

         tmp_wesc = 0.0
!  
!        copy the following from wroutput.f

         do 498 i=1,12
             tmp_wesc = tmp_wesc + enesc (i)
 498     continue
         enescSum(ithRun) = tmp_wesc/dble(nphtot)


!$OMP    critical

           ntracSum = ntracSum + ntrac
           t_enescSum = t_enescSum + enescSum(ithRun)

!$OMP    end critical

        if (print_flag .gt. 0) then

         CALL copypriv(ithRun, srFlag, nescgp, enesc, wcut, 
     &        wmin, wmax, wlost, wesc, wrr, wabs, wcen, epgain, etot,
     &        npart, nphtot, nploss, nlost, nesc, nrr, nabs, ncen,
     &        nscat, nsplt, ntrac, 
     &        g_etot, g_epgain, g_wlost, g_wesc, g_wrr, g_wabs, 
     &        g_wcen, g_enesc, ng_npart, ng_nphtot, ng_nploss,
     &        ng_nlost, ng_nesc, ng_nrr, ng_nabs, ng_ncen, ng_nscat,
     &        ng_nsplt, ng_ntrac, ng_nescgp, ibuf, jbuf, rbuf, sbuf,
     &        lescbuf, nescbuf, lenbuf, enbuf )


        endif

         CALL msecond(t3)

         r1 = ranf(mySeed)

c........MPI task 0 collects timing information including from other MPI 
c........tasks if any are present.
         IF( MPIid .eq. 0  ) THEN

            g_texec(ithRun)        = t2-t1
            g_overheadTime(ithRun) = t3-t2
            g_lastRanf(ithRun)     = r1

!$OMP MASTER
            IF( numMPItasks .GT. 1 ) THEN

               DO 10 i = 1, numMPItasks-1
                  CALL MPI_IRECV( loopbuf(1,i), numThreads*4, 
     &                 MPI_DOUBLE_PRECISION, MPI_ANY_SOURCE,
     &                 MPI_ANY_TAG, MPI_COMM_WORLD, req(i), ierr )
 10            CONTINUE

               CALL MPI_WAITALL( numMPItasks-1, req, statArray, ierr )        

               DO 20 i = 1, numMPItasks-1
                  k = statArray( MPI_TAG, i ) - 1
                  DO 30 j = 1, numThreads
                     offset = j*4-3
                     g_texec(k+j)        = loopbuf(offset,i)
                     g_overheadTime(k+j) = loopbuf(offset+1,i)
                     g_firstRanf(k+j)    = loopbuf(offset+2,i)
                     g_lastRanf(k+j)     = loopbuf(offset+3,i)
 30               CONTINUE
 20            CONTINUE

            END IF
!$OMP END MASTER
         END IF


c........Send timing/random number info to MPI task 0
         IF( MPIid .gt. 0 ) THEN
            offset = thrID*4-3
            thrBuf(offset)   = t2-t1
            thrBuf(offset+1) = t3-t2
            thrBuf(offset+2) = fRanBuf(thrID)
            thrBuf(offset+3) = r1

!$OMP BARRIER
!$OMP MASTER
            CALL MPI_SEND( thrBuf, numThreads*4, MPI_DOUBLE_PRECISION, 
     &           0, ithRun, MPI_COMM_WORLD, ierr )
!$OMP END MASTER

         END IF

         ithRun = ithRun + numThreads
         runCount = runCount + 1

 1000 CONTINUE

c.....Need to save the number of threads before exiting parallel
c.....region - the numThreads variable is private and will be undefined
c.....after END PARALLEL.  Needed to calculate efficiency in writeout routine.
!$OMP MASTER
      IF ( MPIid .EQ. 0 ) numThreadsSave = numThreads
!$OMP END MASTER

!$OMP END PARALLEL

c.....Believe it or not, this next assignment is needed to work around
c.....an SGI compiler bug.  Shouldn't need it, but we do.
      numThreads = numThreadsSave


      
       IF( numMPItasks .GT. 1 ) THEN

         CALL MPI_REDUCE( depArray, depBuff, nzones, 
     &        MPI_DOUBLE_PRECISION, MPI_SUM, 0, MPI_COMM_WORLD, ierr )
          

         CALL MPI_REDUCE( runCount, nRunsSum, 1, MPI_INTEGER,
     &        MPI_SUM, 0, MPI_COMM_WORLD, ierr )
       ELSE
         nRunsSum = runCount
       END IF

       IF( (numMPItasks .GT. 1) .AND. (srFlag .EQV. .TRUE.) ) THEN
         CALL MPI_BARRIER( MPI_COMM_WORLD, ierr )
       END IF

       CALL msecond(loopEndTime)


       IF( MPIid .eq. 0 ) CALL writeout(numMPItasks, numThreads)

c
c
c
       CALL MPI_REDUCE(ntracSum, g_ntracSum , 1, MPI_DOUBLE_PRECISION,
     &        MPI_SUM, 0, MPI_COMM_WORLD, ierr )


       g_enescSum = 0.0
       CALL MPI_ALLREDUCE(t_enescSum, g_enescSum , 1, 
     &        MPI_DOUBLE_PRECISION, MPI_SUM, MPI_COMM_WORLD, ierr )


       avg_enescSum = g_enescSum/nRuns
c
c      calculate out the std. dev
c

       ithRun = MPIid* nRunsPerMPItask
    
       del_diff = 0.0
       DO 50 i = 1, nRunsPerMPItask 
         tmp_var = abs(g_enescSum/nRuns - enescSum(i+ithRun))
         del_diff = del_diff + tmp_var*tmp_var
 50    CONTINUE


       CALL MPI_REDUCE(del_diff, g_del_diff , 1, MPI_DOUBLE_PRECISION,
     &        MPI_SUM, 0, MPI_COMM_WORLD, ierr )

       IF( MPIid .eq. 0 ) THEN  
         std_dev = sqrt(g_del_diff/nRuns)

         open(nout3,FILE='out_answers.txt',STATUS='UNKNOWN',
     |        ACCESS='SEQUENTIAL',FORM='FORMATTED')


         write(nout3,600) g_ntracSum
 600     format(//,'Total tracks          = ', f20.1 )

         write(nout3,601) progWallClockTime
 601     format(//,'progTime              = ', f20.2,' sec') 


         write(nout3,605) 
 605     format(//,'Sequoia Benchmark Version 1.0') 
    
         write(nout3,602) g_ntracSum/progWallClockTime 
 602     format(//,'Total tracks per sec. = ', f20.2)

         write(nout3,603) avg_enescSum
 603     format(//,'avg. esc. prob.       = ', f20.6)

         write(nout3,604) std_dev
 604     format(//,'std dev               = ', f20.6)

         close(nout3)

       END IF  



 1001 CONTINUE

      CALL MPI_FINALIZE( ierr )

      STOP
      END
