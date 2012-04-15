#include "irs.h"
#include "irscom.h"
#include "BlockMapping.h"
#include "Boundary.h"
#include "FunctionTimer.h"
int acumnm(int comflag)
{ 
   int i,j,ibc,ibc_out ;
   int iblk_out,gblk,gblk_in;
   int len;
   int iblk;
   int error;
   int proc;
   int *ndx;
   double *na;
   double *nas;
   Boundary_t *bnd;
   Boundary_t *bnd2;
   Boundary_t *sldbnd;
   Boundary_t *sldbnd2;
   error = 0;
   len = 0;
   if  (!ifcom)  {
      return(error);
   }
   STARTTIMER(ACUMNM) ;
   if (ifparallel) {
      curcombuf = ACUMNM;
      if (comflag==COM_RECV) {
         initbuf(ACUMNM,COM_RECV);
         postbuf(ACUMNM,COM_RECV);
         STOPTIMER(ACUMNM,comflag) ;
         return(error);
      } else if (comflag==COM_SEND) {
         initbuf(ACUMNM,COM_SEND);
      } else if (comflag==COM_WAIT_SEND) {
         waitbuf(ACUMNM,COM_WAIT_SEND,COM_ALL);
         freebuf(ACUMNM,COM_SEND);
         STOPTIMER(ACUMNM,comflag) ;
         return(error);
      } else if (comflag==COM_WAIT_RECV) {
         while((proc=waitbuf(ACUMNM,COM_WAIT_RECV,COM_ANY))>=0) {
             for (i=0;i<hydro_len_order[proc];i++) {
                ibc=hydro_tag_order[proc][i];
                gblk=hydro_blk_order[proc][i];
                iblk=gmap[gblk].lblk;
                bnd = domains[iblk].bnd;
                sldbnd = domains[iblk].sldbnd;
                gblk_in = domains[iblk].bnd[ibc].blk_send;
                len=domains[iblk].bnd[ibc].len_nrecv1;
	        domains[iblk].bnd[ibc].buf_acum= MALLOT(double,len);
	        na = domains[iblk].bnd[ibc].buf_acum;
                getdata(na,len,COM_DOUBLE,gblk_in,&bnd[ibc],COM_ACCUM);
             }
         }
         freebuf(ACUMNM,COM_RECV);
      }
   }
   for (j=0;j<hydro_len_order_send;j++) {
      ibc = hydro_tag_order[myid][j+hydro_len_order[myid]];
      gblk = hydro_blk_order[myid][j+hydro_len_order[myid]];
      iblk = gmap[gblk].lblk;
      bnd = domains[iblk].bnd;
      sldbnd = domains[iblk].sldbnd;
      ibc_out = bnd[ibc].bndnbc;
      gblk = bnd[ibc].blk_send;
      proc = gmap[gblk].proc;
      if ((proc!=myid)&&(comflag==COM_SEND)) {
         putdata(domains[iblk].nmass,len,COM_DOUBLE,gblk,&bnd[ibc],COM_ACCUM);
      } else if ((proc==myid)&&(comflag==COM_SEND)) {
         iblk_out=gmap[gblk].lblk;
         bnd2 = domains[iblk_out].bnd;
         sldbnd2 = domains[iblk_out].sldbnd;
         ndx = bnd2[ibc_out].ndx_send;
         bnd[ibc].buf_acum= MALLOT(double,bnd[ibc].len_nrecv1);
         na = bnd[ibc].buf_acum;
         for ( i = 0 ; i < bnd2[ibc_out].len_nsend1 ; i++ ) {
            na[i] = domains[iblk_out].nmass[ndx[i]]  ;
         }
      } else if (comflag==COM_WAIT_RECV) {
         na = bnd[ibc].buf_acum;
         ndx = bnd[ibc].ndx_recv;
         len = bnd[ibc].len_nrecv1;
         for ( i = 0 ; i < len ; i++ ) {
            domains[iblk].nmass[ndx[i]]+=na[i];
         }
         if (len > 0) FREEMEM(bnd[ibc].buf_acum);
      } else if (comflag==COM_SET_SIZE_DOUBLE) {
         len_sendd[proc]+=bnd[ibc].len_nsend1;
         len_recvd[proc]+=bnd[ibc].len_nrecv1;
      } else if (comflag==COM_SET_SIZE_INT) {
         len_sendi[proc] = 0;
         len_recvi[proc] = 0;
      }
   }
   if ((ifparallel)&&(comflag==COM_SEND)) {
      postbuf(ACUMNM,COM_SEND);
   }
   STOPTIMER(ACUMNM,comflag) ;
   return(error);
}
