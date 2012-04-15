#include <stdio.h>            
#include "irs.h"
#include "irsctl.h"	
void ctlmsg1 (char msg[]) {	
  if (myid != 0) { return; }
  PRINT(stdout,"%s",msg);
  fflush(stdout);
  if (fpout != NULL) {
    PRINT(fpout,"%s",msg);
    fflush(fpout);
  }
}
