#include "irs.h"
#include "irsblk.h"
#include "irsbndry.h"
#include "irscom.h"
#include "irsctl.h"
#include "BlockMapping.h"
#include "FunctionTimer.h"
int  blockin0( int type ) {
   char *me = "blockin0";
   char op[10],msg[MAXLINE];
   int cflag;
   int imax, jmax, kmax;
   int gblk;
   if (nblk >= nblkx-1) {
      sprintf(msg,"number of blocks exceeds nblkx = %d",nblkx);
      ctlwarning(me,msg);
      return(1);
   }
   if ((type == QUAD2D) && (ndims == 3)) {
      sprintf(msg,"You are specifying a 2D mesh in a 3D problem.\n\t\tYou might want to use hex instead of the quad command.");
      ctlerror(me,msg);
   }
   if ((type == HEX3D) && (ndims == 2)) {
      sprintf(msg,"You are specifying a 3D mesh in a 2D problem.\n\t\tYou might want to use quad instead of the hex command.\n\t\tOr you might want to set ndims to 3.");
      ctlerror(me,msg);
   }
   if (type == QUAD2D) {
      imax = geti(&cflag) + NPNL - 1;
      jmax = geti(&cflag) + NPNL - 1;
      domains[nblk].type = QUAD2D ;
      domains[nblk].imin = NPNL ;
      domains[nblk].jmin = NPNL ;
      domains[nblk].kmin = 0 ;
      domains[nblk].imax = imax;
      domains[nblk].jmax = jmax;
      domains[nblk].kmax = 0 ;
   }  else if (type == HEX3D) {
      imax = geti(&cflag) + NPNL - 1;
      jmax = geti(&cflag) + NPNL - 1;
      kmax = geti(&cflag) + NPNL - 1;
      domains[nblk].type = HEX3D ;
      domains[nblk].imin = NPNL ;
      domains[nblk].jmin = NPNL ;
      domains[nblk].kmin = NPNL ;
      domains[nblk].imax = imax;
      domains[nblk].jmax = jmax;
      domains[nblk].kmax = kmax;
   } else {
      sprintf(msg,"unknown block type '%s'",op);
      ctlwarning(me,msg);
      return(1);
   }
   if (ifparallel) {
       if (unblk > 1) {
         sprintf(msg,"You may not use parallel mesh generation on multi-block problems.");
         ctlerror(me,msg);
      }
      blknum = unblk ;
      domains[nblk].jp = domains[nblk].imax - domains[nblk].imin + 
                         1 + NPNL + NPNR;
      domains[nblk].kp = 0;
      if (ndims == 3) {
         domains[nblk].kp = domains[nblk].jp * (domains[nblk].jmax - 
	                    domains[nblk].jmin + 1 + NPNL + NPNR);
      }
      setumap( &domains[nblk] ) ;
      peekc(op);
      if (strcmp(op,"blkdiv")) {
         if (nblkx <= num_procs) {
            sprintf(msg,"Number of domains (%i) exceeds nblkx (%i).  Please increase nblkx.",num_procs,nblkx);
            ctlerror(me,msg);
         }
         blkdivin(1);
      } else {
         geta(op);
         blkdivin(0);
      } 
      if (nblkx <= num_procs) {
         sprintf(msg,"Number of domains (%i) exceeds nblkx (%i).  Please increase nblkx.",num_procs,nblkx);
         ctlerror(me,msg);
      }
      calculate_mappings();
      for (gblk = 0; gblk < gnblk; gblk++) {
         if (gmap[gblk].proc == myid) {
            domains[nblk].type     = type ;
            domains[nblk].sclnamix = sclnamix ;
            TRSEXT(domains[nblk],gmap[gblk],gmap[gblk]);
            if (ndims == 2) {
               domains[nblk].kmin = 0;
               domains[nblk].kmax = 0;
            } 
            initblk(nblk,&domains[nblk]);
            domains[nblk].gblk = gblk;
            domain_hash_tbl_rgst(&(domains[nblk]));  
            nblk++;
         }
      }
      if (ifparallel) {
         bndry_init();
         initcom( NULL, 0);
         varcom_bufinit();
      }
   } else {
      peekc(op);
      if (!strcmp(op,"blkdiv")) {
         sprintf(msg,"blkdiv command may only appear after quad or hex during parallel \n\t\tgeneration.");
         ctlerror(me,msg);
      }
      domains[nblk].sclnamix = sclnamix ;
      initblk( nblk, &domains[nblk] ) ;
      setumap( &domains[nblk] ) ;
      blknum = nblk ;
      nblk++ ;
   }
   return(0) ;
}
