#include "irs.h"
#include "irslag.h"
#include "irsdmp.h"
#include "irsedits.h"
#include "irsrgst.h"
#include "irscom.hh"
#include "BlockMapping.h"
#include "Command.h"
#include "FunctionTimer.h"
#include "Rgst.h"
#include "Tagorder.hh"
#include "TimeStepControl.h"
#include "Tracer.h"
int initcom( char *dmpname, int mdmpflag )
{
   char *me = "initcom";
   char *kern, *rem;
   char msg[MAXLINE];
   int i, iblk, gblk, ierr;
   int mynblk, mycyc;
   int error = 0;
   int paragen;
   int namelen;
   int numBlocks, numDomains;
   int *domainFiles;
#ifdef SILO
   DBfile *idbid;
#endif
   RGST_AttributeElem_t *func;
   paragen = 0;
   if ((ifparallel) && (dmpname == NULL)) paragen = 1;
   if ((ifparallel) && (paragen == 0)) {
      comlock(dmp_nbaton);
      if (mdmpflag) {
         kern = strtok(dmpname,"-");
         rem  = strtok(NULL,"-");
         mycyc = atoi(rem);
         RestartCycle = mycyc;
         strcpy(RestartKernel,kern);
#ifdef SILO
         rootfile_read(kern, mycyc);
#endif
         ifparallel = 1;
      } else {
         namelen = strlen(dmpname);
         if (namelen > 10) {
            strncpy(RestartKernel,dmpname,namelen - 10);
            RestartKernel[namelen - 9] = '\0';
            strncpy(msg,dmpname + namelen - 10, 5);
            msg[6] = '\0';
            RestartCycle = atoi(msg);
         } else {
         }
#ifdef SILO
         idbid = DBOpen (dmpname, DB_PDB, DB_READ);
         if (idbid == NULL) {
            error = 1 ;
            sprintf(msg,"Can't open dump %s\n",dmpname);
            ctlwarning(me,msg);
            return(error) ;
         }
         decomp_setdir(idbid);
         error = DBReadVar(idbid,"NumBlocks",&numBlocks);
         error = DBReadVar(idbid,"NumDomains",&numDomains);
         decomp_new(numBlocks, numDomains);
         decomp_read(idbid, msg, 0, 0);
         error += DBSetDir(idbid, "/");  
         Restart_read_global(idbid);

	 dmpattr_set();
	 domainFiles = MALLOT(int, gnblk);
	 for (gblk = 0; gblk < gnblk; gblk++) {  
	    domainFiles[gblk] = gmap[gblk].lblk;
	 }
         ifparallel = TRUE;
         calculate_mappings();
         mynblk = 0;
         for (gblk = 0; gblk < gnblk; gblk++) {
            if (gmap[gblk].proc != myid) continue;
            iblk = gmap[gblk].lblk;
	    Restart_read_domain(idbid, domainFiles[gblk], iblk); 
            mynblk++;
         }
	 nblk = mynblk;
	 DBClose(idbid);
	 dmpattr_unset();
         FREEMEM(domainFiles);
#endif
      }
      comunlock(dmp_nbaton);
   }
   if (gnblk < num_procs) {
      ctlnotice(me, "Number of domains is less than the number of processors");
   }
   if (nblk == 0) {
      sprintf(msg,"Process %i has not been allocated any domains.",myid);
      ctlwarning(me,msg);
   }
   for (iblk = 0; iblk < nblk; iblk++) {
      if (domains[iblk].nbnd > 0) { 
         ifcom=TRUE; 
      }
   }
   if (ifparallel) ifcom = TRUE;
   if (ifvsame) {
      if (paragen) {
         ctlerror(me,"Vsame boundaries do not yet work with parallel generation.\n");   
      }
      vsame_order = ALLOT(Tagorder_t,vsame_max_id);
      vsame_procs = ALLOT(int,vsame_max_id);
      for (i = 0; i < vsame_max_id; i++) {
         vsame_order[i].len = 0;
         vsame_procs[i] = 0;
      }
      setvsameorder();   
   }
   if (ifcom) {
     allotcom();
     initbuforder();
   }
   if ((ifcom) && (!paragen)) {
      initcombufs();
      varcom_bufinit();
   }
   if ((ifparallel) && (!paragen)) {
      com_start_time   = MPI_Wtime_Wrapper();
      com_physics_time = 0;
      genmd = -1;
      error += qbnd(FULL_STEP,COM_RECV);
      error += qbnd(FULL_STEP,COM_SEND);
      error += qbnd(FULL_STEP,COM_WAIT_RECV);
      TimeStepControl_initialize();
      for (iblk = 0; iblk < nblk; iblk++) {
         updateblk(  &domains[iblk], 0, 0.0 ) ;
      }
 ; 
      error += qbnd(FULL_STEP,COM_WAIT_SEND);
      func = rgst_list_attr(A_OBJECT, "Function_Gen");
      while (func != NULL) {
         Command_t *cp = (Command_t *) func->rgst_obj->obj;
         (*(cp->proc))();  
         func = func->next;
      }
      genmd = 0;
      error += editor( FULL_STEP ) ;
   }
   hash_optimize_all();
   return(error);
}
