#include "irs.h"
extern int pccsoff;
int prirup( void )
{
   int sus ;
   char userirup[10];
   sus = 0 ;
   fgets(userirup, 10, stdin);
   if ( (!strcmp(userirup, "c\n")    ) ||
        (!strcmp(userirup, "t\n")    ) ||
        (!strcmp(userirup, "cycle\n")) ||
        (!strcmp(userirup, "time\n") ) ) {
      printtc() ;
   } else if ( (!strcmp(userirup, "r\n")  ) ||
               (!strcmp(userirup, "rad\n")) ) {
      printrc() ;
   } else if (!strcmp(userirup, "wdmp\n")) {
      sus = 1 ;
   } else if (!strcmp(userirup, "wgdmp\n")) {
      sus = 2 ;
   } else if ( (!strcmp(userirup, "stop\n") ) ||
               (!strcmp(userirup, "pause\n")) ) {
      sus     = -1 ;
      pccsoff =  1 ;
   } else if ( (!strcmp(userirup, "quit\n")) ||
               (!strcmp(userirup, "end\n") ) ) {
      sus     = -2 ;
      pccsoff =  1 ;
   } else if ( (!strcmp(userirup, "?\n")   ) ||
               (!strcmp(userirup, "h\n")   ) ||
               (!strcmp(userirup, "help\n")) ) {
      PRINT(stdout,"Help for Run Interrupt Commands:\n");
      PRINT(stdout,"   c, t, cycle, time : Print timestep info\n");
      PRINT(stdout,"   r, rad            : Print radiation info\n");
#ifdef SILO
      PRINT(stdout,"   wdmp, wgdmp       : Dump restart or graphics file\n");
#endif
      PRINT(stdout,"   stop, pause       : Suspend run & accept commands\n");
      PRINT(stdout,"   quit, end         : Terminate execution completely\n");
      PRINT(stdout,"   ?, h, help        : Display this help info\n");
      PRINT(stdout,"   v, version        : Print compile version info\n");
   } else if ( (!strcmp(userirup, "v\n")      ) ||
               (!strcmp(userirup, "version\n")) ) {
      pversion();
   } else if (strcmp(userirup, "\n")) {
      /* PRINT(stdout, "%s %s", "Unknown interrupt command:", userirup); */
   }
   return(sus) ;
}
