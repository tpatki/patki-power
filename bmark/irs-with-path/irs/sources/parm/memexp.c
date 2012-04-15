#include "irs.h"
#include "irsreg.h"
#include "irsblk.h"
#include "irscom.h"
#include "irsctl.h"
#include "irsobjects.h"
#include "irsparm.h"
#include "irsrgst.h"
#include "BiQuadradic.hh"
#include "CycleMesg.h"
#include "FreqMesg.h"
#include "Gparm.h"
#include "Hash.h"
#include "ProblemArray.h"
#include "Region.h"
#include "Source.h"
#include "TimePlot.h"
void memexp( void )
{
   char *me = "memexp";
   char msg[128];
   int i, j, ir, my_maxtpdata;
   ProblemArray_del_all(NULL);
   if (lnbuf == NULL) {
     lnbuf = MALLOT(char, MAXLINE);
     memset(lnbuf,'\0',MAXLINE);
     line = lnbuf;
   }
   GlobalArrays_register();
   domain_attr();
   domains = Domain_construct(nblkx); 
   rgst_add("domains", "Domain_t *", &domains, "nblk");
   decomp_new(nblkx, nblkx);
   fq   = ALLOT(FreqMesg_t, maxtimeplot + 1) ;
   fqtp = ALLOT(int,        maxtimeplot + 1) ;
   for ( i = 0 ; i < maxtimeplot ; i++ ) {
      fqtp[i] = -1 ;
   }
   rgst_add("freqMesgData","FreqMesg_t *",&fq,"nfq");
   cyc   = ALLOT(CycleMesg_t, maxcycleplot + 1) ;
   cyctp = ALLOT(int,         maxcycleplot + 1) ;
   for ( i = 0 ; i < maxcycleplot ; i++ ) {
      cyctp[i] = -1 ;
   }
   rgst_add("cycleMesgData","CycleMesg_t *",&cyc,"ncyc");
   gparm = REALLOT(gparm, Gparm_t, ngparmx + 1) ;
   rgst_add("gparmData","Gparm_t *",&gparm,"ngparm");
   if (reg != NULL) ctlerror(me,gv_errmsg_not_null);
   nregxplus1 = nregx + 1;
   reg = Region_construct(nregxplus1);
   rgst_add("regionalData", "Region_t *", &reg, "nregxplus1");
   rgst_add_attr(A_OBJECT, "regionalData", "RegionalEditObject");
   src = Source_construct(nsrcx + 1);
   rgst_add("sourceData","Source_t *",&src,"nsrc");
   ptab = ALLOT(BiQuadradic_t,nbqx + 1) ;
   etab = ALLOT(BiQuadradic_t,nbqx + 1) ;
   ktab = ALLOT(BiQuadradic_t,nbqx + 1) ;
   stab = ALLOT(BiQuadradic_t,nbqx + 1) ;
   rgst_add("ptabData","BiQuadradic_t *",&ptab,"nbq");
   rgst_add("etabData","BiQuadradic_t *",&etab,"nbq");
   rgst_add("ktabData","BiQuadradic_t *",&ktab,"nbq");
   rgst_add("stabData","BiQuadradic_t *",&stab,"nbq");
   maxtpdata = MAX(maxtimeplot + maxcycleplot, maxtpdata);
   if (tpdata != NULL) ctlerror(me,gv_errmsg_not_null);
   tpdata = ALLOT(TimePlot_t *, maxtpdata) ;
   for (i=0; i<maxtpdata; i++) { tpdata[i] = NULL; }
   rgst_add("timePlotData","TimePlot_t **",&tpdata,"maxtpdata");
   GlobalArrays_allot(NULL);
} 
