#include "irs.h"
#include "irsdmp.h"
#ifdef SILO
DBfile *openpdmp( char* kern, int cyc, int num, int mode, char* dmpname)
{
   char *me = "openpdmp";
   DBfile *idbidin;
   int ierr;
   char infotmp[30], msg[128];
   char fullname[MAXLINE];
   if (num >= 0) {
      if (cyc >= 0) {
         sprintf(dmpname, "%s-%04d-%05d.silo", kern, num, cyc) ;
      } else {
         sprintf(dmpname, "%s-%04d.silo", kern, num) ;
      } 
   } else {
      if (cyc >= 0) {
         sprintf(dmpname, "%s%05d.silo", kern, cyc) ;
      } else {
         sprintf(dmpname, "%s.silo", kern) ;
      }
   } 
   if (mode == 2) return(NULL);
   DBShowErrors(DB_NONE, NULL);
   if (mode == 0) {
      idbidin = DBOpen (dmpname, DB_PDB, DB_READ);
      if (idbidin == NULL) ctlerror(me,gv_errmsg_DBOpen);
   } else {
      sprintf(infotmp, "%s dump file", meshlink_codesys);
      strcpy(fullname,outpath);
      strcat(fullname,dmpname);
      idbidin = DBCreate(fullname, DB_CLOBBER, DB_LOCAL, infotmp, DB_PDB );
   } 
   DBShowErrors(DB_TOP, NULL);
   return(idbidin);
}
#endif
