#include <stdio.h>
#include <string.h>
#include "irs.h"
#include "irsctl.h"
#ifndef _POSIX_SOURCE
#define _POSIX_SOURCE 1
#endif
int geta_leftparen(void) 
{
  char *me = "geta_leftparen";
  char nextsym[MAXLINE], msg[MAXLINE];
  int ierr = 0;
  geta(nextsym);
  if (nextsym[0] != '(') { 
    sprintf(msg,"Expected '(', found \n\t'%s'",nextsym);
    ctlnotice(me,msg);
    ierr = -1;
  }
  return(ierr);
}
