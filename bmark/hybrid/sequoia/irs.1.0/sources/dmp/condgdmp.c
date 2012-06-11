#include "irs.h"
#include "irsdmp.h"
#include "irsrgst.h"

#ifdef SILO
int condgdmp( int cyc )
{
   char *me = "condgdmp";
   int i,j;
   int iblk;
   int gblk;
   int ierr;
   int nsblk;
   int nqvar;
   int error;
   int count;
   int nucdvar;
   int sldblk[MAXBLKS];
   int vartypes[MAXBLKS];
   int meshtypes[MAXBLKS];
   FILE *fp;
   char tmp[MAXWORD+6], msg[128], outdir[18], infotmp[30], idmpname[MAXWORD+17];
   char **ucdnames;
   char **qvarnames;
   char *matnames [MAXBLKS];
   char *meshnames[MAXBLKS];
   DBtoc *toc;
   DBfile *idbidout;
   DBfile *idbidin;
   DBoptlist *ioptnod;
   error = 0;
   sprintf(idmpname, "%sg%05d.silo", pbnm, cyc) ;
   sprintf(infotmp,"%s dump file",meshlink_codesys);
   idbidout = DBCreate(idmpname, DB_CLOBBER, DB_LOCAL,
		       infotmp, DB_PDB );
   sprintf(tmp,"%sg-0000-",pbnm);
   sprintf(idmpname, "%s%05d.silo", tmp, cyc) ;
   idbidin = DBOpen (idmpname, DB_PDB, DB_READ);
   if (idbidin == NULL) {
      sprintf(msg,"Cannot find graphics dump - %s",idmpname);
      ctlerror(me,msg);
   }
   ierr = DBSetDir(idbidin, "/");
   toc = DBGetToc(idbidin);
   nqvar   = toc->nmultivar;
   ucdnames  = ALLOT(char *, nqvar);
   qvarnames = ALLOT(char *, nqvar);
   for (i = 0; i < nqvar; i++) {
      ucdnames[i]  = ALLOT(char,40);
   }
   for (i = 0; i < nqvar; i++) {
      qvarnames[i] = ALLOT(char,40);
   }
   for (i = 0; i < MAXBLKS; i++) {
      matnames[i]  = ALLOT(char,40);
      meshnames[i]  = ALLOT(char,40);
   }
   gblk=0;
   nsblk=0;
   count=0;
   while (idbidin != NULL ) {
      ierr = DBSetDir(idbidin, "/");
      toc = DBGetToc(idbidin);
      nblk = toc->ndir - 1;
      for (iblk=0;iblk<nblk;iblk++) {
         nucdvar = 0;
         rwgdmp(idbidin,idbidout,qvarnames,&nqvar,ucdnames,&nucdvar,iblk,gblk);
         if (nucdvar > 0) {
            sldblk[nsblk] = gblk;
            nsblk++;
         }
         gblk++;
      }
      error+=DBClose(idbidin);
      sprintf(msg,"dump '%s' read",idmpname);
      ctlmsg(msg);
      count++;
      sprintf(tmp,"%sg-%04i-",pbnm,count);
      sprintf(idmpname, "%s%05d.silo", tmp, cyc) ;
      if ( (fp=fopen(idmpname,"r")) == NULL ) {
         idbidin=NULL;
      } else {
         fclose(fp);
         idbidin = DBOpen (idmpname, DB_PDB, DB_READ);
      }
   }
   for (iblk=0; iblk < gblk; iblk++) {
      sprintf(outdir,"/domain%i",iblk);
      (void)strcpy(matnames[iblk],outdir);
      (void)strcat(matnames[iblk],"/");
      (void)strcat(matnames[iblk],"Materials");
      (void)strcpy(meshnames[iblk],outdir);
      (void)strcat(meshnames[iblk],"/hydro_mesh");
      vartypes[iblk] = DB_QUADVAR;
      meshtypes[iblk] = DB_QUAD_RECT;
   }
   ioptnod = DBMakeOptlist( MAXOPTS );
   ierr = ierr + DBAddOption( ioptnod, DBOPT_DTIME, &ttime );
   ierr = ierr + DBAddOption( ioptnod, DBOPT_CYCLE, &cycle );
   ierr = DBSetDir(idbidout, "/");
   ierr = DBPutMultimesh(idbidout,"hydro_mesh", gblk, meshnames,
                         meshtypes, ioptnod);
   ierr = DBPutMultimat(idbidout,"Materials",gblk,matnames,ioptnod);
   for (i=0; i<nqvar; i++) {
      for (iblk=0; iblk < gblk; iblk++) {
         sprintf(meshnames[iblk],"/domain%i/",iblk);
         (void)strcat(meshnames[iblk],qvarnames[i]);
      }
      ierr = DBPutMultivar(idbidout, qvarnames[i], gblk, meshnames,
                              vartypes, ioptnod);
   }
   for (i = 0; i < nucdvar; i++) {
      for (j=0; j < nsblk; j++) {
         iblk = sldblk[j];
         sprintf(meshnames[j],"/domain%i/%s",iblk,ucdnames[i]);
      }
      ierr = DBPutMultivar(idbidout, ucdnames[i], nsblk, meshnames,
                              vartypes, ioptnod);
   }
   if (nsblk > 0) {
      for (j=0; j < nsblk; j++) {
         iblk = sldblk[j];
         sprintf(meshnames[j],"/domain%i/slide_mesh",iblk);
      }
      ierr = DBPutMultimesh(idbidout,"slide_mesh", nsblk, meshnames,
                         meshtypes, ioptnod);
   }
   ierr = DBFreeOptlist(ioptnod);
   error+=DBClose(idbidout);
   for (i = 0; i < nqvar; i++) {
     FREEMEM(qvarnames[i]);
     FREEMEM(ucdnames[i]);
   }
   FREEMEM(qvarnames);
   FREEMEM(ucdnames);
   for (i = 0; i < MAXBLKS; i++) {
      FREEMEM(meshnames[i]);
      FREEMEM(matnames[i]);
   }
   return(error);
}
#endif
