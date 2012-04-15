#include <signal.h>
#include "irs.h"
#include "irsctl.h"
#include "Gparm.h"
void parmsym( void )
{
   int i;
   char tsym[MAXWORD];
   int ifparm_save;
   int ifcomfg_save;
   if ((ifexp) && (!strcmp(sym,"{"))) {
      ifplusmin = 0;
      ifparm_save = ifparm;
      ifcomfg_save = ifcomfg;
      ifcomfg = 0;
      ifparm = 1;
      strcpy(delim, " ,[]{}():;$%*^+-~/\n\r\t"); 
      strcpy(nospace,",[]{}();:%*^+-~/") ;
      expressions_eval(tsym);
      ifparm = ifparm_save; 
      ifcomfg = ifcomfg_save;
      ifplusmin = 1;
      strcpy(sym,tsym);
      strcpy(delim, " ,[]{}():;$%\n\r\t");
      strcpy(nospace,",[]{}();:%") ;
   }  else {
      for ( i = 1 ; i <= ngparm ; i++ ) {
         if (!strcmp(sym, gparm[i].sym)) {
            strcpy(sym, gparm[i].val) ;
            break ;
         }
      }
   } 
}
