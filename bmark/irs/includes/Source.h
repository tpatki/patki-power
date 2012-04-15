#ifndef SOURCE_H
#define SOURCE_H

/* RGST_START */

#include "irsdefs.h"
#include "Hash.h"

/* RGST_END */

/*------------------------------------------------------------------------------
- ENUMERATED TYPES
------------------------------------------------------------------------------*/
/* RGST_START */

typedef enum  {_SourceUnknown_, _SourceConstant_, _SourceTimeDep_,
               _SourceTable_  } SourceMode_t;

typedef enum  { _SourceEdit_, _SourceNoEdit_ } SourceEditMode_t;

/* RGST_END */

/*------------------------------------------------------------------------------
- STRUCTURE
------------------------------------------------------------------------------*/

/* RGST_START */

typedef struct {
  
   char *name;                 /* unique name for this source */
   char *type;                 /* string indicating the type of this source */
   
   int   len;                  /* length of the index list ndx */
   int  *ndx;                  /* index list of afflicted nodes/zones */

   int   centering;            /* flag for zonal or nodal centering of source */
   int   additive;             /* flag which is set to 1 if this source is
                                  additive */
   SourceMode_t   mode;        /* Set to one of the required modes */
   int   region;               /* region number if this is a regional source */

   double *depData;            /* RGST_LEN lenData */ 
                               /* array of dependent data */
   double *indData;            /* RGST_LEN lenData */
                               /* array of independent data */
   int     lenData;            /* length of data arrays */

   char *tableName;            /* name of table to be used in this source */

   char *depField;             /* name of the dependent field in the table */

   char *indField1;            /* name of the independent fields to use for */
   char *indField2;            /* interpolation using the table */
   char *indField3;


   double dSourceEdit;          /* incremental edit during the cycle */
   double  SourceEdit;          /* accumulated edit over the calculation */

} SourceNew_t;

typedef struct {

   char   ndxName[MAXLINE]; /* name of ndxlist */

   int imin;
   int imax;
   int jmin;
   int jmax;
   int kmin;
   int kmax;

   int type ;
   int cent ;

   int *ndxsrc ;        /* RGST_LEN nzsrc */
   int nzsrc ;

   int *idat1 ;         /* RGST_LEN nidat1 */
   int nidat1 ;

   double *fdat1 ;      /* RGST_LEN nfdat1 */
   int nfdat1 ;

   double *dat2 ;       /* RGST_LEN ndat2 */
   int ndat2 ;

   double *dat3 ;       /* RGST_LEN ndat3 */
   int ndat3 ;

} Source_t ;


/* RGST_END */

/*------------------------------------------------------------------------------
- PROTOTYPES
------------------------------------------------------------------------------*/
#ifdef SILO
struct DBfile ;
extern int SourceNew_rdsilo (struct DBfile *idbid );
extern int SourceNew_wtsilo (struct DBfile *idbid );
#endif

struct Domain_s ;

extern Source_t    * Source_construct(int num);
extern SourceNew_t * SourceNew_new(char *name);
extern SourceNew_t * SourceNew_find(char *name, HashTable_t *hash);

extern int SourceNew_gen( void );
extern int SourceNew_input (void);
extern int SourceNew_setattr( SourceNew_t *src );
extern int SourceNew_init( SourceNew_t *src );
extern int SourceNew_setup_attrs(void);
extern int SourceNew_srcoff( void );
extern int SourceNew_showsrc( void );
extern int Source_init(Source_t *ptr);
extern int Source_setup_attrs(void);

extern void Source_merge(struct Domain_s *domain);

extern void SourceNew_packedit( double *buffer, int *len );
extern void SourceNew_unpackedit( double *buffer, int *len );
extern void SourceNew_sumedits( void );
extern void SourceNew_copy(SourceNew_t *src1, SourceNew_t *src2);
extern void SourceNew_free(HashTable_t *hash);
extern void SourceNew_release( SourceNew_t *src);
extern void SourceNew_add( SourceNew_t *src, HashTable_t *hash);
extern void SourceNew_general( double *field, double *weight, char *name, double dtime, struct Domain_s *domain, SourceEditMode_t ifedit);
extern void SourceNew_temperature( double *e, double *t, double *dedt, double *weight, char *name, double dtime, struct Domain_s *domain, SourceEditMode_t ifedit);
extern void SourceNew_energyrate( double *dele, double *weight, char *name, double dtime, double dterate, struct Domain_s *domain, SourceEditMode_t ifedit);
extern void SourceNew_radtemperature( double *phi, double *t, double *weight, char *name, double dtime, struct Domain_s *domain, SourceEditMode_t ifedit);
extern void SourceNew_table (SourceNew_t *src, double *value, double dtime, struct Domain_s *domain);
extern void SourceNew_domain(SourceNew_t *src, struct Domain_s *domain);
extern void SourceNew_getedits(double *src_mass, double *src_e, double *src_xmom, double *src_ymom, double *src_zmom);

#endif

/*------------------------------------------------------------------------------
- GLOBAL VARS
------------------------------------------------------------------------------*/
extern Source_t *src ;

/*******************************************************************************
* END OF FILE
*******************************************************************************/



