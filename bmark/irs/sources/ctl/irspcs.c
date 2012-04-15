void irspcs_register(void) ;
int irspcs_check(void) ;
#ifdef PCS
#include <signal.h>
#include <time.h>
#include "irs.h"
int checkvalue = 0;
time_t stoptime;
void irspcs_register(void) {
   char *me  = "irspcs_register";
   char msg[MAXLINE];
   int error;
   int status;
   time_t mintime;
   mintime = (time_t) warntime;
   error = pcswarn(SIGXCPU, mintime, &checkvalue, &stoptime, &status);
   if (error != 0) { 
      sprintf(msg,"DPCS return an error during initialization.");
      ctlwarning(me,msg);
   }
   return;
}
int irspcs_check(void) {
   return(checkvalue);
}
#else 
void irspcs_register(void) {
   return;
}
int irspcs_check(void) {
   return(0);
}
#endif 
