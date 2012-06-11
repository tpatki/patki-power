#include "irs.h"
#include "irscom.h"
#include "BlockMapping.h"
#include "Boundary.h"
#include "FunctionTimer.h"
int getdata(void *buf, int len, int type, int gblk, Boundary_t *bnd,  
            int com_type  ) {
   int error;
   int i;
   int proc;
   int directflg = 0;
   int *ndx;
   int *idata;
   int *idata_out;
   double *ddata;
   double *ddata_out;
   error=0;
   switch(com_type) {
      case COM_LAYER1N:
         ndx=bnd->ndx_recv;
         len=bnd->len_nrecv1;
         break;
      case COM_LAYER1Z:
         ndx=bnd->zdx_recv;
         len=bnd->len_zrecv1;
         break;
      case COM_LAYER1ZC:
         ndx=bnd->zdx_recv;
         len=bnd->len_zrecv1+bnd->len_zrecvc;
         break;
      case COM_LAYER2N:
         ndx=bnd->ndx_recv+bnd->len_nrecv1;
         len=bnd->len_nrecv2;
         break;
      case COM_LAYER2NC:
         ndx=bnd->ndx_recv+bnd->len_nrecv1;
         len=bnd->len_nrecv2 + bnd->len_nrecvc;
         break;
      case COM_LAYER2Z:
         ndx=bnd->zdx_recv+bnd->len_zrecv1;
         len=bnd->len_zrecv2;
         break;
      case COM_LAYER_ALLN:
         ndx=bnd->ndx_recv;
         len=bnd->len_nrecv1+bnd->len_nrecv2 + bnd->len_nrecvc;
         break;
      case COM_LAYER_ALLZ:
         ndx=bnd->zdx_recv;
         len=bnd->len_zrecv1 + bnd->len_zrecv2 + bnd->len_zrecvc;
         break;
      case COM_LAYER_CZ:
         ndx=bnd->zdx_recv + bnd->len_zrecv1;
         len=bnd->len_zrecvc;
         break;
      case COM_LAYER_CN:
         ndx=bnd->ndx_recv+bnd->len_nrecv1 + bnd->len_nrecv2;
         len=bnd->len_nrecvc;
         break;
      case COM_ACCUM:
         directflg = 1;
         break;
      case COM_DIRECT:
         directflg = 1;
         break;
      case COM_DIRECT_ID:
         directflg = 1;
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
      ddata=combuf[curcombuf].recvd_ptr[proc];
      ddata_out=buf;
      if (directflg) {
         for (i=0;i<len;i++) {
            ddata_out[i]=ddata[i];
         }
      } else {
         for (i=0;i<len;i++) {
            ddata_out[ndx[i]]=ddata[i];
         }
      } 
      combuf[curcombuf].recvd_ptr[proc]+=len;
   }
   if (type==COM_INT) {
      idata=combuf[curcombuf].recvi_ptr[proc];
      idata_out=buf;
      if (directflg) {
         for (i=0;i<len;i++) {
            idata_out[i]=idata[i];
         }
      } else {
         for (i=0;i<len;i++) {
            idata_out[ndx[i]]=idata[i]; 
         } 
      } 
      combuf[curcombuf].recvi_ptr[proc]+=len;
   }
   return(error);
}
