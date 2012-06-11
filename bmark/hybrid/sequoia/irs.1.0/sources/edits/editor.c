#include "irs.h"
#include "irsreg.h"
#include "irscom.h"
#include "irsedits.h"
#include "irsrgst.h"
#include "FunctionTimer.h"
#include "ProblemArray.h"
#include "Rgst.h"
#include "Source.h"
#include "Region.h"
int editor( int stepflag )
{
   char *name;
   int ir;
   int iblk;
   int len;
   int is;
   int i;
   double *buffer;
   RGST_AttributeElem_t *editvars;
   RGST_AttributeElem_t *editvars_ptr;
   double *regetot  = (double *) ProblemArray_ptr("regetot",     NULL);
   double *regke    = (double *) ProblemArray_ptr("regke",       NULL);
   double *regie    = (double *) ProblemArray_ptr("regie",       NULL);
   double *regpe    = (double *) ProblemArray_ptr("regpe",       NULL);
   double *regtke   = (double *) ProblemArray_ptr("regtke",      NULL);
   double *regmass  = (double *) ProblemArray_ptr("regmass",     NULL);
   double *regvol   = (double *) ProblemArray_ptr("regvol",      NULL);
   double *regxmom  = (double *) ProblemArray_ptr("regxmom",     NULL);
   double *regymom  = (double *) ProblemArray_ptr("regymom",     NULL);
   double *regzmom  = (double *) ProblemArray_ptr("regzmom",     NULL);
   double *regxmomp = (double *) ProblemArray_ptr("regxmomp",    NULL);
   double *regymomp = (double *) ProblemArray_ptr("regymomp",    NULL);
   double *regzmomp = (double *) ProblemArray_ptr("regzmomp",    NULL);
   double *regxmomn = (double *) ProblemArray_ptr("regxmomn",    NULL);
   double *regymomn = (double *) ProblemArray_ptr("regymomn",    NULL);
   double *regzmomn = (double *) ProblemArray_ptr("regzmomn",    NULL);
   double *tmatavg  = (double *) ProblemArray_ptr("regtmatavg",  NULL);
   double *tionavg  = (double *) ProblemArray_ptr("regtionavg",  NULL);
   double *tradavg  = (double *) ProblemArray_ptr("regtradavg",  NULL);
   double *cveavg   = (double *) ProblemArray_ptr("regcveavg",   NULL);
   double *cviavg   = (double *) ProblemArray_ptr("regcviavg",   NULL);
   double *regtne   = (double *) ProblemArray_ptr("regtnetot",   NULL);
   double *regdtne  = (double *) ProblemArray_ptr("regdtnetot",  NULL);
   double *regpartmass = (double *) ProblemArray_ptr("regpartmass", NULL);
   double *regpartke   = (double *) ProblemArray_ptr("regpartke", NULL);
   double *regpartdke  = (double *) ProblemArray_ptr("regpartdke", NULL);
   double *regpartnum  = (double *) ProblemArray_ptr("regpartnum", NULL);
   double *regpartnump = (double *) ProblemArray_ptr("regpartnump", NULL);  
   double *regpartxmom = (double *) ProblemArray_ptr("regpartxmom", NULL);  
   double *regpartymom = (double *) ProblemArray_ptr("regpartymom", NULL);  
   double *regpartzmom = (double *) ProblemArray_ptr("regpartzmom", NULL);  
   len = 0 ;
   for ( ir = 1 ; ir <= nreg ; ir++ ) {
      regetot[ir]    = 0.0; len++ ;
      regke[ir]      = 0.0; len++ ;
      regie[ir]      = 0.0; len++ ;
      regtke[ir]     = 0.0; len++ ;
      regpe[ir]      = 0.0; len++ ;
      regmass[ir]    = 0.0; len++ ;
      regvol[ir]     = 0.0; len++ ;
      regxmom[ir]    = 0.0; len++ ;
      regymom[ir]    = 0.0; len++ ;
      regzmom[ir]    = 0.0; len++ ;
      regxmomp[ir]   = 0.0; len++ ;
      regymomp[ir]   = 0.0; len++ ;
      regzmomp[ir]   = 0.0; len++ ;
      regxmomn[ir]   = 0.0; len++ ;
      regymomn[ir]   = 0.0; len++ ;
      regzmomn[ir]   = 0.0; len++ ;
      tmatavg[ir]    = 0.0; len++ ;
      tionavg[ir]    = 0.0; len++ ;
      tradavg[ir]    = 0.0; len++ ;
      cveavg[ir]     = 0.0; len++ ;
      cviavg[ir]     = 0.0; len++ ;
      regpartmass[ir]   = 0.0; len++ ;
      regpartke[ir]     = 0.0; len++ ;
      regpartdke[ir]    = 0.0; len++ ; 
      regpartnum[ir]    = 0.0; len++ ;
      regpartnump[ir]   = 0.0; len++ ;  
      regpartxmom[ir]   = 0.0; len++ ;  
      regpartymom[ir]   = 0.0; len++ ;  
      regpartzmom[ir]   = 0.0; len++ ;  
      for ( is = 0 ; is < reg[ir].nspec ; is++ ) {
         reg[ir].species[is].mass = 0.0 ; len++ ;
      }
      len++; 
   } 
   len += RGST_NUM_OBJECTS_WITH_ATTR("SourceList");
   for ( iblk = 0 ; iblk < nblk ; iblk++ ) {
      if ( ndims == 2 ) {
          regenrgy2d( domains[iblk].x,    domains[iblk].y, 
                      domains[iblk].xdot, domains[iblk].ydot, &domains[iblk] ) ;
      } else {
          regenrgy3d( domains[iblk].x,    domains[iblk].y,    domains[iblk].z, 
                      domains[iblk].xdot, domains[iblk].ydot, domains[iblk].zdot,
                      &domains[iblk] );
      }
   }
   for ( iblk = 0 ; iblk < nblk ; iblk++ ) {
      HashTable_t *hash = domains[iblk].hash;
      double *retot  = (double *) ProblemArray_ptr("regetot", hash);
      double *rke    = (double *) ProblemArray_ptr("regke",   hash);
      double *rie    = (double *) ProblemArray_ptr("regie",   hash);
      double *rpe    = (double *) ProblemArray_ptr("regpe",   hash);
      double *rtke   = (double *) ProblemArray_ptr("regtke",  hash);
      double *rmass  = (double *) ProblemArray_ptr("regmass", hash);
      double *rvol   = (double *) ProblemArray_ptr("regvol",  hash);
      double *rxmom  = (double *) ProblemArray_ptr("regxmom", hash);
      double *rymom  = (double *) ProblemArray_ptr("regymom", hash);
      double *rzmom  = (double *) ProblemArray_ptr("regzmom", hash);
      double *rxmomp = (double *) ProblemArray_ptr("regxmomp",hash);
      double *rymomp = (double *) ProblemArray_ptr("regymomp",hash);
      double *rzmomp = (double *) ProblemArray_ptr("regzmomp",hash);
      double *rxmomn = (double *) ProblemArray_ptr("regxmomn",hash);
      double *rymomn = (double *) ProblemArray_ptr("regymomn",hash);
      double *rzmomn = (double *) ProblemArray_ptr("regzmomn",hash);
      double *rtmatavg  = (double *) ProblemArray_ptr("regtmatavg",hash);
      double *rtionavg  = (double *) ProblemArray_ptr("regtionavg",hash);
      double *rtradavg  = (double *) ProblemArray_ptr("regtradavg",hash);
      double *rcveavg   = (double *) ProblemArray_ptr("regcveavg",hash);
      double *rcviavg   = (double *) ProblemArray_ptr("regcviavg",hash);
      double *rdtne     = (double *) ProblemArray_ptr("regdtnetot",hash);
      double *rpartms   = (double *) ProblemArray_ptr("regpartmass",hash);
      double *rpartke   = (double *) ProblemArray_ptr("regpartke",hash);
      double *rpartdke  = (double *) ProblemArray_ptr("regpartdke",hash);
      double *rpartnum  = (double *) ProblemArray_ptr("regpartnum",hash);
      double *rpartnmp  = (double *) ProblemArray_ptr("regpartnump",hash);
      double *rpartxmo  = (double *) ProblemArray_ptr("regpartxmom",hash);
      double *rpartymo  = (double *) ProblemArray_ptr("regpartymom",hash);
      double *rpartzmo  = (double *) ProblemArray_ptr("regpartzmom",hash);
      for ( ir = 1 ; ir <= nreg ; ir++ ) {
         regetot[ir]    += retot[ir]  ; 
         regke[ir]      += rke[ir]    ; 
         regie[ir]      += rie[ir]    ; 
         regtke[ir]     += rtke[ir]    ; 
         regpe[ir]      += rpe[ir]   ; 
         regmass[ir]    += rmass[ir]  ; 
         regvol[ir]     += rvol[ir]   ; 
         regxmom[ir]    += rxmom[ir]  ; 
         regymom[ir]    += rymom[ir]  ; 
         regzmom[ir]    += rzmom[ir]  ; 
         regxmomp[ir]   += rxmomp[ir] ; 
         regymomp[ir]   += rymomp[ir] ; 
         regzmomp[ir]   += rzmomp[ir] ; 
         regxmomn[ir]   += rxmomn[ir] ; 
         regymomn[ir]   += rymomn[ir] ; 
         regzmomn[ir]   += rzmomn[ir] ; 
         tmatavg[ir]    += rtmatavg[ir]  ; 
         tionavg[ir]    += rtionavg[ir]  ; 
         tradavg[ir]    += rtradavg[ir]  ; 
         cveavg[ir]     += rcveavg[ir]   ; 
         cviavg[ir]     += rcviavg[ir]   ; 
         regdtne[ir]    += rdtne[ir]     ; 
         regpartmass[ir]   += rpartms[ir] ;
         regpartke[ir]     += rpartke[ir] ;
         regpartdke[ir]    += rpartdke[ir] ;
         regpartnum[ir]    += rpartnum[ir] ;
         regpartnump[ir]   += rpartnmp[ir] ;
         regpartxmom[ir]   += rpartxmo[ir] ;
         regpartymom[ir]   += rpartymo[ir] ;
         regpartzmom[ir]   += rpartzmo[ir] ;
      }
   }
   SourceNew_sumedits();
   if (ifparallel) {
      buffer = ALLOT(double,len);
      len = 0 ;
      for ( ir = 1 ; ir <= nreg ; ir++ ) {
	 buffer[len++] = regetot[ir]    ;
	 buffer[len++] = regke[ir]      ;
	 buffer[len++] = regie[ir]      ;
	 buffer[len++] = regtke[ir]     ;
	 buffer[len++] = regpe[ir]      ;
	 buffer[len++] = regmass[ir]    ;
	 buffer[len++] = regvol[ir]     ;
	 buffer[len++] = regxmom[ir]    ;
	 buffer[len++] = regymom[ir]    ;
	 buffer[len++] = regzmom[ir]    ;
	 buffer[len++] = regxmomp[ir]   ;
	 buffer[len++] = regymomp[ir]   ;
	 buffer[len++] = regzmomp[ir]   ;
	 buffer[len++] = regxmomn[ir]   ;
	 buffer[len++] = regymomn[ir]   ;
	 buffer[len++] = regzmomn[ir]   ;
	 buffer[len++] = tmatavg[ir]    ;
	 buffer[len++] = tionavg[ir]    ;
	 buffer[len++] = tradavg[ir]    ;
	 buffer[len++] = cveavg[ir]     ;
	 buffer[len++] = cviavg[ir]     ;
	 buffer[len++] = regdtne[ir]    ;
         buffer[len++] = regpartmass[ir] ;
         buffer[len++] = regpartke[ir] ;
         buffer[len++] = regpartdke[ir] ;
         buffer[len++] = regpartnum[ir] ;
         buffer[len++] = regpartnump[ir] ;
         buffer[len++] = regpartxmom[ir] ;
         buffer[len++] = regpartymom[ir] ;
         buffer[len++] = regpartzmom[ir] ;
         for (is = 0; is < reg[ir].nspec; is++) {
            buffer[len++] = reg[ir].species[is].mass;
         }
      }
      SourceNew_packedit( buffer, &len);
      comreduce(buffer,len,COM_SUM,COM_ALL,COM_DOUBLE);
      len = 0 ;
      for ( ir = 1 ; ir <= nreg ; ir++ ) {
         regetot[ir]    = buffer[len++] ;
         regke[ir]      = buffer[len++] ;
         regie[ir]      = buffer[len++] ;
         regtke[ir]     = buffer[len++] ;
         regpe[ir]      = buffer[len++] ;
         regmass[ir]    = buffer[len++] ;
         regvol[ir]     = buffer[len++] ;
         regxmom[ir]    = buffer[len++] ;
         regymom[ir]    = buffer[len++] ;
         regzmom[ir]    = buffer[len++] ;
         regxmomp[ir]   = buffer[len++] ;
         regymomp[ir]   = buffer[len++] ;
         regzmomp[ir]   = buffer[len++] ;
         regxmomn[ir]   = buffer[len++] ;
         regymomn[ir]   = buffer[len++] ;
         regzmomn[ir]   = buffer[len++] ;
         tmatavg[ir]    = buffer[len++] ;
         tionavg[ir]    = buffer[len++] ;
         tradavg[ir]    = buffer[len++] ;
         cveavg[ir]     = buffer[len++] ;
         cviavg[ir]     = buffer[len++] ;
         regdtne[ir]    = buffer[len++] ;
         regpartmass[ir]   = buffer[len++] ;
         regpartke[ir]     = buffer[len++] ;
         regpartdke[ir]    = buffer[len++] ;
         regpartnum[ir]    = buffer[len++] ;
         regpartnump[ir]   = buffer[len++] ;
         regpartxmom[ir]   = buffer[len++] ;
         regpartymom[ir]   = buffer[len++] ;
         regpartzmom[ir]   = buffer[len++] ;
         for (is = 0; is < reg[ir].nspec; is++) {
            reg[ir].species[is].mass = buffer[len++];
         }
      }
      SourceNew_unpackedit(buffer, &len);
      FREEMEM(buffer) ;
   }
   etot      = 0.0 ;
   ketot     = 0.0 ;
   ietot     = 0.0 ;
   tketot    = 0.0 ;
   petot     = 0.0 ;
   masstot   = 0.0 ;
   volumetot = 0.0 ;
   xmomtot   = 0.0 ;
   ymomtot   = 0.0 ;
   zmomtot   = 0.0 ;
   xmomtotp  = 0.0 ;
   ymomtotp  = 0.0 ;
   zmomtotp  = 0.0 ;
   xmomtotn  = 0.0 ;
   ymomtotn  = 0.0 ;
   zmomtotn  = 0.0 ;
   dtnetot   = 0.0 ;
   for ( ir = 1 ; ir <= nreg ; ir++ ) {
      tmatavg[ir] /= ( cveavg[ir] + ptiny ) ;
      tionavg[ir] /= ( cviavg[ir] + ptiny ) ;
      cveavg[ir]  /= ( regmass[ir] + ptiny ) ;
      cviavg[ir]  /= ( regmass[ir] + ptiny ) ;
      tradavg[ir] /= ( regvol[ir] + ptiny ) ;
      tradavg[ir]  = MAX( tradavg[ir], 0.0 ) ;
      tradavg[ir]  = sqrt( sqrt( tradavg[ir] ) ) ;
      etot      += regetot[ir] ;
      ketot     += regke[ir] ;
      ietot     += regie[ir] ;
      tketot    += regtke[ir] ;
      petot     += regpe[ir] ;
      masstot   += regmass[ir] ;
      volumetot += regvol[ir] ;
      xmomtot   += regxmom[ir] ;
      ymomtot   += regymom[ir] ;
      zmomtot   += regzmom[ir] ;
      xmomtotp  += regxmomp[ir] ;
      ymomtotp  += regymomp[ir] ;
      zmomtotp  += regzmomp[ir] ;
      xmomtotn  += regxmomn[ir] ;
      ymomtotn  += regymomn[ir] ;
      zmomtotn  += regzmomn[ir] ;
      dtnetot   += regdtne[ir] ;
      tnetot    += regdtne[ir] ;
      regtne[ir]   += regdtne[ir];
      regdtne[ir]  = 0.;
   }
   return(0) ;
}
