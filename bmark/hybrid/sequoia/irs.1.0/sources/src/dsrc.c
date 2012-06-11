#include "irs.h"
#include "irssrc.h"
#include "FunctionTimer.h"
void dsrc( double dtime, double *den, Domain_t *domain )
{
   char *me = "dsrc";
   int isrc, i, ntimes, slen ;
   int *sndx ;
   double srct0, srctn, srcv0, srcvn, density ;
   double *srctime, *srcval ;
   FT_INITIALIZE(me, domain->hash)
   for ( isrc = 0 ; isrc < domain->nsrc ; isrc++ ) {
      if ( domain->src[isrc].type == DSRC1 ) {
         sndx    = domain->src[isrc].ndxsrc   ;
         slen    = domain->src[isrc].nzsrc    ;
         density = domain->src[isrc].fdat1[0] ;
         for ( i = 0 ; i < slen ; i++ ) {
	    den[sndx[i]] = density ;
	 }
      } else if ( domain->src[isrc].type == DSRC2 ) {
         sndx    = domain->src[isrc].ndxsrc   ;
         slen    = domain->src[isrc].nzsrc    ;
         ntimes  = domain->src[isrc].idat1[0] ;
         srctime = domain->src[isrc].dat2     ;
         srcval  = srctime + 1         ;
         srct0   = srctime[0] ;
         srctn   = srctime[2*(ntimes-1)] ;
         srcv0   = srcval[0] ;
         srcvn   = srcval[2*(ntimes-1)] ;
         if ( dtime <= srct0 ) {
            density = srcv0 ;
         } else if ( dtime >= srctn ) {
            density = srcvn ;
         } else {
	    for ( i = 2 ; i < 2*ntimes ; i += 2 ) {
               if ( dtime < srctime[i] )  break ;
	    }
            density = ( srcval[i-2] * ( srctime[i] - dtime )
                      + srcval[i]   * ( dtime - srctime[i-2] ) )
                      / ( srctime[i] - srctime[i-2] ) ;
         }
         for ( i = 0 ; i < slen ; i++ ) {
            den[sndx[i]] = density ;
	 }
      }
   }
   FT_FINALIZE(me, domain->hash, 1)
}
