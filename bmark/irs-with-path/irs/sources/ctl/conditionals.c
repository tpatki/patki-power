#include "irs.h"
#include "irsrgst.h"
#include "irsctl.h"
#include "irsgenrd.h"
#include "Hash.h"
#include "Conditional.h"
static int ifnestlevel	= 0;
static int numcond 	= 0;
static int numactcond   = 0;
int conditionals_if( void ) {
   char *me = "conditionals_if";
   char msg[MAXLINE];
   char op[MAXLINE];
   int cflag;
   int flag;
   int level;
   int donecount;
   flag = geti(&cflag);
   if (cflag != 0) {
      sprintf(msg,"Error reading argument of if-statement.");
      ctlwarning(me,msg);
      return(-1);
   }
   level = ifnestlevel;
   ifnestlevel++;
   donecount = 0;
   if (flag != 1) {
      ifexp = 0;
      geta(op);
      while (ifnestlevel != level) {
         if (!strcmp(op,"if")) ifnestlevel++;
         if (!strcmp(op,"endif")) ifnestlevel--;
         if (!strcmp(op,"done")) donecount++;
         if ( donecount > 200 ) {
            sprintf(msg,"Hit end of stream while searching for endif.");
            ctlwarning(me,msg);
            return(-1);
         }
         if (ifnestlevel == level)  break;
         geta(op);
      }
      ifexp = 1;
   }
   return(0);
}
int conditionals_endif( void ) {
   ifnestlevel--;
   return(0);
}
int conditionals_check( void ) {
   return(numactcond);
}
int conditionals_input( int mode ) {
   char *me = "conditionals_input";
   char op[MAXLINE];
   char msg[MAXLINE];
   Conditional_t *cond;
   cond = Conditional_construct(1);
   cond->once = mode;
   cond->id   = numcond;
   if (mode == 2) {
      sprintf(op,"atexit");
      cond->active = 0;
   } else {
      if (mode == 0) {
         sprintf(op,"when");
      } else {
         sprintf(op,"once");
      } 
      cond->expression_len = lineop_grab(&cond->expression, "}",ps);
      ps = NULL;
      if (cond->expression_len <= 0) {
         sprintf(msg,"Error reading expression for %s command.",op);
         ctlwarning(me,msg);
         FREEMEM(cond);
         return(-1);
      }
      numactcond++;
   }
   cond->msg_len = lineop_grab(&cond->msg, "endmsg", NULL);
   ps = NULL;
   if (cond->msg_len <= 0) {
      if (mode != 2) numactcond--;
      sprintf(msg,"Error reading message for %s command.",op);
      ctlwarning(me,msg);
      FREEMEM(cond->expression);
      FREEMEM(cond);
      return(-1);
   }
   conditionals_add(cond);
   numcond++;
   return(0);
}
void conditionals_add( Conditional_t *cond ) {
   char hashname[MAXLINE];
   Conditional_t *cond_root;
   Conditional_t *cond_ptr;
   cond_root = (Conditional_t *) hash_lookup_obj("Cond_root", gv_hash_tbl);
   if (cond_root == NULL) {
      hash_add("Cond_root", "Conditional_t", cond, gv_hash_tbl);
      cond->next = NULL;
      sprintf(hashname,"Cond_%i",cond->id);
      hash_add(hashname, "Conditional_t", cond, gv_hash_tbl);
      return;
   }
   cond_ptr = cond_root;
   while (cond_ptr->next != NULL) cond_ptr = cond_ptr->next;
   cond_ptr->next = cond;
   cond->next = NULL;
   sprintf(hashname, "Cond_%i", cond->id);
   hash_add(hashname, "Conditional_t", cond,gv_hash_tbl);
}
void conditionals_free( void ) {
   char name[MAXLINE];
   Conditional_t *cond_root;
   Conditional_t *cond_ptr;
   Conditional_t *cond_next_ptr;
   cond_root = (Conditional_t *)hash_lookup_obj("Cond_root",gv_hash_tbl);
   if (cond_root == NULL) return;
   cond_ptr = cond_root;
   hash_del2("Cond_root","Conditional_t",gv_hash_tbl);
   while (cond_ptr != NULL) {
      cond_next_ptr = cond_ptr->next;
      sprintf(name,"Cond_%i",cond_ptr->id);
      hash_del2(name,"Conditional_t",gv_hash_tbl);
      FREEMEM(cond_ptr->expression);
      FREEMEM(cond_ptr->msg);
      FREEMEM(cond_ptr);
      cond_ptr = cond_next_ptr;
   }
   numcond = 0;
}
int conditionals_eval(void) {
   int flag;
   int cflag;
   int lasttermfg, termfg = TERMFLG_READY ;
   Conditional_t *cond_root;
   Conditional_t *cond_ptr;
   if (numactcond == 0) return( TERMFLG_READY );
   cond_root = (Conditional_t *) hash_lookup_obj("Cond_root", gv_hash_tbl);
   cond_ptr = cond_root;
   while (cond_ptr != NULL) {
      if (cond_ptr->active) {
         line = cond_ptr->expression;
         ps   = line;
         flag = geti(&cflag);
         line = lnbuf;
         ps   = NULL;
         if (flag == 1) {
            pdmd = 1;
            line = cond_ptr->msg;
            ps   = line;
            lasttermfg = docmd();
            if ( lasttermfg > termfg ) termfg = lasttermfg;
            pdmd = 0;
            line = lnbuf;
            ps   = NULL;
            if (cond_ptr->once) {
               cond_ptr->active = 0;
               numactcond--;
            }
         }
      }
      cond_ptr = cond_ptr->next;
   }
   return( termfg );
}
int conditionals_atexit(void) {
   int lasttermfg, termfg = TERMFLG_READY ;
   Conditional_t *cond_root;
   Conditional_t *cond_ptr;
   cond_root = (Conditional_t *) hash_lookup_obj("Cond_root", gv_hash_tbl);
   cond_ptr = cond_root;
   while (cond_ptr != NULL) {
      if (cond_ptr->once == 2) {
         pdmd = 1;
         line = cond_ptr->msg;
         ps   = line;
         lasttermfg = docmd();
         if ( lasttermfg > termfg ) termfg = lasttermfg;
         pdmd = 0;
         line = lnbuf;
         ps   = NULL;
      }
      cond_ptr = cond_ptr->next;
   }
   return( termfg );
}
int conditionals_show(int num, char **msgout, int *msglen) {
   char *me = "conditionals_show";
   char hashname[MAXLINE];
   char msg[MAXLINE];
   char *str;
   int i;
   int len;
   Conditional_t *cond;
   sprintf(hashname, "Cond_%i",num);
   cond = (Conditional_t *) hash_lookup_obj(hashname, gv_hash_tbl);
   if (cond == NULL) {
      sprintf(msg,"Conditional %i cannot be found.",num);
      ctlwarning(me,msg);
      return(-1);
   }
   if (cond->once == 0) {
      ctlmsg1("when ");
   } else if(cond->once == 1) {
      ctlmsg1("once ");
   } else {
      ctlmsg1("atexit ");
   } 
   i   = 0;
   len = 0;
   str = MALLOT(char, cond->expression_len + 1);
   while (len != cond->expression_len) {
      if (cond->expression[len] != '$') str[i++] = cond->expression[len];
      len++;
   }
   str[i++] = '\n';
   str[i++] = '\0';
   ctlmsg(str);
   FREEMEM(str);
   *msgout = cond->msg;
   *msglen = cond->msg_len;
   return(0);
}
int conditionals_redo(int num) {
   char *me = "conditionals_redo";
   char hashname[MAXLINE];
   char msg[MAXLINE];
   char op[MAXLINE];
   Conditional_t *cond;
   sprintf(hashname, "Cond_%i",num);
   cond = (Conditional_t *) hash_lookup_obj(hashname, gv_hash_tbl);
   if (cond == NULL) {
      sprintf(msg,"Conditional %i cannot be found.",num);
      ctlwarning(me,msg);
      return(-1);
   }
   FREEMEM(cond->expression);
   FREEMEM(cond->msg);
   sprintf(hashname, "Cond_%i",num);
   if (cond->once == 2) {
      sprintf(op,"atexit");
   } else {
      if (cond->once == 0) {
         sprintf(op,"when");
      } else {
         sprintf(op,"once");
      }
      cond->expression_len = lineop_grab(&cond->expression, "}",ps);
      ps = NULL;
      if (cond->expression_len <= 0) {
         sprintf(msg,"Error reading expression for %s command.",op);
         ctlwarning(me,msg);
         return(-1);
      }
   }
   cond->msg_len = lineop_grab(&cond->msg, "endmsg", NULL);
   ps = NULL;
   if (cond->msg_len <= 0) {
      sprintf(msg,"Error reading message for %s command.",op);
      ctlwarning(me,msg);
      return(-1);
   }
   return(0);
}
int conditionals_del(int num) {
   char *me = "conditionals_redo";
   char hashname[MAXLINE];
   char msg[MAXLINE];
   char op[MAXLINE];
   Conditional_t *cond_link, *cond_ptr;
   sprintf(hashname, "Cond_%i", num);
   cond_ptr = (Conditional_t *) hash_lookup_obj(hashname, gv_hash_tbl);
   if (cond_ptr == NULL) {
      sprintf(msg,"Conditional %i cannot be found.",num);
      ctlwarning(me,msg);
      return(-1);
   }
   if (cond_ptr->active) numactcond--;
   cond_link = (Conditional_t *)hash_lookup_obj("Cond_root",gv_hash_tbl);
   if (cond_link == cond_ptr) {
      hash_del2("Cond_root","Conditional_t",gv_hash_tbl);
      if (cond_link->next != NULL) {
         hash_add("Cond_root", "Conditional_t", cond_ptr->next, gv_hash_tbl);
      }
   } else {
      while (cond_link->next != cond_ptr) {
         cond_link = cond_link->next;
      }
      cond_link->next = cond_ptr->next;
   }
   hash_del2(hashname, "Conditional_t", gv_hash_tbl);
   FREEMEM(cond_ptr->expression);
   FREEMEM(cond_ptr->msg);
   FREEMEM(cond_ptr);
   numcond--;
   return(0);
}

#ifdef SILO
void conditionals_rdsilo( DBfile *idbid ) 
{
  char *me = "conditionals_rdsilo";
  char dirname[128];
  int i, count;
  Conditional_t *cond_ptr;
  if (DBSetDir(idbid,"/Global/Conditionals") != 0) ctlerror(me,gv_errmsg_DBSetDir);
  if (DBReadVar(idbid, "NumCond", &numcond)  != 0) ctlerror(me,gv_errmsg_DBReadVar);
  count = numcond;
  for (i = 0; i < numcond; i++) {
    sprintf(dirname,"Cond%i",i);
    cond_ptr = rgst_read_struct_in_dir(idbid, dirname, "Conditional_t", NULL, NULL);
    if (cond_ptr == NULL) ctlerror(me,gv_errmsg_rgst_read_struct_in_dir);
    conditionals_add(cond_ptr);
    if (cond_ptr->active == 0) count--;
  }
  numactcond = count;
  if (DBSetDir(idbid,"/Global") != 0) ctlerror(me,gv_errmsg_DBSetDir);
}
#endif

#ifdef SILO
void conditionals_wtsilo( DBfile *idbid ) 
{
  char *me = "conditionals_wtsilo";
  char dirname[128];
  int i, dims[2];
  Conditional_t *cond_ptr;
  if (DBMkdir( idbid, "/Global/Conditionals") != 0) ctlerror(me,gv_errmsg_DBMkDir);
  cond_ptr = (Conditional_t *)hash_lookup_obj("Cond_root", gv_hash_tbl);
  i = 0;
  while (cond_ptr != NULL) {
    sprintf(dirname,"/Global/Conditionals/Cond%i",i);
    if (rgst_write_struct_in_dir(idbid, dirname, "Conditional_t", cond_ptr, NULL) != 0)
       ctlerror(me,gv_errmsg_rgst_write_struct_in_dir);
    cond_ptr = cond_ptr->next;
    i++;
  }
  dims[0] = 1;
  if (DBSetDir(idbid,"/Global/Conditionals") != 0) ctlerror(me,gv_errmsg_DBSetDir);
  if (DBWrite(idbid, "NumCond", &i, dims, 1, DB_INT) != 0) ctlerror(me,gv_errmsg_DBWrite);
  if (DBSetDir(idbid,"../") != 0) ctlerror(me,gv_errmsg_DBSetDir);
}
#endif
