#include <stdio.h>
#include <string.h>

#ifdef SILO
#include <silo.h>
#endif

#include "irs.h"
#include "irs.h"
#include "irsrgst.h"
#include "Rgst.h"
#ifndef _POSIX_SOURCE
#define _POSIX_SOURCE 1
#endif
#define MAX_NAMELEN  64
#define MAX_FIELDS  256

#ifdef SILO
static int calc_nvals_needed(
  RGST_StructTypeDef_t * sd,
  RGST_Field_t *         fd,
  void **                spp,
  int                    spp_num,
  int *                  nelms);
static void fill_buffer(
  RGST_StructTypeDef_t * sd,
  RGST_Field_t *         fd,
  void **                spp,
  int                    spp_num,
  int                    nvals,
  void *                 buffer);
int rgst_write_linked_list (
  DBfile *idbid,       
  char *dir_name,      
  char *struct_name,   
  void *ll)            
{
  char *me = "rgst_write_linked_list";
  char msg[128];
  int spp_num, ierr;
  void *link = NULL;
  void *ptr = NULL, **spp = NULL;
  RGST_StructTypeDef_t *sd = NULL; 
  if (ll == NULL) { return(0); }
  sd = (RGST_StructTypeDef_t *)rgst_get_td_defn(struct_name,R_STRUCT_TYPEDEF,NULL);
  if (sd == NULL) {
    sprintf(msg,"type '%s' is not a registered data type",struct_name);
    ctlwarning(me,msg);
    return(-1);
  }
  if (rgst_get_ds_field_ndx(sd,"next") < 0) {
    sprintf(msg,"type '%s' does not contain a 'next' field, so it is "
                "not a linked list",struct_name);
    ctlwarning(me,msg);
    return(-1);
  }
  link = ll;
  spp_num = 0;
  while (link != NULL) {
    spp_num++;
    link = RGST_GET_FIELD(link, struct_name, "next");
  }
  spp = ALLOT(void *, spp_num);
  if (spp == NULL) ctlerror(me, gv_errmsg_memory);
  link = ll;
  spp_num = 0;
  while (link != NULL) {
    spp[spp_num] = link;
    spp_num++;
    link = RGST_GET_FIELD(link, struct_name, "next");
  }
  ierr = rgst_write_struct_array(idbid, dir_name, struct_name, spp, spp_num);
  if (ierr != 0) {
    ctlwarning(me,"call to rgst_write_struct_array failed");
  }
  FREEMEM(spp);
  return(ierr);
}
int rgst_write_struct_array (
  DBfile *idbid,       
  char *dir_name,      
  char *struct_name,   
  void **spp,          
  int  spp_num)        
{
  char *me = "rgst_write_struct_array";
  char msg[256], startdir[256];
  int i, j, size, nvals, nbytes, type_ndx, field_type;
  int  *nelms = NULL;
  void *buffer = NULL;
  void *fp = NULL;                
  RGST_StructTypeDef_t *sd = NULL; 
  RGST_Field_t *fd = NULL;         
  void *sp = NULL;                 
  char *emptyfield = "empty";
  int   emptyfieldlen = strlen(emptyfield);
  double *dptr;
  sd = (RGST_StructTypeDef_t *)rgst_get_td_defn(struct_name,R_STRUCT_TYPEDEF,NULL);
  if (sd  == NULL) ctlerror(me,logic_err);
  if (spp == NULL) ctlerror(me,logic_err);
  if (DBGetDir(idbid, startdir) != 0) { ctlerror(me,gv_errmsg_DBGetDir); }
  if (DBMkDir (idbid, dir_name) != 0) { ctlerror(me,gv_errmsg_DBMkDir);  }
  if (DBSetDir(idbid, dir_name) != 0) { ctlerror(me,gv_errmsg_DBSetDir); }
  size = strlen(struct_name) + 1;
  DBWrite(idbid, "struct_name", struct_name, &size, 1, DB_CHAR);
  size = 1;
  DBWrite(idbid, "num_structs", &spp_num,    &size, 1, DB_INT);
  for (i=0; i<sd->num_fields; i++) {
    fd = &(sd->fields[i]);
    if (RGST_QUERY_FIELD_ATTR(sd->name,fd->name,"dump") == TRUE) {
      for (j=0; j<NUM_TYPES_SILO_KNOWS_OF; j++) {
       if (fd->type == rgst_types_silo_knows_of[j]) break;
      }
      if (j >= NUM_TYPES_SILO_KNOWS_OF) {
        sprintf(msg,"Can't write field type '%s'",rgst_datatype_strs[fd->type]);
        ctlerror(me,msg);
      }
      type_ndx = j;
      nelms = ALLOT(int, spp_num);
      nvals = calc_nvals_needed(sd, fd, spp, spp_num, nelms);
      if (nvals > 0) {
        nbytes = nvals * rgst_datatype_sizes[fd->type];
        buffer = (void *)ALLOT(unsigned char, nbytes);
        fill_buffer(sd, fd, spp, spp_num, nvals, buffer);
        dptr = buffer; 
        DBWrite(idbid, fd->name, buffer, &nvals, 1, rgst_silo_types[type_ndx]);
        FREEMEM(buffer);
      }
      else {
        DBWrite(idbid, fd->name, emptyfield, &emptyfieldlen, 1, DB_CHAR);
      }
      sprintf(msg,"%s_nelms",fd->name);
      DBWrite(idbid, msg, nelms, &spp_num, 1, DB_INT);
      FREEMEM(nelms);
      sprintf(msg,"%s_type",fd->name);
      size = 1;
      field_type = (int)fd->type;
      DBWrite(idbid, msg, &field_type, &size, 1, DB_INT);
      sprintf(msg,"%s_nvals",fd->name);
      DBWrite(idbid, msg, &nvals, &size, 1, DB_INT);
    }
  }
  if (DBSetDir(idbid, startdir) != 0) { ctlerror(me,gv_errmsg_DBSetDir); }
  return(0);
}
static void fill_buffer(
  RGST_StructTypeDef_t * sd,      
  RGST_Field_t *         fd,      
  void **                spp,     
  int                    spp_num, 
  int                    nvals,   
  void *                 buffer)  
{
  char *me = "fill_buffer";
  char msg[256];
  int  i, len;
  long field_nvals;
  void *my_values = NULL;  
  void *sp = NULL;         
  void *fp = NULL;         
  void *fdat = NULL;       
  char *str = NULL;        
  char *cbuffer = NULL;    
  int my_nvals = 0;
  double *dptr;
  if (   (fd->type  == R_CHAR)
      && (fd->ndims == 0)
      && (fd->nptrs == 1)
      && (fd->array_size_type == NUM_ARRAY_SIZE_ENUM)) {
      cbuffer = buffer;
      memset(cbuffer,'\0',nvals);
      for (i=0; i<spp_num; i++) {
       sp = spp[i];
       fp = rgst_get_field_addr(sp, sd->name, fd->name, NULL);
       str = *((char **)fp );
       if ((str == NULL) || (strlen(str) == 0)) {
         ; 
       }
       else {
         strcat(cbuffer, str);
         my_nvals += strlen(str);
       }
     }
     my_nvals++;   
     if (my_nvals != nvals) ctlwarning(me,logic_err);
  }
  else if (   (fd->nptrs == 0)
          || ((fd->nptrs == 1) && (fd->ndims == 0)) ) {
    for (i=0; i<spp_num; i++) {
      sp = spp[i];
      if (rgst_get_nelms_in_field(sp, sd, fd, NULL, NULL, &field_nvals) != 0) {
        ctlerror(me,logic_err);
      }
      fp = rgst_get_field_addr(sp, sd->name, fd->name, NULL);
      if (fp == NULL) ctlerror(me, logic_err);
      if (fd->nptrs == 0)  fdat = fp;
      else                 fdat = *((void **)fp);
      if (fdat == NULL) {
        ; 
      }
      else {
        my_values = (void *)((unsigned long)buffer + (my_nvals * rgst_datatype_sizes[fd->type]));
        dptr = fdat;
        memcpy(my_values, fdat, (field_nvals * rgst_datatype_sizes[fd->type]));
        my_nvals += field_nvals;
      }
    }
    if (my_nvals != nvals) ctlerror(me,logic_err);
  }
  else {
    ctlerror(me,logic_err);
  }
}
static int calc_nvals_needed(
  RGST_StructTypeDef_t *sd, 
  RGST_Field_t *fd,         
  void         **spp,       
  int          spp_num,     
  int *        nelms)       
{
  char *me = "calc_nvals_needed";
  char msg[256];
  int  i;
  long field_nvals;
  void *sp = NULL;         
  void *fp = NULL;         
  void *fdat = NULL;       
  char *str = NULL;        
  int nvals = 0;
  if (   (fd->type  == R_CHAR)
      && (fd->ndims == 0)
      && (fd->nptrs == 1)
      && (fd->array_size_type == NUM_ARRAY_SIZE_ENUM)) {
     for (i=0; i<spp_num; i++) {
       sp = spp[i];
       fp = rgst_get_field_addr(sp, sd->name, fd->name, NULL);
       str = *((char **)fp );
       if ((str == NULL) || (strlen(str) == 0)) {
         nelms[i] = 0;
       }
       else {
         nvals += strlen(str);
         nelms[i] = strlen(str);
       }
     }
     nvals++;   
  }
  else if (   (fd->nptrs == 0)
          || ((fd->nptrs == 1) && (fd->ndims == 0))) {
    for (i=0; i<spp_num; i++) {
      sp = spp[i];
      fp = rgst_get_field_addr(sp, sd->name, fd->name, NULL);
      if (rgst_get_nelms_in_field(sp, sd, fd, NULL, NULL, &field_nvals) != 0) {
        ctlerror(me,logic_err);
      }
      if (fd->nptrs == 0)  fdat = fp;
      else                 fdat = *((void **)fp);
      if (fdat == NULL) {
        nelms[i] = 0;
      }
      else {
        nvals   += field_nvals;
        nelms[i] = (int)field_nvals;
      }
    }
  }
  else {
    ctlerror(me,"Can't write field which is a pointer yet\n");
  }
  return(nvals);
}
#endif
