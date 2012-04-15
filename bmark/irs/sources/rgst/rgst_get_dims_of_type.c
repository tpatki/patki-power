#include <stdio.h>                      
#include <stdlib.h>                     
#include "irs.h"             
#include "irsrgst.h"
#include "Rgst.h"
void rgst_get_dims_of_type(
  char *type_str,	
  int  *nptrs,		
  int  *ndims,		
  int  dims[3])		
{
  char *me = "rgst_get_dims_of_type";
  char msg[128];
  int i, j;
  int my_nptrs = 0;
  int my_ndims = 0;
  dims[0] = dims[1] = dims[2] = 0;
  sprintf(msg,"\n\tType '%s' is bad\n\t",type_str);
  for (i=0; i<strlen(type_str); i++) {
    if (type_str[i] == '*') {
      type_str[i] = ' ';
      my_nptrs++;
      if (my_nptrs > 2) {
        strcat(msg,"tRegistry object must be no more than 2 ptrs deep");
        ctlerror(me,msg);
      }
    }
  }
  for (i=0; i<strlen(type_str); i++) {
    if (type_str[i] == '[') {
      if (my_ndims >= 3) {
	strcat(msg,"Registry object must be no more than a 3 dimensional array");
        ctlerror(me,msg);
      }
      type_str[i] = ' ';
      i++;
      if ((type_str[i] >= '0') && (type_str[i] <= '9')) {
        dims[my_ndims] = atoi(&type_str[i]);
        for ( ; i<strlen(type_str); i++) {
          if (type_str[i] == ']') { break; }
          type_str[i] = ' ';
        }
        if (i == strlen(type_str)) {
          strcat(msg,"Did not find ']'");
          ctlerror(me,msg);
        }
        type_str[i] = ' ';
      }
      else {
        strcat(msg,"Did not find integer after '['");
        ctlerror(me,msg);
      }
      my_ndims++;
    }
  }
  for (i = strlen(type_str) - 1; i >= 0; i--) {
    if (type_str[i] == ' ') type_str[i] = '\0';
    else                    break;
  }
  for (i=0; i<strlen(type_str); i++) {
    if (type_str[i] == ' ') {
      for (j=i; j<strlen(type_str); j++) {
        type_str[j] = type_str[j+1];  
      }
    }
    else {
      break;
    }
  }
  *nptrs = my_nptrs;
  *ndims = my_ndims;
}
