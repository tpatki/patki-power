#include <stdio.h>
#include <stdlib.h>
#include "irs.h"
#include "irsdmp.h"
#include "irsrgst.h"
#include "Rgst.h"
#ifdef SILO
int wtparms(DBfile *idbid)    
{
  char *me = "wtparms";
  char  **parm_names = NULL, *parm_chars = NULL, *char_ptr = NULL;
  int     i, num_ints, num_dbls, num_strs, num_parms, num_vals, num_chars;
  int    *parm_lens  = NULL, *parm_ints = NULL;
  double *parm_doubles;
  void   *parm_vals  = NULL;
  RGST_AttributeElem_t *rgst_elm = NULL;
  if (DBMkdir( idbid,"/Global/Parms") != 0) ctlerror(me,gv_errmsg_DBMkDir);
  if (DBSetDir(idbid,"/Global/Parms") != 0) ctlerror(me,gv_errmsg_DBSetDir);
  num_ints = RGST_NUM_OBJECTS_WITH_ATTR("int_parm");
  num_dbls = RGST_NUM_OBJECTS_WITH_ATTR("double_parm");
  num_strs = RGST_NUM_OBJECTS_WITH_ATTR("char_parm");
  num_parms = MAX(num_ints, num_dbls);
  num_parms = MAX(num_parms,num_strs);
  num_vals  = MAX(num_ints * sizeof(int), num_dbls * sizeof(double));
  num_vals  = MAX(num_vals, num_strs * (MAXWORD + 1));
  parm_names    = ALLOT(char *, num_parms);
  parm_lens     = ALLOT(int,    num_parms);
  parm_vals     = ALLOT(char,   num_vals);
  parm_ints     = (int *)parm_vals;
  parm_doubles  = (double *)parm_vals;
  parm_chars    = (char *)parm_vals;
  rgst_elm  = RGST_LIST_OBJECTS_WITH_ATTR("int_parm");
  for (i=0; i<num_ints; i++) {
    if (rgst_elm == NULL) ctlerror(me,logic_err);
    parm_names[i] = strsave(rgst_elm->name);
    parm_lens [i] = 1;
    parm_ints [i] = *(int *)(rgst_elm->rgst_obj->obj);
    rgst_elm = rgst_elm->next;
  }
  if (DBPutCompoundarray(idbid, "int_parms", parm_names,
                         parm_lens, num_ints, parm_ints, num_ints,
                         DB_INT, NULL) != 0) {
    ctlerror(me,gv_errmsg_DBPutCompoundarray);
  }
  rgst_elm = RGST_LIST_OBJECTS_WITH_ATTR("double_parm");
  for (i=0; i<num_dbls; i++) {
    if (rgst_elm == NULL) ctlerror(me,logic_err);
    FREEMEM(parm_names[i]);
    parm_names  [i] = strsave(rgst_elm->name);
    parm_lens   [i] = 1;
    parm_doubles[i] = *(double *)(rgst_elm->rgst_obj->obj);
    rgst_elm = rgst_elm->next;
  }
  if (DBPutCompoundarray(idbid, "double_parms", parm_names,
                         parm_lens, num_dbls, parm_doubles, num_dbls,
                         DB_DOUBLE, NULL) != 0) {
    ctlerror(me,gv_errmsg_DBPutCompoundarray);
  }
  rgst_elm = RGST_LIST_OBJECTS_WITH_ATTR("char_parm");
  num_chars = 0;
  for (i=0; i<num_strs; i++) {
    if (rgst_elm == NULL) ctlerror(me,logic_err);
    char_ptr = (char *)(rgst_elm->rgst_obj->obj);
    FREEMEM(parm_names[i]);
    parm_names[i] = strsave(rgst_elm->name);
    parm_lens [i] = strlen(char_ptr) + 1;
    memset(&(parm_chars[num_chars]),'\0',strlen(char_ptr) + 1);
    strcpy(&(parm_chars[num_chars]),char_ptr);
    num_chars = num_chars + strlen(char_ptr) + 1;
    rgst_elm = rgst_elm->next;
  }
  if (DBPutCompoundarray(idbid, "char_parms", parm_names,
                         parm_lens, num_strs, parm_chars, num_chars,
                         DB_CHAR, NULL) != 0) {
    ctlerror(me,gv_errmsg_DBPutCompoundarray);
  }
  for (i=0; i<num_parms; i++) {
    FREEMEM(parm_names[i]);
  }
  FREEMEM(parm_names);
  FREEMEM(parm_lens);
  FREEMEM(parm_vals);
  return(0);
}
#endif
