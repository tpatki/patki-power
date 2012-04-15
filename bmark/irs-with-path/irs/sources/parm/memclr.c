#include "irs.h"
#include "irsblk.h"
#include "irscom.h"
#include "irsctl.h"
#include "irsedits.h"
#include "irsobjects.h"
#include "irsparm.h"
#include "irsrgst.h"
#include "BiQuadradic.h"
#include "Command.h"
#include "Conditional.h"
#include "CycleMesg.h"
#include "FunctionTimer.h"
#include "Gparm.h"
#include "Hash.h"
#include "NodeList.h"
#include "ProblemArray.h"
#include "Rgst.h"
#include "Region.h"
#include "Spline.h"
#include "Tracer.h"
#include "TimePlot.h"
#include "TimeStepControl.h"
#include "UserList.h"
void memclr( void )
{
   char *me = "memclr";
   char msg[256], **names = NULL;
   int iblk,i,j,k,len2,num_tp_curs,icur, num_edits, num_tpc, num_tp;
   TimePlotCurve_t *tpc_ptr = NULL;
   TimePlot_t *tp_ptr = NULL;
   RGST_AttributeElem_t *func;
   if (domains != NULL) {
     for ( iblk = 0 ; iblk < nblk ; iblk++ ) {
        domain_free(&domains[iblk]);
     }
   }
   spline_free();
   decomp_free();
   NodeList_free();
   conditionals_free();
   species_free();
   TimeStepControl_free(NULL);
   FunctionTimer_free(gv_hash_tbl);
   FunctionTimer_ht_remove(gv_hash_tbl, "global");
   FunctionTimer_ht_setup (gv_hash_tbl, "global");
   UserList_free();
   if (ifcom) freecom();
   FREEMEM(lnbuf);
   line = NULL;
   GlobalArrays_free(NULL);
   func = rgst_list_attr(A_OBJECT, "Function_Free");
   while (func != NULL) {
      Command_t *cp = (Command_t *) func->rgst_obj->obj;
      (*(cp->proc))(NULL);
      func = func->next;
   }
   if (rgst_check_for_obj("sourceData") == TRUE)  {
     rgst_del("sourceData");
     for ( i = 0 ; i < nsrc ; i++ ) {
       if (src[i].nzsrc  > 0) { FREEMEM(src[i].ndxsrc) ; }
       if (src[i].nidat1 > 0) { FREEMEM(src[i].idat1) ; }
       if (src[i].nfdat1 > 0) { FREEMEM(src[i].fdat1) ; }
       if (src[i].ndat2  > 0) { FREEMEM(src[i].dat2) ; }
     }
     FREEMEM(src) ;
   }
   nsrc = 0;
   if (rgst_check_for_obj("freqMesgData") == TRUE) {
     rgst_del("freqMesgData");
     for ( i = 0 ; i < nfq ; i++ ) {
       rgst_del (fq[i].name);
       FREEMEM(fq[i].msg) ;
       FREEMEM(fq[i].name) ;
     }
     FREEMEM(fq) ;
     FREEMEM(fqtp) ;
   }
   nfq = 0;
   if (rgst_check_for_obj("cycleMesgData") == TRUE) {
     rgst_del("cycleMesgData");
     for ( i = 0 ; i < ncyc ; i++ ) {
       rgst_del (cyc[i].name);
       FREEMEM(cyc[i].msg) ;
       FREEMEM(cyc[i].name) ;
     }
     FREEMEM(cyc) ;
     FREEMEM(cyctp) ;
   }
   ncyc = 0;
   if (rgst_check_for_obj("gparmData") == TRUE) {
     rgst_del("gparmData");
     FREEMEM(gparm);
   }
   if (rgst_check_for_obj("timePlotData") == TRUE) {
     rgst_del("timePlotData");
     for (i=0 ; i<ntp ; i++) {
       for (icur=0; icur<tpdata[i]->num_tp_curs; icur++) {
         rgst_del(tpdata[i]->tp_curs[icur]->name);
         TimePlotCurve_destruct(tpdata[i]->tp_curs[icur]);
       }
       rgst_del(tpdata[i]->name);
       TimePlot_destruct(tpdata[i]);
     }
     FREEMEM(tpdata);
   }
   ntp = 0;
   Region_free();
   if (ptab != NULL) rgst_del("ptabData");
   if (etab != NULL) rgst_del("etabData");
   if (ktab != NULL) rgst_del("ktabData");
   if (stab != NULL) rgst_del("stabData");
   FREEMEM(ptab);
   FREEMEM(etab);
   FREEMEM(ktab);
   FREEMEM(stab);
   nbq = 0;
   if (rgst_check_for_obj("domains") == TRUE) {
      rgst_del("domains");
   }
   FREEMEM(domains);       
   names = rgst_list_objs_by_type( &num_tp, "TimePlot_t");
   for (i = 0; i<num_tp; i++) {
     ctlwarning(me,"shawn, why are there time plots left, they should have"
              "been removed by now");
     tp_ptr = rgst_get_t(names[i],"TimePlot_t");
     if (tp_ptr == NULL) ctlerror(me,logic_err);
     rgst_del(names[i]);
     tp_ptr = TimePlot_destruct(tp_ptr);
     FREEMEM(names[i]);
   }
   FREEMEM(names);
   hash_del_objs_of_type(gv_hash_tbl,"double",NULL);
#ifdef DEBUG
   hash_print_by_type(rgst_objs_hash_tbl); 
   hash_print_by_type(gv_hash_tbl);
#endif
}
int memclr_input(int mode) {
   int ifparallel_save = ifparallel;	 
   int ifthreads_save  = ifthreads;	 
   char pbnm_save[MAXLINE];
   char *me = "memclr_input";
   strcpy(pbnm_save,pbnm);
   memclr();
   FunctionTimer_ht_remove(gv_hash_tbl, "global");
   ProblemArray_del_all(NULL);
   rgst_cleanup();
   genmd = -1;
   if (rgst_init() != 0) {
     ctlerror(me,"Registry initialization failed");
   }
   parminit();
   inst_com();
   ifparallel = ifparallel_save;
   ifthreads  = ifthreads_save;
   strcpy(pbnm,pbnm_save);
   if (mode == 1) {
      newfile(inputDeck,1);
   }
   return(0);
}
