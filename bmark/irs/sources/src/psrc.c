#include "irs.h"
#include "irssrc.h"
#include "FunctionTimer.h"
void psrc( double ptime, Domain_t *domain )
{
   char *me = "psrc";
   int isrc, i, ntimes, slen ;
   int *sndx ;
   double srct0, srctn, srcv0, srcvn, pressure ;
   double *srctime, *srcval ;
   FT_INITIALIZE(me, domain->hash)
   for ( isrc = 0 ; isrc < domain->nsrc ; isrc++ ) {
      if ( domain->src[isrc].type == PSRC1 ) {
         sndx     = domain->src[isrc].ndxsrc   ;
         slen     = domain->src[isrc].nzsrc    ;
         pressure = domain->src[isrc].fdat1[0] ;
         for ( i = 0 ; i < slen ; i++ ) {
	    domain->p[sndx[i]] = pressure ;
	 }
      } else if ( domain->src[isrc].type == PSRC2 ) {
         sndx    = domain->src[isrc].ndxsrc   ;
         slen    = domain->src[isrc].nzsrc    ;
         ntimes  = domain->src[isrc].idat1[0] ;
         srctime = domain->src[isrc].dat2     ;
         srcval  = srctime + 1         ;
         srct0   = srctime[0] ;
         srctn   = srctime[2*(ntimes-1)] ;
         srcv0   = srcval[0] ;
         srcvn   = srcval[2*(ntimes-1)] ;
         if ( ptime <= srct0 ) {
            pressure = srcv0 ;
         } else if ( ptime >= srctn ) {
            pressure = srcvn ;
         } else {
	    for ( i = 2 ; i < 2*ntimes ; i += 2 ) {
               if ( ptime < srctime[i] )  break ;
	    }
            pressure = ( srcval[i-2] * ( srctime[i] - ptime )
                       + srcval[i]   * ( ptime - srctime[i-2] ) )
                       / ( srctime[i] - srctime[i-2] ) ;
         }
         for ( i = 0 ; i < slen ; i++ ) {
            domain->p[sndx[i]] = pressure ;
	 }
      }
   }
   FT_FINALIZE(me, domain->hash, 1)
}
