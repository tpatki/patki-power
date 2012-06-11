#include <stdio.h>
#include <string.h>

#ifdef SILO
#include <silo.h>
#endif

#include "irs.h"
#include "irs.h"
#include "irsrgst.h"
#include "Command.h"
#include "Rgst.h"
#ifndef _POSIX_SOURCE
#define _POSIX_SOURCE 1
#endif
#define MAX_NAMELEN  64
#define MAX_FIELDS  256

#ifdef SILO
static int count_fields (
  RGST_Datatype_t         datatype,
  RGST_StructTypeDef_t * sd,
  void *                sp,
  int *                 nelms,
  int *                 nvalues);
static int fill_arrays (
  RGST_Datatype_t         datatype,
  RGST_StructTypeDef_t * sd,
  void *                sp,
  int                   nelems,
  int                   nvalues,
  char *                field_writen,
  char **               elemnames,
  int  *                elemlengths,
                           void *                values);
int rgst_write_struct_in_dir (
  DBfile *idbid,       
  char *dir_name,      
  char *struct_name,   
  void *sp,            
  char *field_name)    
{
  char *me = "rgst_write_struct_in_dir";
  char currdir[256];
  int rc;
  if (DBGetDir(idbid, currdir)  != 0) ctlerror(me,gv_errmsg_DBGetDir);
  if (DBMkDir (idbid, dir_name) != 0) ctlerror(me,gv_errmsg_DBMkDir);
  if (DBSetDir(idbid, dir_name) != 0) ctlerror(me,gv_errmsg_DBSetDir);
  rc = rgst_write_struct(idbid, struct_name, sp, field_name);
  if (DBSetDir(idbid, currdir) != 0)  ctlerror(me,gv_errmsg_DBSetDir);
  return(rc);
}
int rgst_write_struct (
  DBfile *idbid,       
  char *struct_name,   
  void *sp,            
  char *field_name)    
{
  char *me = "rgst_write_struct";
  char *null_str = "null";
  char *errmsg_2d = "Can't write 2-D array--2nd array dimension unknown";
  char msg[256], routine_name[128], outdir[128], enum_type_str[128];
  char compound_array_name[256];
  char *fields_written, *str, **c_ptr_ptr, *chars;
  int  i, ii, jj, kk,  nints, ndbls, nchars, nelms, nvalues, size, ierr;
  int  myint, dim1_size, *dim2_size, *i_ptr, **i_ptr_ptr, *ints, dims[2];
  double **d_ptr_ptr, *d_ptr, *dbls;
  long   j, field_nvals, long_ptr_addr;
  char **elemnames = NULL;
  int   *elemlengths = NULL;
  void  *myvalues = NULL;
  void  *fp;               
  void  *field_data;       
  void  *field_data_ptr;   
  GENERIC_ENUM_TYPEDEF generic_enum;
  RGST_StructTypeDef_t  *sd = NULL; 
  RGST_StructTypeDef_t *fsd = NULL; 
  RGST_Field_t *fd = NULL;           
  Command_t *cp = NULL;
  sd = (RGST_StructTypeDef_t *)rgst_get_td_defn(struct_name,R_STRUCT_TYPEDEF,NULL);
  if (sd == NULL) ctlerror(me,logic_err);
  if (sp == NULL) ctlerror(me,logic_err);
  cp = build_proc_name(struct_name,"write",routine_name);
  if (cp != NULL) {
    if (((*(cp->proc))(idbid, sp, field_name)) != 0) {
      return(0);
    }
  }
  fields_written = ALLOT(char, sd->num_fields);
  memset(fields_written, '\0', sd->num_fields);
  size = strlen(struct_name) + 1;
  DBWrite(idbid, "struct_name", struct_name, &size, 1, DB_CHAR);
  for (i=0; i<NUM_TYPES_SILO_KNOWS_OF; i++) {
    count_fields(rgst_types_silo_knows_of[i], sd, sp, &nelms, &nvalues);
    if (nelms > 0) {
      elemnames   = ALLOT(char *, nelms);
      elemlengths = ALLOT(int,    nelms);
      myvalues    = (void *)ALLOT(double, nvalues);
      fill_arrays(rgst_types_silo_knows_of[i], sd, sp,
                  nelms, nvalues,
                  fields_written, elemnames, elemlengths, myvalues);
      sprintf(compound_array_name,"%s_%s",
              sd->name,rgst_datatype_strs[rgst_types_silo_knows_of[i]]);
      if (nvalues > 0) {
        if (DBPutCompoundarray(idbid, compound_array_name, elemnames,
                               elemlengths, nelms, myvalues, nvalues,
                               rgst_silo_types[i], NULL) != 0) {
           ctlerror(me,gv_errmsg_DBPutCompoundarray);
        }
      } 
      for (j=0; j<nelms; j++) { FREEMEM(elemnames[j]); }
      FREEMEM(elemnames);
      FREEMEM(elemlengths);
      FREEMEM(myvalues);
    }
  }
  for (i=0; i<sd->num_fields; i++) {
    fd = &(sd->fields[i]);
    fp = rgst_get_field_addr(sp, sd->name, fd->name, NULL);
    if (RGST_QUERY_FIELD_ATTR(sd->name,fd->name,"dump") == TRUE) {
      if ((fd->type == R_STRUCT_TYPEDEF) || (fd->type == R_STRUCT)) {
        if ((fd->nptrs == 0) && (fd->ndims == 0)) {
          sprintf(outdir, "%s",fd->name);
          if (DBMkDir (idbid, outdir) != 0) ctlerror(me,gv_errmsg_DBMkDir);
          if (DBSetDir(idbid, outdir) != 0) ctlerror(me,gv_errmsg_DBSetDir);
          if (rgst_write_struct(idbid, fd->td_name, fp, fd->name) != 0)
            ctlerror(me,logic_err);
          if (DBSetDir(idbid, "../") != 0) ctlerror(me,gv_errmsg_DBSetDir);
        }
        else if ( (fd->nptrs == 0) ||
                 ((fd->nptrs == 1) && (fd->ndims == 0)) ) {
          if (rgst_get_nelms_in_field(sp, sd, fd, NULL, NULL, &field_nvals) != 0)
            ctlerror(me,logic_err);
          if (fd->nptrs == 0)  field_data = fp;
          else                 field_data = *((void **)fp);
          if (field_data == NULL) {
            ;
          }
          else {
            if ((fsd = rgst_get_RGST_StructTypeDef_t(fd->td_name)) == NULL) {
              ctlerror(me,logic_err);
            }
            for (j=0; j<field_nvals; j++) {
              long_ptr_addr = (long)field_data + (j * fsd->struct_size);
              field_data_ptr = (void *)long_ptr_addr;
              sprintf(outdir, "%s_%i",fd->name,(int)j);
              if (DBMkDir (idbid, outdir) != 0) ctlerror(me,gv_errmsg_DBMkDir);
              if (DBSetDir(idbid, outdir) != 0) ctlerror(me,gv_errmsg_DBSetDir);
              if (rgst_write_struct(idbid, fd->td_name, field_data_ptr, fd->name) != 0)
                ctlerror(me,logic_err);
              if (DBSetDir(idbid, "../") != 0) ctlerror(me,gv_errmsg_DBSetDir);
            }
          }
        }
        else {
          sprintf(msg,"\n\tCan't write field '%s' of structure '%s'"
                      "\n\tBecause it is not a simple 1-Dimensional array",
                      fd->name,sd->name);
         ctlerror(me,msg);
        }
        if (fields_written[i] == TRUE) ctlerror(me,logic_err);
        fields_written[i] = TRUE;
      }
      else if (fd->type == R_ENUM_TYPEDEF) {
        generic_enum = *((GENERIC_ENUM_TYPEDEF *)fp);
        if ((fd->nptrs == 0) && (fd->ndims == 0)) {
          rgst_conv_enum_type_to_str(fd->td_name, generic_enum, enum_type_str);
          size = strlen(enum_type_str) + 1;
          DBWrite(idbid, sd->fields[i].name, enum_type_str, &size, 1, DB_CHAR);
        }
        else {
          ctlerror(me,"Can't write arrays of enumerated types yet");
        }
        if (fields_written[i] == TRUE) ctlerror(me,logic_err);
        fields_written[i] = TRUE;
      }
      else if (  (fd->type  == R_CHAR)
              && (fd->nptrs == 1)
              && (fd->ndims == 0)
              && (fd->array_size_type == NUM_ARRAY_SIZE_ENUM)) {
        dims[0] = (int)rgst_get_field_array_size(sp, sd, fd);
        str = *((char **)fp);
        if (dims[0] > 0) {
          dims[0] += 1;
        }
        else {
          dims[0] = strlen(null_str) + 1;
          str = null_str;
        }
        if (DBWrite(idbid,fd->name,str,dims,1,DB_CHAR) != 0)
          ctlerror(me,gv_errmsg_DBWrite);
        if (fields_written[i] == TRUE) ctlerror(me,logic_err);
        fields_written[i] = TRUE;
      }
      else if (  (fd->nptrs == 2)  
              && (fd->ndims == 0)
              && (fd->array_size_type != NUM_ARRAY_SIZE_ENUM) ) {
        dim1_size = (int)rgst_get_field_array_size (sp, sd, fd);
	dim2_size = NULL;
        if (fd->str_array_size_field >= 0) {
          fp = rgst_get_field_addr(sp, sd->name, sd->fields[fd->str_array_size_field].name, NULL);
          dim2_size = *(int **)fp;
        }
	if (dim1_size == 0) {
          sprintf(msg,"%s_size",fd->name);
          dims[0] = 1;
          myint = 0;
          ierr = DBWrite(idbid, msg, &myint, dims, 1, DB_INT);
        }
        else if (fd->type == R_CHAR) {
          fp = rgst_get_field_addr(sp, sd->name, fd->name, NULL);
          c_ptr_ptr = *(char ***)fp;
          if (fd->str_array_size_field < 0) {
	    nchars = 0;
	    for (ii=0; ii<dim1_size; ii++) {
              str = c_ptr_ptr[ii];
              if (str == NULL) {
                nchars += 2;
              }
              else {
	        nchars += strlen(str) + 1;
	        if (strlen(str) == 0) nchars++;
              }
            }
	    chars = ALLOT(char, nchars + 1);
	    memset(chars,'\0',nchars);
            for (ii=0; ii<dim1_size; ii++) {
              str = c_ptr_ptr[ii];
              if (str == NULL) {
                strcat(chars, " "); 
              }
              else {
                if (strlen(str) == 0) { strcat(chars, " "); }
	        else                  { strcat(chars, str); }
              }
              if (strlen(chars) >= nchars) {
                sprintf(msg,"chars array of size %d about to be overwritten",nchars);
                ctlerror(me,msg);
              }                                                                                   
              strcat(chars,STR_DELIMITER); 
            }
          }
	  else {
            if (dim2_size == NULL) { ctlerror(me,errmsg_2d); }
            nchars = 0;
	    for (ii=0; ii<dim1_size; ii++) { nchars += dim2_size[ii]; }
            chars = ALLOT(char, nchars + 1);
            memset(chars,'\0',nchars);
	    kk = 0;
	    for (ii=0; ii<dim1_size; ii++) {
              str = c_ptr_ptr[ii];
              for (jj=0; jj<dim2_size[ii]; jj++) {
	        chars[kk] = str[jj];
		kk++;
	      }  
            }
	  } 	 		 
	  if (nchars == 0)  {
            dims[0] = 1;
	    chars[0] = '\0';
          }
	  else {
	    dims[0] = nchars;
	  }
          ierr = DBWrite(idbid, fd->name, chars, dims, 1, DB_CHAR);
          sprintf(msg,"%s_size",fd->name);
          dims[0] = 1;
          myint = nchars;
          ierr += DBWrite(idbid, msg, &myint, dims, 1, DB_INT);
          if (ierr != 0) ctlerror(me,gv_errmsg_DBWrite);
	  FREEMEM(chars);
        }
        else if (fd->type == R_INT) {
          if (dim2_size == NULL) { ctlerror(me,errmsg_2d); }
          fp = rgst_get_field_addr(sp, sd->name, fd->name, NULL);
          i_ptr_ptr = *(int ***)fp;
	  nints = 0;
	  for (ii=0; ii<dim1_size; ii++) { nints += dim2_size[ii]; }
	  ints = ALLOT(int, nints + 1);
	  kk = 0;
	  for (ii=0; ii<dim1_size; ii++) {
            i_ptr = i_ptr_ptr[ii];
            for (jj=0; jj<dim2_size[ii]; jj++) {
	      ints[kk] = i_ptr[jj];
	      kk++;
	    }  
          }
	  if (nints == 0) {
            dims[0] = 1;
	    ints[0] = 0; 
          }
	  else {
	    dims[0] = nints;
          }
	  ierr = DBWrite(idbid, fd->name, ints, dims, 1, DB_INT);
          sprintf(msg,"%s_size",fd->name);
          dims[0] = 1;
          myint = nints;
          ierr += DBWrite(idbid, msg, &myint, dims, 1, DB_INT);
	  if (ierr != 0) ctlerror(me,gv_errmsg_DBWrite);
	  FREEMEM(ints);
        }
        else if (fd->type == R_DOUBLE) {
          if (dim2_size == NULL) { ctlerror(me,errmsg_2d); }
          fp = rgst_get_field_addr(sp, sd->name, fd->name, NULL);
          d_ptr_ptr = *(double ***)fp;
	  ndbls = 0;
	  for (ii=0; ii<dim1_size; ii++) { ndbls += dim2_size[ii]; }
	  dbls = ALLOT(double, ndbls + 1);
	  kk = 0;
	  for (ii=0; ii<dim1_size; ii++) {
            d_ptr = d_ptr_ptr[ii];
            for (jj=0; jj<dim2_size[ii]; jj++) {
	      dbls[kk] = d_ptr[jj];
	      kk++;
	    }  
          }
	  if (ndbls == 0) { 
            dims[0] = 1; 
	    dbls[0] = 0.0;
	  }
	  else {
	    dims[0] = ndbls;
          }
 	  ierr = DBWrite(idbid, fd->name, dbls, dims, 1, DB_DOUBLE);
          sprintf(msg,"%s_size",fd->name);
          dims[0] = 1;
          myint = ndbls;
          ierr += DBWrite(idbid, msg, &myint, dims, 1, DB_INT);
	  if (ierr != 0) ctlerror(me,gv_errmsg_DBWrite);
	  FREEMEM(dbls);
        }
	else {
          sprintf(msg,"\n\tCoding not done yet to write multi-D dynamic arrays"
	              "\n\tof type '%s'\n",rgst_datatype_strs[fd->type]);
          ctlnotice(me,msg);
        }
      }
      else {
        if (fields_written[i] != TRUE) {
          sprintf(msg,"Do not know how to write field '%s' of type '%s' of structure '%s'",
                       fd->name,
                       rgst_datatype_strs[fd->type],
                       sd->name);
          ctlnotice(me,msg);
        }
      }
    }  
  }    
  FREEMEM(fields_written);
  return(0);
}
static int fill_arrays(
  RGST_Datatype_t datatype,  
  RGST_StructTypeDef_t * sd, 
  void * sp,                 
  int nelems,                
  int nvalues,               
  char *fields_written,      
  char **elemnames,          
  int  *elemlengths,         
  void *values)            
{
  char *me = "fill_arrays";
  char msg[256];
  void *my_values;
  int  i, datatype_size;
  int  my_nelms   = 0;
  int  my_nvalues = 0;
  long field_nvals;
  RGST_Field_t *fd = NULL;         
  void       *fp = NULL;         
  void       *field_data = NULL; 
  for (i=0; i<NUM_TYPES_SILO_KNOWS_OF; i++) {
    if (datatype == rgst_types_silo_knows_of[i]) break;
  }
  if (i >= NUM_TYPES_SILO_KNOWS_OF) {
    sprintf(msg,"cannot fill arrays of type '%s' yet",rgst_datatype_strs[datatype]);
    ctlerror(me,msg);
  }
  datatype_size = rgst_datatype_sizes[datatype];
  for (i=0; i<sd->num_fields; i++) {
    fd = &(sd->fields[i]);
    fp = rgst_get_field_addr(sp, sd->name, fd->name, NULL);
    if (RGST_QUERY_FIELD_ATTR(sd->name,fd->name,"dump") == TRUE) {
      if (  (fd->type  == R_CHAR)
         && (fd->nptrs == 1)
         && (fd->ndims == 0)
         && (fd->array_size_type == NUM_ARRAY_SIZE_ENUM)) {
         ;
      }
     else if (   (fd->nptrs == 2)  
              && (fd->ndims == 0)
              && (fd->array_size_type != NUM_ARRAY_SIZE_ENUM)) {
          ;
      }
      else if (fd->type == datatype) {
        if ((fd->nptrs == 0) && (fd->ndims == 0)) {
          field_data  = fp;
          field_nvals = 1;
        }
        else if ( (fd->nptrs == 0) ||
                 ((fd->nptrs == 1) && (fd->ndims == 0))) {
          if (rgst_get_nelms_in_field(sp, sd, fd, NULL, NULL, &field_nvals) != 0)
            ctlerror(me,logic_err);
          if (fd->nptrs == 0)  field_data = fp;
          else                 field_data = *((void **)fp);
        }
        else {
          ctlerror(me,logic_err);
        }
        if (field_data == NULL) {
          elemlengths[my_nelms] = 0;
        }
        else {
          my_values = (void *)((unsigned long)values + (my_nvalues * datatype_size));
          memcpy(my_values, field_data, (field_nvals * datatype_size));
          elemlengths[my_nelms] = (int)field_nvals;
          my_nvalues += field_nvals;
        }
        if (fields_written[i] == TRUE) ctlerror(me,logic_err);
        fields_written[i] = TRUE;
        elemnames  [my_nelms] = strsave(fd->name);
        my_nelms++;
      }
    }
  }
  if ((my_nelms != nelems) || (my_nvalues != nvalues))
    ctlerror(me,logic_err);
  return(0);
}
static int count_fields(
  RGST_Datatype_t        datatype, 
  RGST_StructTypeDef_t * sd,       
  void *                 sp,       
  int *                  nelms,    
  int *                  nvalues)  
{
  char *me = "count_fields";
  int  i;
  int  my_nelms   = 0;
  int  my_nvalues = 0;
  long field_nvals;
  char msg[256];
  RGST_Field_t *fd = NULL;      
  void *fp = NULL;              
  void *field_data = NULL;      
  for (i=0; i<sd->num_fields; i++) {
    fd = &(sd->fields[i]);
    fp = rgst_get_field_addr(sp, sd->name, fd->name, NULL);
    if (RGST_QUERY_FIELD_ATTR(sd->name,fd->name,"dump") == TRUE) {
      if (  (fd->type  == R_CHAR)
         && (fd->nptrs == 1)
         && (fd->ndims == 0)
         && (fd->array_size_type == NUM_ARRAY_SIZE_ENUM)) {
         ; 
      }
      else if (fd->type == datatype) {
        if ((fd->nptrs == 0) && (fd->ndims == 0)) {
          my_nelms++;
          my_nvalues++;
        }
        else if ( (fd->nptrs == 0) ||
                 ((fd->nptrs == 1) && (fd->ndims == 0))) {
          if (rgst_get_nelms_in_field(sp, sd, fd, NULL, NULL, &field_nvals) != 0)
            ctlerror(me,logic_err);
          if (fd->nptrs == 0)  field_data = fp;
          else                 field_data = *((void **)fp);
          if (field_data != NULL) {
            my_nvalues += field_nvals;
          }
          my_nelms++;
        }
        else if (  (fd->nptrs == 2)  
                && (fd->ndims == 0)
                && (fd->array_size_type != NUM_ARRAY_SIZE_ENUM)) {
          ;
        }
        else {
          sprintf(msg,"\n\tCan't count field '%s' of structure '%s'",
                      fd->name,sd->name);
          ctlerror(me,msg);
        }
      }
    }
  }
  *nelms   = my_nelms;
  *nvalues = my_nvalues;
  return(0);
}

#endif
