
#include <signal.h>
#include "irs.h"
#include "irsctl.h"

void outfile(char     *filename )
{
   char *me = "outfile";
   char msg[256];
   char fullname[MAXLINE * 2];
   char outname[MAXLINE *2];
   memset(fullname,'\0',MAXLINE);

/*
fprintf(stderr,"%s DEBUG myid=%d filename=%s child_io_off=%d TRUE=%d\n",
        me,myid,filename,child_io_off,TRUE);

*/

                        /* disable child i/o if requested */

   if (child_io_off == TRUE) {

      if (myid != 0) {
         fpout = NULL;
         return;
      }

   } 

   if (child_io_todir == TRUE) {

      if (myid != 0) {

         sprintf(outname,"%s/%s-%04i-hsp",child_outpath,pbnm,myid);
         strcpy(fullname,outname);
         fpout = fopen(fullname, "wt") ;
         if (fpout == NULL) {
            perror(me);
            sprintf(msg,"fopen of file '%s' failed",fullname);
            ctlerror(me,msg);
         }
         return;
      }
   }


   /* if we reach here we are either the master process or */
   /* theeir is not child process short circuit or file redirection */


      sprintf(outname,"%s-%04i-hsp",pbnm,myid);
      strcpy(fullname,outpath);
      strcat(fullname,outname);
      fpout = fopen(fullname, "wt") ;
      if (fpout == NULL) {
         perror(me);
         sprintf(msg,"fopen of file '%s' failed",fullname);
         ctlerror(me,msg);
      }

}


#ifdef OLD_VERSION

#include <signal.h>
#include "irs.h"
#include "irsctl.h"

void outfile(char     *filename )
{
   char *me = "outfile";
   char msg[256];
   char fullname[MAXLINE]; 
   char outname[MAXLINE]; 
   memset(fullname,'\0',MAXLINE);

/*
fprintf(stderr,"%s DEBUG myid=%d filename=%s child_io_off=%d TRUE=%d\n",
        me,myid,filename,child_io_off,TRUE);
*/

   if (child_io_off == TRUE) {
      if (myid != 0) {
         fpout = NULL;
         return;
      }
   }
/*
fprintf(stderr,"%s DEBUG OOPS myid=%d filename=%s\n",me,myid,filename);
*/

   if (myid != 0) {

      sprintf(outname,"%s-%04i-hsp",pbnm,myid);
      strcpy(fullname,outpath);
      strcat(fullname,outname);
      fpout = fopen(fullname, "wt") ;
      if (fpout == NULL) {
        perror(me);
        sprintf(msg,"fopen of file '%s' failed",fullname);
        ctlerror(me,msg);
      }
   } else {

      strcpy(fullname,outpath);
      strcat(fullname,filename);
      fpout = fopen(fullname, "wt") ;
      if (fpout == NULL) {
        perror(me);
        sprintf(msg,"fopen of file '%s' failed",fullname);
        ctlerror(me,msg);
      }
   }
}

#endif
