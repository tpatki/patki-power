#ifndef Spline_H
#define Spline_H

/*------------------------------------------------------------------------------
- DEFINES AND MACROS
------------------------------------------------------------------------------*/

/* RGST_START */

#include "irsdefs.h"

/* RGST_END */

/* RGST_START */

#define UNKNOWNDATA  0
#define RTDATA       1
#define XYDATA       2
#define VXDATA       3
#define VRDATA       4
#define VTDATA       5

#define CUBIC        0
#define LINEAR       1
#define COMBINED	 2

#define SPLINE_INVERT       1
#define SPLINE_SCALE        2
#define SPLINE_ADD          3
#define SPLINE_DELTA        4

/* RGST_END */

/*------------------------------------------------------------------------------
- STRUCTURE
------------------------------------------------------------------------------*/

/* RGST_START */

struct Spline_t_ {

   char name[MAXWORD];

   int type;

   int coord;

   int flip;

   char indlab[2];
   char deplab[2];

   double x0;
   double y0;
   double z0;

   double axis_x;
   double axis_y;
   double axis_z;

   double norm_x;
   double norm_y;
   double norm_z;

   int len;

   double *dep;		/* RGST_LEN len */
   double *ind; 	/* RGST_LEN len */

   double  dep1;
   double  dep2;

   double *b;		/* RGST_LEN len */
   double *c;	 	/* RGST_LEN len */
   double *d;		/* RGST_LEN len */

   struct Spline_t_ *next;

 } ;

 typedef struct Spline_t_ Spline_t;

/* RGST_END */

/*------------------------------------------------------------------------------
- PROTOTYPES
------------------------------------------------------------------------------*/
#ifdef SILO
extern int  spline_rdsilo(DBfile *idbid);
extern int  spline_wtsilo(DBfile *idbid);
#endif

extern Spline_t * Spline_construct(int num);
extern Spline_t * spline_find(char *name); 
extern int  Spline_init(Spline_t *ptr);
extern int  Spline_setup_attrs(void);
extern int  spline_chkrange(Spline_t *spline, double xmin, double xmax);  
extern int  spline_eval(double val, double *dep, Spline_t *spline); 
extern int  spline_fit(void);
extern int  spline_getxy(double *x, double *y, int n, double xmin, double xmax, double x0, double y0, Spline_t *spline);
extern int  spline_input(void);
extern int  spline_plsp(void);
extern int  spline_plspoff(void);
extern int  spline_print(void);
extern void spline_delete(char *name);
extern void spline_free(void);
extern void spline_getvalues(int mode);
extern void spline_plot( int iflab );
extern void fillvar_spline(double *vptr, double *x, double *y, double *z, double *r, double *t, int len, Spline_t *spline, double xmin, double xmax, char *cnst);

#endif 
/*------------------------------------------------------------------------------
- GLOBAL VARS
------------------------------------------------------------------------------*/

/*******************************************************************************
* END OF FILE
*******************************************************************************/
