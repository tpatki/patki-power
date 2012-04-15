#include "irs.h"
#include "irsgen.h"
#include "NodeList.h"
int  purify( )
{
   char *me = "purify";
   char aname[MAXWORD],lab[MAXWORD],msg[MAXLINE];
   char op[MAXLINE];
   int i,j;
   int error;
   int len ;
   int iblk;
   NodeWindow_t *ndxin;
   NodeWindow_t *ndxptr;
   ndxin = NULL;
   ndxptr = NULL;
   error = 0;
   strcpy(aname,"purify") ;
   error = NodeWindow_read(aname,&ndxin);
   if (error != 0) return(error);
   if (genmd == 0) { 
      NodeWindow_free(ndxin);
      ctlwarning(me,"Purify command can only be used during generation");
      return(error);
   }
   ndxptr = ndxin;
   while (ndxptr != NULL) {
      mkpalab(lab,aname,ndxptr->ublk,ndxptr->in,ndxptr->rank,0,"");
      for (iblk = 0; iblk < nblk; iblk++) {
         len = NodeWindow_fastndx(ndxptr,domains[iblk].gblk, NDX_REAL, NDX_ZONAL);
         if (len > 0) {
            int *ndx = ndxptr->ndx;
            for (i = 0; i < len; i++) {
               if (domains[iblk].ireg[ndx[i]] < 0) {
                  double vfmax;
                  int    idmax;
                  int    mat;
                  int grd = -domains[iblk].ireg[ndx[i]];
                  vfmax = -1.0;
                  idmax = -1;
                  while (grd > 0) {
                     if (domains[iblk].vol[grd] > vfmax) {
                        vfmax = domains[iblk].vol[grd];
                        mat   = domains[iblk].ireg[grd];
                        idmax = grd;
                     }
                     domains[iblk].ireg[grd] = 0;
                     grd = grd - domains[iblk].nnalls;
                     grd = domains[iblk].lnkmix[grd];
                  }
                  domains[iblk].ireg[ndx[i]] = mat;
               }
            }
            for (i = 0; i < domains[iblk].nnalls; i++) {
               if (domains[iblk].ireg[i]  < 0) {
                  domains[iblk].ireg[i] = -1;
               }
            }
         }
         NodeWindow_freendx(ndxptr);
      }
      ndxptr = ndxptr->next;
   }
   NodeWindow_free(ndxin) ;
   return(error) ;
}
