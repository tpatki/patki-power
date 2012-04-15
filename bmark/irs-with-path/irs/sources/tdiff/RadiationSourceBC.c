#include "irs.h"
#include "irstdiff.h"
#include "irsrgst.h"
#include "DiffusionData.h"
#include "FunctionTimer.h"
#include "Rgst.h"
#include "RadiationData.h"
#include "Source.h"
void RadiationSourceBC_2d( RadiationData_t *rblk, DiffusionData_t *tblk, Domain_t *domain )
{
   char *me = "RadiationSourceBC_2d";
   int i;
   double *cdcfl, *cdcfc, *cdcfr ;
   double *cdccl,         *cdccr ;
   double *cdcbl, *cdcbc, *cdcbr ;
   double *cscfl, *cscfc, *cscfr ;
   double *csccl,         *csccr ;
   double *cscbl, *cscbc, *cscbr ;
   double *rscfl, *rscfc, *rscfr ;
   double *rsccl,         *rsccr ;
   double *rscbl, *rscbc, *rscbr ;
   RGST_AttributeElem_t *srclist_ptr;
   RGST_AttributeElem_t *srclist;
   srclist     = rgst_list_attr(A_OBJECT, "SourceRadiationTemperature");
   srclist_ptr = srclist;
   while (srclist != NULL) {
      char        *name     = ATTR_GET_OBJECT_NAME(srclist)
      SourceNew_t *mysrc    = SourceNew_find(name,domain->hash);
      int *ndx = mysrc->ndx;
      int  len = mysrc->len;
      if (mysrc->region > 0) {
         ndx = domain->rndx[mysrc->region];
         len = domain->rlen[mysrc->region];
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
      for ( i = 0 ; i < len ; i++ ) {
         rsccl[ndx[i]] -= csccl[ndx[i]]*tblk->phi[ndx[i]] ; 
         rsccr[ndx[i]] -= csccr[ndx[i]]*tblk->phi[ndx[i]] ; 
         rscbc[ndx[i]] -= cscbc[ndx[i]]*tblk->phi[ndx[i]] ; 
         rscfc[ndx[i]] -= cscfc[ndx[i]]*tblk->phi[ndx[i]] ; 
         rscbl[ndx[i]] -= cscbl[ndx[i]]*tblk->phi[ndx[i]] ; 
         rscbr[ndx[i]] -= cscbr[ndx[i]]*tblk->phi[ndx[i]] ; 
         rscfl[ndx[i]] -= cscfl[ndx[i]]*tblk->phi[ndx[i]] ; 
         rscfr[ndx[i]] -= cscfr[ndx[i]]*tblk->phi[ndx[i]] ; 
         cdccl[ndx[i]] -= csccl[ndx[i]] ; 
         cdccr[ndx[i]] -= csccr[ndx[i]] ; 
         cdcbc[ndx[i]] -= cscbc[ndx[i]] ; 
         cdcfc[ndx[i]] -= cscfc[ndx[i]] ; 
         cdcbl[ndx[i]] -= cscbl[ndx[i]] ; 
         cdcbr[ndx[i]] -= cscbr[ndx[i]] ; 
         cdcfl[ndx[i]] -= cscfl[ndx[i]] ; 
         cdcfr[ndx[i]] -= cscfr[ndx[i]] ; 
         csccl[ndx[i]]  = 0.0 ; 
         csccr[ndx[i]]  = 0.0 ; 
         cscbc[ndx[i]]  = 0.0 ; 
         cscfc[ndx[i]]  = 0.0 ; 
         cscbl[ndx[i]]  = 0.0 ; 
         cscbr[ndx[i]]  = 0.0 ; 
         cscfl[ndx[i]]  = 0.0 ; 
         cscfr[ndx[i]]  = 0.0 ; 
      }
      srclist = srclist->next;
   }
   srclist = srclist_ptr;
   while (srclist != NULL) {
      char        *name     = ATTR_GET_OBJECT_NAME(srclist)
      SourceNew_t *mysrc    = SourceNew_find(name,domain->hash);
      int *ndx = mysrc->ndx;
      int  len = mysrc->len;
      if (mysrc->region > 0) {
         ndx = domain->rndx[mysrc->region];
         len = domain->rlen[mysrc->region];
      }
      for ( i = 0 ; i < len ; i++ ) {
         rblk->ccc[ndx[i]] = 1.0;
         tblk->rhs[ndx[i]] = tblk->phi[ndx[i]];
      }
      srclist = srclist->next;
   }
}
void RadiationSourceBC_3d( RadiationData_t *rblk, DiffusionData_t *tblk, Domain_t *domain )
{
   char *me = "RadiationSourceBC_3d";
   int i;
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
   RGST_AttributeElem_t *srclist_ptr;
   RGST_AttributeElem_t *srclist;
   FT_INITIALIZE(me, domain->hash)
   srclist     = rgst_list_attr(A_OBJECT, "SourceRadiationTemperature");
   srclist_ptr = srclist;
   while (srclist != NULL) {
      char        *name     = ATTR_GET_OBJECT_NAME(srclist)
      SourceNew_t *mysrc    = SourceNew_find(name,domain->hash);
      int *ndx = mysrc->ndx;
      int  len = mysrc->len;
      if (mysrc->region > 0) {
         ndx = domain->rndx[mysrc->region];
         len = domain->rlen[mysrc->region];
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
      for ( i = 0 ; i < len ; i++ ) {
         rsccl[ndx[i]] -= csccl[ndx[i]] * tblk->phi[ndx[i]] ;
         rsccr[ndx[i]] -= csccr[ndx[i]] * tblk->phi[ndx[i]] ;
         rscbc[ndx[i]] -= cscbc[ndx[i]] * tblk->phi[ndx[i]] ;
         rscfc[ndx[i]] -= cscfc[ndx[i]] * tblk->phi[ndx[i]] ;
         rscbl[ndx[i]] -= cscbl[ndx[i]] * tblk->phi[ndx[i]] ;
         rscbr[ndx[i]] -= cscbr[ndx[i]] * tblk->phi[ndx[i]] ;
         rscfl[ndx[i]] -= cscfl[ndx[i]] * tblk->phi[ndx[i]] ;
         rscfr[ndx[i]] -= cscfr[ndx[i]] * tblk->phi[ndx[i]] ;
         rsdcc[ndx[i]] -= csdcc[ndx[i]] * tblk->phi[ndx[i]] ;
         rsdcl[ndx[i]] -= csdcl[ndx[i]] * tblk->phi[ndx[i]] ;
         rsdcr[ndx[i]] -= csdcr[ndx[i]] * tblk->phi[ndx[i]] ;
         rsdbc[ndx[i]] -= csdbc[ndx[i]] * tblk->phi[ndx[i]] ;
         rsdfc[ndx[i]] -= csdfc[ndx[i]] * tblk->phi[ndx[i]] ;
         rsucc[ndx[i]] -= csucc[ndx[i]] * tblk->phi[ndx[i]] ;
         rsucl[ndx[i]] -= csucl[ndx[i]] * tblk->phi[ndx[i]] ;
         rsucr[ndx[i]] -= csucr[ndx[i]] * tblk->phi[ndx[i]] ;
         rsubc[ndx[i]] -= csubc[ndx[i]] * tblk->phi[ndx[i]] ;
         rsufc[ndx[i]] -= csufc[ndx[i]] * tblk->phi[ndx[i]] ;
         cdccl[ndx[i]] -= csccl[ndx[i]] ;
         cdccr[ndx[i]] -= csccr[ndx[i]] ;
         cdcbc[ndx[i]] -= cscbc[ndx[i]] ;
         cdcfc[ndx[i]] -= cscfc[ndx[i]] ;
         cdcbl[ndx[i]] -= cscbl[ndx[i]] ;
         cdcbr[ndx[i]] -= cscbr[ndx[i]] ;
         cdcfl[ndx[i]] -= cscfl[ndx[i]] ;
         cdcfr[ndx[i]] -= cscfr[ndx[i]] ;
         cddcc[ndx[i]] -= csdcc[ndx[i]] ;
         cddcl[ndx[i]] -= csdcl[ndx[i]] ;
         cddcr[ndx[i]] -= csdcr[ndx[i]] ;
         cddbc[ndx[i]] -= csdbc[ndx[i]] ;
         cddfc[ndx[i]] -= csdfc[ndx[i]] ;
         cducc[ndx[i]] -= csucc[ndx[i]] ;
         cducl[ndx[i]] -= csucl[ndx[i]] ;
         cducr[ndx[i]] -= csucr[ndx[i]] ;
         cdubc[ndx[i]] -= csubc[ndx[i]] ;
         cdufc[ndx[i]] -= csufc[ndx[i]] ;
         csccl[ndx[i]] = 0.0 ;
         csccr[ndx[i]] = 0.0 ;
         cscbc[ndx[i]] = 0.0 ;
         cscfc[ndx[i]] = 0.0 ;
         cscbl[ndx[i]] = 0.0 ;
         cscbr[ndx[i]] = 0.0 ;
         cscfl[ndx[i]] = 0.0 ;
         cscfr[ndx[i]] = 0.0 ;
         csdcc[ndx[i]] = 0.0 ;
         csdcl[ndx[i]] = 0.0 ;
         csdcr[ndx[i]] = 0.0 ;
         csdbc[ndx[i]] = 0.0 ;
         csdfc[ndx[i]] = 0.0 ;
         csucc[ndx[i]] = 0.0 ;
         csucl[ndx[i]] = 0.0 ;
         csucr[ndx[i]] = 0.0 ;
         csubc[ndx[i]] = 0.0 ;
         csufc[ndx[i]] = 0.0 ;
         if ( ifdivgrad != 1 ) {
            rsdbl[ndx[i]] -= csdbl[ndx[i]] * tblk->phi[ndx[i]] ;
            rsdbr[ndx[i]] -= csdbr[ndx[i]] * tblk->phi[ndx[i]] ;
            rsdfl[ndx[i]] -= csdfl[ndx[i]] * tblk->phi[ndx[i]] ;
            rsdfr[ndx[i]] -= csdfr[ndx[i]] * tblk->phi[ndx[i]] ;
            rsubl[ndx[i]] -= csubl[ndx[i]] * tblk->phi[ndx[i]] ;
            rsubr[ndx[i]] -= csubr[ndx[i]] * tblk->phi[ndx[i]] ;
            rsufl[ndx[i]] -= csufl[ndx[i]] * tblk->phi[ndx[i]] ;
            rsufr[ndx[i]] -= csufr[ndx[i]] * tblk->phi[ndx[i]] ;
            cddbl[ndx[i]] -= csdbl[ndx[i]] ;
            cddbr[ndx[i]] -= csdbr[ndx[i]] ;
            cddfl[ndx[i]] -= csdfl[ndx[i]] ;
            cddfr[ndx[i]] -= csdfr[ndx[i]] ;
            cdubl[ndx[i]] -= csubl[ndx[i]] ;
            cdubr[ndx[i]] -= csubr[ndx[i]] ;
            cdufl[ndx[i]] -= csufl[ndx[i]] ;
            cdufr[ndx[i]] -= csufr[ndx[i]] ;
            csdbl[ndx[i]]  = 0.0 ;
            csdbr[ndx[i]]  = 0.0 ;
            csdfl[ndx[i]]  = 0.0 ;
            csdfr[ndx[i]]  = 0.0 ;
            csubl[ndx[i]]  = 0.0 ;
            csubr[ndx[i]]  = 0.0 ;
            csufl[ndx[i]]  = 0.0 ;
            csufr[ndx[i]]  = 0.0 ;
         }
      }
      myflops += 54.0 * len ;
      if ( ifdivgrad != 1 ) myflops += 24.0 * len ;
      srclist = srclist->next;
   }
   srclist = srclist_ptr;
   while (srclist != NULL) {
      char        *name     = ATTR_GET_OBJECT_NAME(srclist)
      SourceNew_t *mysrc    = SourceNew_find(name,domain->hash);
      int *ndx = mysrc->ndx;
      int  len = mysrc->len;
      if (mysrc->region > 0) {
         ndx = domain->rndx[mysrc->region];
         len = domain->rlen[mysrc->region];
      }
      for ( i = 0 ; i < len ; i++ ) {
         tblk->rhs[ndx[i]] = tblk->phi[ndx[i]] ;
         rblk->ccc[ndx[i]] = 1.0;
      }
      srclist = srclist->next;
   }
   FT_FINALIZE(me, domain->hash, myflops)
}
