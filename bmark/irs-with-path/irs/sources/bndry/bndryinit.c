#include "irs.h"     
#include "irsblk.h"     
#include "irsbndry.h"
#include "irscom.h"     
#include "irssys.h"     
#include "Boundary.h"
#include "BlockMapping.h"
#include "BndMapping.h"
#include "Extents.h"
#include "FunctionTimer.h"
#include "ProblemArray.h"     
struct BNDRY_PATCH_ {
   int gblk;
   int ublk1;
   int ublk2;
   int ibnd1;
   int ibnd2;
   Extents_t ext;
   struct BNDRY_PATCH_ *next;
};
typedef struct BNDRY_PATCH_ BNDRY_PATCH;
typedef struct {
   int *id;
   int  nid;
} BoundaryInitConnectivity_t;
static void bndry_patch_add(BNDRY_PATCH *elmin, BNDRY_PATCH **list) ;
static int  bndry_ckoverlap(Extents_t extin, BlockMapping_t *map, int maplen, int iblk) ;
static void bndry_map_orient(int *orient, int *orient1, int *orient2) ;
static void bndry_tbnd(Domain_t *domain) ;
static void bndry_extend(Extents_t *ext, Extents_t gext);
static void bndry_printpair(char *header, int blk1, Extents_t ext1,
                                   int blk2, Extents_t ext2) ;
static void bndry_sortndx(int *ndx1, int* ndx2, int len, int jp, int kp, int *orient);
static void bndry_zonal(Domain_t *domain) ;
static void bndry_setbnd(void) ;
static void bndry_insert(int *ndxin, Boundary_t *bnd, int lenin, int com_type) ;
void bndry_init(void) {
   int ncorn;
   int error;
   int iblk;
   ncorn     = bndry_findcrn(umap, unblk);
   while (ncorn != 0) {
      ncorn = bndry_findcrn(umap, unblk);
   }
   bndry_setgbnd();
   if ((!ifparallel) && (gnblk != nblk)) blkdiv();
   bndry_setbnd();
   error = 0;
   for (iblk = 0; iblk < nblk; iblk++) {
   }
   if (ifparallel) {
      comreduce(&error, 1, COM_MAX, COM_ALL, COM_INT);
   }
}
int bndry_findcrn(BlockMapping_t *map, int nmap) {
   char *me = "bndry_findcrn";
   int ibnd;
   int jbnd;
   int ibnd1;
   int ibnd2;
   int iblk;
   int iblk1;
   int iblk2;
   int ovlap;
   int count; 
   int len; 
   int *maplen;
   Extents_t ext;
   Extents_t trext1;
   Extents_t trext2;
   Extents_t ext1;
   Extents_t ext2;
   Extents_t ext3;
   Extents_t ext4;
   BndMapping_t *bnd1;
   BndMapping_t *bnd2;
   count = 0;
   maplen = MALLOT(int,nmap);
   for (iblk = 0; iblk < nmap; iblk++) {
      maplen[iblk] = map[iblk].nbnd;
   }
   for (iblk = 0; iblk < nmap; iblk++) {
      for (ibnd = 0; ibnd < maplen[iblk]; ibnd++) {
         CPYEXT(ext,map[iblk].bnd[ibnd]);
         iblk1 = map[iblk].bnd[ibnd].iblk;
         ibnd1 = map[iblk].bnd[ibnd].id;
         CPYEXT(ext1,map[iblk1].bnd[ibnd1]);
         for (jbnd = 0; jbnd < maplen[iblk1]; jbnd++) {
            iblk2 = map[iblk1].bnd[jbnd].iblk;
            ibnd2 = map[iblk1].bnd[jbnd].id;
            if (jbnd == ibnd1) continue;
            if (iblk2 <= iblk) continue;
            CPYEXT(ext2,map[iblk1].bnd[jbnd]);
            len = extents_overlap(&ext1, &ext2, &ext3);
            if (len > 0) {
               extents_transform(ext1, ext, map[iblk1].bnd[ibnd1].orientation,
                                ext3, &trext1);
               ovlap = bndry_ckoverlap(trext1,&map[iblk],map[iblk].nbnd,iblk2);
               if (ovlap == 0) {
                  count++;
                  CPYEXT(ext4,map[iblk2].bnd[ibnd2]);
                  extents_transform(ext2, ext4, 
                         map[iblk1].bnd[jbnd].orientation, ext3, &trext2);
                  bnd1 = &map[iblk].bnd[map[iblk].nbnd];
                  bnd2 = &map[iblk2].bnd[map[iblk2].nbnd];
                  bndry_map_orient(bnd1->orientation,
                                   map[iblk].bnd[ibnd].orientation,
                                   map[iblk1].bnd[jbnd].orientation);
                  bndry_map_orient(bnd2->orientation,
                                   map[iblk2].bnd[ibnd2].orientation,
                                   map[iblk1].bnd[ibnd1].orientation);
                  bnd2->iblk = iblk;
                  bnd1->iblk = iblk2;
                  bnd2->id = map[iblk].nbnd;
                  bnd1->id = map[iblk2].nbnd;
                  CPYEXT((*bnd1),trext1);
                  CPYEXT((*bnd2),trext2);
                  map[iblk].nbnd++;
                  map[iblk2].nbnd++;
		  if ((map[iblk2].nbnd > nbndx) || (map[iblk].nbnd > nbndx)) {
		     ctlerror(me,"Too many block boundaries.  Increase nbndx.");
		  }
                  bndry_printpair("Found boundary ",iblk,trext1, iblk2, trext2);
               }
            }
         }
      }
   }
   FREEMEM(maplen);
   return(count);
}
static int bndry_ckoverlap(Extents_t extin, BlockMapping_t *map, int maplen, int iblk) {
  int ibnd;
  int len;
  Extents_t ext;
  Extents_t extout;
  Extents_t extinp;
  extinp.imin = MIN(extin.imin,extin.imax);
  extinp.jmin = MIN(extin.jmin,extin.jmax);
  extinp.kmin = MIN(extin.kmin,extin.kmax);
  extinp.imax = MAX(extin.imin,extin.imax);
  extinp.jmax = MAX(extin.jmin,extin.jmax);
  extinp.kmax = MAX(extin.kmin,extin.kmax);
  len = 0;
  for (ibnd = 0; ibnd < maplen; ibnd++) {
     if (iblk >= 0) { 
        if (map->bnd[ibnd].iblk == iblk) {
           CPYEXT(ext,map->bnd[ibnd]);
           len += extents_overlap(&ext,&extinp,&extout);
        }
     } else {
        CPYEXT(ext,map->bnd[ibnd]);
        len += extents_overlap(&ext,&extinp,&extout);
     }
  }
  return(len);
}
static void bndry_map_orient(int *orient, int *orient1, int *orient2) {
   int sign1;
   int sign2;
   int i;
   int j;
   int k;
   for (k = 0; k < 3; k++) {
      i = abs(orient2[k]) - 1;
      sign2 = 1;
      if (orient2[k] < 0) sign2 = -1;
      j = abs(orient1[i]) - 1;
      sign1 = 1;
      if (orient1[i] < 0) sign1 = -1;
      orient[k] = sign1 * sign2 * (j + 1);
   }
}
void bndry_setgbnd(void) {
   char *me = "bndry_setgbnd";
   char msg[2*MAXLINE];
   int ublk;
   int ublk1, ublk2;
   int gblk;
   int gblka, gblkb;
   int ibnd;
   int ibnd1, ibnd2;
   int ibnda, ibndb;
   int len;
   int lena, lenb;
   int *orienta;
   int *orientb;
   Extents_t uext;
   Extents_t gext;
   Extents_t ext;
   Extents_t ext1;
   Extents_t ext2;
   Extents_t trext;
   Extents_t exta, extb;
   BNDRY_PATCH *bndlist;
   BNDRY_PATCH *bndlista;
   BNDRY_PATCH *bndlistb;
   BNDRY_PATCH *bndtmp;
   bndlist = NULL;
   bndlista = NULL;
   bndlistb = NULL;
   for (ublk = 0; ublk < unblk; ublk++) {
      for (gblk = 0; gblk < gnblk; gblk++) {
         if (gmap[gblk].ublk != ublk) continue;
         CPYEXT(gext,gmap[gblk]);
         for (ibnd = 0; ibnd < umap[ublk].nbnd; ibnd++) {
            CPYEXT(uext,umap[ublk].bnd[ibnd]);
            len = extents_overlap(&uext,&gext,&ext);
            if (len > 0) {
               bndtmp = MALLOT(BNDRY_PATCH,1);
               bndtmp->gblk   = gblk;
               bndtmp->ublk1  = ublk;
               bndtmp->ublk2  = umap[ublk].bnd[ibnd].iblk;
               bndtmp->ibnd1  = ibnd;
               bndtmp->ibnd2  = umap[ublk].bnd[ibnd].id;
               CPYEXT(bndtmp->ext,ext);
               bndry_patch_add(bndtmp,&bndlist);
            }
         }
      }
   }
   bndlista = bndlist;
   while (bndlista != NULL) {
      gblka = bndlista->gblk;
      ublk1 = bndlista->ublk1;
      ublk2 = bndlista->ublk2;
      ibnd1 = bndlista->ibnd1;
      ibnd2 = bndlista->ibnd2;
      orienta = umap[ublk1].bnd[ibnd1].orientation;
      orientb = umap[ublk2].bnd[ibnd2].orientation;
      bndlistb = bndlista->next;
      while (bndlistb != NULL) {
         if ((bndlistb->ublk2 == ublk1) &&
             (bndlistb->ublk1 == ublk2) &&
             (bndlistb->ibnd1 == ibnd2) &&
             (bndlistb->ibnd2 == ibnd1)) {
             gblkb = bndlistb->gblk;
             CPYEXT(ext1,umap[ublk1].bnd[ibnd1]);
             CPYEXT(ext2,umap[ublk2].bnd[ibnd2]);
             extents_transform(ext1, ext2, umap[ublk1].bnd[ibnd1].orientation,
                               bndlista->ext, &trext);
             lenb = extents_overlap(&bndlistb->ext, &trext, &extb);
             extents_transform(ext2, ext1, umap[ublk2].bnd[ibnd2].orientation,
                               bndlistb->ext, &trext);
             lena = extents_overlap(&bndlista->ext, &trext, &exta);
             if ((lena > 0) && (lena == lenb)) {
                if (bndry_ckoverlap(exta, &gmap[gblka], gmap[gblka].nbnd, 
                                    gblkb)) {
                   goto nextb;
                }
                if (gblka != gblkb) {
                   ibnda = gmap[gblka].nbnd;
                   ibndb = gmap[gblkb].nbnd;
                } else {
                   ibnda = gmap[gblka].nbnd;
                   ibndb = gmap[gblkb].nbnd+1;
                } 
                gmap[gblka].nbnd++;
                gmap[gblkb].nbnd++;
		if ((gmap[gblka].nbnd > nbndx) || 
		    (gmap[gblkb].nbnd > nbndx)) {
		   ctlerror(me,"Too many block boundaries.  Increase nbndx.");
		}
                gmap[gblka].bnd[ibnda].iblk = gblkb;
                gmap[gblkb].bnd[ibndb].iblk = gblka;
                gmap[gblka].bnd[ibnda].id   = ibndb;
                gmap[gblkb].bnd[ibndb].id   = ibnda;
                gmap[gblka].bnd[ibnda].len  = lena;
                gmap[gblkb].bnd[ibndb].len  = lenb;
                gmap[gblka].bnd[ibnda].orientation[0] = orienta[0];
                gmap[gblka].bnd[ibnda].orientation[1] = orienta[1];
                gmap[gblka].bnd[ibnda].orientation[2] = orienta[2];
                gmap[gblkb].bnd[ibndb].orientation[0] = orientb[0];
                gmap[gblkb].bnd[ibndb].orientation[1] = orientb[1];
                gmap[gblkb].bnd[ibndb].orientation[2] = orientb[2];
                CPYEXT(gmap[gblka].bnd[ibnda],exta);
                CPYEXT(gmap[gblkb].bnd[ibndb],extb);
             }
             if ((lenb > 0) && (lena > 0) && (lena != lenb)) {
                sprintf(msg,"Error matching boundaries between blocks %i and %i",ublk1,ublk2);
                ctlwarning(me,msg);
             }
         }
nextb:   bndlistb = bndlistb->next;
      }
      bndlista = bndlista->next;
   }
   bndlista = bndlist;
   while (bndlista != NULL) {
      bndlistb = bndlista->next;
      FREEMEM(bndlista);
      bndlista = bndlistb;
   }
   for (gblk = 0; gblk < gnblk; gblk++) {
      if (gmap[gblk].nbnd > nbndx) {
         sprintf(msg,"Domain %i has asked for %i bnds which exceeds the limit set \n\t\tby nbndx = %i.  Either increase nbndx or check to make sure \n\t\tthat you don't have an insane decomposition.",gblk,gmap[gblk].nbnd, nbndx);
         ctlerror(me,msg);
      }
      for (ibnd = 0; ibnd < gmap[gblk].nbnd; ibnd++) {
         if (gmap[gblk].bnd[ibnd].orientation[0] == 0) {
            gmap[gblk].bnd[ibnd].orientation[0] = 1;
            gmap[gblk].bnd[ibnd].orientation[1] = 2;
            gmap[gblk].bnd[ibnd].orientation[2] = 3;
         }
      }
   }
}
static void bndry_patch_add(BNDRY_PATCH *elmin, BNDRY_PATCH **list) {
   BNDRY_PATCH *local_list;
   local_list = *list;
   if (local_list != NULL) {
      while (local_list->next != NULL) local_list = local_list->next;
      local_list->next = elmin;
   } else {
      *list = elmin;
   }
   elmin->next = NULL;
}
static void bndry_tbnd(Domain_t *domain) {
   int i;
   int ibnd1,ibnd2;
   int gblk1,gblk2;
   int len1;
   int len2;
   int *ndx1;
   int *ndx2;
   int *rank;
   int pn[3];
   Extents_t bext1;
   Extents_t bext2;
   Extents_t gext1;
   Extents_t gext2;
   Extents_t ext1;
   Extents_t ext2;
   Extents_t ext3;
   Extents_t trext1;
   Extents_t trext2;
   gblk1 = domain->gblk;   
   for (ibnd1 = 0; ibnd1 < domain->nbnd; ibnd1++) {
      gblk2 = gmap[gblk1].bnd[ibnd1].iblk;
      ibnd2 = gmap[gblk1].bnd[ibnd1].id;
      TRSEXT(gext1,gmap[gblk1],gmap[gblk1]);
      TRSEXT(gext2,gmap[gblk2],gmap[gblk2]);
      TRSEXT(bext1,gmap[gblk1].bnd[ibnd1],gmap[gblk1]);
      TRSEXT(bext2,gmap[gblk2].bnd[ibnd2],gmap[gblk2]);
      CPYEXT(ext1,bext1);
      len1 = LENEXT(ext1);
      bndry_extend(&ext1,gext1); 
      extents_transform(bext1, bext2, gmap[gblk1].bnd[ibnd1].orientation,
                                ext1, &trext2);
      len2 = extents_overlap(&trext2,&gext2,&ext3);
      if (ndims == 2) {
         ext3.kmin = 0;
         ext3.kmax = 0;
      }
      if (len1 != len2) {
         extents_transform(bext2, bext1, gmap[gblk2].bnd[ibnd2].orientation,
                                ext3, &trext1);
         extents_shift(gext1,bext1,0,0,pn,1,&ext1);
         ndx1 = MALLOT(int,(len1 + len2));
         len1 = extents_xor(ext1,trext1,gmap[gblk1].jp,gmap[gblk1].kp,ndx1);
         rank = MALLOT(int,len1);
         for (i = 0; i < len1; i++) {
            rank[i] = 0;
         }
         sort2_int(len1, ndx1 - 1, rank - 1);
         bndry_insert(ndx1,&domain->bnd[ibnd1],len1, COM_RECV);
         FREEMEM(ndx1);
         FREEMEM(rank);
      }
      CPYEXT(ext2,bext2);
      len2 = LENEXT(ext2);
      bndry_extend(&ext2,gext2); 
      extents_transform(bext2, bext1, gmap[gblk2].bnd[ibnd2].orientation,
                                  ext2, &trext1);
      len1 = extents_overlap(&trext1,&gext1,&ext3);
      if (ndims == 2) {
         ext3.kmin = 0;
         ext3.kmax = 0;
      }
      if (len1 != len2) {
         extents_shift(gext1,bext1,0,0,pn,-1,&ext1);
         ndx1 = MALLOT(int,(len1 + len2));
         len1 = extents_xor(ext1,ext3,gmap[gblk1].jp,gmap[gblk1].kp,ndx1);
         ndx2 = MALLOT(int,len1);
         bndry_sortndx(ndx1, ndx2, len1, gmap[gblk1].jp, gmap[gblk1].kp, 
                       gmap[gblk1].bnd[ibnd1].orientation);
         bndry_insert(ndx2,&domain->bnd[ibnd1],len1, COM_SEND);
         FREEMEM(ndx1);
         FREEMEM(ndx2);
      }
   }
}
static void  bndry_extend(Extents_t *ext, Extents_t gext) {
   int type;
   int pn[3];
   Extents_t myext;
   CPYEXT(myext,(*ext));
   extents_shift(gext,myext,0,0,pn,1,ext);
   type = extents_gettype((*ext));
   if ((type == FACE) && (ndims == 2)) {
      if (ext->imin == ext->imax) {
         ext->jmin--;
         ext->jmax++;
      }
      if (ext->jmin == ext->jmax) {
         ext->imin--;
         ext->imax++;
      }
   } else if ((type == FACE) && (ndims == 3)) {
      if (ext->imin == ext->imax) {
         ext->jmin--;
         ext->jmax++;
         ext->kmin--;
         ext->kmax++;
      }
      if (ext->jmin == ext->jmax) {
         ext->imin--;
         ext->imax++;
         ext->kmin--;
         ext->kmax++;
      }
      if (ext->kmin == ext->kmax) {
         ext->imin--;
         ext->imax++;
         ext->jmin--;
         ext->jmax++;
      }
   } else if ((type == EDGE) && (ndims == 3)) {
      if (ext->imin != ext->imax) {
         ext->imin--;
         ext->imax++;
      }
      if (ext->jmin != ext->jmax) {
         ext->jmin--;
         ext->jmax++;
      }
      if (ext->kmin != ext->kmax) {
         ext->kmin--;
         ext->kmax++;
      }
   } 
} 
static void bndry_printpair(char *header, int blk1, Extents_t ext1, 
                                   int blk2, Extents_t ext2) 
{
   if (ndims == 3) {
      PRINT(stdout,"%s %i:(%i:%i,%i:%i,%i:%i) and %i:(%i:%i,%i:%i,%i:%i)\n",
                      header, blk1,
                      ext1.imin,ext1.imax,
                      ext1.jmin,ext1.jmax,
                      ext1.kmin,ext1.kmax,
                      blk2,
                      ext2.imin,ext2.imax,
                      ext2.jmin,ext2.jmax,
                      ext2.kmin,ext2.kmax);
   } else {
      PRINT(stdout,"%s %i:(%i:%i,%i:%i) and %i:(%i:%i,%i:%i)\n",header,blk1,
                    ext1.imin,ext1.imax,
                    ext1.jmin,ext1.jmax,
                    blk2,
                    ext2.imin,ext2.imax,
                    ext2.jmin,ext2.jmax);
   }
}
static void bndry_sortndx(int *ndx1, int* ndx2, int len, int jp, int kp, int *orient)
{
   int i,j,k,n;
   int ip,id;
   int istride, jstride, kstride;
   int str[3]; 
   int *rank;
   rank = MALLOT(int,len);
   str[0] = 1;
   str[1] = jp;
   str[2] = kp;
   istride = str[abs(orient[0]) - 1];
   jstride = str[abs(orient[1]) - 1];
   kstride = str[abs(orient[2]) - 1];
   if ((orient[0] == -1) || (orient[1] == -1) || (orient[2] == -1)) {
      istride *= -1;
   }
   if ((orient[0] == -2) || (orient[1] == -2) || (orient[2] == -2)) {
      jstride *= -1;
   }
   if ((orient[0] == -3) || (orient[1] == -3) || (orient[2] == -3)) {
      kstride *= -1;
   }
   if (ndims == 3) {
      for (n = 0; n < len; n++) {
         id = ndx1[n];
         k = id / kp;
         j = (id  - k * kp)/ jp;
         i = (id  - (j * jp) - (k * kp));
         ip = istride * i + jstride * j + kstride * k;
         rank[n] = ip;
         ndx2[n] = id;
      }
   } else {
      for (n = 0; n < len; n++) {
         id = ndx1[n];
         j = id / jp;
         i = id  - (j * jp);
         ip = istride * i + jstride * j; 
         rank[n] = ip;
         ndx2[n] = id;
      }
   } 
   sort2_int(len, rank - 1, ndx2 - 1);
   FREEMEM(rank);
}
static void bndry_insert(int *ndxin, Boundary_t *bnd, int lenin, int com_type) 
{
   int i;
   int len;
   int lennew;
   int lenold;
   int *ndx;
   int *ndxold;
   if (com_type == COM_SEND) {
      lenold    = COM_LEN_ALLN_S((*bnd));
      ndxold = bnd->ndx_send;
   } else {
      lenold = COM_LEN_ALLN_R((*bnd));
      ndxold = bnd->ndx_recv;
   } 
   len = lenin + lenold;
   ndx = MALLOT(int,len);
   lennew = 0; 
   for (i = 0; i < lenold; i++) {
      ndx[lennew++] = ndxold[i];
   }
   for (i = 0; i < lenin; i++) {
      ndx[lennew++] = ndxin[i];
   }
   if (com_type == COM_SEND) {
      FREEMEM(bnd->ndx_send);
      bnd->ndx_send = ndx;
      bnd->len_nsendc += lenin;
   } else {
      FREEMEM(bnd->ndx_recv);
      bnd->ndx_recv = ndx;
      bnd->len_nrecvc += lenin;
   }
}
static void bndry_setbnd(void) 
{
   int iblk;
   int gblk;
   int len;
   int type;
   int ibnd;
   int *ndx;
   int pn[3];
   Extents_t ext;
   Extents_t trext;
   Extents_t lext;
   BndMapping_t *gbnd;
   for (iblk = 0; iblk < nblk; iblk++) {
      CPYEXT(lext,domains[iblk]);
      gblk = domains[iblk].gblk;
      gbnd = gmap[gblk].bnd;
      domains[iblk].nbnd = gmap[gblk].nbnd;
      for (ibnd = 0; ibnd < gmap[gblk].nbnd; ibnd++) {
         len = LENEXT(gmap[gblk].bnd[ibnd]);
         domains[iblk].bnd[ibnd].active         = 1;
         domains[iblk].bnd[ibnd].encon          = 0;
         domains[iblk].bnd[ibnd].blk_send       = gbnd[ibnd].iblk;
         domains[iblk].bnd[ibnd].bndnbc         = gbnd[ibnd].id;
         domains[iblk].bnd[ibnd].orientation[0] = gbnd[ibnd].orientation[0];
         domains[iblk].bnd[ibnd].orientation[1] = gbnd[ibnd].orientation[1];
         domains[iblk].bnd[ibnd].orientation[2] = gbnd[ibnd].orientation[2];
         domains[iblk].bnd[ibnd].len_nsend1     = 0;
         domains[iblk].bnd[ibnd].len_nsend2     = 0;
         domains[iblk].bnd[ibnd].len_nsendc     = 0;
         domains[iblk].bnd[ibnd].len_zsend1     = 0;
         domains[iblk].bnd[ibnd].len_zsend2     = 0;
         domains[iblk].bnd[ibnd].len_zsendc     = 0;
         domains[iblk].bnd[ibnd].len_nrecv1     = 0;
         domains[iblk].bnd[ibnd].len_nrecv2     = 0;
         domains[iblk].bnd[ibnd].len_nrecvc     = 0;
         domains[iblk].bnd[ibnd].len_zrecv1     = 0;
         domains[iblk].bnd[ibnd].len_zrecv2     = 0;
         domains[iblk].bnd[ibnd].len_zrecvc     = 0;
         FREEMEM(domains[iblk].bnd[ibnd].ndx_send);
         FREEMEM(domains[iblk].bnd[ibnd].ndx_recv);
         FREEMEM(domains[iblk].bnd[ibnd].zdx_send);
         FREEMEM(domains[iblk].bnd[ibnd].zdx_recv);
         domains[iblk].bnd[ibnd].ndx_send       = MALLOT(int,3*len);
         domains[iblk].bnd[ibnd].ndx_recv       = MALLOT(int,3*len);
         TRSEXT(domains[iblk].bnd[ibnd],gbnd[ibnd],gmap[gblk]);
         if (ndims == 2) {
            domains[iblk].bnd[ibnd].kmin = 0;
            domains[iblk].bnd[ibnd].kmax = 0;
         }
         CPYEXT(ext,domains[iblk].bnd[ibnd]);
         if (gblk >= domains[iblk].bnd[ibnd].blk_send) {
            extents_getndx(ext, domains[iblk].jp, domains[iblk].kp, 
                           domains[iblk].bnd[ibnd].ndx_send);
            extents_getndx(ext, domains[iblk].jp, domains[iblk].kp, 
                           domains[iblk].bnd[ibnd].ndx_recv);
         } else {
            extents_getndx_orient(ext, domains[iblk].jp, domains[iblk].kp,
                                  domains[iblk].bnd[ibnd].orientation,
                                  domains[iblk].bnd[ibnd].ndx_recv);
            extents_getndx_orient(ext, domains[iblk].jp, domains[iblk].kp,
                                  domains[iblk].bnd[ibnd].orientation,
                                  domains[iblk].bnd[ibnd].ndx_send);
         } 
         domains[iblk].bnd[ibnd].len_nsend1 = len;
         domains[iblk].bnd[ibnd].len_nrecv1 = len;
         CPYEXT(ext,domains[iblk].bnd[ibnd]);
         extents_shift(lext, ext, domains[iblk].jp, domains[iblk].kp, pn, 1, &trext);
         domains[iblk].bnd[ibnd].pn = pn[0] + pn[1] + pn[2];
         domains[iblk].bnd[ibnd].pn_vector[0] = pn[0];
         domains[iblk].bnd[ibnd].pn_vector[1] = pn[1];
         domains[iblk].bnd[ibnd].pn_vector[2] = pn[2];
         ndx = domains[iblk].bnd[ibnd].ndx_recv + len;
         if (gblk >= domains[iblk].bnd[ibnd].blk_send) {
            extents_getndx(trext, domains[iblk].jp, domains[iblk].kp, ndx);
         } else {
            extents_getndx_orient(trext, domains[iblk].jp, domains[iblk].kp, 
                               domains[iblk].bnd[ibnd].orientation, ndx);
         } 
         CPYEXT(ext,domains[iblk].bnd[ibnd]);
         extents_shift(lext, ext, domains[iblk].jp, domains[iblk].kp, pn, -1, &trext);
         ndx = domains[iblk].bnd[ibnd].ndx_send + len;
         if (gblk >= domains[iblk].bnd[ibnd].blk_send) {
            extents_getndx(trext, domains[iblk].jp, domains[iblk].kp, ndx);
         } else {
            extents_getndx_orient(trext, domains[iblk].jp, domains[iblk].kp,
                               domains[iblk].bnd[ibnd].orientation, ndx);
         }
         type = extents_gettype(ext);
         if ((ndims == 2) && (type == FACE)) {
            domains[iblk].bnd[ibnd].len_nsend2 = len;
            domains[iblk].bnd[ibnd].len_nrecv2 = len;
         } else if ((ndims == 2) && (type == CORNER)) {
            domains[iblk].bnd[ibnd].len_nsendc = len;
            domains[iblk].bnd[ibnd].len_nrecvc = len;
         } else if ((ndims == 3) && (type == FACE)) {
            domains[iblk].bnd[ibnd].len_nsend2 = len;
            domains[iblk].bnd[ibnd].len_nrecv2 = len;
         } else if ((ndims == 3) && (type == EDGE)) {
            domains[iblk].bnd[ibnd].len_nsendc = len;
            domains[iblk].bnd[ibnd].len_nrecvc = len;
         } else if ((ndims == 3) && (type == CORNER)) {
            domains[iblk].bnd[ibnd].len_nsendc = len;
            domains[iblk].bnd[ibnd].len_nrecvc = len;
         }
      }
      bndry_tbnd(&domains[iblk]);
      bndry_zonal(&domains[iblk]);
   }
}
static void bndry_zonal(Domain_t *domain) 
{
   int i;
   int pz;
   int rz;
   int ibnd;
   int len;
   int *node;
   int *zone;
   int *ndx;
   int *zdx;
   int *zdxtmp;
   int *n1, *n2, *n3, *n4;
   int *n5, *n6, *n7, *n8;
   node = MALLOT(int,domain->nnalls);
   zone = MALLOT(int,domain->nnalls);
   for (ibnd = 0; ibnd < domain->nbnd; ibnd++) {
      len = COM_LEN_ALLN_S(domain->bnd[ibnd]);
      domain->bnd[ibnd].zdx_send = MALLOT(int,len);
      len = COM_LEN_ALLN_R(domain->bnd[ibnd]);
      domain->bnd[ibnd].zdx_recv = MALLOT(int,len);
      pz = 0;
      if (domain->bnd[ibnd].pn_vector[0] < 0) pz = pz - 1;
      if (domain->bnd[ibnd].pn_vector[1] < 0) pz = pz - domain->jp;
      if (domain->bnd[ibnd].pn_vector[2] < 0) pz = pz - domain->kp;
      domain->bnd[ibnd].pz = pz;
      rz = 0;
      if (domain->bnd[ibnd].pn_vector[0] > 0) rz = rz - 1;
      if (domain->bnd[ibnd].pn_vector[1] > 0) rz = rz - domain->jp;
      if (domain->bnd[ibnd].pn_vector[2] > 0) rz = rz - domain->kp;
      domain->bnd[ibnd].rz = rz;
      for (i = 0; i < domain->nnalls; i++) {
         node[i] = 0;
         zone[i] = 0;
      }
      len = COM_LEN_1N_S(domain->bnd[ibnd]) + COM_LEN_2N_S(domain->bnd[ibnd]);
      ndx = COM_NDX_1N_S(domain->bnd[ibnd]);
      for (i = 0; i < len; i++) {
         node[ndx[i]] = 1;
      }
      len = COM_LEN_1N_R(domain->bnd[ibnd]) + COM_LEN_2N_R(domain->bnd[ibnd]);
      ndx = COM_NDX_1N_R(domain->bnd[ibnd]);
      for (i = 0; i < len; i++) {
         node[ndx[i]] = 1;
      }
      if (ndims == 2) {
         NDSET2D(node,n1,n2,n3,n4);
         for (i = domain->fpz; i <= domain->lpz; i++) {
            if ((n1[i] + n3[i])  == 2) zone[i] = 1;
            if ((n2[i] + n4[i])  == 2) zone[i] = 1;
         }
      } else {
         NDSET3D(node,n1,n2,n3,n4,n5,n6,n7,n8);
         for (i = domain->fpz; i <= domain->lpz; i++) {
            if ((n1[i] + n7[i]) == 2) zone[i] = 1;
            if ((n2[i] + n8[i]) == 2) zone[i] = 1;
            if ((n3[i] + n5[i]) == 2) zone[i] = 1;
            if ((n4[i] + n6[i]) == 2) zone[i] = 1;
         }
      }
      len = 0;
      ndx = domain->bnd[ibnd].ndx_send;
      for (i = 0; i < domain->bnd[ibnd].len_nsend1; i++) {
         if (zone[ndx[i] + rz] == 1) {
            domain->bnd[ibnd].zdx_send[len++] = ndx[i] + rz;
         }
      }
      domain->bnd[ibnd].len_zsend1 = len;
      len = 0;
      ndx = domain->bnd[ibnd].ndx_recv;
      for (i = 0; i < domain->bnd[ibnd].len_nrecv1; i++) {
         if (zone[ndx[i] + pz] == 1) {
            domain->bnd[ibnd].zdx_recv[len++] = ndx[i] + pz;
         }
      }
      domain->bnd[ibnd].len_zrecv1 = len;
      len = COM_LEN_NC_S(domain->bnd[ibnd]);
      ndx = COM_NDX_NC_S(domain->bnd[ibnd]);
      for (i = 0; i < len; i++) {
         node[ndx[i]] = 2;
      }
      if (ndims == 2) {
         for (i = domain->fpz; i <= domain->lpz; i++) {
            if ((n1[i] + n3[i])  == 3) zone[i] = 2;
            if ((n2[i] + n4[i])  == 3) zone[i] = 2;
         }
      } else {
         for (i = domain->fpz; i <= domain->lpz; i++) {
            if ((n1[i] + n7[i]) == 3) zone[i] = 2;
            if ((n2[i] + n8[i]) == 3) zone[i] = 2;
            if ((n3[i] + n5[i]) == 3) zone[i] = 2;
            if ((n4[i] + n6[i]) == 3) zone[i] = 2;
         }
      }
      len = COM_LEN_NC_S(domain->bnd[ibnd]);
      if (len > 0) {
         zdx = COM_ZDX_ZC_S(domain->bnd[ibnd]);
         len = 0;
         for (i = domain->fpz; i <= domain->lpz; i++) {
            if (zone[i] == 2) {
               zdx[len++] = i;
               zone[i] = 0;
            }
         }
         if (domain->gblk < domain->bnd[ibnd].blk_send) {
            zdxtmp = MALLOT(int,len);
            bndry_sortndx(zdx, zdxtmp, len, domain->jp, domain->kp, domain->bnd[ibnd].orientation);
            for (i = 0; i < len; i++) {
               zdx[i] = zdxtmp[i];
            }
            FREEMEM(zdxtmp);
         } 
         domain->bnd[ibnd].len_zsendc = len;
      }
      len = COM_LEN_NC_S(domain->bnd[ibnd]);
      ndx = COM_NDX_NC_S(domain->bnd[ibnd]);
      for (i = 0; i < len; i++) {
         node[ndx[i]] = 0;
      }
      len = COM_LEN_NC_R(domain->bnd[ibnd]);
      ndx = COM_NDX_NC_R(domain->bnd[ibnd]);
      for (i = 0; i < len; i++) {
         node[ndx[i]] = 2;
      }
      if (ndims == 2) {
         for (i = domain->fpz; i <= domain->lpz; i++) {
            if ((n1[i] + n3[i])  == 3) zone[i] = 2;
            if ((n2[i] + n4[i])  == 3) zone[i] = 2;
         }
      } else {
         for (i = domain->fpz; i <= domain->lpz; i++) {
            if ((n1[i] + n7[i]) == 3) zone[i] = 2;
            if ((n2[i] + n8[i]) == 3) zone[i] = 2;
            if ((n3[i] + n5[i]) == 3) zone[i] = 2;
            if ((n4[i] + n6[i]) == 3) zone[i] = 2;
         }
      }
      len = COM_LEN_NC_R(domain->bnd[ibnd]);
      if (len > 0) {
         zdx = COM_ZDX_ZC_R(domain->bnd[ibnd]);
         len = 0;
         for (i = domain->fpz; i <= domain->lpz; i++) {
            if (zone[i] == 2) {
               zdx[len++] = i;
               zone[i] = 0;
            }
         }
         if (domain->gblk < domain->bnd[ibnd].blk_send) {
            zdxtmp = MALLOT(int,len);
            bndry_sortndx(zdx, zdxtmp, len, domain->jp, domain->kp, domain->bnd[ibnd].orientation);
            for (i = 0; i < len; i++) {
               zdx[i] = zdxtmp[i];
            }
            FREEMEM(zdxtmp);
         } 
         domain->bnd[ibnd].len_zrecvc = len;
      }
      len     = COM_LEN_1Z_S(domain->bnd[ibnd]);
      zdx     = COM_ZDX_1Z_S(domain->bnd[ibnd]);
      zdxtmp = COM_ZDX_2Z_S(domain->bnd[ibnd]);
      for (i = 0; i < len; i++) {
         zdxtmp[i] = zdx[i] - domain->bnd[ibnd].pn;
      }
      domain->bnd[ibnd].len_zsend2 = len;
      len     = COM_LEN_1Z_R(domain->bnd[ibnd]);
      zdx     = COM_ZDX_1Z_R(domain->bnd[ibnd]);
      zdxtmp = COM_ZDX_2Z_R(domain->bnd[ibnd]);
      for (i = 0; i < len; i++) {
         zdxtmp[i] = zdx[i] + domain->bnd[ibnd].pn;
      }
      domain->bnd[ibnd].len_zrecv2 = len;
      len = COM_LEN_ALLZ_S(domain->bnd[ibnd]);
      domain->bnd[ibnd].zdx_send = REALLOT(domain->bnd[ibnd].zdx_send,int,len);
      len = COM_LEN_ALLZ_R(domain->bnd[ibnd]);
      domain->bnd[ibnd].zdx_recv = REALLOT(domain->bnd[ibnd].zdx_recv,int,len);
   }
   FREEMEM(node);
   FREEMEM(zone);
}
void bndry_setmomflx( void ) {
   char *me = "bndry_setmomflx";
   char msg[MAXLINE];
   int i,j,k,ibnd;
   int ip, id, gotone;
   int iblk;
   int gblk;
   int *numnodes;
   int *zone, *con, *node, *dnode;
   int *c1, *c2, *c3, *c4, *c5, *c6, *c7, *c8;
   BoundaryInitConnectivity_t *bcon;
   ProblemArray_t *prb;
   numnodes = MALLOT(int, gnblk);
   for (gblk = 0; gblk < gnblk; gblk++) numnodes[gblk] = 0;
   ProblemArray_add("BND_con", NULL, 0, R_INT, NULL);
   ProblemArray_add("BND_node", NULL, 0, R_INT, NULL);
   ProblemArray_add("BND_zone", NULL, 0, R_INT, NULL);
   ProblemArray_add("BND_struct", NULL, 0, R_STRUCT, NULL);
   for (iblk = 0; iblk < nblk; iblk++) {
      int count;
      ProblemArray_add("BND_con", NULL, domains[iblk].nnodes, R_INT, 
                       domains[iblk].hash);
      ProblemArray_add("BND_node", NULL, domains[iblk].nnodes, R_INT, 
                       domains[iblk].hash);
      ProblemArray_add("BND_zone", NULL, domains[iblk].namix, R_INT, 
                       domains[iblk].hash);
      node = ProblemArray_allotptr("BND_node", domains[iblk].hash);
      zone = ProblemArray_allotptr("BND_zone", domains[iblk].hash);
      con  = ProblemArray_allotptr("BND_con", domains[iblk].hash);
      bcon = MALLOT(BoundaryInitConnectivity_t, domains[iblk].nnodes);
      ProblemArray_add("BND_struct", bcon, domains[iblk].nnodes, R_STRUCT, 
                       domains[iblk].hash);
      for (i = 0; i < domains[iblk].nnodes; i++) {
        if (domains[iblk].node[i] == 1) {
           node[i] = domains[iblk].gblk;
        } else {
           node[i] = -1;
        } 
        con[i] = 0;
        bcon[i].nid = 0;
        bcon[i].id = NULL;
      }
      for (i = 0; i < domains[iblk].namix; i++) {
         zone[i] = 0;
      }
      for (ibnd = 0; ibnd < domains[iblk].nbnd; ibnd++) {
         int *ndx = COM_NDX_1N_R(domains[iblk].bnd[ibnd]);
         int  len = COM_LEN_1N_R(domains[iblk].bnd[ibnd]);
         for (i = 0; i < len; i++) {
            if (node[ndx[i]] < domains[iblk].bnd[ibnd].blk_send) {
               node[ndx[i]] = domains[iblk].bnd[ibnd].blk_send;
            }
         }
      }
      count = 0;
      for (i = 0; i < domains[iblk].nnalls; i++) {
         if (node[i] == domains[iblk].gblk) count++;
      }
      numnodes[domains[iblk].gblk] = count;
      if (ndims == 2) {
         for (j = domains[iblk].jmin; j < domains[iblk].jmax; j++) {
            for (i = domains[iblk].imin; i < domains[iblk].imax; i++) {
               ip = i + j * domains[iblk].jp;
               zone[ip] = 1;
            }
         }
      } else {
         for (k = domains[iblk].kmin; k < domains[iblk].kmax; k++) {
            for (j = domains[iblk].jmin; j < domains[iblk].jmax; j++) {
               for (i = domains[iblk].imin; i < domains[iblk].imax; i++) {
                  ip = i + j * domains[iblk].jp + k * domains[iblk].kp;
                  zone[ip] = 1;
               }
            }
         }
      } 
   }
   if (ifparallel) {
     comreduce(numnodes, gnblk, COM_SUM, COM_ALL, COM_INT);
   }
   for (gblk = 1; gblk < gnblk; gblk++) {
      numnodes[gblk] = numnodes[gblk] + numnodes[gblk - 1];
   }
   for (iblk = 0; iblk < nblk; iblk++) {
      int count;
      gblk = domains[iblk].gblk;
      node = (int *) ProblemArray_ptr("BND_node", domains[iblk].hash);
      zone = (int *) ProblemArray_ptr("BND_zone", domains[iblk].hash);
      con  = (int *) ProblemArray_ptr("BND_con", domains[iblk].hash);
      if (gblk == 0) {
         count = 1;
      } else {
         count = numnodes[gblk - 1] + 1;
      } 
      if (ndims == 2) {
         for (j = domains[iblk].jmin; j <= domains[iblk].jmax; j++) {
            for (i = domains[iblk].imin; i <= domains[iblk].imax; i++) {
               ip = i + j * domains[iblk].jp;
               if (node[ip] == gblk) {
                   node[ip] = count;
                   count++;
               }
            }
         }
      } else {
         for (k = domains[iblk].kmin; k <= domains[iblk].kmax; k++) {
            for (j = domains[iblk].jmin; j <= domains[iblk].jmax; j++) {
               for (i = domains[iblk].imin; i <= domains[iblk].imax; i++) {
                  ip = i + j * domains[iblk].jp + k * domains[iblk].kp;
                  if (node[ip] == gblk) {
                      node[ip] = count;
                      count++;
                  }
               }
            }
         }
      } 
      if (ndims == 2) {
         NDSET2D_STRCT(domains[iblk], con, c1, c2, c3, c4);
         for (i = domains[iblk].frz; i <= domains[iblk].lrz; i++) {
            if (zone[i] == 1) {
               c1[i] += 1;
               c2[i] += 1;
               c3[i] += 1;
               c4[i] += 1;
            }
         }
      } else {
         NDSET3D_STRCT(domains[iblk], con, c1, c2, c3, c4, c5, c6, c7, c8);
         for (i = domains[iblk].frz; i <= domains[iblk].lrz; i++) {
            if (zone[i] == 1) {
               c1[i] += 1;
               c2[i] += 1;
               c3[i] += 1;
               c4[i] += 1;
               c5[i] += 1;
               c6[i] += 1;
               c7[i] += 1;
               c8[i] += 1;
            }
         }
      } 
      prb = ProblemArray_find("BND_node",domains[iblk].hash);
      varcomset(prb->ptr, -1, "node", COM_INT, COM_LAYER1N, COM_OVR, gblk);
      prb = ProblemArray_find("BND_con",domains[iblk].hash);
      varcomset(prb->ptr, -1, "con", COM_INT, COM_ACCUM, COM_NOOP, gblk);
   }
   varcom(COM_SET_SIZE);
   varcom(COM_SEND_RECV);
   for (iblk = 0; iblk < nblk; iblk++) {
      int jp = domains[iblk].jp;
      int kp = domains[iblk].kp;
      Boundary_t *bnd = domains[iblk].bnd;
      bcon = (BoundaryInitConnectivity_t *) 
                  ProblemArray_ptr("BND_struct", domains[iblk].hash);
      con  = (int *) ProblemArray_ptr("BND_con", domains[iblk].hash);
      node = (int *) ProblemArray_ptr("BND_node", domains[iblk].hash);
      dnode = domains[iblk].node;
      for (i = domains[iblk].frn; i <= domains[iblk].lrn; i++) {
         if (con[i] > 0) {
            if ((ndims == 2) && (con[i] < 4)) con[i] = 4;
            if ((ndims == 3) && (con[i] < 8)) con[i] = 8;
            bcon[i].id = MALLOT(int,con[i]);
            for (j = 0; j < con[i]; j++) {
               bcon[i].id[j] = -1;
            }
            if (dnode[i - 1 ] == 1) bcon[i].id[bcon[i].nid++] = node[i - 1 ];
            if (dnode[i + 1 ] == 1) bcon[i].id[bcon[i].nid++] = node[i + 1 ];
            if (dnode[i - jp] == 1) bcon[i].id[bcon[i].nid++] = node[i - jp];
            if (dnode[i + jp] == 1) bcon[i].id[bcon[i].nid++] = node[i + jp];
            if (ndims == 3) {
               if (dnode[i - kp] == 1) bcon[i].id[bcon[i].nid++] = node[i - kp];
               if (dnode[i + kp] == 1) bcon[i].id[bcon[i].nid++] = node[i + kp];
            } 
         }
      }
      for (ibnd = 0; ibnd < domains[iblk].nbnd; ibnd++) {
         int *ndx = COM_NDX_1N_R(bnd[ibnd]);
         int  len = COM_LEN_1N_R(bnd[ibnd]);
         gblk = domains[iblk].gblk;
         if (bnd[ibnd].encon == 0) {
            int offset = 0;
            bnd[ibnd].buf_int = MALLOT(int,len + 1);
            for (i = 0; i <= len; i++) bnd[ibnd].buf_int[i] = 0;
            if (abs(bnd[ibnd].pn) == 1)  offset = bnd[ibnd].pn;
            if (abs(bnd[ibnd].pn) == jp) offset = bnd[ibnd].pn;
            if (abs(bnd[ibnd].pn) == kp) offset = bnd[ibnd].pn;
            if (offset != 0) {
               for (i = 0; i < len; i++) {
                  bnd[ibnd].buf_int[i + 1] = node[ndx[i] - offset];
               }
               bnd[ibnd].buf_int[0] = len;
            }
         } else {
            int offset[3];
            int nd = 0;
            int id = 0;
            int *pn = bnd[ibnd].pn_vector;
            int *bp;
            bnd[ibnd].buf_int = MALLOT(int, ((ndims * len) + 1));
            for (i = 0; i <= ndims*len; i++) bnd[ibnd].buf_int[i] = -1;
            if (abs(pn[0]) == 1)  offset[id++] = pn[0];
            if (abs(pn[1]) == jp) offset[id++] = pn[1];
            if ((ndims == 3) && (abs(pn[2]) == kp)) offset[id++] = pn[2];
            bp = bnd[ibnd].buf_int + 1;
            for (nd = 0; nd < id; nd++) {
               for (i = 0; i < len; i++) {
                  bp[i] = node[ndx[i] - offset[nd]];
               }
               bp = bp + len;
            }
            bnd[ibnd].buf_int[0] = id * len;
         } 
      }
      varcomset(NULL, -1, "buf", COM_INT, COM_DIRECT, COM_NOOP, gblk);
   }
   varcom(COM_SET_SIZE);
   varcom(COM_SEND_RECV);
   for (iblk = 0; iblk < nblk; iblk++) {
      Boundary_t *bnd = domains[iblk].bnd;
      int *con;
      bcon = (BoundaryInitConnectivity_t *) 
                  ProblemArray_ptr("BND_struct", domains[iblk].hash);
      con  = (int *) ProblemArray_ptr("BND_con", domains[iblk].hash);
      for (ibnd = 0; ibnd < domains[iblk].nbnd; ibnd++) {
         int *ndx = COM_NDX_1N_R(bnd[ibnd]);
         int  len = COM_LEN_1N_R(bnd[ibnd]);
         if (bnd[ibnd].encon == 0) {
            bnd[ibnd].momflxtag = MALLOT(int, len);
            for (i = 0; i < len; i++) bnd[ibnd].momflxtag[i] = 0;
            bnd[ibnd].len_momflxtag = len;
            for (i = 0; i < len; i++) {
               id = bnd[ibnd].buf_int[i];
               ip = ndx[i];
               gotone = 0;
               for (j = 0; j < bcon[ip].nid; j++) {
                  if (bcon[ip].id[j] == id) gotone = 1;
               }
               if ((id > 0) && (con[ip] > 0) && (gotone == 0)) {
                  if (con[ip] <= bcon[ip].nid) {
                     sprintf(msg,"Boundary %i in domain %i has exceeded unique momentum fluxes for connectivity %i",
                        ibnd, domains[iblk].gblk, con[ip]);
                     ctlerror(me,msg);
                  }
                  bcon[ip].id[bcon[ip].nid++] = id;
                  bnd[ibnd].momflxtag[i] = 1;
               } else {
                  bnd[ibnd].momflxtag[i] = 0;
               } 
            }
            FREEMEM(bnd[ibnd].buf_int);
         } else {
            int nd;
            int *bp;
            int *mtag;
            bnd[ibnd].momflxtag = MALLOT(int, ndims * len);
            for (i = 0; i < ndims * len; i++) bnd[ibnd].momflxtag[i] = 0;
            bnd[ibnd].len_momflxtag = ndims * len;
	    mtag = bnd[ibnd].momflxtag;
	    bp   = bnd[ibnd].buf_int;
	    for (nd = 0; nd < bnd[ibnd].encon; nd++) {
                for (i = 0; i < len; i++) {
	            gotone = 0;
                    ip = ndx[i];
                    id = bp[i];
                    for (j = 0; j < bcon[ip].nid; j++) {
                       if (bcon[ip].id[j] == id) gotone = 1;
                    }
                    if ((id > 0) && (con[ip] > 0) && (gotone == 0)) {
                       if (con[ip] <= bcon[ip].nid) {
                          sprintf(msg,"Boundary %i in domain %i has exceeded unique momentum fluxes for connectivity %i",
                             ibnd, domains[iblk].gblk, con[ip]);
                          ctlerror(me,msg);
                       }
                       bcon[ip].id[bcon[ip].nid++] = id;
                       mtag[i] = 1;
                   }
                }
                bp   = bp   + len;
                mtag = mtag + len;
	    }
            FREEMEM(bnd[ibnd].buf_int);
         } 
      }
      for (i = 0; i < domains[iblk].nnodes; i++) {
         if (bcon[i].nid > 0) {
            FREEMEM(bcon[i].id);
         }
      }
   }
   ProblemArray_free("BND_con");
   ProblemArray_free("BND_node");
   ProblemArray_free("BND_zone");
   ProblemArray_free("BND_struct");
   FREEMEM(numnodes);
}
void bndry_zdxneighbor( void ) {
   char *me = "bndry_zdxneighbor";
   char msg[MAXLINE];
   int ibnd;
   int iblk;
   int i;
   int len;
   int *ndx;
}
