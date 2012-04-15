#include <stdio.h>
#include <string.h>
#include "irs.h"
#include "irsgen.h"
#include "irsrgst.h"
#include "ProblemArray.h"
#include "Rgst.h"
#ifndef _POSIX_SOURCE
#define _POSIX_SOURCE 1
#endif
int getarg(
  char *type,       
  void *ptr,        
  int  ptrlen)      
{
  char *me = "getarg";
  char *errmsg1 = "ptr requested, len arg will be ignored";
  char msg[256], sym[128];
  int  ifun ;
  int  i, len, ptr_requested, copied_len;
  double *darg = NULL;         
  double *dptr;
  int    *iptr;
  RGST_Datatype_t expected_type;
  if (ptrlen < 0) ctlerror(me,logic_err);
  if      (strcmp(type,"int")      == 0) {
    expected_type = R_INT;
    ptr_requested = FALSE;
  }
  else if (strcmp(type,"double")   == 0) {
    expected_type = R_DOUBLE;
    ptr_requested = FALSE;
  }
  else if (strcmp(type,"int *")    == 0) {
    expected_type = R_INT;
    ptr_requested = TRUE;
    if (ptrlen !=  0) ctlnotice(me,errmsg1);
    ptrlen = 1;                    \
  }
  else if (strcmp(type,"double *") == 0) {
    expected_type = R_DOUBLE;
    ptr_requested = TRUE;
    if (ptrlen != 0) ctlnotice(me,errmsg1);
    ptrlen = 1;
  }
  else {
    sprintf(msg,"type '%s' is bad--cannot get arg of that type",type);
    ctlwarning(me,msg);
    return(-1);
  }
  peekc(sym) ;
  if (!isalpha(sym[0])) {
    len = getflst(&darg, -ptrlen);
  } else {
    geta(sym);
    if ((ifun = isargfun(sym)) >= 0) {
      len = doarg_fun_alloc(ifun, &darg, -ptrlen);
    } else if (rgst_check_for_obj(sym) == TRUE) {
      ProblemArray_t *prb = ProblemArray_find(sym,NULL);
      if (prb != NULL) {
        len = getfpaa_rgst(sym, &darg, -ptrlen);
      } else {
        len = getrgstdata(R_DOUBLE, sym, (void **)&darg, -ptrlen);
      }
    } else {
      sprintf(msg,"\n\tDo not know how to get argument starting at symbol '%s'"
                  "\n\tIt is not a number list, or a known function, or"
                  "\n\tan object in the registry",
                  sym);
      ctlwarning(me,msg);
      len = -1;
    }
  }
  if (len <= 0) {
    return(len);
  }
  if (ptr_requested == TRUE) {
    copied_len = len;
  }
  else {
    copied_len = MIN(len,ptrlen);
    if (len > ptrlen) {
      sprintf(msg,"\n\tjust read %d numbers from input.  Calling routine"
                  "\n\tonly expected a max of %d numbers"
                  "\n\t%d numbers have just been lost from the input",
                  len,ptrlen,len-ptrlen);
      ctlwarning(me,msg);
    }
  }
  if (expected_type == R_INT) {
    if (ptr_requested == TRUE) {
      iptr = ALLOT(int,copied_len);
      for (i=0; i<copied_len; i++) iptr[i] = (int)darg[i];
      *(int **)ptr = iptr;
    }
    else {
      iptr = (int *)ptr;
      for (i=0; i<copied_len; i++) iptr[i] = (int)darg[i];
    }
    FREEMEM(darg);
  }
  else if (expected_type == R_DOUBLE) {
    if (ptr_requested == TRUE) {
      *(double **)ptr = darg;
    }
    else {
      dptr = (double *)ptr;
      memcpy(dptr,darg,sizeof(double) * copied_len);
      FREEMEM(darg);
    }
  }
  else {
    ctlerror(me,logic_err);
    copied_len = -1;
  }
  return(copied_len);
}
