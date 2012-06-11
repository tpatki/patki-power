#include <stdio.h>
#include <string.h>

#ifdef SILO
#include <silo.h>
#endif

#include "irs.h"
#include "irsdefs.h"
#include "irs.h"
#include "irsrgst.h"
#include "Rgst.h"
#ifndef _POSIX_SOURCE
#define _POSIX_SOURCE 1
#endif
#define MAX_NAMELEN  64
#define MAX_FIELDS  256

#ifdef SILO
static int fill_fields_from_buffer(
  RGST_StructTypeDef_t *sd,
  RGST_Field_t *fd,
  void *buff,
  RGST_Datatype_t dump_type,
  int  dump_nvals,
  int  spp_num,
  int  *nelms,
  void **spp);
void *rgst_read_linked_list (
  DBfile *idbid,       
  char *dir_name,      
  char *struct_name)   
{
  char *me = "rgst_read_linked_list";
  char msg[128];
  int i, num_structs;
  void **ptr_array, *head_ptr, **next;
  RGST_StructTypeDef_t *sd = NULL; 
  sd = (RGST_StructTypeDef_t *)rgst_get_td_defn(struct_name,R_STRUCT_TYPEDEF,NULL);
  if (sd == NULL) {
    sprintf(msg,"type '%s' is now a registered data type",struct_name);
    ctlwarning(me,msg);
    return(NULL);
  }
  if (rgst_get_ds_field_ndx(sd,"next") < 0) {
    sprintf(msg,"type '%s' does not contain a 'next' field, so it is "
                "not a linked list",struct_name);
    ctlwarning(me,msg);
    return(NULL);
  }
  ptr_array = rgst_read_struct_array(idbid,dir_name,struct_name,&num_structs);
  if (ptr_array == NULL) return (NULL);
  for (i=0; i<num_structs - 1; i++) {
    next  = rgst_get_field_addr(ptr_array[i], struct_name, "next", NULL);
    *next = ptr_array[i+1];
  }
  next  = rgst_get_field_addr(ptr_array[num_structs-1], struct_name, "next", NULL);
  *next = NULL;
  head_ptr = ptr_array[0];
  FREEMEM(ptr_array);
  return(head_ptr);
}
void **rgst_read_struct_array (
  DBfile *idbid,       
  char *dir_name,      
  char *struct_name,   
  int  *num_structs)   
{
  char *me = "rgst_read_struct_array";
  char startdir[STRLEN], msg[STRLEN], silo_struct_name[STRLEN];
  int  i, j, ierr, spp_num, type_ndx, dump_type, dump_nvals;
  int *nelms = NULL;
  RGST_StructTypeDef_t *sd = NULL; 
  RGST_Field_t *fd = NULL;         
  DBtoc *toc = NULL;
  void  *buffer = NULL;            
  void **spp = NULL;               
  *num_structs = 0;
  sd = (RGST_StructTypeDef_t *)rgst_get_td_defn(struct_name,R_STRUCT_TYPEDEF,NULL);
  if (sd  == NULL) ctlerror(me,logic_err);
  if (DBGetDir(idbid, startdir) != 0) { ctlerror(me,gv_errmsg_DBGetDir); }
  DBShowErrors(DB_NONE, NULL);
  ierr = DBSetDir(idbid, dir_name);
  DBShowErrors(DB_TOP, NULL);
  if (ierr != 0) {
#ifdef DEBUG
    ifdefd out to allow for backwards file compatiblity without 
    a bunch of notices.
    sprintf(msg,"\n\tDirectory '%s' does not exist in silo file"
                "\n\tbypassing read of '%s' data structures",
                dir_name,struct_name);
    ctlnotice(me,msg);
#endif
    if (DBSetDir(idbid, startdir) != 0) { ctlerror(me,gv_errmsg_DBSetDir); }
    return(NULL);
  }
  memset(silo_struct_name,'\0',STRLEN);
  DBShowErrors(DB_NONE, NULL);
  ierr = DBReadVar(idbid,"struct_name",silo_struct_name);
  DBShowErrors(DB_TOP, NULL);
  if (ierr != 0) {
#ifdef DEBUG
    ifdefd out to allow for backwards file compatiblity without 
    a bunch of notices.
    sprintf(msg,"\n\tDirectory '%s' was not written using the "
                "rgst_write_struct_array routine"
                "\n\tbypassing read of '%s' data strcutures",
                 dir_name,struct_name);
    ctlnotice(me,msg);
#endif
    if (DBSetDir(idbid, startdir) != 0) { ctlerror(me,gv_errmsg_DBSetDir); }
    return(NULL);
  }
  if (strcmp(silo_struct_name,struct_name) != 0) {
    sprintf(msg,"\n\tWrong directory!  Programmer tried to read structure type"
                "\n\t'%s' but directory '%s' contains structure type '%s'",
                struct_name,dir_name,silo_struct_name);
    ctlwarning(me,msg);
    if (DBSetDir(idbid, startdir) != 0) { ctlerror(me,gv_errmsg_DBSetDir); }
    return(NULL);
  }
  if (DBReadVar(idbid,"num_structs",&spp_num) != 0) {
    ctlerror(me,logic_err);
  }
  *num_structs = spp_num;
  if (spp_num == 0) {
    return(NULL);
  }
  toc = DBGetToc(idbid);
  toc = copy_toc(toc);
  spp = ALLOT(void *, spp_num);
  if (spp == NULL) { ctlerror(me,gv_errmsg_memory); }
  for (i=0; i<spp_num; i++) {
    spp[i] = rgst_construct(R_STRUCT, struct_name, 1);
  }
  for (i=0; i<sd->num_fields; i++) {
    fd = &(sd->fields[i]);
    if (RGST_QUERY_FIELD_ATTR(sd->name,fd->name,"dump") == TRUE) {
      for (j=0; j<NUM_TYPES_SILO_KNOWS_OF; j++) {
       if (fd->type == rgst_types_silo_knows_of[j]) break;
      }
      if (j >= NUM_TYPES_SILO_KNOWS_OF) {
        sprintf(msg,"Can't read field type '%s'",rgst_datatype_strs[fd->type]);
        ctlerror(me,msg);
      }
      type_ndx = j;
      for (j=0; j<toc->nvar; j++) {
        if (strcmp(fd->name,toc->var_names[j]) == 0) break;
      }
      if (j >= toc->nvar) {
        sprintf(msg,"\n\tBypassing read of field '%s' for structure '%s'"
                    "\n\tThis field was not written to the dump",
                    fd->name,sd->name);
        ctlnotice(me,msg);
      }
      else {
        sprintf(msg,"%s_nelms",fd->name);
        nelms = ALLOT(int, spp_num);
        if (DBReadVar(idbid, msg, nelms) != 0) ctlerror(me,logic_err);
        sprintf(msg,"%s_type",fd->name);
        if (DBReadVar(idbid, msg, &dump_type) != 0) ctlerror(me,logic_err);
        sprintf(msg,"%s_nvals",fd->name);
        if (DBReadVar(idbid, msg, &dump_nvals) != 0) ctlerror(me,logic_err);
        if (dump_nvals > 0) {
          buffer = malloc(rgst_datatype_sizes[dump_type] * dump_nvals);
          if (buffer == NULL) { ctlerror(me,gv_errmsg_memory); }
          if (DBReadVar(idbid,fd->name,buffer) != 0) {
            ctlerror(me,gv_errmsg_DBReadVar);
          }
          fill_fields_from_buffer(sd, fd,  buffer, (RGST_Datatype_t)dump_type,
                                  dump_nvals, spp_num, nelms, spp);
          FREEMEM(buffer);
        }
        FREEMEM(nelms);
      }
    } 
  }   
  toc = free_toc(toc);
  return(spp);
}
static int fill_fields_from_buffer(
  RGST_StructTypeDef_t *sd,       
  RGST_Field_t *fd,               
  void *buff,                     
  RGST_Datatype_t dump_type,      
  int  dump_nvals,                
  int  spp_num,                   
  int *nelms,                     
  void **spp)                     
{
  char *me = "fill_fields_from_buffer";
  char msg[256];
  int  jj, nvals = 0;
  long ii, field_nvals;
  void   *sp = NULL;                   
  void   *fp;                          
  void   *fdat;                        
  char   *fdat_char,   *buff_char;     
  short  *fdat_short,  *buff_short;    
  int    *fdat_int,    *buff_int;      
  long   *fdat_long,   *buff_long;     
  float  *fdat_float,  *buff_float;    
  double *fdat_double, *buff_double;
  if (dump_nvals == 0) { return(0); }
  buff_short  = (short  *)buff;
  buff_int    = (int    *)buff;
  buff_long   = (long   *)buff;
  buff_float  = (float  *)buff;
  buff_double = (double *)buff;
  buff_char   = (char   *)buff;
  if (   (fd->type  == R_CHAR)
      && (fd->ndims == 0)
      && (fd->nptrs == 1)
      && (fd->array_size_type == NUM_ARRAY_SIZE_ENUM)) {
    for (jj=0; jj<spp_num; jj++) {
      sp = spp[jj];
      fp = rgst_get_field_addr(sp, sd->name, fd->name, NULL);
      if (fp == NULL) ctlerror(me, logic_err);
      if (nelms[jj] > 0) {
        if ((nvals + nelms[jj]) >= dump_nvals) ctlerror(me,logic_err);
        fdat_char = ALLOT(char, nelms[jj] + 1);
        memset(fdat_char,'\0',nelms[jj] + 1);
        buff_char   = &((char   *)buff)[nvals];
        strncpy(fdat_char, buff_char, nelms[jj]);
        *(char **)fp = fdat_char;
        nvals += nelms[jj];
      }
      else {
        *(char **)fp = NULL;
      }
    }
    nvals++; 
    if (nvals != dump_nvals) ctlerror(me,logic_err);
  }
  else if (   (fd->nptrs == 0)
          || ((fd->nptrs == 1) && (fd->ndims == 0)) ) {
    for (jj=0; jj<spp_num; jj++) {
      sp = spp[jj];
      fp = rgst_get_field_addr(sp, sd->name, fd->name, NULL);
      if (fp == NULL) ctlerror(me, logic_err);
      if (nelms[jj] > 0) {
        if (fd->nptrs == 0) {
          fdat = fp;
        }
        else {
         fdat = ALLOT(char, (rgst_datatype_sizes[fd->type] * nelms[jj]));
         *((void **)fp) = fdat;
        }
        if (rgst_get_nelms_in_field(sp, sd, fd, NULL, NULL, &field_nvals) != 0) {
          ctlerror(me,logic_err);
        }
        if (field_nvals != nelms[jj]) {
          sprintf(msg,"\n\tSilo file says field '%s' of struct '%s' has %d elements"
                      "\n\tCurrent registry says it has %d elements"
                      "\n\tWhich is correct ?",
                      fd->name,sd->name,nelms[jj],(int)field_nvals);
          ctlerror(me,msg);
        }
        fdat_short  = fdat;
        fdat_int    = fdat;
        fdat_long   = fdat;
        fdat_float  = fdat;
        fdat_double = fdat;
        fdat_char   = fdat;
        buff_short  = &((short  *)buff)[nvals];
        buff_int    = &((int    *)buff)[nvals];
        buff_long   = &((long   *)buff)[nvals];
        buff_float  = &((float  *)buff)[nvals];
        buff_double = &((double *)buff)[nvals];
        buff_char   = &((char   *)buff)[nvals];
        if ((nvals + field_nvals) > dump_nvals) { ctlerror(me,logic_err); }
        switch (fd->type) {
        case R_SHORT:
          if      (dump_type == R_SHORT)  memcpy(fdat_short, buff_short, sizeof(short)*field_nvals);
          else if (dump_type == R_INT)    for (ii=0; ii<field_nvals; ii++) fdat_short[ii] = (short)buff_int[ii];
          else if (dump_type == R_LONG)   for (ii=0; ii<field_nvals; ii++) fdat_short[ii] = (short)buff_long[ii];
          else if (dump_type == R_FLOAT)  for (ii=0; ii<field_nvals; ii++) fdat_short[ii] = (short)buff_float[ii];
          else if (dump_type == R_DOUBLE) for (ii=0; ii<field_nvals; ii++) fdat_short[ii] = (short)buff_double[ii];
          else if (dump_type == R_CHAR)   for (ii=0; ii<field_nvals; ii++) fdat_short[ii] = (short)buff_char[ii];
          else ctlerror(me,logic_err);
          break;
        case R_INT:
          if      (dump_type == R_INT)    memcpy(fdat_int, buff_int, sizeof(int)*field_nvals);
          else if (dump_type == R_SHORT)  for (ii=0; ii<field_nvals; ii++) fdat_int[ii] = (int)buff_short[ii];
          else if (dump_type == R_LONG)   for (ii=0; ii<field_nvals; ii++) fdat_int[ii] = (int)buff_long[ii];
          else if (dump_type == R_FLOAT)  for (ii=0; ii<field_nvals; ii++) fdat_int[ii] = (int)buff_float[ii];
          else if (dump_type == R_DOUBLE) for (ii=0; ii<field_nvals; ii++) fdat_int[ii] = (int)buff_double[ii];
          else if (dump_type == R_CHAR)   for (ii=0; ii<field_nvals; ii++) fdat_int[ii] = (int)buff_char[ii];
          else ctlerror(me,logic_err);
          break;
        case R_LONG:
          if      (dump_type == R_LONG)   memcpy(fdat_long, buff_long, sizeof(long)*field_nvals);
          else if (dump_type == R_SHORT)  for (ii=0; ii<field_nvals; ii++) fdat_long[ii] = (long)buff_short[ii];
          else if (dump_type == R_INT)    for (ii=0; ii<field_nvals; ii++) fdat_long[ii] = (long)buff_int[ii];
          else if (dump_type == R_FLOAT)  for (ii=0; ii<field_nvals; ii++) fdat_long[ii] = (long)buff_float[ii];
          else if (dump_type == R_DOUBLE) for (ii=0; ii<field_nvals; ii++) fdat_long[ii] = (long)buff_double[ii];
          else if (dump_type == R_CHAR)   for (ii=0; ii<field_nvals; ii++) fdat_long[ii] = (long)buff_char[ii];
          else ctlerror(me,logic_err);
          break;
        case R_FLOAT:
          if      (dump_type == R_FLOAT)  memcpy(fdat_float, buff_float, sizeof(float)*field_nvals);
          else if (dump_type == R_SHORT)  for (ii=0; ii<field_nvals; ii++) fdat_float[ii] = (float)buff_short[ii];
          else if (dump_type == R_INT)    for (ii=0; ii<field_nvals; ii++) fdat_float[ii] = (float)buff_int[ii];
          else if (dump_type == R_LONG)   for (ii=0; ii<field_nvals; ii++) fdat_float[ii] = (float)buff_long[ii];
          else if (dump_type == R_DOUBLE) for (ii=0; ii<field_nvals; ii++) fdat_float[ii] = (float)buff_double[ii];
          else if (dump_type == R_CHAR)   for (ii=0; ii<field_nvals; ii++) fdat_float[ii] = (float)buff_char[ii];
          else ctlerror(me,logic_err);
          break;
        case R_DOUBLE:
          if      (dump_type == R_DOUBLE) memcpy(fdat_double, buff_double, sizeof(double)*field_nvals);
          else if (dump_type == R_SHORT)  for (ii=0; ii<field_nvals; ii++) fdat_double[ii] = (double)buff_short[ii];
          else if (dump_type == R_INT)    for (ii=0; ii<field_nvals; ii++) fdat_double[ii] = (double)buff_int[ii];
          else if (dump_type == R_LONG)   for (ii=0; ii<field_nvals; ii++) fdat_double[ii] = (double)buff_long[ii];
          else if (dump_type == R_FLOAT)  for (ii=0; ii<field_nvals; ii++) fdat_double[ii] = (double)buff_float[ii];
          else if (dump_type == R_CHAR)   for (ii=0; ii<field_nvals; ii++) fdat_double[ii] = (double)buff_char[ii];
          else ctlerror(me,logic_err);
          break;
        case R_CHAR:
          if      (dump_type == R_CHAR)   memcpy(fdat_char, buff_char, sizeof(char)*field_nvals);
          else if (dump_type == R_SHORT)  for (ii=0; ii<field_nvals; ii++) fdat_char[ii] = (char)buff_short[ii];
          else if (dump_type == R_INT)    for (ii=0; ii<field_nvals; ii++) fdat_char[ii] = (char)buff_int[ii];
          else if (dump_type == R_LONG)   for (ii=0; ii<field_nvals; ii++) fdat_char[ii] = (char)buff_long[ii];
          else if (dump_type == R_FLOAT)  for (ii=0; ii<field_nvals; ii++) fdat_char[ii] = (char)buff_float[ii];
          else if (dump_type == R_DOUBLE) for (ii=0; ii<field_nvals; ii++) fdat_char[ii] = (char)buff_double[ii];
          else ctlerror(me,logic_err);
          break;
        default: ctlerror(me,logic_err);
        } 
        nvals = nvals + field_nvals;
      }
      else {
        if (fd->nptrs == 1) {
          *(void **)fp = NULL;
        }
      }
    }
    if (nvals != dump_nvals) { ctlerror(me, logic_err); }
  }
  else {
    ctlerror(me,"can't unpack this type of fields yet");
  }
  return(0);
}
#endif
