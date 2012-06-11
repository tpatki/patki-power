#include <stdio.h>
#include <string.h>
#include "irs.h"
#include "irsctl.h"
#include "irsrgst.h"
#include "Rgst.h"
#ifndef _POSIX_SOURCE
#define _POSIX_SOURCE 1
#endif
void get_words_at_prompt(
  char *str, 	
  int  str_len) 
{
  char *me = "get_words_at_prompt";
  char tmpstr[256], msg[256];
  int expsave;
  int plmsave;
  int comsave;
  memset(str,'\0',str_len);
  expsave = ifexp;
  comsave = ifcomfg;
  plmsave = ifplusmin;
  ifexp = 0;
  ifcomfg = 0;
  ifplusmin = 0;
  do {
    memset(tmpstr,'\0',256);
    peekc2(tmpstr);
    if (   (strcmp(tmpstr,"$")     == 0) 
        || (strcmp(tmpstr,"fm")    == 0)) {
      break;
    }
    geta(tmpstr);
    if (strlen(str) > 0) strcat(str," ");   
    if ((strlen(str) + strlen(tmpstr)) >= str_len) {
      sprintf(msg,"Tell programmer to increase str_len to at least %d",
                  (int)(strlen(str) + strlen(tmpstr)));
      ctlnotice(me,msg);
    }
    else {
      strcat(str,tmpstr);			
    }
    if ((ps != NULL) && (*ps == '$')) break; 
  } while (ctlflag != iflf);
  ifexp     = expsave;
  ifcomfg   = comsave;
  ifplusmin = plmsave;
}
