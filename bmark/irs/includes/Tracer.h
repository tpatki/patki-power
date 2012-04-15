#ifndef Tracer_H
#define Tracer_H

/* RGST_START */

#include "irsdefs.h"

/* RGST_END */

/*------------------------------------------------------------------------------
- DEFINES AND MACROS
------------------------------------------------------------------------------*/
#define TRACER_FREE  0
#define TRACER_FIXED 1
#define TRACER_LOST  2

/*------------------------------------------------------------------------------
- STRUCTURE
------------------------------------------------------------------------------*/

/* RGST_START */

typedef struct Tracer_s {

   char name[MAXWORD];
   
   double x;
   double y;
   double z;

   double xdot;
   double ydot;
   double zdot;

   double zeta1;
   double zeta2;
   double zeta3;

   int type;

   int zone;
   int owner;

   struct Tracer_s *next;

} Tracer_t;

/* RGST_END */

/*------------------------------------------------------------------------------
- PROTOTYPES
------------------------------------------------------------------------------*/
#ifdef SILO
extern int tracer_rdsilo(DBfile *inFile);
extern int tracer_wtpointmesh(DBfile *inFile);
extern int tracer_wtsilo(DBfile *inFile);
#endif

extern char * tracer_cunpack(char *data, int len);
extern int tracer_input(void);
extern int tracer_print(void);
extern int tracer_tntrp(void);
extern void tracer_advance(double dt);
extern void tracer_collect(void);
extern void tracer_cpack(char * *data);
extern void tracer_dpack(double * *data, int *outlen, int oldlen);
extern void tracer_dunpack(double *data, int len);
extern void tracer_find(void);
extern void tracer_free(void);
extern void tracer_ipack(int * *data, int *outlen, int *stroutlen, int oldlen);
extern void tracer_iunpack(int *data, int len, char *tracer_names);
extern void tracer_plot(int iflab);

#endif

/*------------------------------------------------------------------------------
- GLOBAL VARS
------------------------------------------------------------------------------*/

/*******************************************************************************
* END OF FILE
*******************************************************************************/
