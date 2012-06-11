#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/time.h>
#include "irs.h"
#include "irsbndry.h"
#include "irscom.h"
#include "irsctl.h"
#include "irsdmp.h"
#include "irsedits.h"
#include "irseos.h"
#include "irslag.hh"
#include "irsreg.h"
#include "irssrc.h"
#include "irssys.h"
#include "irstdiff.h"
#include "CycleMesg.h"
#include "Source.h"
#include "FunctionTimer.h"
#include "TimeStepControl.h"
int xirs( int    ncycle,  
           double ntime  ) 
{
   char *me = "xirs";
   char package[MAXLINE];
   char msg[MAXLINE];
   int my_nblk = nblk;
   int i, error, iblk, ifsus2,  fdforstdin, nready, maxndtg ;
   int ifsus = 0, newSubcycleCount, rdifit_sum, edifit_sum, idifit_sum ;
   unsigned long elapsed_clocks;
   double        elapsed_secs;
   double timestart, cpu, esave, kesave, iesave, halfDeltatSubcycle, deltatSum ;
   double runtime;
   double dtgtemp, deltatLastSubcycle, currentDeltat, depositionFraction ;
   double deltatSubcycleStart ;
   fd_set readfds;
   struct timeval timeout ;
   FT_INITIALIZE(me, gv_hash_tbl)
   error = 0 ;
   cpu = getcpu() ;
   if (ifparallel) {
      timestart = MPI_Wtime_Wrapper() ;
   }
   while ( (cycle < ncycle) && (ttime < ntime) && (error == 0) ) {
	
#ifdef TERRY_TRACE
   if (terry_trace_flag == TRUE) {
	IRS_ROUTINE1_cntr++;
	TRCHKGT(ENTERING_IRS_ROUTINE1, cycle, IRS_ROUTINE1_cntr, 0, 0, 0); 
   } 
#endif
#ifdef HPMCOUNTERS
        hpmStart(HPM_IRS_ROUTINE1, "IRS_ROUTINE1");
#endif

      InitCycle() ;
#include "pardo.h"
      for ( iblk = 0 ; iblk < my_nblk ; iblk++ ) {
         erate( ttime, deltat, NULL, 1, &domains[iblk] ) ;
         SourceNew_energyrate( NULL, domains[iblk].den, 
	                       "SourceEnergyRateRadiation",
                                ttime, deltat, &domains[iblk], _SourceEdit_);
      }
      if ( ngroup > 0 ) {
#include "pardo.h"
         for ( iblk = 0 ; iblk < my_nblk ; iblk++ ) {
            CalcDtSource( &domains[iblk] ) ;
         }
      }

#ifdef HPMCOUNTERS
        hpmStop(HPM_IRS_ROUTINE1);
#endif
#ifdef TERRY_TRACE
   if (terry_trace_flag == TRUE) {
	TRCHKGT(EXITING_IRS_ROUTINE1, cycle, IRS_ROUTINE1_cntr, 0, 0, 0); 
	IRS_ROUTINE2_cntr++;
	TRCHKGT(ENTERING_IRS_ROUTINE2, cycle, IRS_ROUTINE2_cntr, 0, 0, 0); 
   } 
#endif
#ifdef HPMCOUNTERS
        hpmStart(HPM_IRS_ROUTINE2, "IRS_ROUTINE2");
#endif

      PreSubcycle() ;
      deltatSubcycleStart = deltatSubcycle ;
      deltatSum  = 0.0 ;
      ndtg       = 0 ;
      rdifit_sum = 0 ;
      edifit_sum = 0 ;
      idifit_sum = 0 ;

#ifdef HPMCOUNTERS
        hpmStop(HPM_IRS_ROUTINE2);
#endif
#ifdef TERRY_TRACE
   if (terry_trace_flag == TRUE) {
	TRCHKGT(EXITING_IRS_ROUTINE2, cycle, IRS_ROUTINE2_cntr, 0, 0, 0); 
   } 
#endif

      while ( deltatSum < (0.9999 * deltat) ) {

#ifdef TERRY_TRACE
   if (terry_trace_flag == TRUE) {
	IRS_ROUTINE3_cntr++;
	TRCHKGT(ENTERING_IRS_ROUTINE3, cycle, IRS_ROUTINE3_cntr, 0, 0, 0); 
   } 
#endif
#ifdef HPMCOUNTERS
        hpmStart(HPM_IRS_ROUTINE3, "IRS_ROUTINE3");
#endif

         ndtg++ ;
         deltatSum += deltatSubcycle ;
         if ( ndtg > maxsubcycles ) {
            error = 1 ;
	    sprintf( package, "Subcycling" ) ;
            break ;
         }
         halfDeltatSubcycle = 0.5 * deltatSubcycle ;
         if ( (iftmode == 1) || (iftion == 1) ) {
            DtTempInitialize() ;
	 }

#ifdef HPMCOUNTERS
        hpmStop(HPM_IRS_ROUTINE3);
#endif
#ifdef TERRY_TRACE
   if (terry_trace_flag == TRUE) {
	TRCHKGT(EXITING_IRS_ROUTINE3, cycle, IRS_ROUTINE3_cntr, 0, 0, 0); 
	IRS_ROUTINE4_cntr++;
	TRCHKGT(ENTERING_IRS_ROUTINE4, cycle, IRS_ROUTINE4_cntr, 0, 0, 0); 
   } 
#endif
#ifdef HPMCOUNTERS
        hpmStart(HPM_IRS_ROUTINE4, "IRS_ROUTINE4");
#endif

#include "pardo.h"
         for ( iblk = 0 ; iblk < my_nblk ; iblk++ ) {
            RegionTableAllocate( &domains[iblk], reg, nreg ) ;
            RegionTableInitialize( &domains[iblk], reg, nreg, 
                                    domains[iblk].specfrac ) ;
	    if ( ioneq == 1 ) {
               zstarcal( domains[iblk].den, domains[iblk].tmat,
                        &domains[iblk] ) ;
            }
         }

#ifdef HPMCOUNTERS
        hpmStop(HPM_IRS_ROUTINE4);
#endif
#ifdef TERRY_TRACE
   if (terry_trace_flag == TRUE) {
	TRCHKGT(EXITING_IRS_ROUTINE4, cycle, IRS_ROUTINE4_cntr, 0, 0, 0); 
	IRS_ROUTINE5_cntr++;
	TRCHKGT(ENTERING_IRS_ROUTINE5, cycle, IRS_ROUTINE5_cntr, 0, 0, 0); 
   } 
#endif
#ifdef HPMCOUNTERS
        hpmStart(HPM_IRS_ROUTINE5, "IRS_ROUTINE5");
#endif
	
         depositionFraction = halfDeltatSubcycle / deltat ;
         if ( (ngroup == 1) || (ifedif == 1) || (ifidif == 1) ) {
            tdiff( halfDeltatSubcycle, (ttime+halfDeltatSubcycle),
                   depositionFraction ) ;
          } else if ( ngroup >= 1 ) {
 ; 
         }
         rdifit_sum += rdifit ;
         edifit_sum += edifit ;
         idifit_sum += idifit ;
 ;          if (error ) {
            break ;
	 }

#ifdef HPMCOUNTERS
        hpmStop(HPM_IRS_ROUTINE5);
#endif
#ifdef TERRY_TRACE
   if (terry_trace_flag == TRUE) {
	TRCHKGT(EXITING_IRS_ROUTINE5, cycle, IRS_ROUTINE5_cntr, 0, 0, 0); 
	IRS_ROUTINE6_cntr++;
	TRCHKGT(ENTERING_IRS_ROUTINE6, cycle, IRS_ROUTINE6_cntr, 0, 0, 0); 
   } 
#endif
#ifdef HPMCOUNTERS
        hpmStart(HPM_IRS_ROUTINE6, "IRS_ROUTINE6");
#endif

         if ( (ngroup > 0) || (ifedif == 1) || (ifidif == 1) ) {
            EosDriver( (ttime+deltatSubcycle), deltatSubcycle ) ;
	 }
         if ((ngroup == 1) || (ifedif == 1) || (ifidif == 1) ) {
            tdiff( halfDeltatSubcycle, (ttime+deltatSubcycle),
                   depositionFraction ) ;
          } else if ( ngroup >= 1 ) {
 ; 
         }
         rdifit_sum += rdifit ;
         edifit_sum += edifit ;
         idifit_sum += idifit ;

#ifdef HPMCOUNTERS
        hpmStop(HPM_IRS_ROUTINE6);
#endif
#ifdef TERRY_TRACE
   if (terry_trace_flag == TRUE) {
	TRCHKGT(EXITING_IRS_ROUTINE6, cycle, IRS_ROUTINE6_cntr, 0, 0, 0); 
	IRS_ROUTINE7_cntr++;
	TRCHKGT(ENTERING_IRS_ROUTINE7, cycle, IRS_ROUTINE7_cntr, 0, 0, 0); 
   } 
#endif
#ifdef HPMCOUNTERS
        hpmStart(HPM_IRS_ROUTINE7, "IRS_ROUTINE7");
#endif

         if ( (ngroup == 0) && (iftion == 1) ) {
#include "pardo.h"
            for ( iblk = 0 ; iblk < my_nblk ; iblk++ ) {
               RegionTableInitialize( &domains[iblk], reg, nreg, 
                                       domains[iblk].specfrac ) ;
               ChemPotCalc( domains[iblk].den, domains[iblk].tmat,
                           &domains[iblk] ) ;
               teicouple( domains[iblk].emat, domains[iblk].tmat,
                          domains[iblk].dedt, domains[iblk].eion,
                          domains[iblk].tion, domains[iblk].deidt,
                          domains[iblk].den,  1.0, deltatSubcycle,
                          &domains[iblk] ) ;
            }
	 }

#ifdef HPMCOUNTERS
        hpmStop(HPM_IRS_ROUTINE7);
#endif
#ifdef TERRY_TRACE
   if (terry_trace_flag == TRUE) {
	TRCHKGT(EXITING_IRS_ROUTINE7, cycle, IRS_ROUTINE7_cntr, 0, 0, 0); 
	IRS_ROUTINE8_cntr++;
	TRCHKGT(ENTERING_IRS_ROUTINE8, cycle, IRS_ROUTINE8_cntr, 0, 0, 0); 
   } 
#endif
#ifdef HPMCOUNTERS
        hpmStart(HPM_IRS_ROUTINE8, "IRS_ROUTINE8");
#endif

#include "pardo.h"
         for ( iblk = 0 ; iblk < my_nblk ; iblk++ ) {
            RegionTableFree( &domains[iblk], reg, nreg ) ;
         }
         ttime += deltatSubcycle ;
         subcycle++ ;
         error += update( deltatSubcycle, 1 ) ;
	 if (error) {
	    sprintf( package, "update" ) ;
	    break ;
	 }
         if ( (ndeltat   < 0.9    * deltatSubcycle) &&
              (deltatSum < 0.9999 * deltat) ) {
            newSubcycleCount = (int)(1.0 + ( deltat - deltatSum ) / ndeltat);
            deltatSubcycle   = ( deltat - deltatSum ) / newSubcycleCount ;
         }

#ifdef HPMCOUNTERS
        hpmStop(HPM_IRS_ROUTINE8);
#endif
#ifdef TERRY_TRACE
   if (terry_trace_flag == TRUE) {
	TRCHKGT(EXITING_IRS_ROUTINE8, cycle, IRS_ROUTINE8_cntr, 0, 0, 0); 
   } 
#endif

      }  

#ifdef TERRY_TRACE
   if (terry_trace_flag == TRUE) {
      	IRS_ROUTINE9_cntr++;
	TRCHKGT(ENTERING_IRS_ROUTINE9, cycle, IRS_ROUTINE9_cntr, 0, 0, 0); 
   } 
#endif
#ifdef HPMCOUNTERS
        hpmStart(HPM_IRS_ROUTINE9, "IRS_ROUTINE9");
#endif

      if ( error ) {
         break ;
      }
      rdifit = rdifit_sum ;
      edifit = edifit_sum ;
      idifit = idifit_sum ;
      delcyc++ ;
      deltatLastSubcycle = deltatSubcycle ;
      deltatSubcycle     = ndeltat ;
      if ( deltatSubcycle > dtfc * deltatSubcycleStart ) {
         deltatSubcycle = dtfc * deltatSubcycleStart ;
         dtcon[0] = '0'  ; 
         dtcon[1] = '\0' ;
      }
      if ( deltatSubcycle > dtmax ) {
         deltatSubcycle = dtmax ;
         dtcon[0] = '0'  ; 
         dtcon[1] = '\0' ;
      }
      currentDeltat = deltat  ;
      TimeStepControl_getmin( "SubCycleTimeStepControl", &deltat ) ;
      if ( deltat == plarge ) {
         deltat = deltatSubcycle ;
      }
      deltat  = MIN( deltat, dtmax ) ;
      dtgtemp = 0.5 + deltat / deltatSubcycle ;
      if ( dtgtemp > (double)ndtgx ) {
         maxndtg = ndtgx ;
      } else {
         maxndtg = (int)dtgtemp ;
      }
      if ( maxndtg <     1 ) maxndtg = 1     ;
      if ( maxndtg > ndtgx ) maxndtg = ndtgx ;
      deltatSubcycle = MIN( deltatSubcycle, (deltat / (double)maxndtg) ) ;
      deltat         = maxndtg * deltatSubcycle ;

#ifdef HPMCOUNTERS
        hpmStop(HPM_IRS_ROUTINE9);
#endif
#ifdef TERRY_TRACE
   if (terry_trace_flag == TRUE) {
	TRCHKGT(EXITING_IRS_ROUTINE9, cycle, IRS_ROUTINE9_cntr, 0, 0, 0); 
	IRS_ROUTINE10_cntr++;
	TRCHKGT(ENTERING_IRS_ROUTINE10, cycle, IRS_ROUTINE10_cntr, 0, 0, 0); 
   } 
#endif
#ifdef HPMCOUNTERS
        hpmStart(HPM_IRS_ROUTINE10, "IRS_ROUTINE10");
#endif

      PostSubcycle( deltat, deltatLastSubcycle ) ;
      if ( (ifparallel) && (error != 0) ) {
         sprintf(msg,"Physics package %s returned error - exiting.",package);
         ctlerror(me,msg);
      }
      cycle++ ;
      mpi_reset_cntrs(cycle);

#ifdef HPMCOUNTERS
        hpmStop(HPM_IRS_ROUTINE10);
#endif
#ifdef TERRY_TRACE
   if (terry_trace_flag == TRUE) {
	TRCHKGT(EXITING_IRS_ROUTINE10, cycle, IRS_ROUTINE10_cntr, 0, 0, 0); 
	IRS_ROUTINE11_cntr++;
	TRCHKGT(ENTERING_IRS_ROUTINE11, cycle, IRS_ROUTINE11_cntr, 0, 0, 0); 
   } 
#endif
#ifdef HPMCOUNTERS
        hpmStart(HPM_IRS_ROUTINE11, "IRS_ROUTINE11");
#endif

#ifndef TFLOPS
      ifsus = 0 ;
      if ( myid == 0 ) {
         timeout.tv_sec  = 0 ;
         timeout.tv_usec = 0 ;
         fdforstdin = fileno(stdin) ;
         FD_ZERO(&readfds) ;
         FD_SET(fdforstdin, &readfds) ;
         nready = select(fdforstdin + 1, &readfds, NULL, NULL, &timeout) ;
         if ( nready > 0 ) {
            ifsus = prirup() ;
         }
      }
#endif
      if (myid == 0) {
         ifsus2 = irspcs_check();
         if (ifsus2 != 0) {
            ifsus = 3;
            sprintf(msg,"DPCS has issued a stop message.");
            ctlwarning(me,msg);
         }
      }
      if ( runtime_max >= 0.0 ) {
         runtime = getruntime();
         if (runtime >= runtime_max) {
            ifsus = 3;
            sprintf( msg, "Runtime of %f minutes exceeded maximum of %f",
                     runtime/60.0, runtime_max/60.0 ) ;
            ctlmsg(msg) ;
         }
      }

#ifdef HPMCOUNTERS
        hpmStop(HPM_IRS_ROUTINE11);
#endif
#ifdef TERRY_TRACE
   if (terry_trace_flag == TRUE) {
	TRCHKGT(EXITING_IRS_ROUTINE11, cycle, IRS_ROUTINE11_cntr, 0, 0, 0); 
	IRS_ROUTINE12_cntr++;
	TRCHKGT(ENTERING_IRS_ROUTINE12, cycle, IRS_ROUTINE12_cntr, 0, 0, 0); 
   } 
#endif
#ifdef HPMCOUNTERS
        hpmStart(HPM_IRS_ROUTINE12, "IRS_ROUTINE12");
#endif

      if (ifparallel) {
         combcast(&ifsus,1,COM_INT,0) ;
      }

#ifdef HPMCOUNTERS
        hpmStop(HPM_IRS_ROUTINE12);
#endif
#ifdef TERRY_TRACE
   if (terry_trace_flag == TRUE) {
	TRCHKGT(EXITING_IRS_ROUTINE12, cycle, IRS_ROUTINE12_cntr, 0, 0, 0); 
	IRS_ROUTINE13_cntr++;
	TRCHKGT(ENTERING_IRS_ROUTINE13, cycle, IRS_ROUTINE13_cntr, 0, 0, 0); 
   } 
#endif
#ifdef HPMCOUNTERS
        hpmStart(HPM_IRS_ROUTINE13, "IRS_ROUTINE13");
#endif

      if ( ifsus == 1 ) {

#ifdef SILO
         Restart_write(0) ;
#endif
         ifsus = TERMFLG_READY ;
      } else if ( ifsus == 2 ) {

#ifdef SILO
         wgdmp() ;
#endif
         ifsus = TERMFLG_READY ;
      } else if ( ifsus == 3 ) {
#ifdef SILO
         Restart_write(0) ;
#endif
         ifsus  = TERMFLG_TIME ;
         break ;
      } else if ( ifsus == -1 ) {
         ifsus = TERMFLG_USERSTOP ;
         break ;
      } else if ( ifsus == -2 ) {
         ifsus = TERMFLG_EXIT;
         break;
      }

#ifdef HPMCOUNTERS
        hpmStop(HPM_IRS_ROUTINE13);
#endif
#ifdef TERRY_TRACE
   if (terry_trace_flag == TRUE) {
	TRCHKGT(EXITING_IRS_ROUTINE13, cycle, IRS_ROUTINE13_cntr, 0, 0, 0); 
   } 
#endif

   } 


#ifdef TERRY_TRACE
   if (terry_trace_flag == TRUE) {
	IRS_ROUTINE14_cntr++;
	TRCHKGT(ENTERING_IRS_ROUTINE14, cycle, IRS_ROUTINE14_cntr, 0, 0, 0); 
   } 
#endif
#ifdef HPMCOUNTERS
        hpmStart(HPM_IRS_ROUTINE14, "IRS_ROUTINE14");
#endif

   if ( error != 0 ) {
      sprintf(msg,"Physics package %s returned error - exiting.",package);
      printtc() ;
      ctlerror(me,msg);
   }

   error += editor( FULL_STEP ) ;
   runcpu = runcpu + getcpu() - cpu ;

   if (ifparallel) {
      com_physics_time += MPI_Wtime_Wrapper() - timestart ;
   }

#ifdef HPMCOUNTERS
        hpmStop(HPM_IRS_ROUTINE14);
#endif
#ifdef TERRY_TRACE
   if (terry_trace_flag == TRUE) {
	TRCHKGT(EXITING_IRS_ROUTINE14, cycle, IRS_ROUTINE14_cntr, 0, 0, 0); 
   } 
#endif

   FT_FINALIZE(me, gv_hash_tbl, 1)
   return(ifsus) ;
}
