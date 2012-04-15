#include "irs.h"
#include "irsbndry.h"
#include "BlockMapping.h"
#include "NodeList.h"
int bndin( void )
{
   char *me = "bndin";
   char msg[MAXLINE];
   int i;
   int nbnd1,nbnd2;
   int error;
   int len;
   int len1, len2;
   int ublk1, ublk2; 
   char aname[MAXWORD];
   char op[MAXLINE];
   int *undx;
   NodeWindow_t *ndxin1;
   NodeWindow_t *ndxin2;
   NodeWindow_t *ndxptr1;
   NodeWindow_t *ndxptr2;
   error = 0 ;
   ndxin1 = NULL;
   ndxin2 = NULL;
   strcpy( aname, "bnd" ) ;
   error = NodeWindow_read(aname,&ndxin1);
   if (error != 0) {
      sprintf(msg,"Error reading index list for %s",aname);
      ctlwarning(me,msg);
   }
   geta(op) ;
   geta(op) ;
   error = NodeWindow_read(aname,&ndxin2);
   if (error != 0) {
      sprintf(msg,"Error reading index list for %s",aname);
      ctlwarning(me,msg);
   }
   ndxptr1 = ndxin1;
   ndxptr2 = ndxin2;
   while ((ndxptr1 != NULL) && (ndxptr2 != NULL)) {
      ublk1 = ndxptr1->ublk;
      nbnd1 = umap[ublk1].nbnd;
      ublk2 = ndxptr2->ublk;
      nbnd2 = umap[ublk2].nbnd;
      if (ublk1 == ublk2) {
         nbnd2 = nbnd1 + 1;
      }
      CPYEXT(umap[ublk1].bnd[nbnd1],(*ndxptr1));
      len1 = LENEXT(umap[ublk1].bnd[nbnd1]);
      CPYEXT(umap[ublk2].bnd[nbnd2],(*ndxptr2));
      len2 = LENEXT(umap[ublk2].bnd[nbnd2]);
      if (len1 != len2) {
         sprintf(msg,"Boundary between %i and %i is not one to one.\n",
                 ublk1,ublk2);
         ctlerror(me,msg);
      }
      umap[ublk1].bnd[nbnd1].iblk = ublk2;
      umap[ublk1].bnd[nbnd1].id = nbnd2;
      umap[ublk2].bnd[nbnd2].iblk = ublk1;
      umap[ublk2].bnd[nbnd2].id = nbnd1;
      umap[ublk1].bnd[nbnd1].orientation[0] = 1;
      umap[ublk1].bnd[nbnd1].orientation[1] = 2;
      umap[ublk1].bnd[nbnd1].orientation[2] = 3;
      umap[ublk2].bnd[nbnd2].orientation[0] = 1;
      umap[ublk2].bnd[nbnd2].orientation[1] = 2;
      umap[ublk2].bnd[nbnd2].orientation[2] = 3;
      umap[ublk1].nbnd++;
      umap[ublk2].nbnd++;
      ndxptr1 = ndxptr1->next;
      ndxptr2 = ndxptr2->next;
   }
   if ((ndxptr1 != NULL) || (ndxptr2 != NULL)) {
      sprintf(msg,"Boundary lists %s and %s are not one to one in block number\n",ndxin1->label,ndxin2->label);
      ctlerror(me,msg);
   }
   NodeWindow_free(ndxin1);
   NodeWindow_free(ndxin2);
   ifcom = 1 ;
   return(error) ;
}
