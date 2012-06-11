#include <stdio.h>
#include <string.h>
#include "irs.h"
#include "irs.h"
#include "Hash.h"
#include "Rgst.h"
#include "irsrgst.h"
#ifndef _POSIX_SOURCE
#define _POSIX_SOURCE 1
#endif
char **rgst_list_objs_by_type(
  int *num_objs,                
  char *type)                   
{
  char *me = "rgst_list_objs_by_type";
  char type_str[128]; 
  char **names = NULL;
  HashElm_t **he_list;
  int i, real_num_objs, my_num_objs;
  int nptrs, myndims, dims[3];
  strncpy(type_str,type,127);       
  rgst_get_dims_of_type(type_str,&nptrs,&myndims,&dims[0]);
  he_list = hash_get_elm_list(&my_num_objs, type_str, rgst_objs_hash_tbl);
  if (he_list == NULL) return(NULL);
  if (my_num_objs == 0) {
     FREEMEM(he_list);
     *num_objs = 0;
     return(NULL);
  }
  hash_sort_array(he_list,my_num_objs);
  if ((names = ALLOT(char *, my_num_objs)) == NULL) ctlerror(me,gv_errmsg_memory);
  real_num_objs = 0;
  for (i=0; i<my_num_objs; i++) {
    if (rgst_get_t(he_list[i]->name,type) != NULL) {
      names[real_num_objs] = strsave(he_list[i]->name);
      real_num_objs++;
    }
  }       
  FREEMEM(he_list);
  *num_objs = real_num_objs;
  return(names);
}
