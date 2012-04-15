#ifndef Extents_H
#define Extents_H

/*------------------------------------------------------------------------------
- DEFINES AND MACROS
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
- STRUCTURE
------------------------------------------------------------------------------*/

typedef struct {

   int imin;
   int imax;
   int jmin;
   int jmax;
   int kmin;
   int kmax;

} Extents_t ;


/*------------------------------------------------------------------------------
- PROTOTYPES
------------------------------------------------------------------------------*/
extern void setgmap(int ublk, Extents_t ext); 
extern void rdtruegrid_mesh(double *x, double *y, double *z, int *node, Extents_t ext, int jp, int kp);
extern void extents_getlogical(Extents_t *ext, int logical, int *min, int *max);
extern void extents_getndx(Extents_t ext, int jp, int kp, int *ndx);
extern void extents_getndx_orient(Extents_t ext, int jp, int kp, int *orient, int *ndx);
extern void extents_setlogical(Extents_t *ext, int logical, int *min, int *max);
extern void extents_shift(Extents_t gext, Extents_t ext, int jp, int kp, int *pn, int dir, Extents_t *extout);
extern void extents_transform(Extents_t ext1, Extents_t ext2, int *orient, Extents_t extin, Extents_t *extout);
extern int extents_aggregate(Extents_t *subext, int nsubext,  Extents_t supext, int flag);
extern int extents_gettype(Extents_t extin);
extern int extents_overlap(Extents_t *ext1, Extents_t *ext2, Extents_t *ext3);
extern int extents_redext(Extents_t *extout, Extents_t extin, int type);
extern int extents_xor(Extents_t ext1, Extents_t ext2, int jp, int kp, int *ndx);

#endif

/*------------------------------------------------------------------------------
- GLOBAL VARS
------------------------------------------------------------------------------*/

/*******************************************************************************
* END OF FILE
*******************************************************************************/
