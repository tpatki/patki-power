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
#define CRNSET(a,b,ndx) \
   if ((i1 == -1) && (i2 > 0)) { \
      ndx[i] = ip+zp1; \
   } else if ((i1 > 0) && (i2 == -1)) { \
      ndx[i] = ip+zp2; \
   } else if ((i1 > 0) && (i2 > 0)) { \
      ndx[i] = ip+zp1+zp2; \
   } else if ((i1 == -1) && (i2 == -1)) { \
      ndx[i] = ip+zp1+zp2; \
   } 
#define CRNBCSET(a,b) \
   if ((i1 == -1) && (i2 > 0)) { \
      bc[ip] = bc[ip+zp2]; \
   } else if ((i1 > 0) && (i2 == -1)) { \
      bc[ip] = bc[ip+zp1]; \
   } else if ((i1 > 0) && (i2 > 0)) { \
      bc[ip] = bc[ip+zp1+zp2]; \
   } else if ((i1 == -1) && (i2 == -1)) { \
      bc[ip] = bc[ip+zp1+zp2]; \
   }
#define CRNSETRD(a,b,ndx) \
   if ((i1 == -1) && (i2 > 0)) { \
      ndx[i] = ip+zp1; \
   } else if ((i1 > 0) && (i2 == -1)) { \
      ndx[i] = ip+zp2; \
   } else if ((i1 > 0) && (i2 > 0)) { \
      ndx[i] = ip+zp1+zp2; \
   } else if ((i1 == -1) && (i2 == -1)) { \
      ndx[i] = ip; \
   } ; \
   if ((i1 != 0) && (i2 != 0)) bznord[i] = 2 ;
#define CRNSETND(a,b,ndx) \
   if ((i1 == -1) && (i2 > 0)) { \
      ndx[i] = ip+zp1; \
   } else if ((i1 > 0) && (i2 == -1)) { \
      ndx[i] = ip+zp2; \
   } else if ((i1 > 0) && (i2 > 0)) { \
      ndx[i] = ip+zp1; \
   } else if ((i1 == -1) && (i2 == -1)) { \
      ndx[i] = ip+zp1+zp2; \
   } 
#define CRNBCSETND(a,b) \
   if ((i1 == -1) && (i2 > 0)) { \
      bc[ip] = bc[ip+zp2]; \
   } else if ((i1 > 0) && (i2 == -1)) { \
      bc[ip] = bc[ip+zp1]; \
   } else if ((i1 > 0) && (i2 > 0)) { \
      bc[ip] = bc[ip+zp2]; \
   } else if ((i1 == -1) && (i2 == -1)) { \
      bc[ip] = bc[ip+zp1+zp2]; \
   } ; \
   if ((i1 != 0) && (i2 != 0)) bndord[i] = 2 ;
void genradreflst( Domain_t *domain )
   {
   int i,j,k,ibc,len ;
   int stride[6];
   int rphozlen;
   int rphonlen;
   int count;
   int i1,i2,i3;
   int s1,s2,s3;
   int ip;
   int zp1,zp2;
   int *bc;
   int *bcp;
   int *ndx;
   int *bznord ;
   int *bndord ;
   int *rphozdx;
   int *rphondx;
   int *rbndndx;
   int *rbndzdx;
   int *ireg;
   int *iregp;
   int *iregr;
   int *node;
   int *nodep;
   int *refstrz;
   int *refstrn;
   int *ir1, *ir2, *ir3, *ir4, *ir5, *ir6;
   stride[0] = -1;
   stride[1] = -domain->jp;
   stride[2] = 1;
   stride[3] = domain->jp;
   stride[4] = domain->kp;
   stride[5] = -domain->kp;
   if (domain->rphozlen > 0) {
      FREEMEM(domain->rphozdx);
      FREEMEM(domain->rbndzdx);
      domain->rphozlen = 0;
   }
   if (domain->rphonlen > 0) {
      FREEMEM(domain->rphondx);
      FREEMEM(domain->rbndndx);
      FREEMEM(domain->rphonbc);
      domain->rphonlen = 0;
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
   refstrn = ALLOT(int,len);
   refstrz = ALLOT(int,len);
   for (i = 0; i < len; i++ ) {
      node[i]=0;
      bc[i]=0;
   }
   for (i = 0; i < domain->nnalls; i++ ) {
      ireg[i] = abs(domain->ireg[i]);
      node[i] = domain->node[i];
   }
   rphozdx = ALLOT(int,domain->nnalls);
   rphondx = ALLOT(int,domain->nnalls);
   rphozlen = 0;
   rphonlen = 0;
   if (ndims == 2) {
      for (j = domain->jmin-1;j<=domain->jmax;j++) {
         for (i = domain->imin-1;i<=domain->imax;i++) {
            ip = i + j*domain->jp;
            if (domain->ireg[ip]==0) {
               rphozdx[rphozlen] = ip;
               rphozlen++;
            }
         }
      }
      for (j = domain->jmin-1;j<=domain->jmax+1;j++) {
         for (i = domain->imin-1;i<=domain->imax+1;i++) {
            ip = i + j*domain->jp;
            if (domain->node[ip]==0) {
               rphondx[rphonlen] = ip;
               rphonlen++;
            }
         }
      }
   } else {
      for (k = domain->kmin-1;k<=domain->kmax;k++) {
         for (j = domain->jmin-1;j<=domain->jmax;j++) {
            for (i = domain->imin-1;i<=domain->imax;i++) {
               ip = i + j*domain->jp + k*domain->kp;
               if (domain->ireg[ip]==0) {
                  rphozdx[rphozlen] = ip;
                  rphozlen++;
               }
            }
         }
      }
      for (k = domain->kmin-1;k<=domain->kmax+1;k++) {
         for (j = domain->jmin-1;j<=domain->jmax+1;j++) {
            for (i = domain->imin-1;i<=domain->imax+1;i++) {
               ip = i + j*domain->jp + k*domain->kp;
               if (domain->node[ip]==0) {
                  rphondx[rphonlen] = ip;
                  rphonlen++;
               }
            }
         }
      }
   } 
   rbndzdx=ALLOT(int,rphozlen);
   rbndndx=ALLOT(int,rphonlen);
   domain->rphozlen=rphozlen;
   domain->rphonlen=rphonlen;
   bznord = ALLOT(int,rphozlen);
   for ( i = 0 ; i < rphozlen ; i++ ) bznord[i] = 0 ;
   bndord = ALLOT(int,rphonlen);
   for ( i = 0 ; i < rphonlen ; i++ ) bndord[i] = 0 ;
   for (ibc=0;ibc<domain->nbnd;ibc++) {
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
   for (ibc=0;ibc<domain->nbc;ibc++) {
      ndx = domain->bc[ibc].ndx ;
      len = domain->bc[ibc].len ;
      iregp =  ireg + domain->bc[ibc].pz ;
      iregr =  domain->ireg + domain->bc[ibc].rz ;
      nodep =  node + domain->bc[ibc].pn ;
      bcp =  bc + domain->bc[ibc].pn ;
      for ( i = 0 ; i < len ; i++ ) 
	 {
         nodep[ndx[i]]=ndx[i];
         bcp[ndx[i]]=ibc;
         bc[ndx[i]]=ibc;
         }
      if (domain->bc[ibc].rtype == OPEN)
	{
	for ( i = 0 ; i < len ; i++ )
	  {
	  if (iregr[ndx[i]] != 0) 
	    {
	    iregp[ndx[i]] = -1 ;
	    }
	  }
	}
      else
	{
	for ( i = 0 ; i < len ; i++ )
	  {
	  if (iregr[ndx[i]] != 0) 
	    { 
	    iregp[ndx[i]]=ndx[i]+domain->bc[ibc].rz;
	    }
          }
        }
   }
   for (i = 0; i < rphozlen; i++) {
      ip = rphozdx[i];
      rbndzdx[i] = ireg[ip];
      if (rbndzdx[i] != 0) bznord[i] = 1 ;
   }
   for (i = 0; i < rphonlen; i++) {
      ip = rphondx[i];
      rbndndx[i] = node[ip];
      if (rbndndx[i] > 0) bndord[i] = 1 ;
   }
   for (i = 0; i < rphozlen; i++) {
      ip = rphozdx[i];
      if (ireg[ip] == 0) {
         if ( ndims == 2 ) {
            i1 = 0;
            i2 = 0;
            SIDESET(ireg,1,domain->jp,ir1,ir2,ir3,ir4);
            CRNCHK(1,domain->jp);
            CRNSETRD(i1,i2,rbndzdx);
         } else {
            i1 = 0;
            i2 = 0;
            SIDESET(ireg,1,domain->jp,ir1,ir2,ir3,ir4);
            CRNCHK(1,domain->jp);
            if ( (i1 !=0 ) && (i2 !=0 ) ) { CRNSETRD(i1,i2,rbndzdx); }
            i1 = 0;
            i2 = 0;
            SIDESET(ireg,1,domain->kp,ir1,ir2,ir3,ir4);
            CRNCHK(1,domain->kp);
            if ( (i1 !=0 ) && (i2 !=0 ) ) { CRNSETRD(i1,i2,rbndzdx); }
            i1 = 0;
            i2 = 0;
            SIDESET(ireg,domain->jp,domain->kp,ir1,ir2,ir3,ir4);
            CRNCHK(domain->jp,domain->kp);
            if ( (i1 !=0 ) && (i2 !=0 ) ) { CRNSETRD(i1,i2,rbndzdx); }
         }
      } 
   }
   for (i = 0; i < rphonlen; i++) {
      ip = rphondx[i];
      if (node[ip] == 0) {
         if ( ndims == 2 ) {
            i1 = 0;
            i2 = 0;
            SIDESET(node,1,domain->jp,ir1,ir2,ir3,ir4);
            CRNCHK(1,domain->jp);
            CRNSETND(i1,i2,rbndndx);
            CRNBCSETND(i1,i2);
         } else {
            i1 = 0;
            i2 = 0;
            SIDESET(node,1,domain->jp,ir1,ir2,ir3,ir4);
            CRNCHK(1,domain->jp);
            if ( (i1 !=0 ) && (i2 !=0 ) ) {
               CRNSETND(i1,i2,rbndndx);
               CRNBCSETND(i1,i2);
            }
            i1 = 0;
            i2 = 0;
            SIDESET(node,1,domain->kp,ir1,ir2,ir3,ir4);
            CRNCHK(1,domain->kp);
            if ( (i1 !=0 ) && (i2 !=0 ) ) {
               CRNSETND(i1,i2,rbndndx);
               CRNBCSETND(i1,i2);
            }
            i1 = 0;
            i2 = 0;
            SIDESET(node,domain->jp,domain->kp,ir1,ir2,ir3,ir4);
            CRNCHK(domain->jp,domain->kp);
            if ( (i1 !=0 ) && (i2 !=0 ) ) {
               CRNSETND(i1,i2,rbndndx);
               CRNBCSETND(i1,i2);
            }
         }
      }
   }
   if (ndims == 3) {
      for (i = 0; i < rphozlen; i++) {
         ip = rphozdx[i];
	 refstrz[ip] = rbndzdx[i] - ip ;
         if (rbndzdx[i]>0) {
            if (ireg[rbndzdx[i]]<0) {
               ireg[ip] =  -2;
            } else {
               ireg[ip] = rbndzdx[i];
            }
         } else {
            ireg[ip] = rbndzdx[i];
         }
      }
      for (i = 0; i < rphonlen; i++) {
         ip = rphondx[i];
	 refstrn[ip] = rbndndx[i] - ip ;
         if (rbndndx[i]>0) {
            if (node[rbndndx[i]]<0) {
               node[ip] =  -2;
            } else {
               node[ip] = rbndndx[i];
            }
         } else {
            node[ip] = rbndndx[i];
         }
      }
      for (i = 0; i < rphozlen; i++) {
         ip = rphozdx[i];
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
               rbndzdx[i] = ip + refstrz[ip - (i1+1)*s1 - (i2+1)*s2 - (i3+1)*s3] ;
            } else if ((i1 <= -1) && (i2 <= -1) && (i3 > 0  )) {
               rbndzdx[i] = ip + refstrz[ip + s1] ;
            } else if ((i1 <= -1) && (i2 > 0  ) && (i3 <= -1)) {
               rbndzdx[i] = ip + refstrz[ip + s1] ;
            } else if ((i1 <= -1) && (i2 > 0  ) && (i3 > 0  )) {
               rbndzdx[i] = ip + refstrz[ip + s2] ; 
            } else if ((i1 > 0  ) && (i2 <= -1) && (i3 <= -1)) {
               rbndzdx[i] = ip + refstrz[ip + s2] ;
            } else if ((i1 > 0  ) && (i2 <= -1) && (i3 > 0  )) {
               rbndzdx[i] = ip + refstrz[ip + s1] ; 
            } else if ((i1 > 0  ) && (i2 > 0  ) && (i3 <= -1)) {
               rbndzdx[i] = ip + refstrz[ip + s1] ; 
            } else if ((i1 > 0  ) && (i2 > 0  ) && (i3 > 0  )) {
               rbndzdx[i] = ip + refstrz[ip + s1] ;
            }
	    if ((i1 != 0) && (i2 != 0) && (i3 != 0)) bznord[i] = 3 ;
         }
      }
      for (i = 0; i < rphonlen; i++) {
         ip = rphondx[i];
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
	       rbndndx[i] = ip + refstrn[ip - (i1+1)*s1 - (i2+1)*s2 - (i3+1)*s3]; 
            } else if ((i1 <= -1) && (i2 <= -1) && (i3 > 0  )) {
               rbndndx[i] = ip + refstrn[ip + s3] ;
               bc[ip] = bc[ip+s3];
            } else if ((i1 <= -1) && (i2 > 0  ) && (i3 <= -1)) {
               rbndndx[i] = ip + refstrn[ip + s2] ;
               bc[ip] = bc[ip+s2];
            } else if ((i1 <= -1) && (i2 > 0  ) && (i3 > 0  )) {
               rbndndx[i] = ip + refstrn[ip + s2] ;
               bc[ip] = bc[ip+s2];
            } else if ((i1 > 0  ) && (i2 <= -1) && (i3 <= -1)) {
               rbndndx[i] = ip + refstrn[ip + s1] ;
               bc[ip] = bc[ip+s1];
            } else if ((i1 > 0  ) && (i2 <= -1) && (i3 > 0  )) {
               rbndndx[i] = ip + refstrn[ip + s1] ;
               bc[ip] = bc[ip+s1];
            } else if ((i1 > 0  ) && (i2 > 0  ) && (i3 <= -1)) {
               rbndndx[i] = ip + refstrn[ip + s1] ;
               bc[ip] = bc[ip+s1];
            } else if ((i1 > 0  ) && (i2 > 0  ) && (i3 > 0  )) {
               rbndndx[i] = ip + refstrn[ip + s1] ;
               bc[ip] = bc[ip+s1];
            }
	    if ((i1 != 0) && (i2 != 0) && (i3 != 0)) bndord[i] = 3 ;  
         }
      }
   }
   count = 0;
   for (i = 0; i < rphozlen; i++) {
      if (rbndzdx[i]>0) {
         count++;
      }
   }
   domain->rbndzdx = ALLOT(int,count);
   domain->rphozdx = ALLOT(int,count);
   count=0;
   for (i = 0; i < rphozlen; i++) {
      if (rbndzdx[i]>0 && bznord[i] == 1) {
         domain->rbndzdx[count] = rbndzdx[i];
         domain->rphozdx[count] = rphozdx[i];
         count++;
      }
   }
   for (i = 0; i < rphozlen; i++) {
      if (rbndzdx[i]>0 && bznord[i] == 2) {
         domain->rbndzdx[count] = rbndzdx[i];
         domain->rphozdx[count] = rphozdx[i];
         count++;
      }
   }
   for (i = 0; i < rphozlen; i++) {
      if (rbndzdx[i]>0 && bznord[i] == 3) {
         domain->rbndzdx[count] = rbndzdx[i];
         domain->rphozdx[count] = rphozdx[i];
         count++;
      }
   }
   domain->rphozlen = count;
   count = 0;
   for (i = 0; i < rphonlen; i++) {
      if (rbndndx[i]>0) {
         count++;
      }
   }
   domain->rbndndx = ALLOT(int,count);
   domain->rphondx = ALLOT(int,count);
   domain->rphonbc = ALLOT(int,count);
   count=0;
   for (i = 0; i < rphonlen; i++) {
      if (rbndndx[i]>0 && bndord[i] == 1) {
         domain->rbndndx[count] = rbndndx[i]-rphondx[i];
         domain->rphondx[count] = rphondx[i];
         domain->rphonbc[count] = bc[rphondx[i]];
         count++;
      }
   }
   for (i = 0; i < rphonlen; i++) {
      if (rbndndx[i]>0 && bndord[i] == 2) {
         domain->rbndndx[count] = rbndndx[i]-rphondx[i];
         domain->rphondx[count] = rphondx[i];
         domain->rphonbc[count] = bc[rphondx[i]];
         count++;
      }
   }
   for (i = 0; i < rphonlen; i++) {
      if (rbndndx[i]>0 && bndord[i] == 3) {
         domain->rbndndx[count] = rbndndx[i]-rphondx[i];
         domain->rphondx[count] = rphondx[i];
         domain->rphonbc[count] = bc[rphondx[i]];
         count++;
      }
   }
   domain->rphonlen = count;
   FREEMEM(rphondx);
   FREEMEM(rbndndx);
   FREEMEM(rbndzdx);
   FREEMEM(rphozdx);
   FREEMEM(bznord);
   FREEMEM(bndord);
   FREEMEM(bc);
   FREEMEM(ireg);
   FREEMEM(node);
   FREEMEM(refstrz);
   FREEMEM(refstrn);
}
#undef SIDESET
#undef CRNCHK
#undef CRNSET
#undef CRNBCSET
#undef CRNSETRD
#undef CRNSETND
#undef CRNBCSETND
#undef SIDESET3D
#undef CRNCHK3D
#undef CRNSET3D
