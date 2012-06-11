#include "irs.h"
#include "irsbndry.h"
#define SIDESET(v,s1,s2,v1,v2,v3,v4) \
   v1 = v - s2; \
   v2 = v + s1; \
   v3 = v + s2; \
   v4 = v - s1;
#define SIDESET3D(v,v1,v2,v3,v4,v5,v6) \
   v1 = v - 1; \
   v2 = v - domain->jp; \
   v3 = v + 1 ; \
   v4 = v + domain->jp; \
   v5 = v + domain->kp; \
   v6 = v - domain->kp;
#define CRNCHK(s1,s2) \
   if ((ir1[ip]!=0) && (ir2[ip]!=0)) { \
      i1 = ir1[ip]; \
      i2 = ir2[ip]; \
      zp1 = -s2; \
      zp2 = s1; \
   } else if ((ir2[ip]!=0) && (ir3[ip]!=0)) { \
      i1 = ir2[ip]; \
      i2 = ir3[ip]; \
      zp1 = s1; \
      zp2 = s2; \
   } else if ((ir3[ip]!=0) && (ir4[ip]!=0)) { \
      i1 = ir3[ip]; \
      i2 = ir4[ip]; \
      zp1 = s2; \
      zp2 = -s1; \
   } else if ((ir4[ip]!=0) && (ir1[ip]!=0)) { \
      i1 = ir4[ip]; \
      i2 = ir1[ip]; \
      zp1 = -s1; \
      zp2 = -s2; \
   }
#define CRNCHK3D(a,b,c) \
   if ((ir##a[ip] != 0) && (ir##b[ip] != 0 ) && (ir##c[ip] != 0 )) { \
      i1 = ir##a[ip]; \
      i2 = ir##b[ip]; \
      i3 = ir##c[ip]; \
      s1 = stride[a-1]; \
      s2 = stride[b-1]; \
      s3 = stride[c-1]; \
   }
#define CRNSETZN(a,b,ndx) \
   if ((a == -1) && (b > 0)) { \
      ndx[i] = ip+zp1; \
   } else if ((a > 0) && (b == -1)) { \
      ndx[i] = ip+zp2; \
   } else if ((a > 0) && (b > 0)) { \
      ndx[i] = ip+zp1+zp2; \
   } else if ((a == -1) && (b == -1)) { \
      ndx[i] = ip+zp1+zp2; \
   } ;  \
   if ((a != 0) && (b != 0)) bznord[i] = 2 ;
#define CRNSETND(a,b,ndx) \
   if ((a == -1) && (b > 0)) { \
      ndx[i] = ip+zp1; \
   } else if ((a > 0) && (b == -1)) { \
      ndx[i] = ip+zp2; \
   } else if ((a > 0) && (b > 0)) { \
      ndx[i] = ip+zp1 ; \
   } else if ((a == -1) && (b == -1)) { \
      ndx[i] = ip+zp1+zp2; \
   } ;  \
   if ((a != 0) && (b != 0)) bndord[i] = 2 ;
#define CRNBCSET(a,b) \
   if ((a == -1) && (b > 0)) { \
      bc[ip] = bc[ip+zp2]; \
   } else if ((a > 0) && (b == -1)) { \
      bc[ip] = bc[ip+zp1]; \
   } else if ((a > 0) && (b > 0)) { \
      bc[ip] = bc[ip + zp2]; \
   } else if ((a == -1) && (b == -1)) { \
      bc[ip] = bc[ip+zp1+zp2]; \
   }
void genreflst( Domain_t *domain ) {
   int i,j,k,ibc,len ;
   int stride[6];
   int phozlen;
   int phonlen;
   int count;
   int i1,i2,i3;
   int s1,s2,s3;
   int ip;
   int zp1,zp2;
   int *bc;
   int *bcp;
   int *ndx;
   int *phozdx;
   int *phondx;
   int *bndndx;
   int *bndzdx;
   int *ireg;
   int *iregp;
   int *iregr;
   int *node;
   int *nodep;
   int *bznord;
   int *bndord;
   int *refstrz;
   int *refstrn;
   int *ir1, *ir2, *ir3, *ir4, *ir5, *ir6;
   stride[0] = -1;
   stride[1] = -domain->jp;
   stride[2] = 1;
   stride[3] = domain->jp;
   stride[4] = domain->kp;
   stride[5] = -domain->kp;
   if (domain->phozlen > 0) {
      FREEMEM(domain->phozdx);
      FREEMEM(domain->bndzdx);
      domain->phozlen = 0;
   }
   if (domain->phonlen > 0) {
      FREEMEM(domain->phondx);
      FREEMEM(domain->bndndx);
      FREEMEM(domain->phonbc);
      domain->phonlen = 0;
   }
   ireg = ALLOT(int,domain->nnalls);
   if (ndims == 3) {
      len = (domain->imax-domain->imin+NPNL+NPNR+2)*
            (domain->jmax-domain->jmin+NPNL+NPNR+2)*
            (domain->kmax-domain->kmin+NPNL+NPNR+2);
   } else {
      len = (domain->imax-domain->imin+NPNL+NPNR+2)*
            (domain->jmax-domain->jmin+NPNL+NPNR+2);
   }
   node = ALLOT(int,len);
   bc = ALLOT(int,len);
   refstrz = ALLOT(int,len);
   refstrn = ALLOT(int,len);
   for (i = 0; i < len; i++ ) {
      node[i]=0;
      bc[i]=0;
      refstrz[i]=0;
      refstrn[i]=0;
   }
   for (i = 0; i < domain->nnalls; i++ ) {
      ireg[i] = abs(domain->ireg[i]);
      node[i] = domain->node[i];
   }
   phozdx = ALLOT(int,domain->nnalls);
   phondx = ALLOT(int,domain->nnalls);
   phozlen = 0;
   phonlen = 0;
   if (ndims == 2) {
      for (j = domain->jmin-1; j <= domain->jmax; j++) {
         for (i = domain->imin-1; i <= domain->imax; i++) {
            ip = i + j*domain->jp;
            if (domain->ireg[ip]==0) {
               phozdx[phozlen] = ip;
               phozlen++;
            }
         }
      }
      for (j = domain->jmin-1; j <= domain->jmax+1; j++) {
         for (i = domain->imin-1; i <= domain->imax+1; i++) {
            ip = i + j*domain->jp;
            if (domain->node[ip]==0) {
               phondx[phonlen] = ip;
               phonlen++;
            }
         }
      }
   } else {
      for (k = domain->kmin-1; k <= domain->kmax; k++) {
         for (j = domain->jmin-1; j <= domain->jmax; j++) {
            for (i = domain->imin-1; i <= domain->imax; i++) {
               ip = i + j*domain->jp + k*domain->kp;
               if (domain->ireg[ip]==0) {
                  phozdx[phozlen] = ip;
                  phozlen++;
               }
            }
         }
      }
      for (k = domain->kmin-1;k<=domain->kmax+1;k++) {
         for (j = domain->jmin-1;j<=domain->jmax+1;j++) {
            for (i = domain->imin-1;i<=domain->imax+1;i++) {
               ip = i + j*domain->jp + k*domain->kp;
               if (domain->node[ip]==0) {
                  phondx[phonlen] = ip;
                  phonlen++;
               }
            }
         }
      }
   } 
   bndzdx=ALLOT(int,phozlen);
   bndndx=ALLOT(int,phonlen);
   domain->phozlen = phozlen;
   domain->phonlen = phonlen;
   bznord = ALLOT(int,phozlen);
   for ( i = 0 ; i < phozlen ; i++ ) {
      bznord[i] = 0 ;
   }
   bndord = ALLOT(int,phonlen);
   for ( i = 0 ; i < phonlen ; i++ ) {
      bndord[i] = 0 ;
   }
   for (ibc = 0; ibc < domain->nbnd; ibc++) {
      len = domain->bnd[ibc].len_zrecv1+domain->bnd[ibc].len_zrecvc;
      ndx = domain->bnd[ibc].zdx_recv;
      for ( i = 0 ; i < len ; i++ ) {
         ireg[ndx[i]] = -1;
      }
      len = domain->bnd[ibc].len_nrecv2+domain->bnd[ibc].len_nrecvc;
      ndx = domain->bnd[ibc].ndx_recv+domain->bnd[ibc].len_nrecv1;
      for ( i = 0 ; i < len ; i++ ) {
         node[ndx[i]] = -1;
      }
   }  
   for (ibc = 0; ibc < domain->nbc; ibc++) {
      ndx = domain->bc[ibc].ndx ;
      len = domain->bc[ibc].len ;
      iregp =  ireg + domain->bc[ibc].pz ;
      iregr =  domain->ireg + domain->bc[ibc].rz ;
      nodep =  node + domain->bc[ibc].pn;
      bcp =  bc + domain->bc[ibc].pn;
      for ( i = 0 ; i < len ; i++ ) {
         nodep[ndx[i]] = ndx[i];
         bcp[ndx[i]]   = ibc;
         bc[ndx[i]]    = ibc;
         if (iregr[ndx[i]] != 0) { 
            iregp[ndx[i]]=ndx[i]+domain->bc[ibc].rz;
         }
      }
   }
   for (i = 0; i < phozlen; i++) {
      ip = phozdx[i];
      bndzdx[i] = ireg[ip];
      if (bndzdx[i] != 0) bznord[i] = 1 ;
   }
   for (i = 0; i < phonlen; i++) {
      ip = phondx[i];
      bndndx[i] = node[ip];
      if (bndndx[i] > 0) bndord[i] = 1 ;
   }
   for (i = 0; i < phozlen; i++) {
      ip = phozdx[i];
      if (ireg[ip] == 0) {
         if ( ndims == 2 ) {
            i1 = 0;
            i2 = 0;
            SIDESET(ireg,1,domain->jp,ir1,ir2,ir3,ir4);
            CRNCHK(1,domain->jp);
            CRNSETZN(i1,i2,bndzdx);
         } else {
            i1 = 0;
            i2 = 0;
            SIDESET(ireg,1,domain->jp,ir1,ir2,ir3,ir4);
            CRNCHK(1,domain->jp);
            if ( (i1 !=0 ) && (i2 !=0 ) ) { CRNSETZN(i1,i2,bndzdx); }
            i1 = 0;
            i2 = 0;
            SIDESET(ireg,1,domain->kp,ir1,ir2,ir3,ir4);
            CRNCHK(1,domain->kp);
            if ( (i1 !=0 ) && (i2 !=0 ) ) { CRNSETZN(i1,i2,bndzdx); }
            i1 = 0;
            i2 = 0;
            SIDESET(ireg,domain->jp,domain->kp,ir1,ir2,ir3,ir4);
            CRNCHK(domain->jp,domain->kp);
            if ( (i1 !=0 ) && (i2 !=0 ) ) { CRNSETZN(i1,i2,bndzdx); }
         }
      } 
   }
   for (i = 0; i < phonlen; i++) {
      ip = phondx[i];
      if (node[ip] == 0) {
         if ( ndims == 2 ) {
            i1 = 0;
            i2 = 0;
            SIDESET(node,1,domain->jp,ir1,ir2,ir3,ir4);
            CRNCHK(1,domain->jp);
            CRNSETND(i1,i2,bndndx);
            CRNBCSET(i1,i2);
         } else {
            i1 = 0;
            i2 = 0;
            SIDESET(node,1,domain->jp,ir1,ir2,ir3,ir4);
            CRNCHK(1,domain->jp);
            if ( (i1 !=0 ) && (i2 !=0 ) ) {
               CRNSETND(i1,i2,bndndx);
               CRNBCSET(i1,i2);
            }
            i1 = 0;
            i2 = 0;
            SIDESET(node,1,domain->kp,ir1,ir2,ir3,ir4);
            CRNCHK(1,domain->kp);
            if ( (i1 !=0 ) && (i2 !=0 ) ) {
               CRNSETND(i1,i2,bndndx);
               CRNBCSET(i1,i2);
            }
            i1 = 0;
            i2 = 0;
            SIDESET(node,domain->jp,domain->kp,ir1,ir2,ir3,ir4);
            CRNCHK(domain->jp,domain->kp);
            if ( (i1 !=0 ) && (i2 !=0 ) ) {
               CRNSETND(i1,i2,bndndx);
               CRNBCSET(i1,i2);
            }
         }
      }
   }
   if (ndims == 3) {
      for (i = 0; i < phozlen; i++) {
         ip = phozdx[i];
         refstrz[ip] = bndzdx[i] - ip ;
         if (bndzdx[i]>0) {
            if (ireg[bndzdx[i]]<0) {
               ireg[ip] =  -2;
            } else {
               ireg[ip] = bndzdx[i];
            }
         } else {
            ireg[ip] = bndzdx[i];
         }
      }
      for (i = 0; i < phonlen; i++) {
         ip = phondx[i];
         refstrn[ip] = bndndx[i] - ip ;
         if (bndndx[i]>0) {
            if (node[bndndx[i]]<0) {
               node[ip] =  -2;
            } else {
               node[ip] = bndndx[i];
            }
         } else {
            node[ip] = bndndx[i];
         }
      }
      for (i = 0; i < phozlen; i++) {
         ip = phozdx[i];
         if (ireg[ip] == 0) {
	    i1 = i2 = i3 = 0 ;
            SIDESET3D(ireg,ir1,ir2,ir3,ir4,ir5,ir6);
            CRNCHK3D(1,2,5);
            CRNCHK3D(1,4,5);
            CRNCHK3D(2,3,5);
            CRNCHK3D(3,4,5);
            CRNCHK3D(1,2,6);
            CRNCHK3D(1,4,6);
            CRNCHK3D(2,3,6);
            CRNCHK3D(3,4,6);
            if        ((i1 <= -1) && (i2 <= -1) && (i3 <= -1)) {
               bndzdx[i] = ip + refstrz[ip - (i1+1)*s1-(i2+1)*s2-(i3+1)*s3] ;
            } else if ((i1 <= -1) && (i2 <= -1) && (i3 > 0  )) {
               bndzdx[i] = ip + refstrz[ip + s1] ;
            } else if ((i1 <= -1) && (i2 > 0  ) && (i3 <= -1)) {
               bndzdx[i] = ip + refstrz[ip + s1] ;
            } else if ((i1 <= -1) && (i2 > 0  ) && (i3 > 0  )) {
               bndzdx[i] = ip + refstrz[ip + s2] ;
            } else if ((i1 > 0  ) && (i2 <= -1) && (i3 <= -1)) {
               bndzdx[i] = ip + refstrz[ip + s2] ;
            } else if ((i1 > 0  ) && (i2 <= -1) && (i3 > 0  )) {
               bndzdx[i] = ip + refstrz[ip + s1] ;
            } else if ((i1 > 0  ) && (i2 > 0  ) && (i3 <= -1)) {
               bndzdx[i] = ip + refstrz[ip + s1] ;
            } else if ((i1 > 0  ) && (i2 > 0  ) && (i3 > 0  )) {
               bndzdx[i] = ip + refstrz[ip + s1] ;
            }
            if ((i1 != 0) && (i2 != 0) && (i3 != 0)) bznord[i] = 3 ;
         }
      }
      for (i = 0; i < phonlen; i++) {
         ip = phondx[i];
         if (node[ip] == 0) {
	    i1 = i2 = i3 = 0 ;
            SIDESET3D(node,ir1,ir2,ir3,ir4,ir5,ir6);
            CRNCHK3D(1,2,5);
            CRNCHK3D(1,4,5);
            CRNCHK3D(2,3,5);
            CRNCHK3D(3,4,5);
            CRNCHK3D(1,2,6);
            CRNCHK3D(1,4,6);
            CRNCHK3D(2,3,6);
            CRNCHK3D(3,4,6);
            if        ((i1 <= -1) && (i2 <= -1) && (i3 <= -1)) {
               bc[ip] = bc[ip - (i1+1)*s1 - (i2+1)*s2 - (i3+1)*s3];
               bndndx[i] = ip + refstrn[ip - (i1+1)*s1-(i2+1)*s2-(i3+1)*s3];
            } else if ((i1 <= -1) && (i2 <= -1) && (i3 > 0  )) {
               bndndx[i] = ip + refstrn[ip + s3] ;
               bc[ip] = bc[ip+s3];
            } else if ((i1 <= -1) && (i2 > 0  ) && (i3 <= -1)) {
               bndndx[i] = ip + refstrn[ip + s2] ;
               bc[ip] = bc[ip+s2];
            } else if ((i1 <= -1) && (i2 > 0  ) && (i3 > 0  )) {
               bndndx[i] = ip + refstrn[ip + s2] ;
               bc[ip] = bc[ip+s2];
            } else if ((i1 > 0  ) && (i2 <= -1) && (i3 <= -1)) {
               bndndx[i] = ip + refstrn[ip + s1] ;
               bc[ip] = bc[ip+s1];
            } else if ((i1 > 0  ) && (i2 <= -1) && (i3 > 0  )) {
               bndndx[i] = ip + refstrn[ip + s1] ;
               bc[ip] = bc[ip+s1];
            } else if ((i1 > 0  ) && (i2 > 0  ) && (i3 <= -1)) {
               bndndx[i] = ip + refstrn[ip + s1] ;
               bc[ip] = bc[ip+s1];
            } else if ((i1 > 0  ) && (i2 > 0  ) && (i3 > 0  )) {
               bndndx[i] = ip + refstrn[ip + s1] ;
               bc[ip] = bc[ip+s1];
            }
            if ((i1 != 0) && (i2 != 0) && (i3 != 0)) bndord[i] = 3 ;
         }
      }
   }
   count = 0;
   for (i = 0; i < phozlen; i++) {
      if (bndzdx[i]>0) {
         count++;
      }
   }
   domain->bndzdx = ALLOT(int,count);
   domain->phozdx = ALLOT(int,count);
   count=0;
   for (i = 0; i < phozlen; i++) {
      if ((bndzdx[i]>0)&&(bznord[i]==1)) {
         domain->bndzdx[count] = bndzdx[i];
         domain->phozdx[count] = phozdx[i];
         count++;
      }
   }
   for (i = 0; i < phozlen; i++) {
      if ((bndzdx[i]>0)&&(bznord[i]==2)) {
         domain->bndzdx[count] = bndzdx[i];
         domain->phozdx[count] = phozdx[i];
         count++;
      }
   }
   for (i = 0; i < phozlen; i++) {
      if ((bndzdx[i]>0)&&(bznord[i]==3)) {
         domain->bndzdx[count] = bndzdx[i];
         domain->phozdx[count] = phozdx[i];
         count++;
      }
   }
   domain->phozlen = count;
   count = 0;
   for (i = 0; i < phonlen; i++) {
      if (bndndx[i]>0) {
         count++;
      }
   }
   domain->bndndx = ALLOT(int,count);
   domain->phondx = ALLOT(int,count);
   domain->phonbc = ALLOT(int,count);
   count=0;
   for (i = 0; i < phonlen; i++) {
      if ((bndndx[i]>0)&&(bndord[i]==1)) {
         domain->bndndx[count] = bndndx[i]-phondx[i];
         domain->phondx[count] = phondx[i];
         domain->phonbc[count] = bc[phondx[i]];
         count++;
      }
   }
   for (i = 0; i < phonlen; i++) {
      if ((bndndx[i]>0)&&(bndord[i]==2)) {
         domain->bndndx[count] = bndndx[i]-phondx[i];
         domain->phondx[count] = phondx[i];
         domain->phonbc[count] = bc[phondx[i]];
         count++;
      }
   }
   for (i = 0; i < phonlen; i++) {
      if ((bndndx[i]>0)&&(bndord[i]==3)) {
         domain->bndndx[count] = bndndx[i]-phondx[i];
         domain->phondx[count] = phondx[i];
         domain->phonbc[count] = bc[phondx[i]];
         count++;
      }
   }
   domain->phonlen = count;
   FREEMEM(phondx);
   FREEMEM(bndndx);
   FREEMEM(bndzdx);
   FREEMEM(phozdx);
   FREEMEM(bznord);
   FREEMEM(bndord);
   FREEMEM(refstrn);
   FREEMEM(refstrz);
   FREEMEM(bc);
   FREEMEM(ireg);
   FREEMEM(node);
   bndzonelist(domain);
}
#undef SIDESET
#undef CRNCHK
#undef CRNSETZN
#undef CRNSETND
#undef CRNBCSET
#undef SIDESET3D
#undef CRNCHK3D
#undef CRNSET3D
