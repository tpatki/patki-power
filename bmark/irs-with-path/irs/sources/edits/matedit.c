#include "irs.h"
#include "irsedits.h"
#include "irseos.h"
#include "irsreg.h"
#include "Region.h"
int matedit( void ) 
{
   char *me = "matedit";
   char msg[256];
   int i, ir, count, ie ;
   ctlmsg("-------------------------------------------------------------------------------"); 
   sprintf(msg,"Material edit:  Cycle: %i   Time step: %e",cycle,ttime);
   ctlmsg(msg);
   ctlmsg("-------------------------------------------------------------------------------"); 
   for ( ir = 1 ; ir <= nreg ; ir++ ) {
      for ( ie = 0 ; ie < reg[ir].numGroups ; ie++ ) {
         sprintf( msg,"Region: %i   EOS: %i   ",
                  ir, reg[ir].eosGroup[ie].database.number ) ;
         ctlmsg(msg) ;
         sprintf( msg,"   EOS form: %i   refd: %3.6f  etamin: %.6e   etamax: %.6e",
                  reg[ir].eosGroup[ie].database.form, reg[ir].eosGroup[ie].refd,
                  reg[ir].eosGroup[ie].etamin, reg[ir].eosGroup[ie].etamax ) ;    
         ctlmsg(msg) ;
         sprintf( msg,"   bhe: %3.6f   e0: %3.6f",
                  reg[ir].bhe, reg[ir].eosGroup[ie].e0 ) ;
         ctlmsg(msg) ;
         sprintf(msg,"   EOS coefficients:");
         ctlmsg(msg);
         sprintf(msg,"      ");
         ctlmsg1(msg);
         count = 0 ;
         for ( i = 0 ; i < reg[ir].eosGroup[ie].database.ndata ; i++ ) {
            sprintf(msg,"%0.6e  ",reg[ir].eosGroup[ie].database.data[i]);
            ctlmsg1(msg);
            count++ ;
            if ( count > 4 ) {
               count = 0 ;
               ctlmsg1("\n      ");
            }
         }
         ctlmsg1("\n");
         if (reg[ir].str > 0) {
            ctlmsg("   Strength Parameters:\n");
            sprintf(msg,"      str: %i          cmu: %3.6f        y: %3.6f",
                    reg[ir].str, reg[ir].stress->cmu, reg[ir].stress->y ) ;
            ctlmsg(msg) ;
            sprintf( msg,"       au: %3.6f    bu: %0.6e   ye: %3.6f     yp: %0.6e",
                     reg[ir].stress->au, reg[ir].stress->bu, reg[ir].stress->ye,
                     reg[ir].stress->yp ) ;
            ctlmsg(msg) ;
            sprintf( msg,"     gam0: %3.6f    yb: %3.6f      yc: %3.6f  ywhmx: %3.6f",
                     reg[ir].stress->gam0, reg[ir].stress->yb, reg[ir].stress->yc,
                     reg[ir].stress->ywhmx ) ;
            ctlmsg(msg) ;
            sprintf( msg,"      ayz: %4.3f    gzyz: %5.3f         wyz: %5.3f      tmyz: %7.2f",
                     reg[ir].stress->ayz, reg[ir].stress->gzyz, reg[ir].stress->wyz,
                     reg[ir].stress->tmyz ) ;
            ctlmsg(msg) ;
            sprintf(msg,"      ecxfit: ") ;
            ctlmsg(msg) ;
            sprintf( msg,"         %2.6e %2.6e %2.6e %2.6e",
                     reg[ir].stress->ecxfit[0], reg[ir].stress->ecxfit[1],
                     reg[ir].stress->ecxfit[2], reg[ir].stress->ecxfit[3] ) ;
            ctlmsg(msg) ;
            sprintf( msg,"         %2.6e %2.6e %2.6e %2.6e",
                     reg[ir].stress->ecxfit[4], reg[ir].stress->ecxfit[5],
                     reg[ir].stress->ecxfit[6], reg[ir].stress->ecxfit[7] ) ;
            ctlmsg(msg) ;
            sprintf( msg,"         %2.6e %2.6e ",
                     reg[ir].stress->ecxfit[8], reg[ir].stress->ecxfit[9] ) ;
            ctlmsg(msg) ;
            sprintf(msg,"      emxfit: ") ;
            ctlmsg(msg) ;
            sprintf( msg,"         %2.6e %2.6e %2.6e %2.6e",
                     reg[ir].stress->emxfit[0], reg[ir].stress->emxfit[1],
                     reg[ir].stress->emxfit[2], reg[ir].stress->emxfit[3] ) ;
            ctlmsg(msg) ;
            sprintf( msg,"         %2.6e %2.6e %2.6e %2.6e",
                     reg[ir].stress->emxfit[4], reg[ir].stress->emxfit[5],
                     reg[ir].stress->emxfit[6], reg[ir].stress->emxfit[7] ) ;
            ctlmsg(msg) ;
            sprintf( msg,"         %2.6e %2.6e ",
                     reg[ir].stress->emxfit[8], reg[ir].stress->emxfit[9] ) ;
            ctlmsg(msg) ;
         }
         ctlmsg("");	
      }
   }
   ctlmsg("-------------------------------------------------------------------------------"); 
   return(0);
}
