#include <stdio.h>
#include <stdlib.h>
#include "irs.h"
#include "irsdmp.h"
#include "irsparm.h"
#include "irsrgst.h"
#ifdef SILO
int rdparms(DBfile *idbid)    
{
  char *me = "rdparms";
  char startdir[256];
  int i, ndx;
  int  *ints = NULL;
  double *doubles = NULL;
  char *chars = NULL, *str = NULL;
  DBcompoundarray *comparray;
  if (DBGetDir(idbid,startdir) != 0)        ctlerror(me,gv_errmsg_DBGetDir);
  if (DBSetDir(idbid,"/Global/Parms") != 0) ctlerror(me,gv_errmsg_DBSetDir);
  comparray = DBGetCompoundarray(idbid, "int_parms");
  if (  (comparray == NULL)
     || (comparray->datatype != DB_INT) ) {
    ctlerror(me,logic_err);
  }
  ints = (int *)comparray->values;
  for (i=0; i<comparray->nelems; i++) {
    if (comparray->elemlengths[i] != 1) { ctlerror(me,logic_err); }
    setparmi(comparray->elemnames[i],ints[i]);
  }
  DBFreeCompoundarray(comparray);
  comparray = DBGetCompoundarray(idbid, "double_parms");
  if (  (comparray == NULL)
     || (comparray->datatype != DB_DOUBLE) ) {
    ctlerror(me,logic_err);
  }
  doubles = (double *)comparray->values;
  for (i=0; i<comparray->nelems; i++) {
    if (comparray->elemlengths[i] != 1) { ctlerror(me,logic_err); }
    setparmf(comparray->elemnames[i],doubles[i]);
  }
  DBFreeCompoundarray(comparray);
  comparray = DBGetCompoundarray(idbid, "char_parms");
  if (  (comparray == NULL)
     || (comparray->datatype != DB_CHAR) ) {
    ctlerror(me,logic_err);
  }
  chars = (char *)comparray->values;
  ndx = 0;
  for (i=0; i<comparray->nelems; i++) {
    setparmc(comparray->elemnames[i], &(chars[ndx]) );
    ndx = ndx + comparray->elemlengths[i];
  }
  DBFreeCompoundarray(comparray);
  if (DBSetDir(idbid, startdir)  != 0) ctlerror(me,gv_errmsg_DBSetDir);
  return(0);
}
#endif
