#include "irs.h"
#include "irssrc.h"
#include "irsbndry.h"
#include "irsblk.h"
#include "irsgen.h"
#include "irsreg.h"
#include "irsrgst.h"
#include "BlockMapping.h"
#include "Command.h"
#include "Source.h"
#include "Domain.h"
#include "Rgst.h"
#include "Region.h"
int blkgen( Domain_t *domain ) {
   int error, i, len, isrc, ivar, ir , j;
   int *ndx, *ndxmix, *grdmix ;
   double *var, t ;
   RGST_AttributeElem_t *func;
   error = 0 ;
   regndx(domain) ;
   domain->ndeltat = plarge ;
   if ( ifdynspec > 0 ) {
      for ( i = 0 ; i < domain->namix ; i++ ) {
         domain->specfrac[i].mass_frac = NULL ;
         ir = domain->ireg[i] ;
         if ( ir > 0 ) {
            len = reg[ir].nspec ;
            domain->specfrac[i].mass_frac = MALLOT(double,len) ;
            for ( j = 0 ; j < len ; j++) {
               domain->specfrac[i].mass_frac[j] = 
		 reg[ir].species[j].massFraction0 ;
            }
         }
      }
   } else {
   } 
   if ( iftion == 1 ) {
      for ( i = 0 ; i < domain->namix ; i++ ) {
	 if ( domain->tion[i] == ptiny ) {
            domain->tion[i] = domain->tmat[i] ;
         }
      }
   }
   if ( ngroup > 0 ) {
      for ( ir = 1 ; ir <= nreg ; ir++ ) {
         ndx = domain->rndx[ir] ;
         for ( i = 0 ; i < domain->rlen[ir] ; i++ ) {
            if ( domain->trad[ndx[i]] == ptiny ) {
               t = domain->tmat[ndx[i]] ;
            } else {
               t = domain->trad[ndx[i]] ;
            }
            domain->trad[ndx[i]] = t ;
            domain->erad[ndx[i]] = t * t * t * t ;
         }
      }
   }
   initbc(domain) ;
   if ( unblk > 1 ) {
   }
   genreflst(domain) ;
   if ( (ngroup > 0) || (ifedif == 1) || (ifidif == 1)  ) {
      genradreflst(domain) ;
   }
   for (i = 0; i < domain->nnalls; i++ ) {
      if (fabs(domain->xdot[i]) < ucut) domain->xdot[i] = 0.0;
      if (fabs(domain->ydot[i]) < ucut) domain->ydot[i] = 0.0;
      if ( ndims == 3 ) {
         if (fabs(domain->zdot[i]) < ucut) domain->zdot[i] = 0.0;
      }
   }
   if ( ndims == 2 ) {
      refnd2d( domain->x,    domain->y,    domain ) ;
      refnd2d( domain->xdot, domain->ydot, domain ) ;
         volcal2d( domain->vol, domain->area, domain->x, domain->y, domain ) ;
   } else if ( ndims == 3 ) {
      refnd3d( domain->x,    domain->y,    domain->z,    domain ) ;
      refnd3d( domain->xdot, domain->ydot, domain->zdot, domain ) ;
         volcal3d( domain->vol, domain->x, domain->y, domain->z, domain ) ;
   }
   ndx = domain->rndx[0] ;
   len = domain->rlen[0] ;
   for ( i = 0 ; i < len ; i++ ) {
      domain->zmass[ndx[i]] = 0.0 ;
      domain->ireg[ndx[i]]  = 0   ;
   }

   SourceNew_general(domain->xdot, domain->nmass, 
                        "SourceXVelocity", ttime, domain, _SourceNoEdit_);
   SourceNew_general(domains->ydot, domain->nmass,
                        "SourceYVelocity", ttime, domain, _SourceNoEdit_);
   if (ndims == 3) {
      SourceNew_general(domains->zdot, domains->nmass,
                        "SourceZVelocity", ttime, domain, _SourceNoEdit_);
   }
   if ( domain->nsrc > 0 ) {
      if ( domain->type == QUAD2D ) {
 ;       } else if ( domain->type == HEX3D ) {
 ;       }
   }
   func = rgst_list_attr(A_OBJECT, "Function_GenDomain");
   while (func != NULL) {
      Command_t *cp = (Command_t *) func->rgst_obj->obj;
      (*(cp->proc))(domain);
      func = func->next;
   }
   return(error) ;
}
