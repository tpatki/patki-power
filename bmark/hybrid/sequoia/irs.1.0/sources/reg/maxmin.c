#include "irs.h"
#include "irsreg.h"
#include "irscom.h"
#include "irsrgst.h"
#include "BlockMapping.h"
#include "FunctionTimer.h"
#include "NodeList.h"
#include "ProblemArray.h"
int  maxmin( void )
{
   char *me = "maxmin";
   char aname[MAXWORD], fname[10], op[MAXLINE], lab[MAXWORD], msg[MAXLINE];
   int  i, j, k;
   int  ndxmin, ndxmax, array_type;
   int  error = 0;
   int  imin, imax, blkmin, blkmax, len, iblk;
   int *lndx, *undx, *lblk;
   double amin, amax ;
   double *a;
   double *ddata_min;
   double *ddata_max;
   NodeWindow_t *ndxin = NULL, *ndxptr = NULL;
   strcpy(aname,"maxmin") ;
   error = NodeWindow_read(aname,&ndxin);
   geta(op) ;
   if (strcmp(op,"=")) {
      error = 1 ;
      sprintf(msg,"Got %s instead of expected '=' after maxmin",op) ;
      ctlwarning(me,msg);
      newline() ;
      NodeWindow_free(ndxin);
      return(error);
   }
   geta(fname) ;
   if (  (RGST_QUERY_OBJECT_ATTR(fname,"Zonal")  == FALSE)
      && (RGST_QUERY_OBJECT_ATTR(fname,"Nodal") == FALSE)) {
      error = 1 ;
      sprintf(msg,"Unknown field name %s in maxmin command",fname) ;
      ctlwarning(me,msg);
      newline() ;
      NodeWindow_free(ndxin);
      return(error);
   }
   amin   = plarge;
   amax   = -plarge;
   blkmin = -1;
   blkmax = -1;
   array_type = ZONAL_ARRAY;
   if (RGST_QUERY_OBJECT_ATTR(fname,"Nodal") == TRUE) array_type = NODAL_ARRAY;
   ndxptr = ndxin;
   while (ndxptr != NULL) {
      for (iblk = 0; iblk < nblk; iblk++) {
         if (array_type == ZONAL_ARRAY) {
            len =  NodeWindow_fastndx(ndxptr,domains[iblk].gblk, NDX_REAL, 
                   NDX_ZONAL);
         } else {
            len =  NodeWindow_fastndx(ndxptr,domains[iblk].gblk, NDX_REAL, 
                   NDX_NODAL);
         }
         lndx = ndxptr->ndx;
         a = (double *)ProblemArray_ptr(fname, domains[iblk].hash);
         for (i = 0; i < len; i++) {
            if (a[lndx[i]] >= amax) {
               amax = a[lndx[i]];
               ndxmax = lndx[i];
               blkmax = domains[iblk].gblk;
            }
            if (a[lndx[i]] <= amin) {
               amin = a[lndx[i]];
               ndxmin = lndx[i];
               blkmin = domains[iblk].gblk;
            }
         }
         NodeWindow_freendx(ndxptr);
      }
      ndxptr = ndxptr->next;
   }
   if (ifparallel) {
      ddata_min = MALLOT(double,num_procs);
      ddata_max = MALLOT(double,num_procs);
      for (i = 0; i < num_procs; i++) {
         ddata_min[i] = 0.0;
         ddata_max[i] = 0.0;
      }
      ddata_min[myid] = amin;
      ddata_max[myid] = amax;
      comreduce(ddata_min, num_procs,COM_SUM,COM_ALL,COM_DOUBLE);
      comreduce(ddata_max, num_procs,COM_SUM,COM_ALL,COM_DOUBLE);
      amin = plarge;
      amax = -plarge;
      imin = -1;
      imax = -1;
      for (i = 0; i < num_procs; i++) {
         if (ddata_min[i] < amin) {
            imin = i;
            amin = ddata_min[i];
         }
         if (ddata_max[i] > amax) {
            imax = i;
            amax = ddata_max[i];
         }
      }
      FREEMEM(ddata_min);
      FREEMEM(ddata_max);
      if ((imin == -1) || (imax == -1)) {
         sprintf(msg,"Error in finding maxmin of %s",fname);
         ctlwarning(me,msg);
         NodeWindow_free(ndxin);
         return(-1);
      }
      combcast(&blkmax,1,COM_INT,imax); 
      combcast(&blkmin,1,COM_INT,imin); 
      combcast(&ndxmax,1,COM_INT,imax); 
      combcast(&ndxmin,1,COM_INT,imin); 
   }
   if (blkmin >= 0) {
      if (ndims == 2) {
         j = ndxmin / gmap[blkmin].jp;
         i = ndxmin - (j * gmap[blkmin].jp);
	 i = i - 2 * NPNL + 1 + gmap[blkmin].imin;
	 j = j - 2 * NPNL + 1 + gmap[blkmin].jmin;
         sprintf(msg,"%s min:%d(%d,%d) = %e",
                  fname,gmap[blkmin].ublk,i,j,amin) ;
      } else {
         k = ndxmin / gmap[blkmin].kp;
         j = (ndxmin - (k * gmap[blkmin].kp))/gmap[blkmin].jp;
         i = ndxmin - (j * gmap[blkmin].jp) - (k * gmap[blkmin].kp);
	 i = i - 2 * NPNL + 1 + gmap[blkmin].imin;
	 j = j - 2 * NPNL + 1 + gmap[blkmin].jmin;
	 k = k - 2 * NPNL + 1 + gmap[blkmin].kmin;
         sprintf(msg,"%s min:%d(%d,%d,%d) = %e",
                  fname,gmap[blkmin].ublk,i,j,k,amin) ;
      } 
      ctlmsg(msg);
   } 
   if (blkmax >= 0) {
      if (ndims == 2) {
         j = ndxmax / gmap[blkmax].jp;
         i = ndxmax - (j * gmap[blkmax].jp);
	 i = i - 2 * NPNL + 1 + gmap[blkmax].imin;
	 j = j - 2 * NPNL + 1 + gmap[blkmax].jmin;
         sprintf(msg,"%s max:%d(%d,%d) = %e",
                  fname,gmap[blkmax].ublk,i,j,amax) ;
      } else {
         k = ndxmax / gmap[blkmax].kp;
         j = (ndxmax - (k * gmap[blkmax].kp))/gmap[blkmax].jp;
         i = ndxmax - (j * gmap[blkmax].jp) - (k * gmap[blkmax].kp);
	 i = i - 2 * NPNL + 1 + gmap[blkmax].imin;
	 j = j - 2 * NPNL + 1 + gmap[blkmax].jmin;
	 k = k - 2 * NPNL + 1 + gmap[blkmax].kmin;
         sprintf(msg,"%s max:%d(%d,%d,%d) = %e",
                  fname,gmap[blkmax].ublk,i,j,k,amax) ;
      } 
      ctlmsg(msg);
   }
   NodeWindow_free(ndxin);
   return(error) ;
}
