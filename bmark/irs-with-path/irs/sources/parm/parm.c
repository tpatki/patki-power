#include <stdio.h>                    
#include <stdlib.h>                     
#include "irs.h"              
#include "irsparm.h"
#include "irsrgst.h"
#include "Rgst.h"
int newparm(
  char *name,             
  void *parm,             
  RGST_Datatype_t type,   
  int  len)               
{
  char *me = "newparm";
  char msg[128], tstr[64];
  int  ierr;
  if      (type == R_INT)  {
    if ((ierr = rgst_add(name,"int",parm,NULL)) == 0) { 
      RGST_ADD_OBJECT_ATTR(name,"int_parm");
    }
  }
  else if (type == R_DOUBLE) {
    if ((ierr = rgst_add(name,"double",parm,NULL)) == 0) {
      RGST_ADD_OBJECT_ATTR(name,"double_parm");
    }
  }
  else if (type == R_CHAR) {
    if (len < 1) {
      sprintf(msg,"Length of char parm %s is < 1",name);
      ctlerror(me,msg);
    }
    if (strlen(((char *)parm)) > len) {
      sprintf(msg,"Parm %s is length %d, string %s is too long to fit",
                  name,len,(char*)parm);
      ctlerror(me,msg);
    }
    sprintf(tstr,"char [%d]",len);
    if ((ierr = rgst_add(name,tstr,parm,NULL)) == 0) {
      RGST_ADD_OBJECT_ATTR(name,"char_parm");
    }
  }
  else {
    ctlerror(me,logic_err);
  }
  if (ierr != 0) {
    sprintf(msg,"Error adding parm '%s' to the registry",name);
    ctlwarning(me,msg);
    return(-1);
  }
  return(0);
}
int  setparmi(
  char *name,   
  int  ival)    
{
  char *me = "setparmi";
  char msg[256];
  int  *iparm = NULL;
  if (  (rgst_check_for_obj(name)                != TRUE)
     || (RGST_QUERY_OBJECT_ATTR(name,"int_parm") != TRUE)) {
    sprintf(msg,"Can't set '%s' -- it is not an int parm",name);
    ctlnotice(me,msg);
    return(-1);
  }
  iparm = rgst_get(name);
  *iparm = ival;
  return(0);
}
int  setparmf(
  char  *name,   
  double dval)   
{
  char *me = "setparmf";
  char msg[256];
  double *dparm = NULL;
  if (  (rgst_check_for_obj(name)                   != TRUE)
     || (RGST_QUERY_OBJECT_ATTR(name,"double_parm") != TRUE)) {
    sprintf(msg,"Can't set '%s' -- it is not an double parm",name);
    ctlnotice(me,msg);
    return(-1);
  }
  dparm = rgst_get(name);
  *dparm = dval;
  return(0);
}
int  setparmc(
  char  *name,   
  char  *cval)   
{
  char *me = "setparmf";
  char msg[256];
  char *cparm = NULL;
  int  len;
  if (  (rgst_check_for_obj(name)                 != TRUE)
     || (RGST_QUERY_OBJECT_ATTR(name,"char_parm") != TRUE)) {
    sprintf(msg,"Can't set '%s' -- it is not a char parm",name);
    ctlnotice(me,msg);
    return(-1);
  }
  len = rgst_get_object_len(name);
  if (strlen(cval) > len) {
    sprintf(msg,"\n\tLength of parm '%s' is %d.  Cannot fit entire string"
                "\n\t'%s' into it -- will truncate to fit",
                name,len,cval);
  }
  cparm = rgst_get(name);
  memset(cparm,'\0', len);
  strncpy(cparm,cval,len);
  return(0);
}
