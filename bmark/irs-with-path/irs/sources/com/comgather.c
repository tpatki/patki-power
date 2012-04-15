#include "irs.h"
#include "irscom.h"
#include "irsrgst.h"
#include "FunctionTimer.h"
#include "NodeList.h"
#include "ProblemArray.h"
void comgather( void *buf, char *name, NodeWindow_t *ndxin, int root) 
{
   char *me = "comgather";
   char msg[MAXLINE];
   int i;
   int ip;
   int iblk;
   int type;
   int len,len_total;
   int *ndx;
   int *blk;
   int *pos;
   int *imap;
   int *idata;
   int *ibuf;
   double *ddata;
   double *dbuf;
   ProblemArray_t *prb;
   ProblemArray_t *prb_array;
   prb = ProblemArray_find(name,NULL);
   if (prb == NULL) {
      sprintf(msg,"Cannot find variable %s.",name);
      ctlwarning(me,msg);
      return;
   }
   type = -1;
   if (prb->type == R_INT)    type = COM_INT;
   if (prb->type == R_DOUBLE) type = COM_DOUBLE;
   if (type == -1) {
      sprintf(msg, "Variable %s has type which cannot be used in comgather.",
                    name);
      ctlwarning(me,msg);
      return;
   }
   prb_array = ProblemArray_setblk(name);
   ndx = ndxin->ndx;
   pos = ndxin->pos;
   blk = ndxin->blk;
   len = ndxin->len;
   len_total = ndxin->len_total;
   imap = ALLOT(int,len_total);
   for (i = 0; i < len_total; i++) {
      imap[i] = 0;
   }
   if (type == COM_INT) {
      if (ifparallel) {
         idata = ALLOT(int,len_total);
      } else {
         idata = buf;
      }
      for (i = 0; i < len; i++) {
         ip   = pos[i];
         iblk = blk[i];
         ibuf = (int*) prb_array[iblk].ptr;
         if (ndx[i] >= prb_array[iblk].len) {
           sprintf(msg,"\n\tProblem Array '%s' has length %d"
                       "\n\t%d is an invalid index",
                        prb_array->name,prb_array->len,ndx[i]);
           ctlnotice(me,msg);
           idata[ip] = 0;
         }
         else {
           idata[ip] = ibuf[ndx[i]];
         }
         imap[ip]  = 1;
      }
   } else {
      if (ifparallel) {
         ddata = ALLOT(double,len_total);
      } else {
         ddata = buf;
      }
      for (i = 0; i < len; i++) {
         ip   = pos[i];
         iblk = blk[i];
         dbuf = (double *)prb_array[iblk].ptr;
         if (ndx[i] >= prb_array[iblk].len) {
           sprintf(msg,"\n\tProblem Array '%s' has length %d"
                       "\n\t%d is an invalid index",
                        prb_array->name,prb_array->len,ndx[i]);
           ctlnotice(me,msg);
           ddata[ip] = 0.0;
         }
         else {
           ddata[ip] = dbuf[ndx[i]];
         }
         imap[ip]  = 1;
      }
   } 
   if (ifparallel) {
      comreduce(imap,len_total,COM_SUM,COM_ONE,COM_INT);
      if (type == COM_DOUBLE) {
         comreduce(ddata,len_total,COM_SUM,COM_ONE,COM_DOUBLE);
         if (myid == root) {
            dbuf = (double *) buf;
            for (i = 0;i < len_total; i++) {
               if (imap[i] > 1) {
                  ddata[i] = ddata[i] / (double)imap[i];
               }
               dbuf[i] = ddata[i];
            }
         }
         FREEMEM(ddata);
      } else {
         comreduce(idata,len_total,COM_SUM,COM_ONE,COM_INT);
         if (myid == root) {
            ibuf = (int *) buf;
            for (i = 0;i < len_total; i++) {
               if (imap[i] > 1) {
                  idata[i] = idata[i] / imap[i];
               }
	       ibuf[i] = idata[i];
            }
         }
         FREEMEM(idata);
      } 
   }
   FREEMEM(imap);
   FREEMEM(prb_array);
}
