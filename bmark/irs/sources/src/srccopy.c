#include "irs.h"
#include "irssrc.h"
#include "Extents.h"
#include "Source.h"
void srccopy(Domain_t *domain1, Extents_t* ext1, Domain_t *domain2, Extents_t *ext2, 
             int irep)
{
   int i,j,k;
   int ip;
   int count;
   int isrc;
   int isrc2;
   int len;
   Source_t *src1;
   Source_t *src2;
   Extents_t ext0;
   Extents_t ext3;
   Extents_t ext4;
   src1 = domain1->src;
   src2 = domain2->src;
   for (isrc = 0; isrc < domain1->nsrc; isrc++) {
      CPYEXT(ext0,(*ext1));
      CPYEXT(ext3,src1[isrc]);
      if (src1[isrc].cent == ZONAL_ARRAY) {
         if (ext0.imax!=ext0.imin) {
            ext0.imin = ext0.imin - 1 ;
         }
         if (ext0.jmax!=ext0.jmin) {
            ext0.jmin = ext0.jmin - 1 ;
         }
         if (ext0.kmax!=ext0.kmin) {
            ext0.kmin = ext0.kmin - 1 ;
         }
      }
      len = extents_overlap(&ext0,&ext3,&ext4);
      if (len > 0) {
         isrc2 = domain2->nsrc;
         if (isrc2 >= nsrcx) {
            domain2->src = REALLOT(domain2->src, Source_t, isrc2 + 1);
            src2 = domain2->src;
	 }
	 if (ndims == 2) {
	    ext4.kmin = NPNL;
	    ext4.kmax = NPNL;
	 }
         RELEXT(ext4,ext4,(*ext1),(*ext2));
         if (irep > 1) {
            ext4.kmin = ext2->kmin;
            ext4.kmax = ext2->kmax;
            if (src1[isrc].cent == ZONAL_ARRAY) {
               ext4.kmax--;
            }
         }
         len = LENEXT(ext4);
         src2[isrc2].nzsrc = len;
         src2[isrc2].ndxsrc = ALLOT(int,len);
         CPYEXT(src2[isrc2],ext4);
         count = 0;
         if ((ndims == 2) && (irep == 0)) {
            for (j = ext4.jmin; j <= ext4.jmax; j++) { 
               for (i = ext4.imin; i <= ext4.imax; i++) { 
                  ip = i + j * domain2->jp;
                  src2[isrc2].ndxsrc[count++] = ip;
               }
            }
         } else if (((ndims == 2) && (irep > 0)) || (ndims == 3)) {
            for (k = ext4.kmin; k <= ext4.kmax; k++) { 
               for (j = ext4.jmin; j <= ext4.jmax; j++) { 
                  for (i = ext4.imin; i <= ext4.imax; i++) { 
                     ip = i + j * domain2->jp + k * domain2->kp;
                     src2[isrc2].ndxsrc[count++] = ip;
                  }
               }
            }
         }
         src2[isrc2].type = src1[isrc].type;
         src2[isrc2].cent = src1[isrc].cent;
         src2[isrc2].nidat1 = src1[isrc].nidat1;
         src2[isrc2].nfdat1 = src1[isrc].nfdat1;
         src2[isrc2].ndat2 = src1[isrc].ndat2;
         src2[isrc2].ndat3 = src1[isrc].ndat3;
         strcpy(src2[isrc2].ndxName,src1[isrc].ndxName);
         if (src2[isrc2].nidat1 > 0) {
            src2[isrc2].idat1 = ALLOT(int,src2[isrc2].nidat1);
            for (i=0;i<src2[isrc2].nidat1;i++) {
               src2[isrc2].idat1[i] = src1[isrc].idat1[i];
            }
         }
         if (src2[isrc2].nfdat1 > 0) {
            src2[isrc2].fdat1 = ALLOT(double,src2[isrc2].nfdat1);
            for (i=0;i<src2[isrc2].nfdat1;i++) {
               src2[isrc2].fdat1[i] = src1[isrc].fdat1[i];
            }
         }
         if (src2[isrc2].ndat2 > 0) {
            src2[isrc2].dat2 = ALLOT(double,src2[isrc2].ndat2);
            for (i=0;i<src2[isrc2].ndat2;i++) {
               src2[isrc2].dat2[i] = src1[isrc].dat2[i];
            }
         }
         if (src2[isrc2].ndat3 > 0) {
            src2[isrc2].dat3 = ALLOT(double,src2[isrc2].ndat3);
            for (i=0;i<src2[isrc2].ndat3;i++) {
               src2[isrc2].dat3[i] = src1[isrc].dat3[i];
            }
         }
         domain2->nsrc++;
      }
   }
}
