#include "irs.h"
#include "irssrc.h"
#include "FunctionTimer.h"
void esrc( double etime, double *emat, Domain_t *domain )
{
   char *me = "esrc";
   int isrc, i, ntimes, slen ;
   int *sndx ;
   double srct0, srctn, srcv0, srcvn, energy ;
   double *srctime, *srcval ;
   FT_INITIALIZE(me, domain->hash)
   for ( isrc = 0 ; isrc < domain->nsrc ; isrc++ ) {
      if ( domain->src[isrc].type == ESRC1 ) {
         sndx   = domain->src[isrc].ndxsrc   ;
         slen   = domain->src[isrc].nzsrc    ;
         energy = domain->src[isrc].fdat1[0] ;
         for ( i = 0 ; i < slen ; i++ ) {
	    emat[sndx[i]] = energy ;
	 }
      } else if ( domain->src[isrc].type == ESRC2 ) {
         sndx    = domain->src[isrc].ndxsrc   ;
         slen    = domain->src[isrc].nzsrc    ;
         ntimes  = domain->src[isrc].idat1[0] ;
         srctime = domain->src[isrc].dat2     ;
         srcval  = srctime + 1         ;
         srct0   = srctime[0] ;
         srctn   = srctime[2*(ntimes-1)] ;
         srcv0   = srcval[0] ;
         srcvn   = srcval[2*(ntimes-1)] ;
         if ( etime <= srct0 ) {
            energy = srcv0 ;
         } else if ( etime >= srctn ) {
            energy = srcvn ;
         } else {
	    for ( i = 2 ; i < 2*ntimes ; i += 2 ) {
               if ( etime < srctime[i] )  break ;
	    }
            energy = ( srcval[i-2] * ( srctime[i] - etime )
                     + srcval[i]   * ( etime - srctime[i-2] ) )
                     / ( srctime[i] - srctime[i-2] ) ;
         }
         for ( i = 0 ; i < slen ; i++ ) {
            emat[sndx[i]] = energy ;
	 }
      }
   }
   FT_FINALIZE(me, domain->hash, 1)
}
