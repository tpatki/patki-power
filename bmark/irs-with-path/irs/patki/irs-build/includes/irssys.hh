#ifndef IRSSYS_H
#define IRSSYS_H

/*******************************************************************************
* DEFINES
*******************************************************************************/

/*******************************************************************************
* PROTOTYPES
*******************************************************************************/
double getcpu(void);
double getruntime(void);
double icasum(double *v, int n, double *pflops);
double icdot(double *v1, double *v2, int n, double *pflops);
double icnrml2(double *v, int n);
double icsum(double *v, int n, double *pflops);
double vmax(int *ndxmax, double *v, int n);
double vmin(int *ndxmin, double *v, int n);
int getndx(int *ndx, int *flag, int test, int n, int *zbit);
int getndx0(int *ndx, int *flag, int ioff, int test, int n, int *zbit);
int lists_overlap(int *list1, int nlist1, int *list2, int nlist2, int *list3);
int sort2_double(int n, int *irr, double *xrr);
int sort2_double_int(int len, int *in, double *db);
int sort2_int(int n, int *irr, int *xrr);
int sort_ptr_array(void * *array_ptr, int len, size_t fld_offset);
int tstsum(int *flag, int test, int n, int *zbit);
void fprint_(char *s, int *err);
void HardwareInit(void);


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
double base  =   0.0 ;
double tlast  =   0.0 ;

/*******************************************************************************
* END OF FILE
*******************************************************************************/
