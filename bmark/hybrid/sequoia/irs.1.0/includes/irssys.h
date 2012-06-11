#ifndef IRSSYS_H
#define IRSSYS_H

/*******************************************************************************
* DEFINES
*******************************************************************************/

/*******************************************************************************
* PROTOTYPES
*******************************************************************************/
extern double getcpu(void);
extern double getruntime(void);
extern double icasum(double *v, int n, double *pflops);
extern double icdot(double *v1, double *v2, int n, double *pflops);
extern double icnrml2(double *v, int n);
extern double icsum(double *v, int n, double *pflops);
extern double vmax(int *ndxmax, double *v, int n);
extern double vmin(int *ndxmin, double *v, int n);
extern int getndx(int *ndx, int *flag, int test, int n, int *zbit);
extern int getndx0(int *ndx, int *flag, int ioff, int test, int n, int *zbit);
extern int lists_overlap(int *list1, int nlist1, int *list2, int nlist2, int *list3);
extern int sort2_double(int n, int *irr, double *xrr);
extern int sort2_double_int(int len, int *in, double *db);
extern int sort2_int(int n, int *irr, int *xrr);
extern int sort_ptr_array(void * *array_ptr, int len, size_t fld_offset);
extern int tstsum(int *flag, int test, int n, int *zbit);
extern void fprint_(char *s, int *err);
extern void HardwareInit(void);


/*		****************************************************************
*		*
*		* stacklib routines
*		*
*		***************************************************************/
#ifdef STKLIB
int    fortran lvsum() ;
int    fortran qztoil() ;
int    fortran qjne1() ;
int    fortran qjeq1() ;
int    fortran qz1cps() ;
int    fortran comprs() ;
int    fortran qvmin() ;
int    fortran qvmax() ;
int    fortran imax1() ;
double fortran sdot() ;
/*
   omnilib routines
*/
double fortran ssum() ;
double fortran snrm2() ;
double fortran sasum() ;
#endif

#endif
/*******************************************************************************
* GLOBALS
*******************************************************************************/
extern double base ;   /* HH_INIT  0.0 */
extern double tlast ;  /* HH_INIT  0.0 */

/*******************************************************************************
* END OF FILE
*******************************************************************************/
