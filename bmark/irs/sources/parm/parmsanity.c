#include "irs.h"
#include "irsparm.h"
#include "irseos.h"
void parmsanity( void )
{
   char *me = "parmsanity" ;
   if ( ndims == 3 ) ifplane = 0 ;
   if ( (iftion == 1) || (ngroup > 0) || (ifedif == 1) || (ifidif == 1) ) {
      ioneq = 1 ;
   }
   if ( if_eos_mix_zeq == 1 ) {
      ioneq = 1 ;
   }
   eifrac = 1.0 ;
}
