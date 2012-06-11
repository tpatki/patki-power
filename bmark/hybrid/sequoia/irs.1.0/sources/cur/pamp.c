#include "irs.h"
#include "cgl.h"
#include "irscur.h"
static void pamp_write( int cn ) ;
int pamp( void ) {
   int cn, cflag ;
   cn = geti(&cflag) ;
   if (myid == 0) pamp_write(cn) ;
   return(0) ;
}
static void pamp_write( int cn ) {
   char *me = "pamp_write";
   char msg[256];
   int i ;
   if (ifcuron[cn] == 0) {
      sprintf(msg,"can't write pamp curve for curve %d",cn);
      ctlnotice(me,msg);
   } else {
      strcpy(msg,outpath);
      strcat(msg,pbnm);
      strcat(msg,".cur");
      fpamp = fopen(msg,"at");       
      if (fpamp == 0) {
         fpamp = fopen(msg,"wt");       
      }
      fprintf(fpamp,"# %d %s vs. %s\n",cn,p1d[2*cn].namelab, p1d[2*cn+1].namelab) ;
      for ( i = 0 ; i < p1d[2*cn+1].palen ; i++ ) {
         fprintf(fpamp," % e   % e\n",p1d[2*cn+1].fpa[i], p1d[2*cn].fpa[i]) ;
      }
      fprintf(fpamp,"end\n") ;
      fclose(fpamp);
   }
}
