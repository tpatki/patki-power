#include "irs.h"
#include "irscom.h"
#include "FunctionTimer.h" 
#include "Tagorder.h"
int vsamecom(int stepflag, int comflag)
{ 
   int i,j,k,id;
   int ip;
   int len;
   int ibc;
   int ngrp;
   int iblk;
   int error;
   int *ndx;
   double mass;
   double norm;
   double *x;
   double *y;
   double *z;
   double *nm;
   double *xa;
   double *ya;
   double *za;
   error = 0;
   if  (!ifvsame) { 
      return(error);
   }
   if (ifparallel) {
      STARTTIMER(VSAMECOM) ;
      curcombuf = VSAMECOM;
      if (comflag==COM_COLLECT) {
         initbuf(VSAMECOM,COM_COLLECT);
      } 
   } 
   if (ifcom) {
      for (iblk = 0; iblk < nblk; iblk++ ) {
         for (ibc = 0 ; ibc < domains[iblk].nbnd; ibc++) {
            ndx = domains[iblk].bnd[ibc].ndx_send;
            len = domains[iblk].bnd[ibc].len_nsend1+
                  domains[iblk].bnd[ibc].len_nsend2+domains[iblk].bnd[ibc].len_nsendc;
            for (i = 0; i < len; i++) {
               domains[iblk].node[ndx[i]]++;
            }
         }
      }
   }
   for (id = 0; id < vsame_max_id; id++) {
      if ((vsame_order[id].len > 0) && (comflag == COM_COLLECT)) {
         iblk = vsame_order[id].blk[0];
         ibc = vsame_order[id].tag[0];
         ngrp = domains[iblk].bc[ibc].ngrp;
         if (ndims == 2) {
            nm = ALLOT(double,ngrp);
            xa = ALLOT(double,ngrp);
            ya = ALLOT(double,ngrp);
         } else {
            nm = ALLOT(double,ngrp);
            xa = ALLOT(double,ngrp);
            ya = ALLOT(double,ngrp);
            za = ALLOT(double,ngrp);
         }
         for (j = 0; j < ngrp; j++ ) {
            nm[j] = 0.;
            xa[j] = 0.;
            ya[j] = 0.;
            if (ndims == 3) {
               za[j] = 0.;
            }
         }
         for (i = 0; i < vsame_order[id].len; i++) {
            iblk = vsame_order[id].blk[i];
            ibc = vsame_order[id].tag[i];
            len = domains[iblk].bc[ibc].lgrp;
            ndx = domains[iblk].bc[ibc].ndx;
            if (stepflag == VSAMECOM1) {
               x = domains[iblk].xdot;
               y = domains[iblk].ydot;
               if (ndims == 3) z = domains[iblk].zdot;
            } else if (stepflag == VSAMECOM2) {
               x = domains[iblk].delx;
               y = domains[iblk].dely;
               if (ndims == 3) z = domains[iblk].delz;
            }
            if (ndims == 2) {
               if (stepflag == VSAMECOM0) {
                  for (k = 0; k < len; k++ ) {
                     norm = 1./domains[iblk].node[ndx[k]];
                     nm[0] += domains[iblk].nmass[ndx[k]]*norm;
                     xa[0] += x[ndx[k]]*norm;
                     ya[0] += y[ndx[k]]*norm;
                  }
               } else {
                  for (k = 0; k < len; k++ ) {
                     norm = 1./domains[iblk].node[ndx[k]];
                     mass = domains[iblk].nmass[ndx[k]]*norm;
                     nm[0] += mass;
                     xa[0] += x[ndx[k]]*mass;
                     ya[0] += y[ndx[k]]*mass;
                  }
               }
            } else {
               for (j = 0; j < ngrp; j++ ) {
                  ip = 0;
                  if (stepflag == VSAMECOM0) {
                     for (k = 0; k < len; k++ ) {
                        norm = 1./domains[iblk].node[ndx[ip]];
                        nm[j] += domains[iblk].nmass[ndx[ip]]*norm;
                        xa[j] += x[ndx[ip]]*norm;
                        ya[j] += y[ndx[ip]]*norm;
                        za[j] += z[ndx[ip]]*norm;
                        ip++;
                     }
                  } else {
                     for (k = 0; k < len; k++ ) {
                        norm = 1./domains[iblk].node[ndx[ip]];
                        nm[j] += domains[iblk].nmass[ndx[ip]]*norm;
                        xa[j] += x[ndx[ip]]*domains[iblk].nmass[ndx[ip]]*norm;
                        ya[j] += y[ndx[ip]]*domains[iblk].nmass[ndx[ip]]*norm;
                        za[j] += z[ndx[ip]]*domains[iblk].nmass[ndx[ip]]*norm;
                        ip++;
                     }
                  }
               }
            }
         }
         if ((ifparallel) && (vsame_procs[id]>0)) {
            putdata(nm,ngrp,COM_DOUBLE,id,NULL,COM_DIRECT_ID);
            putdata(xa,ngrp,COM_DOUBLE,id,NULL,COM_DIRECT_ID);
            putdata(ya,ngrp,COM_DOUBLE,id,NULL,COM_DIRECT_ID);
            if (ndims == 3) {
               putdata(za,ngrp,COM_DOUBLE,id,NULL,COM_DIRECT_ID);
            }
         } else {
            if (ndims == 2) {
               xa[0] = xa[0]/(nm[0]+ptiny);
               ya[0] = ya[0]/(nm[0]+ptiny);
            } else {
               for (j = 0; j < ngrp; j++ ) {
                  xa[j] = xa[j]/(nm[j]+ptiny);
                  ya[j] = ya[j]/(nm[j]+ptiny);
                  za[j] = za[j]/(nm[j]+ptiny);
               }
            }
            for (i = 0; i < vsame_order[id].len; i++) {
               iblk = vsame_order[id].blk[i];
               ibc = vsame_order[id].tag[i];
               len = domains[iblk].bc[ibc].lgrp;
               ndx = domains[iblk].bc[ibc].ndx;
               if (stepflag == VSAMECOM1) {
                  x = domains[iblk].xdot;
                  y = domains[iblk].ydot;
                  if (ndims == 3) z = domains[iblk].zdot;
               } else if (stepflag == VSAMECOM2) {
                  x = domains[iblk].delx;
                  y = domains[iblk].dely;
                  if (ndims == 3) z = domains[iblk].delz;
               }
               if (ndims == 2) {
                  if (stepflag == VSAMECOM0) {
                     for (k = 0; k < len; k++ ) {
                        x[ndx[k]]=xa[0]*domains[iblk].nmass[ndx[k]];
                        y[ndx[k]]=ya[0]*domains[iblk].nmass[ndx[k]];
                     }
                  } else {
                     for (k = 0; k < len; k++ ) {
                        x[ndx[k]]=xa[0];
                        y[ndx[k]]=ya[0];
                     }
                  }
               } else {
                  for (j = 0; j < ngrp; j++ ) {
                     ip = 0;
                     if (stepflag == VSAMECOM0) {
                        for (k = 0; k < len; k++ ) {
                           x[ndx[ip]]=xa[j]*domains[iblk].nmass[ndx[ip]];
                           y[ndx[ip]]=ya[j]*domains[iblk].nmass[ndx[ip]];
                           z[ndx[ip]]=za[j]*domains[iblk].nmass[ndx[ip]];
                           ip++;
                        }
                     } else {
                        for (k = 0; k < len; k++ ) {
                           x[ndx[ip]]=xa[j];
                           y[ndx[ip]]=ya[j];
                           z[ndx[ip]]=za[j];
                           ip++;
                        }
                     }
                  }
               }
            }
         }
         FREEMEM(nm);
         FREEMEM(xa);
         FREEMEM(ya);
         if (ndims == 3) {
            FREEMEM(za);
         }
      }
      if (comflag == COM_SET_SIZE_DOUBLE) {
         len = 0;
         if (vsame_order[id].len > 0) {
            iblk = vsame_order[id].blk[0];
            ibc = vsame_order[id].tag[0];
            ngrp = domains[iblk].bc[ibc].ngrp;
            if (ndims == 2) {
               len  = ngrp*3;
            } else {
               len  = ngrp*4;
            } 
         }
         len_sendd[id] += len;
         len_recvd[id] += len;
      }
      if (comflag == COM_SET_SIZE_INT) {
         len_sendi[id] = 0;
         len_recvi[id] = 0;
      }
   }
   if ((ifparallel) && (comflag == COM_COLLECT)) {
      postbuf(VSAMECOM,COM_COLLECT);
      for (id = 0; id < vsame_max_id; id++) {
         if ((vsame_procs[id]>0) && (vsame_order[id].len > 0)) {
            iblk = vsame_order[id].blk[0];
            ibc = vsame_order[id].tag[0];
            ngrp = domains[iblk].bc[ibc].ngrp;
            if (ndims == 2) {
               nm = ALLOT(double,ngrp);
               xa = ALLOT(double,ngrp);
               ya = ALLOT(double,ngrp);
            } else {
               nm = ALLOT(double,ngrp);
               xa = ALLOT(double,ngrp);
               ya = ALLOT(double,ngrp);
               za = ALLOT(double,ngrp);
            }
            getdata(nm,ngrp,COM_DOUBLE,id,NULL,COM_DIRECT_ID);
            getdata(xa,ngrp,COM_DOUBLE,id,NULL,COM_DIRECT_ID);
            getdata(ya,ngrp,COM_DOUBLE,id,NULL,COM_DIRECT_ID);
            if (ndims == 3) {
               getdata(za,ngrp,COM_DOUBLE,id,NULL,COM_DIRECT_ID);
            }
            if (ndims == 2) {
               xa[0] = xa[0]/(nm[0]+ptiny);
               ya[0] = ya[0]/(nm[0]+ptiny);
            } else {
               for (j = 0; j < ngrp; j++ ) {
                  xa[j] = xa[j]/(nm[j]+ptiny);
                  ya[j] = ya[j]/(nm[j]+ptiny);
                  za[j] = za[j]/(nm[j]+ptiny);
               }
            }
            for (i = 0; i < vsame_order[id].len; i++) {
               iblk = vsame_order[id].blk[i];
               ibc = vsame_order[id].tag[i];
               len = domains[iblk].bc[ibc].lgrp;
               ndx = domains[iblk].bc[ibc].ndx;
               if (stepflag == VSAMECOM1) {
                  x = domains[iblk].xdot;
                  y = domains[iblk].ydot;
                  if (ndims == 3) z = domains[iblk].zdot;
               } else if (stepflag == VSAMECOM2) {
                  x = domains[iblk].delx;
                  y = domains[iblk].dely;
                  if (ndims == 3) z = domains[iblk].delz;
               }
               if (ndims == 2) {
                  if (stepflag == VSAMECOM0) {
                     for (k = 0; k < len; k++ ) {
                        x[ndx[k]]=xa[0]*domains[iblk].nmass[ndx[k]];
                        y[ndx[k]]=ya[0]*domains[iblk].nmass[ndx[k]];
                     }
                  } else {
                     for (k = 0; k < len; k++ ) {
                        x[ndx[k]]=xa[0];
                        y[ndx[k]]=ya[0];
                     }
                  } 
               } else {
                  for (j = 0; j < ngrp; j++ ) {
                     ip = 0;
                     if (stepflag == VSAMECOM0) {
                        for (k = 0; k < len; k++ ) {
                           x[ndx[ip]]=xa[j]*domains[iblk].nmass[ndx[ip]];
                           y[ndx[ip]]=ya[j]*domains[iblk].nmass[ndx[ip]];
                           z[ndx[ip]]=za[j]*domains[iblk].nmass[ndx[ip]];
                           ip++;
                        }
                     } else {
                        for (k = 0; k < len; k++ ) {
                           x[ndx[ip]]=xa[j];
                           y[ndx[ip]]=ya[j];
                           z[ndx[ip]]=za[j];
                           ip++;
                        }
                     } 
                  }
               }
            }
            FREEMEM(nm);
            FREEMEM(xa);
            FREEMEM(ya);
            if (ndims == 3) {
               FREEMEM(za);
            }
         }
      }
      freebuf(VSAMECOM,COM_COLLECT);
   }
   if (ifcom) {
      for (iblk = 0; iblk < nblk; iblk++ ) {
         for (ibc = 0 ; ibc < domains[iblk].nbnd; ibc++) {
            ndx = domains[iblk].bnd[ibc].ndx_send;
            len = domains[iblk].bnd[ibc].len_nsend1+
                  domains[iblk].bnd[ibc].len_nsend2+domains[iblk].bnd[ibc].len_nsendc;
            for (i = 0; i < len; i++) {
               domains[iblk].node[ndx[i]] = 1;
            }
         }
      }
   }
   if (ifparallel) {
      STOPTIMER(VSAMECOM,comflag) ;
   }
   return(error);
}
