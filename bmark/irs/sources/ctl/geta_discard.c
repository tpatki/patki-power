#include <stdio.h>
#include <string.h>
#include "irs.h"
#include "irsctl.h"
#ifndef _POSIX_SOURCE
#define _POSIX_SOURCE 1
#endif
void geta_discard(int verbose) 
{
  char tempstr[256];
  if (verbose == TRUE) ctlmsg1("Discarding following unneeded tokens at end of line:\n\t");
  while (ctlflag != iflf) {
    peekc(tempstr);
    if (strcmp(tempstr,"$") != 0) {
      geta(tempstr);
      if (verbose == TRUE) ctlmsg1(tempstr);
      if (ps != NULL)  {
        if (*ps == '$') {
          ps = NULL;
          break;
        }
      }
    }
  }
  if (verbose == TRUE) ctlmsg("");
}
