#include "irs.h"
#include "irscom.h"
#include "irsdmp.h"
#include "mach.h"
#include "cgl.h"
#include "FunctionTimer.h"
#ifdef SILO
int rgfxstate( DBfile *idbid )
{
   int ierr;
   if (num_procs > 1) return(0);
   ierr = DBSetDir(idbid, "/Global");
   return(ierr);
}   
#endif
