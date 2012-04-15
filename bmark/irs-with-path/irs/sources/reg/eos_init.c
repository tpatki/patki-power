#include "irs.h"
#include "irsreg.h"
#include "irscom.h"
#include "irseos.h"
#include "irsparm.h"
#include "FunctionTimer.h"
#include "Hash.h"
int eos_init( int ifgen )
{
   char *me = "eos_init";
   char msg[256];
   int ir, i, jeos, multieos, error, *ndx, iblk ;
   int needpor, irestart, ndata ;
   double emin, emax ;
   double myflops = 1.0;
   int j, k ;
   int id ;
   
   int ifqeos ;
   double *fwork ;
   int    *iwork ;
   double z23, cs ;
   double twothirds = 2.0 / 3.0 ;
   FT_INITIALIZE(me, gv_hash_tbl)
   Region_check() ;
   error =  0 ;
   for ( ir = 1 ; ir <= nreg ; ir++ ) {
      i = -1 ;
      for ( jeos = 0 ; jeos < reg[ir].numGroups ; jeos++ ) {
	 if ( reg[ir].eosGroup[jeos].database.type == _Null_ ) {
            i = jeos ;
            break ;
	 }
      }
      if ( i != -1 ) {
         sprintf( msg, "EOS %d in region %d has not been defined.", i, ir ) ;
         ctlnotice( me, msg ) ;
         error = 1 ;
      }
   }
   EosGroup_check() ;

   if ( (ngroup == 1) ) {
      for ( ir = 1 ; ir <= nreg ; ir++ ) {
         i = -1 ;
         for ( jeos = 0 ; jeos < reg[ir].numGroups ; jeos++ ) {
	    if ( reg[ir].opacityGroup[jeos].rosTable.type == _Null_ ) {
               i = jeos ;
               break ;
	    }
         }
         if ( i != -1 ) {
            sprintf( msg, "Rosseland opacity %d in region %d has not been"
                          " defined.", i, ir ) ;
            ctlnotice( me, msg ) ;
            error = 1 ;
         }
      }
      for ( ir = 1 ; ir <= nreg ; ir++ ) {
         i = -1 ;
         for ( jeos = 0 ; jeos < reg[ir].numGroups ; jeos++ ) {
	    if ( reg[ir].opacityGroup[jeos].planckTable.type == _Null_ ) {
               i = jeos ;
               break ;
	    }
         }
         if ( i != -1 ) {
            sprintf( msg, "Planck opacity %d in region %d has not been"
                          " defined.", i, ir ) ;
            ctlnotice( me, msg ) ;
            error = 1 ;
         }
      }
   }
   if ( (ifgen == 1) && ((ngroup == 1) ) ) {
      for ( ir = 1 ; ir <= nreg ; ir++ ) {
         for ( jeos = 0 ; jeos < reg[ir].numGroups ; jeos++ ) {
	    if ( reg[ir].opacityGroup[jeos].planckTable.form < 0 ) {
                  reg[ir].opacityGroup[jeos].planckTable.form = 2 ;
	    }
	 }
      }
   }
   if ( (ifgen == 1) && (ioneq == 1) ) {
      for ( ir = 1 ; ir <= nreg ; ir++ ) {
         for ( jeos = 0 ; jeos < reg[ir].numGroups ; jeos++ ) {
            if ( (ngroup == 1) && 
                 (reg[ir].opacityGroup[jeos].planckTable.form == 2) ) {
               reg[ir].ioneq = 1 ;
	    }
	 }
      }
   }
   for ( ir = 1 ; ir <= nreg ; ir++ ) {
      multieos = 0 ;
      for ( jeos = 0 ; jeos < reg[ir].numGroups ; jeos++ ) {
         if ( reg[ir].eosGroup[jeos].database.form == 4 ) {
 ;          }
      }
   }
   if ( ZERO == 0 ) {
      needpor = 0 ;
      for ( ir = 1 ; ir <= nreg ; ir++ ) {
	 for ( jeos = 0 ; jeos < reg[ir].numGroups ; jeos++ ) {
            if ( reg[ir].eosGroup[jeos].database.form == 20 ) {
               needpor = 20 ;
               break ;
            } else if ( reg[ir].eosGroup[jeos].database.form == 12 ) {
               needpor = 12 ;
               break ;
            } else if ( reg[ir].eosGroup[jeos].database.form == 13 ) {
               needpor = 13 ;
               break ;
            }
	 }
         if ( needpor != 0 ) break ;
      }
      if ( needpor != 0 ) {
         sprintf( msg, "EOS form %d in region %d ",
                       needpor, ir ) ;
         ctlnotice( me, msg ) ;
         error = 1 ;
      }
   }
   if ( ifgen == 1 ) {
      for ( ir = 1 ; ir <= nreg ; ir++ ) {
         if ( reg[ir].burn == 0 ) continue ;
         if ( (reg[ir].eosGroup[0].database.form ==   1) ||
              (reg[ir].eosGroup[0].database.form == 101)  ) {
            emin =  plarge ;
            emax = -plarge ;
            for ( iblk = 0 ; iblk < nblk ; iblk++ ) {
               ndx = domains[iblk].rndx[ir] ;
               for ( i = 0 ; i < domains[iblk].rlen[ir] ; i++ ) {
                  emin = MIN( emin, domains[iblk].tmat[ndx[i]] ) ;
                  emax = MAX( emax, domains[iblk].tmat[ndx[i]] ) ;
	       }
	    }
	    if (ifparallel) {
	       comreduce(&emin, 1, COM_MIN, COM_ALL, COM_DOUBLE);
	       comreduce(&emax, 1, COM_MAX, COM_ALL, COM_DOUBLE);
	    }
            if ( fabs((emax - emin)/(0.5*(emax + emin) + ptiny)) > 0.01 ) {
               sprintf(msg,"\n\tInitial tmat for region %d JWL EOS %d %e %e"
                           "\n\tinside of Huygens source region not"
                           " constant", ir,
                           reg[ir].eosGroup[0].database.number,emin,emax) ;
               ctlwarning( me, msg ) ;
	    }
 ; 	 }
      }
   }
   ifqeos = 0 ;
   for ( ir = 1 ; ir <= nreg ; ir++ ) {
      for ( jeos = 0 ; jeos < reg[ir].numGroups ; jeos++ ) {
         double d0, e0, p0, t0, z0, dedt0, dpdt0, dpdr0 ;
         if ( (reg[ir].eosGroup[jeos].database.form == 111) || 
              (reg[ir].eosGroup[jeos].database.form == 311)  ) {
            ndata = reg[ir].eosGroup[jeos].database.ndata ;
            if ( reg[ir].eosGroup[jeos].database.data[ndata-1] == -1.0 ) {
               reg[ir].eosGroup[jeos].database.data[ndata-1] = 0.0 ;
               if ( ifqeos == 0 ) {
                    fwork = ALLOT(double,10773) ;
                  iwork = ALLOT(int,513) ;
                  ifqeos = 1 ;
               }
               d0  = reg[ir].eosGroup[jeos].refd ;
               t0  = reg[ir].eosGroup[jeos].database.data[1] ;
               j   = 1 ;
               z23 = pow( reg[ir].eosGroup[jeos].zbar, twothirds ) ;
               cs = reg[ir].eosGroup[jeos].database.data[0] ;
                 dpdt0 = 1; dedt0 = 1; p0 = 1; e0 = 1;
               dpdr0 += t0 * dpdt0 * dpdt0 / ( d0 * d0 * dedt0 ) ;
               reg[ir].eosGroup[jeos].database.data[0] =
                       reg[ir].eosGroup[jeos].refd * ( dpdr0 - cs * cs ) ;
               reg[ir].eosGroup[jeos].database.data[1] =
                       p0 - reg[ir].eosGroup[jeos].database.data[2] ;
               reg[ir].eosGroup[jeos].database.data[2] = e0 ;
            }
         }
         if ( (reg[ir].eosGroup[jeos].database.form == 211) ||
              (reg[ir].eosGroup[jeos].database.form == 321)  ) {
            ndata = reg[ir].eosGroup[jeos].database.ndata ;
            if ( reg[ir].eosGroup[jeos].database.data[ndata-1] == -1.0 ) {
               reg[ir].eosGroup[jeos].database.data[ndata-1] = 0.0 ;
               if ( ifqeos == 0 ) {
                    fwork = ALLOT(double,10773) ;
                  iwork = ALLOT(int,513) ;
                  ifqeos = 1 ;
               }
  	    }
         }
      }
   }
   if ( ifqeos ) {
      FREEMEM(fwork) ;
      FREEMEM(iwork) ;
   }
   irestart = 0 ;
   for ( ir = 1 ; ir <= nreg ; ir++ ) {
      for ( jeos = 0 ; jeos < reg[ir].numGroups ; jeos++ ) {
      }
      if ( irestart == 1 ) break ;
   }
   if ( ifgen == 1 ) {
      irestart = 0 ;
   }
   for ( ir = 1 ; ir <= nreg ; ir++ ) {
      if ( reg[ir].nspec > 0 ) {
         for ( jeos = 0 ; jeos < reg[ir].numGroups ; jeos++ ) {
	    int numspec   = reg[ir].eosGroup[jeos].numSpeciesInGroup ;
            int *speclist = reg[ir].eosGroup[jeos].speclist ;
            double fsum   = 0.0 ;
	    double asum   = 0.0 ;
            double zsum   = 0.0 ;
            for ( i = 0 ; i < numspec ; i++ ) {
	       int    index        = speclist[i] ;
               double abar         = reg[ir].species[index].abar ;
               double zbar         = reg[ir].species[index].zbar ;
               double atomfraction = reg[ir].species[index].atomFraction0 ;
	       asum += atomfraction * abar ;
               zsum += atomfraction * zbar ;
               fsum += atomfraction ;
	    }
            fsum += ptiny ;
            reg[ir].eosGroup[jeos].abar = asum / fsum ;
            reg[ir].eosGroup[jeos].zbar = zsum / fsum ;
	 }
      }
   }
   for ( ir = 1 ; ir <= nreg ; ir++ ) {
      for ( jeos = 0 ; jeos < reg[ir].numGroups ; jeos++ ) {
         if ( reg[ir].eosGroup[jeos].database.refd == -1.0 ) 
              reg[ir].eosGroup[jeos].database.refd =
              reg[ir].eosGroup[jeos].refd ;
         if ( reg[ir].eosGroup[jeos].database.abar == -1.0 ) 
              reg[ir].eosGroup[jeos].database.abar =
              reg[ir].eosGroup[jeos].abar ;
         if ( reg[ir].eosGroup[jeos].database.zbar == -1.0 ) 
              reg[ir].eosGroup[jeos].database.zbar =
              reg[ir].eosGroup[jeos].zbar ;
         if ( reg[ir].eosGroup[jeos].refd == -1.0 ) 
              reg[ir].eosGroup[jeos].refd =
              reg[ir].eosGroup[jeos].database.refd ;
         if ( reg[ir].eosGroup[jeos].abar == -1.0 ) 
              reg[ir].eosGroup[jeos].abar =
              reg[ir].eosGroup[jeos].database.abar ;
         if ( reg[ir].eosGroup[jeos].zbar == -1.0 ) 
              reg[ir].eosGroup[jeos].zbar =
              reg[ir].eosGroup[jeos].database.zbar ;
         if ( (ngroup == 1) ) {
            if ( reg[ir].opacityGroup[jeos].planckTable.refd == -1.0 ) 
                 reg[ir].opacityGroup[jeos].planckTable.refd =
                 reg[ir].eosGroup[jeos].database.refd ;
            if ( reg[ir].opacityGroup[jeos].planckTable.abar == -1.0 ) 
                 reg[ir].opacityGroup[jeos].planckTable.abar =
                 reg[ir].eosGroup[jeos].database.abar ;
            if ( reg[ir].opacityGroup[jeos].planckTable.zbar == -1.0 ) 
                 reg[ir].opacityGroup[jeos].planckTable.zbar =
                 reg[ir].eosGroup[jeos].database.zbar ;
            if ( reg[ir].opacityGroup[jeos].rosTable.refd == -1.0 ) 
                 reg[ir].opacityGroup[jeos].rosTable.refd =
                 reg[ir].eosGroup[jeos].database.refd ;
            if ( reg[ir].opacityGroup[jeos].rosTable.abar == -1.0 ) 
                 reg[ir].opacityGroup[jeos].rosTable.abar =
                 reg[ir].eosGroup[jeos].database.abar ;
            if ( reg[ir].opacityGroup[jeos].rosTable.zbar == -1.0 ) 
                 reg[ir].opacityGroup[jeos].rosTable.zbar =
                 reg[ir].eosGroup[jeos].database.zbar ;
         }
      }
   }
   for ( ir = 1 ; ir <= nreg ; ir++ ) {
      for ( jeos = 0 ; jeos < reg[ir].numGroups ; jeos++ ) {
         if ( reg[ir].eosGroup[jeos].refd == -1.0 ) {
            error = 1 ;
            sprintf( msg, "REFD not set in eos %d region %d.", jeos, ir ) ;
            ctlwarning( me, msg ) ;
         }
      }
   }
   if ( (iftmode == 1) || (iftion == 1) ) {
      for ( ir = 1 ; ir <= nreg ; ir++ ) {
         for ( jeos = 0 ; jeos < reg[ir].numGroups ; jeos++ ) {
            if ( reg[ir].eosGroup[jeos].abar == -1.0 ) {
               error = 1 ;
               sprintf( msg, "ABAR not set in eos %d region %d.", jeos, ir ) ;
               ctlwarning( me, msg ) ;
            }
	 }
      }
      for ( ir = 1 ; ir <= nreg ; ir++ ) {
         for ( jeos = 0 ; jeos < reg[ir].numGroups ; jeos++ ) {
            if ( reg[ir].eosGroup[jeos].zbar == -1.0 ) {
               error = 1 ;
               sprintf( msg, "ZBAR not set in eos %d region %d.", jeos, ir ) ;
               ctlwarning( me, msg ) ;
            }
	 }
      }
   }
   if ( ifgen == 1) {
      for ( ir = 1 ; ir <= nreg ; ir++ ) {
         if ( (reg[ir].eosGroup[0].database.form == 13) &&
              (reg[ir].eosGroup[1].database.form ==  0)  ) {
            sprintf(msg,"reg %d eos %d form 13 finding crush curve",
                    ir, reg[ir].eosGroup[0].database.number ) ;
            ctlwarning( me, msg ) ;
            i = reg[ir].eosGroup[1].database.ndata / 2 ;
            i = 2 * i - reg[ir].eosGroup[1].database.ndata ;
            if ( i != 0 ) {
               sprintf(msg,
                       "number of crush points for reg %d eos %d is not even",
                       ir, reg[ir].eosGroup[1].database.number ) ;
               ctlwarning( me, msg ) ;
            } else {
 ; 
            }
         }
      }
   }
   if ( ifgen == 1)  
     {
       for ( ir = 1 ; ir <= nreg ; ir++ ) 
	 {
	 }
     }
   if ( ifgen == 1)  
     {
       for ( ir = 1 ; ir <= nreg ; ir++ ) 
	 {
	   if (reg[ir].eosGroup[0].database.form == 17) 
	     {
		
		 {
		   sprintf(msg,
			   "\n\tAnalytic JWL++ Version");
		   ctlmsg( msg ) ;
		   sprintf(msg,
			   "\nap=%12.5e bp=%12.5e r1p=%12.5e r2p=%12.5e\n"
			   "                wp=%12.5e cp=%12.5e",
			   reg[ir].eosGroup[0].database.data[0], 
			   reg[ir].eosGroup[0].database.data[1], 
			   reg[ir].eosGroup[0].database.data[2],
			   reg[ir].eosGroup[0].database.data[3], 
			   reg[ir].eosGroup[0].database.data[4], 
			   reg[ir].eosGroup[0].database.data[5] ) ;
		   ctlmsg( msg ) ;
		   sprintf(msg,
			   "nr=%12.5e kappar=%12.5e",
			   reg[ir].eosGroup[0].database.data[6], 
			   reg[ir].eosGroup[0].database.data[7] ) ;
		   ctlmsg( msg ) ;
		 }
	       sprintf(msg,
		       "Q  =%12.5e M   =%12.5e",
		       reg[ir].eosGroup[0].database.data[8], 
		       reg[ir].eosGroup[0].database.data[14] ) ;
	       ctlmsg( msg ) ;
	       sprintf(msg,
		       "G1 =%12.5e MP1 =%12.5e F2 =%12.5e\n"
		       "G2 =%12.5e MP2 =%12.5e\n",
		       reg[ir].eosGroup[0].database.data[9],
		       reg[ir].eosGroup[0].database.data[10],
		       reg[ir].eosGroup[0].database.data[11],
		       reg[ir].eosGroup[0].database.data[12],
		       reg[ir].eosGroup[0].database.data[13] ) ;
	       ctlmsg( msg ) ;
	     }
	 }
     }
   if ( ifgen == 1)  
     {
       for ( ir = 1 ; ir <= nreg ; ir++ ) 
	 {
	   if (reg[ir].eosGroup[0].database.form == 19) 
	     {
	       if( ifdynspec != 1 )
		 {
		   sprintf(msg,"ifdynspec must be set to 1 run run JWL++ two rate model\n") ;
		   ctlerror( me, msg) ;
		 }
	       sprintf(msg,"\n\treg %d eos %d form 19 (JWL++ two rate model)",
		       ir, reg[ir].eosGroup[0].database.number ) ;
	       ctlmsg( msg ) ;
	       sprintf(msg,
		       "\nFR=%12.5e",
		       reg[ir].eosGroup[0].database.data[0] ) ;
	       ctlmsg( msg ) ;
	       sprintf(msg,
		       "\nA=%12.5e B= %12.5e C=  %12.5e R1=%12.5e R2=%12.5e\n"
		       "W=%12.5e E0=%12.5e BHE=%12.5e",
		       reg[ir].eosGroup[0].database.data[1], 
		       reg[ir].eosGroup[0].database.data[2], 
		       reg[ir].eosGroup[0].database.data[3],
		       reg[ir].eosGroup[0].database.data[4], 
		       reg[ir].eosGroup[0].database.data[5], 
		       reg[ir].eosGroup[0].database.data[6], 
		       reg[ir].eosGroup[0].database.data[7], 
		       reg[ir].eosGroup[0].database.data[8] ) ;
	       ctlmsg( msg ) ;
	       sprintf(msg,
		       "\nnr=%12.5e kappar=%12.5e",
		       reg[ir].eosGroup[0].database.data[9], 
		       reg[ir].eosGroup[0].database.data[10] ) ;
	       ctlmsg( msg ) ;
	       sprintf(msg,
		       "Pi      =%12.5e",
		       reg[ir].eosGroup[0].database.data[11] ) ;
	       ctlmsg( msg ) ;
	       sprintf(msg,
		       "\nG1 =%12.5e MP1 =%12.5e\n"
		       "G2 =%12.5e MP2 =%12.5e\n",
		       reg[ir].eosGroup[0].database.data[12],
		       reg[ir].eosGroup[0].database.data[13],
		       reg[ir].eosGroup[0].database.data[14],
		       reg[ir].eosGroup[0].database.data[15] ) ;
	       ctlmsg( msg ) ;
	       sprintf(msg,
		       "AR19=%12.5e VR19=%12.5e\n",
		       reg[ir].eosGroup[0].database.data[16],
		       reg[ir].eosGroup[0].database.data[17] ) ;
	       ctlmsg( msg ) ;
 ; 	     }
	 }
     }
  FT_FINALIZE(me, gv_hash_tbl, myflops) 
   return(error) ;
}
