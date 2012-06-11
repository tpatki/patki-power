#include "irs.h"
#include "irsobjects.h"
#include "irsdmp.h"
#include "irsctl.h"
#include "irsrgst.h"
#include "ProblemArray.h"
#ifdef SILO
int  wgdmp( void )
{
   char *me = "wgdmp";
   int  error, i;
   int  gotone;
   char msg[64];
   char mykern[MAXWORD];
   char op[MAXWORD];
   error = 0 ;
   gotone = 1;
   if (lfchk() > 0) gotone = 0;
   while (gotone) {
      peekc(op);
      if (RGST_QUERY_OBJECT_ATTR(op,"DomainVar") == TRUE) {
	ProblemArray_t *prb = ProblemArray_find(op,NULL);
        geta(op);
	if (prb->type == R_DOUBLE) {
           rgst_add_attr(A_OBJECT, op, "dDomainDumpVar");
           rgst_add_attr(A_OBJECT, op, "DomainDumpVar");
	} else if (prb->type == R_INT) {
           rgst_add_attr(A_OBJECT, op, "iDomainDumpVar");
           rgst_add_attr(A_OBJECT, op, "DomainDumpVar");
	} else {
           sprintf(msg,"Can't dump %s with wgdmp",op);
           ctlnotice(me,msg);
	} 
      } else if (!strcmp(op,"submesh")) {
         geta(op);
         error = SubMesh_parse();
	 if (error != 0) {
            sprintf(msg,"Error trying to parse submesh input.");
            ctlwarning(me,msg);
	 }
      } else {
        gotone = 0;
      }
      if (lfchk() > 0) gotone = 0;
   }
   sprintf(mykern,"%sg",pbnm);
   gv_alldump = FALSE;
   error = Restart_write_driver(mykern, cycle, gv_alldump);
   if ((ifparallel) || (multi_dump_write > 1)) {
      rootfile_write(NULL, mykern, cycle);
   }
   SubMesh_free();
   dmpattr_unset();
   return(error) ;
}
#endif
