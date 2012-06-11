#include "irs.h"
#include "BlockMapping.h"
#include "Boundary.h"
#include "FunctionTimer.h"
#include "irscom.h"
int putdata(void* buf, int len, int type, int gblk, Boundary_t *bnd, 
            int com_type  ) {
   int error;
   int proc;
   int i;
   int directflg = 0;
   int *ndx;
   int *idata;
   int *idata_in;
   double *ddata;
   double *ddata_in;
   error=0;
   switch(com_type) {
      case COM_LAYER1N:
         ndx=bnd->ndx_send;
         len=bnd->len_nsend1;
         break;
      case COM_LAYER1Z:
         ndx=bnd->zdx_send;
         len=bnd->len_zsend1;
         break;
      case COM_LAYER1ZC:
         ndx=bnd->zdx_send;
         len=bnd->len_zsend1 + bnd->len_zsendc;
         break;
      case COM_LAYER2N:
         ndx=bnd->ndx_send+bnd->len_nsend1;
         len=bnd->len_nsend2;
         break;
      case COM_LAYER2NC:
         ndx=bnd->ndx_send+bnd->len_nsend1;
         len=bnd->len_nsend2 + bnd->len_nsendc;
         break;
      case COM_LAYER2Z:
         ndx=bnd->zdx_send+bnd->len_zsend1;
         len=bnd->len_zsend2;
         break;
      case COM_LAYER_ALLN:
         ndx=bnd->ndx_send;
         len=bnd->len_nsend1+bnd->len_nsend2+bnd->len_nsendc;
         break;
      case COM_LAYER_ALLZ:
         ndx=bnd->zdx_send;
         len=bnd->len_zsend1 + bnd->len_zsend2 + bnd->len_zsendc;
         break;
      case COM_LAYER_CZ:
         ndx=bnd->zdx_send+bnd->len_zsend1;
         len=bnd->len_zsendc;
         break;
      case COM_LAYER_CN:
         ndx=bnd->ndx_send+bnd->len_nsend1 + bnd->len_nsend2;
         len=bnd->len_nsendc;
         break;
      case COM_ACCUM:
         ndx=bnd->ndx_send;
         len=bnd->len_nsend1;
         break;
      case COM_DIRECT:
         directflg=1;
         break;
      case COM_DIRECT_ID:
         directflg=1;
         break;
      default:
	 error=1;
         break;
   }
   if (com_type == COM_DIRECT_ID) {
      proc=gblk;
   } else {
      proc=gmap[gblk].proc;
   }
   if (type==COM_DOUBLE) {
      ddata=combuf[curcombuf].sendd_ptr[proc];
      ddata_in=buf;
      if (directflg) {
         for (i=0;i<len;i++) {
            ddata[i]=ddata_in[i];
         }
      } else {
         for (i=0;i<len;i++) {
            ddata[i]=ddata_in[ndx[i]];
         }
      }
      combuf[curcombuf].sendd_ptr[proc]+=len;
   }
   if (type==COM_INT) {
      idata=combuf[curcombuf].sendi_ptr[proc];
      idata_in=buf;
      if (directflg) {
         for (i=0;i<len;i++) {
            idata[i]=idata_in[i];
         }
      } else {
         for (i=0;i<len;i++) {
            idata[i]=idata_in[ndx[i]];
         }
      }
      combuf[curcombuf].sendi_ptr[proc]+=len;
   }
   return(error);
}
