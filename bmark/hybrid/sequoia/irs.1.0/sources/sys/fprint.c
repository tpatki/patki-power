#include "irs.h"
#include "irssys.h"
void fprint_( char *s, int *err ) {
   char t[80] ;
   strncpy(t,s,40) ;
   printf( "%s  %x\n", t, *err ) ;
}
