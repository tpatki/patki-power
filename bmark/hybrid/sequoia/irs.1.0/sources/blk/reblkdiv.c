#include "irs.h"
#include "irsblk.h"
#include "irscom.h"
#include "irsdmp.h"
#include "irsgen.h"
#include "irsrgst.h"
#include "BlockMapping.h"
#include "Extents.h"
#include "NodeList.h"
int reblkdiv( void ) {

   char *me = "reblkdiv";
   char msg[MAXLINE];
   char tmp[MAXLINE];
   char *cptr;
   char **varlist;
   int i;
   int iblk, gblk, gblk2;
   int ublk;
   int gnblk_save;
   int ifroot;
   int len;
   int imaxmix;
   int num_vars;
   int error = 0;

#ifdef SILO
   int my_nblk;
   int *domainFiles;
   int *domainRead;
   Extents_t ext, ext1, ext2,ext3,exta,extb;
   BlockMapping_t *gmap_save;
   Domain_t *domain_tmp;
   DBfile *idbid;
   DBmultimesh *multiMesh;
   error = 0;
   Restart_write(0);
   if (ifparallel) combarrier();
   for (iblk = 0; iblk < nblk; iblk++) {
      domain_free(&domains[iblk]);
   }
   nblk = 0;
   regen_pregen();
   domainFiles = MALLOT(int, gnblk);
   domainRead  = MALLOT(int, gnblk);
   gmap_save   = MALLOT(BlockMapping_t, gnblk);
   for (gblk = 0; gblk < gnblk; gblk++) {
      CPYEXT(gmap_save[gblk],gmap[gblk]);
      gmap_save[gblk].lblk = gmap[gblk].lblk;
      gmap_save[gblk].ublk = gmap[gblk].ublk;
      gmap_save[gblk].gblk = gmap[gblk].gblk;
      gmap_save[gblk].proc = gmap[gblk].proc;
      gmap_save[gblk].jp   = gmap[gblk].jp;
      gmap_save[gblk].kp   = gmap[gblk].kp;
      gmap[gblk].nbnd      = -1;
      FREEMEM(gmap[gblk].bnd);
   }
   gnblk_save = gnblk;
   gnblk      = 0;
   for (ublk = 0; ublk < unblk; ublk++) {
      CPYEXT(ext,umap[ublk]);
      setgmap(ublk, ext);
   }
   blkdivin(0);
   calculate_mappings();
   for (gblk2 = 0; gblk2 < gnblk_save; gblk2++) {
      domainRead[gblk2] = -1;
      CPYEXT(ext2,gmap_save[gblk2]);
      for (gblk = 0; gblk < gnblk; gblk++) {
         if (gmap[gblk].proc != myid) continue;
         if (gmap[gblk].ublk != gmap_save[gblk2].ublk) continue;
         CPYEXT(ext1,gmap[gblk]);
         len = extents_overlap(&ext1,&ext2,&ext3);
         if (len == 0) continue;
         if (ndims == 2) {
            len = (ext3.imax - ext3.imin) * (ext3.jmax - ext3.jmin);
         } else {
            len = (ext3.imax - ext3.imin) * (ext3.jmax - ext3.jmin) *
                  (ext3.kmax - ext3.kmin);
         } 
         if (len > 0) {
            domainRead[gblk2] = 1;
         }
      }
   }
   if ((ifparallel) || (multi_dump_write > 1)) {
      ifroot = 1;
      sprintf(tmp,"%s%s%05d.root",outpath,pbnm,cycle);
      idbid = DBOpen(tmp, DB_PDB, DB_READ);
   } else {
      ifroot = 0;
      sprintf(tmp,"%s%s%05d.silo",outpath,pbnm,cycle);
      idbid = DBOpen(tmp, DB_PDB, DB_READ);
   }
   if (idbid == NULL) {
      sprintf(msg,"Cannot open file %s",tmp);
      ctlerror(me,msg);
   }
   multiMesh = DBGetMultimesh(idbid, "hydro_mesh");
   if (ifroot) {
      error += DBReadVar(idbid, "DomainFiles", domainFiles);
      DBClose(idbid);
   } else {
      for (gblk = 0; gblk < gnblk_save; gblk++) {
         domainFiles[gblk] = gblk;
      }
   } 
   my_nblk = 0;
   for (gblk = 0; gblk < gnblk; gblk++) {
      if (gmap[gblk].proc == myid) {
         domains[my_nblk].sclnamix = sclnamix;
         if (ndims == 3) domains[my_nblk].type     = HEX3D;
         if (ndims == 2) domains[my_nblk].type     = QUAD2D;
         TRSEXT(domains[my_nblk],gmap[gblk],gmap[gblk]);
         if (ndims == 2) {
             domains[my_nblk].kmin = 0;
             domains[my_nblk].kmax = 0;
         }
         initblk(my_nblk,&domains[my_nblk]);
         domains[my_nblk].gblk = gblk;
         domain_hash_tbl_rgst(&(domains[my_nblk]));    
         my_nblk++;
      }
   }
   nblk = my_nblk;
   regen_reset();
   dmpattr_set();
   for (gblk2 = 0; gblk2 < gnblk_save; gblk2++) {
      if (domainRead[gblk2] == -1) continue;
      CPYEXT(ext2,gmap_save[gblk2]);
      if (ifroot) {
         strcpy(tmp,multiMesh->meshnames[gblk2]);
         cptr = strtok(tmp,":");
         idbid = DBOpen(cptr, DB_PDB, DB_READ);
      } 
      sprintf(tmp,"/domain%i",domainFiles[gblk2]);
      if (DBSetDir(idbid, tmp) != 0) ctlerror(me,gv_errmsg_DBSetDir);
      domain_tmp = Domain_construct(1);
      rgst_read_struct(idbid, "Domain_t", domain_tmp, NULL);
      for (iblk = 0; iblk < nblk; iblk++) {
         gblk = domains[iblk].gblk;
         ublk = gmap[gblk].ublk;
         if (ublk != gmap_save[gblk2].ublk) continue;
         CPYEXT(ext1,gmap[gblk]);
         len = extents_overlap(&ext1,&ext2,&ext3);
         if (len == 0) continue;
         if (ndims == 2) {
            len = (ext3.imax - ext3.imin) * (ext3.jmax - ext3.jmin);
         } else {
            len = (ext3.imax - ext3.imin) * (ext3.jmax - ext3.jmin) *
                  (ext3.kmax - ext3.kmin);
         } 
         if (len > 0) {
            TRSEXT(exta,ext3,gmap_save[gblk2]);
            TRSEXT(extb,ext3,gmap[gblk]);
            domaincopy(domain_tmp, &exta, &domains[iblk], &extb);
	    domains[iblk].ndeltat = domain_tmp->ndeltat;
	    domains[iblk].dtg = domain_tmp->dtg;
         }
      }
      domain_free(domain_tmp);
      FREEMEM(domain_tmp);
      if (ifroot) {
         DBClose(idbid);
      }
   }
   if (!ifroot) {
      DBClose(idbid);
   }
   dmpattr_unset();
   FREEMEM(domainFiles);
   FREEMEM(domainRead);
   FREEMEM(gmap_save);
   DBFreeMultimesh(multiMesh);
   for (iblk = 0; iblk < nblk; iblk++) {
      BoundaryCondition_merge(&domains[iblk]);
      Source_merge(&domains[iblk]);
   }
   regen();
#endif
   return(error);
}
