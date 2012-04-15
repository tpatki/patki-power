#include "irs.h"
#include "irssys.h"
#include "irscom.h"
#include "irsdefs.h"
#include "irstdiff.h"
#include "DiffusionData.h"
#include "FunctionTimer.h"
#include "RadiationData.h"
#include "TimeStepControl.h"
static void MatrixSolveCG( RadiationData_t *rblk, RadiationData_t *cblk,
                           DiffusionData_t *tblk, double eps, int maxit,
                           int *iterations, double *error ) ;
static void MatrixSolvePC2D( RadiationData_t *cblk, RadiationData_t *rblk,
                             Domain_t *domain ) ;
static void MatrixSolvePC3D( RadiationData_t *cblk, RadiationData_t *rblk,
                             Domain_t *domain ) ;
void MatrixSolveDriver( RadiationData_t *rblk, RadiationData_t *cblk, 
	                DiffusionData_t *tblk, Domain_t *domains,
                        int *iterations, double *error )
{
   char *me = "MatrixSolveDriver";
   int iblk             ;
   int comerr  = 0      ;
   int my_nblk = nblk   ;
   double myflops = 0.0 ;
   FT_INITIALIZE(me, gv_hash_tbl)
   if ( solver == 1 ) {
   } else {
      if ( ifprecon == 0 ) {
#include "pardo.h"
         for ( iblk = 0 ; iblk < my_nblk ; iblk++ ) {
            int i ;
            for ( i = domains[iblk].frz ; i <= domains[iblk].lrz ; i++ ) {
               cblk[iblk].ccc[i] = 1.0 ;
            }
         }
      }
      if ( ifprecon > 0 ) {
#include "pardo.h"
         for ( iblk = 0 ; iblk < my_nblk ; iblk++ ) {
            int i ;
            for ( i = domains[iblk].frz ; i <= domains[iblk].lrz ; i++ ) {
               cblk[iblk].ccc[i] = 1.0 / ( rblk[iblk].ccc[i] + ptiny ) ; 
            }
            myflops += 5.0 * ( domains[iblk].lrz - domains[iblk].frz + 1 ) ;
         }
      }
      comerr += rbndcom(RBNDCOM6,COM_RECV,0) ;
      comerr += rbndcom(RBNDCOM6,COM_SEND,0) ;
      comerr += rbndcom(RBNDCOM6,COM_WAIT_RECV,0) ;
      comerr += rbndcom(RBNDCOM6,COM_WAIT_SEND,0) ;
#include "pardo.h"
      for ( iblk = 0 ; iblk < my_nblk ; iblk++ ) {
      }
      if ( ifprecon >= 2 ) {
         if ( ndims == 2 ) {
#include "pardo.h"
            for ( iblk = 0 ; iblk < my_nblk ; iblk++ ) {
               MatrixSolvePC2D( &cblk[iblk], &rblk[iblk], &domains[iblk] ) ;
	    }
         }
         if ( ndims == 3 ) {
#include "pardo.h"
            for ( iblk = 0 ; iblk < my_nblk ; iblk++ ) {
               MatrixSolvePC3D( &cblk[iblk], &rblk[iblk], &domains[iblk] ) ;
	    }
         }
      }
      if ( ifprecon > 1 ) {
#include "pardo.h"
         for ( iblk = 0 ; iblk < my_nblk ; iblk++ ) {
            cblkbc( &cblk[iblk], &domains[iblk] ) ;
         }
      }
      MatrixSolveCG( rblk, cblk, tblk, rdifepsx, rdifitx, iterations, error ) ;
   }
   FT_FINALIZE(me, gv_hash_tbl, myflops)
}
static void MatrixSolveCG( RadiationData_t *rblk, RadiationData_t *cblk,
                           DiffusionData_t *tblk, double eps, int maxit,
                           int *iterations, double *error )
{
   char *me = "MatrixSolveCG";
   int iter,  iblk, comerr;
   int my_nblk = nblk ;
   double cgsums[4] ;
   double dotp, dotprev, dotrz ;
   double alpha, beta ;
   double normx, normp, normr, normrhs ;
   double rerr, xerr ;
   double **x, **b, **p, **r, **t, **z ;
   double myflops = 0.0;
   FT_INITIALIZE(me, gv_hash_tbl)
   comerr = 0 ;
   x = ALLOT(double*,nblk) ;
   b = ALLOT(double*,nblk) ;
   p = ALLOT(double*,nblk) ;
   r = ALLOT(double*,nblk) ;
   t = ALLOT(double*,nblk) ;
   z = ALLOT(double*,nblk) ;
#include "pardo.h"
   for ( iblk = 0 ; iblk < my_nblk ; iblk++ ) {
      x[iblk] = tblk[iblk].phi ;
      b[iblk] = tblk[iblk].rhs ;
      p[iblk] = tblk[iblk].dphi  ;
      r[iblk] = tblk[iblk].adphi ;
   }
#include "pardo.h"
   for ( iblk = 0 ; iblk < my_nblk ; iblk++ ) {
      int i;
      i = domains[iblk].nnalls + 1 ;
      t[iblk] = MALLOT(double,i) ;
      z[iblk] = MALLOT(double,i) ;
      for ( i = 0 ; i <= domains[iblk].nnalls ; i++ ) {
         p[iblk][i] = 0.0 ;
         r[iblk][i] = 0.0 ;
         t[iblk][i] = 0.0 ;
         z[iblk][i] = 0.0 ;
      }
   }
   comerr += rbndcom(RBNDCOM1,COM_RECV,0)      ;
   comerr += rbndcom(RBNDCOM1,COM_SEND,0)      ;
   comerr += rbndcom(RBNDCOM1,COM_WAIT_RECV,0) ;
   comerr += rbndcom(RBNDCOM1,COM_WAIT_SEND,0) ;
#include "pardo.h"
   for ( iblk = 0 ; iblk < my_nblk ; iblk++ ) {
 ; 
   }
#include "pardo.h"
   for ( iblk = 0 ; iblk < my_nblk ; iblk++ ) {
      setpz2( x[iblk], 0.0, &domains[iblk] ) ;
   }
#include "pardo.h"
   for ( iblk = 0 ; iblk < my_nblk ; iblk++ ) {
      rmatmult( &domains[iblk], &rblk[iblk], x[iblk], r[iblk] ) ;
   }
#include "pardo.h"
   for ( iblk = 0 ; iblk < my_nblk ; iblk++ ) {
      int i;
      int is;
      int ie;
      is = domains[iblk].frz ;
      ie = domains[iblk].lrz ;
      for ( i = is ; i <= ie ; i++ ) {
         r[iblk][i] = b[iblk][i] - r[iblk][i] ;
      }
      myflops += 1.0 * ( ie - is + 1 ) ;
   }
   comerr += rbndcom(RBNDCOM5,COM_RECV,0)      ;
   comerr += rbndcom(RBNDCOM5,COM_SEND,0)      ;
   comerr += rbndcom(RBNDCOM5,COM_WAIT_RECV,0) ;
   comerr += rbndcom(RBNDCOM5,COM_WAIT_SEND,0) ;
#include "pardo.h"
   for ( iblk = 0 ; iblk < my_nblk ; iblk++ ) {
 ; 
   }
#include "pardo.h"
   for ( iblk = 0 ; iblk < my_nblk ; iblk++ ) {
      setpz2( r[iblk], 0.0, &domains[iblk] ) ;
   }
#include "pardo.h"
   for ( iblk = 0 ; iblk < my_nblk ; iblk++ ) {
      rmatmult( &domains[iblk], &cblk[iblk], r[iblk], z[iblk] ) ;
   }
#include "pardo.h"
   for ( iblk = 0 ; iblk < my_nblk ; iblk++ ) {
      setpz1( z[iblk], 0.0, &domains[iblk] ) ;
      setpz2( z[iblk], 0.0, &domains[iblk] ) ;
   }
#include "pardo.h"
   for ( iblk = 0 ; iblk < my_nblk ; iblk++ ) {
      int i;
      int is;
      int ie;
      is = domains[iblk].frz ;
      ie = domains[iblk].lrz ;
      for ( i = is ; i <= ie ; i++ ) {
         p[iblk][i] = z[iblk][i] ;
      }
   }
   dotprev = 0.0 ;
   normrhs = 0.0 ;
#include "pardo.h"
   for ( iblk = 0 ; iblk < my_nblk ; iblk++ ) {
      int i ;
      for ( i = 0 ; i < domains[iblk].nnalls ; i++ ) {
	 if ( fabs( r[iblk][i] ) < ptiny ) r[iblk][i] = 0.0 ;
	 if ( fabs( z[iblk][i] ) < ptiny ) z[iblk][i] = 0.0 ;
	 if ( fabs( b[iblk][i] ) < ptiny ) b[iblk][i] = 0.0 ;
      }
   }
   for ( iblk = 0 ; iblk < nblk ; iblk++ ) {
      dotprev += icdot( r[iblk], z[iblk], domains[iblk].nnalls, &myflops ) ;
      normrhs += norml2( &domains[iblk], b[iblk] ) ;
   }
   cgsums[0] = dotprev ;
   cgsums[1] = normrhs ;
   if (ifparallel) {
      comreduce( cgsums, 2, COM_SUM, COM_ALL, COM_DOUBLE ) ;
   }
   dotprev = cgsums[0] ;
   normrhs = cgsums[1] ;
   normrhs = sqrt( normrhs ) + ptiny ;
   for ( iter = 1 ; iter <= maxit ; iter++ ) {
      comerr += rbndcom(RBNDCOM1,COM_RECV,0)      ;
      comerr += rbndcom(RBNDCOM1,COM_SEND,0)      ;
      comerr += rbndcom(RBNDCOM1,COM_WAIT_RECV,0) ;
      comerr += rbndcom(RBNDCOM1,COM_WAIT_SEND,0) ;
#include "pardo.h"
      for ( iblk = 0 ; iblk < my_nblk ; iblk++ ) {
 ; 
      }
#include "pardo.h"
      for ( iblk = 0 ; iblk < my_nblk ; iblk++ ) {
         setpz2( p[iblk], 0.0, &domains[iblk] ) ;
      }
#include "pardo.h"
      for ( iblk = 0 ; iblk < my_nblk ; iblk++ ) {
         rmatmult( &domains[iblk], &rblk[iblk], p[iblk], t[iblk] ) ;
      }
#include "pardo.h"
      for ( iblk = 0 ; iblk < my_nblk ; iblk++ ) {
         setpz1( p[iblk], 0.0, &domains[iblk] ) ;
         setpz1( t[iblk], 0.0, &domains[iblk] ) ;
         setpz2( t[iblk], 0.0, &domains[iblk] ) ;
      }
      dotp = 0.0 ;
#include "pardo.h"
      for ( iblk = 0 ; iblk < my_nblk ; iblk++ ) {
         int i ;
         for ( i = 0 ; i < domains[iblk].nnalls ; i++ ) {
	    if ( fabs( p[iblk][i] ) < ptiny ) p[iblk][i] = 0.0 ;
	    if ( fabs( t[iblk][i] ) < ptiny ) t[iblk][i] = 0.0 ;
         }
      }
      for ( iblk = 0 ; iblk < nblk ; iblk++ ) {
         dotp += icdot( p[iblk], t[iblk], domains[iblk].nnalls, &myflops) ;
      }
      if (ifparallel)  {
         comreduce( &dotp, 1, COM_SUM, COM_ALL, COM_DOUBLE ) ;
      }
      alpha = dotprev / ( dotp + ptiny ) ;
#include "pardo.h"
      for ( iblk = 0 ; iblk < my_nblk ; iblk++ ) {
         int i;
         int is;
         int ie;
         is = domains[iblk].frz ;
         ie = domains[iblk].lrz ;
         for ( i = is ; i <= ie ; i++ ) {
            x[iblk][i] = x[iblk][i] + alpha * p[iblk][i] ;
            r[iblk][i] = r[iblk][i] - alpha * t[iblk][i] ;
         }
         myflops += 4.0 * ( ie - is + 1 ) ;
      }
      comerr += rbndcom(RBNDCOM5,COM_RECV,0)      ;
      comerr += rbndcom(RBNDCOM5,COM_SEND,0)      ;
      comerr += rbndcom(RBNDCOM5,COM_WAIT_RECV,0) ;
      comerr += rbndcom(RBNDCOM5,COM_WAIT_SEND,0) ;
#include "pardo.h"
      for ( iblk = 0 ; iblk < my_nblk ; iblk++ ) {
 ; 
      }
#include "pardo.h"
      for ( iblk = 0 ; iblk < my_nblk ; iblk++ ) {
         setpz2( r[iblk], 0.0, &domains[iblk] ) ;
      }
#include "pardo.h"
      for ( iblk = 0 ; iblk < my_nblk ; iblk++ ) {
         rmatmult( &domains[iblk], &cblk[iblk], r[iblk], z[iblk] ) ;
      }
#include "pardo.h"
      for ( iblk = 0 ; iblk < my_nblk ; iblk++ ) {
         setpz1( x[iblk], 0.0, &domains[iblk] ) ;
         setpz2( x[iblk], 0.0, &domains[iblk] ) ;
         setpz1( r[iblk], 0.0, &domains[iblk] ) ;
         setpz1( z[iblk], 0.0, &domains[iblk] ) ;
         setpz2( z[iblk], 0.0, &domains[iblk] ) ;
      }
      dotrz = 0.0 ;
      normx = 0.0 ;
      normp = 0.0 ;
      normr = 0.0 ;
#include "pardo.h"
      for ( iblk = 0 ; iblk < my_nblk ; iblk++ ) {
         int i ;
         for ( i = 0 ; i < domains[iblk].nnalls ; i++ ) {
	    if ( fabs( p[iblk][i] ) < ptiny ) p[iblk][i] = 0.0 ;
	    if ( fabs( r[iblk][i] ) < ptiny ) r[iblk][i] = 0.0 ;
	    if ( fabs( x[iblk][i] ) < ptiny ) x[iblk][i] = 0.0 ;
	    if ( fabs( z[iblk][i] ) < ptiny ) z[iblk][i] = 0.0 ;
         }
      }
      for ( iblk = 0 ; iblk < nblk ; iblk++ ) {
         dotrz += icdot( r[iblk], z[iblk], domains[iblk].nnalls,&myflops) ;
         normx += norml2( &domains[iblk], x[iblk] ) ;
         normp += norml2( &domains[iblk], p[iblk] ) ;
         normr += norml2( &domains[iblk], r[iblk] ) ;
      }
      cgsums[0] = dotrz ;
      cgsums[1] = normx ;
      cgsums[2] = normp ;
      cgsums[3] = normr ;
      if (ifparallel) {
         comreduce( cgsums, 4, COM_SUM, COM_ALL, COM_DOUBLE ) ;
      }
      dotrz = cgsums[0] ;
      normx = cgsums[1] ;
      normp = cgsums[2] ;
      normr = cgsums[3] ;
      normx = sqrt( normx ) ;
      normp = sqrt( normp ) ;
      normr = sqrt( normr ) ;
      xerr = fabs( alpha ) * normp / ( normx + ptiny ) ;
      rerr = normr / normrhs ;
      if ( (xerr < eps) && (rerr < eps) && (iter >= rdifitn) ) {
         break ;
      }
      beta    = dotrz / ( dotprev + ptiny ) ;
      dotprev = dotrz ;
#include "pardo.h"
      for ( iblk = 0 ; iblk < my_nblk ; iblk++ ) {
         int i;
         int is;
         int ie;
         is = domains[iblk].frz ;
         ie = domains[iblk].lrz ;
         for ( i = is ; i <= ie ; i++ ) {
            p[iblk][i] = z[iblk][i] + beta * p[iblk][i] ;
	 }
         myflops += 2.0 * ( ie - is + 1 ) ;
      }
   } 
   *iterations = iter              ;
   *error      = MAX( xerr, rerr ) ;
#include "pardo.h"
   for ( iblk = 0 ; iblk < my_nblk ; iblk++ ) {
      int i;
      int zone_max     = -1;
      double value_max = -plarge;
      TimeStepControl_t *tsc = TimeStepControl_find("TSC_Residual",domains[iblk].hash) ; 
      for ( i = domains[iblk].frz ; i <= domains[iblk].lrz ; i++ ) {
         if (fabs(r[iblk][i]) > value_max) {
            zone_max  = i;
            value_max = fabs(r[iblk][i]);
         }
      }
      tsc->value = 1.0 / (value_max + ptiny);
      if (ndims == 2) NDXEXT2D( zone_max, tsc->i, tsc->j, domains[iblk]) ; 
      if (ndims == 3) NDXEXT3D( zone_max, tsc->i, tsc->j, tsc->k, domains[iblk]);        
      myflops += 1.0 * ( domains[iblk].lrz - domains[iblk].frz + 1 ) ;
   }
#include "pardo.h"
   for ( iblk = 0 ; iblk < my_nblk ; iblk++ ) {
      FREEMEM( t[iblk] ) ;
      FREEMEM( z[iblk] ) ;
   }
   FREEMEM(x) ;
   FREEMEM(b) ;
   FREEMEM(p) ;
   FREEMEM(r) ;
   FREEMEM(t) ;
   FREEMEM(z) ;
   FT_FINALIZE(me, gv_hash_tbl, myflops)
}
static void MatrixSolvePC2D( RadiationData_t *cblk, RadiationData_t *rblk,
                             Domain_t *domain )
{
   char *me = "MatrixSolvePC2D" ;
   int i, jp, frz, lpz ;
   double myflops = 0.0;
   FT_INITIALIZE(me, domain->hash)
   jp  = domain->jp  ;
   frz = domain->frz ;
   lpz = domain->lpz ;
   for ( i = frz ; i <= lpz ; i++ ) {
      cblk->ccl[i] -= cblk->ccc[i] * rblk->ccl[i] * cblk->ccc[i-1]    ;
      cblk->cbc[i] -= cblk->ccc[i] * rblk->cbc[i] * cblk->ccc[i-jp]   ;
      cblk->cbl[i] -= cblk->ccc[i] * rblk->cbl[i] * cblk->ccc[i-1-jp] ;
      cblk->cbr[i] -= cblk->ccc[i] * rblk->cbr[i] * cblk->ccc[i+1-jp] ;
   }
   myflops += 12.0 * ( lpz - frz + 1 ) ;
   FT_FINALIZE(me, domain->hash, myflops) 
}
static void MatrixSolvePC3D( RadiationData_t *cblk, RadiationData_t *rblk,
                             Domain_t *domain )
{
   char *me = "MatrixSolvePC3D" ;
   double *ccci, *ddbl, *ddbc, *ddbr, *ddcl, *ddcc, *ddcr, *ddfl, *ddfc, *ddfr;
   double *dcbl, *dcbc, *dcbr, *dccl;
   int comerr ;
   int i ;
   double myflops = 0.0;
   FT_INITIALIZE(me, domain->hash)
   dccl = cblk->ccc - 1 ;
   dcbr = cblk->ccc - domain->jp + 1 ;
   dcbc = cblk->ccc - domain->jp     ;
   dcbl = cblk->ccc - domain->jp - 1 ;
   ddfr = cblk->ccc - domain->kp + domain->jp + 1 ;
   ddfc = cblk->ccc - domain->kp + domain->jp     ;
   ddfl = cblk->ccc - domain->kp + domain->jp - 1 ;
   ddcr = cblk->ccc - domain->kp + 1 ;
   ddcc = cblk->ccc - domain->kp     ;
   ddcl = cblk->ccc - domain->kp - 1 ;
   ddbr = cblk->ccc - domain->kp - domain->jp + 1 ;
   ddbc = cblk->ccc - domain->kp - domain->jp    ;
   ddbl = cblk->ccc - domain->kp - domain->jp - 1 ;
   for ( i = domain->frz ; i <= domain->lpz ; i++ ) {
      cblk->ccl[i] = -rblk->ccl[i] *cblk->ccc[i]*dccl[i] ;
      cblk->cbr[i] = -rblk->cbr[i] * cblk->ccc[i] * dcbr[i] ;
      cblk->cbc[i] = -rblk->cbc[i] * cblk->ccc[i] * dcbc[i] ;
      cblk->cbl[i] = -rblk->cbl[i] * cblk->ccc[i] * dcbl[i] ;
      cblk->dfr[i] = -rblk->dfr[i] * cblk->ccc[i] * ddfr[i] ;
      cblk->dfc[i] = -rblk->dfc[i] * cblk->ccc[i] * ddfc[i] ;
      cblk->dfl[i] = -rblk->dfl[i] * cblk->ccc[i] * ddfl[i] ;
      cblk->dcr[i] = -rblk->dcr[i] * cblk->ccc[i] * ddcr[i] ;
      cblk->dcc[i] = -rblk->dcc[i] * cblk->ccc[i] * ddcc[i] ;
      cblk->dcl[i] = -rblk->dcl[i] * cblk->ccc[i] * ddcl[i] ;
      cblk->dbr[i] = -rblk->dbr[i] * cblk->ccc[i] * ddbr[i] ;
      cblk->dbc[i] = -rblk->dbc[i] * cblk->ccc[i] * ddbc[i] ;
      cblk->dbl[i] = -rblk->dbl[i] * cblk->ccc[i] * ddbl[i] ;
   }
   myflops += 28.0 * ( domain->lpz - domain->frz + 1 ) ;
   FT_FINALIZE(me, domain->hash, myflops)
}
