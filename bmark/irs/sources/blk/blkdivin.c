#include "irs.h"
#include "irsblk.h"
#include "irscom.h"
#include "irsctl.h"
#include "BlockMapping.h"
#include "Extents.h"
#include "FunctionTimer.h"
typedef struct {
   int    ublk;
   int    numdomains;
   int    ni;
   int    nj;
   int    nk;
   int   *islice;
   int   *jslice;
   int   *kslice;
   double avezones;
   double error;
} BLKDIV_DECOMP;
#define BLKDIV_NONE         0
#define BLKDIV_SLICE        1
#define BLKDIV_BLOCK_SPEC   2
#define BLKDIV_BLOCK_UNSPEC 3
#define BLKDIV_ZONES_SPEC   4
static void   blkdiv_autodall(BLKDIV_DECOMP *bdiv,int numdomains) ;
static void   blkdiv_gmap    (BLKDIV_DECOMP *bdiv) ;
static void   blkdiv_setslice(BLKDIV_DECOMP *bdiv) ;
static int    blkdiv_getslice(BLKDIV_DECOMP *bdiv, char *opin) ;
static void   blkdiv_zones   (BLKDIV_DECOMP *bdiv) ;
static double blkdiv_cost    (int i, int j, int k, int nx, int ny, int nz) ;
static double blkdiv_autod   (BLKDIV_DECOMP *bdiv) ;
int blkdivin( int mode ) 
{
   char *me = "blkdivin";
   char op[MAXWORD];
   char msg[512];
   int cflag;
   int error;
   int ublk;
   int gblk;
   int iblk;
   int nd;
   int ublk_set;
   int option;
   int opfg;
   int count;
   double cost;
   BLKDIV_DECOMP *bdiv;
   error = 0;
   bdiv = MALLOT(BLKDIV_DECOMP,unblk);
   for (ublk = 0; ublk < unblk; ublk++) {
     bdiv[ublk].ublk = ublk;
     bdiv[ublk].numdomains = 0;
     bdiv[ublk].ni = 0;
     bdiv[ublk].nj = 0;
     bdiv[ublk].nk = 0;
     bdiv[ublk].islice = NULL;
     bdiv[ublk].jslice = NULL;
     bdiv[ublk].kslice = NULL;
     bdiv[ublk].avezones = 0.;
     bdiv[ublk].error    = 0.;
   }
   ublk = blknum;
   ublk_set = 0;
   option = BLKDIV_NONE;
   if (mode == 0) {
      opfg = 1;
   } else {
      opfg = 0;
      option = BLKDIV_BLOCK_UNSPEC;
      bdiv[ublk].numdomains = num_procs;
   } 
   while (opfg == 1) {
      peekc(op);
      if (!strcmp(":",op)) {
         geta(op);
         ublk = geti(&cflag);
	 ublk_set = 1;
         if ((ublk < 0) || (ublk >= unblk)) {
           sprintf(msg,"Block number %d is not valid.\n",ublk);
           ctlerror(me,msg);
         }
      } else if ((!strcmp("i",op)) ||
                 (!strcmp("j",op)) ||
                 (!strcmp("k",op))) {
         option = BLKDIV_SLICE;
	 geta(op);
	 error = blkdiv_getslice(&bdiv[ublk],op);
	 if (error != 0) {
	    sprintf(msg,"Error reading list of %s planes.\n",op);
	    ctlerror(me,msg);
	 }
         if (lfchk()) opfg = 0;
      } else if ((!strcmp("blocks",op)) ||
                 (!strcmp("domains",op))) {
	 geta(op);
	 geta(op); 
         peekc(op);
         if (!strcmp("(",op)) {
            option = BLKDIV_BLOCK_SPEC;
	    geta(op); 
	    bdiv[ublk].ni = geti(&cflag) - 1;
	    geta(op); 
	    bdiv[ublk].nj = geti(&cflag) - 1;
            if (ndims == 3) {
	       peekc(op);
	       if (strcmp(op,"x") ) {
	          bdiv[ublk].nk = 0;
	       } else {
	          geta(op);
	          bdiv[ublk].nk = geti(&cflag) - 1;
	       } 
            }
	    geta(op); 
	    if (lfchk()) opfg = 0;
         } else {
            option = BLKDIV_BLOCK_UNSPEC;
            bdiv[ublk].numdomains = geti(&cflag);
	    if (lfchk()) opfg = 0;
         }
      } else if (!strcmp("zones",op)) {
	 geta(op);
	 geta(op); 
	 bdiv[ublk].avezones = getf(&cflag);
	 bdiv[ublk].error    = getf(&cflag);
         option = BLKDIV_ZONES_SPEC;
         if (lfchk()) opfg = 0;
      } else {
	 opfg=0;
      }		 
   }
   count = 0;
   if ((ublk_set) || (unblk == 1)) {	
      for (gblk = 0; gblk < gnblk; gblk++) { 
         if (gmap[gblk].ublk == ublk) count++;
      }
   } else {
      for (iblk = 0; iblk < unblk; iblk++) { 
         count = 0;
         for (gblk = 0; gblk < gnblk; gblk++) { 
            if (gmap[gblk].ublk == iblk) count++;
         }
         if (count > 1) break;
      }
   } 
   if (count > 1) {
      sprintf(msg, "Elements of this problem have already been decomposed.\n\t\t"
              "Perhaps you have an inappropriately placed blkdiv command.\n\t\t"
              "Make sure you haven't issued a blkdiv twice for the same block\n\t\t"
	      "or during parallel generation.");
      ctlerror(me,msg);
   }
   if (option == BLKDIV_SLICE) {
      blkdiv_gmap(&bdiv[ublk]);
   } else if (option == BLKDIV_BLOCK_SPEC) {
      blkdiv_setslice(&bdiv[ublk]);
      blkdiv_gmap(&bdiv[ublk]);
   } else if (option == BLKDIV_BLOCK_UNSPEC) {
      if ((ublk_set) || (unblk == 1)) {	
         cost = blkdiv_autod(&bdiv[ublk]);
         blkdiv_setslice(&bdiv[ublk]);
         blkdiv_gmap(&bdiv[ublk]);
      } else {
	 nd = bdiv[ublk].numdomains;
	 bdiv[ublk].numdomains = 0;
         blkdiv_autodall(bdiv,nd);
	 for (ublk = 0; ublk < unblk; ublk++) {
	    cost = blkdiv_autod(&bdiv[ublk]);
            blkdiv_setslice(&bdiv[ublk]);
            blkdiv_gmap(&bdiv[ublk]);
	 }
      } 
   } else if (option == BLKDIV_ZONES_SPEC) {
      if ((ublk_set) || (unblk == 1)) {	
         blkdiv_zones(&bdiv[ublk]);
         blkdiv_setslice(&bdiv[ublk]);
         blkdiv_gmap(&bdiv[ublk]);
         nd = bdiv[ublk].numdomains;
      } else {
         nd = 0;
         for (ublk = 0; ublk < unblk; ublk++) {
            bdiv[ublk].avezones = bdiv[0].avezones;
            bdiv[ublk].error    = bdiv[0].error;
            blkdiv_zones(&bdiv[ublk]);
            blkdiv_setslice(&bdiv[ublk]);
            blkdiv_gmap(&bdiv[ublk]);
            nd += bdiv[ublk].numdomains;
         }
         PRINT(stdout,"Total number of domains -> %i.\n",nd);
         if (fpout != NULL) {
            PRINT(fpout,"Total number of domains -> %i.\n",nd);
         }
         for (ublk = 0; ublk < unblk; ublk++) {
            PRINT(stdout,"Block %i -> %i domains\n",ublk, bdiv[ublk].numdomains);
            if (fpout != NULL) {
               PRINT(fpout,"Block %i -> %i domains\n",ublk, bdiv[ublk].numdomains);
            }
         }
      } 
   } 
   for (ublk = 0; ublk < unblk; ublk++) {
      if (bdiv[ublk].ni > 0) FREEMEM(bdiv[ublk].islice);
      if (bdiv[ublk].nj > 0) FREEMEM(bdiv[ublk].jslice);
      if (bdiv[ublk].nk > 0) FREEMEM(bdiv[ublk].kslice);
   }
   FREEMEM(bdiv);
   return(error) ;
}
static int blkdiv_getslice(BLKDIV_DECOMP *bdiv, char *opin) {
   char op[MAXWORD];
   int ublk;
   int len;
   int opfg;
   int error;
   int cflag;
   int j;
   int *slice;
   ublk = bdiv->ublk;
   opfg = 1;
   if (!strcmp(opin,"i")) {
      len = umap[ublk].imax - umap[ublk].imin;
      bdiv->islice = MALLOT(int,len);
      slice = bdiv->islice;
   } else if (!strcmp(opin,"j")) {
      len = umap[ublk].jmax - umap[ublk].jmin;
      bdiv->jslice = MALLOT(int,len);
      slice = bdiv->jslice;
   } else if (!strcmp(opin,"k")) {
      len = umap[ublk].kmax - umap[ublk].kmin;
      bdiv->kslice = MALLOT(int,len);
      slice = bdiv->kslice;
   } 
   geta(op); 
   geta(op); 
   j = 0;
   error = 0;
   while (opfg == 1) {
      peekc(op);
      if (!strcmp(")",op)) {
         geta(op);
         opfg = 0;
      } else {
         slice[j] = geti(&cflag) + NPNL - 1;
         if (cflag == 1) {
            error = 1;
            opfg = 0;
         }
         j++;
      } 
   }
   if (!strcmp(opin,"i")) bdiv->ni = j;
   if (!strcmp(opin,"j")) bdiv->nj = j;
   if (!strcmp(opin,"k")) bdiv->nk = j;
   return(error);
}
static void blkdiv_setslice(BLKDIV_DECOMP *bdiv) {
   int i;	 
   int rem;
   int inc;
   int len;
   int ublk;
   ublk = bdiv->ublk;
   if (bdiv->ni > 0) {
      bdiv->islice = MALLOT(int,bdiv->ni);
      len = umap[ublk].imax - umap[ublk].imin;
      inc = len / (bdiv->ni + 1);
      rem = len % (bdiv->ni + 1);
      bdiv->islice[0] = NPNL + inc;
      if (rem > 0) {
         bdiv->islice[0]++;
         rem--;
      }
      for (i = 1; i < bdiv->ni; i++) {
         bdiv->islice[i] = bdiv->islice[i - 1] + inc;
	 if (rem > 0) {
            bdiv->islice[i]++;
            rem--;
	 }
      }
   }
   if (bdiv->nj > 0) {
      bdiv->jslice = MALLOT(int,bdiv->nj);
      len = umap[ublk].jmax - umap[ublk].jmin;
      inc = len / (bdiv->nj + 1);
      rem = len % (bdiv->nj + 1);
      bdiv->jslice[0] = NPNL + inc;
      if (rem > 0) {
         bdiv->jslice[0]++;
         rem--;
      }
      for (i = 1; i < bdiv->nj; i++) {
         bdiv->jslice[i] = bdiv->jslice[i - 1] + inc;
	 if (rem > 0) {
            bdiv->jslice[i]++;
            rem--;
	 }
      }
   } 
   if (bdiv->nk > 0) {
      bdiv->kslice = MALLOT(int,bdiv->nk);
      len = umap[ublk].kmax - umap[ublk].kmin;
      inc = len / (bdiv->nk + 1);
      rem = len % (bdiv->nk + 1);
      bdiv->kslice[0] = NPNL + inc;
      if (rem > 0) {
         bdiv->kslice[0]++;
         rem--;
      }
      for (i = 1; i < bdiv->nk; i++) {
         bdiv->kslice[i] = bdiv->kslice[i - 1] + inc;
	 if (rem > 0) {
            bdiv->kslice[i]++;
            rem--;
	 }
      } 
   } 
}
static void blkdiv_gmap(BLKDIV_DECOMP *bdiv) {
   char *me = "blkdiv_gmap";
   char msg[MAXLINE];
   int i,j;
   int ip;
   int len;
   int ublk;
   int gblk;
   int nbnd1,nbnd2;
   int gblk1,gblk2;
   int gblk_last;
   int gblk_next;
   int numdomains;
   Extents_t *ext;
   Extents_t ext0;
   Extents_t extovlp;
   Extents_t gext1;
   Extents_t gext2;
   for (i = 0; i < bdiv->ni - 1; i++) {
      for (j = bdiv->ni - 1; j > i; j--) {
        if (bdiv->islice[i] > bdiv->islice[j]) {
           ip = bdiv->islice[j];
           bdiv->islice[j] = bdiv->islice[i];
           bdiv->islice[i] = ip;
        }
      }
   }
   for (i = 0; i < bdiv->nj - 1; i++) {
      for (j = bdiv->nj - 1; j > i; j--) {
        if (bdiv->jslice[i] > bdiv->jslice[j]) {
           ip = bdiv->jslice[j];
           bdiv->jslice[j] = bdiv->jslice[i];
           bdiv->jslice[i] = ip;
        }
      }
   }
   for (i = 0; i < bdiv->nk - 1; i++) {
      for (j = bdiv->nk - 1; j > i; j--) {
        if (bdiv->kslice[i] > bdiv->kslice[j]) {
           ip = bdiv->kslice[j];
           bdiv->kslice[j] = bdiv->kslice[i];
           bdiv->kslice[i] = ip;
        }
      }
   }
   ublk = bdiv->ublk;
   CPYEXT(ext0,umap[ublk]);
   numdomains = (bdiv->ni + 1) * (bdiv->nj + 1) * (bdiv->nk + 1);
   if ((gnblk + numdomains - 1) > nblkx) {
      sprintf(msg,"Number of domains (%i) exceeds nblkx (%i).  Please increase nblkx.",numdomains + gnblk -1, nblkx);
      ctlerror(me,msg);   
   }
   ext    = MALLOT(Extents_t,numdomains);
   for (gblk = 0; gblk < numdomains; gblk++) {
       CPYEXT(ext[gblk],ext0);
   }
   gblk_last = 0;
   gblk_next = 1;
   for (i = 0; i < bdiv->ni; i++) {
      for (gblk = 0; gblk <= gblk_last; gblk++) {
         if ((bdiv->islice[i] > ext[gblk].imin) &&
             (bdiv->islice[i] < ext[gblk].imax)) {
            ext[gblk_next].imin = bdiv->islice[i];
            ext[gblk_next].imax = ext[gblk].imax;
            ext[gblk].imax      = bdiv->islice[i];
            gblk_next++;
         }
      }
      gblk_last = gblk_next;
   }
   for (i = 0; i < bdiv->nj; i++) {
      for (gblk = 0; gblk <= gblk_last; gblk++) {
         if ((bdiv->jslice[i] > ext[gblk].jmin) &&
             (bdiv->jslice[i] < ext[gblk].jmax)) {
            ext[gblk_next].jmin = bdiv->jslice[i];
            ext[gblk_next].jmax = ext[gblk].jmax;
            ext[gblk_next].imin = ext[gblk].imin;
            ext[gblk_next].imax = ext[gblk].imax;
            ext[gblk].jmax      = bdiv->jslice[i];
            gblk_next++;
         }
      }
      gblk_last = gblk_next;
   }
   for (i = 0; i < bdiv->nk; i++) {
      for (gblk = 0; gblk <= gblk_last; gblk++) {
         if ((bdiv->kslice[i] > ext[gblk].kmin) &&
             (bdiv->kslice[i] < ext[gblk].kmax)) {
            ext[gblk_next].kmin = bdiv->kslice[i];
            ext[gblk_next].kmax = ext[gblk].kmax;
            ext[gblk_next].imin = ext[gblk].imin;
            ext[gblk_next].imax = ext[gblk].imax;
            ext[gblk_next].jmin = ext[gblk].jmin;
            ext[gblk_next].jmax = ext[gblk].jmax;
            ext[gblk].kmax      = bdiv->kslice[i];
            gblk_next++;
         }
      }
      gblk_last = gblk_next;
   }
   for (gblk = 0; gblk < gnblk; gblk++) {
      if (gmap[gblk].ublk == ublk) break;
   }
   gblk_last  = gnblk;
   gnblk = gblk;
   setgmap(ublk,ext[0]);
   gnblk = gblk_last;
   for (gblk = 1; gblk < numdomains; gblk++) {
      setgmap(ublk,ext[gblk]);
   }
   for (gblk1 = 0; gblk1 < gnblk; gblk1++) {
      if (gmap[gblk1].ublk != ublk) continue;
      CPYEXT(gext1,gmap[gblk1]);
      for (gblk2 = gblk1 + 1; gblk2 < gnblk; gblk2++) {
         if (gmap[gblk2].ublk != ublk) continue;
         CPYEXT(gext2,gmap[gblk2]);
         len = extents_overlap(&gext1,&gext2,&extovlp);
	 if (len > 0) {
            nbnd1 = gmap[gblk1].nbnd;
            nbnd2 = gmap[gblk2].nbnd;
	    gmap[gblk1].bnd[nbnd1].iblk = gblk2;
	    gmap[gblk2].bnd[nbnd2].iblk = gblk1;
	    gmap[gblk1].bnd[nbnd1].id = nbnd2;
	    gmap[gblk2].bnd[nbnd2].id = nbnd1;
	    CPYEXT(gmap[gblk1].bnd[nbnd1],extovlp);
	    CPYEXT(gmap[gblk2].bnd[nbnd2],extovlp);
            gmap[gblk1].bnd[nbnd1].orientation[0] = 1;
            gmap[gblk1].bnd[nbnd1].orientation[1] = 2;
            gmap[gblk1].bnd[nbnd1].orientation[2] = 3;
            gmap[gblk2].bnd[nbnd2].orientation[0] = 1;
            gmap[gblk2].bnd[nbnd2].orientation[1] = 2;
            gmap[gblk2].bnd[nbnd2].orientation[2] = 3;
            gmap[gblk1].nbnd++;
            gmap[gblk2].nbnd++;
	 }
      }
   }
   if (numdomains > 0) ifcom = 1;
   FREEMEM(ext);
}
static double blkdiv_autod(BLKDIV_DECOMP *bdiv) {
   int i,j,n;
   int ublk;
   int nx, ny ,nz;
   int imin, jmin, kmin;
   double cost;
   double costmin;
   costmin = plarge;
   n = bdiv->numdomains;
   ublk = bdiv->ublk;
   nx = umap[ublk].imax - umap[ublk].imin + 1;
   ny = umap[ublk].jmax - umap[ublk].jmin + 1;
   nz = umap[ublk].kmax - umap[ublk].kmin + 1;
   for (i = 1; i <= n; i++) {
       if (n%i == 0) {
          if (ndims == 3) {
             for (j = 1; j <= i; j++) {
                if ((i%j) == 0) {
                   cost = blkdiv_cost(j, i/j, n/i, nx, ny, nz);
                   if (cost < costmin) {
                      imin = j;
                      jmin = i/j;
                      kmin = n/i;
                      costmin = cost;
                   }
                }
             }
          } else {
             cost = blkdiv_cost(i, n/i, 1, nx, ny, nz);
             if (cost < costmin) {
                imin = i;
                jmin = n/i;
                kmin = 1;
                costmin = cost;
             }
          } 
       }
    }
    bdiv->ni  = imin - 1;
    bdiv->nj  = jmin - 1;
    bdiv->nk  = kmin - 1;
    return(costmin);
}
static void blkdiv_autodall(BLKDIV_DECOMP *bdiv,int numdomains) {
   int ublk;
   int ublk1,ublk2;
   int uidtmp;
   int totzones;
   int avezones;
   int ndoms;
   int ndoms_orig;
   int j;
   int *uzones;
   int *udoms;
   int *uid;
   double udevtmp;
   double *udev;
   totzones = 0;
   if (numdomains <= unblk) {
      for (ublk = 0; ublk < unblk; ublk++) {
         bdiv[ublk].numdomains = 1;
      }
      return;
   }
   uzones = MALLOT(int,unblk);
   udoms  = MALLOT(int,unblk);
   uid    = MALLOT(int,unblk);
   udev   = MALLOT(double,unblk);
   for (ublk = 0; ublk < unblk; ublk++) {
      if (ndims == 2) {
         uzones[ublk] = (umap[ublk].imax - umap[ublk].imin) * 
                        (umap[ublk].jmax - umap[ublk].jmin);
      } else {
         uzones[ublk] = (umap[ublk].imax - umap[ublk].imin) * 
                        (umap[ublk].jmax - umap[ublk].jmin) *
                        (umap[ublk].kmax - umap[ublk].kmin);
      } 
      totzones     += uzones[ublk];
      uid[ublk]    =  ublk;
      udoms[ublk]  =  0;
      udev[ublk]   =  0.;
   }
   avezones = (int)( ( (double)totzones / (double)numdomains ) + 0.5);
   ndoms = 0;
   for (ublk = 0; ublk < unblk; ublk++) {
      udoms[ublk] = (int)( ( (double)uzones[ublk] / (double)avezones ) + 0.5);
      udoms[ublk] = MAX(udoms[ublk],1);
      udev[ublk]  = ((double)(udoms[ublk] * avezones - uzones[ublk]))/
                     (double)(udoms[ublk]);
      ndoms += udoms[ublk];
   }
   ndoms_orig = ndoms;
   for (ublk1 = 0; ublk1 < unblk - 1; ublk1++) {
      for (ublk2 = unblk - 1; ublk2 > ublk1; ublk2--) {
         if (udev[ublk1] < udev[ublk2]) {
            udevtmp     = udev[ublk2];
            uidtmp      = uid[ublk2];
            udev[ublk2] = udev[ublk1];
            uid[ublk2]  = uid[ublk1];
            udev[ublk1] = udevtmp;
            uid[ublk1]  = uidtmp;
         }
      }
   }
   if (ndoms > numdomains) {
      j = 0;
      while (ndoms != numdomains) {
         ublk = uid[j];
         if (udoms[ublk] == 1) {
            j++;
            continue;
         }
         udoms[ublk]--;
         udev[j]  = ((double)(udoms[ublk] * avezones - uzones[ublk]))/
                     (double)(udoms[ublk]);
         ndoms--;
         j++;
      }
   } else if (ndoms < numdomains) {
      j = unblk - 1;
      while (ndoms != numdomains) {
         ublk = uid[j];
         udoms[ublk]++;
         udev[j]  = ((double)(udoms[ublk] * avezones - uzones[ublk]))/
                        (double)(udoms[ublk]);
         ndoms++;
         j--;
      }
   }
   PRINT(stdout,"Original guess of domains -> %i.\n",ndoms_orig);
   PRINT(stdout,"Total number of zones -> %i.\n",totzones);
   PRINT(stdout,"Average number of zones -> %i.\n",avezones);
   if (fpout != NULL) {
      PRINT(fpout,"Original guess of domains -> %i.\n",ndoms_orig);
      PRINT(fpout,"Total number of zones -> %i.\n",totzones);
      PRINT(fpout,"Average number of zones -> %i.\n",avezones);
   }
   for (j = 0; j < unblk; j++) {
      ublk = uid[j];
      bdiv[ublk].numdomains = udoms[ublk];
      PRINT(stdout,"Block %i -> %i domains with deviation %f zones\n",ublk, udoms[ublk],udev[j]);
      if (fpout != NULL) {
         PRINT(fpout,"Block %i -> %i domains with deviation %f zones\n",ublk, udoms[ublk],udev[j]);
      }
   }
   FREEMEM(uzones);
   FREEMEM(udoms);
   FREEMEM(udev);
   FREEMEM(uid);
}
static double blkdiv_cost(int i, int j, int k, int nx, int ny, int nz) {
   double costtot;
   i--;
   j--;
   k--;
   costtot = 0;
   costtot+=i*((ny*nz));
   costtot+=j*((nx*nz));
   costtot+=k*((ny*nx));
   costtot+=2*i*j*((nz));
   costtot+=2*i*k*((ny));
   costtot+=2*j*k*((nx));
   costtot+=4*i*j*k;
   return(costtot);
}
static void blkdiv_zones(BLKDIV_DECOMP *bdiv) {
   int ublk;	
   int nd;	
   int ndoms_min;
   int ndoms_max;
   int ndmin;
   double zones;
   double costmin;
   double cost;
   ublk = bdiv->ublk;
   if (ndims == 2) {
      zones = ( double ) ((umap[ublk].imax - umap[ublk].imin) * 
                          (umap[ublk].jmax - umap[ublk].jmin));
   } else {
      zones = ( double ) ((umap[ublk].imax - umap[ublk].imin) * 
                          (umap[ublk].jmax - umap[ublk].jmin) *
                          (umap[ublk].kmax - umap[ublk].kmin));
   } 
   ndoms_min = (int ) (( zones / (bdiv->avezones * ( 1 + bdiv->error)) ) );
   ndoms_max = (int ) (( zones / (bdiv->avezones * ( 1 - bdiv->error)) ) );
   costmin = plarge;
   ndmin   = ndoms_min;
   if ((ndoms_max > 1) && (ndoms_min == 1)) ndoms_min++; 
   for (nd = ndoms_min; nd <= ndoms_max; nd++) {
      bdiv->numdomains = nd;
      cost = blkdiv_autod(bdiv);
      if (cost < costmin) {
         ndmin    = nd;
         costmin  = cost;
      }
   }
   bdiv->numdomains = ndmin;
   cost = blkdiv_autod(bdiv);
}
#undef BLKDIV_NONE
#undef BLKDIV_SLICE
#undef BLKDIV_BLOCK_SPEC
#undef BLKDIV_BLOCK_UNSPEC
#undef BLKDIV_ZONES_SPEC
