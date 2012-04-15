#include <stdio.h>     
#include "irs.h"
#include "irsctl.h"	
#include "FunctionTimer.h"
#include "irscom.h"	
void ctlmsg (char msg[]) {	
  if (myid != 0) { return; }
  PRINT(stdout,"%s\n",msg);
  fflush(stdout);
  if (fpout != NULL) {
    PRINT(fpout,"%s\n",msg);
    fflush(fpout);
  }
}
