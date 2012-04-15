#include "irs.h"
#include "irsblk.h"     
#include "irscom.h"
#include "irsdmp.hh"
#include "irsrgst.h"
#include "Hash.h"
#include "ProblemArray.h"

#ifdef SILO
int conddmp( int cyc )
{
   char *me = "conddmp";
   int ierr, i, ii, n, multi, exists, filecount, iblk, gblk, count;
   int error = 0;
   int numDomains, numBlocks;
   int *sldblk;
   FILE *fp;
   char idmpname[MAXWORD+16], odmpname[MAXWORD+16], infotmp[30];
   char tmp[MAXWORD+6], msg[128];
   DBfile *idbid;
   DBfile *idbidout;
   filecount = -1;
   do {
      filecount++;
      sprintf(tmp,"%s-%04i-",pbnm,filecount);
      sprintf(idmpname, "%s%05d.silo", tmp, cyc) ;
      exists = ((fp=fopen(idmpname,"r"))!=NULL);
      if (fp != NULL) fclose(fp);
   } while (exists);
   if (multi_dump_write > filecount/2) {
      multi_dump_write = filecount/2;
   }
   if (multi_dump_write < 2) {
      multi_dump_write = 1;
   }
   sprintf(tmp,"%s-0000-",pbnm);
   sprintf(idmpname, "%s%05d.silo", tmp, cyc) ;
   idbid = DBOpen (idmpname, DB_PDB, DB_READ);
   if (idbid == NULL) ctlerror(me,gv_errmsg_DBOpen);
   decomp_setdir(idbid);
   error = DBReadVar(idbid,"NumBlocks",&numBlocks);
   error = DBReadVar(idbid,"NumDomains",&numDomains);
   decomp_new(numBlocks, numDomains);
   decomp_read(idbid, msg, 0, 0);
   error += DBSetDir(idbid, "/");
   Restart_read_global(idbid); 
   dmpattr_set();
   ifparallel = 0;
   sldblk = ALLOT(int,nblkx);
   calculate_mappings();
   count=0;
   for (multi=0; multi<multi_dump_write; multi++) {
      gblk=0;
      if (multi_dump_write < 2) {
         sprintf(odmpname, "%s_c%05d.silo", pbnm, cyc) ;
      } else {
         sprintf(odmpname, "%s_c-%04d-%05d.silo", pbnm, multi, cyc) ;
      }
      sprintf(infotmp, "%s dump file", meshlink_codesys); 
      idbidout = DBCreate(odmpname, DB_CLOBBER, DB_LOCAL, infotmp, DB_PDB );
      for ( n=0; n < filecount / multi_dump_write + 
                  ((multi < filecount % multi_dump_write) ? 1:0); n++ ) {
         if (n>0 || multi>0) {
            sprintf(tmp,"%s-%04i-",pbnm,count);
            sprintf(idmpname, "%s%05d.silo", tmp, cyc) ;
            idbid = DBOpen (idmpname, DB_PDB, DB_READ);
            error += DBReadVar(idbid, "ndoms", &nblk);
         }
         for (iblk=0;iblk<nblk;iblk++) {
            sldblk[gblk] = 0;
            Restart_read_domain(idbid, iblk, gblk); 
            gv_alldump = TRUE;
            Restart_write_domain(idbidout, gblk);
            domain_free(&domains[gblk]);
            gblk++;
         }
         error+=DBClose(idbid);
         sprintf(msg,"dump '%s' read",idmpname);
         ctlmsg(msg);
         count++;
         if (fp != NULL) fclose(fp);
      }
      nblk=gblk;
      Restart_write_global(idbidout);
      error += DBSetDir(idbidout, "/");
      rootfile_write(idbidout, pbnm, cyc);
      error+=DBClose(idbidout);
   }
   FREEMEM(sldblk);
   dmpattr_unset();
   nblk = 0;
   return(error);
}
#endif
