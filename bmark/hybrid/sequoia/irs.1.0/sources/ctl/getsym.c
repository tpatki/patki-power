#include <signal.h>
#include "irs.h"
#include "irsctl.h"
void getsym( void )
{
   char *tsym ;
   char star ;
   if (ifcomfg) star = '*' ;
   else         star = '\0' ;
   tsym = sym;
   if ( ps == NULL )  ps = line ;
   while ((*ps == ' ') || (*ps == '\t'))  ps++ ;
   if ((*ps != '\0') && (*ps != '\n') && (*ps != star)) {
      *(tsym++) = *ps;
      if (ifnotin(nospace,ps++)) {
         while (ifnotin(delim, ps)) *(tsym++) = *(ps++);
      }
      while ((*ps == ' ') || (*ps == '\t'))  ps++ ;
      if ((*ps == '\n') || ((ifcomfg) && (*ps == '*'))) {
         ctlflag = iflf ;
         ps++ ;
      } else {
         ctlflag = 0;
      }
      if (ifplusmin) {
         iplusmin = 0 ;
         tsym-- ;
         if (*tsym == '+')  iplusmin =  1 ;
         if (*tsym == '-')  iplusmin = -1 ;
         if (iplusmin == 0)    tsym++ ;
      }
      *tsym = '\0';
   } else {
      ps = NULL ;
   } 
   return ;
}
