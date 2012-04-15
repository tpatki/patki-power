#include "irs.h"
#include "irsobjects.h"
static char ObjectName[MAXLINE];
static int  ObjectName_set = 0;
int ObjectName_input(void ) {
   char *me = "ObjectName_input";
   geta(ObjectName);
   ObjectName_set = 1;
   return(0);
}
char *ObjectName_get(void) {
   if (ObjectName_set == 1) {
      ObjectName_set = 0;
      return(ObjectName);
   }
   return(NULL);
}
