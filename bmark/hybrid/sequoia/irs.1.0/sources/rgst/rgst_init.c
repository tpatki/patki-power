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
char *rgst_datatype_strs[NUM_RGST_Datatype_t] = {
  "char",          "unsigned char",
  "short",         "unsigned short",
  "short int",     "unsigned short int",
  "int",           "unsigned int",
  "long",          "unsigned long",
  "long int",      "unsigned long int",
  "long long",     "unsigned long long",
  "long long int", "unsigned long long int",
  "float",  
  "double",        
  "void",
  "struct", 
  "ctype typedef", 
  "enum typedef", 
  "struct typedef",
  "function",
  "int array",
  "double array"
};
size_t rgst_datatype_sizes[R_VOID] = {
  sizeof(char),          sizeof(unsigned char),
  sizeof(short),         sizeof(unsigned short),
  sizeof(short int),     sizeof(unsigned short int),
  sizeof(int),           sizeof(unsigned int),
  sizeof(long),          sizeof(unsigned long),
  sizeof(long int),      sizeof(unsigned long int),
  sizeof(long long),     sizeof(unsigned long long),
  sizeof(long long int), sizeof(unsigned long long int),
  sizeof(float), 
  sizeof(double)
};

RGST_Datatype_t rgst_types_silo_knows_of[NUM_TYPES_SILO_KNOWS_OF] =
  { R_SHORT, R_INT, R_LONG, R_FLOAT, R_DOUBLE, R_CHAR};

#ifdef SILO
DBdatatype    rgst_silo_types[NUM_TYPES_SILO_KNOWS_OF] =
  { DB_SHORT, DB_INT, DB_LONG, DB_FLOAT, DB_DOUBLE, DB_CHAR};
#endif

HashTable_t *rgst_types_hash_tbl      = NULL;

HashTable_t *rgst_objs_hash_tbl       = NULL;

HashTable_t *rgst_field_ndx_hash_tbl  = NULL;

int rgst_init(void)
{
  char *me = "rgst_init";
  int i;
  RGST_BasicCTypeDef_t *c_type;
  RGST_Function_t          *fn;
  rgst_types_hash_tbl      = hash_tbl_create(61, NULL);
  rgst_objs_hash_tbl       = hash_tbl_create(2039, NULL);
  rgst_field_ndx_hash_tbl  = hash_tbl_create(1021, NULL);
  if ((rgst_types_hash_tbl     == NULL)  || 
      (rgst_objs_hash_tbl      == NULL)  ||
      (rgst_field_ndx_hash_tbl == NULL)) {
    return(-1);
  }
  for (i=0; i<R_VOID; i++) {
    if ((c_type = ALLOT(RGST_BasicCTypeDef_t, 1)) == NULL)
      ctlerror(me,gv_errmsg_memory);
    c_type->type      = (RGST_Datatype_t) i;
    c_type->type_size = rgst_datatype_sizes[i];
    hash_add(rgst_datatype_strs[i],
             rgst_datatype_strs[i],
             c_type, rgst_types_hash_tbl);
  }
  if ((fn = ALLOT(RGST_Function_t, 1)) == NULL)
    ctlerror(me,gv_errmsg_memory);
  hash_add(rgst_datatype_strs[R_FUNCTION],
           rgst_datatype_strs[R_FUNCTION],
           fn, rgst_types_hash_tbl);
  rgst_add_h_file_types();
  rgst_types_hash_tbl->name      = strsave(RGST_TYPES_HT_NAME);
  rgst_objs_hash_tbl->name       = strsave(RGST_OBJS_HT_NAME);
  rgst_field_ndx_hash_tbl->name  = strsave(RGST_Field_t_NDX_HT_NAME);
  rgst_add(rgst_types_hash_tbl->name,     "HashTable_t *", &rgst_types_hash_tbl,     NULL);
  rgst_add(rgst_objs_hash_tbl->name,      "HashTable_t *", &rgst_objs_hash_tbl,      NULL);
  rgst_add(rgst_field_ndx_hash_tbl->name, "HashTable_t *", &rgst_field_ndx_hash_tbl, NULL);
  return(0);
}
