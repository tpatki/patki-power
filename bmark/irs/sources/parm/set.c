#include "irs.h"
#include "irsparm.h"
#include "irsrgst.h"
int  set( void )
{
   char *me = "set";
   char msg[128];
   int cflag;
   char pname[MAXWORD];
   void *obj;
   geta(pname) ;
   if (genmd != -1) {
      cflag = rgst_query_attr(A_OBJECT, pname, "ParmMemorySensitive",NULL);
      if (cflag) {
         sprintf(msg,"Setting flag %s has memory implications.\n\t  You have been warned",
                        pname);
         ctlnotice(me,msg);
      }
      if (ifparallel) {
         cflag = rgst_query_attr(A_OBJECT, pname, "ParmParallelSensitive",NULL);
         if (cflag) {
            sprintf(msg,"Setting flag %s has parallel implications.\n\t  You have been warned"
                           ,pname);
            ctlnotice(me,msg);
         }
      }
   }
   if (rgst_check_for_obj(pname) != TRUE) {
     sprintf(msg,"Can't set '%s' -- it is not in the registry",pname);
     ctlnotice(me,msg);
     return(-1);
   }
   obj = rgst_get(pname);
   if      (RGST_QUERY_OBJECT_ATTR(pname,"int_parm") == TRUE) {
     *((int *)(obj)) = geti(&cflag);
   }
   else if (RGST_QUERY_OBJECT_ATTR(pname,"double_parm") == TRUE) {
     *((double *)(obj)) = getf(&cflag);
   }
   else if (RGST_QUERY_OBJECT_ATTR(pname,"char_parm") == TRUE) {
     geta((char *)obj);
   }
   else {
     sprintf(msg,"Can't set '%s' -- it is not a parm",pname);
     ctlnotice(me,msg);
     return(-1);
   }
   return(0);
}
