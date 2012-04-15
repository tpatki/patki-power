#include "irs.h"
#include "irsreg.h"
#include "irstdiff.h"
#include "FunctionTimer.h"
void planck_opacity( double *xplnk, double *tcen, double dtrad,
                     double *phi, Domain_t *domain )
{  
   char *me = "planck_opacity";
   int i, j, ir, form, number, *ndx, *ndxmix, *grdmix ;
   double tm3, xlim, limitc ;
   double *den = domain->den ;
   double myflops = 0.0;
   FT_INITIALIZE(me, domain->hash)
   limitc = dtrad * 2.998e4 * 10.0 / 3.0 ;
   for ( ir = 1 ; ir <= nreg ; ir++ ) {
      int    numGroups = reg[ir].numGroups ;
      int    length    = domain->rlen[ir] ;
      double *ckros    = MALLOT(double,length) ;
      double *cplnk    = MALLOT(double,length) ;
      double *cden     = MALLOT(double,length) ;
      ndx              = domain->rndx[ir] ;
      for ( i = 0 ; i < length ; i++ ) {
         xplnk[ndx[i]] = 0.0 ;
      }
      if ( length > 0 ) {
         for ( j = 0 ; j < numGroups ; j++ ) {
	    RegionTable_t *regionTable = 
	      &domain->domainRegions[ir].regionTables[j] ;
	    OpacityGroup_t *opacityGroup = &reg[ir].opacityGroup[j] ;
	    double *massFraction         = regionTable->massFrac ;
            double *zstar                = regionTable->zstar ;
            double *zbar                 = regionTable->z ;
            double *abar                 = regionTable->a ;
            double *mu                   = regionTable->chemicalPotential ;
            double *volFrac ;
            double *coef                 = opacityGroup->planckTable.data ;
	    double planckMultiplier      = opacityGroup->planckMultiplier ;
            if ( numGroups == 1 ) {
               for ( i = 0 ; i < length ; i++ ) {
                  cden[i] = den[ndx[i]] ;
	       }
	    } else {
               volFrac = domain->eosvf + j * domain->namix ;
               for ( i = 0 ; i < length ; i++ ) {
                  cden[i] = massFraction[i] * den[ndx[i]] /
                            ( volFrac[ndx[i]] + ptiny ) ;
	       }
               myflops += 6.0 * length ;
	    }
	    form   = reg[ir].opacityGroup[j].planckTable.form   ;
            number = reg[ir].opacityGroup[j].planckTable.number ;
            if        ( form == 1 ) {
               KpAnalytic_fm1( cplnk, cden, coef, dtrad, ir,
                               domain, opacityGroup ) ;
            } else if ( form == 2 ) {
	       KpAnalytic_fm2( cplnk, cden, abar, zbar, zstar, mu, dtrad, ir,
                               phi, domain, opacityGroup ) ;
            } else if ( form == 3 ) {
               ;
            } else if ( form == 5 ) {
               KpAnalytic_fm5( cplnk, cden, abar, zstar, dtrad, ir,
                               domain, opacityGroup ) ;
            } else if ( form == 6 ) {
               ;
            } else if ( form == 7 ) {
               KpAnalytic_fm7( cplnk, cden, domain->tmat, coef, dtrad, ir,
                               domain, opacityGroup ) ;
            } else if ( form == 8 ) {
	       KpAnalytic_fm8( cplnk, cden, abar, zbar, dtrad, ir,
                               phi, domain, opacityGroup ) ;
            } else if ( form == 9 ) {
	       KpAnalytic_fm9( cplnk, cden, abar, zbar, dtrad, ir,
                               phi, domain, opacityGroup ) ;
	    }
            if ( numGroups == 1 ) {
   	       for ( i = 0 ; i < length ; i++ ) {
	          xplnk[ndx[i]] = cplnk[i] ;
	       }
	    } else {
   	       for ( i = 0 ; i < length ; i++ ) {
	          xplnk[ndx[i]] += volFrac[ndx[i]] * cplnk[i] ;
	       }
               myflops += 2.0 * length ;
	    }
	    if ( reg[ir].plklmt > 0.0 ) {
	      for ( i = 0 ; i < length ; i++ ) {
		tm3  = MAX( domain->tmat[ndx[i]], tfloor ) ;
		tm3  = tm3 * tm3 * tm3 ;
		xlim = reg[ir].plklmt * cden[i] *
		  domain->dedt[ndx[i]] / ( 4.0 * tm3 * sbc ) ;
		cplnk[i] = MIN( cplnk[i], xlim ) ;
	      }
	      myflops += 10.0 * length;
	    }
	    if ( planckMultiplier <= 10.0 ) {
	      int fm        = reg[ir].opacityGroup[j].rosTable.form ;
	      double *data  = reg[ir].opacityGroup[j].rosTable.data ;
	      number        = reg[ir].opacityGroup[j].rosTable.number ;
	      if        ( fm == 1 ) {
		KrAnalytic_fm1( ckros, cden, data, dtrad, ir,
				domain, opacityGroup ) ;
	      } else if ( fm == 3 ) {
		KrAnalytic_fm3( ckros, cden, tcen, abar, data, 
				dtrad, ir,
				domain, opacityGroup ) ;
	      } else if ( fm == 5 ) {
		KrAnalytic_fm5( ckros, cden, tcen, abar, zbar,
				dtrad, ir,
				domain, opacityGroup ) ;
	      } else if ( fm == 6 ) {
		KrAnalytic_fm6( ckros, cden, tcen, abar, zbar, data,
				dtrad, ir, domain, opacityGroup ) ;
	      } else if ( fm == 7 ) {
		KrAnalytic_fm7( ckros, cden, tcen, data, dtrad, ir,
				domain, opacityGroup ) ;
	      } else if ( fm == 8 ) {
		KrAnalytic_fm8( ckros, cden, data, dtrad, ir,
				domain, opacityGroup ) ;
	      } else if ( fm == 9 ) {
		double refd = reg[ir].eosGroup[j].refd ;
		KrAnalytic_fm9( ckros, cden, abar, data, 
				refd, dtrad, ir,
				domain, opacityGroup ) ;
	      }
	      for ( i = 0 ; i < domain->rlen[ir] ; i++ ) {
		xlim = limitc * ckros[i] ;
		cplnk[i] = MIN( cplnk[i], xlim ) ;
	      }
	      myflops += 1.0 * domain->rlen[ir] ;
	    }
	 }
         FREEMEM(cplnk) ;
         FREEMEM(ckros) ;
         FREEMEM(cden)  ;
         if ( domain->rlenmix[ir] > 0 ) {
	    ndxmix = domain->rndxmix[ir] ;
	    grdmix = domain->rgrdmix[ir] ;
	    for ( i = 0 ; i < domain->rlenmix[ir] ; i++ ) {
	       xplnk[grdmix[i]] += xplnk[ndxmix[i]] * domain->vol[ndxmix[i]] ;
	    }
	    myflops += 2.0 * domain->rlenmix[ir] ;
         }
      }
   }
   FT_FINALIZE(me, domain->hash, myflops)
}
