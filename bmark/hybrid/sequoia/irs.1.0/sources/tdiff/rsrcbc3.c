#include "irs.h"
#include "irssrc.h"
#include "irstdiff.h"
#include "DiffusionData.h"
#include "FunctionTimer.h"
#include "RadiationData.h"
void rsrcbc3( RadiationData_t *rblk, DiffusionData_t *tblk, Domain_t *domain )
{
   char *me = "rsrcbc3";
   int isrc, irsrc, i;
   int *sndx, slen;
   double *cdcfl, *cdcfc, *cdcfr ;
   double *cdccl,         *cdccr ;
   double *cdcbl, *cdcbc, *cdcbr ;
   double *cscfl, *cscfc, *cscfr ;
   double *csccl,         *csccr ;
   double *cscbl, *cscbc, *cscbr ;
   double *rscfl, *rscfc, *rscfr ;
   double *rsccl,         *rsccr ;
   double *rscbl, *rscbc, *rscbr ;
   double *cddfl, *cddfc, *cddfr ;
   double *cddcl, *cddcc, *cddcr ;
   double *cddbl, *cddbc, *cddbr ;
   double *csdfl, *csdfc, *csdfr ;
   double *csdcl, *csdcc, *csdcr ;
   double *csdbl, *csdbc, *csdbr ;
   double *rsdfl, *rsdfc, *rsdfr ;
   double *rsdcl, *rsdcc, *rsdcr ;
   double *rsdbl, *rsdbc, *rsdbr ;
   double *cdufl, *cdufc, *cdufr ;
   double *cducl, *cducc, *cducr ;
   double *cdubl, *cdubc, *cdubr ;
   double *csufl, *csufc, *csufr ;
   double *csucl, *csucc, *csucr ;
   double *csubl, *csubc, *csubr ;
   double *rsufl, *rsufc, *rsufr ;
   double *rsucl, *rsucc, *rsucr ;
   double *rsubl, *rsubc, *rsubr ;
   double myflops = 0.0;
   FT_INITIALIZE(me, domain->hash)
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
         cddcc = rblk->ccc - domain->kp ;
         cddcl = rblk->ccc - domain->kp - 1 ;
         cddcr = rblk->ccc - domain->kp + 1 ;
         cddbc = rblk->ccc - domain->kp - domain->jp ;
         cddfc = rblk->ccc - domain->kp + domain->jp ;
         cddbl = rblk->ccc - domain->kp - domain->jp - 1 ;
         cddbr = rblk->ccc - domain->kp - domain->jp + 1 ;
         cddfl = rblk->ccc - domain->kp + domain->jp - 1 ;
         cddfr = rblk->ccc - domain->kp + domain->jp + 1 ;
         cducc = rblk->ccc + domain->kp ;
         cducl = rblk->ccc + domain->kp - 1 ;
         cducr = rblk->ccc + domain->kp + 1 ;
         cdubc = rblk->ccc + domain->kp - domain->jp ;
         cdufc = rblk->ccc + domain->kp + domain->jp ;
         cdubl = rblk->ccc + domain->kp - domain->jp - 1 ;
         cdubr = rblk->ccc + domain->kp - domain->jp + 1 ;
         cdufl = rblk->ccc + domain->kp + domain->jp - 1 ;
         cdufr = rblk->ccc + domain->kp + domain->jp + 1 ;
         csccl = rblk->ccl ;
         csccr = rblk->ccl + 1 ;
         cscbc = rblk->cbc ;
         cscfc = rblk->cbc + domain->jp ;
         cscbl = rblk->cbl ;
         cscbr = rblk->cbr ;
         cscfl = rblk->cbr + domain->jp - 1 ;
         cscfr = rblk->cbl + domain->jp + 1 ;
         csdcc = rblk->dcc ;
         csdcl = rblk->dcl ;
         csdcr = rblk->dcr ;
         csdbc = rblk->dbc ;
         csdfc = rblk->dfc ;
         csdbl = rblk->dbl ;
         csdbr = rblk->dbr ;
         csdfl = rblk->dfl ;
         csdfr = rblk->dfr ;
         csucc = rblk->dcc + domain->kp ;
         csucl = rblk->dcr + domain->kp - 1 ;
         csucr = rblk->dcl + domain->kp + 1 ;
         csubc = rblk->dfc + domain->kp - domain->jp ;
         csufc = rblk->dbc + domain->kp + domain->jp ;
         csubl = rblk->dfr + domain->kp - domain->jp - 1 ;
         csubr = rblk->dfl + domain->kp - domain->jp + 1 ;
         csufl = rblk->dbr + domain->kp + domain->jp - 1 ;
         csufr = rblk->dbl + domain->kp + domain->jp + 1 ;
         rsccl = tblk->rhs - 1 ;
         rsccr = tblk->rhs + 1 ;
         rscbc = tblk->rhs - domain->jp ;
         rscfc = tblk->rhs + domain->jp ;
         rscbl = tblk->rhs - domain->jp - 1 ;
         rscbr = tblk->rhs - domain->jp + 1 ;
         rscfl = tblk->rhs + domain->jp - 1 ;
         rscfr = tblk->rhs + domain->jp + 1 ;
         rsdcc = tblk->rhs - domain->kp ;
         rsdcl = tblk->rhs - domain->kp - 1 ;
         rsdcr = tblk->rhs - domain->kp + 1 ;
         rsdbc = tblk->rhs - domain->kp - domain->jp ;
         rsdfc = tblk->rhs - domain->kp + domain->jp ;
         rsdbl = tblk->rhs - domain->kp - domain->jp - 1 ;
         rsdbr = tblk->rhs - domain->kp - domain->jp + 1 ;
         rsdfl = tblk->rhs - domain->kp + domain->jp - 1 ;
         rsdfr = tblk->rhs - domain->kp + domain->jp + 1 ;
         rsucc = tblk->rhs + domain->kp ;
         rsucl = tblk->rhs + domain->kp - 1 ;
         rsucr = tblk->rhs + domain->kp + 1 ;
         rsubc = tblk->rhs + domain->kp - domain->jp ;
         rsufc = tblk->rhs + domain->kp + domain->jp ;
         rsubl = tblk->rhs + domain->kp - domain->jp - 1 ;
         rsubr = tblk->rhs + domain->kp - domain->jp + 1 ;
         rsufl = tblk->rhs + domain->kp + domain->jp - 1 ;
         rsufr = tblk->rhs + domain->kp + domain->jp + 1 ;
         for ( i = 0 ; i < slen ; i++ ) {
            rsccl[sndx[i]] -= csccl[sndx[i]] * tblk->phi[sndx[i]] ;
            rsccr[sndx[i]] -= csccr[sndx[i]] * tblk->phi[sndx[i]] ;
            rscbc[sndx[i]] -= cscbc[sndx[i]] * tblk->phi[sndx[i]] ;
            rscfc[sndx[i]] -= cscfc[sndx[i]] * tblk->phi[sndx[i]] ;
            rscbl[sndx[i]] -= cscbl[sndx[i]] * tblk->phi[sndx[i]] ;
            rscbr[sndx[i]] -= cscbr[sndx[i]] * tblk->phi[sndx[i]] ;
            rscfl[sndx[i]] -= cscfl[sndx[i]] * tblk->phi[sndx[i]] ;
            rscfr[sndx[i]] -= cscfr[sndx[i]] * tblk->phi[sndx[i]] ;
            rsdcc[sndx[i]] -= csdcc[sndx[i]] * tblk->phi[sndx[i]] ;
            rsdcl[sndx[i]] -= csdcl[sndx[i]] * tblk->phi[sndx[i]] ;
            rsdcr[sndx[i]] -= csdcr[sndx[i]] * tblk->phi[sndx[i]] ;
            rsdbc[sndx[i]] -= csdbc[sndx[i]] * tblk->phi[sndx[i]] ;
            rsdfc[sndx[i]] -= csdfc[sndx[i]] * tblk->phi[sndx[i]] ;
            rsucc[sndx[i]] -= csucc[sndx[i]] * tblk->phi[sndx[i]] ;
            rsucl[sndx[i]] -= csucl[sndx[i]] * tblk->phi[sndx[i]] ;
            rsucr[sndx[i]] -= csucr[sndx[i]] * tblk->phi[sndx[i]] ;
            rsubc[sndx[i]] -= csubc[sndx[i]] * tblk->phi[sndx[i]] ;
            rsufc[sndx[i]] -= csufc[sndx[i]] * tblk->phi[sndx[i]] ;
            cdccl[sndx[i]] -= csccl[sndx[i]] ;
            cdccr[sndx[i]] -= csccr[sndx[i]] ;
            cdcbc[sndx[i]] -= cscbc[sndx[i]] ;
            cdcfc[sndx[i]] -= cscfc[sndx[i]] ;
            cdcbl[sndx[i]] -= cscbl[sndx[i]] ;
            cdcbr[sndx[i]] -= cscbr[sndx[i]] ;
            cdcfl[sndx[i]] -= cscfl[sndx[i]] ;
            cdcfr[sndx[i]] -= cscfr[sndx[i]] ;
            cddcc[sndx[i]] -= csdcc[sndx[i]] ;
            cddcl[sndx[i]] -= csdcl[sndx[i]] ;
            cddcr[sndx[i]] -= csdcr[sndx[i]] ;
            cddbc[sndx[i]] -= csdbc[sndx[i]] ;
            cddfc[sndx[i]] -= csdfc[sndx[i]] ;
            cducc[sndx[i]] -= csucc[sndx[i]] ;
            cducl[sndx[i]] -= csucl[sndx[i]] ;
            cducr[sndx[i]] -= csucr[sndx[i]] ;
            cdubc[sndx[i]] -= csubc[sndx[i]] ;
            cdufc[sndx[i]] -= csufc[sndx[i]] ;
            csccl[sndx[i]] = 0.0 ;
            csccr[sndx[i]] = 0.0 ;
            cscbc[sndx[i]] = 0.0 ;
            cscfc[sndx[i]] = 0.0 ;
            cscbl[sndx[i]] = 0.0 ;
            cscbr[sndx[i]] = 0.0 ;
            cscfl[sndx[i]] = 0.0 ;
            cscfr[sndx[i]] = 0.0 ;
            csdcc[sndx[i]] = 0.0 ;
            csdcl[sndx[i]] = 0.0 ;
            csdcr[sndx[i]] = 0.0 ;
            csdbc[sndx[i]] = 0.0 ;
            csdfc[sndx[i]] = 0.0 ;
            csucc[sndx[i]] = 0.0 ;
            csucl[sndx[i]] = 0.0 ;
            csucr[sndx[i]] = 0.0 ;
            csubc[sndx[i]] = 0.0 ;
            csufc[sndx[i]] = 0.0 ;
            if ( ifdivgrad != 1 ) {
               rsdbl[sndx[i]] -= csdbl[sndx[i]] * tblk->phi[sndx[i]] ;
               rsdbr[sndx[i]] -= csdbr[sndx[i]] * tblk->phi[sndx[i]] ;
               rsdfl[sndx[i]] -= csdfl[sndx[i]] * tblk->phi[sndx[i]] ;
               rsdfr[sndx[i]] -= csdfr[sndx[i]] * tblk->phi[sndx[i]] ;
               rsubl[sndx[i]] -= csubl[sndx[i]] * tblk->phi[sndx[i]] ;
               rsubr[sndx[i]] -= csubr[sndx[i]] * tblk->phi[sndx[i]] ;
               rsufl[sndx[i]] -= csufl[sndx[i]] * tblk->phi[sndx[i]] ;
               rsufr[sndx[i]] -= csufr[sndx[i]] * tblk->phi[sndx[i]] ;
               cddbl[sndx[i]] -= csdbl[sndx[i]] ;
               cddbr[sndx[i]] -= csdbr[sndx[i]] ;
               cddfl[sndx[i]] -= csdfl[sndx[i]] ;
               cddfr[sndx[i]] -= csdfr[sndx[i]] ;
               cdubl[sndx[i]] -= csubl[sndx[i]] ;
               cdubr[sndx[i]] -= csubr[sndx[i]] ;
               cdufl[sndx[i]] -= csufl[sndx[i]] ;
               cdufr[sndx[i]] -= csufr[sndx[i]] ;
               csdbl[sndx[i]]  = 0.0 ;
               csdbr[sndx[i]]  = 0.0 ;
               csdfl[sndx[i]]  = 0.0 ;
               csdfr[sndx[i]]  = 0.0 ;
               csubl[sndx[i]]  = 0.0 ;
               csubr[sndx[i]]  = 0.0 ;
               csufl[sndx[i]]  = 0.0 ;
               csufr[sndx[i]]  = 0.0 ;
	    }
         }
         myflops += 54.0 * slen ;
         if ( ifdivgrad != 1 ) {
            myflops += 24.0 * slen ;
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
            tblk->rhs[sndx[i]] = tblk->phi[sndx[i]] ;
            rblk->ccc[sndx[i]] = 1.0;
	  }
       }
    }
  FT_FINALIZE(me, domain->hash, myflops)
}
