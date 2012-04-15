#include "irs.h"
#include "irsedits.h"
#include "irsreg.h"
#include "ProblemArray.h"
int regedit( int stepflag )
{
   char *me = "regedit";
   char msg[256];   
   int iblk ;
   int ir ;
   char *dash = "-------------------------------------------------------------"
                "------------------" ;
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
   editor(stepflag);
   ctlmsg(dash);
   sprintf(msg,"Region edit:  Cycle: %i   Time step: %e", cycle,ttime) ;
   ctlmsg(msg);
   ctlmsg(dash);
 {       ctlmsg("              e              ke             ie           mass") ;
   }
   ctlmsg(dash);
   for ( ir = 1 ; ir <= nreg ; ir++ ) {
 { 
         sprintf(msg,"      %i  %13.6e  %13.6e  %13.6e  %13.6e",ir,
               regetot[ir],regke[ir],regie[ir],regmass[ir]);
         ctlmsg(msg);
      }
   }
   ctlmsg(dash);
 { 
      sprintf(msg,"Total    %13.6e  %13.6e  %13.6e  %13.6e",
                   etot, ketot, ietot, masstot ) ;
      ctlmsg(msg);
   }
   ctlmsg(dash);
   if ( (iftmode == 1) || ( iftion == 1) ) {
      ctlmsg("Average:      tmat           tion           trad            cve         cvi") ;
      ctlmsg(dash);
      for ( ir = 1 ; ir <= nreg ; ir++ ) {
         sprintf(msg,"      %i  %13.6e  %13.6e  %13.6e  %13.6e  %13.6e", ir,
                      tmatavg[ir], tionavg[ir], tradavg[ir],
                      cveavg[ir],  cviavg[ir] ) ;
         ctlmsg(msg);
      }
      ctlmsg(dash);
   }
   if  (ndims == 2 ) {
      ctlmsg("                   xmom         ymom");
      ctlmsg(dash);
      ctlmsg("  Reg:");
      for ( ir = 1 ; ir <= nreg ; ir++ ) {
         sprintf(msg,"      %i   Tot: %13.6e  %13.6e",ir,regxmom[ir],regymom[ir]);
         ctlmsg(msg);
         sprintf(msg,"          Pos: %13.6e  %13.6e",regxmomp[ir],regymomp[ir]);
         ctlmsg(msg);
         sprintf(msg,"          Neg: %13.6e  %13.6e",regxmomn[ir],regymomn[ir]);
         ctlmsg(msg);
      }   
      ctlmsg(dash);
      sprintf(msg, "Total          %13.6e  %13.6e", xmomtot,  ymomtot);
      ctlmsg(msg);
      sprintf(msg, "Total     Pos: %13.6e  %13.6e", xmomtotp, ymomtotp);
      ctlmsg(msg);
      sprintf(msg, "Total     Neg: %13.6e  %13.6e", xmomtotn, ymomtotn);
      ctlmsg(msg);
      ctlmsg(dash);
   } else {
      sprintf(msg,"                   xmom           ymom            zmom");
      ctlmsg(msg);
      ctlmsg(dash);
      ctlmsg("  Reg:");
      for ( ir = 1 ; ir <= nreg ; ir++ ) {
         sprintf(msg,"      %i   Tot: %13.6e  %13.6e  %13.6e",ir,
	      regxmom[ir],regymom[ir],regzmom[ir]);
         ctlmsg(msg);
         sprintf(msg,"          Pos: %13.6e  %13.6e  %13.6e",
	      regxmomp[ir],regymomp[ir],regzmomp[ir]);
         ctlmsg(msg);
         sprintf(msg,"          Neg: %13.6e  %13.6e  %13.6e",
	      regxmomn[ir],regymomn[ir],regzmomn[ir]);
         ctlmsg(msg);
      }
      ctlmsg(dash);
      sprintf(msg, "Total          %13.6e  %13.6e  %13.6e",
                     xmomtot, ymomtot, zmomtot ) ;
      ctlmsg(msg);
      sprintf(msg, "Total     Pos: %13.6e  %13.6e  %13.6e",
                     xmomtotp, ymomtotp, zmomtotp ) ;
      ctlmsg(msg);
      sprintf(msg, "Total     Neg: %13.6e  %13.6e  %13.6e",
                     xmomtotn, ymomtotn, zmomtotn ) ;
      ctlmsg(msg);
      ctlmsg(dash);
   }
   return(0);
}
