#include "irs.h"
#include "irssrc.h"
#include "FunctionTimer.h"
#include "UserList.h"
#include "Region.h"
void erate( double etime, double dterate, double *dele, int type,
            Domain_t *domain )
{
   char *me = "erate";
   int isrc, i, j, ntimes, slen ;
   int *sndx , sreg;
   double srct0, srctn, srcv0, srcvn, energy ;
   double *srctime, *srcval, ertim, fraction ;
   double myflops  = 1.0;
   double *tmat    = domain->tmat    ;
   double *ematsrc = domain->ematsrc ;
   double *eionsrc = domain->eionsrc ;
   double *frac    = MALLOT(double, domain->namix);
   int *speclist;
   int nspeclist;
   FT_INITIALIZE(me, domain->hash)
   for ( isrc = 0 ; isrc < domain->nsrc ; isrc++ ) {
      UserList_t *list = NULL;
      if ( (domain->src[isrc].type == ERATE2) && (type == 0) ) {
         sndx    = domain->src[isrc].ndxsrc   ;
         slen    = domain->src[isrc].nzsrc    ;
         ntimes  = domain->src[isrc].idat1[0] ;
         srctime = domain->src[isrc].dat2     ;
         srcval  = srctime + 1         ;
         srct0   = srctime[0] ;
         srctn   = srctime[2*(ntimes-1)] ;
         srcv0   = srcval[0] ;
         srcvn   = srcval[2*(ntimes-1)] ;
         ertim   = etime + dterate * 0.5 ;
         sreg    = domain->src[isrc].idat1[1] ;
	 if (sreg > 0 ) {
	   slen = domain->rlen[sreg];
	   sndx = domain->rndx[sreg];
	 }
         if ( ertim <= srct0 ) {
            energy = srcv0 * dterate ;
         } else if ( ertim >= srctn ) {
            energy = srcvn * dterate ;
         } else {
	    for ( i = 2 ; i < 2*ntimes ; i += 2 ) {
               if ( ertim < srctime[i] )  break ;
	    }
            energy = dterate * ( srcval[i-2] * ( srctime[i] - ertim )
                     + srcval[i]   * ( ertim - srctime[i-2] ) )
                     / ( srctime[i] - srctime[i-2] ) ;
         }
         for ( i = 0 ; i < slen ; i++ ) {
            dele[sndx[i]] += energy ;
	 }
         myflops += slen;
      }
      if ( (domain->src[isrc].type == ERATE4) && (type == 1) ) {
         sndx    = domain->src[isrc].ndxsrc   ;
         slen    = domain->src[isrc].nzsrc    ;
         ntimes  = domain->src[isrc].idat1[0] ;
         srctime = domain->src[isrc].dat2     ;
         srcval  = srctime + 1         ;
         srct0   = srctime[0] ;
         srctn   = srctime[2*(ntimes-1)] ;
         srcv0   = srcval[0] ;
         srcvn   = srcval[2*(ntimes-1)] ;
         ertim   = etime + dterate * 0.5 ;
         sreg    = domain->src[isrc].idat1[1] ;
	 if (sreg > 0 ) {
	   slen = domain->rlen[sreg];
	   sndx = domain->rndx[sreg];
           list = UserList_find(domain->src[isrc].ndxName);
	 }
	 for (i = 0; i < slen; i++) {
	    frac[i] = 1.0;
	 }
	 if ((ifdynspec == 1) && (list != NULL)) {
	    UserList_t *list_ptr = list;    
	    speclist = MALLOT(int, reg[sreg].nspec);
	    nspeclist = 0;
	    while (list_ptr != NULL) {
	       for (i = 0; i < reg[sreg].nspec; i++) {
	          if (!strcmp(list_ptr->name, reg[sreg].species[i].name)) {
	             speclist[nspeclist++] = i;
	          }
	       }
	       list_ptr = list_ptr->next;
	    }
	    for (i = 0; i < slen; i++) {
	       frac[i] = 0.0;
	       for (j = 0; j < nspeclist; j++) {
	          frac[i] += domain->specfrac[sndx[i]].mass_frac[speclist[j]];
	       }
	    }
	 }
         if ( ertim <= srct0 ) {
            energy = srcv0 * dterate;
         } else if ( ertim >= srctn ) {
            energy = srcvn * dterate ;
         } else {
	    for ( i = 2 ; i < 2*ntimes ; i += 2 ) {
               if ( ertim < srctime[i] )  break ;
	    }
            energy = dterate * ( srcval[i-2] * ( srctime[i] - ertim )
                     + srcval[i]   * ( ertim - srctime[i-2] ) )
                     / ( srctime[i] - srctime[i-2] ) ;
         }
         if ( iftmode == 1 ) {
            for ( i = 0 ; i < slen ; i++ ) {
               ematsrc[sndx[i]] += energy * frac[i];
	    }
            myflops += (2 * slen) ;
	 }
         if ( iftion == 1 ) {
            for ( i = 0 ; i < slen ; i++ ) {
               double fenergy = energy * frac[i];
               fraction          = tmat[sndx[i]] / ( tmat[sndx[i]] + tsplit ) ;
               fraction          = MIN( fraction, 1.0 ) ;
               fraction          = MAX( fraction, 0.0 ) ;
               ematsrc[sndx[i]] += ( 1.0 - fraction ) * fenergy;
               eionsrc[sndx[i]] +=         fraction   * fenergy;
	    }
            myflops += 11.0 * slen ;
	 }
	 if ((ifdynspec == 1) && (list != NULL)) {
	    FREEMEM(speclist);
	 }
      }
   }
   FREEMEM(frac);
   FT_FINALIZE(me, domain->hash, myflops)
}
