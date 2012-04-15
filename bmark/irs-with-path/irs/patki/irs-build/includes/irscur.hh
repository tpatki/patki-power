#ifndef IRSCUR_H
#define IRSCUR_H

#include "VectorStruct.h"

/*******************************************************************************
* DEFINES
*******************************************************************************/
#define MNC 10

/*******************************************************************************
* PROTOTYPES
*******************************************************************************/

double irsfmax(double *x, int n);
double irsfmin(double *x, int n);
int curbold(void);
int curbop(int bop);
int curgetxy(int mode);
int curst(void);
int curwrtxy(int mode);
int delcur(void);
int dist(int ioflag);
int getcur(int cc, int tpflag);
int getnxcn(void);
int getvec(VectorStruct_t *vecstr, int labflag, int allocflag);
int getvec1(VectorStruct_t *vecstr, int labflag);
int getvectp(VectorStruct_t *vecstr);
int pamp(void);
int plot(void);
int plotmd(void);
int setcur(double *x, double *y, int n, char *xlab, char *ylab);
int setcur0(int cc, double *x, double *y, int n, char *xlab, char *ylab);
int tpamp(void);
int tplot(void);
int xlim(void);
int ylim(void);
void clrcur(void);
void curgetxy0(int cn, double val, int mode);
void curlmt(void);
void curwrtxy0(char *outfile, double val0, int cn, double val, int mode);
void delcur0(int cn);
void dobop(char *chop, double *x, double *y, double *xa, double *ya, double *xb, double *yb, int n, int bop);
void dorop(double *result, double *field, int *ndx, int n, int roptype);
void douop1(double *xa, double *ya, int n, int uop);
void douop2(char *chop, double *x, double *y, double *xa, double *ya, int n, int uop);
void getcurroot(double *ret, int *nret, double *x, double *y, int n, double yval, double xmin, double xmax);
void stoplot(int my_itp);
void xlimpic(void);

#endif
/*******************************************************************************
* GLOBALS
*******************************************************************************/
int ifcuron[MNC] ;
int ifcurbd[MNC] ;
int ifcursel[MNC] ;
int ifcurst[MNC] ;
int ncurx  =   MNC ;
int ncur   =   0   ;
int xlimfg  =   0 ;
int ylimfg  =   0 ;
int cnset  =   -1 ;
double cxmn ;
double cxmx ;
double cymn ;
double cymx ;
double xmn ;
double xmx ;
double ymn ;
double ymx ;

VectorStruct_t p1d[2*MNC] ;

/* file pointer for pampers file */

FILE *fpamp  =  NULL ;


/*******************************************************************************
* END OF FILE
*******************************************************************************/
