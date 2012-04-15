#include "irs.h"
#include "irsgen.h"
int  isbeta(
	    char     *sym )
{
   int c,flag ;
   c = sym[0] ;
   flag = 0 ;
   if (('a' <= c) & (c <= 'z'))  flag = 1 ;
   if (('A' <= c) & (c <= 'Z'))  flag = 1 ;
   return(flag) ;
}
