#include "irs.h"
#include "FunctionTimer.h"
#include "irscom.h"
typedef struct {
   int *zonal;
   int *nodal;
} COMVERIFY_DATA;
void comverify(void) {
   char msg[MAXLINE];
   int i,j,k;
   int ip, len;
   int ibc;
   int iblk;
   int gotone;
   int *ndx;
   COMVERIFY_DATA *data;
   data = MALLOT(COMVERIFY_DATA,nblk);
   for (iblk = 0; iblk < nblk; iblk++) {
      data[iblk].zonal = MALLOT(int,domains[iblk].nnalls);
      for (i = 0; i < domains[iblk].nnalls; i++) {
         data[iblk].zonal[i] = 0;
      }
      data[iblk].nodal = MALLOT(int,domains[iblk].nnodes);
      for (i = 0; i < domains[iblk].nnodes; i++) {
         data[iblk].nodal[i] = 0;
      }
      if (ndims == 2) {
         for (j = domains[iblk].jmin; j < domains[iblk].jmax; j++) {
            for (i = domains[iblk].imin; i < domains[iblk].imax; i++) {
               ip = i + j * domains[iblk].jp;
               data[iblk].zonal[ip] = 1;
            }
         }
         for (j = domains[iblk].jmin; j <= domains[iblk].jmax; j++) {
            for (i = domains[iblk].imin; i <= domains[iblk].imax; i++) {
               ip = i + j * domains[iblk].jp;
               data[iblk].nodal[ip] = 1;
            }
         }
      } else {
         for (k = domains[iblk].kmin; k < domains[iblk].kmax; k++) {
            for (j = domains[iblk].jmin; j < domains[iblk].jmax; j++) {
               for (i = domains[iblk].imin; i < domains[iblk].imax; i++) {
                  ip = i + j * domains[iblk].jp + k * domains[iblk].kp;
                  data[iblk].zonal[ip] = 1;
               }
            }
         } 
         for (k = domains[iblk].kmin; k <= domains[iblk].kmax; k++) {
            for (j = domains[iblk].jmin; j <= domains[iblk].jmax; j++) {
               for (i = domains[iblk].imin; i <= domains[iblk].imax; i++) {
                  ip = i + j * domains[iblk].jp + k * domains[iblk].kp;
                  data[iblk].nodal[ip] = 1;
               }
            }
         }
      } 
   }
   for (iblk = 0; iblk < nblk; iblk++) {
      varcomset(data[iblk].zonal,-1,"zonal",COM_INT,COM_LAYER1ZC,COM_NOOP,
                domains[iblk].gblk);
      varcomset(data[iblk].nodal,-1,"nodal",COM_INT,COM_LAYER2NC,COM_NOOP,
                domains[iblk].gblk);
   }
   varcom(COM_SET_SIZE);
   varcom(COM_SEND_RECV);
   for (iblk = 0; iblk < nblk; iblk++) {
      ndx = domains[iblk].phozdx;
      len = domains[iblk].phozlen;
      for (i = 0; i < len; i++) {
         data[iblk].zonal[ndx[i]] += 1;
      }
      ndx = domains[iblk].phondx;
      len = domains[iblk].phonlen;
      for (i = 0; i < len; i++) {
         data[iblk].nodal[ndx[i]] += 1;
      }
      gotone = 0;
      if (ndims == 2) {
         for (j = domains[iblk].jmin - 1; j <= domains[iblk].jmax; j++) {
            for (i = domains[iblk].imin - 1; i <= domains[iblk].imax; i++) {
               ip = i + j * domains[iblk].jp;
               if (data[iblk].zonal[ip] != 1) {
                  gotone = ip;
               }
            }
         }
         if (gotone != 0) {
            NDXEXT2D(gotone,i,j,domains[iblk]);
            i = i - NPNL + 1;
            j = j - NPNL + 1;
            sprintf(msg,"Failed zonal communication test (%i) at :%i(%i,%i)",
                    data[iblk].zonal[gotone],domains[iblk].gblk,i,j);
            ctlmsg(msg);
         }
      } else {
         for (k = domains[iblk].kmin - 1; k <= domains[iblk].kmax; k++) {
            for (j = domains[iblk].jmin - 1; j <= domains[iblk].jmax; j++) {
               for (i = domains[iblk].imin - 1; i <= domains[iblk].imax; i++) {
                  ip = i + j * domains[iblk].jp + k * domains[iblk].kp;
                  if (data[iblk].zonal[ip] != 1) {
                     gotone = ip;
                  }
               }
            }
         }
         if (gotone != 0) {
            NDXEXT3D(gotone,i,j,k,domains[iblk]);
            i = i - NPNL + 1;
            j = j - NPNL + 1;
            k = k - NPNL + 1;
            sprintf(msg,"Failed zonal communication test (%i) at :%i(%i,%i,%i)",
                    data[iblk].zonal[gotone],domains[iblk].gblk,i,j,k);
            ctlmsg(msg);
         }
      }
      gotone = 0;
      if (ndims == 2) {
         for (j = domains[iblk].jmin - 1; j <= domains[iblk].jmax + 1; j++) {
            for (i = domains[iblk].imin - 1; i <= domains[iblk].imax + 1; i++) {
               ip = i + j * domains[iblk].jp;
               if (data[iblk].nodal[ip] != 1) {
                  gotone = ip;
               }
            }
         }
         if (gotone != 0) {
            NDXEXT2D(gotone,i,j,domains[iblk]);
            sprintf(msg,"Failed nodal communication test (%i,%i) at :%i(%i,%i)",
                    gotone,data[iblk].nodal[gotone],domains[iblk].gblk,i,j);
            ctlmsg(msg);
         }
      } else {
         for (k = domains[iblk].kmin - 1; k <= domains[iblk].kmax + 1; k++) {
            for (j = domains[iblk].jmin - 1; j <= domains[iblk].jmax + 1; j++) {
               for (i = domains[iblk].imin - 1; i <= domains[iblk].imax + 1; i++) {
                  ip = i + j * domains[iblk].jp + k * domains[iblk].kp;
                  if (data[iblk].nodal[ip] != 1) {
                     gotone = ip;
                  }
               }
            }
         }
         if (gotone != 0) {
            NDXEXT3D(gotone,i,j,k,domains[iblk]);
            sprintf(msg,"Failed nodal communication test (%i) at :%i(%i,%i,%i)",
                    data[iblk].nodal[gotone],domains[iblk].gblk,i,j,k);
            ctlmsg(msg);
         }
      }
      FREEMEM(data[iblk].zonal);
      FREEMEM(data[iblk].nodal);
   }
   FREEMEM(data);
}
