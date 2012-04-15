#include "irs.h"
#include "irsobjects.h"
#include "irsdmp.h"
#include "irscom.h"
#include "irsreg.h"
#include "irsrgst.h"
#include "BlockMapping.h"
#include "FunctionTimer.h"
#include "ProblemArray.h"
#include "Region.h"
#include "Rgst.h"
#include "Tracer.h"

#ifdef SILO
void rootfile_write( DBfile *idbidin, char  *kern, int   cyc_in)
{
   char *me = "wdmprt_rootfile";
   char msg[MAXLINE];
   char dmpname[MAXLINE];
   char infotmp[MAXLINE];
   int i,ir;
   int iblk, gblk;
   int npblk;
   int nsblk;
   int id;
   int ierr;
   int num;
   int blkperfile;
   int leftovers;
   int count;
   int openfile;
   int *nmatspec;
   int *slidemap;
   int *localdomain;
   int *meshtypes; 
   int *vartypes;
   int dims[1];
   RGST_AttributeElem_t *dumpvar;
   RGST_AttributeElem_t *dumpvar_ptr;
   char **meshnames, **matnames, **rootnames;
   char searchpath[]="";
   static char defvars2[] = {
    "velocity vector {xdot,ydot};"
      "slidevt vector {xvt,yvt};"
        "slidevb vector {xvb,yvb};"
          "speed scalar sqrt(xdot*xdot + ydot*ydot);"};
   static char defvars3[] = {
    "velocity vector {xdot,ydot,zdot};"
      "slidevt vector {xvt,yvt,zvt};"
        "slidevb vector {xvb,yvb,zvb};"
          "speed scalar sqrt(xdot*xdot + ydot*ydot + zdot*zdot)"};
   DBoptlist *ioptnod;
   DBfile *idbiddum;
   DBfile *idbid;
   ierr = 0;
   openfile = 0;
   if (idbidin == NULL) {
      openfile = 1;
   } else {
      idbid = idbidin;
   } 
   if ((openfile) && (myid == 0)) {
      sprintf(msg,"%s%s%05d.root",outpath,kern,cyc_in);
      sprintf(infotmp, "%s dump file", meshlink_codesys);
      idbid = DBCreate(msg, DB_CLOBBER, DB_LOCAL, infotmp, DB_PDB);
   }
   slidemap         = MALLOT(int, 2 * gnblk);
   localdomain      = slidemap + gnblk;
   for (gblk = 0; gblk < gnblk; gblk++) {
      slidemap[gblk]    = 0;
      localdomain[gblk] = -1;
   }
   for (iblk = 0; iblk < nblk; iblk++) {
      gblk = domains[iblk].gblk;
      localdomain[gblk] = iblk;
   }
   if (ifparallel) {
      comreduce(slidemap, 2 * gnblk, COM_MAX, COM_ONE, COM_INT);
   }
   if ((openfile) && (myid != 0)) {
      FREEMEM(slidemap);
      return;
   }
   dims[0] = 1;
   ierr = DBWrite(idbid, "_meshtv_searchpath", searchpath, dims, 1, DB_CHAR);
   if ( ndims == 2 ) {
     dims[0] = strlen(defvars2);
     ierr = DBWrite(idbid, "_meshtv_defvars", defvars2, dims, 1, DB_CHAR);
   } else {
     dims[0] = strlen(defvars3);
     ierr = DBWrite(idbid, "_meshtv_defvars", defvars3, dims, 1, DB_CHAR);
   }
   if (DBMkdir( idbid, "Decomposition") != 0) ctlerror(me,gv_errmsg_DBMkDir);
   if (DBSetDir(idbid, "Decomposition") != 0) ctlerror(me,gv_errmsg_DBSetDir);
   for (gblk = 0; gblk < gnblk; gblk++) {
      gmap[gblk].lblk = gblk;
   }


   decomp_write(idbid,"domain");
   DBSetDir(idbid,"../");
   for (gblk = 0; gblk < gnblk; gblk++) {
      gmap[gblk].lblk = -1;
   }
   for (iblk = 0; iblk < nblk; iblk++) {
      gblk = domains[iblk].gblk;
      gmap[gblk].lblk = iblk;
   }
   meshtypes = ALLOT(int,gnblk);
   vartypes  = ALLOT(int,gnblk);
   matnames  = (char **)calloc(gnblk,sizeof(char *));
   meshnames = (char **)calloc(gnblk,sizeof(char *));
   rootnames = (char **)calloc(gnblk,sizeof(char *));
   ioptnod = DBMakeOptlist( 10 );
   for (gblk = 0; gblk < gnblk; gblk++) {
      matnames[gblk]   = ALLOT(char,128);
      meshnames[gblk]  = ALLOT(char,128);
      rootnames[gblk]  = ALLOT(char,128);
      vartypes[gblk]  = DB_QUADVAR;
      meshtypes[gblk] = DB_QUADMESH;
   }
   num = -1;
   blkperfile = gnblk / multi_dump_write;
   leftovers  = gnblk % multi_dump_write;
   count      = 0;
   if (multi_dump_write > 1) num = 0;
   for (gblk = 0; gblk < gnblk; gblk++) {
      if (ifparallel) num = gmap[gblk].proc;
      idbiddum = openpdmp(kern, cyc_in, num, 2, dmpname);
      if (iffamily) {
         sprintf(msg,"%s%05d/%s",kern,cyc_in,dmpname);
      } else {
         strcpy(msg,dmpname);
      }
      if (multi_dump_write > 1) {
         sprintf(rootnames[gblk],"%s:/domain%i", msg, count);
         localdomain[gblk] = count;
      } else if (openfile) {
         sprintf(rootnames[gblk],"%s:/domain%i", msg, localdomain[gblk]);
      } else {
         sprintf(rootnames[gblk],"/domain%i", localdomain[gblk]);
      } 
      sprintf(matnames[gblk],"%s/Materials",rootnames[gblk]);
      sprintf(meshnames[gblk],"%s/hydro_mesh",rootnames[gblk]);
      if (multi_dump_write > 1) {
         count++;
         id = blkperfile;
         if (num < leftovers)  id = blkperfile + 1;
         if (count >= id) {
            count = 0;
            num++;
         }
      }
   }
   dims[0] = gnblk;
   ierr = DBWrite(idbid, "DomainFiles", localdomain, dims, 1, DB_INT);
   ierr = ierr + DBAddOption( ioptnod, DBOPT_DTIME, &ttime );
   ierr = ierr + DBAddOption( ioptnod, DBOPT_CYCLE, &cycle );
   id = 0;
   ierr = ierr + DBAddOption( ioptnod, DBOPT_BLOCKORIGIN, &id );
   id = 0;
   ierr = ierr + DBAddOption( ioptnod, DBOPT_GROUPORIGIN, &id );
   ierr = ierr + DBAddOption( ioptnod, DBOPT_NGROUPS, &unblk );
   if (ifdynspec) {
      nmatspec = MALLOT(int, nreg);
      for (ir = 1; ir <= nreg; ir++) {
         nmatspec[ir - 1] = reg[ir].nspec;
      }
      DBAddOption(ioptnod, DBOPT_MATNAME,  "Materials"  );
      DBAddOption(ioptnod, DBOPT_NMAT,     &nreg    );
      DBAddOption(ioptnod, DBOPT_NMATSPEC,  nmatspec );
      ir = DB_ON;
      DBAddOption(ioptnod, DBOPT_USESPECMF,  &ir );
   }
   ierr = DBSetDir(idbid, "/");
   ierr = DBPutMultimesh(idbid,"hydro_mesh", gnblk, meshnames,
                         meshtypes, ioptnod);
   dumpvar = rgst_list_attr(A_OBJECT,"DomainDumpVar");
   dumpvar_ptr = dumpvar;
   while (dumpvar_ptr != NULL) {
      char *name          = ATTR_GET_OBJECT_NAME(dumpvar_ptr);
      for (gblk = 0; gblk < gnblk; gblk++) {
         sprintf(meshnames[gblk],"%s/%s",rootnames[gblk],name);
      }
      ierr = DBPutMultivar(idbid, name, gnblk, meshnames, vartypes, ioptnod);
      dumpvar_ptr = dumpvar_ptr->next;
   }
   ierr = DBPutMultimat(idbid,"Materials",gnblk,matnames,ioptnod);
   if (ierr != 0) {
         ctlwarning(me,"Silo error, put Multimat");
         return;
   }
   if (ifdynspec) {
      for (gblk = 0; gblk < gnblk; gblk++) {
         sprintf(matnames[gblk],"%s/Species",rootnames[gblk]);
      }
      ierr = DBPutMultimatspecies(idbid,"Species",gnblk,matnames,ioptnod);
      if (ierr != 0) {
         ctlwarning(me,"Silo error, put Multimatspecies");
      }
   }
   id = 0;
   nsblk = 0;
   for (gblk = 0; gblk < gnblk; gblk++) {
      if (slidemap[gblk]) {
         sprintf(meshnames[id],"%s/slide_mesh",rootnames[gblk]);
         meshtypes[id]=DB_UCDMESH;
         vartypes[id]=DB_UCDVAR;
         id++;
         nsblk++;
      }
   }
   if (nsblk > 0) {
      ierr = DBPutMultimesh(idbid,"slide_mesh",id, meshnames, meshtypes, 
                            ioptnod);
      id = 0;
      for (gblk = 0; gblk < gnblk; gblk++) {
         if (slidemap[gblk]) {
            sprintf(meshnames[id],"%s/xvt",rootnames[gblk]);
            id++;
         }
      }
      ierr = DBPutMultivar(idbid, "xvt" , id, meshnames, vartypes, ioptnod);
      id = 0;
      for (gblk = 0; gblk < gnblk; gblk++) {
         if (slidemap[gblk]) {
            sprintf(meshnames[id],"%s/xvb",rootnames[gblk]);
            id++;
         }
      }
      ierr = DBPutMultivar(idbid, "xvb" , id, meshnames, vartypes, ioptnod);
      id = 0;
      for (gblk = 0; gblk < gnblk; gblk++) {
         if (slidemap[gblk]) {
            sprintf(meshnames[id],"%s/yvt",rootnames[gblk]);
            id++;
         }
      }
      ierr = DBPutMultivar(idbid, "yvt" , id, meshnames, vartypes, ioptnod);
      id = 0;
      for (gblk = 0; gblk < gnblk; gblk++) {
         if (slidemap[gblk]) {
            sprintf(meshnames[id],"%s/yvb",rootnames[gblk]);
            id++;
         }
      }
      ierr = DBPutMultivar(idbid, "yvb" , id, meshnames, vartypes, ioptnod);
      if (ndims == 3) {
         id = 0;
         for (gblk = 0; gblk < gnblk; gblk++) {
            if (slidemap[gblk]) {
               sprintf(meshnames[id],"%s/zvt",rootnames[gblk]);
               id++;
            }
         }
         ierr = DBPutMultivar(idbid, "zvt" , id, meshnames, vartypes, ioptnod);
         id = 0;
         for (gblk = 0; gblk < gnblk; gblk++) {
            if (slidemap[gblk]) {
               sprintf(meshnames[id],"%s/zvb",rootnames[gblk]);
               id++;
            }
         }
         ierr = DBPutMultivar(idbid, "zvb" , id, meshnames, vartypes, ioptnod);
      }
   }
   SubMesh_wtroot(idbid, ioptnod, rootnames);
   ierr = DBFreeOptlist(ioptnod);
   for (gblk = 0; gblk < gnblk; gblk++) {
      free(meshnames[gblk]);
      free(matnames[gblk]);
      free(rootnames[gblk]);
   }
   free(meshnames);
   free(matnames);
   free(rootnames);
   FREEMEM(slidemap);
   if (ifdynspec) {
      FREEMEM(nmatspec);
   }
   FREEMEM(meshtypes);
   FREEMEM(vartypes);
   if (openfile) DBClose(idbid);
   return;
}
#endif

#ifdef SILO
void rootfile_read( char  *kern, int   cyc_in ) {
   char *me = "rootfile_read";
   char *cptr;
   char msg[MAXLINE], name[MAXLINE], tmp[MAXLINE];
   int  i, error, ierr, first, iblk, gblk, numDomains, numBlocks, mynblk;
   int  *domainFiles;
   DBmultimesh *multiMesh;
   DBfile      *idbid;
   memset(name,'\0',MAXLINE);
   sprintf(name,"%s%s%05d.root",outpath,kern,cyc_in);
   idbid = DBOpen(name, DB_PDB, DB_READ);
   if (idbid == NULL) {
      sprintf(msg,"Cannot open file %s",name);
      ctlerror(me,msg);
   }
   decomp_setdir(idbid);
   error = DBReadVar(idbid,"NumBlocks",&numBlocks); 
   error = DBReadVar(idbid,"NumDomains",&numDomains);
   decomp_new(numBlocks, numDomains);
   decomp_read(idbid, name, 0, 0);
   error = DBSetDir(idbid,"/");
   calculate_mappings();
   multiMesh = DBGetMultimesh(idbid, "hydro_mesh");
   domainFiles = MALLOT(int, gnblk);
   error += DBReadVar(idbid, "DomainFiles", domainFiles);
   DBClose(idbid);
   first  = 1;
   mynblk = 0;
   for (gblk = 0; gblk < multiMesh->nblocks; gblk++) {
      if (gmap[gblk].proc != myid) continue;
      memset(tmp,'\0',MAXLINE);
      strcpy(tmp,multiMesh->meshnames[gblk]);
      cptr = strtok(tmp,":");
      iblk = gmap[gblk].lblk;
      idbid = DBOpen(cptr, DB_PDB, DB_READ);
      if (idbid == NULL) {
         sprintf(msg,"Cannot open file %s",cptr);
         ctlerror(me,msg);
      }
      if ( first ) {
         first = 0;
         Restart_read_global(idbid);
	 dmpattr_set();
         nblk = 0;  
         gnblk = numDomains;
         unblk = numBlocks;;
      }
      Restart_read_domain(idbid, domainFiles[gblk], iblk); 
      error += DBClose(idbid);
      mynblk++;
   }
   nblk = mynblk;
   if (nblk == 0) {
      memset(tmp,'\0',MAXLINE);
      strcpy(tmp,multiMesh->meshnames[gnblk - 1]);
      cptr = strtok(tmp,":");
      idbid = DBOpen(cptr, DB_PDB, DB_READ);
      if (idbid == NULL) {
         sprintf(msg,"Cannot open file %s",cptr);
         ctlerror(me,msg);
      }
      Restart_read_global(idbid);
      dmpattr_set();
      nblk = 0;  
      gnblk = numDomains;
      unblk = numBlocks;;
   }
   DBFreeMultimesh(multiMesh);
   dmpattr_unset();
   FREEMEM(domainFiles);
}
#endif
