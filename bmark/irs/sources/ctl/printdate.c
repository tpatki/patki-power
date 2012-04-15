#include <time.h>
#include <string.h>
#include "irs.h"
int printdate( void ) {
   char msg[MAXLINE];
   char ctimestr[256];
   char *timestr;
   int len;
   time_t mytime;
   mytime = time(NULL);
   timestr = ctime(&mytime);
   ctimestr[255] = '\0';
   strncpy(ctimestr,timestr,255);
   len = strlen(ctimestr);
   ctimestr[len - 1] = ']';
   sprintf(msg,"[%s",ctimestr);
   ctlmsg(msg);
   return(0);
}
