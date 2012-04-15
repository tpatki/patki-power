#include "irs.h"
#include "BlockMapping.h"
#include "Boundary.h"
#include "FunctionTimer.h"
#include "irscom.h"
int qbnd(int stepflag, int comflag)
{ 
   int i,ibc,ibc_out ;
   int j;
   int iblk_out,gblk,gblk_in;
   int len;
   int iblk;
   int error;
   int proc;
   int *inndx,*outndx;
   int *inzdx,*outzdx;
   double *xv,*yv,*x,*y;
   double *xvp,*yvp,*xp,*yp;
   double *zv,*z;
   double *zvp,*zp;
   Boundary_t *bnd;
   Boundary_t *bnd2;
   Boundary_t *sldbnd;
   Boundary_t *sldbnd2;
   error = 0;
   len = 0;
   if  (!ifcom)  {
      return(error);
   }
   STARTTIMER(QBND) ;
   if (ifparallel) {
      curcombuf = QBND;
      if (comflag==COM_RECV) {
         initbuf(QBND,COM_RECV);
         postbuf(QBND,COM_RECV);
         STOPTIMER(QBND,comflag) ;
         return(error);
      } else if (comflag==COM_SEND) {
         initbuf(QBND,COM_SEND);
      } else if (comflag==COM_WAIT_SEND) {
         waitbuf(QBND,COM_WAIT_SEND,COM_ALL);
         freebuf(QBND,COM_SEND);
         STOPTIMER(QBND,comflag) ;
         return(error);
      } else if (comflag==COM_WAIT_RECV) {
         while((proc=waitbuf(QBND,COM_WAIT_RECV,COM_ANY))>=0) {
             for (i=0;i<hydro_len_order[proc];i++) {
                ibc=hydro_tag_order[proc][i];
                gblk=hydro_blk_order[proc][i];
                iblk=gmap[gblk].lblk;
                bnd = domains[iblk].bnd;
                sldbnd = domains[iblk].sldbnd;
                gblk_in = bnd[ibc].blk_send;
                if (stepflag==FULL_STEP) {
                   x  = domains[iblk].x;
                   xv = domains[iblk].xdot;
                   y  = domains[iblk].y;
                   yv = domains[iblk].ydot;
                   z  = domains[iblk].z;
                   zv = domains[iblk].zdot;
                }
                else {
                   x  = domains[iblk].x;
                   xv = domains[iblk].xdot;
                   y  = domains[iblk].y;
                   yv = domains[iblk].ydot;
                   z  = domains[iblk].z;
                   zv = domains[iblk].zdot;
                }
                getdata(x,len,COM_DOUBLE,gblk_in,&bnd[ibc],COM_LAYER2NC);
                getdata(y,len,COM_DOUBLE,gblk_in,&bnd[ibc],COM_LAYER2NC);
                getdata(xv,len,COM_DOUBLE,gblk_in,&bnd[ibc],COM_LAYER2NC);
                getdata(yv,len,COM_DOUBLE,gblk_in,&bnd[ibc],COM_LAYER2NC);
                if (ndims == 3) {
                   getdata(z,len,COM_DOUBLE,gblk_in,&bnd[ibc],COM_LAYER2NC);
                   getdata(zv,len,COM_DOUBLE,gblk_in,&bnd[ibc],COM_LAYER2NC);
                   getdata(domains[iblk].vol,len,COM_DOUBLE,gblk_in,&bnd[ibc],
                        COM_LAYER1Z);
                } else {
                   getdata(domains[iblk].area,len,COM_DOUBLE,gblk_in,&bnd[ibc],
                        COM_LAYER1Z);
                }

             }
         }
         freebuf(QBND,COM_RECV);
      }
   }
   for (j=0;j<hydro_len_order_send;j++) {
      ibc=hydro_tag_order[myid][j+hydro_len_order[myid]];
      gblk=hydro_blk_order[myid][j+hydro_len_order[myid]];
      iblk = gmap[gblk].lblk;
      bnd = domains[iblk].bnd;
      sldbnd = domains[iblk].sldbnd;
      gblk=bnd[ibc].blk_send;
      proc = gmap[gblk].proc;
      ibc_out=bnd[ibc].bndnbc;
      if (stepflag==FULL_STEP) {
         x  = domains[iblk].x;
         xv = domains[iblk].xdot;
         y  = domains[iblk].y;
         yv = domains[iblk].ydot;
         z  = domains[iblk].z;
         zv = domains[iblk].zdot;
      }
      else {
         x  = domains[iblk].x;
         xv = domains[iblk].xdot;
         y  = domains[iblk].y;
         yv = domains[iblk].ydot;
         z  = domains[iblk].z;
         zv = domains[iblk].zdot;
      }
      if ((proc!=myid)&&(comflag==COM_SEND)) {
         putdata(x,len,COM_DOUBLE,gblk,&bnd[ibc],COM_LAYER2NC);
         putdata(y,len,COM_DOUBLE,gblk,&bnd[ibc],COM_LAYER2NC);
         putdata(xv,len,COM_DOUBLE,gblk,&bnd[ibc],COM_LAYER2NC);
         putdata(yv,len,COM_DOUBLE,gblk,&bnd[ibc],COM_LAYER2NC);
         if (ndims == 3) {
            putdata(z,len,COM_DOUBLE,gblk,&bnd[ibc],COM_LAYER2NC);
            putdata(zv,len,COM_DOUBLE,gblk,&bnd[ibc],COM_LAYER2NC);
            putdata(domains[iblk].vol,len,COM_DOUBLE,gblk,&bnd[ibc],
                  COM_LAYER1Z);
         } else {
            putdata(domains[iblk].area,len,COM_DOUBLE,gblk,&bnd[ibc],
                  COM_LAYER1Z);
         }

      } else if ((proc==myid)&&(comflag==COM_SEND)) {
         iblk_out = gmap[gblk].lblk;
         bnd2     = domains[iblk_out].bnd;
         sldbnd2  = domains[iblk_out].sldbnd;
         inndx  = COM_NDX_2NC_R(bnd[ibc]);
         outndx = COM_NDX_2NC_S(bnd2[ibc_out]);
         inzdx  = COM_ZDX_1ZC_R(bnd[ibc]);
         outzdx = COM_ZDX_1ZC_S(bnd2[ibc_out]);
         if (stepflag==FULL_STEP) {
            xp  = domains[iblk_out].x;
            xvp = domains[iblk_out].xdot;
            yp  = domains[iblk_out].y;
            yvp = domains[iblk_out].ydot;
            zp  = domains[iblk_out].z;
            zvp = domains[iblk_out].zdot;
         } else {
            xp  = domains[iblk_out].x;
            xvp = domains[iblk_out].xdot;
            yp  = domains[iblk_out].y;
            yvp = domains[iblk_out].ydot;
            zp  = domains[iblk_out].z;
            zvp = domains[iblk_out].zdot;
         }
         if (ndims == 2) {
            len = COM_LEN_2NC_R(bnd[ibc]);
            for ( i = 0 ; i < len; i++ ) {
               x[inndx[i]]  = xp[outndx[i]] ;
               y[inndx[i]]  = yp[outndx[i]] ;
               xv[inndx[i]] = xvp[outndx[i]] ;
               yv[inndx[i]] = yvp[outndx[i]] ;
            }
            len = COM_LEN_1ZC_R(bnd[ibc]);
            for ( i = 0; i < len; i++ ) {
               domains[iblk].area[inzdx[i]]=domains[iblk_out].area[outzdx[i]];
            }
         } else {
            len = COM_LEN_2NC_R(bnd[ibc]);
            for ( i = 0 ; i < len; i++ ) {
               x[inndx[i]]  = xp[outndx[i]] ;
               y[inndx[i]]  = yp[outndx[i]] ;
               z[inndx[i]]  = zp[outndx[i]] ;
               xv[inndx[i]] = xvp[outndx[i]] ;
               yv[inndx[i]] = yvp[outndx[i]] ;
               zv[inndx[i]] = zvp[outndx[i]] ;
            }
            len = COM_LEN_1ZC_R(bnd[ibc]);
            for ( i = 0 ; i < len; i++ ) {
               domains[iblk].vol[inzdx[i]]=domains[iblk_out].vol[outzdx[i]];
            }
         } 

      } else if (comflag==COM_WAIT_RECV) {

      } else if (comflag==COM_SET_SIZE_DOUBLE) {
         if (ndims == 2) {
            len = COM_LEN_2NC_S(bnd[ibc]);
            len_sendd[proc] += 4*len;
            len = COM_LEN_2NC_R(bnd[ibc]);
            len_recvd[proc] += 4*len;
            len = COM_LEN_1ZC_S(bnd[ibc]);
            len_sendd[proc] += len;
            len = COM_LEN_1ZC_R(bnd[ibc]);
            len_recvd[proc] += len;
         } else {
            len = COM_LEN_2NC_R(bnd[ibc]);
            len_recvd[proc] += 6*len;
            len = COM_LEN_2NC_S(bnd[ibc]);
            len_sendd[proc] += 6*len;
            len = COM_LEN_1ZC_S(bnd[ibc]);
            len_sendd[proc] += len;
            len = COM_LEN_1ZC_R(bnd[ibc]);
            len_recvd[proc] += len;
         } 

      } else if (comflag==COM_SET_SIZE_INT) {
         len_sendi[proc] = 0;
         len_recvi[proc] = 0;
      }
   }
   if ((ifparallel)&&(comflag==COM_SEND)) {
      postbuf(QBND,COM_SEND);
   }
   STOPTIMER(QBND,comflag) ;
   return(error);
}
