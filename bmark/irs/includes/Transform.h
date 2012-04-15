#ifndef Transform_H
#define Transform_H

/*------------------------------------------------------------------------------
- STRUCTURE
------------------------------------------------------------------------------*/

/* RGST_START */

typedef struct {

   char *name;

   double cent[3];
   double axis[3];
   double norm[3];
   double perp[3];

} Transform_t;

/* RGST_END */

/*------------------------------------------------------------------------------
- PROTOTYPES
------------------------------------------------------------------------------*/
#ifdef SILO
extern int Transform_rdsilo(DBfile *idbid );
extern int Transform_wtsilo(DBfile *idbid) ;
#endif

extern Transform_t* Transform_find(char *name);
extern void Transform_add(char *name, double *mycent, double *myaxis, double *mynorm);
extern void Transform_del(char *name);
extern void Transform_init(Transform_t *trans);
extern void Transform_rt2xyz( double *x, double *y, double *z, double *r, double *t,   
                       int len, Transform_t *trans);
extern void Transform_xyz2rt(double *x, double *y, double *z, double *r, double *t,
                      int len, Transform_t *trans) ;
extern void Transform_getcoord(double *x,double *y,double *z,double *r,double *t,
                        double *p, int *ndx, int len, int array_type,
                        int ifrt, Domain_t *domain, Transform_t *trans);

extern void Transform_settrans(double *cx, double *cy, double *cz,
                        double *ax, double *ay, double *az,
                        double *nx, double *ny, double *nz,
                        double *px, double *py, double *pz,
                        Transform_t *trans) ;
extern void Transform_parse(char *name) ;
extern void Transform_setup_attrs( void );

extern int Transform_setptr(char *name1, char *name2, char *name3, double *p[3],
                     double *x, double *y, double *z,
                     double *r, double *theta, double *phi, double *t);
extern int  Transform_set( int flag );
extern int Transform_free( void );

extern int Transform_getpolar( int mode );

#endif

/*------------------------------------------------------------------------------
- GLOBAL VARS
------------------------------------------------------------------------------*/

/*******************************************************************************
* END OF FILE
*******************************************************************************/
