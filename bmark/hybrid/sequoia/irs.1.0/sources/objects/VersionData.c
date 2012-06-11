#include <stdlib.h>
#include "irsdefs.h"
#include "VersionData.h"
VersionData_t *VersionData_destruct(VersionData_t *ptr)
{
  FREEMEM(ptr->node_compiled);
  FREEMEM(ptr->date_compiled);
  FREEMEM(ptr->time_compiled);
  FREEMEM(ptr->os_compiled);
  FREEMEM(ptr->opt_compiled);
  FREEMEM(ptr->dump_version);
  FREEMEM(ptr->person);
  FREEMEM(ptr);
  return(NULL);
}
