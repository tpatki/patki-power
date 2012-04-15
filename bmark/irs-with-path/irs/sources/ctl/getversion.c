#include "irsversion.h"
#include "irs.h"
#include "irsdmp.h"
#include "VersionData.hh"
void getversion(void) 
{
   gv_ver.node_compiled = strsave(VER_NODENAME);
   gv_ver.date_compiled = strsave(VER_DATE);
   gv_ver.time_compiled = strsave(VER_TIME);
   gv_ver.os_compiled   = strsave(VER_OS);
   gv_ver.opt_compiled  = strsave(VER_OPT);
   gv_ver.dump_version  = strsave(VER_DUMP);
   gv_ver.person        = strsave(VER_PERSON);
}
