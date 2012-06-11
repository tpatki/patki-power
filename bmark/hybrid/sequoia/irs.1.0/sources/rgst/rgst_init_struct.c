#include <stdio.h>
#include <string.h>
#include "irs.h"
#include "irs.h"
#include "irsrgst.h"
#include "Command.h"
#include "Hash.h"
#include "Rgst.h"
#ifndef _POSIX_SOURCE
#define _POSIX_SOURCE 1
#endif
int rgst_init_struct(
  char *type,   
  void *ptr)    
{
  char *me = "rgst_init_struct";
  char msg[256], routine_name[128];
  int  i;
  long j;
  long field_nvals;
  RGST_StructTypeDef_t *sd = NULL;   
  RGST_Field_t          *fd = NULL;   
  void                *fp = NULL;   
  void *generic_ptr = NULL;
  Command_t *cp = NULL;
  char                   *charptr;             
  unsigned char          *ucharptr;            
  short                  *shortptr;
  unsigned short         *ushortptr;
  short int              *shortintptr;
  unsigned short int     *ushortintptr;
  int                    *intptr;
  unsigned int           *uintptr;
  long                   *longptr;
  unsigned long          *ulongptr;
  long int               *longintptr;
  unsigned long int      *ulongintptr;
  long long              *longlongptr;
  unsigned long long     *ulonglongptr;
  long long int          *longlongintptr;
  unsigned long long int *ulonglongintptr;
  float                  *floatptr;
  double                 *doubleptr;
  GENERIC_ENUM_TYPEDEF   *enumptr;
  if (type == NULL) ctlerror(me,logic_err);
  sd = (RGST_StructTypeDef_t *)rgst_get_td_defn(type, R_STRUCT_TYPEDEF, NULL);
  if (sd == NULL) ctlerror(me,logic_err);
  cp = build_proc_name(sd->name,"init",routine_name); 
  if (cp != NULL) {
    if (((*(cp->proc))(ptr)) != 0) {
      sprintf(msg,"'%s' initialization routine returned error code",routine_name);
      ctlwarning(me,msg);
    }
    return(0);
  }
  for (i=0; i<sd->num_fields; i++) {
    fd = &(sd->fields[i]);
    fp = rgst_get_field_addr(ptr, sd->name, fd->name, NULL);
    if (fd->nptrs > 0) {
      generic_ptr = (void *)fp;
      generic_ptr = NULL;
    }
    else {
      if (rgst_get_nelms_in_field(ptr, sd, fd, NULL, NULL, &field_nvals) != 0)
        ctlerror(me,logic_err);
      switch(fd->type) {
        case R_CHAR:
          memset(fp, '\0', field_nvals);
          break;
        case R_UNSIGNED_CHAR:
          ucharptr = fp;
          for (j=0; j<field_nvals; j++) ucharptr[j] = (unsigned char)0;
          break;
        case R_SHORT:
          shortptr = fp;
          for (j=0; j<field_nvals; j++) shortptr[j] = 0;
          break;
        case R_UNSIGNED_SHORT:
          ushortptr = fp;
          for (j=0; j<field_nvals; j++) ushortptr[j] = 0;
          break;
        case R_SHORT_INT:
          shortintptr = fp;
          for (j=0; j<field_nvals; j++) shortintptr[j] = 0;
          break;
        case R_UNSIGNED_SHORT_INT:
          ushortintptr = fp;
          for (j=0; j<field_nvals; j++) ushortintptr[j] = 0;
          break;
        case R_INT:
          intptr = fp;
          for (j=0; j<field_nvals; j++) intptr[j] = 0;
          break;
        case R_UNSIGNED_INT:
          uintptr = fp;
          for (j=0; j<field_nvals; j++) uintptr[j] = 0;
          break;
        case R_LONG:
          longptr = fp;
          for (j=0; j<field_nvals; j++) longptr[j] = 0;
          break;
        case R_UNSIGNED_LONG:
          ulongptr = fp;
          for (j=0; j<field_nvals; j++) ulongptr[j] = 0;
          break;
        case R_LONG_INT:
          longintptr = fp;
          for (j=0; j<field_nvals; j++) longintptr[j] = 0;
          break;
        case R_UNSIGNED_LONG_INT:
          ulongintptr = fp;
          for (j=0; j<field_nvals; j++) ulongintptr[j] = 0;
          break;
        case R_LONG_LONG:
          longlongptr = fp;
          for (j=0; j<field_nvals; j++) longlongptr[j] = 0;
          break;
        case R_UNSIGNED_LONG_LONG:
          ulonglongptr = fp;
          for (j=0; j<field_nvals; j++) ulonglongptr[j] = 0;
          break;
        case R_LONG_LONG_INT:
          longlongintptr = fp;
          for (j=0; j<field_nvals; j++) longlongintptr[j] = 0;
          break;
        case R_UNSIGNED_LONG_LONG_INT:
          ulonglongintptr = fp;
          for (j=0; j<field_nvals; j++) ulonglongintptr[j] = 0;
          break;
        case R_FLOAT:
          floatptr = fp;
          for (j=0; j<field_nvals; j++) floatptr[j] = 0.0;
          break;
        case R_DOUBLE:
          doubleptr = fp;
          for (j=0; j<field_nvals; j++) doubleptr[j] = 0.0;
          break;
        case R_STRUCT_TYPEDEF:
          if (rgst_init_struct(fd->td_name,fp) != 0) ctlerror(me,logic_err);
          break;
        default:
          ctlerror(me,logic_err);
      }
    }
  }
  return(0);
}
