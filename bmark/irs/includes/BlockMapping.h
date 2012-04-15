#ifndef BlockMapping_H
#define BlockMapping_H

#include "BndMapping.h"

/*------------------------------------------------------------------------------
- STRUCTURE
------------------------------------------------------------------------------*/
typedef struct BlockMapping_s {
   int proc;               /* processor number                             */
   int gblk;               /* global block number                          */
   int lblk;               /* local block number                           */
   int ublk;               /* user block number                            */
   int imax;               /* max i index within user block                */
   int jmax;               /* max j index within user block                */
   int kmax;               /* max k index within user block                */
   int imin;               /* min i index within user block                */
   int jmin;               /* min j index within user block                */
   int kmin;               /* min k index within user block                */
   int jp;                 /* j stride                                     */
   int kp;                 /* k stride                                     */
   int nbnd;               /* number of boundaries shared by this block    */
   BndMapping_t *bnd;      /* map of boundary                              */

} BlockMapping_t;


/*------------------------------------------------------------------------------
- PROTOTYPES
------------------------------------------------------------------------------*/
extern void printmapping(BlockMapping_t *map);
extern int rdtruegrid_decomp(BlockMapping_t *map, int startblk, int ndlistflg, int *num_blocks);

#endif

/*------------------------------------------------------------------------------
- GLOBAL VARS
------------------------------------------------------------------------------*/

/* global blk mapping */

extern BlockMapping_t *gmap;

extern int gnblk ;		/* The total number of domains in the problem.
                       		This could span multiple user blocks.
                       		This will be
			 	>= unblk, since the blkdiv command can be
			   	used to split user blocks into multiple
			     	global blocks */

/* user blk mapping */

extern BlockMapping_t *umap;

extern int unblk ;	/* The number of user-specified blocks */

/*******************************************************************************
* END OF FILE
*******************************************************************************/
