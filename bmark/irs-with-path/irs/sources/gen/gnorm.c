#include "irs.h"
#include "irsgen.h"
#include "NodeList.h"
int  gnorm( int type )
{
   char *me = "gnorm";
   char aname[10],lab[30],msg[MAXLINE];
   char op[MAXWORD];
   int error = 0 ;
   int len ;
   int i,i1,i2 ;
   int iblk, cflag;
   double *fx,*fy,*fz ;
   double oldnorm, newnorm, scale;
   int *lblk, *lndx;
   NodeWindow_t *ndxin;
   NodeWindow_t *ndxptr;
   ndxin = NULL;
   ndxptr = NULL;
   strcpy(aname,"norm") ;
   error = NodeWindow_read(aname,&ndxin);
   if (error != 0) return(error);
   geta(op) ;
   newnorm = getf(&cflag) ;
   ndxptr = ndxin;
   while (ndxptr != NULL) {
      len = NodeWindow_getndx(ndxin,-1,NDX_OVERLAP, NDX_REAL, NDX_NODAL);
      lblk = ndxin->blk;
      lndx = ndxin->ndx;
      for (i = 0; i < len; i++) {
         iblk = lblk[i];
         fx = domains[iblk].x ;
         fy = domains[iblk].y ;
         fz = domains[iblk].z ;
         if (type == 1) {
            fx = domains[iblk].xdot ;
            fy = domains[iblk].ydot ;
            fz = domains[iblk].zdot ;
         }
         if (ndims == 2) {
            oldnorm = sqrt(fx[lndx[i]]*fx[lndx[i]] + fy[lndx[i]]*fy[lndx[i]]);
            scale = newnorm / (oldnorm + ptiny);
            fx[lndx[i]] *= scale;
            fy[lndx[i]] *= scale;
         } else {
            oldnorm = sqrt(fx[lndx[i]]*fx[lndx[i]] + fy[lndx[i]]*fy[lndx[i]] +
                           fz[lndx[i]]*fz[lndx[i]]);
            scale = newnorm / (oldnorm + ptiny);
            fx[lndx[i]] *= scale;
            fy[lndx[i]] *= scale;
            fz[lndx[i]] *= scale;
         }
      }
      ndxptr = ndxptr->next;
   }
   NodeWindow_free(ndxin);
   return(error) ;
}
