#include <sys/types.h>
#include <dirent.h>
#include "irs.h"
#include "irscom.h"
#include "irsdmp.h"
#include "irsgen.h"
#include "irssrc.h"
#include "FunctionTimer.h"
#ifndef scandir
int scandir();
#endif 
#ifndef alphasort
int alphasort();
#endif 
static char *getdmplst_base;
static char *getdmplst_exten;
static int   getdmplst_extenlen;
static int   getdmplst_baselen;
static int   getdmplst_mdmpflag;
static int   getdmplst_cyc;
static int  getdmplst_pruner(struct dirent *dentry);

#ifdef SILO
void  getdmplst_last( char *dmpname, char *extention, int mode, int mdmpflag )
{
   char *me = "getdmplst";
   char msg[128];
   char tmp1[MAXLINE] ;
   char tmp2[MAXLINE] ;
   char tmp3[MAXLINE] ;
   char *baseptr;
   int ndumps;
   int i;
   int mycyc;
   struct dirent **dmplist;
   getdmplst_base     = dmpname;
   getdmplst_exten    = extention;
   getdmplst_extenlen = strlen(extention);
   getdmplst_baselen  = strlen(dmpname);
   getdmplst_mdmpflag = mdmpflag;
   getdmplst_cyc      = mode;
   if (myid == 0) {
      ndumps = scandir(".",&dmplist,&getdmplst_pruner,&alphasort); 
   }
   if (ifparallel) combcast(&ndumps,1,COM_INT,0);
   if (ndumps <= 0) {
      sprintf(msg,"Cannot find dump with kernel %s.",dmpname);      
      ctlerror(me,msg);
   }
   if (myid == 0) {
      if (mdmpflag) {
         strcpy(tmp1,dmplist[ndumps - 1]->d_name);
         baseptr = strtok(tmp1,".");
         baseptr += getdmplst_baselen;
         sprintf(tmp3,"%s-%s",dmpname,baseptr);
         strcpy(dmpname,tmp3);
      } else {
         if (mode >= -1) {
            strcpy(dmpname,dmplist[ndumps - 1]->d_name);
         } else if (mode == -2) {
            for (i = ndumps - 1; i >= 0; i--) {
               baseptr = dmplist[i]->d_name + getdmplst_baselen;
               memset (tmp1,'\0',6);
               strncpy(tmp1,baseptr,5);
	       mycyc = atoi(tmp1);
	       if (mycyc < cycle) break;
            }
            if (i == -1) {
               strcpy(dmpname,dmplist[0]->d_name);
            } else {
               strcpy(dmpname,dmplist[i]->d_name);
            } 
         } else if (mode == -3) {
            for (i = 0; i < ndumps; i++) {
               baseptr = dmplist[i]->d_name + getdmplst_baselen;
               memset (tmp1,'\0',6);
               strncpy(tmp1,baseptr,5);
	       mycyc = atoi(tmp1);
	       if (mycyc > cycle) break;
            }
            if (i == ndumps) {
               strcpy(dmpname,dmplist[ndumps - 1]->d_name);
            } else {
               strcpy(dmpname,dmplist[i]->d_name);
            } 
         } 
      }
      for (i = 0; i < ndumps; i++) {
         FREEMEM(dmplist[i]);
      }
      FREEMEM(dmplist);
      strcpy(tmp1,dmpname);
   }
   if (ifparallel) {
      combcast(tmp1,MAXLINE,COM_CHAR,0);
      strcpy(dmpname,tmp1);
   }
}
void  getdmplst_numbers( char *dmpname, int mycyc , int *lenout, int **listout)
{
   char *me = "getdmplst_numbers";
   char msg[128];
   char tmp1[MAXLINE] ;
   char tmp2[MAXLINE] ;
   char *baseptr;
   int ndumps;
   int i;
   int *list;
   struct dirent **dmplist;
   strcpy(tmp1,"silo");
   getdmplst_base     = dmpname;
   getdmplst_exten    = tmp1;
   getdmplst_baselen  = strlen(dmpname);
   getdmplst_mdmpflag = 1;
   getdmplst_cyc      = mycyc;
   ndumps = scandir(".",&dmplist,&getdmplst_pruner,&alphasort); 
   if (ndumps == 0) {
      sprintf(msg,"Cannot find dump with kernel %s.",dmpname);      
      ctlerror(me,msg);
   }
   list = MALLOT(int,ndumps);
   for (i = 0; i < ndumps; i++) {
      strcpy(tmp1,dmplist[i]->d_name);
      baseptr = strtok(tmp1,"-");
      baseptr = strtok(NULL,"-");
      strncpy(tmp2,baseptr,4);
      list[i] = atoi(tmp2);
   }
   listout[0] = list;
   *lenout    = ndumps;
   for (i = 0; i < ndumps; i++) {
      FREEMEM(dmplist[i]);
   }
   FREEMEM(dmplist);
}
static int getdmplst_pruner( struct dirent *dentry) {
   char stmp[MAXLINE];	 
   char tmp2[MAXLINE];	 
   char *tmp;
   int len;    
   int mycyc;    
   len = strlen(dentry->d_name);
   if (len < (getdmplst_baselen + getdmplst_extenlen)) {
      return(0);
   }
   if (strncmp(getdmplst_base, dentry->d_name, getdmplst_baselen) != 0) {
      return(0);
   }
   tmp = &dentry->d_name[len - getdmplst_extenlen];
   if (strcmp(tmp, getdmplst_exten) != 0) {
      return(0);
   }
   tmp = dentry->d_name + getdmplst_baselen;
   if (isbeta(tmp) == 1) {
      return(0);
   }
   if (getdmplst_cyc >= 0) {
      strncpy(tmp2,dentry->d_name + getdmplst_baselen,5);
      mycyc = atoi(tmp2);
      if (mycyc != getdmplst_cyc) return(0);
   }
   return(1);
}
#endif
