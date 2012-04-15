#include "irs.h"
#include "irsgen.h"
#include "FunctionTimer.h"
#include "irscom.h"
#include "irsrgst.h"
#include "NodeList.h"
#include "ProblemArray.h"
int getfpaa(char *aname, double *farg )
{
   char *me = "getfpaa";
   char msg[MAXLINE];	 
   int i, j, len, iblk, error;
   int *ndx, *blk ;
   double *fdata ;
   NodeWindow_t *ndxin = NULL;
   ProblemArray_t  *prb;
   ProblemArray_t  *prb_array;
   error = NodeWindow_read(aname,&ndxin);
   if (ndxin->next != NULL) {
      sprintf(msg,"Cannot accept multi-block index lists on right hand side of assignment.");
      ctlwarning(me,msg);
      error = -1;
      return(error);
   }
   len = NodeWindow_getndx(ndxin,-1,NDX_NO_OVERLAP,NDX_REAL,NDX_NODAL);
   ndx = ndxin->ndx;
   blk = ndxin->blk;
   j = 0;
   prb = ProblemArray_find(aname,NULL);
   if (prb->type != R_DOUBLE) {
      sprintf(msg,"Array %s must be a float array",aname);
      ctlwarning(me,msg);
      error = -1;
      return(error);
   }
   if (RGST_QUERY_OBJECT_ATTR(aname,"GlobalArray") == TRUE) {
     fdata = (double *)prb->ptr;
     for ( i = 0 ; i < len ; i++ ) {
       farg[i] = fdata[ndx[i]] ;
     }
     j = len;
   } else if (RGST_QUERY_OBJECT_ATTR(aname,"DomainVar") == TRUE) {
     prb_array = ProblemArray_setblk(aname);
     for ( i = 0 ; i < len ; i++ ) {
       iblk = blk[i];
       fdata     = (double *)prb_array[iblk].ptr;
       farg[j++] = fdata[ndx[i]] ;
     }
     FREEMEM(prb_array);
   }
   NodeWindow_free(ndxin);
   return(j) ;
}
int getfpaa_rgst(
  char    *aname,   
  double **dptr,    
  int      dptrlen) 
{
  char *me = "getfpaa_rgst";
  char msg[256], errmsg1[256];
  int i,ip, copied_len, len, iblk, *ndx, *blk;
  int *mask, *pos;
  double *ddata_out, *ddata_pa;
  ProblemArray_t   *prb;
  ProblemArray_t   *prb_array;
  NodeWindow_t  *ndxin = NULL;
  NodeWindow_t  *ndxcpt = NULL;
  ndxcpt = MALLOT(NodeWindow_t,1);
  NodeWindow_read(aname,&ndxin);
  len = NodeWindow_compact(ndxin,ndxcpt,-1,NDX_NO_OVERLAP,NDX_REAL,NDX_NODAL);
  len = ndxcpt->len_total;
  NodeWindow_free(ndxin);
  ndx = ndxcpt->ndx;
  blk = ndxcpt->blk;
  pos = ndxcpt->pos;
  if (dptrlen < 0) {
    if (dptrlen == -1) { dptrlen = len; }
    else               { dptrlen = -dptrlen; }
   if ((*dptr = ALLOT(double,dptrlen)) == NULL) ctlerror(me,gv_errmsg_memory);
  }
  ddata_out = *dptr;
  sprintf(errmsg1,"Attempt to copy more than %d doubles into array of "
                  "length %d",dptrlen,dptrlen);
  copied_len = 0;
  prb = ProblemArray_find(aname, NULL);
  if (prb->type != R_DOUBLE) {
     sprintf(msg,"Array %s in not of type float.",aname);
     ctlwarning(me,msg);
     return(-1);
  }
  if (RGST_QUERY_OBJECT_ATTR(aname,"DomainVar") == FALSE) {
    ddata_pa = (double *)prb->ptr;
    for (copied_len=0; copied_len<len; copied_len++) {
      if (copied_len >= dptrlen) {
        ctlwarning(me,errmsg1);
        break;
      }
      ddata_out[copied_len] = ddata_pa[ndx[copied_len]];
    }
  } else {
    prb_array = ProblemArray_setblk(aname);
    for (i = 0; i < ndxcpt->len; i++) {
      ip   = pos[i];
      iblk = blk[i];
      ddata_pa = (double *)prb_array[iblk].ptr;
      ddata_out[ip] = ddata_pa[ndx[i]];
    }
    FREEMEM(prb_array);
    copied_len = ndxcpt->len_total;
    if (ifparallel) {
       mask = ALLOT(int,ndxcpt->len_total);
       comreduce(ddata_out, ndxcpt->len_total, COM_SUM, COM_ALL, COM_DOUBLE);
       comreduce(mask, ndxcpt->len_total, COM_SUM, COM_ALL, COM_INT);
       for (i = 0; i < ndxcpt->len_total; i++) {
          if (mask[i] > 1) {
             ddata_out[i] = ddata_out[i] / (double) mask[i];
          }
       }
       FREEMEM(mask);
    }
  }
  NodeWindow_free(ndxcpt);
  return(copied_len) ;
}
