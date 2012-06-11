#include "irs.h"
#include "irsbndry.h"
#include "Boundary.h"
void setcrnlst(int len, int *ndx, int* nflg, int nstr,Boundary_t *bnd, 
               Domain_t *domain) 
{
   int i;
   int lenz;
   int lenn;
   int i1,i2;
   int flag[6];
   int rn,pn;
   int rz,pz;
   int noffsend,noffrecv;
   int zoffsend,zoffrecv;
   for (i=0;i<6;i++) {
      flag[i]=1;
   }
   if (len>2) {
      i1 = 1;
      i2 = len-1;
   } else {
      i1 = 0;
      i2 = len;
   }
   for (i=i1;i<i2;i++) {
      if (domain->node[ndx[i]+1]==1) {
         flag[0]=0;
      }
      if (domain->node[ndx[i]-1]==1) {
         flag[1]=0;
      }
      if (domain->node[ndx[i]+domain->jp]==1) {
         flag[2]=0;
      }
      if (domain->node[ndx[i]-domain->jp]==1) {
         flag[3]=0;
      }
      if (ndims==3) {
         if (domain->node[ndx[i]+domain->kp]==1) {
            flag[4]=0;
         }
         if (domain->node[ndx[i]-domain->kp]==1) {
            flag[5]=0;
         }
      }
   }
   pn = flag[0]-flag[1]+(flag[2]-flag[3])*domain->jp+(flag[4]-flag[5])*domain->kp;
   rn = -pn;
   if (ndims==2) {
      rz = rn - flag[1] - flag[3]*domain->jp;
      pz = - flag[1] - flag[3]*domain->jp;
   } else {
      rz = rn - flag[1] - flag[3]*domain->jp - flag[5]*domain->kp;
      pz = - flag[1] - flag[3]*domain->jp - flag[5]*domain->kp;
   }
   bnd->pn = pn;
   bnd->rz = rz;
   bnd->pz = pz;
   lenz=0;
   lenn=0;
   noffsend = bnd->len_nsend1;
   noffrecv = bnd->len_nrecv1;
   zoffsend = bnd->len_zsend1;
   zoffrecv = bnd->len_zrecv1;
   for (i=0;i<len;i++) {
      bnd->ndx_send[i+noffsend] = ndx[i]+rn;
      bnd->ndx_recv[i+noffrecv] = ndx[i]+pn;
      lenn++;
      if ((domain->ireg[ndx[i]+rz]!=0) &&
          (nflg[ndx[i]+nstr]!=0)) {
         bnd->zdx_send[lenz + zoffsend] = ndx[i]+rz;
         bnd->zdx_recv[lenz + zoffrecv] = ndx[i]+pz;
         lenz++;
      }
   }
   bnd->len_zsendc = lenz;
   bnd->len_zrecvc = lenz;
   bnd->len_nsendc = lenn;
   bnd->len_nrecvc = lenn;
}
