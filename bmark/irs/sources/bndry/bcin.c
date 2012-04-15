#include "irs.h"
#include "irssrc.h"
#include "irsbndry.hh"
#include "NodeList.h"
int bcin( void ) 
{
   char *me = "bcin";
   char aname[MAXWORD],op[MAXWORD],msg[MAXLINE] ;
   char bcname[MAXWORD];
   char ndxname[MAXWORD];
   int i;
   int len,ibc;
   int error;
   int iblk,gblk;
   int gotnorad;
   int gotvsame;
   int *ndx;
   NodeWindow_t *ndxin_src;
   NodeWindow_t *ndxin;
   NodeWindow_t *ndxptr;
   error = 0 ;
   ndxin_src = NULL;
   ndxin     = NULL;
   ndxptr    = NULL;
   memset(aname,'\0',MAXWORD);
   strcpy(aname,"bc") ;
   error = NodeWindow_read(aname,&ndxin) ;
   if (error != 0) {
      sprintf(msg,"Error reading index list for %s",aname);
      ctlwarning(me,msg);
   }
   geta(op) ;
   geta(bcname) ;
   if ( (!strcmp(bcname,"xeuler")) ||
        (!strcmp(bcname,"yeuler")) ||
        (!strcmp(bcname,"zeuler"))  ) {
      NodeWindow_copyall(ndxin,&ndxin_src);
      error  = srcin_init( 0, bcname, ndxin_src ) ;
      if ( error != 0 ) {
         sprintf(msg,"Error setting source structure for bc [x,y,z]euler\n");
         ctlwarning(me,msg);
         return(error) ;
      }
      strcpy(bcname,"free") ;
   }
   NodeList_addnextseq("NL_BC", ndxin, ndxname) ;
   peekc(op);
   gotnorad = 0 ;
   gotvsame = 0 ;
   if (!strcmp(op,"norad")) {
      geta(op);
      gotnorad = 1;
      peekc(op);
      if (!strcmp(op,"vsame")) {
         geta(op);
         gotvsame = 1;
      }
   } else if (!strcmp(op,"vsame")) {
      geta(op);
      gotvsame = 1;
      peekc(op);
      if (!strcmp(op,"norad")) {
         geta(op);
         gotnorad = 1;
      }
   }
   ndxptr = ndxin;
   while (ndxptr != NULL) {
      for (iblk = 0; iblk < nblk; iblk++) {
         gblk = domains[iblk].gblk;
         len = NodeWindow_fastndx(ndxptr,gblk,NDX_REAL, NDX_NODAL);
         if (len > 0) {
            ibc = domains[iblk].nbc ;
            ndx = MALLOT(int,len);
            for (i = 0; i < len; i++) {
               ndx[i] = ndxptr->ndx[i];
            }
            if (ibc >= nbcx) {
               error = 1 ;
               sprintf(msg,"number of bc's in block %d (%d) exceeds nbcx\n",
                       iblk,ibc);
               ctlwarning(me,msg);
               return(error) ;
            }
            domains[iblk].nbc++ ;
            error += bcin0(len,ndx,ibc,bcname,&domains[iblk]);
            if (gotvsame) {
               error += vsamein0(len,ndx,ibc,&domains[iblk]);
               ifvsame = 1;
            }
            if (gotnorad) {
               domains[iblk].bc[ibc].rtype = CLOSED;
            }
            strcpy(domains[iblk].bc[ibc].ndxName,ndxname);
            NodeWindow_freendx(ndxptr);
         }
      }
      ndxptr = ndxptr->next;
   }
   return(error) ;
}
