#include <stdio.h>
#include <stdlib.h>
#include "irs.h"
#include "irsrgst.h"
#include "Rgst.h"
#include "Command.h"
Command_t * build_proc_name(
  char *struct_name,        
  char *procedure_suffix,   
  char *routine_name)       
{
  char *me = "build_proc_name";
  char msg[256];
  int  i, len;
  Command_t *cp = NULL;
  strcpy(routine_name,struct_name);
  len = strlen(routine_name);
  if (len > 2) {
    if ( (routine_name[len-1] == 't') && (routine_name[len-2] == '_') ) {
      routine_name[len-1] = '\0';
      routine_name[len-2] = '\0';
    }
  }
  strcat(routine_name,"_");
  strcat(routine_name,procedure_suffix);
  if (rgst_check_for_obj(routine_name) == TRUE) {
    if ((cp = (Command_t *)rgst_get_t(routine_name,"function")) == NULL) {
      sprintf(msg,"%s is in the registry, but it is not a function",routine_name);
      ctlwarning(me,msg);
    }
  }
  return(cp);
}
