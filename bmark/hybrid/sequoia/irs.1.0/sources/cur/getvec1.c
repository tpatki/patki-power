#include "irs.h"
#include "irsgen.h"
#include "cgl.h"
#include "irscur.h"
#include "NodeList.h"
#include "VectorStruct.h"
int getvec1(
  VectorStruct_t *vecstr,	
  int      labflag)	
{
   char *me = "getvec1";
   char msg[MAXLINE];
   char lab[MAXLINE] ;
   int error, len, i ;
   int *ndx;
   NodeWindow_t *ndxin;
   ndxin = NULL;
   error = 0 ;
   error = NodeWindow_read(vecstr->namevec,&ndxin);
   if (error != 0) return(error);
   if (ndxin->next != NULL) {
      sprintf(msg,"Routine getvec cannot process multi-block node lists.");
      ctlwarning(me,msg);
      error = 1;
      return(error);
   }
   len = NodeWindow_getndx(ndxin,-1,NDX_OVERLAP, NDX_REAL, NDX_NODAL);
   ndx = ndxin->ndx;
   if (labflag != 0) {
      mkpalab(vecstr->namelab,vecstr->namevec,ndxin->ublk,ndxin->in,
              ndxin->rank,0,"");
   }
   if (len == -1) {
      error = 1 ;
      return(error) ;
   }
   if (roptype == 0) {
      vecstr->palen = len ;
      if (vecstr->type == INT) {
         vecstr->ipa = ALLOT(int,vecstr->palen) ;
         for ( i = 0 ; i < len ; i++ ) {
            vecstr->ipa[i] = vecstr->iloc[ndx[i]] ;
         }
      } else if (vecstr->type == FLOAT) {
         vecstr->fpa = ALLOT(double,vecstr->palen) ;
         for ( i = 0 ; i < len ; i++ ) {
            vecstr->fpa[i] = vecstr->floc[ndx[i]] ;
         }
      }
   } else {
      vecstr->palen = 1 ;
      if (vecstr->type == INT) {
         vecstr->ipa    = ALLOT(int,vecstr->palen) ;
         vecstr->ipa[0] = vecstr->iloc[ndx[0]] ;
      } else if (vecstr->type == FLOAT) {
         vecstr->fpa = ALLOT(double,vecstr->palen) ;
         dorop(vecstr->fpa,vecstr->floc,ndx,len,roptype) ;
      }
   }
   NodeWindow_free(ndxin);
   return(error) ; 
}
