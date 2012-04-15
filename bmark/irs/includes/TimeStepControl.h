#ifndef TimeStepControl_H
#define TimeStepControl_H

/*------------------------------------------------------------------------------
- STRUCTURE
------------------------------------------------------------------------------*/

/* RGST_START */

typedef struct {

   char name[256] ;
   char key[32]  ;

   double value ;

   int block ;
   int i ;
   int j ;
   int k ;

} TimeStepControl_t ;

/* RGST_END */

/*------------------------------------------------------------------------------
- PROTOTYPES
------------------------------------------------------------------------------*/
#ifdef SILO
extern void TimeStepControl_wtsilo(DBfile *idbid);
extern void TimeStepControl_rdsilo(DBfile *idbid);
#endif

extern TimeStepControl_t *TimeStepControl_find( char *name, HashTable_t *hash ) ;
extern TimeStepControl_t* TimeStepControl_construct(int num);
extern void TimeStepControl_register(char *name, char *key);
extern void TimeStepControl_add( TimeStepControl_t *tsc, HashTable_t *hash ) ;
extern void TimeStepControl_free( HashTable_t *hash ) ;
extern void TimeStepControl_initialize( void ) ;
extern void TimeStepControl_findmin( char *attr, double *mydeltat ) ;
extern void TimeStepControl_setup_attrs(void);
extern void TimeStepControl_getmin( char *attr, double *mindt );
extern int  TimeStepControl_getvalue( void );
extern int  TimeStepControl_print( void ) ;
extern int  TimeStepControl_init(TimeStepControl_t *tsc);

#endif
/*------------------------------------------------------------------------------
- GLOBAL VARS
------------------------------------------------------------------------------*/

/* general time step limits */

extern double dtmin ;
extern double dtmax ;

/* time step multipliers */

extern double fcrnt   ;
extern double dtfc    ;
extern double dtffc   ;
extern double dtgfc   ;
extern double dtjfc   ;
extern double dtefc   ;
extern double dtifc   ;
extern double dtrfc   ;
extern double dtsefc  ;
extern double dtsifc  ;
extern double dttfc   ;
extern double dtvfc   ;
extern double dtwfc   ;

/* time step offsets */

extern double dtemin  ;
extern double dtimin  ;
extern double dtrmin  ;
extern double dtsemin ;
extern double dtsimin ;
extern double dtwmin ;

/* mixed zone cutoff fraction for time steps */

extern double vfdtmin ;

/* block and zone indices for controling time step */

extern int dtb ;
extern int dti ;
extern int dtj ;
extern int dtk ;

extern char dtcon[MAXWORD] ;

/*******************************************************************************
* END OF FILE
*******************************************************************************/
