#include "irs.h"
#include "irsrgst.h"
#include "irsblk.h"
#include "irscom.h"
#include "irsbndry.h"
#include "irsdmp.h"
#include "irsctl.h"
#include "irsgen.h"
#include "BndMapping.h"
#include "BlockMapping.h"
#include "Extents.h"
#include "Hash.h"
#include "NodeList.h"
#define SEWMESH_MAX_UBLK 256
#define SEWMESH_MAX_GBLK 2048
#define SEWMESH_MAXMESH  256
#define SEWMESH_MAXBND   64
#define MESH_TRUEGRID 1
#define MESH_SILO 2
typedef struct {
   int type;
   int num_blocks;
   char name[MAXLINE];
} SEWMESH_MESHDESC;
typedef struct {
   double x[27];
   double y[27];
   double z[27];
} SEWMESH_BNDMATCH;
typedef struct {
   SEWMESH_BNDMATCH *bnd;
} SEWMESH_BLKBND;
typedef struct {
   int id;
   int nsblk;
   int      *map;
   Extents_t   ext;
   BlockMapping_t *smap;
   NodeWindow_t *nlist;
} SUPER_BLK;

#ifdef SILO
static int  sewmeshes_wtmesh(double *x, double *y, double *z, int ublk, 
                             SEWMESH_BLKBND *umapm,  DBoptlist *Options, 
                             DBfile *OutFile) ;
#endif

static int  sewmeshes_consolidate(SUPER_BLK *sblk, int id) ;
static int  sewmeshes_getnodes(int ublk, int dir, SUPER_BLK *sblk);
static void sewmeshes_matchmesh(SEWMESH_BLKBND *umapm) ;
static void sewmeshes_determine_size(SUPER_BLK *sblk) ;
static void sewmeshes_merge_NodeLists( SUPER_BLK *sblk );
static void sewmeshes_pack_bnds(SUPER_BLK *sblk ) ;
static void sewmeshes_merge_ublks(int *map, BlockMapping_t *newumap) ;
static void sewmeshes_NodeList_update( int *meshmap );
static void sewmeshes_siloize_tg(char *name, int num_block, int num, int ustart) ;

#ifdef SILO
int sewmeshes(int NumOutputFiles) {
   char *me = "sewmeshes";
   char msg[MAXLINE];
   char op[MAXLINE];
   char outname[MAXLINE];
   char outstr[MAXLINE];
   char redostr[MAXLINE];
   char searchpath[]="";
   char **meshnames;
   int gotone;
   int nmeshes;
   int i,j,nm;
   int iblk;
   int ublk;
   int nunblk;
   int unblk_old;
   int gblk;
   int error;
   int len;
   int num_supblk;
   int junki;
   int trueGridFileCount;
   int siloFileCount;
   int *meshtypes;
   int *meshmap;
   int *meshnum;
   int *meshblk;
   int *node;
   int dims[3];
   double *x, *y, *z;
   SEWMESH_BLKBND *umapm;
   SEWMESH_MESHDESC mdesc[SEWMESH_MAXMESH];
   SUPER_BLK *sblks;
   BlockMapping_t *numap;
   DBfile *OutFile;
   DBfile *SiloFile;
   DBoptlist *Options;
   Extents_t ext;
   gmap = ALLOT(BlockMapping_t,SEWMESH_MAX_GBLK) ;
   umap = ALLOT(BlockMapping_t,SEWMESH_MAX_UBLK) ;
   umapm = ALLOT(SEWMESH_BLKBND,SEWMESH_MAX_UBLK) ;
   sblks = ALLOT(SUPER_BLK,SEWMESH_MAX_UBLK) ;
   meshmap = ALLOT(int,SEWMESH_MAX_UBLK) ;
   meshnum = ALLOT(int,SEWMESH_MAX_UBLK) ;
   meshblk = ALLOT(int,SEWMESH_MAX_UBLK) ;
   unblk = 0;
   gnblk = 0;
   nblkx = SEWMESH_MAX_GBLK;
   nbndx = SEWMESH_MAXBND;
   for (ublk = 0; ublk < SEWMESH_MAX_UBLK; ublk++) {
      meshmap[ublk] = -1;
      meshnum[ublk] = -1;
      meshblk[ublk] = -1;
      umap[ublk].bnd = MALLOT(BndMapping_t,SEWMESH_MAXBND);
      umapm[ublk].bnd = MALLOT(SEWMESH_BNDMATCH,SEWMESH_MAXBND);
   }
   for (i = 0; i < SEWMESH_MAX_UBLK; i++) {
      umap[i].nbnd = 0;
   }
   for (ublk = 0; ublk < SEWMESH_MAX_GBLK; ublk++) {
      gmap[ublk].bnd = MALLOT(BndMapping_t,SEWMESH_MAXBND);
   }
   for (i = 0; i < SEWMESH_MAX_GBLK; i++) {
      gmap[i].nbnd = 0;
   }
   genmd = 1;
   gotone = 1;
   nmeshes = 0;
   while (gotone) {
      peekc(op);
      if (!strcmp(op,"rdmesh")) {
         geta(op);
         geta(op);
         if (!strcmp(op,"silo")) {
            mdesc[nmeshes].type = MESH_SILO;
	    geta(op);
            strcpy(mdesc[nmeshes].name,op);
            SiloFile = DBOpen (mdesc[nmeshes].name, DB_PDB, DB_READ);
	    ublk = unblk;
            decomp_setdir(SiloFile);		 
	    decomp_read(SiloFile, op, unblk, gnblk);
            DBSetDir(SiloFile,"/");
	    for (i = 0; i < gnblk; i++) {
	       gmap[i].nbnd = 0;
	    }
	    for (i = ublk; i < unblk; i++) {
	       meshmap[i] = i;
	       meshblk[i] = i - ublk;
	       meshnum[i] = nmeshes;
	    }
            mdesc[nmeshes].num_blocks = (unblk - ublk);
            DBShowErrors(DB_NONE, NULL);
	    error = DBSetDir(SiloFile,"Nodelists");
	    if (error != 0) {
	       error = DBSetDir(SiloFile,"/Global/Nodelists");
	    }
            DBShowErrors(DB_TOP, NULL);
	    if (error == 0) {
	       NodeList_rdsilo(SiloFile,ublk);
	    } else {
               error = 0;		 
	    } 
	    DBClose(SiloFile);
         } else if (!strcmp(op,"truegrid")) {
            mdesc[nmeshes].type = MESH_TRUEGRID;
            geta(mdesc[nmeshes].name);
            error = newfile(mdesc[nmeshes].name,1);
            if (error != 0) {
               sprintf(msg,"Failed to open TrueGrid mesh %s",
                                                   mdesc[nmeshes].name);
               ctlerror(me,msg);
            }
            error = rdtruegrid_decomp(umap, unblk, 1, 
                                             &mdesc[nmeshes].num_blocks);
            for (ublk=unblk; ublk < (unblk+mdesc[nmeshes].num_blocks); ublk++) {
	       meshmap[ublk] = ublk;
	       meshblk[ublk] = ublk - unblk;
	       meshnum[ublk] = nmeshes;
               CPYEXT(ext,umap[ublk]);
               setgmap(ublk,ext);
            }
            unblk += mdesc[nmeshes].num_blocks;
            if (error != 0) {
               sprintf(msg,"Failed to read TrueGrid mesh %s",
                                                   mdesc[nmeshes].name);
               ctlerror(me,msg);
            }
            endfile();
         }  else {
            sprintf(msg,"Mesh type %s is not recognized.",op);
            ctlerror(me,msg);
         }  
         nmeshes++;
      } else {
         gotone = 0;
      } 
   }
   gotone = 1;
   if (!strcmp(op,"done")) {
      gotone = 0;
   }
   while (gotone) {
      if (!strcmp(op,"bnd")) {
         geta(op);
         bndin();
      } else {
         gotone = 0;
      } 
      if (gotone) peekc(op);
   }
   gotone = 1;
   if (!strcmp(op,"done")) {
      gotone = 0;
   }
   num_supblk = 0;
   unblk_old = unblk;
   while (gotone) {
      if (!strcmp(op,"consolidate")) {
         geta(op);
         sewmeshes_consolidate(&sblks[num_supblk],num_supblk);
         num_supblk++;
      } else {
         gotone = 0;
      } 
      if (gotone) peekc(op);
   }
   if (strcmp(op,"done")) strcpy(redostr,line);
   for (i = 0; i < num_supblk; i++) {
      sewmeshes_determine_size(&sblks[i]);
      sewmeshes_pack_bnds(&sblks[i]);
      sewmeshes_merge_NodeLists(&sblks[i]);
      for (iblk = 1; iblk < sblks[i].nsblk; iblk++) {
         ublk = sblks[i].smap[iblk].ublk;
         meshmap[ublk] = -1;
      }
   }
   if (num_supblk > 0) {
      i = 0;
      ublk = 0;
      for (nm = 0; nm < nmeshes; nm++) {
         if (mdesc[nm].type == MESH_TRUEGRID) {
            sewmeshes_siloize_tg(mdesc[nm].name,mdesc[nm].num_blocks,i,ublk);
            i++;
         }
         ublk += mdesc[nm].num_blocks;
      }
      for (i = 0; i < num_supblk; i++) {
         ublk = sblks[i].smap[0].ublk;
         umap[ublk].jp = sblks[i].ext.imax - sblks[i].ext.imin + 1 + NPNL + NPNR;
         umap[ublk].kp = sblks[i].ext.jmax - sblks[i].ext.jmin + 1 + NPNL + NPNR;
         CPYEXT(umap[ublk],sblks[i].ext);
         if (ndims == 2) {
            umap[ublk].kp = 0;
         } else {
            umap[ublk].kp = umap[ublk].kp * umap[ublk].jp;
         } 
      }
      nunblk = 0;
      for (ublk = 0; ublk < unblk; ublk++) {
         if (meshmap[ublk] >= 0) {
            meshmap[ublk] = nunblk;
            nunblk++;
         }
      }
      numap = ALLOT(BlockMapping_t,nunblk) ;
      for (ublk = 0; ublk < nunblk; ublk++) {
         numap[ublk].bnd = MALLOT(BndMapping_t,SEWMESH_MAXBND);
      }
      sewmeshes_merge_ublks(meshmap,numap);
      for (i = 0; i < num_supblk; i++) {
         ublk = sblks[i].smap[0].ublk;
         sblks[i].id = meshmap[ublk];
         for (iblk = 1; iblk < sblks[i].nsblk; iblk++) {
            meshmap[sblks[i].smap[iblk].ublk] = meshmap[ublk];
         }
      }
      sewmeshes_NodeList_update(meshmap);
      for (ublk = 0; ublk < SEWMESH_MAX_UBLK; ublk++) {
         FREEMEM(umap[ublk].bnd);
      }
      FREEMEM(umap);
      umap = numap;
      unblk = nunblk;
      gnblk = 0;
      for (ublk = 0; ublk < unblk; ublk++) {
         CPYEXT(ext,umap[ublk]);
         setgmap(ublk,ext);
      }
   }
   gotone = 1;
   if (!strcmp(op,"done")) {
      gotone = 0;
   }
   if (gotone) {
      strcpy(line,redostr);
      ps = line;
   }
   while (gotone) {
      if (!strcmp(op,"blkdiv")) {
         geta(op);
         blkdivin(0);
      } else {
         gotone = 0;
      } 
      if (gotone) peekc(op);
   }
   sprintf(outname,"%smesh.silo",pbnm);
   OutFile = DBCreate(outname, DB_CLOBBER, DB_LOCAL, NULL, DB_PDB );
   dims[0] = 1;
   error = DBWrite(OutFile, "_meshtv_searchpath", searchpath, dims, 1, DB_CHAR);
    Options = DBMakeOptlist( MAXOPTS ); 
   set_silo_option(Options, -1); 
   nblk = gnblk;
   trueGridFileCount = 0;
   siloFileCount = 0;
   nm = -1;
   for (ublk = 0; ublk < unblk; ublk++) {
      CPYEXT(ext,umap[ublk]);
      if (ndims == 2) {
         len = (ext.imax + NPNR + 1)*(ext.jmax + NPNR + 1);
      } else {
         len = (ext.imax + NPNR + 1)*(ext.jmax + NPNR + 1)*
               (ext.kmax + NPNR + 1);
      } 
      x    = MALLOT(double, len);
      y    = MALLOT(double, len);
      z    = MALLOT(double, len);
      node = MALLOT(int   , len);
      for (i = 0; i < num_supblk; i++) {
         if (sblks[i].id == ublk) break;
      }
      if ((num_supblk != 0) && (i != num_supblk)) {
         for (iblk = 0; iblk < sblks[i].nsblk; iblk++) {
            nm = meshnum[sblks[i].smap[iblk].ublk];
            SiloFile = DBOpen (mdesc[nm].name, DB_PDB, DB_READ);
            gblk = meshblk[sblks[i].smap[iblk].ublk];
            sprintf(outstr,"/domain%i",gblk);		 
            error += DBSetDir(SiloFile,outstr);
            CPYEXT(ext,sblks[i].smap[iblk]);
            rdsilomesh(SiloFile,"hydro_mesh", x, y, z, node, ext, 
	                   umap[ublk].jp, umap[ublk].kp);
            error += DBSetDir(SiloFile,"../");
            DBClose(SiloFile);
         }
      } else {
         if (nm != meshnum[ublk]) {
            if (nm != -1) {
               if (mdesc[nm].type == MESH_TRUEGRID) {
                  endfile();
                  trueGridFileCount--;
               } else if (mdesc[nm].type == MESH_SILO) {
                  DBClose(SiloFile);
                  siloFileCount--;
               } 
            }
            nm = meshnum[ublk];
            PRINT(stdout,"Opening mesh file %s\n",mdesc[nm].name);
            if (mdesc[nm].type == MESH_TRUEGRID) {
               error = newfile(mdesc[nm].name,1);
               newline();
               nxtsym(1);
               error = rdtruegrid_decomp(umap, -1, 0, &junki);
               trueGridFileCount++;
            } else if (mdesc[nm].type == MESH_SILO) {
               SiloFile = DBOpen (mdesc[nm].name, DB_PDB, DB_READ);
               siloFileCount++;
               j = 0;
            } 
         }
         if (mdesc[nm].type == MESH_TRUEGRID) {
            PRINT(stdout,"Reading mesh block %i\n",ublk);
            rdtruegrid_mesh(x, y, z, node, ext, umap[ublk].jp, umap[ublk].kp);
         } else if (mdesc[nm].type == MESH_SILO) {
            PRINT(stdout,"Reading mesh block %i\n",ublk);
            sprintf(outstr,"/domain%i",j);		 
            j++;
            error += DBSetDir(SiloFile,outstr);
            rdsilomesh(SiloFile,"hydro_mesh", x, y, z, node, ext, 
	                   umap[ublk].jp, umap[ublk].kp);
            error += DBSetDir(SiloFile,"../");
         }
      }
      sewmeshes_wtmesh(x, y, z, ublk, umapm, Options, OutFile);
      FREEMEM(x);
      FREEMEM(y);
      FREEMEM(z);
      FREEMEM(node);
   }
   if (mdesc[nm].type == MESH_TRUEGRID) {
      if (trueGridFileCount > 0) endfile();
   } else if (mdesc[nm].type == MESH_SILO) {
      if (siloFileCount > 0) DBClose(SiloFile);
   } 
   error += DBFreeOptlist(Options);
   error += DBMkDir(OutFile, "/Global");
   sewmeshes_matchmesh(umapm);
   bndry_findcrn(umap, unblk);
   bndry_findcrn(umap, unblk);
   bndry_setgbnd();
   for (gblk = 0; gblk < gnblk; gblk++) {
     gmap[gblk].lblk = gblk;
   }
   error += DBMkDir(OutFile, "/Global/Decomposition");
   error += DBSetDir(OutFile, "/Global/Decomposition");
   decomp_write(OutFile, "domain");
   error += DBSetDir(OutFile, "/Global");
   NodeList_wtsilo(OutFile);
   Options = DBMakeOptlist( MAXOPTS );
   meshnames = (char **) calloc(gnblk, sizeof(char *));
   meshtypes = MALLOT(int,gnblk);
   for (gblk = 0; gblk < gnblk; gblk++) {
      meshnames[gblk] = MALLOT(char,100);
      sprintf(meshnames[gblk],"/domain%i/hydro_mesh",gblk);
      meshtypes[gblk] = DB_QUADMESH;
   }
   error += DBAddOption( Options, DBOPT_DTIME, &ttime );
   error += DBAddOption( Options, DBOPT_CYCLE, &cycle );
   error += DBSetDir(OutFile, "/");
   error += DBPutMultimesh(OutFile,"hydro_mesh", gnblk, meshnames,
                         meshtypes, Options);
   for (gblk = 0; gblk < gnblk; gblk++) {
      FREEMEM(meshnames[gblk]);
   }
   FREEMEM(meshnames);
   FREEMEM(meshtypes);
   error += DBFreeOptlist(Options);
   DBClose(OutFile);
   PRINT(stdout,"Mesh file %s has been created.\n",outname);
   for (ublk = 0; ublk < SEWMESH_MAX_UBLK; ublk++) {
      FREEMEM(umapm[ublk].bnd);
   }
   if (num_supblk == 0) unblk = SEWMESH_MAX_UBLK;
   for (ublk = 0; ublk < unblk; ublk++) {
      FREEMEM(umap[ublk].bnd);
   }
   for (ublk = 0; ublk < SEWMESH_MAX_GBLK; ublk++) {
      FREEMEM(gmap[ublk].bnd);
   }
   FREEMEM(gmap);
   FREEMEM(umap);
   FREEMEM(umapm);
   for (ublk = 0; ublk < num_supblk; ublk++) {
      NodeWindow_free(sblks[ublk].nlist);
      FREEMEM(sblks[ublk].map);
      FREEMEM(sblks[ublk].smap);
   }
   FREEMEM(sblks);
   FREEMEM(meshmap);
   FREEMEM(meshnum);
   FREEMEM(meshblk);
   return(error);
}
#endif


#ifdef SILO
static int sewmeshes_wtmesh(double *x, double *y, double *z, int ublk, 
                     SEWMESH_BLKBND *umapm,  DBoptlist *Options, 
                     DBfile *OutFile) 
{
   char outstr[MAXLINE];
   int gblk;
   int error;
   int ibnd;
   int ip;
   int jp;
   int kp;
   int i,n;
   Extents_t ext;
   Extents_t extred[27];
   error = 0;
   jp = umap[ublk].jp;
   kp = umap[ublk].kp;
   for (ibnd = 0; ibnd < umap[ublk].nbnd; ibnd++) {
      CPYEXT(ext,umap[ublk].bnd[ibnd]);
      n = extents_redext(extred,ext,CORNER);
      if (ndims == 2) {
         for (i = 0; i < n; i++) {
            ip = extred[i].imin + jp * extred[i].jmin;
            umapm[ublk].bnd[ibnd].x[i] = x[ip];
            umapm[ublk].bnd[ibnd].y[i] = y[ip];
            umapm[ublk].bnd[ibnd].z[i] = 0;
         }
      } else {
         for (i = 0; i < n; i++) {
            ip = extred[i].imin + jp * extred[i].jmin + kp * extred[i].kmin;
            umapm[ublk].bnd[ibnd].x[i] = x[ip];
            umapm[ublk].bnd[ibnd].y[i] = y[ip];
            umapm[ublk].bnd[ibnd].z[i] = z[ip];
         }
      } 
   }
   for (gblk = 0; gblk < gnblk; gblk++) {
      if (gmap[gblk].ublk == ublk) {
         sprintf(outstr,"/domain%i",gblk);
         error += DBMkDir(OutFile,outstr);
         error += DBSetDir(OutFile,outstr);
         CPYEXT(ext,gmap[gblk]);
         error += wtsilomesh(OutFile, Options, "hydro_mesh", x, y, z, ext, 
                             umap[ublk].jp, umap[ublk].kp);
      }
   }
   return(error);
}
#endif

#define SEW_EXTDIF(o,ext1,ext2) \
   if (ext1.imin > ext2.imin)  o[0] =  1; \
   if (ext1.imin == ext2.imin) o[0] =  0; \
   if (ext1.imin < ext2.imin)  o[0] = -1; \
   if (ext1.jmin > ext2.jmin)  o[1] =  1; \
   if (ext1.jmin == ext2.jmin) o[1] =  0; \
   if (ext1.jmin < ext2.jmin)  o[1] = -1; \
   if (ext1.kmin > ext2.kmin)  o[2] =  1; \
   if (ext1.kmin == ext2.kmin) o[2] =  0; \
   if (ext1.kmin < ext2.kmin)  o[2] = -1;
#define SEW_VECDOT(o1,o2) (o1[0]*o2[0] + o1[1]*o2[1] + o1[2]*o2[2])
#define SEW_FNDONE(i,o) \
   if (o[0] != 0) i = 0; \
   if (o[1] != 0) i = 1; \
   if (o[2] != 0) i = 2;
#define SEW_VECCPY(o1,o2) \
   o1[0] = o2[0]; \
   o1[1] = o2[1]; \
   o1[2] = o2[2];
static void sewmeshes_matchmesh(SEWMESH_BLKBND *umapm) 
{
   char *me = "sewmeshes_matchmesh";
   char msg[MAXLINE];
   int type;
   int ublk1;
   int ublk2;
   int ibnd1;
   int ibnd2;
   int nred1,nred2;
   int i,j, ip;
   int i1,i2;
   int n1,n2;
   int ordertmp;
   int sign;
   int *orient1;
   int *orient2;
   int v1[3], v2[3];
   int v3[3], v4[3];
   int t1[3], t2[3], t3[3];
   int u1[3], u2[3], u3[3];
   int order[16];
   int id1[16];
   int id2[16];
   double difftmp;
   double diff[16];
   double *x1,*x2;
   double *y1,*y2;
   double *z1,*z2;
   Extents_t ext1;
   Extents_t ext2;
   Extents_t ext1red[27];
   Extents_t ext2red[27];
   for (ublk1 = 0; ublk1 < unblk; ublk1++) {
      for (ibnd1 = 0; ibnd1 < umap[ublk1].nbnd; ibnd1++) {
         ublk2 = umap[ublk1].bnd[ibnd1].iblk;
         ibnd2 = umap[ublk1].bnd[ibnd1].id;
         if (ublk2 < ublk1) continue;
         CPYEXT(ext1,umap[ublk1].bnd[ibnd1]);
         CPYEXT(ext2,umap[ublk2].bnd[ibnd2]);
         type = extents_gettype(ext1);
         if (type != FACE) continue;
         nred1 = extents_redext(ext1red,ext1,CORNER);
         nred2 = extents_redext(ext2red,ext2,CORNER);
         if (nred1 != nred2) {
            sprintf(msg,"Attempting to match boundary between %i and %i with different logical dimensions\n",ublk1,ublk2);
            ctlerror(me,msg);
         }
         x1 = umapm[ublk1].bnd[ibnd1].x;
         y1 = umapm[ublk1].bnd[ibnd1].y;
         z1 = umapm[ublk1].bnd[ibnd1].z;
         x2 = umapm[ublk2].bnd[ibnd2].x;
         y2 = umapm[ublk2].bnd[ibnd2].y;
         z2 = umapm[ublk2].bnd[ibnd2].z;
         ip = 0;
         if (ndims == 2) {
            for (j = 0; j < nred1; j++) {
               for (i = 0; i < nred1; i++) {
                  diff[ip] = (x1[i] - x2[j]) * (x1[i] - x2[j]) +
                             (y1[i] - y2[j]) * (y1[i] - y2[j]);
                  order[ip] = ip;
                  id1[ip] = i;
                  id2[ip] = j;
                  ip++;
               }
            }
         } else {
            for (j = 0; j < nred1; j++) {
               for (i = 0; i < nred1; i++) {
                  diff[ip] = (x1[i] - x2[j]) * (x1[i] - x2[j]) +
                             (y1[i] - y2[j]) * (y1[i] - y2[j]) +
                             (z1[i] - z2[j]) * (z1[i] - z2[j]);
                  order[ip] = ip;
                  id1[ip] = i;
                  id2[ip] = j;
                  ip++;
               }
            }
         } 
         for (i = 0; i < ip - 1; i++) {
            for (j = ip - 1; j > i; j--) {
               if (diff[i] > diff[j]) {
                  difftmp  = diff[j];
                  ordertmp = order[j];
                  diff[j]  = diff[i];
                  order[j] = order[i];
                  diff[i]  = difftmp;
                  order[i] = ordertmp;
               }
            }
         }
	 orient1 = umap[ublk1].bnd[ibnd1].orientation;
	 orient2 = umap[ublk2].bnd[ibnd2].orientation;
	 if (ndims == 2) {
            n1 = id1[order[0]];
            n2 = id1[order[1]];
	    SEW_EXTDIF(v1,ext1red[n1],ext1red[n2]);
            n1 = id2[order[0]];
            n2 = id2[order[1]];
	    SEW_EXTDIF(v2,ext2red[n1],ext2red[n2]);
	    orient1[2] = 3;
	    orient2[2] = 3;
	    SEW_FNDONE(i1,v1);
	    SEW_FNDONE(i2,v2);
	    sign = 1;
	    if (v1[i1]*v2[i2] < 0) sign = -1;
	    orient1[i2] = sign*(i1 + 1);
	    orient2[i1] = sign*(i2 + 1);
	 } else {
            n1 = id1[order[0]];
            n2 = id1[order[1]];
	    SEW_EXTDIF(t1,ext1red[n1],ext1red[n2]);
            n1 = id1[order[0]];
            n2 = id1[order[2]];
	    SEW_EXTDIF(t2,ext1red[n1],ext1red[n2]);
            n1 = id1[order[0]];
            n2 = id1[order[3]];
	    SEW_EXTDIF(t3,ext1red[n1],ext1red[n2]);
            n1 = id2[order[0]];
            n2 = id2[order[1]];
	    SEW_EXTDIF(u1,ext2red[n1],ext2red[n2]);
            n1 = id2[order[0]];
            n2 = id2[order[2]];
	    SEW_EXTDIF(u2,ext2red[n1],ext2red[n2]);
            n1 = id2[order[0]];
            n2 = id2[order[3]];
	    SEW_EXTDIF(u3,ext2red[n1],ext2red[n2]);
	    if (SEW_VECDOT(t1,t1) == 1) {
	       SEW_VECCPY(v1,t1);
	       SEW_VECCPY(v3,u1);
	    }
	    if (SEW_VECDOT(t2,t2) == 1) {
	       SEW_VECCPY(v1,t2);
	       SEW_VECCPY(v3,u2);
	    }
	    if (SEW_VECDOT(t3,t3) == 1) {
	       SEW_VECCPY(v1,t3);
	       SEW_VECCPY(v3,u3);
	    }
	    if (SEW_VECDOT(v1,t1) == 0) {
	       SEW_VECCPY(v2,t1);
	       SEW_VECCPY(v4,u1);
	    }
	    if (SEW_VECDOT(v1,t2) == 0) {
	       SEW_VECCPY(v2,t2);
	       SEW_VECCPY(v4,u2);
	    }
	    if (SEW_VECDOT(v1,t3) == 0) {
	       SEW_VECCPY(v2,t3);
	       SEW_VECCPY(v4,u3);
	    }
	    SEW_FNDONE(i1,v1);
	    SEW_FNDONE(i2,v3);
	    sign = 1;
	    if (v1[i1]*v3[i2] < 0) sign = -1;
	    orient1[i2] = sign*(i1 + 1);
	    orient2[i1] = sign*(i2 + 1);
	    SEW_FNDONE(i1,v2);
	    SEW_FNDONE(i2,v4);
	    sign = 1;
	    if (v2[i1]*v4[i2] < 0) sign = -1;
	    orient1[i2] = sign*(i1 + 1);
	    orient2[i1] = sign*(i2 + 1);
         } 
	 if ((ext1.imin == ext1.imax) && 
	     (ext1.imin == umap[ublk1].imin)) n1 = -1;
	 if ((ext1.imin == ext1.imax) && 
	     (ext1.imin == umap[ublk1].imax)) n1 = 1;
	 if ((ext1.jmin == ext1.jmax) && 
	     (ext1.jmin == umap[ublk1].jmin)) n1 = -2;
	 if ((ext1.jmin == ext1.jmax) && 
	     (ext1.jmin == umap[ublk1].jmax)) n1 = 2;
	 if (ndims == 3) {
	    if ((ext1.kmin == ext1.kmax) && 
	        (ext1.kmin == umap[ublk1].kmin)) n1 = -3;
	    if ((ext1.kmin == ext1.kmax) && 
	        (ext1.kmin == umap[ublk1].kmax)) n1 = 3;
	 }
	 if ((ext2.imin == ext2.imax) && 
	     (ext2.imin == umap[ublk2].imin)) n2 = -1;
	 if ((ext2.imin == ext2.imax) && 
	     (ext2.imin == umap[ublk2].imax)) n2 = 1;
	 if ((ext2.jmin == ext2.jmax) && 
	     (ext2.jmin == umap[ublk2].jmin)) n2 = -2;
	 if ((ext2.jmin == ext2.jmax) && 
	     (ext2.jmin == umap[ublk2].jmax)) n2 = 2;
	 if (ndims == 3) {
	    if ((ext2.kmin == ext2.kmax) && 
	        (ext2.kmin == umap[ublk2].kmin)) n2 = -3;
	    if ((ext2.kmin == ext2.kmax) && 
	        (ext2.kmin == umap[ublk2].kmax)) n2 = 3;
	 }
	 sign = 1;
	 if ((n1 * n2) > 0) sign = -1;
	 orient1[abs(n2) - 1] = sign * abs(n1);
	 orient2[abs(n1) - 1] = sign * abs(n2);
      }
   }
}
#undef SEW_EXTDIF
#undef SEW_VECDOT
#undef SEW_FNDONE
#undef SEW_VECCPY
static int sewmeshes_consolidate(SUPER_BLK *sblk, int id) {
   char name[MAXLINE];
   char op[MAXLINE];
   int error;
   int iblk;
   NodeWindow_t *ndxptr;
   sblk->nlist = NULL;
   sblk->nsblk = 0;
   sblk->id    = id;
   sprintf(name,"consolidate");
   error = NodeWindow_read(name,&sblk->nlist);
   if (error != 0) return(-1);
   ndxptr = sblk->nlist;
   while (ndxptr != NULL) {
      sblk->nsblk++;
      ndxptr = ndxptr->next;
   }
   sblk->smap = MALLOT(BlockMapping_t,sblk->nsblk);
   sblk->map  = MALLOT(int,unblk);
   for (iblk = 0; iblk < unblk; iblk++) {
      sblk->map[iblk] = -1;
   }
   iblk = 0;
   ndxptr = sblk->nlist;
   while (ndxptr != NULL) {
      sblk->smap[iblk].ublk = ndxptr->ublk;
      sblk->map[sblk->smap[iblk].ublk] = iblk;
      iblk++;
      ndxptr = ndxptr->next;
   }
   return(0);
}
static void sewmeshes_determine_size(SUPER_BLK *sblk) {
   char *me = "determine_size";
   char msg[MAXLINE];
   int iblk;
   int ublk;
   int ublk2;
   int nbnd;
   int ibnd;
   int ibnd2;
   int type;
   int zones;
   int nsblk;
   BlockMapping_t *smap;
   Extents_t ext;
   Extents_t *subext;
   Extents_t supext;
   iblk = 0;
   nsblk = sblk->nsblk;
   smap  = sblk->smap;
   ublk = smap[0].ublk;
   CPYEXT(supext,umap[ublk]);
   for (iblk = 0; iblk < nsblk; iblk++) {
      ublk = smap[iblk].ublk;
      smap[iblk].imin = sewmeshes_getnodes(ublk,1,sblk);
      smap[iblk].jmin = sewmeshes_getnodes(ublk,2,sblk);
      if (ndims == 3) {
         smap[iblk].kmin = sewmeshes_getnodes(ublk,3,sblk);
      } else {
         smap[iblk].kmin = 0;
      } 
      smap[iblk].imax = smap[iblk].imin + umap[ublk].imax - umap[ublk].imin;
      smap[iblk].jmax = smap[iblk].jmin + umap[ublk].jmax - umap[ublk].jmin;
      if (ndims == 3) {
         smap[iblk].kmax = smap[iblk].kmin + umap[ublk].kmax - umap[ublk].kmin;
      } else {
         smap[iblk].kmax = 0;
      } 
      supext.imax = MAX(smap[iblk].imax,supext.imax);
      supext.jmax = MAX(smap[iblk].jmax,supext.jmax);
      supext.kmax = MAX(smap[iblk].kmax,supext.kmax);
   }
   subext = MALLOT(Extents_t,nsblk);
   for (iblk = 0; iblk < nsblk; iblk++) {
      CPYEXT(subext[iblk],smap[iblk]);
   }
   type = extents_aggregate(subext,nsblk,supext,1);
   FREEMEM(subext);
   if (type != 0) {
      sprintf(msg,"Error trying to consolidate blocks (%i ... %i).\n\tThis could be caused by TrueGrid not properly merging boundaries\n\tor the blocks you are trying to consolidate are not fully connected.",
                 smap[0].ublk,smap[nsblk -1].ublk);
      ctlerror(me,msg);
   }
   CPYEXT(sblk->ext,supext);
   for (iblk = 0; iblk < nsblk; iblk++) {
      ublk = smap[iblk].ublk;
      nbnd = 0;
      for (ibnd = 0; ibnd < umap[ublk].nbnd; ibnd++) {
         ublk2 = umap[ublk].bnd[ibnd].iblk;
         ibnd2 = umap[ublk].bnd[ibnd].id;
         if (ublk2 == -1) continue;
         CPYEXT(ext,umap[ublk].bnd[ibnd]);
         type = extents_gettype(ext);
         if (type != FACE) {
            umap[ublk2].bnd[ibnd2].iblk = -1;
            continue;
         }
         if (sblk->map[ublk2] < 0) {
            CPYEXT(umap[ublk].bnd[nbnd],umap[ublk].bnd[ibnd]);
            umap[ublk].bnd[nbnd].iblk = umap[ublk].bnd[ibnd].iblk;
            umap[ublk].bnd[nbnd].id = umap[ublk].bnd[ibnd].id;
            umap[ublk].bnd[nbnd].imin += smap[iblk].imin - NPNL;
            umap[ublk].bnd[nbnd].imax += smap[iblk].imin - NPNL;
            umap[ublk].bnd[nbnd].jmin += smap[iblk].jmin - NPNL;
            umap[ublk].bnd[nbnd].jmax += smap[iblk].jmin - NPNL;
	    if (ndims == 3) {
               umap[ublk].bnd[nbnd].kmin += smap[iblk].kmin - NPNL;
               umap[ublk].bnd[nbnd].kmax += smap[iblk].kmin - NPNL;
	    }
            umap[ublk].bnd[nbnd].orientation[0] = umap[ublk].bnd[ibnd].orientation[0];
            umap[ublk].bnd[nbnd].orientation[1] = umap[ublk].bnd[ibnd].orientation[1];
            umap[ublk].bnd[nbnd].orientation[2] = umap[ublk].bnd[ibnd].orientation[2];
            umap[ublk2].bnd[ibnd2].id = nbnd;
            umap[ublk2].bnd[ibnd2].iblk = ublk;
            nbnd++;
         } 
      }
      umap[ublk].nbnd = nbnd;
   }
}
static int sewmeshes_getnodes(int ublk, int dir, SUPER_BLK *sblk) {
   char *me = "sewmeshes_getnodes";
   char msg[128];
   int ibnd;
   int nodes;
   int type;
   int ublk2;
   Extents_t ext;
   nodes = 0;
   for (ibnd = 0; ibnd < umap[ublk].nbnd; ibnd++) {
      ublk2 = umap[ublk].bnd[ibnd].iblk;
      if ( sblk->map[ublk2] < 0 ) continue;
      CPYEXT(ext,umap[ublk].bnd[ibnd]);
      type = extents_gettype(ext);
      if ((type == FACE) && (dir == 1) && (ext.imin == ext.imax) && 
                                          (ext.imin == umap[ublk].imin)) {
         break;
      }
      if ((type == FACE) && (dir == 2) && (ext.jmin == ext.jmax) && 
                                          (ext.jmin == umap[ublk].jmin)) {
         break;
      }
      if ((type == FACE) && (dir == 3) && (ext.kmin == ext.kmax) && 
                                          (ext.kmin == umap[ublk].kmin)) {
         break;
      }
   }
   if (ibnd != umap[ublk].nbnd) {
      if ((umap[ublk].bnd[ibnd].orientation[0] != 1) ||
          (umap[ublk].bnd[ibnd].orientation[1] != 2) ||
          (umap[ublk].bnd[ibnd].orientation[2] != 3)) {
         sprintf(msg, "There has been an attempt to merge blocks with different orientation in super-block %i",sblk->id);
         ctlerror(me,msg);
      }
   }
   if (dir == 1) {
      if (ibnd == umap[ublk].nbnd) return(umap[ublk].imin);
      nodes = sewmeshes_getnodes(ublk2,1,sblk);
      nodes += umap[ublk2].imax - umap[ublk2].imin ;
   }
   if (dir == 2) {
      if (ibnd == umap[ublk].nbnd) return(umap[ublk].jmin);
      nodes = sewmeshes_getnodes(ublk2,2,sblk);
      nodes += umap[ublk2].jmax - umap[ublk2].jmin;
   }
   if (dir == 3) {
      if (ibnd == umap[ublk].nbnd) return(umap[ublk].kmin);
      nodes = sewmeshes_getnodes(ublk2,3,sblk);
      nodes += umap[ublk2].kmax - umap[ublk2].kmin ;
   }
   return(nodes);
}
static void sewmeshes_merge_NodeLists( SUPER_BLK *sblk )
{
   char msg[MAXLINE];
   int i,j;
   int ublk;
   int iblk;
   int error;
   int ifcon;
   int num_lists;
   int *map;
   char **list;
   BlockMapping_t *smap;
   NodeWindow_t *ndxptr;
   NodeWindow_t *ndxptr_tmp;
   NodeList_t *NodeList;
   Extents_t supext;
   Extents_t *subext;
   int nsubext;
   map  = sblk->map;
   smap = sblk->smap;
   list = rgst_list_objs_by_type(&num_lists,"NodeList_t");
   for (i = 0; i < num_lists; i++) {
      nsubext = 0;
      NodeList = (NodeList_t *)rgst_get_t(list[i],"NodeList_t");
      ndxptr  = NodeList->list;
      while (ndxptr != NULL) {
         ublk = ndxptr->ublk;
         if (map[ublk] >= 0) {
            iblk = map[ublk];
            nsubext++;
            ndxptr->in[0][0] += smap[iblk].imin - NPNL;
            ndxptr->in[0][1] += smap[iblk].imin - NPNL;
            ndxptr->in[1][0] += smap[iblk].jmin - NPNL;
            ndxptr->in[1][1] += smap[iblk].jmin - NPNL;
            ndxptr->imin += smap[iblk].imin - NPNL;
            ndxptr->imax += smap[iblk].imin - NPNL;
            ndxptr->jmin += smap[iblk].jmin - NPNL;
            ndxptr->jmax += smap[iblk].jmin - NPNL;
            if (ndims == 3) {
               ndxptr->kmin += smap[iblk].kmin - NPNL;
               ndxptr->kmax += smap[iblk].kmin - NPNL;
               ndxptr->in[2][0] += smap[iblk].kmin - NPNL;
               ndxptr->in[2][1] += smap[iblk].kmin - NPNL;
            }
         }
         ndxptr = ndxptr->next;
      }
      FREEMEM(list[i]);
      if (nsubext == 0) continue;
      ndxptr = NodeList->list;
      subext = MALLOT(Extents_t,nsubext);
      supext.imin = sblk->ext.imax;
      supext.imax = sblk->ext.imin;
      supext.jmin = sblk->ext.jmax;
      supext.jmax = sblk->ext.jmin;
      supext.kmin = sblk->ext.kmax;
      supext.kmax = sblk->ext.kmin;
      j = 0;
      while (ndxptr != NULL) {
         ublk = ndxptr->ublk;
         if (map[ublk] >= 0) {
            CPYEXT(subext[j],(*ndxptr));
            supext.imin = MIN(supext.imin,subext[j].imin);
            supext.imax = MAX(supext.imax,subext[j].imax);
            supext.jmin = MIN(supext.jmin,subext[j].jmin);
            supext.jmax = MAX(supext.jmax,subext[j].jmax);
            if (ndims == 3) {
               supext.kmin = MIN(supext.kmin,subext[j].kmin);
               supext.kmax = MAX(supext.kmax,subext[j].kmax);
            }
            j++;
         }
         ndxptr = ndxptr->next;
      }
      error = extents_aggregate(subext,nsubext,supext,0);
      if (error != 0) {
         sprintf(msg,"Nodelist %s cannot be consolidated.",NodeList->name);
         ctlmsg(msg);
         FREEMEM(subext);
         continue;
      } 
      ndxptr = NodeList->list;
      ndxptr_tmp = NodeList->list;
      ifcon = 0;
      while (ndxptr != NULL) {
         ublk = ndxptr->ublk;
         if (map[ublk] >= 0) {
            if (ifcon == 0) {
               ifcon = 1;
               if (ndxptr->in[0][0] == ndxptr->imin) ndxptr->in[0][0] = supext.imin;
               if (ndxptr->in[1][0] == ndxptr->jmin) ndxptr->in[1][0] = supext.jmin;
               if (ndxptr->in[2][0] == ndxptr->kmin) ndxptr->in[2][0] = supext.kmin;
               if (ndxptr->in[0][1] == ndxptr->imin) ndxptr->in[0][1] = supext.imin;
               if (ndxptr->in[1][1] == ndxptr->jmin) ndxptr->in[1][1] = supext.jmin;
               if (ndxptr->in[2][1] == ndxptr->kmin) ndxptr->in[2][1] = supext.kmin;
               if (ndxptr->in[0][1] == ndxptr->imax) ndxptr->in[0][1] = supext.imax;
               if (ndxptr->in[1][1] == ndxptr->jmax) ndxptr->in[1][1] = supext.jmax;
               if (ndxptr->in[2][1] == ndxptr->kmax) ndxptr->in[2][1] = supext.kmax;
               if (ndxptr->in[0][0] == ndxptr->imax) ndxptr->in[0][0] = supext.imax;
               if (ndxptr->in[1][0] == ndxptr->jmax) ndxptr->in[1][0] = supext.jmax;
               if (ndxptr->in[2][0] == ndxptr->kmax) ndxptr->in[2][0] = supext.kmax;
               CPYEXT((*ndxptr),supext);
               ndxptr_tmp = ndxptr;
               ndxptr = ndxptr->next;
            } else {
               ndxptr_tmp->next = ndxptr->next;
               FREEMEM(ndxptr);
               ndxptr = ndxptr_tmp->next;
            } 
         } else {
            ndxptr_tmp = ndxptr;
            ndxptr = ndxptr->next;
         } 
      }
      FREEMEM(subext);
   }
   FREEMEM(list);
}
static void sewmeshes_pack_bnds(SUPER_BLK *sblk ) {
   int iblk;
   int ublk;
   int ublk0;
   int ublk2;
   int ns;
   int ibnd;
   int ibnd2;
   int nbnd;
   ublk0 = sblk->smap[0].ublk;
   nbnd = 0;
   for (iblk = 0; iblk < sblk->nsblk; iblk++) {
      ublk = sblk->smap[iblk].ublk;
      nbnd += umap[ublk].nbnd;
   }
   umap[ublk0].bnd = REALLOT(umap[ublk0].bnd,BndMapping_t,nbnd);
   nbnd = umap[ublk0].nbnd;
   for (iblk = 1; iblk < sblk->nsblk; iblk++) {
      ublk = sblk->smap[iblk].ublk;
      for (ibnd = 0; ibnd < umap[ublk].nbnd; ibnd++) {
         if (umap[ublk0].bnd[ibnd].iblk < 0) continue;
         CPYEXT(umap[ublk0].bnd[nbnd],umap[ublk].bnd[ibnd]);
         umap[ublk0].bnd[nbnd].iblk = umap[ublk].bnd[ibnd].iblk;
         umap[ublk0].bnd[nbnd].id = umap[ublk].bnd[ibnd].id;
         umap[ublk0].bnd[nbnd].orientation[0] = umap[ublk].bnd[ibnd].orientation[0];
         umap[ublk0].bnd[nbnd].orientation[1] = umap[ublk].bnd[ibnd].orientation[1];
         umap[ublk0].bnd[nbnd].orientation[2] = umap[ublk].bnd[ibnd].orientation[2];
         ublk2 = umap[ublk].bnd[ibnd].iblk;
         ibnd2 = umap[ublk].bnd[ibnd].id;
         umap[ublk2].bnd[ibnd2].iblk = ublk0;
         umap[ublk2].bnd[ibnd2].id = nbnd;
         nbnd++;
      }
      FREEMEM(umap[ublk].bnd);
      umap[ublk].nbnd = 0;
   }
   umap[ublk0].nbnd = nbnd;
}
static void sewmeshes_merge_ublks(int *map, BlockMapping_t *newumap) {
   char *me = "sewmeshes_merge_ublks";
   char msg[MAXLINE];
   int ublk;
   int u1;
   int u2;
   int ublk_new;
   int ublk1;
   int ublk2;
   int ibnd;
   int nbnd1;
   int nbnd2;
   int ibnd1;
   int ibnd2;
   int error;
   int nsubext;
   int orient1[3];
   int orient2[3];
   int *tag1;
   int *tag2;
   Extents_t supext1;
   Extents_t supext2;
   Extents_t *subext1;
   Extents_t *subext2;
   for (ublk = 0; ublk < unblk; ublk++) {
      ublk_new = map[ublk];
      if (ublk_new >= 0) {
         CPYEXT(newumap[ublk_new],umap[ublk]);
         newumap[ublk_new].ublk = ublk_new;
         newumap[ublk_new].jp = umap[ublk].jp;
         newumap[ublk_new].kp = umap[ublk].kp;
         newumap[ublk_new].nbnd = 0;
      }
   }
   for (u1 = 0; u1 < unblk - 1; u1++) {
      if (map[u1] < 0) continue;
      ublk1   = map[u1];
      subext1 = MALLOT(Extents_t,umap[u1].nbnd);
      subext2 = MALLOT(Extents_t,umap[u1].nbnd);
      tag1    = MALLOT(int,umap[u1].nbnd);
      tag2    = MALLOT(int,umap[u1].nbnd);
      for (u2 = u1; u2 < unblk; u2++) {
         if (map[u2] < 0) continue;
         ublk2   = map[u2];
         supext1.imin = umap[u1].imax;
         supext1.imax = umap[u1].imin;
         supext1.jmin = umap[u1].jmax;
         supext1.jmax = umap[u1].jmin;
         supext1.kmin = umap[u1].kmax;
         supext1.kmax = umap[u1].kmin;
         supext2.imin = umap[u2].imax;
         supext2.imax = umap[u2].imin;
         supext2.jmin = umap[u2].jmax;
         supext2.jmax = umap[u2].jmin;
         supext2.kmin = umap[u2].kmax;
         supext2.kmax = umap[u2].kmin;
         nsubext = 0;
         for (ibnd = 0; ibnd < umap[u1].nbnd; ibnd++) {
            if (umap[u1].bnd[ibnd].iblk == u2) {
               CPYEXT(subext1[nsubext],umap[u1].bnd[ibnd]);
               supext1.imin = MIN(supext1.imin,subext1[nsubext].imin);
               supext1.imax = MAX(supext1.imax,subext1[nsubext].imax);
               supext1.jmin = MIN(supext1.jmin,subext1[nsubext].jmin);
               supext1.jmax = MAX(supext1.jmax,subext1[nsubext].jmax);
               if (ndims == 3) {
                  supext1.kmin = MIN(supext1.kmin,subext1[nsubext].kmin);
                  supext1.kmax = MAX(supext1.kmax,subext1[nsubext].kmax);
               }
               tag1[nsubext] = ibnd;
               if (nsubext == 0) {
                  orient1[0] = umap[u1].bnd[ibnd].orientation[0];
                  orient1[1] = umap[u1].bnd[ibnd].orientation[1];
                  orient1[2] = umap[u1].bnd[ibnd].orientation[2];
               } else {
                  if( (orient1[0] != umap[u1].bnd[ibnd].orientation[0] ) ||
                      (orient1[1] != umap[u1].bnd[ibnd].orientation[1] ) ||
                      (orient1[2] != umap[u1].bnd[ibnd].orientation[2] )) {
                     sprintf(msg,"Orientation error while trying to merge blocks %i and %i.",u1,u2);
                     ctlerror(me,msg);
                  }
               } 
               ibnd2 = umap[u1].bnd[ibnd].id;
               CPYEXT(subext2[nsubext],umap[u2].bnd[ibnd2]);
               supext2.imin = MIN(supext2.imin,subext2[nsubext].imin);
               supext2.imax = MAX(supext2.imax,subext2[nsubext].imax);
               supext2.jmin = MIN(supext2.jmin,subext2[nsubext].jmin);
               supext2.jmax = MAX(supext2.jmax,subext2[nsubext].jmax);
               if (ndims == 3) {
                  supext2.kmin = MIN(supext2.kmin,subext2[nsubext].kmin);
                  supext2.kmax = MAX(supext2.kmax,subext2[nsubext].kmax);
               }
               tag2[nsubext] = ibnd2;
               if (nsubext == 0) {
                  orient2[0] = umap[u2].bnd[ibnd2].orientation[0];
                  orient2[1] = umap[u2].bnd[ibnd2].orientation[1];
                  orient2[2] = umap[u2].bnd[ibnd2].orientation[2];
               } else {
                  if( (orient2[0] != umap[u2].bnd[ibnd2].orientation[0] ) ||
                      (orient2[1] != umap[u2].bnd[ibnd2].orientation[1] ) ||
                      (orient2[2] != umap[u2].bnd[ibnd2].orientation[2] )) {
                     sprintf(msg,"Orientation error while trying to merge blocks %i and %i.",u1,u2);
                     ctlerror(me,msg);
                  }
               } 
               nsubext++;
            }
         }
         if (nsubext > 0) {
            error = extents_aggregate(subext1,nsubext,supext1,1);
            if (error != 0) {
               sprintf(msg,"Error trying to merge collective boundaries between %i and %i.",u1,u2);
               ctlerror(me,msg);
            }
            error = extents_aggregate(subext2,nsubext,supext2,1);
            if (error != 0) {
               sprintf(msg,"Error trying to merge collective boundaries between %i and %i.",u1,u2);
               ctlerror(me,msg);
            }
            nbnd1 = newumap[ublk1].nbnd;
            nbnd2 = newumap[ublk2].nbnd;
            if (ublk2 == ublk1) {
               nbnd2 = nbnd1 + 1;
            }
            CPYEXT(newumap[ublk1].bnd[nbnd1],supext1);
            CPYEXT(newumap[ublk2].bnd[nbnd2],supext2);
            newumap[ublk1].bnd[nbnd1].iblk = ublk2;
            newumap[ublk2].bnd[nbnd2].iblk = ublk1;
            ibnd1 = tag1[0]; 
            newumap[ublk1].bnd[nbnd1].orientation[0] = umap[u1].bnd[ibnd1].orientation[0];
            newumap[ublk1].bnd[nbnd1].orientation[1] = umap[u1].bnd[ibnd1].orientation[1];
            newumap[ublk1].bnd[nbnd1].orientation[2] = umap[u1].bnd[ibnd1].orientation[2];
            ibnd2 = tag2[0]; 
            newumap[ublk2].bnd[nbnd2].orientation[0] = umap[u2].bnd[ibnd2].orientation[0];
            newumap[ublk2].bnd[nbnd2].orientation[1] = umap[u2].bnd[ibnd2].orientation[1];
            newumap[ublk2].bnd[nbnd2].orientation[2] = umap[u2].bnd[ibnd2].orientation[2];
            newumap[ublk1].bnd[nbnd1].id = nbnd2;
            newumap[ublk2].bnd[nbnd2].id = nbnd1;
            newumap[ublk1].nbnd++;
            newumap[ublk2].nbnd++;
         }
      }
      FREEMEM(subext1);
      FREEMEM(subext2);
      FREEMEM(tag1);
      FREEMEM(tag2);
   }
}
static void sewmeshes_NodeList_update( int *meshmap )
{
   char msg[MAXLINE];
   int i;
   int ublk;
   int num_lists;
   char **list;
   NodeWindow_t *ndxptr;
   NodeList_t *NodeList;
   list = rgst_list_objs_by_type(&num_lists,"NodeList_t");
   for (i = 0; i < num_lists; i++) {
      NodeList = (NodeList_t *)rgst_get_t(list[i],"NodeList_t");
      ndxptr  = NodeList->list;
      while (ndxptr != NULL) {
         ublk = ndxptr->ublk;
         ndxptr->ublk = meshmap[ublk];
         ndxptr = ndxptr->next;
      }
      FREEMEM(list[i]);
   }
   FREEMEM(list);
}

#ifdef SILO
static void sewmeshes_siloize_tg(char *name, int num_block, int num, int ustart) {
   char outstr[MAXLINE];	 
   int i;
   int ublk;
   int iblk;
   int len;
   int error;
   int junki;
   int *node;
   double *x, *y, *z;
   Extents_t ext;
   DBfile *SiloFile;
   error = newfile(name,1);
   newline();
   nxtsym(1);
   sprintf(name,"sewmesh_tg%i.silo",num);
   SiloFile = DBCreate(name, DB_CLOBBER, DB_LOCAL, NULL, DB_PDB );
   error = rdtruegrid_decomp(umap, -1, 0, &junki);
   for (iblk = 0; iblk < num_block; iblk++) {
      ublk = ustart + iblk;
      CPYEXT(ext,umap[ublk]);
      if (ndims == 2) {
         len = (ext.imax + NPNR + 1)*(ext.jmax + NPNR + 1);
      } else {
         len = (ext.imax + NPNR + 1)*(ext.jmax + NPNR + 1)*
                             (ext.kmax + NPNR + 1);
      }
      x = MALLOT(double,len);       
      y = MALLOT(double,len);       
      z = MALLOT(double,len);       
      node = MALLOT(int,len);       
      rdtruegrid_mesh(x, y, z, node, ext, umap[ublk].jp, umap[ublk].kp);
      sprintf(outstr,"/domain%i",iblk);
      error += DBMkDir(SiloFile,outstr);
      error += DBSetDir(SiloFile,outstr);
      error += wtsilomesh(SiloFile, NULL, "hydro_mesh", x, y, z, ext, 
                                 umap[ublk].jp, umap[ublk].kp);
      FREEMEM(x);
      FREEMEM(y);
      FREEMEM(z);
      FREEMEM(node);
   }
   DBClose(SiloFile);
   endfile();
}
#endif
