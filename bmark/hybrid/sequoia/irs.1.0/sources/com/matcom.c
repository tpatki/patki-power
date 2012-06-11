#include "irs.h"
#include "irscom.h"
#include "irsreg.h"
#include "Boundary.h"
#include "FunctionTimer.h"
#include "SpeciesFraction.h"
void matcom_init(int stepflag);
void matcom_final(void);
void matcom_clear(Domain_t *domain, int mode, SpeciesFraction_t *specmf) ;
void matcom_setbnd(Boundary_t *mbnd, Boundary_t *bnd, int comtype, 
                     Domain_t *domain ) ;
void matcom_init(int stepflag) {
   int proc;
   int iblk;
   for (iblk = 0; iblk < nblk; iblk++) {
      if (domains[iblk].nbnd > 0) {
         if (domains[iblk].mbnd == NULL) {
            domains[iblk].mbnd = MALLOT(Boundary_t,domains[iblk].nbnd);
         }
      }
   }
   combuf_initlen(stepflag);
}
void matcom_final(void) {
   int iblk;
   int ibnd;
   int len;
   for (iblk = 0; iblk < nblk; iblk++) {
      if (domains[iblk].nbnd > 0) {
         for (ibnd = 0; ibnd < domains[iblk].nbnd; ibnd++) {
            FREEMEM(domains[iblk].mbnd[ibnd].zdx_send);
            len = COM_LEN_ALLZ_R(domains[iblk].mbnd[ibnd]);
            if (len > 0) FREEMEM(domains[iblk].mbnd[ibnd].zdx_recv);
         }
         FREEMEM(domains[iblk].mbnd);
      }
   }
}
void matcom_setbnd(Boundary_t *mbnd, Boundary_t *bnd, int comtype, 
                           Domain_t *domain ) 
{
   char *me = "matcom_setbnd";   
   int i;
   int j;
   int grd;
   int len;
   int id, ip;
   int len_layer1;
   int len_layer2;
   int len_layerc;
   int maxlen;
   int *zdx;
   int *iregmix;
   if (comtype == COM_SEND) {
      len = COM_LEN_ALLZ_S((*bnd));
      zdx = COM_ZDX_ALLZ_S((*bnd));
      len_layer1 = COM_LEN_1Z_S((*bnd));
      len_layerc = COM_LEN_1ZC_S((*bnd));
      len_layer2 = COM_LEN_ALLZ_S((*bnd));
      mbnd->len_zsend1 = 0;
      mbnd->len_zsend2 = 0;
      mbnd->len_zsendc = 0;
      mbnd->blk_send   = bnd->blk_send;
      mbnd->bndnbc     = bnd->bndnbc;
      mbnd->buf_int  = MALLOT(int,len + 3);
      maxlen = MIN(2*len,domain->mixmax);
      mbnd->zdx_send = MALLOT(int,maxlen);
      id = 0;
      i = 0;
      for (i = 0; i < len; i++) {
         grd = domain->ireg[zdx[i]];    
         ip = 0;
         if (grd > 0) ip = grd;
         if (grd < 0) {
            grd = -grd; 
            while (grd > 0) {
               mbnd->zdx_send[id] = grd;
               grd = domain->lnkmix[grd - domain->nnalls];
               id++;
               ip--;
               if (id >= (maxlen - 1)) {
                  maxlen += len;
                  mbnd->zdx_send = REALLOT(mbnd->zdx_send,int,maxlen);
               }
            }
         }
         if ((i+1) == len_layer1) mbnd->len_zsend1 = id;
         if ((i+1) == len_layerc) mbnd->len_zsendc = id;
         if ((i+1) == len_layer2) mbnd->len_zsend2 = id;
         mbnd->buf_int[i] = ip;
      }
      mbnd->len_zsend2  = mbnd->len_zsend2 - mbnd->len_zsendc;
      mbnd->len_zsendc  = mbnd->len_zsendc - mbnd->len_zsend1;
      mbnd->buf_int[i++] = mbnd->len_zsend1;
      mbnd->buf_int[i++] = mbnd->len_zsendc;
      mbnd->buf_int[i++] = mbnd->len_zsend2;
   } else if (comtype == COM_RECV) {
      len = COM_LEN_ALLZ_R((*bnd));
      mbnd->len_zrecv1 = mbnd->buf_int[len    ];
      mbnd->len_zrecvc = mbnd->buf_int[len + 1];
      mbnd->len_zrecv2 = mbnd->buf_int[len + 2];
      len = COM_LEN_ALLZ_R((*mbnd));
      if (len > 0) {
         mbnd->zdx_recv = MALLOT(int,len);
      }
      iregmix = domain->ireg + domain->nnalls;
      id = 0;
      for (i = 0; i < len; i++) {
         while ((iregmix[id] != 0) && (id < domain->mixmax)) id++;
         if (id >= domain->mixmax) {
            ctlerror(me,"We've run out of mixed slots.  Increase sclnamix.");
         }
         mbnd->zdx_recv[i] = id + domain->nnalls;
	 iregmix[id] = nreg + 1;
         id++;
      }
      zdx = COM_ZDX_ALLZ_R((*bnd));
      len = COM_LEN_ALLZ_R((*bnd));
      j = 0;
      for (i = 0; i < len; i++) {
         grd = mbnd->buf_int[i];
         if (grd > 0) {
            domain->ireg[zdx[i]] = grd; 
         } else if (grd < 0) {
            domain->nmixzn++;
            domain->ireg[zdx[i]] = -mbnd->zdx_recv[j];
            grd++;
            while(grd < 0) {
               id = mbnd->zdx_recv[j];
               domain->lnkmix[id - domain->nnalls] = mbnd->zdx_recv[j+1];
               domain->grdpnt[id - domain->nnalls] = zdx[i];
               grd++;
               j++;
            }
            id = mbnd->zdx_recv[j];
            domain->lnkmix[id - domain->nnalls] = -1;
            domain->grdpnt[id - domain->nnalls] = zdx[i];
            j++;
         }
      }
   }
}
void matcom_clear(Domain_t *domain, int mode, SpeciesFraction_t *specmf) {
   int i;
   int len;
   int grd;
   int ibnd;
   int *zdx; 
   for (ibnd = 0; ibnd < domain->nbnd; ibnd++) {
      len = COM_LEN_ALLZ_R(domain->bnd[ibnd]);
      zdx = COM_ZDX_ALLZ_R(domain->bnd[ibnd]);
      for (i = 0; i < len; i++) {
         if ((mode == 0) && (domain->ireg[zdx[i]] < 0)) {
            domain->nmixzn--;
            grd = -domain->ireg[zdx[i]];
            while (grd > 0) {
               domain->ireg[grd] = 0;
               if (ifdynspec) {
                  if (specmf[grd].mass_frac != NULL) {
                     FREEMEM(specmf[grd].mass_frac);
                  }
               }
               grd = domain->lnkmix[grd - domain->nnalls];
            }
         } 
         domain->ireg[zdx[i]] = 0; 
         if (ifdynspec) {
            if (specmf[zdx[i]].mass_frac != NULL) {
               FREEMEM(specmf[zdx[i]].mass_frac);
            }
         }
      }
   }
}
