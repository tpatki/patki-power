#include <stdio.h>
#include <string.h>
#include "irs.h"
#include "irsgen.h"
#include "irsrgst.h"
#include "AEStackElm.h"
#include "Command.h"
#include "Rgst.h"
#ifndef _POSIX_SOURCE
#define _POSIX_SOURCE 1
#endif
int getrgstdata(
  RGST_Datatype_t  dt,     
  char          *sym,    
  void          **ptr,   
  int            ptrlen) 
{
  char *me = "getrgstdata";
  char msg[256];
  int  i, objlen, copied_len, error;
  int    *outintptr = NULL, *rointptr = NULL;
  double *outdblptr = NULL, *rodblptr = NULL;
  RGST_Object_t   *ro;
  RGST_Datatype_t rodatatype;
  AEStackElm_t *ae_elm;
  Command_t *cp;
  if ((ro = rgst_get_RGST_Object_t(sym)) == NULL) {
    sprintf(msg,"object '%s' is not in the registry",sym);
    ctlerror(me,msg);
    return(-1);
  }
  if (   (ro->datatype != R_DOUBLE)
      && (ro->datatype != R_INT)
      && (ro->datatype != R_FUNCTION)) {
    sprintf(msg,"\n\tRegistry object '%s' is of type '%s'"
                "\n\tCan only get registry data of type 'int', 'double', or 'function'",
                sym, rgst_datatype_strs[ro->datatype]);
    ctlwarning(me,msg);
    return(-1);
  }
  if ((dt != R_DOUBLE) && (dt != R_INT)) {
    sprintf(msg,"\n\tThis routine currently only retrieves 'int' or 'double'"
                "\n\tCannot retrieve type '%s'",
                 rgst_datatype_strs[dt]);
    ctlwarning(me,msg);
    return(-1);
  }
  if (ro->datatype != dt) {
  }
  if (ro->datatype == R_FUNCTION) {
    cp = (Command_t *)ro->obj;
    (*(cp->handler))(cp);
    ae_elm = ae_stack_pop();
    if (ae_elm != NULL) {
      if (ae_elm->type == R_INT) {
        rointptr   = &(ae_elm->i_value);
        rodatatype = R_INT;
        objlen     = 1;
      }
      else if (ae_elm->type == R_INT_ARRAY) {
        rointptr   = ae_elm->i_array;
        rodatatype = R_INT;
        objlen     = ae_elm->len;
      }
      else if (ae_elm->type == R_DOUBLE) {
        rodblptr   = &(ae_elm->d_value);
        rodatatype = R_DOUBLE;
        objlen     = 1;
      }
      else if (ae_elm->type == R_DOUBLE_ARRAY) {
        rodblptr   = ae_elm->d_array;
        rodatatype = R_DOUBLE;
        objlen     = ae_elm->len;
      }
      else {
        ctlerror(me,logic_err);
      }
    }
    else {
      sprintf(msg,"function '%s' did not return an int or float (or array thereof)'",
                  ro->name);
      ctlnotice(me,msg);
      return(-1);
    }
  }
  else {
    if ((objlen = (int)rgst_get_ro_len(ro)) < 0) {
      return(-1);
    }
  }
  if (ptrlen < 0)   {
    if (ptrlen == -1) { ptrlen = objlen;  }
    else              { ptrlen = -ptrlen; }
    if (dt == R_DOUBLE) {
      if ((*(double **)ptr = MALLOT(double,ptrlen)) == NULL)
        ctlerror(me,gv_errmsg_memory);
    }
    else {
      if ((*(int **)ptr = MALLOT(int,ptrlen)) == NULL)
        ctlerror(me,gv_errmsg_memory);
    }
  }
  copied_len = MIN(ptrlen, objlen);
  if (dt == R_DOUBLE) outdblptr = *(double **)ptr;
  else                outintptr = *(int    **)ptr;
  if      (ro->datatype == R_FUNCTION) {
  }
  else if (ro->datatype == R_INT) {
    rodatatype = R_INT;
    if      (ro->nptrs == 0) rointptr =  (int *) ro->obj;
    else if (ro->nptrs == 1) rointptr = *(int **)ro->obj;
    else                     ctlerror(me,logic_err);
  }
  else if (ro->datatype == R_DOUBLE) {
    rodatatype = R_DOUBLE;
    if      (ro->nptrs == 0) rodblptr =  (double *) ro->obj;
    else if (ro->nptrs == 1) rodblptr = *(double **)ro->obj;
    else                     ctlerror(me,logic_err);
  }
  else {
    ctlerror(me,logic_err);
  }
  for (i=0; i<copied_len; i++) {
    if (dt == R_DOUBLE) {
      if      (rodatatype == R_DOUBLE) { outdblptr[i] = (double)rodblptr[i]; }
      else if (rodatatype == R_INT)    { outdblptr[i] = (double)rointptr[i]; }
      else                             { ctlerror(me,logic_err); }
    }
    else if (dt == R_INT) {
      if      (rodatatype == R_DOUBLE) { outintptr[i] = (int)rodblptr[i]; }
      else if (rodatatype == R_INT)    { outintptr[i] = (int)rointptr[i]; }
      else                             { ctlerror(me,logic_err); }
    }
    else {
      ctlerror(me,logic_err);
    }
  }
  return(copied_len);
}
