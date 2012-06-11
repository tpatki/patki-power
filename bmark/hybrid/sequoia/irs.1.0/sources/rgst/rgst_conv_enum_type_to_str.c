#include "irs.h"
#include "irsrgst.h"
#include "Rgst.h"
int rgst_conv_enum_type_to_str(
  char *               enum_typedef_name,  
  GENERIC_ENUM_TYPEDEF enum_type,          
  char                 enum_type_str[])    
{
  char *me = "rgst_conv_enum_type_to_str";
  char msg[256];
  RGST_EnumTypeDef_t *enum_defn = NULL;
  RGST_Datatype_t data_type;
  int ndx;
  enum_defn = rgst_get_td_defn(enum_typedef_name, R_ENUM_TYPEDEF, NULL);
  if (enum_defn == NULL) ctlerror(me,logic_err);
  ndx = (int)enum_type;
  if (ndx >= enum_defn->num_entries) {
    sprintf(msg,"%d is an enumerated type number for enumerated type '%s'",
                ndx,enum_typedef_name);
    ctlerror(me,msg);
  }
  strcpy(enum_type_str,enum_defn->entry_strings[ndx]);
  return(0);
}
GENERIC_ENUM_TYPEDEF rgst_conv_str_to_enum_type(
  char *  enum_typedef_name,  
  char    enum_type_str[])    
{
  char *me = "rgst_conv_str_to_enum_type";
  char msg[128];
  int i;
  RGST_EnumTypeDef_t *enum_defn = NULL;
  GENERIC_ENUM_TYPEDEF enum_type;
  enum_defn = rgst_get_td_defn(enum_typedef_name, R_ENUM_TYPEDEF, NULL);
  if (enum_defn == NULL) ctlerror(me,logic_err);
  for (i=0; i<enum_defn->num_entries; i++) {
    if (strcmp(enum_type_str,enum_defn->entry_strings[i]) == 0) break;
  }
  if (i<enum_defn->num_entries) {
    enum_type = (GENERIC_ENUM_TYPEDEF)i;
  }
  else {
    sprintf(msg,"'%s' is not a valid enumerated type for type '%s'",
                enum_type_str,enum_typedef_name);
    ctlwarning(me,msg);
    enum_type = (GENERIC_ENUM_TYPEDEF)-1;
  }
  return(enum_type);
}
