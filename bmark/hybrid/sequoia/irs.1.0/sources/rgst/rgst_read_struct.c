#include <stdio.h>
#include <string.h>

#ifdef SILO
#include <silo.h>
#endif

#include "irs.h"
#include "irsctl.h"
#include "irsdefs.h"
#include "irsrgst.h"
#include "Command.h"
#include "Rgst.h"
#define MSGLEN 256
#define READVARLEN 524288	

#ifdef SILO
typedef struct ds_checklist_str {
  int field_read;                  
  int field_ndx;                   
  int allocated_array_size;        
} DS_CHECKLIST_TYPE;
static int st_pre_check_struct(
  void *ptr,
  RGST_StructTypeDef_t *sd,
  DS_CHECKLIST_TYPE   *ds_checklist,
  int ds_checklist_size
);
static int st_fill_field_from_comparray(
  RGST_StructTypeDef_t *sd,
  RGST_Field_t          *fd,
  void                *fp,
  void                *comparray_values,
  int                  comparray_values_ndx,
  int                  comparray_elemlength,
  int                  comparray_type,
  DS_CHECKLIST_TYPE   *ds_checklist
                                       );

void * rgst_read_struct_in_dir (
  DBfile *idbid,       
  char *dir_name,      
  char *struct_name,   
  void *in_sp,         
  char *field_name)    
{
  char *me = "rgst_read_struct_in_dir";
  char currdir[256];
  void *rv = NULL;
  if (DBGetDir(idbid, currdir)  != 0) ctlerror(me,gv_errmsg_DBGetDir);
  if (DBSetDir(idbid, dir_name) != 0) ctlerror(me,gv_errmsg_DBSetDir);
  rv = rgst_read_struct(idbid, struct_name, in_sp, field_name);
  if (DBSetDir(idbid, currdir)  != 0) ctlerror(me,gv_errmsg_DBSetDir);
  return(rv);
}


void * rgst_read_struct (
  DBfile *idbid,       
  char *struct_name,   
  void *in_sp,         
  char *field_name)    
{
  char *me = "rgst_read_struct";
  char *null_str = "null";
  char msg[MSGLEN], silo_struct_name[STRLEN], routine_name[STRLEN];
  char readvar[READVARLEN], *chars, *char_ptr, **char_ptrs, *token;
  char enum_str[STRLEN], outdir[STRLEN], comparray_name[MSGLEN];
  int  i, k, l, ii, jj, kk, ierr, ds_checklist_size, field_ndx, values_ndx;
  int packed_array_size, *ints, dim1_size, *dim2_size;
  int **int_ptrs, *int_ptr;
  long j, field_nvals, long_ptr_addr;
  double *dbls, **dbl_ptrs, *dbl_ptr;
  size_t type_size;
  void *sp;                        
  void *fp;                        
  void *field_data;                
  void *struct_ptr;                
  RGST_StructTypeDef_t  *sd = NULL; 
  RGST_StructTypeDef_t *fsd = NULL; 
  RGST_Field_t *fd = NULL;           
  GENERIC_ENUM_TYPEDEF generic_enum;
  Command_t *cp = NULL, *pre_read_cp = NULL;
  DS_CHECKLIST_TYPE *ds_checklist = NULL;
  DBtoc *toc = NULL, *temp_toc;
  DBcompoundarray *comparray;
  sd = (RGST_StructTypeDef_t *)rgst_get_td_defn(struct_name,R_STRUCT_TYPEDEF,NULL);
  if (sd == NULL) ctlerror(me,logic_err);
  if (in_sp == NULL) {
    sp = rgst_construct(R_STRUCT, struct_name, 1);
    if (sp == NULL) ctlerror(me, logic_err);
  }
  else {
    sp = in_sp;
  }
  pre_read_cp = build_proc_name(struct_name,"pre_read",routine_name);
  if (pre_read_cp != NULL) {
    if (((*(pre_read_cp->proc))(idbid, sp, field_name)) != 0) { return(sp); }
  }
  memset(silo_struct_name,'\0',STRLEN);
  if (DBReadVar(idbid,"struct_name",silo_struct_name) != 0) {
    sprintf(msg,"\n\tRead of variable 'struct_name' failed.  Either the programmer"
                "\n\tdid not place the open silo file in the correct directory"
                "\n\tor this silo file was not created using registry io.");
    ctlwarning(me,msg);
    return(NULL);
  }
  if (strcmp(silo_struct_name,struct_name) != 0) {
    sprintf(msg,"\n\tProgrammer expected to read structure type '%s'"
                "\n\tBut open silo file contains a structure of type '%s'",
                struct_name,silo_struct_name);
    ctlwarning(me,msg);
    return(NULL);
  }
  if ((ds_checklist = ALLOT(DS_CHECKLIST_TYPE,sd->num_fields)) == NULL)
    ctlerror(me,gv_errmsg_memory);
  ds_checklist_size = 0;
  for (i=0; i<sd->num_fields; i++) {
    fd = &(sd->fields[i]);
    if ((RGST_QUERY_FIELD_ATTR(sd->name,fd->name,"dump")) == TRUE) {
      ds_checklist[ds_checklist_size].field_read           = FALSE;
      ds_checklist[ds_checklist_size].allocated_array_size = -1;
      ds_checklist[ds_checklist_size].field_ndx            = i;
      ds_checklist_size++;
    }
  }
  if (in_sp != NULL) {
    ierr = st_pre_check_struct(sp, sd, ds_checklist, ds_checklist_size);
    if (ierr != 0) {
      FREEMEM(ds_checklist);
      ctlerror(me,logic_err);
    }
  }
  toc = DBGetToc(idbid);
  toc = copy_toc(toc);
  for (i=0; i<NUM_TYPES_SILO_KNOWS_OF; i++) {
    sprintf(comparray_name,"%s_%s",
            sd->name,rgst_datatype_strs[rgst_types_silo_knows_of[i]]);
    for (j=0; j<toc->narrays; j++) {
      if (strcmp(comparray_name,toc->array_names[j]) == 0) break;
    }
    if (j < toc->narrays) {
      comparray = DBGetCompoundarray(idbid,comparray_name);
      values_ndx = 0;
      for (k=0; k<comparray->nelems; k++) {
        for (l=0; l<ds_checklist_size; l++) {
          field_ndx = ds_checklist[l].field_ndx;
          if (strcmp(comparray->elemnames[k],sd->fields[field_ndx].name) == 0) {
            fd = &(sd->fields[field_ndx]);
            fp = rgst_get_field_addr(sp, sd->name, fd->name, NULL);
            st_fill_field_from_comparray(sd, fd, fp, comparray->values, values_ndx,
                                         comparray->elemlengths[k],
                                         comparray->datatype, &(ds_checklist[l]));
            if (ds_checklist[l].field_read == TRUE) ctlerror(me,logic_err);
            ds_checklist[l].field_read = TRUE;
            break;
          }
        }
        values_ndx += comparray->elemlengths[k];
#ifdef DEBUG
        if (debugflag == TRUE) {
          if (l >= ds_checklist_size) {
            sprintf(msg,"field '%s' of data structure '%s' is in the silo "
                        "file but was not read",
                         comparray->elemnames[k],sd->name);
            ctlnotice(me,msg);
          }
        }
#endif
      }
      DBFreeCompoundarray(comparray);
    }
  } 
  for (i=0; i<ds_checklist_size; i++) {
    field_ndx = ds_checklist[i].field_ndx;
    fd = &(sd->fields[field_ndx]);
    fp = rgst_get_field_addr(sp, sd->name, fd->name, NULL);
    if ((fd->type == R_STRUCT) || (fd->type == R_STRUCT_TYPEDEF)) {
      if ((fd->nptrs == 0) && (fd->ndims == 0)) {
        sprintf(outdir, "%s",fd->name);
        for (j=0; j<toc->ndir; j++) {
          if (strcmp(outdir,toc->dir_names[j]) == 0) break;
        }
        if (j < toc->ndir) {
          if (DBSetDir(idbid, outdir) != 0) ctlerror(me,gv_errmsg_DBSetDir);
          rgst_read_struct(idbid, fd->td_name, fp, fd->name);
          if (DBSetDir(idbid, "../") != 0) ctlerror(me,gv_errmsg_DBSetDir);
        }
        else {
          sprintf(msg,"\n\tfield '%s' of data structure '%s' should exist as a"
                      "\n\tdirectory in the silo file, but it does not",
                      fd->name,sd->name);
          ctlwarning(me,msg);
        }
      }
      else if ( (fd->nptrs == 0) ||
               ((fd->nptrs == 1) && (fd->ndims == 0)) ) {
        if (rgst_get_nelms_in_field(sp, sd, fd, NULL, NULL, &field_nvals) != 0)
          ctlerror(me,logic_err);
        if (field_nvals > 0) {
          if (fd->nptrs == 0) {
            field_data = fp;
            if (field_data == NULL) ctlerror(me,logic_err);
          }
          else {
            field_data = *((void **)fp);
            if (field_data == NULL) {
              if (ds_checklist[i].allocated_array_size > 0) ctlerror(me,logic_err);
              field_data = rgst_construct(fd->type,fd->td_name, (int)field_nvals);
              if (field_data == NULL) ctlerror(me,logic_err);
              *((void **)fp) = field_data;
              ds_checklist[i].allocated_array_size = (int)field_nvals;
            }
          }
          type_size = rgst_get_datatype_size(fd->type, fd->td_name);
          for (j=0; j<field_nvals; j++) {
            sprintf(outdir, "%s_%i",fd->name,(int)j);
            for (k=0; k<toc->ndir; k++) {
              if (strcmp(outdir,toc->dir_names[k]) == 0) break;
            }
            if (k < toc->ndir) {
              if (DBSetDir(idbid, outdir) != 0) ctlerror(me,gv_errmsg_DBSetDir);
              long_ptr_addr = (long)field_data + (j * type_size);
              struct_ptr    = (void *)long_ptr_addr;
              rgst_read_struct(idbid, fd->td_name, struct_ptr, fd->name);
              if (DBSetDir(idbid, "../") != 0) ctlerror(me,gv_errmsg_DBSetDir);
            }
            else {
              sprintf(msg,"\n\tfield '%s' of data structure '%s' should exist as a"
                          "\n\tdirectory in the silo file, but it does not",
                          outdir,sd->name);
              ctlwarning(me,msg);
            }
          }     
        }	
      }		
      else {
        sprintf(msg,"\n\tCan't read field '%s' of structure '%s'"
                    "\n\tBecause it is not a simple 1-Dimensional array",
                    fd->name,sd->name);
        ctlerror(me,msg);
      }
    } 
    else if (fd->type == R_ENUM_TYPEDEF) {
      for (k=0; k<toc->nvar; k++) {
        if (strcmp(fd->name,toc->var_names[k]) == 0) break;
      }
      if (k < toc->nvar) {
        if ((fd->nptrs == 0) && (fd->ndims == 0)) {
          memset(enum_str,'\0',STRLEN);
          if (DBReadVar(idbid, fd->name, enum_str) != 0) {
            ctlerror(me,gv_errmsg_DBReadVar);
          }
          generic_enum = rgst_conv_str_to_enum_type(fd->td_name, enum_str);
          *((GENERIC_ENUM_TYPEDEF *)fp) = generic_enum;
        }
        else {
          ctlerror(me,"Can't read arrays of enumerated types yet");
        } 
      }
      else {
        sprintf(msg,"\n\tEnumerated type, field '%s' of data structure '%s'"
                    "\n\tshould exist as a string in the silo file, but it does not",
                    fd->name,sd->name);
        ctlwarning(me,msg);
      }
    }
    else if (  (fd->type  == R_CHAR)
            && (fd->nptrs == 1)
            && (fd->ndims == 0)
            && (fd->array_size_type == NUM_ARRAY_SIZE_ENUM)) {
      DBShowErrors(DB_NONE, NULL);
      if (DBReadVar(idbid,fd->name,readvar) != 0) {
        temp_toc = DBGetToc(idbid);
        for (ii=0; ii<temp_toc->nvar; ii++) {
          if (strcmp(fd->name,temp_toc->var_names[ii]) == 0) {
            ctlerror(me,gv_errmsg_DBReadVar);
          }
        }
        *(char **)fp = NULL;
        ds_checklist[i].field_read = TRUE;
      }
      else {
        if (strlen(readvar) >= READVARLEN) {
          fprintf(stderr,"error - just read var of length %d\n",strlen(readvar));
          ctlerror(me,"have programmer increase READVARLEN");   
        }
        if (strcmp(readvar,null_str) == 0) { *(char **)fp = NULL;             }
        else                               { *(char **)fp = strsave(readvar); }
        if (ds_checklist[i].field_read == TRUE) ctlerror(me,logic_err);
        ds_checklist[i].field_read = TRUE;
      }
      DBShowErrors(DB_TOP, NULL);
    }
    else if (  (fd->nptrs == 2)
            && (fd->ndims == 0)
            && (fd->array_size_type != NUM_ARRAY_SIZE_ENUM) ) {
      dim1_size = (int)rgst_get_field_array_size(sp, sd, fd);
      dim2_size = NULL;
      if (fd->str_array_size_field >= 0) {
        fp = rgst_get_field_addr(sp, sd->name, sd->fields[fd->str_array_size_field].name, NULL);
        dim2_size = *(int **)fp;
      }
      sprintf(msg,"%s_size",fd->name);
      if (DBReadVar(idbid,msg,&packed_array_size) != 0) {
        ctlerror(me,gv_errmsg_DBReadVar);
      }
      fp = rgst_get_field_addr(sp, sd->name, fd->name, NULL);
      if (packed_array_size <= 0 ) {
        ; 
      }
      else {
        if (fd->type == R_CHAR) {
          char_ptrs = *((char ***)fp);
          if (char_ptrs == NULL) {
            char_ptrs = ALLOT(char *, dim1_size);
            for (ii=0; ii<dim1_size; ii++) { char_ptrs[ii] = NULL; }
            *((char ***)fp) = char_ptrs;
          }
          chars = ALLOT(char, packed_array_size + 1);
          memset(chars,'\0',packed_array_size + 1);
          if (DBReadVar(idbid, fd->name, chars) != 0) {
            ctlerror(me,gv_errmsg_DBReadVar);
          }
          if (fd->str_array_size_field < 0) {
            token = strtok(chars,STR_DELIMITER);
            ii = 0;
            while (token != NULL) {
              if (ii >= dim1_size) { ctlerror(me,logic_err); }
              if (strcmp(token," ") == 0) { char_ptrs[ii] = NULL; }
              else                        { char_ptrs[ii] = strsave(token); }
              ii++;
              token = strtok(NULL,STR_DELIMITER);
            }
          }
          else {
            if (dim2_size == NULL) { ctlerror(me,logic_err); }
            kk = 0;
            for (ii=0; ii<dim1_size; ii++) {
              char_ptr = char_ptrs[ii];
              if (char_ptr == NULL) {
                char_ptrs[ii] = ALLOT(char, dim2_size[ii]);
                char_ptr = char_ptrs[ii];
              }
              for (jj=0; jj<dim2_size[ii]; jj++) {
                char_ptr[jj] = chars[kk];
                kk++;
              }
            }
          }
          FREEMEM(chars);
        }
        else if (fd->type == R_INT) {
          int_ptrs = *((int ***)fp);
          if (int_ptrs == NULL) {
            int_ptrs = ALLOT(int *, dim1_size);
            for (ii=0; ii<dim1_size; ii++) { int_ptrs[ii] = NULL; }
            *((int ***)fp) = int_ptrs;
          }
          ints = ALLOT(int, packed_array_size);
          if (DBReadVar(idbid, fd->name, ints) != 0) {
            ctlerror(me,gv_errmsg_DBReadVar);
          }
          if (dim2_size == NULL) { ctlerror(me,logic_err); }
          kk = 0;
          for (ii=0; ii<dim1_size; ii++) {
            int_ptr = int_ptrs[ii];
            if (int_ptr == NULL) {
              int_ptrs[ii] = ALLOT(int, dim2_size[ii]);
              int_ptr = int_ptrs[ii];
            }
            for (jj=0; jj<dim2_size[ii]; jj++) {
              int_ptr[jj] = ints[kk];
              kk++;
            }
          }
          FREEMEM(ints);
        }
        else if (fd->type == R_DOUBLE) {
          dbl_ptrs = *((double ***)fp);
          if (dbl_ptrs == NULL) {
            dbl_ptrs = ALLOT(double *, dim1_size);
            for (ii=0; ii<dim1_size; ii++) { dbl_ptrs[ii] = NULL; }
            *((double ***)fp) = dbl_ptrs;
          }
          dbls = ALLOT(double, packed_array_size);
          if (DBReadVar(idbid, fd->name, dbls) != 0) {
            ctlerror(me,gv_errmsg_DBReadVar);
          }
          if (dim2_size == NULL) { ctlerror(me,logic_err); }
          kk = 0;
          for (ii=0; ii<dim1_size; ii++) {
            dbl_ptr = dbl_ptrs[ii];
            if (dbl_ptrs[ii] == NULL) {
              dbl_ptrs[ii] = ALLOT(double, dim2_size[ii]);
              dbl_ptr = dbl_ptrs[ii];
            }
            for (jj=0; jj<dim2_size[ii]; jj++) {
              dbl_ptr[jj] = dbls[kk];
              kk++;
            }
          }
          FREEMEM(dbls);
        }
      }
      if (ds_checklist[i].field_read == TRUE) ctlerror(me,logic_err);
      ds_checklist[i].field_read = TRUE;
    }
    else {
      if (ds_checklist[i].field_read != TRUE) {
        for (ii=0; ii<NUM_TYPES_SILO_KNOWS_OF; ii++) {
          if (fd->type == rgst_types_silo_knows_of[ii]) break;
        }
        if (ii >= NUM_TYPES_SILO_KNOWS_OF) {
          sprintf(msg,"Do not know how to read field '%s' of type '%s' of structure '%s'",
                       fd->name,
                       rgst_datatype_strs[fd->type],
                       sd->name);
          ctlerror(me,msg);
	}
      }
    }
  } 
  toc = free_toc(toc);
  cp = build_proc_name(struct_name,"post_read",routine_name);
  if (cp != NULL) {
    (*(cp->proc))(idbid, sp, field_name);
  }
  FREEMEM(ds_checklist);
  return(sp);
}

static int st_pre_check_struct(
  void *ptr,                          
  RGST_StructTypeDef_t *sd,           
  DS_CHECKLIST_TYPE   *ds_checklist,  
  int ds_checklist_size)              
{
  char *me = "st_pre_check_struct";
  char msg[256];
  int  i, field_ndx;
  long array_size;
  RGST_Field_t *fd, *array_size_fd;
  void *fp;
  void *generic_ptr;
  size_t type_size;
  for (i=0; i<ds_checklist_size; i++) {
    field_ndx = ds_checklist[i].field_ndx;
    fd = &(sd->fields[field_ndx]);
    if (  (fd->nptrs == 1)
       && (fd->ndims == 0)
       && (fd->array_size_type != NUM_ARRAY_SIZE_ENUM)) {
      array_size = rgst_get_field_array_size(ptr,sd,fd);
      ds_checklist[i].allocated_array_size = (int)array_size;
      fp = rgst_get_field_addr(ptr, sd->name, fd->name, NULL);
      generic_ptr = *((void **)fp);
      if (generic_ptr == NULL) {
        if (array_size > 0) {
            type_size = rgst_get_datatype_size(fd->type, fd->td_name);
            generic_ptr = ALLOT(char, (type_size * array_size));
            *((void **)fp) = generic_ptr;
        }
      }
      else {
        if (array_size < 1) {
          array_size_fd  = &(sd->fields[fd->array_size_field]);
          if      (fd->array_size_type == FIELD_OFFSET) {
            sprintf(msg,"\n\tField '%s' of structure '%s' has been allocated"
                        "\n\tHowever field '%s', which is the length of the"
                        "\n\tallocated field, is set to %d",
                         fd->name, sd->name,
                         array_size_fd->name, (int)array_size);
            ctlwarning(me,msg);
          }
          else if (fd->array_size_type == GLOBAL_VAR) {
            sprintf(msg,"\n\tField '%s' of structure '%s' has been allocated"
                        "\n\tHowever global var '%s' which is the length of the"
                        "\n\tallocated field, is set to %d",
                         fd->name, sd->name,
                         fd->array_size_global_var, (int)array_size);
            ctlwarning(me,msg);
          }
          else {
            ctlerror(me,logic_err);
          }
          return(-1);
        }
      }
    }
  }   
  return(0);
}
static int st_fill_field_from_comparray(
  RGST_StructTypeDef_t *sd,         
  RGST_Field_t *fd,                  
  void *fp,                        
  void *ca_values,                 
  int ca_values_ndx,               
  int ca_elemlength,               
  int ca_type,                     
  DS_CHECKLIST_TYPE *ds_checklist) 
{
  char *me = "st_fill_field_from_comparray";
  char msg[512];
  int i, nvals;
  void   *fdat;                        
  char   *fdat_char,   *cdat_char;     
  short  *fdat_short,  *cdat_short;    
  int    *fdat_int,    *cdat_int;      
  long   *fdat_long,   *cdat_long;     
  float  *fdat_float,  *cdat_float;    
  double *fdat_double, *cdat_double;
  if (ca_elemlength < 1) {
    return(0);	     
  }
  if ( (fd->nptrs == 0) && (fd->ndims == 0) ) {
    fdat = fp;
    nvals = 1;
  }
  else {
    if (fd->nptrs > 1) {
      sprintf(msg,"\n\tCannot copy data to field '%s' of structure '%s"
                  "\n\tbecause it is a %d-dimensional dynamically allocated array"
                  "\n\tCode to do this not done yet",
                  fd->name, sd->name, fd->nptrs);
      ctlerror(me,msg);
    }
    else if (fd->nptrs == 1) {
      if (fd->ndims != 0) {
        sprintf(msg,"\n\tCannot copy data to field '%s' of structure '%s'"
                    "\n\tbecause it is a 1-dimensional dynamic array of arrays"
                   "\n\tCode to do this not done yet",
                    fd->name, sd->name);
        ctlerror(me,msg);
      }
      fdat = *((void **)fp);
      if (fdat == NULL) {
        if (ds_checklist->allocated_array_size > 0) {
          ctlerror(me,logic_err);
        }
#ifdef DEBUG
        if (debugflag == TRUE) {
          printf("DEBUG[%s] struct '%s' field '%s' allocating dynamic array of %d bytes\n",
            me,sd->name,fd->name,(int)rgst_datatype_sizes[fd->type] * ca_elemlength);
        }
#endif
        fdat = ALLOT(char, (rgst_datatype_sizes[fd->type] * ca_elemlength));
        *((void **)fp) = fdat;
        ds_checklist->allocated_array_size = ca_elemlength;
      }
      nvals = ds_checklist->allocated_array_size;
    }
    else {       
      fdat  = fp;
      nvals = 1;
      for (i=0; i<fd->ndims; i++) nvals = nvals * fd->dims[i];
    }
    if (nvals < ca_elemlength) {
      if (nvals == -1) {
        sprintf(msg,"\n\tField '%s' of structure '%s' has been allocated by user"
                    "\n\tBut the length of this array has not been registered"
                    " using RGST_LEN in the .h file"
                    "\b\tAbout to copy data into this array of unknown length",
                    fd->name,sd->name);
        ctlnotice(me,msg);
        nvals = ca_elemlength;
      }
      else {
        sprintf(msg,"\n\tField '%s' of structure '%s' allocated with %d elements"
                    "\n\tSilo file holds %d elements.  Cannot copy all the"
                    " silo data into this array",
                    fd->name, sd->name, nvals, ca_elemlength);
        ctlnotice(me,msg);
      }
    }
  }
  fdat_short  = fdat;
  fdat_int    = fdat;
  fdat_long   = fdat;
  fdat_float  = fdat;
  fdat_double = fdat;
  fdat_char   = fdat;
  cdat_short  = &(((short  *)ca_values)[ca_values_ndx]);
  cdat_int    = &(((int    *)ca_values)[ca_values_ndx]);
  cdat_long   = &(((long   *)ca_values)[ca_values_ndx]);
  cdat_float  = &(((float  *)ca_values)[ca_values_ndx]);
  cdat_double = &(((double *)ca_values)[ca_values_ndx]);
  cdat_char   = &(((char   *)ca_values)[ca_values_ndx]);
  switch (fd->type) {
   case R_SHORT:
    if      (ca_type == DB_SHORT) memcpy(fdat_short, cdat_short, sizeof(short)*nvals);
    else if (ca_type == DB_INT)   for (i=0; i<nvals; i++) fdat_short[i] = (short)cdat_int[i];
    else if (ca_type == DB_LONG)  for (i=0; i<nvals; i++) fdat_short[i] = (short)cdat_long[i];
    else if (ca_type == DB_FLOAT) for (i=0; i<nvals; i++) fdat_short[i] = (short)cdat_float[i];
    else if (ca_type == DB_DOUBLE)for (i=0; i<nvals; i++) fdat_short[i] = (short)cdat_double[i];
    else if (ca_type == DB_CHAR)  for (i=0; i<nvals; i++) fdat_short[i] = (short)cdat_char[i];
    else ctlerror(me,logic_err);
    break;
   case R_INT:
    if      (ca_type == DB_INT)   memcpy(fdat_int, cdat_int, sizeof(int)*nvals);
    else if (ca_type == DB_SHORT) for (i=0; i<nvals; i++) fdat_int[i] = (int)cdat_short[i];
    else if (ca_type == DB_LONG)  for (i=0; i<nvals; i++) fdat_int[i] = (int)cdat_long[i];
    else if (ca_type == DB_FLOAT) for (i=0; i<nvals; i++) fdat_int[i] = (int)cdat_float[i];
    else if (ca_type == DB_DOUBLE)for (i=0; i<nvals; i++) fdat_int[i] = (int)cdat_double[i];
    else if (ca_type == DB_CHAR)  for (i=0; i<nvals; i++) fdat_int[i] = (int)cdat_char[i];
    else ctlerror(me,logic_err);
    break;
   case R_LONG:
    if      (ca_type == DB_LONG)  memcpy(fdat_long, cdat_long, sizeof(long)*nvals);
    else if (ca_type == DB_SHORT) for (i=0; i<nvals; i++) fdat_long[i] = (long)cdat_short[i];
    else if (ca_type == DB_INT)   for (i=0; i<nvals; i++) fdat_long[i] = (long)cdat_int[i];
    else if (ca_type == DB_FLOAT) for (i=0; i<nvals; i++) fdat_long[i] = (long)cdat_float[i];
    else if (ca_type == DB_DOUBLE)for (i=0; i<nvals; i++) fdat_long[i] = (long)cdat_double[i];
    else if (ca_type == DB_CHAR)  for (i=0; i<nvals; i++) fdat_long[i] = (long)cdat_char[i];
    else ctlerror(me,logic_err);
    break;
   case R_FLOAT:
    if      (ca_type == DB_FLOAT) memcpy(fdat_float, cdat_float, sizeof(float)*nvals);
    else if (ca_type == DB_SHORT) for (i=0; i<nvals; i++) fdat_float[i] = (float)cdat_short[i];
    else if (ca_type == DB_INT)   for (i=0; i<nvals; i++) fdat_float[i] = (float)cdat_int[i];
    else if (ca_type == DB_LONG)  for (i=0; i<nvals; i++) fdat_float[i] = (float)cdat_long[i];
    else if (ca_type == DB_DOUBLE)for (i=0; i<nvals; i++) fdat_float[i] = (float)cdat_double[i];
    else if (ca_type == DB_CHAR)  for (i=0; i<nvals; i++) fdat_float[i] = (float)cdat_char[i];
    else ctlerror(me,logic_err);
    break;
   case R_DOUBLE:
    if      (ca_type == DB_DOUBLE)memcpy(fdat_double, cdat_double, sizeof(double)*nvals);
    else if (ca_type == DB_SHORT) for (i=0; i<nvals; i++) fdat_double[i] = (double)cdat_short[i];
    else if (ca_type == DB_INT)   for (i=0; i<nvals; i++) fdat_double[i] = (double)cdat_int[i];
    else if (ca_type == DB_LONG)  for (i=0; i<nvals; i++) fdat_double[i] = (double)cdat_long[i];
    else if (ca_type == DB_FLOAT) for (i=0; i<nvals; i++) fdat_double[i] = (double)cdat_float[i];
    else if (ca_type == DB_CHAR)  for (i=0; i<nvals; i++) fdat_double[i] = (double)cdat_char[i];
    else ctlerror(me,logic_err);
    break;
   case R_CHAR:
    if      (ca_type == DB_CHAR)  memcpy(fdat_char, cdat_char, sizeof(char)*nvals);
    else if (ca_type == DB_SHORT) for (i=0; i<nvals; i++) fdat_char[i] = (char)cdat_short[i];
    else if (ca_type == DB_INT)   for (i=0; i<nvals; i++) fdat_char[i] = (char)cdat_int[i];
    else if (ca_type == DB_LONG)  for (i=0; i<nvals; i++) fdat_char[i] = (char)cdat_long[i];
    else if (ca_type == DB_FLOAT) for (i=0; i<nvals; i++) fdat_char[i] = (char)cdat_float[i];
    else if (ca_type == DB_DOUBLE)for (i=0; i<nvals; i++) fdat_char[i] = (char)cdat_double[i];
    else ctlerror(me,logic_err);
    break;
   default: ctlerror(me,logic_err);
  }
  return(0);
}

#endif
