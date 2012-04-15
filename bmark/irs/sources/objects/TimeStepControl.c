#include "irs.h"
#include "irscom.h"
#include "irsctl.h"
#include "irsdmp.h"
#include "irslag.h"
#include "irsrgst.h"
#include "BlockMapping.h"
#include "AEStackElm.h"
#include "FunctionTimer.h"
#include "Hash.h"
#include "NodeList.h"
#include "Rgst.h"
#include "TimeStepControl.h"
void TimeStepControl_register(char *name, char *key) {
   int iblk;
   TimeStepControl_t *tsc;
   TimeStepControl_t *tsc_g;
   tsc_g = TimeStepControl_find(name, NULL);
   if (tsc_g == NULL)  {
      tsc_g = MALLOT(TimeStepControl_t,1);
      TimeStepControl_init(tsc_g);
      tsc_g->value = plarge;
      strcpy(tsc_g->name,name);
      strcpy(tsc_g->key,key);
      TimeStepControl_add(tsc_g, NULL);
   }
   for (iblk = 0; iblk < nblk; iblk++) {
      tsc = TimeStepControl_find(name, domains[iblk].hash);
      if (tsc == NULL) {
         tsc = MALLOT(TimeStepControl_t,1);
         strcpy(tsc->name,name);
         strcpy(tsc->key,key);
         tsc->value = tsc_g->value;
         tsc->block = tsc_g->block;
         tsc->i     = tsc_g->i;
         tsc->j     = tsc_g->j;
         tsc->k     = tsc_g->k;
         TimeStepControl_add(tsc, domains[iblk].hash);
      }
   }
}
void TimeStepControl_add( TimeStepControl_t *tsc, HashTable_t *hash ) 
{
   char msg[MAXLINE];
   if (hash == NULL) {
      if (rgst_check_for_obj(tsc->name)) {
         sprintf(msg,"Attempting to add an already existing time step control - %s",tsc->name);
         ctlerror("TimeStepControl_add",msg);
      }
      rgst_add(tsc->name,"TimeStepControl_t", tsc, NULL);
      hash_add(tsc->name,"TimeStepControl_t", tsc, gv_hash_tbl);
   } else {
      hash_add(tsc->name,"TimeStepControl_t", tsc, hash);
   } 
}
TimeStepControl_t *TimeStepControl_find( char *name, HashTable_t *hash ) 
{
   TimeStepControl_t *tsc = NULL;
   if (hash == NULL) {
      tsc = (TimeStepControl_t *) rgst_get_t(name, "TimeStepControl_t");
   } else {
      tsc = (TimeStepControl_t *) hash_lookup_obj(name, hash);
   } 
   return(tsc);
}
void TimeStepControl_free( HashTable_t *hash ) {
   int i, numelm;
   HashElm_t **hashelm;
   char **varlist;
   if (hash == NULL) {
      varlist = rgst_list_objs_by_type( &numelm, "TimeStepControl_t");
      if (varlist == NULL) return;
      for (i = 0; i < numelm; i++) {
          TimeStepControl_t *tsc = TimeStepControl_find(varlist[i],NULL);
          rgst_del(varlist[i]);
          hash_del2(tsc->name,"TimeStepControl_t", gv_hash_tbl);
          FREEMEM(tsc);
          FREEMEM(varlist[i]);
      }
      FREEMEM(varlist);
   } else {
      hashelm = hash_get_elm_list(&numelm, "TimeStepControl_t", hash);
      for (i = 0; i < numelm; i++) {
          TimeStepControl_t *tsc = (TimeStepControl_t *) hashelm[i]->obj;
          hash_del2(tsc->name, "TimeStepControl_t", hash);
          FREEMEM(tsc);
      }
      FREEMEM(hashelm);
   } 
}
void TimeStepControl_initialize( void ) {
   rgst_del_attr_all("SubCycleTimeStepControl");
   TimeStepControl_register("TSC_Courant","c");
   RGST_ADD_OBJECT_ATTR("TSC_Courant","ActiveTimeStepControl");
   if ( ( iftion ) || ( iftmode ) ) {
      TimeStepControl_register("TSC_Electron","e");
      RGST_ADD_OBJECT_ATTR("TSC_Electron","ActiveTimeStepControl");
   }

   if ( iftion == 1 ) {
      TimeStepControl_register("TSC_Ion","i");
      RGST_ADD_OBJECT_ATTR("TSC_Ion","ActiveTimeStepControl");
   }
   if ( ndims == 2 ) {
      TimeStepControl_register("TSC_Area","j");
      RGST_ADD_OBJECT_ATTR("TSC_Area","ActiveTimeStepControl");
   }
   if (( ngroup > 0 )  || (ifidif == 1) ||
       (ifedif == 1)) {
      TimeStepControl_register("TSC_Residual","res");
      RGST_ADD_OBJECT_ATTR("TSC_Residual","ActiveTimeStepControl");
      RGST_ADD_OBJECT_ATTR("TSC_Residual","TimeStepEdit");
   }
   if ( ngroup > 0 ) {
      TimeStepControl_register("TSC_Radiation","r");
      RGST_ADD_OBJECT_ATTR("TSC_Radiation","ActiveTimeStepControl");
      TimeStepControl_register("TSC_ElectronSource","se");
      RGST_ADD_OBJECT_ATTR("TSC_ElectronSource","ActiveTimeStepControl");
      if ( sourcesubcycle == 0 ) {
         RGST_ADD_OBJECT_ATTR("TSC_ElectronSource","SubCycleTimeStepControl");
      }
      if ( iftion == 1 ) {
         TimeStepControl_register("TSC_IonSource","si");
         RGST_ADD_OBJECT_ATTR("TSC_IonSource","ActiveTimeStepControl");
         if ( sourcesubcycle == 0 ) {
            RGST_ADD_OBJECT_ATTR("TSC_IonSource","SubCycleTimeStepControl");
	 }
      }
   }

}
void TimeStepControl_findmin( char *attr, double *dt_min ) {
   char *me = "TimeStepControl_findmin";
   char msg[MAXLINE];
   int i;
   int iblk;
   int count;
   int len;
   double mydt_min;
   double *buffer;
   RGST_AttributeElem_t *tscattr;
   RGST_AttributeElem_t *tscattr_ptr;
   NodeWindow_t *ndxin       = NULL;
   NodeList_t   *NodeList_ptr = NULL;


   tscattr = rgst_list_attr(A_OBJECT, attr); 
   tscattr_ptr = tscattr;
   count = 0;
   while (tscattr_ptr != NULL) {
      char *name             = ATTR_GET_OBJECT_NAME(tscattr_ptr)
      TimeStepControl_t *tsc = TimeStepControl_find(name,NULL);
      tsc->value = plarge;
      for (iblk = 0; iblk < nblk; iblk++) {
          TimeStepControl_t *tscb = TimeStepControl_find(name,domains[iblk].hash);
          if (tscb->value < tsc->value) {
             int gblk = domains[iblk].gblk;
             tsc->value = tscb->value;
             tsc->block = gmap[gblk].ublk;
             tsc->i     = tscb->i + gmap[gblk].imin - NPNL;
             tsc->j     = tscb->j + gmap[gblk].jmin - NPNL;
             if (ndims == 3) tsc->k     = tscb->k + gmap[gblk].kmin - NPNL;
          }
      }
      count += 5; 
      tscattr_ptr = tscattr_ptr->next;
   }
   if (ifparallel) {
      len = count * num_procs;
      buffer = ALLOT(double, len);
      tscattr_ptr = tscattr;
      len = myid * count;
      while (tscattr_ptr != NULL) {
         char *name             = ATTR_GET_OBJECT_NAME(tscattr_ptr)
         TimeStepControl_t *tsc = TimeStepControl_find(name,NULL);
         buffer[len++] = tsc->value;
         buffer[len++] = (double )tsc->block;
         buffer[len++] = (double )tsc->i;
         buffer[len++] = (double )tsc->j;
         buffer[len++] = (double )tsc->k;
         tscattr_ptr = tscattr_ptr->next;
      }
      len = count * num_procs;
      comreduce(buffer, len, COM_SUM, COM_ALL, COM_DOUBLE);
      len = 0;
      tscattr_ptr = tscattr;
      while (tscattr_ptr != NULL) {
         char *name             = ATTR_GET_OBJECT_NAME(tscattr_ptr)
         TimeStepControl_t *tsc = TimeStepControl_find(name,NULL);
         for (i = 0; i < num_procs; i++) {
            if (tsc->value > buffer[len + i * count]) {
               tsc->value =  buffer[len + i * count];
               tsc->block = (int) buffer[len + i * count + 1];
               tsc->i     = (int) buffer[len + i * count + 2];
               tsc->j     = (int) buffer[len + i * count + 3];
               tsc->k     = (int) buffer[len + i * count + 4];
            }
         }
	 len += 5;
         tscattr_ptr = tscattr_ptr->next;
      }
      FREEMEM(buffer);
   }
   mydt_min = plarge;
   tscattr_ptr = tscattr;
   while (tscattr_ptr != NULL) {
      char *name             = ATTR_GET_OBJECT_NAME(tscattr_ptr)
      TimeStepControl_t *tsc = TimeStepControl_find(name,NULL);
      int flag               = RGST_QUERY_OBJECT_ATTR(name, "TimeStepEdit");
      if (flag == 0) {
         if (mydt_min > tsc->value) {
            mydt_min  = tsc->value;
            strcpy(dtcon,tsc->key);
            dtb      = tsc->block;
            dti      = tsc->i;
            dtj      = tsc->j;
            dtk      = tsc->k;
         }
      }
      tscattr_ptr = tscattr_ptr->next;
   }
   if ( mydt_min < dtmin ) {
      if ( ndims == 2 ) {
         sprintf(msg,"\n\tTime step too small, exiting"
                      "\n\ttime  = %e, cycle = %d, ndeltat = %e"
                      "\n\tblock = %d, dti = %d, dtj = %d"
                      "\n\tcontrol = %s",
                      ttime, cycle, mydt_min, dtb, dti-NPNL+1, dtj-NPNL+1,
                      dtcon) ;
      } else {
         sprintf(msg,"\n\tTime step too small, exiting"
                     "\n\ttime  = %e, cycle = %d, ndeltat = %e"
                     "\n\tblock = %d, dti = %d, dtj = %d, dtk = %d"
                      "\n\tcontrol = %s",
                     ttime, cycle, mydt_min, dtb, dti-NPNL+1, dtj-NPNL+1,
                     dtk-NPNL+1, dtcon ) ;
      }
#ifdef SILO
      Restart_write(0) ;
#endif
      if (ifparallel) combarrier() ;
      coredumpflag = FALSE;
      ctlerror(me,msg) ;
   }
   NodeList_ptr = NodeList_find("TimeStepZone");
   if (NodeList_ptr == NULL) {
       NodeWindow_make(&ndxin, dti, dti, dtj, dtj, dtk, dtk, dtb, "TimeStepZone");
       NodeList_make(ndxin,"TimeStepZone");
   } else {
       NodeWindow_make(&NodeList_ptr->list, dti, dti, dtj, dtj, dtk, dtk, dtb, 
                                                               "TimeStepZone");
   } 
   *dt_min = mydt_min ;


   return;
}

int TimeStepControl_print( void ) {
   char msg[MAXLINE];
   char *name;
   int i,j,k;
   RGST_AttributeElem_t *tscattr;
   RGST_AttributeElem_t *tscattr_ptr;
   tscattr = rgst_list_attr(A_OBJECT, "ActiveTimeStepControl");
   tscattr_ptr = tscattr;
   while (tscattr_ptr != NULL) {
      char *name             = ATTR_GET_OBJECT_NAME(tscattr_ptr)
      TimeStepControl_t *tsc = TimeStepControl_find(name,NULL);
      name = tsc->name + 4;
      i = MAX(tsc->i - NPNL + 1,0);
      j = MAX(tsc->j - NPNL + 1,0);
      k = MAX(tsc->k - NPNL + 1,0);
      if (ndims == 2) {
         sprintf(msg,"%20s = %0.9e  at :%i(%i,%i)",name, tsc->value,
                   tsc->block, i, j);
      } else {
         sprintf(msg,"%20s = %0.9e  at :%i(%i,%i,%i)",name, tsc->value,
          tsc->block, i, j, k);
      } 
      ctlmsg(msg);
      tscattr_ptr = tscattr_ptr->next;
   }
   return(0);
}
int TimeStepControl_init(TimeStepControl_t *tsc) {
   memset(tsc->name,'\0',MAXLINE); 
   tsc->value = plarge;
   tsc->block = -1;
   tsc->i = -1;
   tsc->j = -1;
   tsc->k = -1;
   return(0);
}

#ifdef SILO
void TimeStepControl_wtsilo(DBfile *idbid) {
   char *me = "TimeStepControl_wtsilo";
   char dirname[MAXLINE];
   int i;
   int error = 0;
   int dims[1];
   RGST_AttributeElem_t *tscattr;
   RGST_AttributeElem_t *tscattr_ptr;
   error = DBMkDir(idbid, "TimeStepControl");
   error = DBSetDir(idbid, "TimeStepControl");
   tscattr = rgst_list_attr(A_OBJECT, "ActiveTimeStepControl");
   tscattr_ptr = tscattr;
   i = 0;
   while (tscattr_ptr != NULL) {
      int idata[4];
      char *name             = ATTR_GET_OBJECT_NAME(tscattr_ptr)
      TimeStepControl_t *tsc = TimeStepControl_find(name,NULL);
      sprintf(dirname,"/Global/TimeStepControl/TimeStepControl%i",i);
      error += DBMkDir(idbid, dirname);
      error += DBSetDir(idbid, dirname);
      dims[0] = strlen(tsc->name) + 1;
      error += DBWrite(idbid,"name",tsc->name, dims, 1, DB_CHAR);
      dims[0] = strlen(tsc->key) + 1;
      error += DBWrite(idbid,"key",tsc->key, dims, 1, DB_CHAR);
      idata[0] = tsc->i;
      idata[1] = tsc->j;
      idata[2] = tsc->k;
      idata[3] = tsc->block;
      dims[0] = 4;
      error += DBWrite(idbid,"idata",idata, dims, 1, DB_INT);
      dims[0] = 1;
      error += DBWrite(idbid,"value",&tsc->value, dims, 1, DB_DOUBLE);
      i++; 
      tscattr_ptr = tscattr_ptr->next;
   }
   error += DBSetDir(idbid, "/Global/TimeStepControl");
   dims[0] = 1;
   error += DBWrite(idbid, "NumTimeStepControls",&i,dims,1,DB_INT);
   if (error != 0) {
      ctlwarning(me,"Error reading in time step controls.");
   }
}
#endif

#ifdef SILO
void TimeStepControl_rdsilo(DBfile *idbid) {
   char dirname[MAXLINE];
   char msg[MAXLINE];
   int error = 0;
   int i,n;
   TimeStepControl_t *tsc;
   DBShowErrors(DB_NONE, NULL);
   error = DBSetDir(idbid, "/Global/TimeStepControl");
   DBShowErrors(DB_TOP, NULL);
   if (error != 0) return;
   error += DBReadVar(idbid, "NumTimeStepControls",&n);
   for (i = 0; i < n; i++) {
      int idata[4];	 
      sprintf(dirname,"/Global/TimeStepControl/TimeStepControl%i",i);
      error += DBSetDir(idbid, dirname);
      error += DBReadVar(idbid,"name",dirname);
      tsc = TimeStepControl_find(dirname,NULL);
      if (tsc == NULL) {
         tsc = MALLOT(TimeStepControl_t,1);
	 strcpy(tsc->name,dirname);
         TimeStepControl_add(tsc, NULL);
      }
      error += DBReadVar(idbid,"key",tsc->key);
      error += DBReadVar(idbid,"idata",idata);
      tsc->i     = idata[0];
      tsc->j     = idata[1];
      tsc->k     = idata[2];
      tsc->block = idata[3];
      error += DBReadVar(idbid,"value",&tsc->value);
   }
}
#endif
int TimeStepControl_getvalue( void ) 
{
   char *me = "TimeStepControl_getvalue";
   char op[MAXLINE];
   char name[MAXLINE];
   char msg[MAXLINE];
   TimeStepControl_t *tsc;
   geta(op);
   geta(op);
   sprintf(name,"TSC_%s",op);
   tsc = TimeStepControl_find(name,NULL);
   sprintf(msg,"timestep(%s)",op);
   if (tsc != NULL) { ctloutput(me,msg,R_DOUBLE,tsc->value); }
   else             { ctloutput(me,msg,R_DOUBLE,plarge); }
   geta(op);
   return(0);
}
void TimeStepControl_getmin( char *attr, double *mindt ) {
   char *me = "TimeStepControl_getmin";
   char msg[MAXLINE];
   double my_mindt;
   RGST_AttributeElem_t *tscattr;
   RGST_AttributeElem_t *tscattr_ptr;
   my_mindt = plarge;
   tscattr = rgst_list_attr(A_OBJECT, attr); 
   tscattr_ptr = tscattr;
   while (tscattr_ptr != NULL) {
      char *name             = ATTR_GET_OBJECT_NAME(tscattr_ptr)
      TimeStepControl_t *tsc = TimeStepControl_find(name,NULL);
      int flag               = RGST_QUERY_OBJECT_ATTR(name, "TimeStepEdit");
      if (flag == 0) {
         if (my_mindt > tsc->value) {
            my_mindt  = tsc->value;
         }
      }
      tscattr_ptr = tscattr_ptr->next;
   }
   *mindt = my_mindt ;
}
