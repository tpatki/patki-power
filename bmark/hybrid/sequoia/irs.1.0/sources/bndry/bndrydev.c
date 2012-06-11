#include "irs.h"
#include "irsbndry.h"
#include "irscom.h"
#include "irsrgst.h"
#include "FunctionTimer.h"
#include "ProblemArray.h"
#include "NodeList.h"
int bndrydev( void )
{
   char *me = "bndrydev";
   char op[MAXLINE];
   char msg[MAXLINE];
   char index[MAXLINE];
   int iblk;
   int cflag;
   int ibnd;
   int i,len;
   int *ndx;
   double diff;
   double diff_max;
   double *data;
   double *data_save;
   ProblemArray_t *prb = NULL;
   geta(op);
   diff_max = getf(&cflag);
   prb = ProblemArray_find(op, NULL);
   if (prb == NULL) {
      sprintf(msg,"Variable %s does not exist.",op);
      ctlwarning(me,msg);
      return(0);
   }
   if (RGST_QUERY_OBJECT_ATTR(op,"Nodal") != TRUE) {
      sprintf(msg,"Variable %s is not a nodal.",op);
      ctlwarning(me,msg);
      return(0);
   }
   ProblemArray_add("BNDRY_datasave", NULL, 0, R_DOUBLE, NULL);
   for (iblk = 0; iblk < nblk; iblk++) {
       ProblemArray_add("BNDRY_datasave", NULL, domains[iblk].nnodes, R_DOUBLE, 
                        domains[iblk].hash);
       data_save = (double *) ProblemArray_allotptr("BNDRY_datasave", 
                                                           domains[iblk].hash); 
       data      = (double *) ProblemArray_ptr(op, domains[iblk].hash); 
       for (i = 0; i < domains[iblk].nnalls; i++) {
          data_save[i] = data[i];
       }
       varcomset(data_save,-1,"data",COM_DOUBLE, COM_LAYER1N, COM_NOOP, 
                 domains[iblk].gblk);
   }
   varcom(COM_SET_SIZE);
   varcom(COM_SEND_RECV);   
   for (iblk = 0; iblk < nblk; iblk++) {
      data_save = (double *) ProblemArray_ptr("BNDRY_datasave", domains[iblk].hash); 
      data      = (double *) ProblemArray_ptr(op, domains[iblk].hash); 
      for (ibnd = 0; ibnd < domains[iblk].nbnd; ibnd++) {
          len = COM_LEN_1N_R(domains[iblk].bnd[ibnd]);
          ndx = COM_NDX_1N_R(domains[iblk].bnd[ibnd]);
          for (i = 0; i < len; i++) {
             diff = fabs(data_save[ndx[i]] - data[ndx[i]]);
             if (diff > diff_max) {
                NodeWindow_getstr(ndx[i], index, domains[iblk].gblk);
                sprintf(msg,"Domain %i  Node %s  Bnd %i  Domain_send %i  Deviation %.20e\n",
                        domains[iblk].gblk, index, ibnd, 
			domains[iblk].bnd[ibnd].blk_send,  diff);
                ctlmsg(msg);
             }
          }
      }
   }
   ProblemArray_free("BNDRY_datasave"); 
   return(0);
}
