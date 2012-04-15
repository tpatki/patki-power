#include <stdio.h>
#include <string.h>
#include "irs.h"
#include "irs.h"
#include "Hash.h"
#include "irsrgst.h"
#include "Rgst.h"
#ifndef _POSIX_SOURCE
#define _POSIX_SOURCE 1
#endif
#define DASH4   "----"
#define DASH8   "--------"
#define DASH12  "------------"
#define DASH15  "---------------"
#define DASH20  "--------------------"
#define DASH32  "--------------------------------"
#define DASH50  "--------------------------------------------------"
void rgst_print_struct_td_defn(
  RGST_StructTypeDef_t *sd)     
{
  int  i, j, padding;
  long field_size, offset_count = 0;
  char type[R_MAXSTR+1], tstr[R_MAXSTR+1], tstr2[R_MAXSTR+1];
  printf("\nPrint of %s structure definition of %d bytes\n",
         sd->name,(int)sd->struct_size);
  printf("%-32s %-50s %-8s %-4s %-8s "
         "%-32s %-20s\n",
         "field",    "type", "offset", "size",  "fieldsiz",
         "array size","str array size");
  printf("%-32s %-50s %-8s %-4s %-8s "
         "%-32s %-20s\n",
         DASH32, DASH50, DASH8, DASH4, DASH8, 
         DASH32, DASH20);
  for (i=0; i<sd->num_fields; i++) {
    if (offset_count != sd->fields[i].offset) {
      padding = (int)(sd->fields[i].offset - offset_count);
      printf("%-32s %-50s %-8ld %-4d %-8ld "
             "%-32s\n",
              "", "padding", 
              offset_count, 1, (long) padding,
              "");
      offset_count += padding; 
    }
    field_size = sd->fields[i].type_size;
    for (j=0; j<sd->fields[i].ndims; j++) {
      field_size = field_size * sd->fields[i].dims[j];
    }
    rgst_create_typedef_name_str (sd->fields[i].type,
                                  sd->fields[i].td_name,
                                  sd->fields[i].nptrs,
                                  sd->fields[i].ndims,
                                  sd->fields[i].dims,
                                  type);
    if      (sd->fields[i].array_size_type == FIELD_OFFSET) 
      sprintf(tstr,"field offset %ld",sd->fields[i].array_size_field_offset);
    else if (sd->fields[i].array_size_type == GLOBAL_VAR)
      sprintf(tstr,"global var '%s'",sd->fields[i].array_size_global_var);
    else if (sd->fields[i].array_size_type == ABSOLUTE_VALUE)
      sprintf(tstr,"abs val %ld",sd->fields[i].array_size_absolute_val);
    else 
      memset(tstr,'\0',R_MAXSTR+1);
    if (sd->fields[i].str_array_size_field_offset >=0)
      sprintf(tstr2,"field offset %ld",sd->fields[i].str_array_size_field_offset);
    else 
      memset(tstr2,'\0',R_MAXSTR+1);
    printf("%-32s %-50s %-8ld %-4d %-8ld "
           "%-32s %-20s\n",
            sd->fields[i].name,
            type,
            sd->fields[i].offset,
            (int) sd->fields[i].type_size,
            field_size,
            tstr,tstr2);
    offset_count += field_size;
  }
  if (offset_count != sd->struct_size) {
    padding = sd->struct_size - offset_count;
    printf("%-32s %-50s %-8ld %-4d %-8ld "
           "%-8s %-8s\n",
            "", "padding",
            offset_count, 1, (long) padding,
            "", "");
  }
}
