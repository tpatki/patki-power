#include "irs.h"
#include "irsreg.h"
void regndx( Domain_t *domain ) {
   char *me = "regndx";
   char msg[128];
   int i,j,k,ir ;
   int *ndx,*ndxmix,*grdmix,*mixzn,*iregmix ;
   for ( ir = 0 ; ir <= nreg ; ir++ ) {
      domain->rlen[ir]    = 0 ;
      domain->rlencln[ir] = 0 ;
      domain->rlenmix[ir] = 0 ;
   }
   for ( i = 0 ; i < domain->nnalls ; i++ ) {
      ir = domain->ireg[i] ;
      if ( ir >= 0 ) {
         domain->rlencln[ir] = domain->rlencln[ir] + 1 ;
      }
   }
   for ( i = domain->nnalls ; i < domain->namix ; i++ ) {
      ir = domain->ireg[i] ;
      if ( ir >= 0 ) {
          domain->rlenmix[ir] = domain->rlenmix[ir] + 1 ;
      }
   }
   for ( ir = 1 ; ir <= nreg ; ir++ ) {
      domain->rlen[ir] = domain->rlencln[ir] + domain->rlenmix[ir] ;
   }
   domain->rlen[0]    = domain->rlencln[0] ;
   domain->rlenmix[0] = 0 ;
   i = 0 ;
   for ( ir = 0 ; ir <= nreg ; ir++ ) {
      domain->rndx[ir]    = domain->nmatlst  + i ;
      domain->rndxmix[ir] = domain->rndx[ir] + domain->rlencln[ir] ;
      i            = i + domain->rlen[ir] ;
   }
   i = 0 ;
   domain->rgrdmix[0] = domain->grdmix;
   for ( ir = 0 ; ir <= nreg ; ir++ ) {
      if ( ir > 0 ) {
         domain->rgrdmix[ir] = domain->rgrdmix[ir-1] + i ;
      }
      i = domain->rlenmix[ir] ;
   }
   for ( ir = 0 ; ir <= nreg ; ir++ ) {
      ndx    = domain->rndx[ir] ;
      ndxmix = domain->rndxmix[ir] ;
      grdmix = domain->rgrdmix[ir] ;
      for ( i = 0 ; i < domain->namix ; i++ ) {
         if (domain->ireg[i] == ir)  *ndx++ = i ;
      }
      for ( i = 0 ; i < domain->rlenmix[ir] ; i++ ) {
         grdmix[i] = domain->grdpnt[ndxmix[i] - domain->nnalls] ;
         if ( domain->ireg[grdmix[i]] >= 0 ) {
            sprintf(msg,"ireg and grdmix(%d) inconsistant (reg %d)",
               grdmix[i],ir) ;
            ctlwarning(me,msg);
	 }
      }
   }
   domain->nmixzn = 0 ;
   for ( i = 0 ; i < domain->nnalls ; i++ ) {
      if ( domain->ireg[i] < 0 ) {
         domain->grdzn[domain->nmixzn] = i ;
         domain->nmixzn++ ;
      }
   }
   k = 0 ;
   domain->rmixzn[0] = domain->mixzn;
   for ( ir = 0 ; ir <= nreg ; ir++ ) {
      if ( ir > 0 ) {
         domain->rmixzn[ir] = domain->rmixzn[0] + k;
      }
      k      = domain->rlenmix[ir] + k ;
      mixzn  = domain->rmixzn[ir] ;
      grdmix = domain->rgrdmix[ir] ;
      for ( i = 0 ; i < domain->rlenmix[ir] ; i++ ) {
 	 for ( j = 0 ; j < domain->nmixzn ; j++ ) {
            if (grdmix[i] == domain->grdzn[j]) break ;
         }
         if ( j < domain->nmixzn ) {
            mixzn[i] = j ;
         } else {
            sprintf(msg,"bad grdmix = %d for reg %d",grdmix[i],ir) ;
            ctlwarning(me,msg);
         }
      }
   }
 { 
      domain->imaxmix = 0 ;
   }
}
