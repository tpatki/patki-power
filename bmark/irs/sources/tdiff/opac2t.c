#include "irs.h"
#include "irsreg.h"
#include "irstdiff.h"
#include "FunctionTimer.h"
void opac2t( double *phi, Domain_t *domain, 
	     double *kros, double *tmax, double dtrad )
{
  char *me = "opac2t";
  int i, j, ir, *ndx, *ndxmix, *grdmix, *mixzn ;
  int fm, number ;
  double kaproslmt ; 
  double *data ;
  double *den = domain->den ;
  double myflops = 0.0;
  FT_INITIALIZE(me, domain->hash)
  for ( i = 0 ; i < domain->namix ; i++ ) {
    kros[i] = 0.0 ;
  }
  for ( ir = 1 ; ir <= nreg ; ir++ ) {
    int length = domain->rlen[ir];
    if ( length > 0 ) {
      double *ckros = MALLOT(double, length) ;
      double *cden  = MALLOT(double, length) ;
      double *volFrac ;
      int *zonelist = domain->rndx[ir]  ;
      int numGroups = reg[ir].numGroups ;
      for ( j = 0 ; j < numGroups ; j++ ) {
	RegionTable_t regionTable = 
	              domain->domainRegions[ir].regionTables[j] ;
	OpacityGroup_t *opacityGroup = &reg[ir].opacityGroup[j] ;
        double *massFraction = regionTable.massFrac ;
	double *zbar         = regionTable.z ;
	double *abar         = regionTable.a ;
	fm     = reg[ir].opacityGroup[j].rosTable.form ;
	data   = reg[ir].opacityGroup[j].rosTable.data ;
	number = reg[ir].opacityGroup[j].rosTable.number ;
        if ( numGroups == 1 ) {
           for ( i = 0 ; i < length ; i++ ) {
              cden[i] = den[zonelist[i]] ;
           }
        } else {
           volFrac = domain->eosvf + j * domain->namix ;
           for ( i = 0 ; i < length ; i++ ) {
              cden[i] = massFraction[i] * den[zonelist[i]] /
                        ( volFrac[zonelist[i]] + ptiny ) ;
           }
           myflops += 6.0 * length ;
        }
	if        ( fm == 1 ) {
	  KrAnalytic_fm1( ckros, cden, data, dtrad, ir,
		          domain, opacityGroup ) ;
	} else if ( fm == 3 ) {
	  KrAnalytic_fm3( ckros, cden, tmax, abar, data, dtrad, ir,
	    	          domain, opacityGroup ) ;
	} else if ( fm == 5 ) {
	  KrAnalytic_fm5( ckros, cden, tmax, abar, zbar, dtrad, ir,
		          domain, opacityGroup ) ;
	} else if ( fm == 6 ) {
	  KrAnalytic_fm6( ckros, cden, tmax, abar, zbar, data, dtrad,
                          ir, domain, opacityGroup ) ;
	} else if ( fm == 7 ) {
	  KrAnalytic_fm7( ckros, cden, tmax, data, dtrad, ir,
		          domain, opacityGroup ) ;
	} else if ( fm == 8 ) {
	  KrAnalytic_fm8( ckros, cden, data, dtrad, ir,
		          domain, opacityGroup ) ;
	} else if ( fm == 9 ) {
	  double refd = reg[ir].eosGroup[j].refd ;
	  KrAnalytic_fm9( ckros, cden, abar, data, refd, dtrad, ir,
		          domain, opacityGroup ) ;
	} else if ( fm == 200 ) {
	  PRINT(stdout, "Rosseland opacity form 200 not yet implemented.\n") ;
	} else if ( fm == 201 ) {
	  PRINT(stdout, "Rosseland opacity form 201 not yet implemented.\n") ;
	} else if ( fm == 202 ) {
	  PRINT(stdout, "Rosseland opacity form 202 not yet implemented.\n") ;
	}
        if ( numGroups == 1 ) {
  	  for ( i = 0 ; i < length ; i++ ) {
	    kros[zonelist[i]] = ckros[i] ;
	  }
	} else {
  	  for ( i = 0 ; i < length ; i++ ) {
	    kros[zonelist[i]] += volFrac[zonelist[i]] * ckros[i] ;
	  }
          myflops += 2.0 * length ;
	}
      }
      FREEMEM(ckros) ;
      FREEMEM(cden)  ;
      if ( reg[ir].mfplmt > 0.0 ) {
	kaproslmt = 1.0 / reg[ir].mfplmt ;
	opaclmt( kros, kaproslmt, zonelist, length, domain) ;
      }
      if ( domain->rlenmix[ir] > 0 ) {
	ndxmix = domain->rndxmix[ir] ;
	grdmix = domain->rgrdmix[ir] ;
	mixzn  = domain->rmixzn [ir] ;
	if ( ifkrwgt == 1 ) {
	  for ( i = 0 ; i < domain->rlenmix[ir] ; i++ ) {
	    kros[grdmix[i]] += kros[ndxmix[i]] * domain->vol[ndxmix[i]] ;
	  }
	  myflops += 2.0 * domain->rlenmix[ir] ;
	} else if ( ifkrwgt == 2 ) {
	  for ( i = 0 ; i < domain->rlenmix[ir] ; i++ ) {
	    kros[grdmix[i]] += kros[ndxmix[i]]
	                     * domain->den[ndxmix[i]] * domain->vol[ndxmix[i]] ;
	  }
	  myflops += 3.0 * domain->rlenmix[ir] ;
	} else if ( ifkrwgt == 3 ) {
	  for ( i = 0 ; i < domain->rlenmix[ir] ; i++ ) {
	    kros[grdmix[i]] += kros[ndxmix[i]]
	                     / ( domain->vol[ndxmix[i]] + ptiny ) ;
	  }
	  myflops += 6.0 * domain->rlenmix[ir] ;
	} else if ( ifkrwgt == 4 ) {
	  for ( i = 0 ; i < domain->rlenmix[ir] ; i++ ) {
	    kros[grdmix[i]] += kros[ndxmix[i]]
      	                     / ( domain->den[ndxmix[i]] *
                                 domain->vol[ndxmix[i]] + ptiny ) ;
	  }
	  myflops += 7.0 * domain->rlenmix[ir] ;
	}
      }
    }
  }
  ndx = domain->rndx[0] ;
  for ( i = 0 ; i < domain->rlen[0] ; i++ ) {
    kros[ndx[i]] = 0.0 ;
  }
  FT_FINALIZE(me, domain->hash, myflops)
}
