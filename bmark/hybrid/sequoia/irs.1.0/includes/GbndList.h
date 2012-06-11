#ifndef GbndList_H
#define GbndList_H

/*------------------------------------------------------------------------------
- DEFINES AND MACROS
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
- STRUCTURE
------------------------------------------------------------------------------*/

/* Temporary grid motion type index list (2d) */

typedef struct {
   int *lstbnd;
   int *ibndx;       /*  IBND index list */
   int *jbndx;       /*  JBND index list */
   int *bbndx;       /*  BOTH index list */
   int *imbndx;      /* -IBND index list */
   int *jmbndx;      /* -JBND index list */
   int *bmbndx;      /* -BOTH index list */
   int nibnd;
   int njbnd;
   int nbbnd;
   int nimbnd;
   int njmbnd;
   int nbmbnd;

} GbndList2d_t ;

/* Temporary grid motion type index list (3d) */

typedef struct {
   int *lstbnd;
   int *ibndx;        /* IBND   index list */
   int *jbndx;        /* JBND   index list */
   int *kbndx;        /* KBND   index list */
   int *ijegndx;      /* IJEDGE index list */
   int *jkegndx;      /* JKEDGE index list */
   int *kiegndx;      /* KIEDGE index list */
   int nibnd;
   int njbnd;
   int nkbnd;
   int nijedge;
   int njkedge;
   int nkiedge;
   int *imbndx;        /* -IBND   index list */
   int *jmbndx;        /* -JBND   index list */
   int *kmbndx;        /* -KBND   index list */
   int *ijmegndx;      /* -IJEDGE index list */
   int *jkmegndx;      /* -JKEDGE index list */
   int *kimegndx;      /* -KIEDGE index list */
   int nimbnd;
   int njmbnd;
   int nkmbnd;
   int nijmedge;
   int njkmedge;
   int nkimedge;
   int *corndx;       /* -CORNER index list */
   int ncorner;

} GbndList3d_t ;

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
