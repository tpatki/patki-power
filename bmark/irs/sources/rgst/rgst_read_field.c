#include <stdio.h>
#include <stdlib.h>
#include "irs.h"
#include "irsrgst.h"
#include "Rgst.h"
#ifdef SILO
int rgst_read_field(
  DBfile *idbid,        
  char *field)          
{
  char  *me = "rgst_read_field";
  char   msg[256], struct_name[STRLEN], array_name[STRLEN];
  int    i, ndx, num, index, *intptr;
  DBtoc *toc = NULL;
  DBcompoundarray *comparray;
  toc = DBGetToc(idbid);
  for (i=0; i<toc->nvar; i++) {
    if (strcmp(toc->var_names[i],"struct_name") == 0) { break; }
  }
  if (i >= toc->nvar) {
    ctlwarning(me,"Program is not in a directory containing a structure"
                  "written by the registry");
    return(-1);
  }
  memset(struct_name,'\0',STRLEN);
  if (DBReadVar(idbid,"struct_name",struct_name) != 0) {
    ctlwarning(me,gv_errmsg_DBReadVar);
    return(-1);
  }
  sprintf(array_name,"%s_int",struct_name);
  for (i=0; i<toc->narrays; i++) {
    if (strcmp(array_name,toc->array_names[i]) == 0) { break; }
  }
  if (i >= toc->narrays) {
    ctlwarning(me,"Structure contains no ints to be read");
  }
  if ((comparray = DBGetCompoundarray(idbid,array_name)) == NULL) {
    ctlwarning(me,gv_errmsg_DBGetCompoundarray);
    return(-1);
  }
  for (ndx=0; ndx<comparray->nelems; ndx++) {
    if (strcmp(comparray->elemnames[ndx],field) == 0) { break; }
  }
  if (ndx >= comparray->nelems) {
    sprintf(msg,"\n\t'%s' is not a field of structure '%s'"
                "\n\tor if it is, it was not written to the dump",
                field,struct_name);
    ctlwarning(me,msg);
    return(-1);
  }
  if (comparray->elemlengths[ndx] != 1) {
    sprintf(msg,"'%s' is an array of %d ints, it must be a scalar",
            field,comparray->elemlengths[ndx]);
    ctlwarning(me,msg);
    return(-1);
  }
  index = 0;
  intptr = (int *)comparray->values;
  for (i=0; i<ndx; i++) {
    index = index + comparray->elemlengths[i];
  }
  if (index >= comparray->nvalues) { ctlerror(me,logic_err); }
  num = intptr[index];
  return(num);
}
#endif
