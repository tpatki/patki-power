#include "irs.h"
#include "irstdiff.h"
#include "irscom.h"
#include "irssrc.h"
#include "DiffusionData.h"
#include "FunctionTimer.h"
#include "RadiationData.h"
void rdiffsrc( DiffusionData_t *tblk, Domain_t *domain, double radtime )
{
   int isrc,irsrc,i ;
   int ntimes ;
   double *srctime,*srcval,srct0,srctn,srcv0,srcvn ;
   double tsrc,rsrc ;
   int *sndx,slen ;
   for ( isrc = 0 ; isrc < domain->nsrc ; isrc++ )
   {
      if ( domain->src[isrc].type == TSRC || domain->src[isrc].type == TSRCINT )
      {
         sndx    = domain->src[isrc].ndxsrc ;
         slen    = domain->src[isrc].nzsrc  ;
         ntimes  = domain->src[isrc].idat1[0] ;
         srctime = domain->src[isrc].dat2     ;
         srcval  = srctime + 1 ;
	 if ( domain->src[isrc].type == TSRCINT )
         {
	    irsrc  = domain->src[isrc].idat1[1] ;
	    ntimes = domain->src[isrc].idat1[0] ;
	    if ( irsrc > 0 ) 
            {
	       sndx = domain->rndx[irsrc] ;
	       slen = domain->rlencln[irsrc] ;
	    }
	 }
         srct0   = srctime[0] ;
         srctn   = srctime[2*(ntimes-1)] ;
         srcv0   = srcval[0] ;
         srcvn   = srcval[2*(ntimes-1)] ;
         if ( radtime <= srct0 )
            tsrc = srcv0 ;
         else if ( radtime >= srctn )
            tsrc = srcvn ;
         else
         {
            for ( i = 2 ; i < 2*ntimes ; i += 2 )
               if ( radtime < srctime[i] )  break ;
            tsrc = (srcval[i-2]*(srctime[i] - radtime)
                  +  srcval[i]*(radtime - srctime[i-2]))
                  / (srctime[i] - srctime[i-2]) ;
         }
         rsrc = tsrc*tsrc ;
         rsrc = rsrc*rsrc ;
         for ( i = 0 ; i < slen ; i++ )
	 {
            tblk->phi [sndx[i]] = rsrc ; 
            domain->trad[sndx[i]] = tsrc ; 
         }
      }
   }
}
