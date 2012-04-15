#include "irs.h"
#include "irsgen.h"
#include "irsctl.h"
#include "Spline.h"
static int doarg_bin(int ifun,char *opname,double *farg, int lentar );
static int doarg_ft( double *farg, int	lentar );
static int doarg_mag( double *farg, int lentar );
static int doarg_ntrp( double *farg, int lentar );
static int doarg_spln(double *dep, int lentar);
static int doarg_un( int ifun, char *opname, double *farg, int lentar );
static int  doarg_bin(
	    int	     ifun,	   char	    *opname,	  double   *farg,
	    int	     lentar )
{
   int error ;
   int i,len,len1,len2 ;
   double *farg1,*farg2 ;
   char mysym[10] ;
   len = 0 ;
   geta(mysym) ;
   ERRCHK(mysym,"(",opname,"arg") ;
   farg1 = ALLOT(double, lentar);
   len1  = getarg("double",farg1, lentar);
   geta(mysym) ;
   ERRCHK(mysym,",",opname,"arg") ;
   farg2 = ALLOT(double,lentar) ;
   len2  = getarg("double",farg2,lentar);
   geta(mysym) ;
   ERRCHK(mysym,")",opname,"arg") ;
   len = len1 ;
   if (( len1 == 1 ) && ( len2 > len1))
      {
      len = len2 ;
      for ( i = 1 ; i < len ; i++ ) farg1[i] = farg1[0] ;
      }
   else if (( len2 == 1 ) && ( len1 > len2))
      {
      len = len1 ;
      for ( i = 1 ; i < len ; i++ ) farg2[i] = farg2[0] ;
      }
   if (ifun == FSUM)
      {
      for ( i = 0 ; i < len ; i++ )
         farg[i] = farg1[i] + farg2[i] ;
      }
   if (ifun == FDIF)
      {
      for ( i = 0 ; i < len ; i++ )
         farg[i] = farg1[i] - farg2[i] ;
      }
   if (ifun == FMLT)
      {
      for ( i = 0 ; i < len ; i++ )
         farg[i] = farg1[i] * farg2[i] ;
      }
   if (ifun == FDIV)
      {
      for ( i = 0 ; i < len ; i++ )
	 {
         if (farg2[i] != 0.) farg[i] = farg1[i]/farg2[i] ;
         else                farg[i] = farg1[i] ;
         }
      }
   if (ifun == FPOW)
      {
      for ( i = 0 ; i < len ; i++ )
         farg[i] = pow(farg1[i],farg2[i]) ;
      }
   if (ifun == FMIN)
      {
      for ( i = 0 ; i < len ; i++ )
	 {
         if (farg1[i] < farg2[i]) farg[i] = farg1[i] ;
         else                     farg[i] = farg2[i] ;
         }
      }
   if (ifun == FMAX)
      {
      for ( i = 0 ; i < len ; i++ )
	 {
         if (farg1[i] > farg2[i]) farg[i] = farg1[i] ;
         else                     farg[i] = farg2[i] ;
         }
      }
   FREEMEM(farg1) ;
   FREEMEM(farg2) ;
   return(len) ;
}
static int  doarg_ft( double *farg, int	lentar )
{
   int error,i,j,lenx,leny;
   char mysym[30] ;
   double *fx,*fn,acc,factor,k  ;
   fx = ALLOT(double,domains[blknum].nnalls) ;
   fn = ALLOT(double,lentar) ;
   geta(mysym) ;
   ERRCHK(mysym,"(","ft","arg") ;
   lenx = getfarg(fx,domains[blknum].nnalls) ;
   geta(mysym) ;
   ERRCHK(mysym,",","ft","arg") ;
   leny = getfarg(fn,lentar) ;
   geta(mysym) ;
   ERRCHK(mysym,")","ft","arg") ;
   factor = acos(-1.0) / ((double) (lenx)) ;
   for ( j = 0 ; j < leny ; j++ ) {
      acc = 0. ;
      for ( i = 0 ; i < lenx ; i++ ) {
	 k    = ((double) i) + 0.5 ;
         acc += fx[i] * cos(fn[j]*factor*k) ;
      }
      if ( fn[j] == 0. ) {
         farg[j] =      acc / ((double) lenx) ;
      } else {
         farg[j] = 2. * acc / ((double) lenx) ;
      }
   }
   FREEMEM(fx) ;
   FREEMEM(fn) ;
   return(leny) ;
}
int doarg_fun( int ifun,	double *farg, int lentar )
{
   int len ;
   if ( ifun == FNTRP ) len = doarg_ntrp(farg,lentar) ;
   if ( ifun == FSPLN ) len = doarg_spln(farg,lentar) ;
   if ( ifun == FMAG  ) len = doarg_mag(farg,lentar) ;
   if ( ifun == FFT   ) len = doarg_ft(farg,lentar) ;
   if ( ifun == FSUM  ) len = doarg_bin(FSUM,"sum",farg,lentar) ;
   if ( ifun == FDIF  ) len = doarg_bin(FDIF,"dif",farg,lentar) ;
   if ( ifun == FMLT  ) len = doarg_bin(FMLT,"mlt",farg,lentar) ;
   if ( ifun == FDIV  ) len = doarg_bin(FDIV,"div",farg,lentar) ;
   if ( ifun == FPOW  ) len = doarg_bin(FPOW,"pow",farg,lentar) ;
   if ( ifun == FMIN  ) len = doarg_bin(FMIN,"min",farg,lentar) ;
   if ( ifun == FMAX  ) len = doarg_bin(FMAX,"min",farg,lentar) ;
   if ( ifun == FSIN  ) len = doarg_un(FSIN,"sin",farg,lentar) ;
   if ( ifun == FCOS  ) len = doarg_un(FCOS,"cos",farg,lentar) ;
   if ( ifun == FTAN  ) len = doarg_un(FTAN,"tan",farg,lentar) ;
   if ( ifun == FCOT  ) len = doarg_un(FCOT,"cot",farg,lentar) ;
   if ( ifun == FABS  ) len = doarg_un(FABS,"abs",farg,lentar) ;
   if ( ifun == FLOG  ) len = doarg_un(FLOG,"log",farg,lentar) ;
   if ( ifun == FEXP  ) len = doarg_un(FEXP,"exp",farg,lentar) ;
   if ( ifun == FSQRT ) len = doarg_un(FSQRT,"sqrt",farg,lentar) ;
   if ( ifun == FSQR  ) len = doarg_un(FSQR,"sqr",farg,lentar) ;
   if ( ifun == FRAND ) len = doarg_un(FRAND,"rand",farg,lentar) ;
   return(len) ;
}
#ifndef _POSIX_SOURCE
#define _POSIX_SOURCE 1
#endif
#define MAXDBLS 512
int doarg_fun_alloc (
  int      ifun,    
  double **dptr,    
  int      dptrlen) 
{
  char *me = "doarg_fun_alloc";
  if (dptrlen < 0) {
    if (dptrlen == -1) { dptrlen = MAXDBLS; }
    else               { dptrlen = -dptrlen; }
    if ((*dptr = ALLOT(double,dptrlen)) == NULL) ctlerror(me,gv_errmsg_memory);
  }
  return(doarg_fun(ifun,*dptr,dptrlen));
}
static int  doarg_mag( double *farg, int lentar )
{
   char *me = "doarg_mag";
   int error,i,lenx,leny,lenz,n;
   char mysym[30],msg[128];
   double *fx,*fy,*fz  ;
   fx = ALLOT(double,lentar) ;
   fy = ALLOT(double,lentar) ;
   fz = ALLOT(double,lentar) ;
   geta(mysym) ;
   ERRCHK(mysym,"(","mag","arg") ;
   lenx = getfarg(fx,lentar) ;
   geta(mysym) ;
   ERRCHK(mysym,",","mag","arg") ;
   lenz = leny = getfarg(fy,lentar) ;
   geta(mysym) ;
   for ( i = 0 ; i < lentar ; i++ ) fz[i] = 0. ;
   if (!strcmp(mysym,","))
      {
      lenz = getfarg(fz,lentar) ;
      geta(mysym) ;
      }
   ERRCHK(mysym,")","mag","arg") ;
   if ((lenx != leny) || (leny != lenz))
	{
        ctlwarning(me,"arguments to mag function are not equal length") ;
	}
   n = lenx ;
   if (n > lentar)
      {
      sprintf(msg,"mag arg len (%d) exceeds target len (%d)",n,lentar) ;
      ctlwarning(me,msg);
      }
   for ( i = 0 ; i < n ; i++ )
      {
      farg[i] = sqrt(fx[i]*fx[i] + fy[i]*fy[i] + fz[i]*fz[i]) ;
      }
   FREEMEM(fx) ;
   FREEMEM(fy) ;
   FREEMEM(fz) ;
   return(n) ;
}
static int doarg_ntrp( double *farg, int lentar )
{
   char *me = "doarg_ntrp";
   int error, i, len, n, loopflag ;
   char mysym[30],msg[128];
   double a1[1], a2[1], a, da ;
   geta(mysym) ;
   ERRCHK(mysym,"(","ntrp","arg") ;
   len = getfarg(a1,1) ;
   if (len != 1) {
      ctlwarning(me,"first arg of ntrp not of length 1");
   }
   geta(mysym) ;
   ERRCHK(mysym,",","ntrp","arg") ;
   len = getfarg(a2,1) ;
   if (len != 1) {
      ctlwarning(me,"second arg of ntrp not of length 1");
   }
   geta(mysym) ;
   n        = lentar ;
   loopflag = 0 ;
   if ( !strcmp(mysym,",") ) {
      geta(mysym) ;
      if ( !strcmp(mysym,"%") ) {
         loopflag = 1 ;
         n        = 1 ;
      } else {
         n = atoi(mysym) + iplusmin ;
      }
      geta(mysym) ;
   }
   ERRCHK(mysym,")","ntrp","arg") ;
   if (n > lentar) {
      sprintf(msg,"length out of ntrp function %d exceeds target length %d",
                    n,lentar) ;
      ctlwarning(me,msg);
      n = lentar ;
   }
   if ( (n < 2 ) && (loopflag == 0) ) {
      sprintf(msg,"length out of ntrp function %d is less than 2",n);
      ctlwarning(me,msg);
      n = 2 ;
   }
   if ( loopflag == 0 ) {
      a  = a1[0] ;
      da = (a2[0] - a1[0]) / ( (double)(n-1) ) ;
      farg[0] = a ;
      for ( i = 1 ; i < n ; i++ ) {
         farg[i] = farg[i-1] + da ;
      }
   } else {
      a  = a1[0] ;
      da = (a2[0] - a1[0]) / ( (double)(ninlen-1) ) ;
      farg[0] = a + nincount * da ;
   }
   return(n) ;
}
static int doarg_spln(double *dep, int lentar)
{
   char *me = "doarg_spln";
   int len;
   int i,n;
   int loopflag;
   int imin,imax;
   Spline_t *spline;
   double xmin[1], xmax[1];
   double deltax;
   double *ind;
   char op[MAXWORD], msg[128];
   loopflag = 0;
   n = lentar;
   geta(op);
   geta(op);
   spline = spline_find(op);
   if (spline == NULL) {
      sprintf(msg,"Spline %s not defined",op);
      ctlwarning(me,msg);
      return(-1);
   }
   geta(op);
   len = getfarg(xmin,1) ;
   if (len != 1) {
      ctlwarning(me,"first arg of spln not of length 1");
   }
   geta(op);
   len = getfarg(xmax,1) ;
   if (len != 1) {
      ctlwarning(me,"second arg of spln not of length 1");
   }
   imin = -1;
   imax = -1;
   len = spline->len;
   for (i=0;i<len-1;i++) {
     if ((xmin[0] >= spline->ind[i])&&(xmin[0] <= spline->ind[i+1])) imin = i;
     if ((xmax[0] >= spline->ind[i])&&(xmax[0] <= spline->ind[i+1])) imax = i;
   }
   if ( (imin == -1) || (imax == -1) ) {
      sprintf(msg,"Bad limits (%f,%f) in spline interpolation",
                     xmin[0],xmax[0]);
      ctlwarning(me,msg);
      return(-1);
   }
   geta(op) ;
   if ( !strcmp(op,",") ) {
      geta(op) ;
      if ( !strcmp(op,"%") ) {
         loopflag = 1 ;
         n        = 1 ;
      } else {
         n = atoi(op) + iplusmin ;
      }
      geta(op) ;
   }
   if (n > lentar) {
      sprintf(msg,"length out of spln function %d exceeds target length %d",n,lentar);
      ctlwarning(me,msg);
      n = lentar ;
   }
   if ( (n < 2 ) && (loopflag == 0) ) {
      sprintf(msg,"length out of spln function %d is less than 2",n);
      ctlwarning(me,msg);
      n = 2 ;
   }
   ind = ALLOT(double,n);
   if (loopflag == 0)  {
      deltax = (xmax[0] - xmin[0])/(double)(n - 1);
      for (i=0;i<n;i++) {
         ind[i] = xmin[0] + deltax*i;
         spline_eval(ind[i],&dep[i],spline);
      }
   } else if (n == 1) {
      deltax = (xmax[0] - xmin[0])/(double)(ninlen - 1);
      ind[0] = xmin[0] + nincount*deltax ;
      spline_eval(ind[0],&dep[0],spline);
   }
   FREEMEM(ind);
   return(n);
}
static int doarg_un( int ifun, char *opname, double *farg, int lentar )
{
   int error ;
   int i, len, len1 ;
   double *farg1 ;
   char mysym[10] ;
   double aconv ;
   len = 0 ;
   aconv = PI / 180.0 ;
   geta(mysym) ;
   ERRCHK(mysym,"(",opname,"arg") ;
   if ( ifun != FRAND ) {
      farg1 = ALLOT(double,lentar) ;
      len1  = getfarg(farg1,lentar) ;
   } else {
      len1  = lentar ;
   }
   geta(mysym) ;
   ERRCHK(mysym,")",opname,"arg") ;
   len = len1 ;
   if ( ifun == FSIN ) {
      for ( i = 0 ; i < len ; i++ ) {
         farg[i] = sin( aconv * farg1[i] ) ;
      }
   }
   if ( ifun == FCOS ) {
      for ( i = 0 ; i < len ; i++ ) {
         farg[i] = cos( aconv * farg1[i] ) ;
      }
   }
   if ( ifun == FTAN ) {
      for ( i = 0 ; i < len ; i++ ) {
         farg[i] = tan( aconv * farg1[i] ) ;
      }
   }
   if ( ifun == FCOT ) {
      for ( i = 0 ; i < len ; i++ ) {
         farg[i] = 1.0 / ( tan( aconv * farg1[i] ) + ptiny ) ;
      }
   }
   if ( ifun == FABS ) {
      for ( i = 0 ; i < len ; i++ ) {
         farg[i] = fabs( farg1[i] ) ;
      }
   }
   if ( ifun == FLOG ) {
      for ( i = 0 ; i < len ; i++ ) {
         farg[i] = log( fabs( farg1[i] ) + ptiny ) ;
      }
   }
   if ( ifun == FEXP ) {
      for ( i = 0 ; i < len ; i++ ) {
         farg[i] = exp( farg1[i] ) ;
      }
   }
   if ( ifun == FSQRT ) {
      for ( i = 0 ; i < len ; i++ ) {
         farg[i] = sqrt( fabs( farg1[i] ) ) ;
      }
   }
   if ( ifun == FSQR ) {
      for ( i = 0 ; i < len ; i++ ) {
         farg[i] = farg1[i] * farg1[i] ;
      }
   }
   if ( ifun == FRAND ) {
 ;    }
   if ( ifun != FRAND ) {
      FREEMEM(farg1) ;
   }
   return(len) ;
}
