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

extern double irsfmax(double *x, int n);
extern double irsfmin(double *x, int n);
extern int curbold(void);
extern int curbop(int bop);
extern int curgetxy(int mode);
extern int curst(void);
extern int curwrtxy(int mode);
extern int delcur(void);
extern int dist(int ioflag);
extern int getcur(int cc, int tpflag);
extern int getnxcn(void);
extern int getvec(VectorStruct_t *vecstr, int labflag, int allocflag);
extern int getvec1(VectorStruct_t *vecstr, int labflag);
extern int getvectp(VectorStruct_t *vecstr);
extern int pamp(void);
extern int plot(void);
extern int plotmd(void);
extern int setcur(double *x, double *y, int n, char *xlab, char *ylab);
extern int setcur0(int cc, double *x, double *y, int n, char *xlab, char *ylab);
extern int tpamp(void);
extern int tplot(void);
extern int xlim(void);
extern int ylim(void);
extern void clrcur(void);
extern void curgetxy0(int cn, double val, int mode);
extern void curlmt(void);
extern void curwrtxy0(char *outfile, double val0, int cn, double val, int mode);
extern void delcur0(int cn);
extern void dobop(char *chop, double *x, double *y, double *xa, double *ya, double *xb, double *yb, int n, int bop);
extern void dorop(double *result, double *field, int *ndx, int n, int roptype);
extern void douop1(double *xa, double *ya, int n, int uop);
extern void douop2(char *chop, double *x, double *y, double *xa, double *ya, int n, int uop);
extern void getcurroot(double *ret, int *nret, double *x, double *y, int n, double yval, double xmin, double xmax);
extern void stoplot(int my_itp);
extern void xlimpic(void);

#endif
/*******************************************************************************
* GLOBALS
*******************************************************************************/
extern int ifcuron[MNC] ;
extern int ifcurbd[MNC] ;
extern int ifcursel[MNC] ;
extern int ifcurst[MNC] ;
extern int ncurx ; 		/* HH_INIT  MNC */
extern int ncur  ; 		/* HH_INIT  0   */
extern int xlimfg ; 		/* HH_INIT  0 */
extern int ylimfg ; 		/* HH_INIT  0 */
extern int cnset ; 		/* HH_INIT  -1 */
extern double cxmn ;
extern double cxmx ;
extern double cymn ;
extern double cymx ;
extern double xmn ;
extern double xmx ;
extern double ymn ;
extern double ymx ;

extern VectorStruct_t p1d[2*MNC] ;

/* file pointer for pampers file */

extern FILE *fpamp ;	/* HH_INIT NULL */


/*******************************************************************************
* END OF FILE
*******************************************************************************/
