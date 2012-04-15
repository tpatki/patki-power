#include "irs.h"
#include "irsgen.h"
#include "BlockMapping.h"
#include "NodeList.h"
static int mixzn0( int grdmix, Domain_t *domain ) ;
int mixzn( void )
{
   char *me = "mixzn";
   char aname[10],lab[30],msg[128];
   int i,error,gotone ;
   int len,grdmix ;
   int gblk, ublk, iblk;
   int i0, j0, k0;
   int *lndx, *lblk;
   NodeWindow_t *ndxin;
   NodeWindow_t *ndxptr;
   ndxin = NULL;
   ndxptr = NULL;
   error = 0 ;
   strcpy(aname,"mixzn") ;
   error = NodeWindow_read(aname,&ndxin);
   if (error != 0) return(error);
   ndxptr = ndxin;
   while (ndxptr != NULL) {
      len = NodeWindow_getndx(ndxptr,-1, NDX_OVERLAP, NDX_REAL, NDX_ZONAL);
      mkpalab(lab,aname,ndxptr->ublk,ndxptr->in,ndxptr->rank,0,"");
      lndx = ndxptr->ndx;
      lblk = ndxptr->blk;
      ublk = ndxptr->ublk;
      for ( i = 0 ; i < len ; i++) {
         iblk = lblk[i];
         gblk = domains[iblk].gblk;
         grdmix = lndx[i] ;
         if (ndims == 2) {
            NDXEXT2D(grdmix,i0,j0,domains[iblk]);
            i0 = i0 + gmap[gblk].imin - 2*NPNL + 1;
            j0 = j0 + gmap[gblk].jmin - 2*NPNL + 1;
            sprintf(msg,"zone:%d(%d,%d)",ublk,i0,j0) ;
            ctlmsg(msg);
            sprintf(msg,"reg   fv           den          tmat         p        cs2") ; 
            ctlmsg(msg);
         } else {
            NDXEXT3D(grdmix,i0,j0,k0,domains[iblk]);
            i0 = i0 + gmap[gblk].imin - 2*NPNL + 1;
            j0 = j0 + gmap[gblk].jmin - 2*NPNL + 1;
            k0 = k0 + gmap[gblk].kmin - 2*NPNL + 1;
            sprintf(msg,"zone:%d(%d,%d,%d)",ublk,i0,j0,k0) ;
            ctlmsg(msg);
            sprintf(msg,"reg   fv           den          tmat         p        cs2") ;
            ctlmsg(msg);
         } 
         gotone = 0;
         gotone = mixzn0(grdmix,&domains[iblk]) ;
         if (gotone == 0) {
            ctlmsg("--zone not mixed");
         }
      }
      ndxptr = ndxptr->next;
   }
   NodeWindow_free(ndxin) ;
   return(error) ;
}
static int mixzn0( int grdmix, Domain_t *domain ) {
   char *me = "mixzn0";
   char msg[128];
   int i, nmix, ndxmix, gotone, *iregmix ;
   iregmix = domain->ireg + domain->nnalls ;
   nmix = domain->namix - domain->nnalls ;
   gotone = 0 ;
   for ( i = 0 ; i < nmix ; i++ ) {
      if ( (domain->grdpnt[i] == grdmix) & (iregmix[i] != 0) ) {
         gotone = 1 ;
         ndxmix = domain->nnalls + i ;
         sprintf(msg,"%d %e %e %e %e %e",
                 domain->ireg[ndxmix], domain->vol[ndxmix], domain->den[ndxmix],
                 domain->tmat[ndxmix], domain->p[ndxmix],   domain->cs2[ndxmix] );
         ctlmsg(msg);
         if ((iftmode == 1) || (iftion == 1) ) {
            sprintf(msg,"       %e %e %e",
                 domain->tion[ndxmix], domain->deidt[ndxmix], domain->dedt[ndxmix] ) ;
            ctlmsg(msg);
         }
      }
   }
   return(gotone) ;
}
