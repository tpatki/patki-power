#include "irs.h"
#include "irssrc.h"
#include "FunctionTimer.h"
void tmsrc( double stime, double *ee, double *te, double *dedt,
                          double *ei, double *ti, double *deidt,
            Domain_t *domain )
{
   char *me = "tmsrc";
   int isrc, irsrc, i, ntimes, slen ;
   int *sndx ;
   double srct0, srctn, srcv0, srcvn, temperature ;
   double *srctime, *srcval ;
   double myflops = 1 ;
   FT_INITIALIZE(me, domain->hash)
   for ( isrc = 0 ; isrc < domain->nsrc ; isrc++ ) {
      if ( domain->src[isrc].type == TESRC1 ) {
         sndx        = domain->src[isrc].ndxsrc   ;
         slen        = domain->src[isrc].nzsrc    ;
         temperature = domain->src[isrc].fdat1[0] ;
         for ( i = 0 ; i < slen ; i++ ) {
	    ee[sndx[i]] += dedt[sndx[i]] * ( temperature - te[sndx[i]] ) ;
            te[sndx[i]]  = temperature ;
	 }
         myflops += 3.0 * slen ;
      } else if ( domain->src[isrc].type == TESRCINT1 ) {
         irsrc       = domain->src[isrc].idat1[0] ;
         temperature = domain->src[isrc].fdat1[0] ;
         slen = 0 ;
         if ( irsrc > 0 ) {
            sndx = domain->rndx[irsrc] ;
            slen = domain->rlencln[irsrc] ;
	 }
         for ( i = 0 ; i < slen ; i++ ) {
	    ee[sndx[i]] += dedt[sndx[i]] * ( temperature - te[sndx[i]] ) ;
            te[sndx[i]]  = temperature ;
	 }
         myflops += 3.0 * slen ;
      } else if ( domain->src[isrc].type == TESRC2 ) {
         sndx    = domain->src[isrc].ndxsrc   ;
         slen    = domain->src[isrc].nzsrc    ;
         ntimes  = domain->src[isrc].idat1[0] ;
         srctime = domain->src[isrc].dat2     ;
         srcval  = srctime + 1         ;
         srct0   = srctime[0] ;
         srctn   = srctime[2*(ntimes-1)] ;
         srcv0   = srcval[0] ;
         srcvn   = srcval[2*(ntimes-1)] ;
         if ( stime <= srct0 ) {
            temperature = srcv0 ;
         } else if ( stime >= srctn ) {
            temperature = srcvn ;
         } else {
	    for ( i = 2 ; i < 2*ntimes ; i += 2 ) {
               if ( stime < srctime[i] )  break ;
	    }
            temperature = ( srcval[i-2] * ( srctime[i] - stime )
                          + srcval[i]   * ( stime - srctime[i-2] ) )
                          / ( srctime[i] - srctime[i-2] ) ;
         }
         for ( i = 0 ; i < slen ; i++ ) {
            ee[sndx[i]] += dedt[sndx[i]] * ( temperature - te[sndx[i]] ) ;
            te[sndx[i]]  = temperature ;
	 }
         myflops += 3.0 * slen ;
      } else if ( domain->src[isrc].type == TESRCINT2 ) {
         irsrc   = domain->src[isrc].idat1[1] ;
         ntimes  = domain->src[isrc].idat1[0] ;
         slen = 0 ;
         if ( irsrc > 0 ) {
            sndx = domain->rndx[irsrc] ;
            slen = domain->rlencln[irsrc] ;
	 }
         srctime = domain->src[isrc].dat2     ;
         srcval  = srctime + 1         ;
         srct0   = srctime[0] ;
         srctn   = srctime[2*(ntimes-1)] ;
         srcv0   = srcval[0] ;
         srcvn   = srcval[2*(ntimes-1)] ;
         if ( stime <= srct0 ) {
            temperature = srcv0 ;
         } else if ( stime >= srctn ) {
            temperature = srcvn ;
         } else {
	    for ( i = 2 ; i < 2*ntimes ; i += 2 ) {
               if ( stime < srctime[i] )  break ;
	    }
            temperature = ( srcval[i-2] * ( srctime[i] - stime )
                          + srcval[i]   * ( stime - srctime[i-2] ) )
                          / ( srctime[i] - srctime[i-2] ) ;
         }
         for ( i = 0 ; i < slen ; i++ ) {
            ee[sndx[i]] += dedt[sndx[i]] * ( temperature - te[sndx[i]] ) ;
            te[sndx[i]]  = temperature ;
	 }
         myflops += 3.0 * slen ;
      }
   }
   if ( iftion == 0 ) {
      FT_FINALIZE(me, domain->hash, myflops)
      return ;
   }
   for ( isrc = 0 ; isrc < domain->nsrc ; isrc++ ) {
      if ( domain->src[isrc].type == TISRC1 ) {
         sndx        = domain->src[isrc].ndxsrc   ;
         slen        = domain->src[isrc].nzsrc    ;
         temperature = domain->src[isrc].fdat1[0] ;
         for ( i = 0 ; i < slen ; i++ ) {
	    ei[sndx[i]] += deidt[sndx[i]] * ( temperature - ti[sndx[i]] ) ;
            ti[sndx[i]]  = temperature ;
	 }
         myflops += 3.0 * slen ;
      } else if ( domain->src[isrc].type == TISRCINT1 ) {
         irsrc       = domain->src[isrc].idat1[0] ;
         temperature = domain->src[isrc].fdat1[0] ;
         slen = 0 ;
         if ( irsrc > 0 ) {
            sndx = domain->rndx[irsrc] ;
            slen = domain->rlencln[irsrc] ;
	 }
         for ( i = 0 ; i < slen ; i++ ) {
            ei[sndx[i]] += deidt[sndx[i]] * ( temperature - ti[sndx[i]] ) ;
            ti[sndx[i]]  = temperature ;
	 }
         myflops += 3.0 * slen ;
      } else if ( domain->src[isrc].type == TISRC2 ) {
         sndx    = domain->src[isrc].ndxsrc   ;
         slen    = domain->src[isrc].nzsrc    ;
         ntimes  = domain->src[isrc].idat1[0] ;
         srctime = domain->src[isrc].dat2     ;
         srcval  = srctime + 1         ;
         srct0   = srctime[0] ;
         srctn   = srctime[2*(ntimes-1)] ;
         srcv0   = srcval[0] ;
         srcvn   = srcval[2*(ntimes-1)] ;
         if ( stime <= srct0 ) {
            temperature = srcv0 ;
         } else if ( stime >= srctn ) {
            temperature = srcvn ;
         } else {
	    for ( i = 2 ; i < 2*ntimes ; i += 2 ) {
               if ( stime < srctime[i] )  break ;
	    }
            temperature = ( srcval[i-2] * ( srctime[i] - stime )
                          + srcval[i]   * ( stime - srctime[i-2] ) )
                          / ( srctime[i] - srctime[i-2] ) ;
         }
         for ( i = 0 ; i < slen ; i++ ) {
            ei[sndx[i]] += deidt[sndx[i]] * ( temperature - ti[sndx[i]] ) ;
            ti[sndx[i]]  = temperature ;
	 }
         myflops += 3.0 * slen ;
      } else if ( domain->src[isrc].type == TISRCINT2 ) {
         irsrc   = domain->src[isrc].idat1[1] ;
         ntimes  = domain->src[isrc].idat1[0] ;
         slen = 0 ;
         if ( irsrc > 0 ) {
            sndx = domain->rndx[irsrc] ;
            slen = domain->rlencln[irsrc] ;
	 }
         srctime = domain->src[isrc].dat2     ;
         srcval  = srctime + 1         ;
         srct0   = srctime[0] ;
         srctn   = srctime[2*(ntimes-1)] ;
         srcv0   = srcval[0] ;
         srcvn   = srcval[2*(ntimes-1)] ;
         if ( stime <= srct0 ) {
            temperature = srcv0 ;
         } else if ( stime >= srctn ) {
            temperature = srcvn ;
         } else {
	    for ( i = 2 ; i < 2*ntimes ; i += 2 ) {
               if ( stime < srctime[i] )  break ;
	    }
            temperature = ( srcval[i-2] * ( srctime[i] - stime )
                          + srcval[i]   * ( stime - srctime[i-2] ) )
                          / ( srctime[i] - srctime[i-2] ) ;
         }
         for ( i = 0 ; i < slen ; i++ ) {
            ei[sndx[i]] += deidt[sndx[i]] * ( temperature - ti[sndx[i]] ) ;
            ti[sndx[i]]  = temperature ;
	 }
         myflops += 3.0 * slen ;
      }
   }
   FT_FINALIZE(me, domain->hash, myflops)
}
