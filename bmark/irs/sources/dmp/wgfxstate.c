#include "irs.h"
#include "irsdmp.h"
#include "mach.h"
#include "cgl.h"
#ifdef SILO
int  wgfxstate( DBfile *idbid )
{
   int ierr;
   int len;
   int dims[1];
   ierr = DBSetDir(idbid, "/Global");
   dims[0] = 1;
   return(ierr);
}   
#endif
