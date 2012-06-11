#ifndef BndMapping_H
#define BndMapping_H

/*------------------------------------------------------------------------------
- STRUCTURE
------------------------------------------------------------------------------*/

typedef struct {
   int iblk;               /* block number              */
   int id;                 /* id number                 */
   int imax;               /* max i index within block  */
   int jmax;               /* max j index within block  */
   int kmax;               /* max k index within block  */
   int imin;               /* min i index within block  */
   int jmin;               /* min j index within block  */
   int kmin;               /* min k index within block  */
   int orientation[3];     /* transformation to neighbor's orientation */
   int len;                /* length of index list      */
   int *ndx;               /* index list of boundary    */
} BndMapping_t; 

/*------------------------------------------------------------------------------
- PROTOTYPES
------------------------------------------------------------------------------*/

#endif

/*------------------------------------------------------------------------------
- GLOBAL VARS
------------------------------------------------------------------------------*/

/*******************************************************************************
* END OF FILE
*******************************************************************************/
