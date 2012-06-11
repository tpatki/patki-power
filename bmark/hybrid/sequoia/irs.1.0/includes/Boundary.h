#ifndef Boundary_H
#define Boundary_H

/*------------------------------------------------------------------------------
- STRUCTURE
------------------------------------------------------------------------------*/

/* RGST_START */

typedef struct Boundary_s {

   int    active    ;     /* determines if this boundary is active */
   int    blk_send;       /* block number which shirs this boundary */
   int    bndnbc    ;     /* index of recv block's boundary */

   int    encon ;         /* flag for enhanced connectivity */


   int   imin   ;         /* boundary extents */
   int   imax   ;
   int   jmin   ;
   int   jmax   ;
   int   kmin   ;
   int   kmax   ;

   int    orientation[3];  /* transformation to neighbor's orientation */
   int    pn          ;    /* offset to phony node */
   int    pn_vector[3];    /* vector offset to phony node */
   int    rz          ;    /* offset to real zone */
   int    pz          ;    /* offset to phony zone */

   int    len_nsend1;     /* length of first send layer of nodal data */
   int    len_nsend2;     /* length of second send layer of nodal data */
   int    len_nsendc;     /* length of corner send layer of nodal data */
   int    len_nsendtot;   /* sum of above 3 lengths--size of ndx_send array */

   int    len_zsend1;     /* length of first send layer of zonal data */
   int    len_zsend2;     /* length of second send layer of zonal data */
   int    len_zsendc;     /* length of corner send layer of zonal data */
   int    len_zsendtot;   /* sum of above 3 lengths--size of zdx_send array */

   int    len_nrecv1;     /* length of first recv layer of nodal data */
   int    len_nrecv2;     /* length of second recv layer of nodal data */
   int    len_nrecvc;     /* length of corner recv layer of nodal data */
   int    len_nrecvtot;   /* sum of above 3 lengths--size of ndx_recv array */

   int    len_zrecv1;     /* length of first recv layer of zonal data */
   int    len_zrecv2;     /* length of second recv layer of zonal data */
   int    len_zrecvc;     /* length of corner recv layer of zonal data */
   int    len_zrecvtot;   /* sum of above 3 lengths--size of zdx_recv array */

   int    *ndx_send  ;     /* index list of nodes to send per bndry */
			   /* RGST_LEN len_nsendtot */
   int    *zdx_send  ;     /* index list of zones to send per bndry */
			   /* RGST_LEN len_zsendtot */
   int    *ndx_recv  ;     /* index list of nodes to recv per bndry */
			   /* RGST_LEN len_nrecvtot */
   int    *zdx_recv  ;     /* index list of zones to recv per bndry */
			   /* RGST_LEN len_zrecvtot */
   int    *zdx_neighbor;   /* my neighbor's list of real zones */
                           /* RGST_LEN len_zrecvtot */

   int    len_momflxtag;   /* length of momflxtag */
   int    *momflxtag ;     /* flags nodes on bnd have good momflx to recv */
			   /* RGST_LEN len_momflxtag */

   double *buf_acum ;      /* temporary buffer for accumulation */

   int    *buf_int    ;       /* temporary integer buffer */
   double *buf_double ;       /* temporary double buffer */

}  Boundary_t ;

/* RGST_END */


/*------------------------------------------------------------------------------
- PROTOTYPES
------------------------------------------------------------------------------*/
#ifdef SILO
struct DBfile ;
extern int Boundary_pre_read(struct DBfile *idbid, Boundary_t *ptr, char *field);
extern int Boundary_write(struct DBfile *idbid, Boundary_t *ptr, char *field);
#endif

extern int Boundary_setup_attrs(void);

#endif

/*------------------------------------------------------------------------------
- GLOBAL VARS
------------------------------------------------------------------------------*/

/*******************************************************************************
* END OF FILE
*******************************************************************************/
