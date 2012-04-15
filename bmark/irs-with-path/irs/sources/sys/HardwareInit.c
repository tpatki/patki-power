#include "irs.h"
#include "irssys.h"
#ifdef osf1
#include <machine/fpu.h>
#endif
void HardwareInit( void )
{
#ifdef osf1
   unsigned long fpcontrolmask = 0x000000;  
   fpcontrolmask |=  IEEE_INHERIT ;
   fpcontrolmask |=  IEEE_TRAP_ENABLE_INV ;
   fpcontrolmask |=  IEEE_TRAP_ENABLE_DZE ;
   fpcontrolmask |=  IEEE_TRAP_ENABLE_OVF ;
   fpcontrolmask |=  IEEE_MAP_DMZ ; 
   fpcontrolmask |=  IEEE_MAP_UMZ ; 
   ieee_set_fp_control( fpcontrolmask ) ;
#endif
}
