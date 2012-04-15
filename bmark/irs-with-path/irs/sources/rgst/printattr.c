#include "irs.h"
#include "irsrgst.h"
#include "irsctl.h"
#include "irsdefs.h"
#include "Hash.h"
#include "Rgst.h"
static void print_attr_type (
  AttrArray_t *ptr)   
{
  int i;
  if (ptr->num_attrs > 0) {
    for (i=0; i<ptr->num_attrs; i++) {
      printf("\t%s\n",ptr->attrs[i]->attr_name);
    }
  }
}
int printattr(void) {
  char *me = "printattr";
  char str[STRLEN], msg[512];
  int  i, fld_ndx;
  RGST_Datatype_t       data_type;
  char *token = NULL, *type_name = NULL, *fld_name = NULL;
  void                *td = NULL;
  RGST_Object_t         *ro = NULL;
  RGST_StructTypeDef_t *sd = NULL;
  RGST_EnumTypeDef_t   *ed = NULL;
  RGST_CTypeDef_t  *cd = NULL;
  RGST_Field_t          *fd = NULL;
  get_words_at_prompt(str, STRLEN);
  token = strtok(str," .");
  if (strcmp(token,"help") == 0) {
    sprintf(msg,"\n\t'printattr' or 'pa' prints the attributes of an object or structure and fields \n\t"
                "\n\tExample:\n\t"
                "\n\tpa domains       Prints attributes of the object 'domains'");
    ctlnotice(me,msg);
    return(0);
  }
  if (rgst_check_for_obj(token) == TRUE) {
    ro = rgst_get_RGST_Object_t(token);
    printf("Object '%s' has %d attributes\n",
             token,ro->attributes->num_attrs);
    print_attr_type(ro->attributes);
    return(0);
  }
  if (rgst_check_for_td_defn(token) == TRUE) {
    td = rgst_get_td_defn(token,NUM_RGST_Datatype_t, &data_type);
    switch (data_type) {
     case R_STRUCT:
     case R_STRUCT_TYPEDEF:
      type_name = token;
      fld_name  = strtok(NULL,". \0");
      sd  = (RGST_StructTypeDef_t *)td;
      if (fld_name == NULL) {
        printf("Structure '%s' has %d attributes\n",
               token,sd->attributes->num_attrs);
        print_attr_type(sd->attributes);
        for (i=0; i<sd->num_fields; i++) {
          fd = &(sd->fields[i]);
          if (fd->attributes->num_attrs > 0) {
            printf("  Field '%s' of structure '%s'  has %d attributes\n",
                      fd->name, type_name,
                      fd->attributes->num_attrs);
            print_attr_type(fd->attributes);
          }
        }
      }
      else {
        if ((fld_ndx = rgst_get_ds_field_ndx(sd, fld_name)) < 0) {
          ; 
        }
        else {
          fd = &(sd->fields[fld_ndx]);
          printf("  Field '%s' of structure '%s'  has %d attributes\n",
                    fd->name, type_name,
                    fd->attributes->num_attrs);
          if (fd->attributes->num_attrs > 0) {
            print_attr_type(fd->attributes);
          }
        }
      }
      break;
     case R_CTYPE_TYPEDEF:
      cd   = (RGST_CTypeDef_t *)td;
      printf("C typedef '%s' has %d attributes\n",
             token,cd->attributes->num_attrs);
      print_attr_type(cd->attributes);
      break;
     case R_ENUM_TYPEDEF:
      ed    = (RGST_EnumTypeDef_t *)td;
      printf("Enumerated typedef '%s' has %d attributes\n",
             token,ed->attributes->num_attrs);
      print_attr_type(ed->attributes);
      break;
     default: break;
    }
    return(0);     
  }
  sprintf(msg,"\n\t'%s' is not an object or typedef",token);
  ctlnotice(me,msg);
  return(0);
}
