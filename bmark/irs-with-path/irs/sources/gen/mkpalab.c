#include "irs.h"
#include "irsgen.h"
void mkpalab( char *lab,  char *aname,  int iblk, int my_in[NRANKX][3],
              int  nrank, int  roptype, char *rop )
{
   int irank ;
   char tmp[MAXLINE] ;
   if ( roptype > 0 ) {
      sprintf(lab,"%s;%s:%d(",aname,rop,iblk) ;
   } else {
      sprintf(lab,"%s:%d(",aname,iblk) ;
   }
   if ( nrank == 1 ) {
      for ( irank = 0 ; irank < nrank ; irank++ ) {
         if (my_in[irank][0] == my_in[irank][1]) {
            sprintf(tmp,"%d",my_in[irank][0]) ;
         } else {
            sprintf(tmp,"%d:%d",my_in[irank][0],my_in[irank][1]) ;
         }
         strcat(lab,tmp) ;
         if (my_in[irank][2] != 1) {
            sprintf(tmp,":%d",my_in[irank][2]) ;
            strcat(lab,tmp) ;
         }
         if (irank < nrank-1) {
            strcat(lab,",") ;
         } else {
            strcat(lab,")") ;
         }
      }
   } else {
      for ( irank = 0 ; irank < nrank ; irank++ ) {
         if (my_in[irank][0] == my_in[irank][1]) {
            sprintf(tmp,"%d",my_in[irank][0]-NPNL+1) ;
         } else {
            sprintf(tmp,"%d:%d",my_in[irank][0]-NPNL+1,my_in[irank][1]-NPNL+1) ;
         }
         strcat(lab,tmp) ;
         if (my_in[irank][2] != 1) {
            sprintf(tmp,":%d",my_in[irank][2]) ;
            strcat(lab,tmp) ;
         }
         if (irank < nrank-1) {
            strcat(lab,",") ;
         } else {
            strcat(lab,")") ;
         }
      }
   }
}
