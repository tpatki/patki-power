#include "irs.h"
#include "irsctl.h"
void nxtsym(int ifadvance)
{
   char *me = "nxtsym";	 
   char *ps2 ;
   char fullprompt[24];
   if (symflag == 0) {
      if (ps != NULL)  getsym() ;
      if ( (ps == NULL) && (pdmd == 1) ) {
         ps   = lnbuf;
         line = lnbuf;
         ctlwarning(me,"hit string terminator in nxtsym under domsg" );
      }
      if ( (ps == NULL) && (ifadvance == 0) ) return ;
      while ( ps == NULL ) {
         if (fpin == stdin) {
	   if (pccsflag) {
	     if (pccsoff) {
	       if ( pccsoff == 1 ) {
                  PRINT(stdout, "%s in interactive mode\n",codename) ;
	       }
	       pccsoff++ ;
	     } else {
	       PRINT(stdout, "%s in production controller mode\n",codename);
	     }
	   }
           if (ifhilite) {
              sprintf(fullprompt, YELOTXT "%s>" NRMLTXT, prompt);
           } else {
	      sprintf(fullprompt, "%s>", prompt) ;
           }
	 }
         if ( lineop_get(line, MAXLINE, fpin, fullprompt) == NULL ) {
            strcpy(line, "done");
            ps = line ;
         } else {
            if (iomrkflag) {
	       if (strlen(iomrkstr) == 0) {
                  strcpy(iomrkstr,line) ;
               } else {
                  strcat(iomrkstr,line) ;
	       }
               if (fpout != NULL) {
                  if (ifecho) { PRINT(fpout, "%s", line) ; }
               }
            }
	 }
         ps2 = line ;
         while ( (*ps2 != '{') && (*ps2 != '\0') && (*ps2 != '\n') ) {
            if (( ifcomfg ) && ( *ps2 == '*' )) {
               *ps2 = '\n' ;
               ps2++ ;
               *ps2 = '\0' ;
               break ;
            }
            ps2++ ;
         }
         getsym() ;
      }
      if ( *ps == '\0' )  ps = NULL ;
      if (ifparm) parmsym() ;
      symflag = 1 ;
   }
}
