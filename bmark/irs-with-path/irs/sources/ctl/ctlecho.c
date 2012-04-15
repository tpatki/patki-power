#include "irs.h"
#include "irsctl.h"
int ctlecho (void) {
  char *me = "ctlecho";
  char msg[MAXLINE];
  char op[MAXLINE];
  int j;
  if (ps == NULL) {
    sprintf(msg,"Echo string must be in quotes");
    ctlwarning(me,msg);
    return(0);
  }
  if (*ps != '\"') {
    sprintf(msg,"Echo string must be in quotes");
    ctlwarning(me,msg);
    return(0);
  }
  *ps++;
  j = 0;
  while ((j != MAXLINE) && (*ps != '\0') && (ps != NULL) && (*ps != '\"')) { 
     msg[j++] = *ps;
     *ps++;
  }
  msg[j] = '\0';

  if (myid == 0) {
    PRINT(stdout,"%s",msg);
    if (fpout != NULL) {
       PRINT(fpout,"%s",msg);
    }
  }

  if (*ps == '\"') {
     *ps++;
  } else {
    ctlwarning(me,"Hit end of line without finding close quote in echo.");
  } 
  peekc(op);
  if (!strcmp(op,",")) {
    geta(op);
  } else {
     if (myid == 0) {
       PRINT(stdout,"\n");
       if (fpout != NULL)  {
          PRINT(fpout,"\n");
       }
     }
  } 
  return(0);
}
