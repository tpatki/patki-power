#include <stdio.h>                      
#include <stdlib.h>
#include <stdarg.h>
#include "irs.h"
#include "irsctl.h"
#include "AEStackElm.h"
#include "Rgst.h"
int ctloutput(
  char * routine,       
  char * label,         
  RGST_Datatype_t type, 
  ...)
{
  char *me = "ctloutput";
  char msg[MAXLINE], tmsg[128];
  int ival, *iarr, len, i;
  double dval, *darr;
  va_list ap;
  if (routine == NULL) ctlerror(me,"routine must be specified");
  memset(msg,'\0',MAXLINE);
  if (label == NULL) { strcpy(msg,routine); }
  else               { strcpy(msg,label);   }
  strcat(msg," = ");
  va_start(ap, type);
  switch (type) {
    case R_INT:
      ival = va_arg(ap,int);
      if (output_dest == TO_STACK) {
        ae_stack_push(routine,label,type,ival);
      }
      else {
        sprintf(tmsg,"%d",ival);
        strcat(msg,tmsg);
        ctlmsg(msg);
      }
      break;
    case R_DOUBLE:
      dval = va_arg(ap,double);
      if (output_dest == TO_STACK) {
        ae_stack_push(routine,label,type,dval);
      }
      else {
        sprintf(tmsg,"%.9e",dval);
        strcat(msg,tmsg);
        ctlmsg(msg);
      }
      break;
    case R_INT_ARRAY:
      iarr = va_arg(ap,int *);
      len  = va_arg(ap,int);
      if (output_dest == TO_STACK) {
        ae_stack_push(routine,label,type,iarr,len);
      }
      else {
        ctlmsg(msg);
        sprintf(msg,"\t");
        for (i=0; i<len; i++) {
          sprintf(tmsg,"%9d ",iarr[i]);
          strcat(msg,tmsg);
          if ((i+1)%5 == 0) {
            ctlmsg(msg);
            sprintf(msg,"\t");
          }
        }
        if (len%5 != 0) {
          ctlmsg(msg);
        }
      }
      break;
    case R_DOUBLE_ARRAY:
      darr = va_arg(ap,double *);
      len  = va_arg(ap,int);
      if (output_dest == TO_STACK) {
        ae_stack_push(routine,label,type,darr,len);
      }
      else {
        ctlmsg(msg);
        sprintf(msg,"\t");
        for (i=0; i<len; i++) {
          sprintf(tmsg,"%.9e ",darr[i]);
          strcat(msg,tmsg);
          if ((i+1)%5 == 0) {
            ctlmsg(msg);
            sprintf(msg,"\t");
          }
        }
        if (len%5 != 0) {
          ctlmsg(msg);
        }
      }
      break;
    default:
      ctlerror(me,"type is invalid");
  }
  va_end(ap);        
  return(0);
}
