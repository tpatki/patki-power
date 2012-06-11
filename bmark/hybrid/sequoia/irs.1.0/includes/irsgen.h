#ifndef IRSGEN_H
#define IRSGEN_H

#include "NodeList.h"

/*******************************************************************************
* DEFINES
*******************************************************************************/
#define FNTRP   0
#define FRATIO  1
#define FSUM    2
#define FDIF    3
#define FMLT    4
#define FDIV    5
#define FPOW    6
#define FSIN    7
#define FCOS    8
#define FTAN    9
#define FCOT   10
#define FABS   11
#define FLOG   12
#define FEXP   13
#define FSQRT  14
#define FSQR   15
#define FMIN   16
#define FMAX   17
#define FMAG   18
#define FFT    19
#define FSPLN  20
#define FRAND  21

#define ERRCHK(a,b,c,d)								\
   if (strcmp(a,b))  								\
      {           								\
      char errmsg[256]; 							\
      error = 1 ; 								\
      sprintf(errmsg,"Found %s instead of '%s' after %s in %s expression",	\
                      a,b,c,d) ;  						\
      ctlmsg(errmsg); 								\
      return(error) ; 								\
      }

/*******************************************************************************
* PROTOTYPES
*******************************************************************************/
extern double ratioeval(double factor, int type, int n);
extern double ratiosum(double ratio, int n);
extern int altmesh(void);
extern int doarg_fun(int ifun, double *farg, int lentar);
extern int doarg_fun_alloc(int ifun, double * *dptr, int dptrlen);
extern int dopa(char *aname);
extern int fillvar_input(void);
extern int gen(void);
extern int getarg(char *type, void *ptr, int ptrlen);
extern int getfarg(double *farg, int lentar);
extern int getfpaa(char *aname, double *farg);
extern int getfpaa_rgst(char *aname, double * *dptr, int dptrlen);
extern int getiarg(int *iarg, int lentar);
extern int getrgstdata(RGST_Datatype_t dt, char *sym, void * *ptr, int ptrlen);
extern int gnorm(int type);
extern int isargfun(char *sym);
extern int isbeta(char *sym);
extern int meshgen_input(int inputtype);
extern int mixzn(void);
extern int pole(void);
extern int purify(void);
extern int rdmesh(void);
extern int rdsilogrid(void);
extern int rdtruegrid(void);
extern int realindex(void);
extern int regen(void);
extern int regen_pregen(void);
extern int regen_reset(void);
extern int sewmeshes(int NumOutputFiles);
extern int wtmesh(void);
extern int zone(void);
extern void arcal2ds(double *area, double *x, double *y, Domain_t *domain);
extern void fillvar_getvar(double *vptr, int *ndx, int *len, char *varname, int *species, int mynspec, int mat, Domain_t *domain);
extern void getematblk(int flag, Domain_t *domain);
extern void getspeed2(double *speed2, Domain_t *domain);
extern void meshgen_linearfill(int logical, NodeWindow_t *ndxin);
extern void meshgen_setlogical(int logical, int *i1, int *i2, int *i3);
extern void mkpalab(char *lab, char *aname, int iblk, int (*my_in)[3], int nrank, int roptype, char *rop);
extern void plgndr(int l, int m, double *xmu, double *plg, int n);
extern void sanityck(void);
extern void tagvoid(Domain_t *domain);
extern void volcal2d(double *vol, double *area, double *x, double *y, Domain_t *domain);
extern void volcal3d(double *vol, double *x, double *y, double *z, Domain_t *domain);

#endif
/*******************************************************************************
* GLOBALS
*******************************************************************************/

extern int roptype ;
extern int ninloops ;
extern int nincount ;
extern int ninlen  ;
extern int nrank ;


/*******************************************************************************
* END OF FILE
*******************************************************************************/
