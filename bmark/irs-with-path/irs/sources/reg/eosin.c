#include "irs.h"
#include "irsreg.h"
#include "irseos.h"
int eosin( void )
{
   char *me = "eosin";
   char *errmsg_ngroupx_exceeded = "\n\tcurrent_eos exceeds ngroupx"
                                   "\n\tHave programmer increase ngroupx";
   char msg[128];
   int eosnum, eosfm, cflag, error = 0;
   int i, ir, ieos, ieosx, ispec, opfg, number;
   char regop[MAXWORD], newcolr[MAXWORD] ;
   char label[MAXWORD] ;
   Database_t *database ;
   current_eos++ ;
   if (current_eos >= ngroupx) ctlerror(me,errmsg_ngroupx_exceeded);
   ir   = current_region ;
   ieos = current_eos    ;
   reg[ir].numGroups++ ;
   database = &reg[ir].eosGroup[ieos].database ;
   opfg  =  1 ;
   while ( opfg == 1 ) {
      peekc(regop) ;
      if ( !strcmp(regop,"analytic") ) {
         geta(regop) ;
         database->type = _Analytic_ ;
         eosnum = geti(&cflag) ;
         database->number = eosnum ;
      } else if ( !strcmp(regop,"form") ) {
         geta(regop) ;
         database->type = _Form_ ;
         eosnum = 0 ;
         eosfm  = geti(&cflag) ;
         database->number = eosnum ;
         database->form   = eosfm  ;
         error = eosin0( eosnum, eosfm ) ;
      } else if ( !strcmp(regop,"table") ) {
         geta(regop) ;
         database->type = _Table_ ;
         strcpy(database->name, regop); 
      } else if ( !strcmp(regop,"e0") ) {
         geta(regop) ;
         reg[ir].eosGroup[ieos].e0 = getf(&cflag) ;
      } else if ( !strcmp(regop,"refd") ) {
         geta(regop) ;
         reg[ir].eosGroup[ieos].refd = getf(&cflag) ;
      } else if ( !strcmp(regop,"etamax") ) {
         geta(regop) ;
         reg[ir].eosGroup[ieos].etamax = getf(&cflag) ;
      } else if ( !strcmp(regop,"etamin") ) {
         geta(regop) ;
         reg[ir].eosGroup[ieos].etamin = getf(&cflag) ;
      } else if ( !strcmp(regop,"abar") ) {
         geta(regop) ;
         reg[ir].eosGroup[ieos].abar = getf(&cflag) ;
      } else if ( !strcmp(regop,"zbar") ) {
         geta(regop) ;
         reg[ir].eosGroup[ieos].zbar = getf(&cflag) ;
      } else if ( !strcmp(regop,"dmlt") ) {
         geta(regop) ;
         reg[ir].eosGroup[ieos].densityMultiplier = getf(&cflag) ;
      } else if ( !strcmp(regop,"emlt") ) {
         geta(regop) ;
         reg[ir].eosGroup[ieos].energyMultiplier = getf(&cflag) ;
      } else if ( !strcmp(regop,"eimlt") ) {
         geta(regop) ;
         reg[ir].eosGroup[ieos].ion_energyMultiplier = getf(&cflag) ;
      } else if ( !strcmp(regop,"pmlt") ) {
         geta(regop) ;
         reg[ir].eosGroup[ieos].pressureMultiplier = getf(&cflag) ;
      } else if ( !strcmp(regop,"pimlt") ) {
         geta(regop) ;
         reg[ir].eosGroup[ieos].ion_pressureMultiplier = getf(&cflag) ;
      } else if ( !strcmp(regop,"eicouplemlt") ) {
         geta(regop) ;
         reg[ir].eosGroup[ieos].eicoupleMultiplier = getf(&cflag) ;
      } else if ( !strcmp(regop,"zstarform") ) {
         geta(regop) ;
         reg[ir].eosGroup[ieos].zstarform = geti(&cflag) ;
      } else if ( !strcmp(regop,"econform") ) {
         geta(regop) ;
         reg[ir].eosGroup[ieos].econform = geti(&cflag) ;
	 if ( reg[ir].eosGroup[ieos].econform < 3 ) {
            reg[ir].eosGroup[ieos].econvalue = getf(&cflag) ;
	 }
      } else if ( !strcmp(regop,"iconform") ) {
         geta(regop) ;
         reg[ir].eosGroup[ieos].iconform = geti(&cflag) ;
	 if ( reg[ir].eosGroup[ieos].iconform < 3 ) {
            reg[ir].eosGroup[ieos].iconvalue = getf(&cflag) ;
	 }
      } else if ( !strcmp(regop,"species") ) {
         geta(regop);
	 error = species_input(ir);
	 if ( error != 0 ) {
	    return(error);
	 }
	 reg[ir].type = _Static_; 
	 if (ifdynspec) reg[ir].type = _Dynamic_; 
	 ispec = reg[ir].nspec;
	 number = reg[ir].eosGroup[ieos].numSpeciesInGroup;
	 reg[ir].eosGroup[ieos].speclist = 
	          REALLOT(reg[ir].eosGroup[ieos].speclist, int, number + 1);
	 reg[ir].eosGroup[ieos].speclist[number]      = ispec - 1;
         reg[ir].eosGroup[ieos].numSpeciesInGroup++;
	 number = reg[ir].opacityGroup[ieos].numSpeciesInGroup;
	 reg[ir].opacityGroup[ieos].speclist = 
	          REALLOT(reg[ir].opacityGroup[ieos].speclist, int, number + 1);
	 reg[ir].opacityGroup[ieos].speclist[number]      = ispec - 1;
         reg[ir].opacityGroup[ieos].numSpeciesInGroup++;
      } else {
         opfg = 0 ;
      }
   }
   return(error) ;
}
