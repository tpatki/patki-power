#include "irs.h"
#include "irsctl.h"	
#include "irsgen.h"
#include "irsgenrd.h"
#include "irsrgst.h"
#include "AEStackElm.h"
#include "Command.h"
#include "Rgst.h"
int docmd( void )
{
   char *me = "docmd";
   char msg[256], mynewcmd[MAXWORD];
   int  ifun, len, i, termfg = TERMFLG_READY, ierr = 0, j = 0;
   double *darg = NULL;
   Command_t *cp;
   RGST_Object_t *ro;
   while(TRUE) {
      strcpy(prompt, codename);
      geta(mynewcmd);
      strcpy(prompt, "<...");
      if ((termfg = endchk(mynewcmd)) != 0) {
         break;
      }
      if (mynewcmd[0] == '*') {
         newline();
      }
      else if (mynewcmd[0] == '$') {
         i = j ;     
      }
      else if (rgst_check_for_obj(mynewcmd) == TRUE) {
         ro = rgst_get_RGST_Object_t(mynewcmd);
         if (ro->datatype == R_FUNCTION) {
            cp = (Command_t *)ro->obj;
            (*(cp->handler))(cp);
         }
         else {
            if ( (RGST_QUERY_OBJECT_ATTR(mynewcmd,"DomainVar")  == TRUE)
               ||(RGST_QUERY_OBJECT_ATTR(mynewcmd,"GlobalArray")  == TRUE)) {
              dopa(mynewcmd);
            }
            else if (RGST_QUERY_OBJECT_ATTR( mynewcmd,"int_parm") == TRUE) {
               ctloutput(me,mynewcmd,R_INT,*((int *)ro->obj));
            }
            else if (RGST_QUERY_OBJECT_ATTR( mynewcmd,"double_parm") == TRUE) {
               ctloutput(me,mynewcmd,R_DOUBLE,*((double *)ro->obj));
            }
            else if (RGST_QUERY_OBJECT_ATTR( mynewcmd,"char_parm") == TRUE) {
               sprintf(msg,"%s = %s",mynewcmd,(char *)ro->obj);
               ctlmsg(msg);
            }
            else {
               sprintf(msg,"\n\tDo not know how to process command '%s'"
                           "\n\tDiscarding remaining tokens on input line.",
                           mynewcmd);
               ctlnotice(me,msg);
               geta_discard(TRUE);
            }
         }
      }
      else if ((ifun = isargfun(sym)) >= 0) {
         if (output_dest == TO_STACK) {
            len = doarg_fun_alloc(ifun, &darg, -1);
            if (len > 1) {
               ctloutput(me,NULL,R_DOUBLE_ARRAY,darg,len);
               free(darg);
            }
            else if (len == 1) {
               ctloutput(me,NULL,R_DOUBLE,*darg);
               free(darg);
            }
            else {
               ctlwarning(me,"doargfun_alloc failed during edit");
            }
         }
         else {
            sprintf(msg,"Do not know how to process command '%s'",mynewcmd);
            ctlnotice(me,msg);
         }
      }
      else {
         sprintf(msg,"Do not know how to process command '%s'",mynewcmd);
         ctlnotice(me,msg);
      }
      if ((pdmd == 1) && (ierr == 1)) {
         termfg = TERMFLG_ERROR ;
         break ;
      }
      if (output_dest == TO_STACK) {
         break;
      }
      if (do_just_one_command == TRUE) {
         break;
      }
      if (ierr) {
         newline();
         ierr = 0;
      }
      if (lastfile == -1) {
         lastfile = 0;   
         break;
      }
   }
   return(termfg);
}
