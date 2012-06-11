#include "irs.h"
#include "irstdiff.h"
#include "irssrc.h"
#include "DiffusionData.h"
#include "RadiationData.h"
void rsrcbc2( RadiationData_t *rblk, DiffusionData_t *tblk, Domain_t *domain )
{
   int isrc, irsrc, i ;
   int *sndx, slen ;
   double *cdcfl, *cdcfc, *cdcfr ;
   double *cdccl,         *cdccr ;
   double *cdcbl, *cdcbc, *cdcbr ;
   double *cscfl, *cscfc, *cscfr ;
   double *csccl,         *csccr ;
   double *cscbl, *cscbc, *cscbr ;
   double *rscfl, *rscfc, *rscfr ;
   double *rsccl,         *rsccr ;
   double *rscbl, *rscbc, *rscbr ;
   for ( isrc = 0 ; isrc < domain->nsrc ; isrc++ ) {
      if ( domain->src[isrc].type == TSRC || domain->src[isrc].type == TSRCINT ) {
         sndx = domain->src[isrc].ndxsrc ;
         slen = domain->src[isrc].nzsrc  ;
	 if ( domain->src[isrc].type == TSRCINT ) {
	    irsrc = domain->src[isrc].idat1[1] ;
	    if ( irsrc > 0 ) {
	       sndx = domain->rndx[irsrc] ;
	       slen = domain->rlencln[irsrc] ;
	    }
	 }
         cdccl = rblk->ccc - 1 ;
         cdccr = rblk->ccc + 1 ;
         cdcbc = rblk->ccc - domain->jp ;
         cdcfc = rblk->ccc + domain->jp ;
         cdcbl = rblk->ccc - domain->jp - 1 ;
         cdcbr = rblk->ccc - domain->jp + 1 ;
         cdcfl = rblk->ccc + domain->jp - 1 ;
         cdcfr = rblk->ccc + domain->jp + 1 ;
         csccl = rblk->ccl ;
         csccr = rblk->ccl + 1 ;
         cscbc = rblk->cbc ;
         cscfc = rblk->cbc + domain->jp ;
         cscbl = rblk->cbl ;
         cscbr = rblk->cbr ;
         cscfl = rblk->cbr + domain->jp - 1 ;
         cscfr = rblk->cbl + domain->jp + 1 ;
         rsccl = tblk->rhs - 1 ;
         rsccr = tblk->rhs + 1 ;
         rscbc = tblk->rhs - domain->jp ;
         rscfc = tblk->rhs + domain->jp ;
         rscbl = tblk->rhs - domain->jp - 1 ;
         rscbr = tblk->rhs - domain->jp + 1 ;
         rscfl = tblk->rhs + domain->jp - 1 ;
         rscfr = tblk->rhs + domain->jp + 1 ;
         for ( i = 0 ; i < slen ; i++ ) {
            rsccl[sndx[i]] -= csccl[sndx[i]]*tblk->phi[sndx[i]] ; 
            rsccr[sndx[i]] -= csccr[sndx[i]]*tblk->phi[sndx[i]] ; 
            rscbc[sndx[i]] -= cscbc[sndx[i]]*tblk->phi[sndx[i]] ; 
            rscfc[sndx[i]] -= cscfc[sndx[i]]*tblk->phi[sndx[i]] ; 
            rscbl[sndx[i]] -= cscbl[sndx[i]]*tblk->phi[sndx[i]] ; 
            rscbr[sndx[i]] -= cscbr[sndx[i]]*tblk->phi[sndx[i]] ; 
            rscfl[sndx[i]] -= cscfl[sndx[i]]*tblk->phi[sndx[i]] ; 
            rscfr[sndx[i]] -= cscfr[sndx[i]]*tblk->phi[sndx[i]] ; 
            cdccl[sndx[i]] -= csccl[sndx[i]] ; 
            cdccr[sndx[i]] -= csccr[sndx[i]] ; 
            cdcbc[sndx[i]] -= cscbc[sndx[i]] ; 
            cdcfc[sndx[i]] -= cscfc[sndx[i]] ; 
            cdcbl[sndx[i]] -= cscbl[sndx[i]] ; 
            cdcbr[sndx[i]] -= cscbr[sndx[i]] ; 
            cdcfl[sndx[i]] -= cscfl[sndx[i]] ; 
            cdcfr[sndx[i]] -= cscfr[sndx[i]] ; 
            csccl[sndx[i]]  = 0.0 ; 
            csccr[sndx[i]]  = 0.0 ; 
            cscbc[sndx[i]]  = 0.0 ; 
            cscfc[sndx[i]]  = 0.0 ; 
            cscbl[sndx[i]]  = 0.0 ; 
            cscbr[sndx[i]]  = 0.0 ; 
            cscfl[sndx[i]]  = 0.0 ; 
            cscfr[sndx[i]]  = 0.0 ; 
         }
      }
   }
   for ( isrc = 0 ; isrc < domain->nsrc ; isrc++ ) {
      if ( domain->src[isrc].type == TSRC || domain->src[isrc].type == TSRCINT ) {
         sndx = domain->src[isrc].ndxsrc ;
         slen = domain->src[isrc].nzsrc  ;
	 if ( domain->src[isrc].type == TSRCINT ) {
	    irsrc = domain->src[isrc].idat1[1] ;
	    if ( irsrc > 0 ) {
	       sndx = domain->rndx[irsrc] ;
	       slen = domain->rlencln[irsrc] ;
	    }
	 }
         for ( i = 0 ; i < slen ; i++ ) {
            rblk->ccc[sndx[i]] = 1.0;
	    tblk->rhs[sndx[i]] = tblk->phi[sndx[i]];
         }
      }
   }
}
