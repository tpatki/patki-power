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
double ratioeval(double factor, int type, int n);
double ratiosum(double ratio, int n);
int altmesh(void);
int doarg_fun(int ifun, double *farg, int lentar);
int doarg_fun_alloc(int ifun, double * *dptr, int dptrlen);
int dopa(char *aname);
int fillvar_input(void);
int gen(void);
int getarg(char *type, void *ptr, int ptrlen);
int getfarg(double *farg, int lentar);
int getfpaa(char *aname, double *farg);
int getfpaa_rgst(char *aname, double * *dptr, int dptrlen);
int getiarg(int *iarg, int lentar);
int getrgstdata(RGST_Datatype_t dt, char *sym, void * *ptr, int ptrlen);
int gnorm(int type);
int isargfun(char *sym);
int isbeta(char *sym);
int meshgen_input(int inputtype);
int mixzn(void);
int pole(void);
int purify(void);
int rdmesh(void);
int rdsilogrid(void);
int rdtruegrid(void);
int realindex(void);
int regen(void);
int regen_pregen(void);
int regen_reset(void);
int sewmeshes(int NumOutputFiles);
int wtmesh(void);
int zone(void);
void arcal2ds(double *area, double *x, double *y, Domain_t *domain);
void fillvar_getvar(double *vptr, int *ndx, int *len, char *varname, int *species, int mynspec, int mat, Domain_t *domain);
void getematblk(int flag, Domain_t *domain);
void getspeed2(double *speed2, Domain_t *domain);
void meshgen_linearfill(int logical, NodeWindow_t *ndxin);
void meshgen_setlogical(int logical, int *i1, int *i2, int *i3);
void mkpalab(char *lab, char *aname, int iblk, int (*my_in)[3], int nrank, int roptype, char *rop);
void plgndr(int l, int m, double *xmu, double *plg, int n);
void sanityck(void);
void tagvoid(Domain_t *domain);
void volcal2d(double *vol, double *area, double *x, double *y, Domain_t *domain);
void volcal3d(double *vol, double *x, double *y, double *z, Domain_t *domain);

#endif
/*******************************************************************************
* GLOBALS
*******************************************************************************/

int roptype ;
int ninloops ;
int nincount ;
int ninlen  ;
int nrank ;


/*******************************************************************************
* END OF FILE
*******************************************************************************/
