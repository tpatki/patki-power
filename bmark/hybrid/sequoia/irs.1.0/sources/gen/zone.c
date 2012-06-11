#include "irs.h"
#include "irsgen.h"
#include "NodeList.h"
int  zone( )
{
   int error;
   int len ;
   int ireg ;
   int cflag ;
   int i;
   int iblk;
   int *lndx;
   double den, tmat;
   char *me = "zone";
   char aname[MAXWORD],lab[MAXWORD],msg[MAXLINE];
   char op[MAXLINE];
   NodeWindow_t *ndxin;
   NodeWindow_t *ndxptr;
   ndxin = NULL;
   ndxptr = NULL;
   error = 0;
   memset(lab,'\0',MAXWORD);
   memset(aname,'\0',MAXWORD);
   strcpy(aname,"zone") ;
   error = NodeWindow_read(aname,&ndxin);
   if (error != 0) return(error);
   geta(op);
   if (strcmp(op,"=")) {
      sprintf(msg,"Expecting equal sign in zone command, found %s instead.\n",
                   op);
      error = -1;
   }
   ireg = geti(&cflag);
   if ((error == 0) && (cflag)) {
      sprintf(msg,"Bad region value %d in %s command.\n",ireg,lab);
      error = -1;
   }
   den = getf(&cflag);
   if ((error == 0) && (cflag)) {
      sprintf(msg,"Bad density value %f in %s command.\n",den,lab);
      error = -1;
   }
   tmat = getf(&cflag);
   if ((error == 0) && (cflag)) {
      sprintf(msg,"Bad temp value %f in %s command.\n",tmat,lab);
      error = -1;
   }
   ndxptr = ndxin;
   while (ndxptr != NULL) {
      for (iblk = 0; iblk < nblk; iblk++) {
         len = NodeWindow_fastndx(ndxptr,domains[iblk].gblk, NDX_REAL, NDX_ZONAL);
         mkpalab(lab,aname,ndxptr->ublk,ndxptr->in,ndxptr->rank,0,"");
         lndx = ndxptr->ndx;
         for (i = 0; i < len; i++) {
            domains[iblk].ireg[lndx[i]] = ireg;
            domains[iblk].den[lndx[i]] = den;
            domains[iblk].tmat[lndx[i]] = tmat;
         }
         NodeWindow_freendx(ndxptr) ;
      }
      ndxptr = ndxptr->next;
   }
   NodeWindow_free(ndxin) ;
   return(error) ;
}
