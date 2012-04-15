#include "irs.h"
#include "irsbndry.h"
#include "BlockMapping.h"
#include "BndMapping.h"
#define MAT_EXPAND(m1,swp) \
   m1[0][abs(swp[0]) - 1] = swp[0]/abs(swp[0]); \
   m1[1][abs(swp[1]) - 1] = swp[1]/abs(swp[1]); \
   m1[2][abs(swp[2]) - 1] = swp[2]/abs(swp[2]); 
#define MAT_IDENT(m1) \
   m1[0][0] = 1; \
   m1[0][1] = 0; \
   m1[0][2] = 0; \
   m1[1][0] = 0; \
   m1[1][1] = 1; \
   m1[1][2] = 0; \
   m1[2][0] = 0; \
   m1[2][1] = 0; \
   m1[2][2] = 1; 
#define MAT_ZERO(m1) \
   m1[0][0] = 0; \
   m1[0][1] = 0; \
   m1[0][2] = 0; \
   m1[1][0] = 0; \
   m1[1][1] = 0; \
   m1[1][2] = 0; \
   m1[2][0] = 0; \
   m1[2][1] = 0; \
   m1[2][2] = 0; 
#define MAT_COPY(m1,m2) \
   m1[0][0] = m2[0][0]; \
   m1[0][1] = m2[0][1]; \
   m1[0][2] = m2[0][2]; \
   m1[1][0] = m2[1][0]; \
   m1[1][1] = m2[1][1]; \
   m1[1][2] = m2[1][2]; \
   m1[2][0] = m2[2][0]; \
   m1[2][1] = m2[2][1]; \
   m1[2][2] = m2[2][2];
#define MAT_X_MAT(m1,m2,m3) \
   m1[0][0] = m2[0][0]*m3[0][0] + m2[0][1]*m3[1][0] + m2[0][2]*m3[2][0]; \
   m1[0][1] = m2[0][0]*m3[0][1] + m2[0][1]*m3[1][1] + m2[0][2]*m3[2][1]; \
   m1[0][2] = m2[0][0]*m3[0][2] + m2[0][1]*m3[1][2] + m2[0][2]*m3[2][2]; \
   m1[1][0] = m2[1][0]*m3[0][0] + m2[1][1]*m3[1][0] + m2[1][2]*m3[2][0]; \
   m1[1][1] = m2[1][0]*m3[0][1] + m2[1][1]*m3[1][1] + m2[1][2]*m3[2][1]; \
   m1[1][2] = m2[1][0]*m3[0][2] + m2[1][1]*m3[1][2] + m2[1][2]*m3[2][2]; \
   m1[2][0] = m2[2][0]*m3[0][0] + m2[2][1]*m3[1][0] + m2[2][2]*m3[2][0]; \
   m1[2][1] = m2[2][0]*m3[0][1] + m2[2][1]*m3[1][1] + m2[2][2]*m3[2][1]; \
   m1[2][2] = m2[2][0]*m3[0][2] + m2[2][1]*m3[1][2] + m2[2][2]*m3[2][2]; 
static int orient_find_neighbor
           (int *utag, int ublk1 ,int ublk2, int mat[3][3]);
static int orient_getmatrix
           (BndMapping_t *ubnd1, int ublk1, BndMapping_t *ubnd2, int ublk2, int mat[3][3]) ;
void orient_ublks(void) 
{
   char *me = "orient_ublks";
   char msg[MAXLINE];
   int i;
   int ibnd;
   int ublk;
   int ublk2;
   int ublk_match;
   int isgood;
   int *utag;
   int mat[3][3];
   BndMapping_t *ubnd1;
   BndMapping_t *ubnd2;
   isgood = 0;
   for (ublk = 0; ublk < unblk; ublk++) {
      for (ibnd = 0; ibnd < umap[ublk].nbnd; ibnd++) {
         if (umap[ublk].bnd[ibnd].orientation[0] == 4) isgood = 1;
      }
   }
   if (isgood == 0) return;
   if (ndims == 2) {
      for (ublk = 0; ublk < unblk; ublk++) {
         for (ibnd = 0; ibnd < umap[ublk].nbnd; ibnd++) {
            ubnd1 = &umap[ublk].bnd[ibnd];
            ublk2 = ubnd1->iblk;
            if (ublk2 < ublk) continue;
            ubnd2 = &umap[ublk2].bnd[ubnd1->id];
            if (orient_getmatrix(ubnd1,ublk,ubnd2,ublk2,mat) == 1) {
               for (i = 0; i < 3; i++) if (mat[0][i] != 0) break;
               ubnd1->orientation[0] = mat[0][i]*(i+1);
               ubnd2->orientation[i] = mat[0][i];
               for (i = 0; i < 3; i++) if (mat[1][i] != 0) break;
               ubnd1->orientation[1] = mat[1][i]*(i+1);
               ubnd2->orientation[i] = mat[1][i]*2;
               for (i = 0; i < 3; i++) if (mat[2][i] != 0) break;
               ubnd1->orientation[2] = mat[2][i]*(i+1);
               ubnd2->orientation[i] = mat[2][i]*3;
               PRINT(stdout,"-------------------------------------------\n");
               PRINT(stdout,"Block %i and Block %i have a shared face.\n",ublk,ublk2);
               PRINT(stdout,"Transformation 1->2: %i  %i  %i\n",
                     ubnd1->orientation[0],
                     ubnd1->orientation[1],
                     ubnd1->orientation[2]);
               PRINT(stdout,"Transformation 2->1: %i  %i  %i\n",
                     ubnd2->orientation[0],
                     ubnd2->orientation[1],
                     ubnd2->orientation[2]);
               PRINT(stdout,"-------------------------------------------\n");
            }
         }
      }
   }
   utag = MALLOT(int,unblk);
   for (ublk = 0; ublk < unblk; ublk++) {
      for (ibnd = 0; ibnd < umap[ublk].nbnd; ibnd++) {
         ubnd1 = &umap[ublk].bnd[ibnd];
         ublk2 = ubnd1->iblk;
         if ((ublk2 > ublk) && (ubnd1->orientation[0] == 0)) {
            ubnd2 = &umap[ublk2].bnd[ubnd1->id];
            for (i = 0; i < unblk; i++) {
               utag[i] = -1;
            }
            for (i = 0; i < umap[ublk2].nbnd; i++) {
               utag[umap[ublk2].bnd[i].iblk] = 0;
            }
            utag[ublk] = 1;
            utag[ublk2] = 0;
            MAT_IDENT(mat);
            ublk_match = ublk;
            while ((ublk_match >= 0) && (ublk_match != ublk2)) {
               ublk_match = orient_find_neighbor(utag,ublk_match,ublk2,mat);
            }
            if (ublk_match >= 0) {
               for (i = 0; i < 3; i++) if (mat[0][i] != 0) break;
               ubnd1->orientation[0] = mat[0][i]*(i+1);
               ubnd2->orientation[i] = mat[0][i];
               for (i = 0; i < 3; i++) if (mat[1][i] != 0) break;
               ubnd1->orientation[1] = mat[1][i]*(i+1);
               ubnd2->orientation[i] = mat[1][i]*2;
               for (i = 0; i < 3; i++) if (mat[2][i] != 0) break;
               ubnd1->orientation[2] = mat[2][i]*(i+1);
               ubnd2->orientation[i] = mat[2][i]*3;
               if (fpout != NULL) {
                  PRINT(fpout,"-------------------------------------------\n");
                  PRINT(fpout,"Block %i and Block %i have a shared corner.\n",ublk,ublk2);
                  PRINT(fpout,"Transformation 1->2: %i  %i  %i\n",
                        ubnd1->orientation[0],
                        ubnd1->orientation[1],
                        ubnd1->orientation[2]);
                  PRINT(fpout,"Transformation 2->1: %i  %i  %i\n",
                        ubnd2->orientation[0],
                        ubnd2->orientation[1],
                        ubnd2->orientation[2]);
                  PRINT(fpout,"-------------------------------------------\n");
               }
            } else {
               sprintf(msg,"Unable to resolve boundary between block %i and %i\n",ublk,ublk2);
               ctlnotice(me,msg);
            }
         }
      }
   }
   FREEMEM(utag);
}
static int orient_find_neighbor(int *utag, int ublk1 ,int ublk2, int mat[3][3]) 
{
   int ublk_match;
   int ibnd;
   int ibnd_match;
   int mat_temp1[3][3];
   int mat_temp2[3][3];
   BndMapping_t *ubnd;
   ubnd = umap[ublk1].bnd;
   ublk_match = -1;
   ibnd_match = -1;
   for (ibnd = 0; ibnd < umap[ublk1].nbnd; ibnd++) {
      if ((ubnd[ibnd].orientation[0] != 0) && (utag[ubnd[ibnd].iblk] == 0)) {
         ublk_match = ubnd[ibnd].iblk;
         ibnd_match = ibnd;
         if (ublk_match == ublk2) break;
      }
   }
   if (ublk_match >= 0) {
      utag[ublk_match] = 1;
      MAT_ZERO(mat_temp1);
      MAT_ZERO(mat_temp2);
      MAT_EXPAND(mat_temp1,ubnd[ibnd_match].orientation);
      MAT_X_MAT(mat_temp2,mat_temp1,mat);
      MAT_COPY(mat,mat_temp2);
   } 
   return(ublk_match);
} 
static int orient_getmatrix(BndMapping_t *ubnd1, int ublk1, BndMapping_t *ubnd2, int ublk2, 
                     int mat[3][3]) {
   int flag = 0;
   int ideg1, ideg2;
   int jdeg1, jdeg2;
   int kdeg1, kdeg2;
   int maxflg1, maxflg2;
   int offt;
   int offn;
   int side;
   side = 0;
   ideg1 = 1;
   jdeg1 = 1;
   kdeg1 = 1;
   ideg2 = 1;
   jdeg2 = 1;
   kdeg2 = 1;
   if (ubnd1->imax != ubnd1->imin) ideg1 = 0;
   if (ubnd1->jmax != ubnd1->jmin) jdeg1 = 0;
   if (ubnd1->kmax != ubnd1->kmin) kdeg1 = 0;
   if (ubnd2->imax != ubnd2->imin) ideg2 = 0;
   if (ubnd2->jmax != ubnd2->jmin) jdeg2 = 0;
   if (ubnd2->kmax != ubnd2->kmin) kdeg2 = 0;
   side = 3 - (ideg1 + jdeg1 + kdeg1);
   if ((ndims == 2) && (side == 1)) {
      flag = 1;
      MAT_ZERO(mat);
      offt = 1;
      if ((ubnd1->ndx[1] - ubnd1->ndx[0]) < 0) offt *= -1 ;
      if ((ubnd2->ndx[1] - ubnd2->ndx[0]) < 0) offt *= -1 ;
      maxflg1 = 0;
      maxflg2 = 0;
      if ((ideg1) && (ubnd1->imax == umap[ublk1].imax)) maxflg1 = 1;
      if ((jdeg1) && (ubnd1->jmax == umap[ublk1].jmax)) maxflg1 = 1;
      if ((ideg2) && (ubnd2->imax == umap[ublk2].imax)) maxflg2 = 1;
      if ((jdeg2) && (ubnd2->jmax == umap[ublk2].jmax)) maxflg2 = 1;
      offn = 1;
      if (maxflg1 == maxflg2) offn = -1;
      mat[0][0] = offn * ideg1 * ideg2 + offt * ( 1 - ideg1 ) * ( 1 - ideg2 );
      mat[0][1] = offn * jdeg1 * ideg2 + offt * ( 1 - jdeg1 ) * ( 1 - ideg2 );
      mat[1][0] = offn * ideg1 * jdeg2 + offt * ( 1 - ideg1 ) * ( 1 - jdeg2 );
      mat[1][1] = offn * jdeg1 * jdeg2 + offt * ( 1 - jdeg1 ) * ( 1 - jdeg2 );
      mat[2][2] = 1;
   } else if ((ndims == 3) && (side == 2)) {
      flag = 1;
      MAT_ZERO(mat);
      MAT_IDENT(mat);
   } 
   return(flag);
}
