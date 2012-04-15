#include "irs.h"
#include "VersionData.h"
void pversion(void) 
{
   PRINT(stdout,"Build Date    : %s at %s\n",gv_ver.date_compiled,
                                             gv_ver.time_compiled); 
   PRINT(stdout,"Target OS     : %s \n",gv_ver.os_compiled);
   PRINT(stdout,"Build Host    : %s \n",gv_ver.node_compiled);
   PRINT(stdout,"Compile Target: %s \n",gv_ver.opt_compiled);
   PRINT(stdout,"Dump Version  : %s \n",gv_ver.dump_version);
   PRINT(stdout,"Compiled by   : %s \n",gv_ver.person);
#ifdef COMMPI
   PRINT(stdout,"Compiled with MPI.\n");
#endif
#ifdef OPENMP
   PRINT(stdout,"Compiled with OpenMP Threads.\n");
#endif
   fflush(stdout);
}
