#include "irs.h"
#include "irsblk.h"
#include "irsdmp.h"
#include "irsgen.h"
#include "BndMapping.h"
#include "BlockMapping.h"
#include "Hash.h"
#include "Extents.h"
#include "NodeList.h"
typedef struct {
   char name[MAXLINE];
   int type;
   int id;
   int imin;
   int imax;
   int jmin;
   int jmax;
   int kmin;
   int kmax;
   int direct;
   int ublk;
} RDTRUE_PATCH;
typedef struct {
   int patch1;
   int patch2;
   int orientation[3];
} RDTRUE_GLUE;  
#define BLKB_PATCH 0
#define USER_PATCH 1
static void rdtruegrid_mesh_skip( Extents_t ext);
int rdtruegrid( void )
{
   char *me = "rdtruegrid";
   int iblk;
   int num_blocks;
   int error = 0;
   char op[MAXLINE];
   char msg[MAXLINE];
   char meshfile[MAXWORD];
   Extents_t ext;
   if (genmd != 1) {
      sprintf(msg, "Attempting to read TrueGrid mesh before memory has been allocated.\n\t\tAre you in merge phase?\n\t\tDid you forget the -sew on the command line?");
      ctlerror(me,msg);
   }
   geta(meshfile);
   error = newfile(meshfile,1);
   if (error != 0) return(error);
   error = rdtruegrid_decomp(umap,unblk,1,&num_blocks);
   for (iblk = unblk; iblk < (num_blocks + unblk); iblk++) {
      domains[iblk].imin = NPNL;
      domains[iblk].jmin = NPNL;
      domains[iblk].kmin = NPNL;
      domains[iblk].imax = umap[iblk].imax;
      domains[iblk].jmax = umap[iblk].jmax;
      domains[iblk].kmax = umap[iblk].kmax;
      if (ndims == 2) domains[iblk].type = QUAD2D;
      if (ndims == 3) domains[iblk].type = HEX3D;
      domains[iblk].sclnamix = sclnamix;
      initblk(iblk,&domains[iblk]);
      domains[iblk].gblk = gnblk;
      domain_hash_tbl_rgst(&(domains[iblk]));
      nblk++;
      CPYEXT(ext,domains[iblk]);
      rdtruegrid_mesh(domains[iblk].x, domains[iblk].y, domains[iblk].z, domains[iblk].node,
                      ext, domains[iblk].jp, domains[iblk].kp);
      setgmap(iblk,ext);
   }
   unblk += num_blocks;
   geta(op);
   endfile();
   return(error);
}
int rdtruegrid_decomp(BlockMapping_t *map, int startblk, int ndlistflg, 
                      int *num_blocks)
{
   int i,j,k ;
   int imin,jmin,kmin;
   int imax,jmax,kmax;
   int istep,jstep,kstep;
   int ip,jp,kp;
   int ig,id;
   int iblk;
   int len;
   int ublk;
   int ublk1,ublk2;
   int ibnd1,ibnd2;
   int junki;
   int cflag;
   int num_patches;
   int num_glue;
   int patch1,patch2;
   int count;
   int orient_ext[7];
   int orient_str[7];
   int error = 0;
   int *ndx;
   RDTRUE_PATCH *patch;
   RDTRUE_GLUE *glue;
   NodeList_t *NodeList;
   NodeWindow_t *my_ndx;
   char op[MAXLINE];
   char msg[MAXLINE];
   char hashname[MAXLINE];
   geta(op);
   *num_blocks = geti(&cflag);
   num_patches = geti(&cflag);
   num_glue  = geti(&cflag);
   if (num_glue > 0) ifcom = 1;
   junki  = geti(&cflag);
   junki  = geti(&cflag);
   geta(op);
   ublk = startblk;
   if (startblk < 0) ublk = 0;
   for (iblk = ublk; iblk < (*num_blocks + ublk); iblk++) {
      geta(op);
      if (startblk >= 0) {
         map[iblk].imin = NPNL;
         map[iblk].jmin = NPNL;
         map[iblk].kmin = NPNL;
         map[iblk].imax = geti(&cflag) + NPNL;
         map[iblk].jmax = geti(&cflag) + NPNL;
         map[iblk].kmax = geti(&cflag) + NPNL;
         if ((map[iblk].kmax - map[iblk].kmin) > 1) ndims = 3;
         if (ndims == 2) {
            map[iblk].kmin = 0;
            map[iblk].kmax = 0;
            map[iblk].jp = map[iblk].imax - map[iblk].imin + 1 + NPNL + NPNR;
            map[iblk].kp = 0;
         } else {
            map[iblk].jp = map[iblk].imax - map[iblk].imin + 1 + NPNL + NPNR;
            map[iblk].kp = map[iblk].jp * (map[iblk].jmax - map[iblk].jmin + 
                           1 + NPNL + NPNR);
         } 
         if (map[iblk].nbnd < 0) {
            map[iblk].bnd = ALLOT(BndMapping_t,nbndx);
            map[iblk].nbnd = 0;
         }
      } else {
         junki = geti(&cflag);
         junki = geti(&cflag);
         junki = geti(&cflag);
      } 
   }
   geta(op);
   patch = MALLOT(RDTRUE_PATCH,num_patches);
   for (i = 0; i < num_patches; i++) {
      geta(op);
      patch[i].type = BLKB_PATCH;
      if (!strcmp(op,"USER2D")) patch[i].type = USER_PATCH;
      if (!strcmp(op,"USER3D")) patch[i].type = USER_PATCH;
      if (!strcmp(op,"BLKBDY")) patch[i].type = BLKB_PATCH;
      geta(patch[i].name);
      junki = geti(&cflag);
      patch[i].imin = geti(&cflag) ;
      patch[i].imax = geti(&cflag) ;
      patch[i].jmin = geti(&cflag) ;
      patch[i].jmax = geti(&cflag) ;
      patch[i].kmin = geti(&cflag) ;
      patch[i].kmax = geti(&cflag) ;
      patch[i].direct = geti(&cflag);
      patch[i].ublk = startblk + geti(&cflag) - 1;
      patch[i].id = geti(&cflag);
   }
   geta(op);
   glue = MALLOT(RDTRUE_GLUE,num_glue);
   for (i = 0; i < num_glue; i++) {
      glue[i].patch1 = geti(&cflag) - 1;
      glue[i].patch2 = geti(&cflag) - 1;
      glue[i].orientation[0] = geti(&cflag);
      glue[i].orientation[1] = geti(&cflag);
      glue[i].orientation[2] = geti(&cflag);
      junki = geti(&cflag);
   }
   if (startblk < 0) {
      FREEMEM(patch);
      FREEMEM(glue);
      return(error);
   }
   for (i = 0; i < num_patches; i++ ) {
      ublk = patch[i].ublk;
      len = patch[i].imax - patch[i].imin + 1;
      if (patch[i].direct == 1) {
         patch[i].imax = patch[i].imax + map[ublk].imin;
         patch[i].imin = patch[i].imax;
      } else if (patch[i].direct == 4) {
         patch[i].imin = patch[i].imin - 1 + map[ublk].imin;
         patch[i].imax = patch[i].imin ;
      } else {
         patch[i].imin = patch[i].imin - 1 + map[ublk].imin;
         patch[i].imax = patch[i].imin + len;
      } 
      len = patch[i].jmax - patch[i].jmin + 1;
      if (patch[i].direct == 2) {
         patch[i].jmax = patch[i].jmax + map[ublk].jmin;
         patch[i].jmin = patch[i].jmax;
      } else if (patch[i].direct == 5) {
         patch[i].jmin = patch[i].jmin - 1 + map[ublk].jmin;
         patch[i].jmax = patch[i].jmin ;
      } else {
         patch[i].jmin = patch[i].jmin - 1 + map[ublk].jmin;
         patch[i].jmax = patch[i].jmin + len;
      } 
      len = patch[i].kmax - patch[i].kmin + 1;
      if (patch[i].direct == 3) {
         patch[i].kmax = patch[i].kmax + map[ublk].kmin;
         patch[i].kmin = patch[i].kmax;
      } else if (patch[i].direct == 6) {
         patch[i].kmin = patch[i].kmin - 1 + map[ublk].kmin;
         patch[i].kmax = patch[i].kmin ;
      } else {
         patch[i].kmin = patch[i].kmin - 1 + map[ublk].kmin;
         patch[i].kmax = patch[i].kmin + len;
      } 
      if (ndims == 2) {
         patch[i].kmin = 0;
         patch[i].kmax = 0;
      }
   }
   for (ig = 0; ig < num_glue; ig++) {
      patch1 = glue[ig].patch1;
      patch2 = glue[ig].patch2;
      ublk1 = patch[patch1].ublk;
      ublk2 = patch[patch2].ublk;
      ibnd1 = map[ublk1].nbnd;
      map[ublk1].bnd[ibnd1].imin = patch[patch1].imin;
      map[ublk1].bnd[ibnd1].jmin = patch[patch1].jmin;
      map[ublk1].bnd[ibnd1].kmin = patch[patch1].kmin;
      map[ublk1].bnd[ibnd1].imax = patch[patch1].imax;
      map[ublk1].bnd[ibnd1].jmax = patch[patch1].jmax;
      map[ublk1].bnd[ibnd1].kmax = patch[patch1].kmax;
      map[ublk1].nbnd++;
      if (genmd != -1) {
         len = (patch[patch1].kmax - patch[patch1].kmin + 1) *
               (patch[patch1].jmax - patch[patch1].jmin + 1) *
               (patch[patch1].imax - patch[patch1].imin + 1);
         map[ublk1].bnd[ibnd1].len = len;
         ndx = map[ublk1].bnd[ibnd1].ndx = MALLOT(int,len);
         jp = map[ublk1].jp;
         kp = map[ublk1].kp;
         count = 0;
         if (ndims == 3) {
            for (k = patch[patch1].kmin; k <= patch[patch1].kmax; k++) {
               for (j = patch[patch1].jmin; j <= patch[patch1].jmax; j++) {
                  for (i = patch[patch1].imin; i <= patch[patch1].imax; i++) {
                     id = i + j*jp + k*kp;
                     ndx[count++] = id;
                  }
               }
            }
         } else {
            for (j = patch[patch1].jmin; j <= patch[patch1].jmax; j++) {
               for (i = patch[patch1].imin; i <= patch[patch1].imax; i++) {
                  id = i + j*jp ;
                  ndx[count++] = id;
               }
            }
         } 
      } 
      for (id = 0; id < 3; id++) {
         if ((glue[ig].orientation[id] == 1) || 
             (glue[ig].orientation[id] == 4)) {
            break;
         }
      }
      if (glue[ig].orientation[id] <= 3) {
         map[ublk1].bnd[ibnd1].orientation[0] = (id + 1);
      } else {
         map[ublk1].bnd[ibnd1].orientation[0] = -(id + 1);
      }
      for (id = 0; id < 3; id++) {
         if ((glue[ig].orientation[id] == 2) || 
             (glue[ig].orientation[id] == 5)) {
            break;
         }
      }
      if (glue[ig].orientation[id] <= 3) {
         map[ublk1].bnd[ibnd1].orientation[1] = (id + 1);
      } else {
         map[ublk1].bnd[ibnd1].orientation[1] = -(id + 1);
      }
      for (id = 0; id < 3; id++) {
         if ((glue[ig].orientation[id] == 3) || 
             (glue[ig].orientation[id] == 6)) {
            break;
         }
      }
      if (glue[ig].orientation[id] <= 3) {
         map[ublk1].bnd[ibnd1].orientation[2] = (id + 1);
      } else {
         map[ublk1].bnd[ibnd1].orientation[2] = -(id + 1);
      }
      ibnd2 = map[ublk2].nbnd;
      map[ublk2].bnd[ibnd2].imin = patch[patch2].imin;
      map[ublk2].bnd[ibnd2].jmin = patch[patch2].jmin;
      map[ublk2].bnd[ibnd2].kmin = patch[patch2].kmin;
      map[ublk2].bnd[ibnd2].imax = patch[patch2].imax;
      map[ublk2].bnd[ibnd2].jmax = patch[patch2].jmax;
      map[ublk2].bnd[ibnd2].kmax = patch[patch2].kmax;
      map[ublk2].nbnd++;
      if (genmd != -1) {
         jp = map[ublk2].jp;
         kp = map[ublk2].kp;
         orient_ext[1] = patch[patch2].imax;
         orient_ext[2] = patch[patch2].jmax;
         orient_ext[3] = patch[patch2].kmax;
         orient_ext[4] = patch[patch2].imin;
         orient_ext[5] = patch[patch2].jmin;
         orient_ext[6] = patch[patch2].kmin;
         orient_str[1] = 1;
         orient_str[2] = jp;
         orient_str[3] = kp;
         orient_str[4] = 1;
         orient_str[5] = jp;
         orient_str[6] = kp;
         if (glue[ig].orientation[0] >= 4) {
            imax = orient_ext[glue[ig].orientation[0]];
            imin = orient_ext[glue[ig].orientation[0] - 3];
            istep = -1;
         } else {
            imin = orient_ext[glue[ig].orientation[0] + 3];
            imax = orient_ext[glue[ig].orientation[0]];
            istep = 1;
         } 
         if (glue[ig].orientation[1] >= 4) {
            jmax = orient_ext[glue[ig].orientation[1]];
            jmin = orient_ext[glue[ig].orientation[1] - 3];
            jstep = -1;
         } else {
            jmin = orient_ext[glue[ig].orientation[1] + 3];
            jmax = orient_ext[glue[ig].orientation[1]];
            jstep = 1;
         } 
         if (glue[ig].orientation[2] >= 4) {
            kmax = orient_ext[glue[ig].orientation[2]];
            kmin = orient_ext[glue[ig].orientation[2] - 3];
            kstep = -1;
         } else {
            kmin = orient_ext[glue[ig].orientation[2] + 3];
            kmax = orient_ext[glue[ig].orientation[2]];
            kstep = 1;
         } 
         ip = orient_str[glue[ig].orientation[0]];
         jp = orient_str[glue[ig].orientation[1]];
         kp = orient_str[glue[ig].orientation[2]];
         len = (patch[patch2].kmax - patch[patch2].kmin + 1) *
               (patch[patch2].jmax - patch[patch2].jmin + 1) *
               (patch[patch2].imax - patch[patch2].imin + 1);
         map[ublk2].bnd[ibnd2].len = len;
         ndx = map[ublk2].bnd[ibnd2].ndx = MALLOT(int,len);
         count = 0;
         if (ndims == 3) {
            for( k = 0; k <= abs(kmax-kmin); k++) {
               for( j = 0; j <= abs(jmax-jmin); j++) {
                  for( i = 0; i <= abs(imax-imin); i++) {
                     id = (i*istep + imin)*ip + 
                          (j*jstep + jmin)*jp + 
                          (k*kstep + kmin)*kp;
                     ndx[count++] = id;
                  }
               }
            }
         } else {
            for( j = 0; j <= abs(jmax-jmin); j++) {
               for( i = 0; i <= abs(imax-imin); i++) {
                  id = (i*istep + imin)*ip + 
                       (j*jstep + jmin)*jp; 
                  ndx[count++] = id;
               }
            }
         }
      }
      for (id = 0; id < 3; id++) {
         if (glue[ig].orientation[id] <= 3) {
            map[ublk2].bnd[ibnd2].orientation[id] = glue[ig].orientation[id];
         } else {
            map[ublk2].bnd[ibnd2].orientation[id] = 
                                          - (glue[ig].orientation[id] - 3);
         }
      }
      map[ublk1].bnd[ibnd1].id = ibnd2;
      map[ublk2].bnd[ibnd2].id = ibnd1;
      map[ublk1].bnd[ibnd1].iblk = ublk2;
      map[ublk2].bnd[ibnd2].iblk = ublk1;
   }
   if (ndlistflg) {
      for (i = 0; i < num_patches; i++) { 
         if (patch[i].type == BLKB_PATCH) continue;
         NodeList = NodeList_find(patch[i].name);
         if (NodeList == NULL) {
            NodeList = MALLOT(NodeList_t,1);
            strcpy(NodeList->name,patch[i].name);
            NodeList_add(NodeList);
            NodeList->list = NULL;
         } 
         my_ndx = MALLOT(NodeWindow_t,1);
         CPYEXT((*my_ndx),patch[i]);
         my_ndx->len  = 0;
         my_ndx->rank = ndims;
         my_ndx->ublk = patch[i].ublk;
         my_ndx->in[0][0] = patch[i].imin;
         my_ndx->in[1][0] = patch[i].jmin;
         my_ndx->in[2][0] = patch[i].kmin;
         my_ndx->in[0][1] = patch[i].imax;
         my_ndx->in[1][1] = patch[i].jmax;
         my_ndx->in[2][1] = patch[i].kmax;
         my_ndx->in[0][2] = 1;
         my_ndx->in[1][2] = 1;
         my_ndx->in[2][2] = 1;
         mkpalab(my_ndx->label,NodeList->name,my_ndx->ublk,my_ndx->in,
                 my_ndx->rank, 0,"");
         NodeWindow_add(my_ndx,&NodeList->list);
      }
   }
   FREEMEM(patch);
   FREEMEM(glue);
   return(error);
}
void rdtruegrid_mesh(double *x, double *y, double *z, int *node, 
                      Extents_t ext, int jp, int kp) 
{
   char op[MAXLINE];
   int i,j,k;
   int id;
   int cflag;
   double junkf;
   geta(op);
   if (ndims == 2) {
      for (k = 0; k < 2; k++) {
         for (j = ext.jmin; j <= ext.jmax; j++) {
            for (i = ext.imin; i <= ext.imax; i++) {
               id = i + jp*j;
               x[id] = getf(&cflag);
               y[id] = getf(&cflag);
               node[id] = 1;
               junkf = getf(&cflag);
            }
         }
      }
   } else {
      for (k = ext.kmin; k <= ext.kmax; k++) {
         for (j = ext.jmin; j <= ext.jmax; j++) {
            for (i = ext.imin; i <= ext.imax; i++) {
               id = i + jp*j + kp*k;
               x[id] = getf(&cflag);
               y[id] = getf(&cflag);
               z[id] = getf(&cflag);
               node[id] = 1;
            }
         }
      }
   }
}
static void rdtruegrid_mesh_skip( Extents_t ext)
{
   char op[MAXLINE];
   int i,j,k;
   int id;
   int cflag;
   double junkf;
   geta(op);
   if (ndims == 2) {
      for (k = 0; k < 2; k++) {
         for (j = ext.jmin; j <= ext.jmax; j++) {
            for (i = ext.imin; i <= ext.imax; i++) {
               junkf = getf(&cflag);
               junkf = getf(&cflag);
               junkf = getf(&cflag);
            }
         }
      }
   } else {
      for (k = ext.kmin; k <= ext.kmax; k++) {
         for (j = ext.jmin; j <= ext.jmax; j++) {
            for (i = ext.imin; i <= ext.imax; i++) {
               junkf = getf(&cflag);
               junkf = getf(&cflag);
               junkf = getf(&cflag);
            }
         }
      }
   }
}
#undef BLKB_PATCH 
#undef USER_PATCH 
