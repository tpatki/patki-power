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
void TimeStepControl_wtsilo(DBfile *idbid);
void TimeStepControl_rdsilo(DBfile *idbid);
#endif

TimeStepControl_t *TimeStepControl_find( char *name, HashTable_t *hash ) ;
TimeStepControl_t* TimeStepControl_construct(int num);
void TimeStepControl_register(char *name, char *key);
void TimeStepControl_add( TimeStepControl_t *tsc, HashTable_t *hash ) ;
void TimeStepControl_free( HashTable_t *hash ) ;
void TimeStepControl_initialize( void ) ;
void TimeStepControl_findmin( char *attr, double *mydeltat ) ;
void TimeStepControl_setup_attrs(void);
void TimeStepControl_getmin( char *attr, double *mindt );
int  TimeStepControl_getvalue( void );
int  TimeStepControl_print( void ) ;
int  TimeStepControl_init(TimeStepControl_t *tsc);

#endif
/*------------------------------------------------------------------------------
- GLOBAL VARS
------------------------------------------------------------------------------*/

/* general time step limits */

double dtmin ;
double dtmax ;

/* time step multipliers */

double fcrnt   ;
double dtfc    ;
double dtffc   ;
double dtgfc   ;
double dtjfc   ;
double dtefc   ;
double dtifc   ;
double dtrfc   ;
double dtsefc  ;
double dtsifc  ;
double dttfc   ;
double dtvfc   ;
double dtwfc   ;

/* time step offsets */

double dtemin  ;
double dtimin  ;
double dtrmin  ;
double dtsemin ;
double dtsimin ;
double dtwmin ;

/* mixed zone cutoff fraction for time steps */

double vfdtmin ;

/* block and zone indices for controling time step */

int dtb ;
int dti ;
int dtj ;
int dtk ;

char dtcon[MAXWORD] ;

/*******************************************************************************
* END OF FILE
*******************************************************************************/
