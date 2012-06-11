#include "irs.h"
#include "irsreg.h"
#include "irstdiff.h"
#include "irs.h"
#include "Domain.h"
#include "Region.h"
#include "SpeciesFraction.h"
void RegionTableAllocate( Domain_t *domain, Region_t *reg, int nreg )
{
  int ir, i ;
  DomainRegion_t *domainRegions = MALLOT(DomainRegion_t, nreg+1) ;
  for ( ir = 1 ; ir <= nreg ; ir++ ) {
    int length    = domain->rlen[ir]  ;
    int numGroups = reg[ir].numGroups ;
    if ( length > 0 ) {
      domainRegions[ir].regionTables = MALLOT(RegionTable_t,numGroups) ;
      for ( i = 0 ; i < numGroups ; i++ ) {
	domainRegions[ir].regionTables[i].zstar    = MALLOT(double, length) ;
	domainRegions[ir].regionTables[i].z        = MALLOT(double, length) ;
	domainRegions[ir].regionTables[i].a        = MALLOT(double, length) ;
	domainRegions[ir].regionTables[i].massFrac = MALLOT(double, length) ;
	domainRegions[ir].regionTables[i].atomFrac = MALLOT(double, length) ;
	domainRegions[ir].regionTables[i].chemicalPotential
	  = MALLOT(double, length) ;
      }
      if ( (iftmode == 1) || (iftion == 1) ) {
         for ( i = 0 ; i < numGroups ; i++ ) {
	   domainRegions[ir].regionTables[i].dscl = MALLOT(double, length) ;
	   domainRegions[ir].regionTables[i].escl = MALLOT(double, length) ;
	   domainRegions[ir].regionTables[i].pscl = MALLOT(double, length) ;
	   domainRegions[ir].regionTables[i].tscl = MALLOT(double, length) ;
         }
      }
    } else {
      domainRegions[ir].regionTables = NULL ;
    }
  }
  domain->domainRegions = domainRegions ;
}
void RegionTableFree( Domain_t *domain, Region_t *reg, int nreg )
{
  int ir, i ;
  for ( ir = 1 ; ir <= nreg ; ir++ ) {
    int length    = domain->rlen[ir]  ;
    int numGroups = reg[ir].numGroups ;
    if ( length > 0 ) {
      for ( i = 0 ; i < numGroups ; i++ ) {
	FREEMEM(domain->domainRegions[ir].regionTables[i].zstar) ;
	FREEMEM(domain->domainRegions[ir].regionTables[i].z) ;
	FREEMEM(domain->domainRegions[ir].regionTables[i].a) ;
	FREEMEM(domain->domainRegions[ir].regionTables[i].massFrac) ;
	FREEMEM(domain->domainRegions[ir].regionTables[i].atomFrac) ;
	FREEMEM(domain->domainRegions[ir].regionTables[i].chemicalPotential) ;
      }
      if ( (iftmode == 1) || (iftion == 1) ) {
         for ( i = 0 ; i < numGroups ; i++ ) {
  	   FREEMEM(domain->domainRegions[ir].regionTables[i].dscl) ;
	   FREEMEM(domain->domainRegions[ir].regionTables[i].escl) ;
	   FREEMEM(domain->domainRegions[ir].regionTables[i].pscl) ;
	   FREEMEM(domain->domainRegions[ir].regionTables[i].tscl) ;
         }
      }
      FREEMEM(domain->domainRegions[ir].regionTables) ;
    } else {
      domain->domainRegions[ir].regionTables = NULL ;
    }
  }
  FREEMEM(domain->domainRegions) ;
}
void RegionTableInitialize( Domain_t *domain, Region_t *reg, 
			    int nreg, SpeciesFraction_t *specfrac )
{
  int ir, i, j, k ;
  double fourthirds =  4.0 / 3.0, seventhirds = 7.0 / 3.0 ;
  double tenthirds  = 10.0 / 3.0 ;
  for ( ir = 1 ; ir <= nreg ; ir++ ) {
    int length    = domain->rlen[ir]  ;
    int numGroups = reg[ir].numGroups ;
    RegionTable_t *regionTable = domain->domainRegions[ir].regionTables ;
    if ( length > 0 ) { 
      if ( reg[ir].type == _Dynamic_ ) {
	for ( i = 0 ; i < numGroups ; i++ ) {
	  double *zbar     = regionTable[i].z ;
	  double *abar     = regionTable[i].a ;
	  double *massFrac = regionTable[i].massFrac ;
	  double *atomFrac = regionTable[i].atomFrac ;
	  double normalizationFactor ;
	  for ( j = 0 ; j < length ; j++) {
	    int index   = domain->rndx[ir][j] ;
	    abar[j]     = 0.0 ;
	    zbar[j]     = 0.0 ;
	    massFrac[j] = 0.0 ;
	    normalizationFactor = 0.0 ;
	    for ( k = 0 ; k < reg[ir].eosGroup[i].numSpeciesInGroup ; k++ ) {
	      int speciesIndex    = reg[ir].eosGroup[i].speclist[k] ;
	      double zSpecies     = reg[ir].species[speciesIndex].zbar ;
	      double aSpecies     = reg[ir].species[speciesIndex].abar ;
	      double *massSpecies = specfrac[index].mass_frac ;
	      double atomFraction = massSpecies[speciesIndex] / aSpecies ;
	      zbar[j]             += atomFraction * zSpecies ;
	      abar[j]             += atomFraction * aSpecies ;
	      massFrac[j]         += massSpecies[speciesIndex] ;
	      normalizationFactor += atomFraction ;
	    }
	    if ( normalizationFactor > 0.0 ) {
	      atomFrac[j]         = normalizationFactor ;
	      normalizationFactor = 1.0 / (normalizationFactor + ptiny) ;
	      zbar[j] *= normalizationFactor ;
	      abar[j] *= normalizationFactor ;
              zbar[j]  = MAX( zbar[j], 1.0 ) ;
              abar[j]  = MAX( abar[j], 1.0 ) ;
	    } else {
	      atomFrac[j] = 0.0 ;
	      zbar[j]     = reg[ir].eosGroup[i].zbar ;
	      abar[j]     = reg[ir].eosGroup[i].abar ;
              zbar[j]     = MAX( zbar[j], 1.0 ) ;
              abar[j]     = MAX( abar[j], 1.0 ) ;
	    }
	  }
	}
	for ( j = 0 ; j < length ; j++ ) { 
	  double normalizationFactor = 0.0 ;
	  for ( i = 0 ; i < numGroups ; i++ ) {
	    normalizationFactor += regionTable[i].atomFrac[j] ;
	  }
	  normalizationFactor = 1.0 / ( normalizationFactor + ptiny ) ;
	  for ( i = 0 ; i < numGroups ; i++ ) {
	    regionTable[i].atomFrac[j] *= normalizationFactor ;
	  }
	}
      } else { 
	for ( i = 0 ; i < numGroups ; i++ ) {
	  double *zbar     = regionTable[i].z ;
	  double *abar     = regionTable[i].a ;
	  double *massFrac = regionTable[i].massFrac ;
	  double *atomFrac = regionTable[i].atomFrac ;
	  double *chemicalPotential = regionTable[i].chemicalPotential ;
	  double normalizationFactor = 0.0 ;
	  double staticZbar          = 0.0 ;
	  double staticAbar          = 0.0 ;
	  double staticMassFraction  = 0.0 ;
	  if ( reg[ir].type == _Static_) {
	    for ( k = 0 ; k < reg[ir].eosGroup[i].numSpeciesInGroup ; k++ ) {
	      int speciesIndex = reg[ir].eosGroup[i].speclist[k] ;
	      double zSpecies  = reg[ir].species[speciesIndex].zbar ;
	      double aSpecies  = reg[ir].species[speciesIndex].abar ;
	      double atomFraction =
		reg[ir].species[speciesIndex].atomFraction0 ;
	      double massFraction = 
		reg[ir].species[speciesIndex].massFraction0 ;
	      staticAbar          += atomFraction * aSpecies ;
	      staticZbar          += atomFraction * zSpecies ;
	      staticMassFraction  += massFraction ;
	      normalizationFactor += atomFraction ;
	    }
	    if ( normalizationFactor > 0.0 ) {
	      staticZbar /= ( normalizationFactor + ptiny ) ;
	      staticAbar /= ( normalizationFactor + ptiny ) ;
	    } else {
	      staticZbar          = reg[ir].eosGroup[i].zbar ;
	      staticAbar          = reg[ir].eosGroup[i].abar ;
	      staticMassFraction  = 0.0 ;
	      normalizationFactor = 0.0 ;
	    }
	  } else { 
	    staticZbar          = reg[ir].eosGroup[i].zbar ;
	    staticAbar          = reg[ir].eosGroup[i].abar ;
	    staticMassFraction  = 1.0 ;
	    normalizationFactor = 1.0 ;
	  }
	  for ( j = 0 ; j < length ; j++ ) {
	    zbar[j]     = staticZbar ;
	    abar[j]     = staticAbar ;
            zbar[j]     = MAX( zbar[j], 1.0 ) ;
            abar[j]     = MAX( abar[j], 1.0 ) ;
	    massFrac[j] = staticMassFraction  ;
	    atomFrac[j] = normalizationFactor ;
	    chemicalPotential[j] = 0.0 ;
	  }
	} 
      }   
      if ( (iftmode == 1) || (iftion == 1) ) {
         for ( i = 0 ; i < numGroups ; i++ ) {
            double densityMultiplier  = reg[ir].eosGroup[i].densityMultiplier  ;
            double energyMultiplier   = reg[ir].eosGroup[i].energyMultiplier   ;
            double pressureMultiplier = reg[ir].eosGroup[i].pressureMultiplier ;
            double abarTable          = reg[ir].eosGroup[i].database.abar      ;
            double zbarTable          = reg[ir].eosGroup[i].database.zbar      ;
	    double *zbar = regionTable[i].z    ;
	    double *abar = regionTable[i].a    ;
            double *dscl = regionTable[i].dscl ;
            double *escl = regionTable[i].escl ;
            double *pscl = regionTable[i].pscl ;
            double *tscl = regionTable[i].tscl ;
	    for ( j = 0 ; j < length ; j++) {
               double ascl = abarTable / abar[j] ;
               double zscl = zbarTable / zbar[j] ;
               dscl[j] = densityMultiplier * zscl * ascl ;
               escl[j] = pow( zscl, seventhirds ) / ( ascl * energyMultiplier ) ;
               pscl[j] = pressureMultiplier * pow( zscl, -tenthirds ) ;
               tscl[j] = pow( zscl, fourthirds ) ;
	    }
         }   
      }
    }     
  }       
}
