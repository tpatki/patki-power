#ifndef AEStackElm_H
#define AEStackElm_H

#include "Rgst.h"

/*------------------------------------------------------------------------------
- DEFINES AND MACROS
------------------------------------------------------------------------------*/

#define RGST_Attribute_t_STR      "RGST_Attribute_t"

#define GETCOMMA() \
  { char msym[MAXWORD]; \
    char mmsg[MAXLINE]; \
    peekc(msym); \
    if (msym[0] == ',') geta(msym); \
  }

/*------------------------------------------------------------------------------
- STRUCTURE
------------------------------------------------------------------------------*/
typedef struct AEStackElm_s {

   char *          routine; /* Name of routine which placed item on the stack */
   RGST_Datatype_t type;    /* R_INT, R_DOUBLE,  R_INT_ARRAY, R_DOUBLE_ARRAY,
                               or R_CHAR if this is a marker created by
                               ae_stack_mark */
   int             nval;    /* Count of number of values placed on stack
                               for a given routine.  First item is 1.  Can be
                               used to see if there are more items for the
                               previous function still on the stack waiting
                               to be popped. */
   int             i_value; /* if type is R_INT */
   int            *i_array; /* if type is R_INT_ARRAY */
   double          d_value; /* if type is R_DOUBLE */
   double         *d_array; /* if type is R_DOUBLE_ARRAY */
   int             len;     /* length of i_array or d_array arrays */

   char           *label;   /* if data has a label, it will be stored here
                               if type is R_CHAR (ie ae_stack_mark) then the
                               name of the function placing items on the stack
                               will be stored here */
   
   struct AEStackElm_s      *next, /* Links to next and prev items in linked list */
                            *prev; /* that forms the stack */

} AEStackElm_t; 

/*------------------------------------------------------------------------------
- PROTOTYPES
------------------------------------------------------------------------------*/
extern AEStackElm_t * AEStackElm_construct(int num);
extern AEStackElm_t * AEStackElm_destruct(AEStackElm_t *ptr);
extern AEStackElm_t * AEStack_pop(void);
extern AEStackElm_t * ae_stack_pop(void);

extern int      AEStackElm_init(AEStackElm_t *ptr);
extern int      AEStack_push(AEStackElm_t *ptr);
extern int      ae_stack_num_vals(char *routine);
extern int      ae_stack_pop_int(void);
extern int      ae_stack_push(char *routine, char *label, RGST_Datatype_t type, ...);
extern void     ae_stack_empty_check(void);
extern double   ae_stack_pop_dbl(void);

extern int    * ae_stack_pop_int_array(void);
extern double * ae_stack_pop_dbl_array(void);

#endif
/*------------------------------------------------------------------------------
- GLOBAL VARS
------------------------------------------------------------------------------*/
extern AEStackElm_t *gv_ae_stack_bottom;   /* HH_INIT NULL */
extern AEStackElm_t *gv_ae_stack_top;      /* HH_INIT NULL */

/*******************************************************************************
* END OF FILE
*******************************************************************************/

#ifndef BiQuadradic_H
#define BiQuadradic_H

/*------------------------------------------------------------------------------
- STRUCTURE
------------------------------------------------------------------------------*/

/* RGST_START */

typedef struct {

   int neos ;
   int nt ;
   int nr ;
   double *tgrid ;
   double *rgrid ;
   int ntab ;
   double *ftab ;

} BiQuadradic_t ;


/* RGST_END */

/*------------------------------------------------------------------------------
- PROTOTYPES
------------------------------------------------------------------------------*/
extern void tabin(BiQuadradic_t *xtab, char *tabname, char *fldname, char *sclname, int num);

#endif

/*------------------------------------------------------------------------------
- GLOBAL VARS
------------------------------------------------------------------------------*/
extern BiQuadradic_t *ptab ;	/* HH_INIT NULL */
extern BiQuadradic_t *etab ;	/* HH_INIT NULL */
extern BiQuadradic_t *ktab ;	/* HH_INIT NULL */
extern BiQuadradic_t *stab ;	/* HH_INIT NULL */

/*******************************************************************************
* END OF FILE
*******************************************************************************/
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
#ifndef Bndlist_H
#define Bndlist_H

#include "pint.h"

/*-----------------------------------------------------------------------------
- Structure
------------------------------------------------------------------------------*/
typedef struct {

   pint *zndx ;

} Bndlist_t ;

/*------------------------------------------------------------------------------
- PROTOTYPES
------------------------------------------------------------------------------*/

#endif

/*------------------------------------------------------------------------------
- GLOBAL VARS
------------------------------------------------------------------------------*/
extern Bndlist_t *bnddat; /* HH_INIT NULL */


/*******************************************************************************
* END OF FILE
*******************************************************************************/
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
#ifndef BoundaryCondition_H
#define BoundaryCondition_H

/* RGST_START */

#include "irsdefs.h"

/* RGST_END */

/*------------------------------------------------------------------------------
- STRUCTURE
------------------------------------------------------------------------------*/

/* RGST_START */

typedef struct {

   char   ndxName[MAXLINE]; /* name of ndxlist */

   int    type  ;           /* type of boundary condition */
   int    rtype ;           /* radiation boundary type */
   int    mode  ;
   int    *ndx  ;           /* RGST_LEN len */
                            /* index list of boundary nodes */
   int    len   ;           /* length of index list */
   int   *zonelist;         /* RGST_LEN lenZonelist */
                            /* list of boundary zones */
   int    lenZonelist;      /* length of zonelist*/

   int    pn    ;           /* offset to phony nodes */
   int    rz    ;           /* offset to real zones */
   int    pz    ;           /* offset to phony zones */

   double nx    ;           /* x normal */
   double ny    ;           /* y normal */
   double nz    ;           /* z normal */

   int    id    ;       /* vsame id */
   int    ngrp  ;       /* number of groups for vsame summing */
   int    lgrp  ;       /* length of each group */

}  BoundaryCondition_t ;

/* RGST_END */


/*------------------------------------------------------------------------------
- PROTOTYPES
------------------------------------------------------------------------------*/
struct Domain_s ;

extern int  BoundaryCondition_init(BoundaryCondition_t *ptr);
extern int  BoundaryCondition_setup_attrs(void);
extern void BoundaryCondition_merge(struct Domain_s *domain);

#endif
/*------------------------------------------------------------------------------
- GLOBAL VARS
------------------------------------------------------------------------------*/

/*******************************************************************************
* END OF FILE
*******************************************************************************/
#ifndef Combuffer_H
#define Combuffer_H

#include "FunctionTimer.h"

/*------------------------------------------------------------------------------
- DEFINES AND MACROS
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
- STRUCTURE
------------------------------------------------------------------------------*/

typedef struct {

   int bufnum;              /* number of this communications buffer */

   char bufname[MAXWORD];   /* name of this communications buffer */

   int *proc;               /* mapping of processor number to individual
                                    buffer number */

   int size;                /* number of individual buffers */

   int *len_sendi;          /* length of the integer send buffers */
   int *len_sendd;          /* length of the double send buffers  */
   int *len_recvi;          /* length of the integer recv buffers */
   int *len_recvd;          /* length of the double recv buffers  */

   int **sendi_buf;         /* pointer to integer send buffer     */
   int **sendi_ptr;         /* pointer into integer send buffer   */
   int **recvi_buf;         /* pointer to integer recv buffer     */
   int **recvi_ptr;         /* pointer into integer recv buffer   */


   double **sendd_buf;      /* pointer to double send buffer      */
   double **sendd_ptr;      /* pointer into double send buffer    */
   double **recvd_buf;      /* pointer to double recv buffer      */
   double **recvd_ptr;      /* pointer into double recv buffer    */

   int **blk_order;         /* pointer to block order of buffer packing */
   int **tag_order;         /* pointer to bc order of buffer packing    */
   int  *len_order;         /* length of order arrays                   */
   int  len_order_send;     /* length of send portion of order arrays   */

   double starttime;        /* start timer                    */
   double *comtimer;        /* accumulated time for each call */

   int mesgtag;             /* message tag for messages sent with this buffer */
   MPI_Request* send_request;  /* array of requests for sends  */
   MPI_Request* recv_request;  /* array of requests for recv's */

   MPI_Status* send_status;    /* array of status (or stati) for sends  */
   MPI_Status* recv_status;    /* array of status (or stati) for recv'c */

   MPI_Comm* comm;              /* communicator used with this buffer    */

} Combuffer_t;

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
#ifndef Command_H
#define Command_H

/*------------------------------------------------------------------------------
- STRUCTURE
------------------------------------------------------------------------------*/

typedef struct Command_s {

  char *name;
  int arg;
  int (*proc)();
  int (*handler)(struct Command_s *);

} Command_t ;


/*------------------------------------------------------------------------------
- PROTOTYPES
------------------------------------------------------------------------------*/
extern Command_t * build_proc_name(char *struct_name, char *procedure_suffix, char *routine_name);
extern int sargs(Command_t *cp);
extern int sargse(Command_t *cp);
extern int zargs(Command_t *cp);
extern int zargse(Command_t *cp);
extern void rgst_print_function(Command_t *cp);

#endif

/*------------------------------------------------------------------------------
- GLOBAL VARS
------------------------------------------------------------------------------*/

/*******************************************************************************
* END OF FILE
*******************************************************************************/
#ifndef Conditional_H
#define Conditional_H

/*------------------------------------------------------------------------------
- DEFINES AND MACROS
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
- STRUCTURE
------------------------------------------------------------------------------*/

/* RGST_START */

typedef struct Conditional_s {

   int   id;
   int   once;
   int   active;
   int   expression_len;
   int   msg_len;

   char *expression;           /* RGST_LEN expression_len */
   char *msg;                  /* RGST_LEN msg_len */

   struct Conditional_s *next;
   
} Conditional_t;

/* RGST_END */

/*------------------------------------------------------------------------------
- PROTOTYPES
------------------------------------------------------------------------------*/
#ifdef SILO
struct DBfile ;
extern void conditionals_rdsilo(struct DBfile *idbid);
extern void conditionals_wtsilo(struct DBfile *idbid);
#endif

extern Conditional_t * Conditional_construct(int num);
extern int Conditional_init(Conditional_t *ptr);
extern int Conditional_setup_attrs(void);
extern void conditionals_add(Conditional_t *cond);
extern void conditionals_free(void);
extern int conditionals_atexit(void);
extern int conditionals_check(void);
extern int conditionals_del(int num);
extern int conditionals_endif(void);
extern int conditionals_eval(void);
extern int conditionals_if(void);
extern int conditionals_input(int mode);
extern int conditionals_redo(int num);
extern int conditionals_show(int num, char * *msgout, int *msglen);

/*------------------------------------------------------------------------------
- GLOBAL VARS
------------------------------------------------------------------------------*/

#endif
/*******************************************************************************
*                              END OF FILE
*******************************************************************************/
#ifndef CycleMesg_H
#define CycleMesg_H

/*------------------------------------------------------------------------------
- DEFINES AND MACROS
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
- STRUCTURE
------------------------------------------------------------------------------*/

/* RGST_START */

typedef struct {
   char *name;          /* unique name for this cycle frequency data struct */
   int  cyctp;
   int  c1;             /* stop cycle */
   int  c2;             /* stop cycle */
   int  dc;             /* cycle step (aka delta cycle) */
   int  nextCycle;      /* next cycle at which to take action */
   char *msg;
   int  msglen;

} CycleMesg_t ;

/* RGST_END */

/*------------------------------------------------------------------------------
- PROTOTYPES
------------------------------------------------------------------------------*/
extern void printcyclefreq(CycleMesg_t *fq);

#endif

/*------------------------------------------------------------------------------
- GLOBAL VARS
------------------------------------------------------------------------------*/
extern int ncyc ;
extern int maxcycleplot ;
extern CycleMesg_t *cyc; /* Array of size ncycx of cycle frequencies */
extern int *cyctp;       /* Array of size ncycx of ints.
                            If a frequency is used to generate a versus-time
                            edit, then this index will be 0 or greater and
                            is used to index into the cyc[] array.  If the
                            frequency is used for purposes other than versus-
                            time edits (time plots), then the index will
                            be set to -1 */


/*******************************************************************************
* END OF FILE
*******************************************************************************/
#ifndef DiffusionData_H
#define DiffusionData_H

/*------------------------------------------------------------------------------
- DEFINES AND MACROS
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
- STRUCTURE
------------------------------------------------------------------------------*/

typedef struct {

  double *phi    ;
  double *dphi   ;
  double *adphi  ;
  double *rhs    ;
  double *esrc   ;
  double *flmt   ;
  double *phim   ;
  double *xplnk  ;
  double *kie    ;
  double *alpha  ;
  double *beta   ;
  double *gamma  ;
  double *rcm3t  ;
  double *diffcl ;
  double *diffcr ;
  double *diffcb ;
  double *diffcf ;
  double *diffcd ;
  double *diffcu ;

} DiffusionData_t ;

/*------------------------------------------------------------------------------
- PROTOTYPES
------------------------------------------------------------------------------*/

#endif

/*------------------------------------------------------------------------------
- GLOBAL VARS
------------------------------------------------------------------------------*/

/* tdiff Radiation flux/data structures */

extern DiffusionData_t *tblk ;


/*******************************************************************************
* END OF FILE
*******************************************************************************/
#ifndef Domain_H
#define Domain_H

/* RGST_START */
#include "irsdefs.h"
#include "pint.h"
#include "Hash.h"
#include "SpeciesFraction.h"
#include "Source.h"
#include "BoundaryCondition.h"
#include "Boundary.h"
/* RGST_END */


/*------------------------------------------------------------------------------
- RegionTable structure
------------------------------------------------------------------------------*/

/* RGST_START */

typedef struct {

  double *zstar;              /* effective ionization state */
  double *z;                  /* average atomic number */
  double *a;                  /* average atomic mass */
  double *massFrac;           /* mass fraction of the group */
  double *atomFrac;           /* atomic fraction of the group */
  double *chemicalPotential;  /* chemical potential for the group */
  double *dscl  ;             /* density     scale factor */
  double *escl  ;             /* energy      scale factor */
  double *pscl  ;             /* pressure    scale factor */
  double *tscl  ;             /* temperature scale factor */

  /* all arrays have a length of number of zones with this region */
   
} RegionTable_t;


/* RGST_END */

/*------------------------------------------------------------------------------
- DomainRegion structure
------------------------------------------------------------------------------*/

/* RGST_START */

typedef struct {
   
  RegionTable_t *regionTables;
  
} DomainRegion_t;

/* RGST_END */

/*------------------------------------------------------------------------------
- Domain structure
------------------------------------------------------------------------------*/

/* RGST_START */

#define NTAB_RAN2   32

typedef struct Domain_s {
   int gblk   ;	
   int type   ;
   int imin   ;	
   int jmin   ; 
   int kmin   ; 
   int imax   ; 
   int jmax   ;
   int kmax   ; 
   int nnalls ;
   int nnodes ;
   int namix  ;
   int mixmax ;
   int nmixcnt;
   int imaxmix;
   int nmixzn ;
   int nzones ;	
   int namixgx;
   int jp     ;
   int kp     ;
   int fpn    ;
   int lpn    ;
   int fpz    ;
   int lpz    ;
   int frn    ;
   int lrn    ;
   int frz    ;
   int lrz    ;
   int    timerLevel ;       /* HH_INIT 0 */
   double cpu_secs;    	    /* HH_INIT 0.0 */
   double wall_secs;        /* HH_INIT 0.0 */
   double flops;    	    /* HH_INIT 0.0 */
   double load ;           
   double sclnamix ;
   double ndeltat ;
   double dtg   ;
   char   dtcon ;
   int    dti   ;
   int    dtj   ;
   int    dtk   ;
   int    *ireg   ;  /* RGST_LEN namix */
   double *x      ;  /* RGST_LEN nnodes */
   double *y      ;  /* RGST_LEN nnodes */
   double *z      ;  /* RGST_LEN nnodes */
   double *xdot   ;  /* RGST_LEN nnodes */
   double *ydot   ;  /* RGST_LEN nnodes */
   double *zdot   ;  /* RGST_LEN nnodes */
   double *den    ;  /* RGST_LEN namix */
   double *emat   ;  /* RGST_LEN namix */
   double *eion   ;  /* RGST_LEN namix */
   double *e_cold ;  /* RGST_LEN namix */
   double *eden   ;  /* RGST_LEN namix */
   double *tke    ;  /* RGST_LEN namix */
   double *tmat   ;  /* RGST_LEN namix */
   double *tion   ;  /* RGST_LEN namix */
   double *dedt   ;  /* RGST_LEN namix */
   double *deidt  ;  /* RGST_LEN namix */
   double *trad   ;  /* RGST_LEN namix */
   double *erad   ;  /* RGST_LEN namix */
   double *p      ;  /* RGST_LEN namix */
   double *pion   ;  /* RGST_LEN namix */
   double *p_cold ;  /* RGST_LEN namix */
   double *cs2    ;  /* RGST_LEN namix */
   double *work1  ;  /* RGST_LEN namix */
   double *work2  ;  /* RGST_LEN namix */
   double *area   ;  /* RGST_LEN namix */
   double *vol    ;  /* RGST_LEN namix */
   double *zmass  ;  /* RGST_LEN namix */
   double *nmass  ;  /* RGST_LEN nnodes */
   double *work3  ;  /* RGST_LEN namix */
   double *work4  ;  /* RGST_LEN namix */
   double *eosvf  ;
   double *eosef  ;
   double *eoseif ;
   double *invLengthSqr;
   double *ematsrc     ;
   double *eionsrc     ;
   double *tmat_extrap ;
   double *tion_extrap ;
   double *kros   ;  /* RGST_LEN namix */
   double *kplnk  ;  /* RGST_LEN namix */
   double *zstar  ;  /* RGST_LEN namix */
   double *tmatold ;
   double *tionold ;
   double *eradold ;
   double *phi    ;
   double *omegasq;  /* RGST_LEN namix */
   double *delx    ;
   double *dely    ;
   double *delz    ;
   double *delnorm ;
   int    *node    ;
   HashTable_t  *hash;
   int  *rlen    ;      /* RGST_LEN nregxplus1 */
   int  *rlencln ;	/* RGST_LEN nregxplus1 */
   int  *rlenmix ;	/* RGST_LEN nregxplus1 */
   pint *rndx    ;	/* RGST_LEN nregxplus1 */
   int  *nmatlst ;      /* RGST_LEN namix */
   pint *rndxmix ;	/* RGST_LEN nregxplus1 */
   pint *rgrdmix ;	/* RGST_LEN nregxplus1 */
   pint *rmixzn  ;	/* RGST_LEN nregxplus1 */
   int  *grdmix  ;	/* RGST_LEN mixmax */
   int  *mixzn   ;	/* RGST_LEN mixmax */
   int  *lnkmix  ;      /* RGST_LEN mixmax */
   int  *grdpnt  ;      /* RGST_LEN mixmax */
   int  *grdzn   ;      /* RGST_LEN mixmax */
   SpeciesFraction_t *specfrac; 
   SpeciesFraction_t *specfrach;
   int     nsrc    ; 
   Source_t *src     ; /* RGST_LEN nsrc */
   int    phonlen  ;     
   int    *phondx  ;  /* RGST_LEN phonlen */
   int    *bndndx  ;  /* RGST_LEN phonlen */
   int    *phonbc  ;  /* RGST_LEN phonlen */
   int    phozlen  ;     
   int    *phozdx  ; /* RGST_LEN phozlen */
   int    *bndzdx  ; /* RGST_LEN phozlen */
   int     rphonlen ;    
   int    *rphondx  ;  /* RGST_LEN rphonlen */
   int    *rbndndx  ;  /* RGST_LEN rphonlen */
   int    *rphonbc  ;  /* RGST_LEN rphonlen */
   int     rphozlen ;  
   int    *rphozdx  ;  /* RGST_LEN rphozlen */
   int    *rbndzdx  ; /* RGST_LEN rphozlen */
   int     nbc     ;      
   BoundaryCondition_t *bc ; /* RGST_LEN nbc */
   int     *msgflag ;    
   int     nbnd     ;   
   Boundary_t *bnd     ; /* RGST_LEN nbnd */
   Boundary_t *mbnd     ; /* RGST_LEN nbnd */
   Boundary_t *sldbnd  ; /* RGST_LEN nbnd */
   DomainRegion_t *domainRegions;

} Domain_t ;

/* RGST END */

/*------------------------------------------------------------------------------
- PROTOTYPES
------------------------------------------------------------------------------*/

#ifdef SILO
struct DBfile ;
extern int Domain_post_read(struct DBfile *idbid, Domain_t *domain, char *field_name);
extern int Domain_pre_read(struct DBfile *idbid, Domain_t *domain, char *field_name);
extern int Domain_write(struct DBfile *idbid, Domain_t *domain, char *field_name);
#endif

extern Domain_t * Domain_construct(int num);

extern int Domain_init(Domain_t *ptr);
extern int Domain_setup_attrs(void);

extern int domain_hash_tbl_rgst(Domain_t *domain);

#endif

/*------------------------------------------------------------------------------
- GLOBAL VARS
------------------------------------------------------------------------------*/

/*******************************************************************************
* END OF FILE
*******************************************************************************/
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
#ifndef FreqMesg_H
#define FreqMesg_H

/*------------------------------------------------------------------------------
- DEFINES AND MACROS
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
- STRUCTURE
------------------------------------------------------------------------------*/

/* RGST_START */

typedef struct {
   char   *name;        /* unique name for this time frequency data struct */
   int    fqtp;
   double t1;           /* start time   */
   double t2;           /* stop time    */
   double dt;           /* time step (aka delta time) */
   double nextTime;     /* next time at which to take action */
   char   *msg;
   int    msglen;

} FreqMesg_t ;

/* RGST_END */


/*------------------------------------------------------------------------------
- PROTOTYPES
------------------------------------------------------------------------------*/
extern void printtimefreq(FreqMesg_t *fq);

#endif

/*------------------------------------------------------------------------------
- GLOBAL VARS
------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------
- time frequency arrays
------------------------------------------------------------------------------*/
extern int nfq ;
extern FreqMesg_t *fq;   /* Array of size nfqx of time frequencies */
extern int *fqtp;        /* Array of size nfqx of ints.
                            If a frequency is used to generate a versus-time
                            edit, then this index will be 0 or greater and
                            is used to index into the fq[] array.  If the
                            frequency is used for purposes other than versus-
                            time edits (time plots), then the index will
                            be set to -1 */

/*******************************************************************************
* END OF FILE
*******************************************************************************/
#ifndef  FunctionTimer_H
#define  FunctionTimer_H

#ifdef TFLOPS
#include <nx.h>
#endif

#include <time.h>
#include <sys/times.h>
#include <stdio.h>

#include "irsdefs.h"
#include "Hash.h"

/*------------------------------------------------------------------------------
- MPI stuff
------------------------------------------------------------------------------*/

        /*----------------------------------------------------------------------
        - If compiling with mpi, then include the mpi header file
        - otherwise define some mpi stuff so that the code will compile properly 
        - even without the mpi library.
        ----------------------------------------------------------------------*/
#ifdef COMMPI

#define __MPIO_INCLUDE
#include <mpi.h>
#undef __MPIO_INCLUDE

#else

typedef int MPI_Status ;
typedef int MPI_Request ;
typedef int MPI_Op ;
typedef int MPI_Datatype ;
typedef int MPI_Comm ;
typedef int MPI_Group ;

extern  MPI_Request  MPI_REQUEST_NULL ;
extern  MPI_Datatype MPI_DOUBLE ;
extern  MPI_Datatype MPI_CHAR;
extern  MPI_Datatype MPI_INT ;
extern  MPI_Comm     MPI_COMM_WORLD ;
extern  MPI_Op       MPI_SUM  ;
extern  MPI_Op       MPI_MIN  ;
extern  MPI_Op       MPI_MAX  ;

#define MPI_UNDEFINED -32766
#define MPI_SUCCESS     0

#define NO_MPI  -999    /* define return value for failure to find MPI */
                        /* can't be valid return value in mpi.h */

#endif                           

/*------------------------------------------------------------------------------
- DEFINES AND MACROS
------------------------------------------------------------------------------*/
#define STRLEN 256

#define TIMER_START     0
#define TIMER_STOP      1

#define FINALIZED       0
#define INITIALIZED     1

#ifndef FREEMEM
#define FREEMEM(iptr) if (iptr != NULL) { free(iptr); iptr = NULL; }
#endif

#ifndef ALLOT
#define ALLOT(a,b)  (a *) calloc(b,sizeof(a))
#endif

#ifndef REALLOT
#define REALLOT(a,b,c)  (b *) realloc(a,(c)*sizeof(b))
#endif

#define ALL_CNTRS       0
#define TOTAL_CNTR      1

        /*-----------------------------------------------------------------------
        - Timers can be compiled in only if -DFUNCTION_TIMERS is specified
        -----------------------------------------------------------------------*/
#ifdef FUNCTION_TIMERS 
#define FT_INITIALIZE(m_name, m_ht)        FunctionTimer_initialize(m_name, m_ht);
#define FT_FINALIZE(m_name, m_ht, m_flops) FunctionTimer_finalize(m_name, m_ht, m_flops);
#else
#define FT_INITIALIZE(m_name, m_ht)        
#define FT_FINALIZE(m_name, m_ht, m_flops)
#endif

/*------------------------------------------------------------------------------
- STRUCTURES
------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
- Enumerated Types
-
- One for each mpi routine for which wrappers have been written
-----------------------------------------------------------------------------*/
typedef enum {
   MPI_Abort_cntr,      MPI_Allgather_cntr, MPI_Allgatherv_cntr, 
   MPI_Allreduce_cntr,
   MPI_Barrier_cntr,    MPI_Bcast_cntr,     MPI_Comm_create_cntr, 
   MPI_Comm_group_cntr, MPI_Comm_rank_cntr, MPI_Comm_size_cntr,  
   MPI_Finalize_cntr,   MPI_Gather_cntr,    MPI_Gatherv_cntr,
   MPI_Group_incl_cntr, MPI_Init_cntr,
   MPI_Irecv_cntr,      MPI_Isend_cntr,     MPI_Recv_cntr,       
   MPI_Reduce_cntr,     MPI_Send_cntr,      MPI_Waitall_cntr,     
   MPI_Waitany_cntr,    MPI_Wait_cntr,      MPI_Wtick_cntr,      
   MPI_Wtime_cntr,      MPI_Total_cntr,
   MPI_num_routines 
}  MPI_ROUTINES_t;

/* RGST_START */

#define FT_NAMELEN		128

typedef struct FunctionTimer_s {

   char   name[FT_NAMELEN];             /* name of timer - should be function name also */

   double cntr;                         /* number of times this timer was started */
   double cpu_secs;
   double wall_secs;

   double flops;                        /* flops just for this routine */
   double agg_flops;                    /* flops for this routine and all */
                                        /* routines called underneath this routine */
   double agg_flops_start;              /* used to calculate above agg_flops */

   double *agg_thr_flops_start;         /* RGST_LEN agg_thr_flops_start_len */
                                        /* used to calculate above agg_flops */
   int     agg_thr_flops_start_len;     /* length of above array */

   double top_cpu_secs;
   double top_wall_secs;
   double top_agg_flops;

   double times_start;         		/* wall times when timer starts */
   double times_stop;          		/* wall times when timer stops */

   double clock_start;	       		/* cpu clocks when timer starts */ 
   double clock_stop;          		/* cpu clocks when timer stops */

   int clock_rolls_start;  		/* Number of clock rolls when timer started */
   int clock_rolls_stop;   		/* number of clock rolls when timer stopped */

   int level;
   int setflag;

} FunctionTimer_t ;

/* RGST_END */


/*------------------------------------------------------------------------------
- PROTOTYPES
------------------------------------------------------------------------------*/
#ifdef SILO
struct DBfile ;
extern void FunctionTimer_rdsilo        (struct DBfile *idbid, HashTable_t *my_hash_tbl);
extern void FunctionTimer_wtsilo        (struct DBfile *idbid, HashTable_t *my_hash_tbl);
#endif

extern void mpi_reset_cntrs	(int cycle);
extern int  timers_file         (void);
extern int  timers_stdout       (void);
extern int  timers_print        (FILE *fp);
extern int test_clockroll       (int rolls, HashTable_t *);

extern void FunctionTimer_maxclock      (double *max, double *min);
extern void FunctionTimer_clock		(int flag,  FunctionTimer_t *fts);
extern void FunctionTimer_initialize	(char *name,  HashTable_t *ht);
extern void FunctionTimer_finalize	(char *name,  HashTable_t *ht, double flops);
extern void FunctionTimer_free		(HashTable_t *ht);
extern void FunctionTimer_print		(FILE *fp, int wall_sort, int cpu_sort, int flops_sort, HashTable_t *ht);
extern void FunctionTimer_out           (FILE *fp, char *fn_name, char *label, int indent, double frac);
extern void FunctionTimer_cpuse         (FILE *fp, int sort_field_flag, int max_field_flag);
extern void FunctionTimer_error         (char proc_name[], char msg[]);
extern void FunctionTimer_init	        (FunctionTimer_t *ptr);
extern void FunctionTimer_warning       (char proc_name[], char msg[]);
extern void FunctionTimer_ht_update     (HashTable_t *old_ht, HashTable_t *new_ht);

extern int  FunctionTimer_ht_setup	(HashTable_t *ht,  char *type);
extern int  FunctionTimer_ht_remove	(HashTable_t *ht,  char *type);
extern int  FunctionTimer_setup_attrs(void);

extern int  FunctionTimer_global_gather (char *name, double **flops, double **cpu_secs, double **wall_secs, double **cntr);
extern int  FunctionTimer_thread_gather (char *name, double **flops, double **cpu_secs, double **wall_secs, double **cntr,  int **gblks);

extern FunctionTimer_t *FunctionTimer_construct	(int num);
extern FunctionTimer_t *FunctionTimer_lookup	(char *name,  HashTable_t *ht);

extern int 	MPI_Init_Wrapper	(int *argc, char ***argv);
extern int 	MPI_Abort_Wrapper	(MPI_Comm comm, int errorcode);
extern int 	MPI_Barrier_Wrapper	(MPI_Comm comm);
extern int 	MPI_Finalize_Wrapper	(void);
extern int 	MPI_Comm_group_Wrapper	(MPI_Comm comm, MPI_Group *group);
extern int 	MPI_Group_incl_Wrapper	(MPI_Group group, int n, int *ranks, MPI_Group *newgroup);
extern int 	MPI_Comm_create_Wrapper	(MPI_Comm comm, MPI_Group group, MPI_Comm *newcomm);
extern int 	MPI_Gather_Wrapper	(void* sendbuf, int sendcount, MPI_Datatype sendtype, void* recvbuf, int recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm);
extern int 	MPI_Gatherv_Wrapper	(void* sendbuf, int sendcount, MPI_Datatype sendtype, void* recvbuf, int *recvcount, int *recvdisp, MPI_Datatype recvtype, int root, MPI_Comm comm);
extern int 	MPI_Allgather_Wrapper	(void* sendbuf, int sendcount, MPI_Datatype sendtype, void* recvbuf, int recvcount, MPI_Datatype recvtype, MPI_Comm comm);
extern int 	MPI_Allgatherv_Wrapper	(void* sendbuf, int sendcount, MPI_Datatype sendtype, void* recvbuf, int *recvcount, int *recvdisp, MPI_Datatype recvtype, MPI_Comm comm);
extern int 	MPI_Bcast_Wrapper	(void* buffer, int count, MPI_Datatype datatype, int root, MPI_Comm comm );
extern int 	MPI_Send_Wrapper	(void* buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm);
extern int 	MPI_Recv_Wrapper	(void* buf, int count, MPI_Datatype datatype, int source, int tag, MPI_Comm comm, MPI_Status *status);
extern int 	MPI_Isend_Wrapper	(void* buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request *request);
extern int 	MPI_Irecv_Wrapper	(void* buf, int count, MPI_Datatype datatype, int source, int tag, MPI_Comm comm, MPI_Request *request);
extern int 	MPI_Wait_Wrapper	(MPI_Request *request, MPI_Status *status);
extern int 	MPI_Waitall_Wrapper	(int count, MPI_Request *array_of_requests, MPI_Status *array_of_status);
extern int 	MPI_Waitany_Wrapper	(int count, MPI_Request *array_of_requests, int *index, MPI_Status *status);
extern int 	MPI_Comm_size_Wrapper	(MPI_Comm comm, int *size);
extern int 	MPI_Comm_rank_Wrapper	(MPI_Comm comm, int *rank);
extern int 	MPI_Allreduce_Wrapper	(void* sendbuf, void* recvbuf, int count, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm);
extern int 	MPI_Reduce_Wrapper	(void* sendbuf, void* recvbuf, int count, MPI_Datatype datatype, MPI_Op op, int root, MPI_Comm comm);
extern double 	MPI_Wtime_Wrapper	(void);
extern double 	MPI_Wtick_Wrapper	(void);


#endif
/*------------------------------------------------------------------------------
- GLOBAL VARS
------------------------------------------------------------------------------*/

#ifdef SILO
struct DBfile ;
extern void FunctionTimer_wtglobals   (struct DBfile *idbid);
extern void FunctionTimer_rdglobals   (struct DBfile *idbid);
#endif

extern double ft_maxclock;      /* max value of clock_t type */
extern double ft_minclock;	/* min value of clock_t type */

extern int debug_switch;

extern int ft_timersflag;	/* Set to FALSE to not use timers */

extern char *	ft_mpi_routine_names[MPI_num_routines];
extern int    	ft_mpi_cntrs        [MPI_num_routines];

extern HashTable_t *	ft_global_ht;
extern HashTable_t **	ft_thread_ht; /* Will be allocated to table of 
                                         ft_num_allocated_ht ptrs at run time */
 
extern int 	ft_num_thread_ht; 
extern int      ft_num_allocated_ht;
extern int 	ft_global_timer_level; 

extern int      ft_running_with_threads;

extern int *	ft_thread_timer_level;	/* These 4 arrays will be allocated to */
extern double * ft_thread_flops;        /* ft_num_allocated_ht at run time */
extern double * ft_thread_cpu_secs;
extern double * ft_thread_wall_secs;
  
extern double 	ft_cpu_secs;    
extern double 	ft_wall_secs;   
extern double 	ft_flops;        

extern double   ft_clock_last;	/* last clock() time, used to detect processor clock rollover */
extern int      ft_clock_rolls;	/* number of times clock() has rolled over */ 

extern char *	ft_out_of_memory;



/*******************************************************************************
* END OF FILE
*******************************************************************************/
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
#ifndef Gparm_H
#define Gparm_H

/* RGST_START */

#include "irsdefs.h"

/* RGST_END */

/*------------------------------------------------------------------------------
- DEFINES AND MACROS
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
- STRUCTURE
------------------------------------------------------------------------------*/

/* RGST_START */

typedef struct {

   char sym[MAXWORD] ;
   char val[20] ;
   int type ;

} Gparm_t ;

/* RGST_END */

/*------------------------------------------------------------------------------
- PROTOTYPES
------------------------------------------------------------------------------*/

#endif

/*------------------------------------------------------------------------------
- GLOBAL VARS
------------------------------------------------------------------------------*/
extern int      ngparm ;
extern int      ngparmx ;
extern Gparm_t *gparm ;

/*******************************************************************************
* END OF FILE
*******************************************************************************/
#ifndef Hash_H
#define Hash_H

/*------------------------------------------------------------------------------
- DEFINES AND MACROS
------------------------------------------------------------------------------*/

#define DEFAULT_HASHSIZE	31	/* Number of slots in a hash table */
#define GENERAL_HASHTBL_NAME	"general"

#define HASH(m_hv, m_ht, m_str)  {              \
    register int   my_hashval = 0;              \
    register char *my_hashstr = m_str;          \
    register char *my_savstr  = m_str;          \
    for (; *my_hashstr != '\0'; ) my_hashval = (my_hashval << 1) ^ (*my_hashstr++); \
    if (strlen(my_savstr) > 30) { for (; *my_savstr != '\0'; ) { my_hashval += *my_savstr++; } } \
    m_hv = abs(my_hashval) % m_ht->size;        \
  }

/*------------------------------------------------------------------------------
- STRUCTURE
------------------------------------------------------------------------------*/

/* RGST_START */

typedef struct HashElm_s {
  char *name;                           /* Unique string which identifies the
					   object in the hash table */
  char *type;				/* String which identifies the type
					   of data that *obj points to */
  void *obj;				/* Pointer to the object stored in the
					   hash table */	
  struct HashElm_s *next;		/* Pointer to next hash table element
					   within a specific slot of the 		
					   hash table.  All elements in this
					   chain have names that hash to the
					   same value */	
} HashElm_t;

typedef struct {                        /* A structure that holds an array */
                                        /* full of hash elements (slots) and */
                                        /* an int that specifies the number */
                                        /* of slots */

  char      *name;                      /* Optional unique name for this hash table */
                                        /*   Used to place hash table in registry */
  int       size;                       /* Numer of slots in the hash table */
  HashElm_t **tbl;                      /* RGST_LEN size */

  double d1,d2,d3,d4,d5,d6,d7,d8;       /* Scratch doubles and ints */
  int    i1,i2,i3;                      /* Used to store stuff identifiers */
                                        /* or other stuff in a thread-safe manner */
  
} HashTable_t;

/* RGST_END */


/*******************************************************************************
* PROTOTYPES
*******************************************************************************/

extern HashElm_t * * hash_get_elm_list(int *num_elms, char *type, HashTable_t *ht);
extern HashElm_t * hash_lookup_elm (char *name, HashTable_t *ht);
extern HashTable_t * hash_tbl_create(int size, char *name);
extern HashTable_t * hash_tbl_free(HashTable_t *ht, int free_obj_flag);
extern void * hash_lookup_obj (char *name, HashTable_t *ht);
extern void hash_add(char *name, char *type, void *obj, HashTable_t *ht);
extern void hash_cond_print_by_type(HashTable_t *ht, char *name);
extern void hash_del(char *name, HashTable_t *ht);
extern void hash_del2(char *name, char *type, HashTable_t *ht);
extern void hash_del_objs_of_type(HashTable_t *ht, char *type, void (*fn_ptr) ());
extern void hash_print        (HashTable_t *ht);
extern void hash_print_by_name(HashTable_t *ht);
extern void hash_print_by_type(HashTable_t *ht);
extern void hash_print_obj(HashElm_t *ptr);
extern void hash_print_structs_of_type(HashTable_t *ht, char *type);
extern void hash_sort_array(HashElm_t **hash_elm_array, int num_objs);
extern void hash_sort_array_by_type(HashElm_t **hash_elm_array, int num_objs);
extern void hash_analyze(HashTable_t *ht, int print_flag, FILE *fp, double *avg_chain, int *max_chain);
extern int get_num_elms_in_hashtable(HashTable_t *ht);
extern int hash_optimize(HashTable_t * *htp);
extern int hash_optimize_all(void);
extern int printhash(void);
extern char * strsave(char *ptr);


#endif

/*******************************************************************************
* GLOBALS
*******************************************************************************/

/*------------------------------------------------------------------------------
- gv_hash_tbl - free'd and reallocated by memclr  
- gv_perm_ht  - exists ALWAYS, used for getting wall time of main, which
-               should NOT be reset when a new silo file is read.
------------------------------------------------------------------------------*/

extern HashTable_t *gv_hash_tbl;          /* HH_INIT NULL */
extern HashTable_t *gv_perm_ht;           /* HH_INIT NULL */   
 
/*******************************************************************************
*                      E N D   O F   F I L E
*******************************************************************************/

#ifndef NodeList_H
#define NodeList_H

#ifdef SILO
#include <silo.h>
#endif

#include "Extents.h"

/* RGST_START */

#include "irsdefs.h"

/* RGST_END */

/*------------------------------------------------------------------------------
- DEFINES
------------------------------------------------------------------------------*/

/* flags for ndx list type generation */

#define NDX_OVERLAP          0  /* generate index list with overlaps at gblk bnds */
#define NDX_NO_OVERLAP       1  /* don't generate index list with overlaps at gblk bnds */
#define NDX_REAL             2  /* generate index list which only contains real zones/nodes */
#define NDX_USER_PHONY       3  /* include user block phonies */
#define NDX_GLBL_PHONY       4  /* include global block phonies */
#define NDX_ZONAL            5  /* zonal index list */
#define NDX_NODAL            6  /* nodal index list */

/*------------------------------------------------------------------------------
- STRUCTURE
------------------------------------------------------------------------------*/

/* RGST_START */

struct NodeWindow_t_ {

   char label[MAXLINE]; 

   int ublk;             /* user block which this list pertains to */

   int imin;             /* extents of node list */
   int imax;
   int jmin;
   int jmax;
   int kmin;
   int kmax;

   int in[4][3];    /* extents and stride info */
   int rank;             /* rank of extents */

   int len;              /* length of blk, ndx, and pos */
   int len_total;        /* length of global list */
   int logical;          /* optional logical direction */

   int *blk;             /* local block number for each ndx point */
   int *ndx;             /* local index list  */
   int *pos;             /* position within global list */
   int *udx;             /* user index list list */

   struct NodeWindow_t_ *next;

} ;

typedef struct NodeWindow_t_ NodeWindow_t;

struct NodeList_t_ {

   char name[MAXLINE];

   NodeWindow_t *list;

} ;

typedef struct NodeList_t_ NodeList_t;

/* RGST_END */


/*------------------------------------------------------------------------------
- PROTOTYPES
------------------------------------------------------------------------------*/

extern void NodeList_add(NodeList_t *new_ndx);
extern void NodeList_free(void);
extern void NodeList_make( NodeWindow_t *ndxin, char *name );
extern NodeList_t *NodeList_find( char *name );
extern void NodeList_addnextseq( char *name, NodeWindow_t *ndxin , char *result);
extern int NodeList_read( void );
extern void NodeList_print(NodeList_t *NodeList);
extern int printnodelist(void);

#ifdef SILO
extern int NodeList_wtsilo(DBfile *idbid);
extern int NodeList_rdsilo(DBfile *idbid, int ublk0);
extern int NodeWindow_rdsilo(DBfile *idbid, char *name, NodeWindow_t **ndxin, int ublk0);
extern int NodeWindow_rdsilo(DBfile *idbid, char *name, NodeWindow_t **ndxin, int ublk0);
extern int NodeWindow_wtsilo(DBfile *idbid, char *name, NodeWindow_t *ndxin);
#endif

extern void NodeList_pack( int **data, int *outlen, int *stroutlen, int oldlen );
extern void NodeList_cpack( char **data );
extern void NodeList_unpack( int *data, int len, char *ndx_names );
extern char *NodeList_cunpack( char *data, int len );
extern void NodeWindow_setext(Extents_t *ext, int ublk, int ndx_incl, int ndx_cent) ;
extern int  NodeWindow_read(char *name, NodeWindow_t **in_ndx) ;
extern void NodeWindow_copy(NodeWindow_t *ndxout, NodeWindow_t *ndxin) ;
extern void NodeWindow_add(NodeWindow_t *new_ndx, NodeWindow_t **list) ;
extern void NodeWindow_free(NodeWindow_t *ndxin) ;
extern void NodeWindow_freendx(NodeWindow_t *ndxin);
extern int  NodeWindow_getndx(NodeWindow_t *inndx, int gblk_in, int ndx_ovlp, int ndx_incl,
                   int ndx_cent );
extern int  NodeWindow_getlen(NodeWindow_t *inndx, int gblk_in, int ndx_ovlp, int ndx_incl,
                   int ndx_cent);
extern int  NodeWindow_range(NodeWindow_t *ndxin1, NodeWindow_t *ndxin2, int plusmin1, int plusmin2);
extern void NodeWindow_setndx(int ublk_in, int gblk_in, int i, int j, int k, int* n,
                 NodeWindow_t *inndx, int ndx_ovlp, int ndx_incl, int ndx_cent);
extern int NodeWindow_compact(NodeWindow_t *inndx, NodeWindow_t *out_ndx,
                    int gblk_in,
                    int ndx_ovlp,
                    int ndx_incl,
                    int ndx_cent ) ;
extern void NodeWindow_copyall(NodeWindow_t *in_ndx, NodeWindow_t **out_ndx);

extern void NodeWindow_make( NodeWindow_t **ndxin, int imin, int imax,
                   int jmin, int jmax, int kmin, int kmax, int ublk,
                   char *name)  ;


extern void NodeWindow_buildndx( NodeWindow_t *ndxin, int ndx_incl, int ndx_cent,
                      int gblk, int *inlen, int **inndx);



extern void NodeWindow_intersect(char *name, NodeWindow_t *ndxin1, 
                          NodeWindow_t *ndxin2,
                          NodeWindow_t **ndxout) ;

extern void NodeList_rename( char *name1, char *name2 );

extern void NodeList_del( char *name);

extern void NodeWindow_getstr(int ndx, char *string, int gblk); 

extern int NodeList_plnl( void ) ;
extern int NodeList_plnloff( void ) ;
extern void NodeList_plot( int iflab );
extern int NodeWindow_fastndx(NodeWindow_t *in_ndx, int gblk, int ndx_incl, int ndx_cent);

#endif

/*------------------------------------------------------------------------------
- GLOBAL VARS
------------------------------------------------------------------------------*/

/*******************************************************************************
* END OF FILE
*******************************************************************************/
#ifndef ProblemArray_H 
#define ProblemArray_H 


/* RGST_START */

#include "irsdefs.h"
#include "Hash.h"
#include "Rgst.h"

/* RGST_END */

/*------------------------------------------------------------------------------
- STRUCTURE
------------------------------------------------------------------------------*/

/* RGST_START */

typedef struct {

   char             name[MAXWORD];	/* name of problem array */
   void            *ptr;   		/* pointer to data */
   int              len;   		/* length of data */
   HashTable_t     *hash;  		/* hash table */
   RGST_Datatype_t  type;  		/* type of data */

} ProblemArray_t;

/* RGST_END */

/*------------------------------------------------------------------------------
- PROTOTYPES
------------------------------------------------------------------------------*/
 
extern ProblemArray_t * ProblemArray_find(char *name, HashTable_t *hash);  
extern ProblemArray_t * ProblemArray_setblk(char *name);

extern HashTable_t * ProblemArray_GetHash(char *name, HashTable_t *hash);

extern void ProblemArray_add(char *name, void *ptr, int len, RGST_Datatype_t type,  HashTable_t *hash); 
extern void ProblemArray_del(char *name, HashTable_t *hash); 
extern void ProblemArray_del_all(HashTable_t* hash) ; 
extern void ProblemArray_free(char *name);
extern void ProblemArray_FreeHash(char *name, HashTable_t *hash);
extern void ProblemArray_CreateHash(char *name, HashTable_t *hash, int size);
  
extern void * ProblemArray_allotptr(char *name, HashTable_t *hash);
extern void * ProblemArray_ptr(char *name, HashTable_t *hash);  

#endif  

/*------------------------------------------------------------------------------
- GLOBAL VARS
------------------------------------------------------------------------------*/

/*******************************************************************************
* END OF FILE
*******************************************************************************/
#ifndef RadiationData_H
#define RadiationData_H

/*------------------------------------------------------------------------------
- STRUCTURE
------------------------------------------------------------------------------*/

typedef struct {
   double *dbl ;
   double *dbc ;
   double *dbr ;
   double *dcl ;
   double *dcc ;
   double *dcr ;
   double *dfl ;
   double *dfc ;
   double *dfr ;
   double *cbl ;
   double *cbc ;
   double *cbr ;
   double *ccl ;
   double *ccc ;
   double *ccr ;
   double *cfl ;
   double *cfc ;
   double *cfr ;
   double *ubl ;
   double *ubc ;
   double *ubr ;
   double *ucl ;
   double *ucc ;
   double *ucr ;
   double *ufl ;
   double *ufc ;
   double *ufr ;
} RadiationData_t ;



/*------------------------------------------------------------------------------
- PROTOTYPES
------------------------------------------------------------------------------*/
extern RadiationData_t newMatrix(int size, int dimensionality, int jp, int kp);
extern void CopyMatrix(RadiationData_t *copyMatrix, RadiationData_t *originalMatrix, int size, int dimensionality);


#endif

/*------------------------------------------------------------------------------
- GLOBAL VARS
------------------------------------------------------------------------------*/
/*
 Define radiation coupling matrix structure *rblk
 Define CG preconditioning matrix structure *cblk
*/
extern RadiationData_t *rblk    ; /* HH_INIT NULL */
extern RadiationData_t *rblkbak ; /* HH_INIT NULL */
extern RadiationData_t *cblk ;    /* HH_INIT NULL */
extern RadiationData_t *pblk ;    /* HH_INIT NULL */


/*******************************************************************************
* END OF FILE
*******************************************************************************/
#ifndef REGION_H
#define REGION_H

/*------------------------------------------------------------------------------
- STRUCTURES
------------------------------------------------------------------------------*/

/* RGST_START */

#define STRESS_FIELD_ARRAY_SIZE	10

typedef enum { _Nospecies_, _Static_, _Dynamic_ } SPECIESTYPE_t;
typedef enum { _Null_, _Form_, _Analytic_, _Table_ } DATABASETYPE_t;
typedef enum { _TwoPhase_NoModel_, _TwoPhase_Always_, _TwoPhase_Melt_ } TWOPHASE_t;

typedef struct {
   DATABASETYPE_t  type   ;                      /* database type              */
   int             index  ;                      /* database index   */
   int             number ;                      /* database number            */
   int             interp_method ;               /* interpolation method       */
   int             form   ;                      /* form number for database   */
   int             ndata  ;                      /* length of data array       */
   double         *data   ;                      /* RGST_LEN ndata             */
   double          refd   ;                      /* database reference density */
   double          rhomin ;                      /* database minimum density   */
   double          rhomax ;                      /* database maximum density   */
   double          t0     ;                      /* database reference T       */
   double          abar   ;                      /* database A-bar             */
   double          zbar   ;                      /* database Z-bar             */
   char            name[256];                    /* table name for eos tables  */
} Database_t ;

typedef struct {
   char            name[32] ;
   int             clyde_number  ;
   double          atomic_number ;
   double          atomic_weight ;
   double          atom_fraction ;
   double          mass_fraction ;
} Component_t;

typedef struct Species_s {

   char                name[32];

   int                 id;
   int                 ncomp;
   int                 reaction;

   double              abar;
   double              zbar;
   double              massFraction0; 
   double              atomFraction0;
   double              mass;

   Component_t        *comp;                     /* RGST_LEN ncomp            */

   struct Species_s   *next;

} Species_t;

/* Opacity structure */

typedef struct {
  Database_t       planckTable ;                 /* Planck opacity database   */
  Database_t       rosTable ;                    /* Rosseland opacity database*/
  Database_t       multiGroupTable ;             /* multigroup database       */
  int              numSpeciesInGroup ;           /* number of species in group*/
  int             *speclist ;                    /* RGST_LEN numSpeciesInGroup */
  double           densityMultiplier ;           /* opacity density multiplier*/
  double           planckMultiplier ;            /* Planck opacity multiplier */
  double           rosMultiplier ;               /* Rosseland opacity mult.   */
  double           KTfloor ;                     /* T floor for tabular Kr/Kp */
} OpacityGroup_t ;

/* EOS structure */

typedef struct {
  Database_t      database ;                    /* EOS database                          */
  int             numSpeciesInGroup ;           /* number of species                     */
  int            *speclist  ;                   /* RGST_LEN numSpeciesInGroup            */
  int             zstarform ;                   /* zstar calculation method              */
  int             econform  ;                   /* electron diffusion coefficient method */
  int             iconform  ;                   /* ion      diffusion coefficient method */
  double          econvalue ;                   /* constant for forms 1 & 2 e-conduction */
  double          iconvalue ;                   /* constant for forms 1 & 2 i-conduction */
  double          e0        ;                   /* reference energy                      */
  double          refd      ;                   /* reference density                     */
  double          etamax    ;                   /* maximum compression                   */
  double          etamin    ;                   /* minimum compression                   */
  double          abar      ;                   /* A-bar for this EOS                    */
  double          zbar      ;                   /* Z-bar for this EOS                    */
  double          densityMultiplier      ;      /* density      multiplier               */
  double          energyMultiplier       ;      /* energy       multiplier               */
  double          ion_energyMultiplier   ;      /* ion energy   multiplier               */
  double          pressureMultiplier     ;      /* pressure     multiplier               */
  double          ion_pressureMultiplier ;      /* ion pressure multiplier               */
  double          eicoupleMultiplier     ;      /* electron-ion coupling mult            */
} EosGroup_t ;

/* material strength data */

typedef struct {
                       /* data for Steinberg-Guinan model */
   double cmu        ;
   double y          ;
   double yb         ;
   double yc         ;
   double gam0       ;
   double ywhmx      ;
   double au         ;
   double ye         ;
   double bu         ;
   double yp         ;
   double ayz        ;
   double tmyz       ;
   double gzyz       ;
   double wyz        ;
   double ytsmn      ;
   double ytsmx      ;
   double sumin      ;
   double sumax      ;
   double epsmax     ;
   double begr       ;
   double endr       ;
   double ecxfit[STRESS_FIELD_ARRAY_SIZE] ;
   double emxfit[STRESS_FIELD_ARRAY_SIZE] ;

                       /* data for Bill Moran's fracture model */
   int    flag       ;
   double coef[STRESS_FIELD_ARRAY_SIZE]   ;
   double *yieldi    ;                           /* RGST_LEN lentabi          */
   int    lentabi    ;
   double *yieldf    ;                           /* RGST_LEN lentabf          */
   int    lentabf    ;

                       /* data for Steinberg-Guinan-Lund model */
   double tol        ;
   double expcut     ;
   double c1str      ;
   double c2str      ;
   double c3str      ;
   double uk2        ;
   double ya         ;
   double yprl       ;
   double ystrmx     ;

                       /* data for Klepeis-Bales extension to S-G model */
   double alphakb    ;
   double etakb      ;
   double bkb        ;
   double mkb        ;

} Stress_t ;

typedef enum { _ViscConst_, _ViscFit_, _ViscTable_ } PartViscMods_t;

typedef struct {

  EosGroup_t         *eosGroup ;                 /* RGST_LEN numGroups        */
  OpacityGroup_t     *opacityGroup ;             /* RGST_LEN numGroups        */
  Species_t          *species ;                  /* RGST_LEN nspec            */
  int                *reactionMolesList ;      
  int                *reactions ;	 	

  /* lengths of region structures and arrays */

  int                 numGroups ;                /* number of regional groups */
  int                 nspec ;                    /* number of species         */
  int                 numReactions ;
  int                 numReactionMoles ;
/*  int                 len_visc;       */           /* length of viscosity array */

  SPECIESTYPE_t       type ;

  Stress_t           *stress ;                   /* constitutive model data   */

  /* Regional model flags */

  int                 pminmd ;                   /* minimum pressure mode     */
  int                 burn ;                     /* HE burn model             */
  int                 str ;                      /* strength model            */
  int                 ioneq ;                    /* electron-ion equilibration*/
  int                 color ;                    /* color for rshd commands   */
  int                 damage ;                   /* damage model              */
  TWOPHASE_t          twoPhase;                  /* two phase model           */
  int                 twoPhaseMaterial;          /* two phase model material  */
  int                 particulate;               /* particulate transport flag*/
  PartViscMods_t      viscmodel;                 /* viscosity model for       */
                                                 /* particulate transport     */

  /* misc. region model parameters */

  double              por0 ;                     /* initial porosity          */
  double              porfail ;                  /* failure porosity          */
  double              etahold ;                  /* density cutoff for damage */
  double              rlagrx ;                   /* mesh relaxation multiplier*/
  double              rxwgt ;                    /* mesh relaxation weighting */
  double              xray ;                     /* x-ray absorption coef.    */
  double              bhe ;                      /* HE beta parameter         */
  double              detvel ;                   /* HE detonation velocity    */
  double              plklmt ;                   /* Planck opacity limit      */
  double              mfplmt ;                   /* mean-free-path limit      */
  double              dmin ;                     /* minimum density           */
  double              emin ;                     /* minimum energy            */
  double              pmin ;                     /* minimum pressure          */

  /* regional artificial viscosity and hourglass parameters */

  double              qlin ;                     /* linear    Q coefficient   */
  double              qquad ;                    /* quadratic Q coefficient   */
  double              hgfrac ;                   /* hourglass   coefficient   */

  /* Navier-Stokes and LES model parameters */

  double              visca ;                    /* Navier-Stokes coefficient */
  double              viscb ;                    /* Navier-Stokes coefficient */
  double              viscc ;                    /* Navier-Stokes coefficient */
  double              viscn ;                    /* Navier-Stokes coefficient */
  double              visccv ;                   /* Navier-Stokes Cv          */
  double              schmidt ;                  /* LES Schmidt number        */
  double              prandtl ;                  /* LES Prandtl number        */
  double              aturb ;                    /* LES viscosity coefficient */
  double              bturb ;                    /* LES buoyancy source coef. */
  double              cturb ;
  double              dturb ;                    /* LES dissipation coef.     */

} Region_t;

/* RGST_END */

/*------------------------------------------------------------------------------
- PROTOTYPES
------------------------------------------------------------------------------*/

#ifdef SILO
struct DBfile ;
extern int Region_pre_read(struct DBfile *idbid, Region_t *ptr, char *field_name);
extern int Region_write(struct DBfile *idbid, Region_t *ptr, char *field_name);
extern int Species_post_read(struct DBfile *idbid, Species_t *ptr, char *field_name);
extern int species_rdsilo(struct DBfile *inFile, Region_t *regin);
extern int species_wtsilo(struct DBfile *inFile, Region_t *regin);
#endif

struct Domain_s ;

extern Database_t *     Database_construct(int num);
extern int              Database_setup_attrs(void);
extern int              Database_init(Database_t *ptr);

extern Species_t *      Species_construct(int num);
extern int              Species_init(Species_t *ptr);
extern int              Species_getlist(int *list, char *name, Species_t *slist, int slen);
extern int              Species_setup_attrs(void);

extern OpacityGroup_t * OpacityGroup_construct(int num);
extern int              OpacityGroup_init(OpacityGroup_t *ptr);
extern int              OpacityGroup_setup_attrs(void);

extern EosGroup_t *     EosGroup_construct(int num);
extern void             EosGroup_check(void);
extern int              EosGroup_init(EosGroup_t *ptr);
extern int              EosGroup_setup_attrs(void);

extern Stress_t *       Stress_construct(int num);
extern int              Stress_init(Stress_t *ptr);
extern int              Stress_setup_attrs(void);

extern Region_t *       Region_construct(int num);
extern int              Region_init(Region_t *ptr);
extern int              Region_setup_attrs(void);
extern void             Region_destruct(Region_t *region);
extern void             Region_free(void);
extern void             Region_check(void);


extern void RegionTableAllocate(struct Domain_s *domain, Region_t *reg, int nreg);
extern void RegionTableFree(struct Domain_s *domain, Region_t *reg, int nreg);
extern Species_t * species_find(char *name);
extern void species_add(Species_t *species);
extern void species_copy(Species_t *spec1, Species_t *spec2);
extern void species_free(void);
extern void species_init(void);

extern int region_edit(void);
extern int region_input(void);
extern int region_opin(void);
extern int species_input(int regionNumber);

#endif

/*------------------------------------------------------------------------------
- GLOBAL VARS
------------------------------------------------------------------------------*/

/* region data structure */

extern Region_t *reg ;          /* HH_INIT NULL */


/*******************************************************************************
* END OF FILE
*******************************************************************************/
#ifndef Rgst_H
#define Rgst_H

/* RGST_START */

#include "irsdefs.h"
#include "Hash.h"

/* RGST_END */

/*------------------------------------------------------------------------------
- STRUCTURE
------------------------------------------------------------------------------*/

  /*----------------------------------------------------------------------------
  - This enumerated type specifes all the basic C data types that are known
  - to the registry.  The names of these types are fairly self-explanatory.
  -
  - I prefaced eachtype with "R_" to avoid name conflicts with other
  - libraries that may be linked with the code.
  -
  - Whenever more RGST enumerated datatypes are added, be sure to also
  - add string versions of the names to the rgst_datatype_strs[] and
  - rgst_datatype_sizes in rgst_init.c
  -----------------------------------------------------------------------------*/

/* RGST_START */

typedef enum { 
  GENERIC_ENUM_TYPE 
} GENERIC_ENUM_TYPEDEF;

typedef enum {

  R_CHAR,          R_UNSIGNED_CHAR,
  R_SHORT,         R_UNSIGNED_SHORT,
  R_SHORT_INT,     R_UNSIGNED_SHORT_INT,
  R_INT,           R_UNSIGNED_INT,
  R_LONG,          R_UNSIGNED_LONG,
  R_LONG_INT,      R_UNSIGNED_LONG_INT,
  R_LONG_LONG,     R_UNSIGNED_LONG_LONG,
  R_LONG_LONG_INT, R_UNSIGNED_LONG_LONG_INT,
  R_FLOAT,
  R_DOUBLE,
  R_VOID,
  R_STRUCT,
  R_CTYPE_TYPEDEF,
  R_ENUM_TYPEDEF,
  R_STRUCT_TYPEDEF,
  R_FUNCTION,
  R_INT_ARRAY,
  R_DOUBLE_ARRAY,
  NUM_RGST_Datatype_t

} RGST_Datatype_t;

  /*----------------------------------------------------------------------------
  - This enumerated type is used to specify the size of a dynamic array
  - in the registry.  That is, something that looks like
  -
  - double *myarray
  -
  - The actual length of this array can be either stored in another
  - field within the data structure that hold 'myarray', or it can be
  - stored in a global var, or it can be an absolute value given by
  - the call that adds this array to the registry.
  -----------------------------------------------------------------------------*/
typedef enum {

  FIELD_OFFSET, GLOBAL_VAR, ABSOLUTE_VALUE,
  NUM_ARRAY_SIZE_ENUM

} ARRAY_SIZE_ENUM;

  /*----------------------------------------------------------------------------
  - This enumerated type is used to speicify if an attribute is associated
  - with a typedef, a field within a structure, or with a registry object.
  -----------------------------------------------------------------------------*/
typedef enum {

  A_TYPE,
  A_FIELD,
  A_OBJECT,
  NUM_ATTR_Assoc_t

} ATTR_Assoc_t;

/* RGST_END */

/*------------------------------------------------------------------------------
- Forward declaration of typedefs and structures.
-
- These are used because of self-referential data structures.
-
- E.G. RGST_Attribute_t contains a ptr to  RGST_Object_t and
-      RGST_Object_t    contains a ptr to RGST_Attribute_t
-
-------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
- This is used to hold a dynamically allocated array of attribute pointers.
-------------------------------------------------------------------------------*/

/* RGST_START */

struct RGST_Attribute_s ;

typedef struct {

  int num_attrs;                   /* Num of attrs in following attrs array */
  int size_attrs;                  /* Length of following attrs array */
  struct RGST_Attribute_s **attrs; /* Array full of attribute ptrs */

} AttrArray_t;

/* RGST_END */

/*------------------------------------------------------------------------------
- This defines a field of a structure for the registry
------------------------------------------------------------------------------*/
/* RGST_START */

typedef struct {

  char          name[R_MAXSTR_PLUS1];    /* Name of this field                */
  RGST_Datatype_t type;                  /* C Data type of this field         */
  int           type_size;               /* Size in bytes of this data type   */
  char          td_name[R_MAXSTR_PLUS1]; /* Name of structure or typedef of   */
                                         /*   this field.  Only used if above */
                                         /*   type is STRUCT, CTYPE_TYPEDEF,  */
                                         /*   ENUM_TYPEDEF, or STRUCT_TYPEDEF */
  long offset;                           /* Offset of this field from the     */
                                         /*   begining of the structure       */
  int  nptrs;                            /* Num of ptrs of this field         */
  int  ndims;                            /* Num of dimensions of this field   */
  int  dims[3];                          /* Dimensions of this field.         */
                                         /*   Only used if ndims > 0          */
  ARRAY_SIZE_ENUM array_size_type;       /* If this field is a ptr that will  */
                                         /* be used as an array, then the     */
                                         /* size of this array may be speci-  */
                                         /* fied by:                          */
                                         /*                                   */
                                         /* FIELD_OFFSET : Another field      */
                                         /*   within this data structure.     */
                                         /* GLOBAL_VAR : A global var placed  */
                                         /*   in the registry.                */
                                         /* ABSOLUTE_VALUE: An long spec-     */
                                         /*   fying the size of the array.    */
                                         /*                                   */
                                         /*                                   */
  int  array_size_field;                 /* If FIELD_OFFSET: the index of     */
                                         /*   another field in this struct    */
  long array_size_field_offset;          /* If FIELD_OFFSET: the offset of    */
                                         /*   another field in this struct    */
  char array_size_global_var[R_MAXSTR_PLUS1];
                                         /* If GLOBAL_VAR: the name of a      */
                                         /*   global var in the registry.     */
  long array_size_absolute_val;          /* If ABSOLUTE_VALUE: The size of    */
                                         /*   the ptr-array                   */
                                         /*                                   */
  int  str_array_size_field;             /* If this field is a ptr-to-ptr     */
                                         /* then the array-of-array sizes     */
                                         /* may be specified in another       */
                                         /* field within the structure.       */
                                         /* This is the index of this other   */
                                         /* field ...                         */
  long str_array_size_field_offset;      /* And this is the offset of the     */
                                         /* other field ...                   */
  AttrArray_t *attributes;               /* Attributes for this field */

} RGST_Field_t;

/* RGST_END */

/*------------------------------------------------------------------------------
- This defines a structure typedef for the registry
------------------------------------------------------------------------------*/
/* RGST_START */

typedef struct {

  char            name[R_MAXSTR_PLUS1]; /* Name of this structure definition  */
  RGST_Field_t   *fields;               /* Fields in this structure definition*/
  int             num_fields;           /* Number of fields                   */
  int             struct_size;          /* Size of entire structure in bytes  */
  AttrArray_t    *attributes;           /* Attributes for this typedef        */

} RGST_StructTypeDef_t;

/* RGST_END */

/*------------------------------------------------------------------------------
- This defines an enumerated typedef for the registry
------------------------------------------------------------------------------*/
/* RGST_START */

typedef struct {

  char            name[R_MAXSTR_PLUS1];
  int             num_entries;
  char **         entry_strings;        /* Pointer to array of strings which
                                           give the string names of each
                                           enumerated type entry */
  AttrArray_t    *attributes;           /* Attributes for this typedef */

} RGST_EnumTypeDef_t;

/* RGST_END */

/*------------------------------------------------------------------------------
- This defines a typedef of a 'C' type for the registry.
-------------------------------------------------------------------------------*/
/* RGST_START */

typedef struct {

  char            name[R_MAXSTR_PLUS1];
  RGST_Datatype_t type;
  int             type_size;
  int             nptrs;
  int             ndims;
  int             dims[3];
  AttrArray_t   *attributes;          /* Attributes for this typedef */

} RGST_CTypeDef_t;

/* RGST_END */

/*------------------------------------------------------------------------------
-
------------------------------------------------------------------------------*/
/* RGST_START */

typedef struct {

  RGST_Datatype_t type;
  int           type_size;

} RGST_BasicCTypeDef_t;

/* RGST_END */

/*------------------------------------------------------------------------------
-
------------------------------------------------------------------------------*/
/* RGST_START */

typedef struct {

  RGST_Datatype_t type;

} RGST_Function_t;

/* RGST_END */

/*------------------------------------------------------------------------------
- This defines a registry object.
------------------------------------------------------------------------------*/
/* RGST_START */

typedef struct {

  char           *name;         /* Unique name of this object */
  char           *usertype;     /* */
  RGST_Datatype_t datatype;     /* C data type of this object */
  int             nptrs;        /* eg. int **myint   would set nptrs to 2 */
  int             ndims;        /* eg. int myint[10] would set ndims to 1 */
  int             dims[3];      /* eg. int mying[10] would set dims[0] to 10 */
  void           *obj;          /* Pointer to the object */

  ARRAY_SIZE_ENUM array_size_type;
  int             array_size_field;
  long            array_size_field_offset;
  char            array_size_global_var[R_MAXSTR_PLUS1];
  long            array_size_absolute_val;

  AttrArray_t   *attributes;  /* Attributes for this typedef */

} RGST_Object_t;

/* RGST_END */

/*------------------------------------------------------------------------------
- Data structure of an element in the attributes hash table, and
- linked list.
-
- This stores the info for an object that has a given attribute.
-
- EG. The "zonal" attributes hash table and linked lists would be
-     comprised of many of these, one for each object, field, or
-     data structure that has the "zonal" attribute".
-
------------------------------------------------------------------------------*/

/* RGST_START */

typedef struct RGST_AttributeElem_s {


  char *name;                  /* Unique key which is either
                                    0) The name of a  structure
                                    1) The name of a  structure + field
                                    2) The name of an object */

  ATTR_Assoc_t assoc;            /* What this attribute is attached to
                                  A_TYPE   = typedef,
                                  A_FIELD  = field,
                                  A_OBJECT = registry object.  */

  RGST_Datatype_t rgst_datatype; /* If above assoc is A_TYPE or A_FIELD,
                                  then the type of the data structure.
                                  It may be one of the following types:

                                  RGST_STRUCT         if assoc is type or field
                                  RGST_STRUCT_TYPEDEF if assoc is type or field
                                  RGST_CTYPE_TYPEDEF  if assoc is type
                                  RGST_ENUM_TYPEDEF   if assoc is type */

  RGST_CTypeDef_t      *rgst_ctype_defn;  /* If assoc is type or field, one of */
  RGST_EnumTypeDef_t   *rgst_enum_defn;   /* these 3 will contain a ptr to the   */
  RGST_StructTypeDef_t *rgst_struct_defn; /* registry structure definition.      */

  RGST_Field_t *rgst_field;      /* If above type is field then ptr to registry
                                  field definition (which contains, among
                                  other things, the offset of this field
                                  within the data structure */

  RGST_Object_t *rgst_obj;       /* If above type is object, then ptr to registry
                                  object definition */

  struct RGST_AttributeElem_s     *next,
                                  *prev;

} RGST_AttributeElem_t;

/* RGST_END */

/*------------------------------------------------------------------------------
- Data structure for an attribute
-
- Note: This structure will be placed within the general hash table
-       for the code.  So the first thing to do when querying the
-       attribute, is to retrieve this data structure, with a unique
-       key such as "zonal", from the general hash table.
------------------------------------------------------------------------------*/

/* RGST_START */

typedef struct RGST_Attribute_s {

  char *attr_name;                    /* e.g. "zonal", Unique key */

  RGST_AttributeElem_t *obj_head,     /* linked list of objects with attr */
                       *type_head,    /* linked list of types   with attr */
                       *field_head;   /* linked list of fields  with attr */

  HashTable_t          *table;        /* Hash table, containing all objects,
                                         structs, and fields with this attr */

} RGST_Attribute_t;

/* RGST_END */


/*------------------------------------------------------------------------------
- PROTOTYPES
------------------------------------------------------------------------------*/

extern int  AttrArray_init(AttrArray_t *ptr);
extern int  RGST_Object_init(RGST_Object_t *ptr);
extern void AttrArray_add(RGST_Attribute_t *new_attr, AttrArray_t *ptr);
extern void AttrArray_del(char *attr_name, AttrArray_t *ptr);

extern RGST_AttributeElem_t * rgst_copy_attr_elm_list(RGST_AttributeElem_t *elm_list);
extern RGST_AttributeElem_t * rgst_create_RGST_AttributeElem_t(char *name, ATTR_Assoc_t assoc, RGST_Datatype_t datatype, void *v_ptr, RGST_Field_t *fld_ptr);
extern RGST_AttributeElem_t * rgst_free_RGST_AttributeElem_t(RGST_AttributeElem_t *ptr);
extern RGST_AttributeElem_t * rgst_free_attr_elm_list(RGST_AttributeElem_t *ptr);
extern RGST_Attribute_t     * rgst_free_RGST_Attribute_t(RGST_Attribute_t *ptr);
extern RGST_Attribute_t     * AttrArray_search(char *attr_name, AttrArray_t *ptr);
extern RGST_Object_t        * RGST_Object_construct(int num);
extern RGST_Object_t        * RGST_Object_create(char *name, char *type_str, RGST_Datatype_t datatype, int nptrs, int ndims, int *dims, void *obj, ARRAY_SIZE_ENUM array_size_type, int array_size_field, long array_size_field_offset, char *array_size_global_var, long array_size_absolute_val);
extern RGST_Object_t        * RGST_Object_destruct(RGST_Object_t *ptr);
extern AttrArray_t          * AttrArray_construct(int num);
extern AttrArray_t          * AttrArray_destruct(AttrArray_t *ptr);

#endif

/*------------------------------------------------------------------------------
- GLOBAL VARS
------------------------------------------------------------------------------*/

/*******************************************************************************
* END OF FILE
*******************************************************************************/
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



#ifndef SpeciesFraction_H
#define SpeciesFraction_H

/*------------------------------------------------------------------------------
- STRUCTURE
------------------------------------------------------------------------------*/

/* RGST_START */

typedef struct {

   double *mass_frac;	/* zonal species mass fraction */

} SpeciesFraction_t;

/* RGST_END */


/*------------------------------------------------------------------------------
- PROTOTYPES
------------------------------------------------------------------------------*/


#endif

/*******************************************************************************
* END OF FILE
*******************************************************************************/
#ifndef Spline_H
#define Spline_H

/*------------------------------------------------------------------------------
- DEFINES AND MACROS
------------------------------------------------------------------------------*/

/* RGST_START */

#include "irsdefs.h"

/* RGST_END */

/* RGST_START */

#define UNKNOWNDATA  0
#define RTDATA       1
#define XYDATA       2
#define VXDATA       3
#define VRDATA       4
#define VTDATA       5

#define CUBIC        0
#define LINEAR       1
#define COMBINED	 2

#define SPLINE_INVERT       1
#define SPLINE_SCALE        2
#define SPLINE_ADD          3
#define SPLINE_DELTA        4

/* RGST_END */

/*------------------------------------------------------------------------------
- STRUCTURE
------------------------------------------------------------------------------*/

/* RGST_START */

struct Spline_t_ {

   char name[MAXWORD];

   int type;

   int coord;

   int flip;

   char indlab[2];
   char deplab[2];

   double x0;
   double y0;
   double z0;

   double axis_x;
   double axis_y;
   double axis_z;

   double norm_x;
   double norm_y;
   double norm_z;

   int len;

   double *dep;		/* RGST_LEN len */
   double *ind; 	/* RGST_LEN len */

   double  dep1;
   double  dep2;

   double *b;		/* RGST_LEN len */
   double *c;	 	/* RGST_LEN len */
   double *d;		/* RGST_LEN len */

   struct Spline_t_ *next;

 } ;

 typedef struct Spline_t_ Spline_t;

/* RGST_END */

/*------------------------------------------------------------------------------
- PROTOTYPES
------------------------------------------------------------------------------*/
#ifdef SILO
extern int  spline_rdsilo(DBfile *idbid);
extern int  spline_wtsilo(DBfile *idbid);
#endif

extern Spline_t * Spline_construct(int num);
extern Spline_t * spline_find(char *name); 
extern int  Spline_init(Spline_t *ptr);
extern int  Spline_setup_attrs(void);
extern int  spline_chkrange(Spline_t *spline, double xmin, double xmax);  
extern int  spline_eval(double val, double *dep, Spline_t *spline); 
extern int  spline_fit(void);
extern int  spline_getxy(double *x, double *y, int n, double xmin, double xmax, double x0, double y0, Spline_t *spline);
extern int  spline_input(void);
extern int  spline_plsp(void);
extern int  spline_plspoff(void);
extern int  spline_print(void);
extern void spline_delete(char *name);
extern void spline_free(void);
extern void spline_getvalues(int mode);
extern void spline_plot( int iflab );
extern void fillvar_spline(double *vptr, double *x, double *y, double *z, double *r, double *t, int len, Spline_t *spline, double xmin, double xmax, char *cnst);

#endif 
/*------------------------------------------------------------------------------
- GLOBAL VARS
------------------------------------------------------------------------------*/

/*******************************************************************************
* END OF FILE
*******************************************************************************/
#ifndef State_H
#define State_H

/*------------------------------------------------------------------------------
- STRUCTURE
------------------------------------------------------------------------------*/

typedef struct {

  double  timeStep ;
  double  currentTime ;

  /* nodal positions */
  double *x ;
  double *y ;
  double *z ;

  /* nodal velocities */
  double *xdot ;
  double *ydot ;
  double *zdot ;

  /* scalar fields */
  double *den  ;
  double *emat ;
  double *eion ;
  double *erad ;
  double *tmat ;
  double *tion ;
  double *trad ;

  /* zonal strength */
  double *sxx ;
  double *sxy ;
  double *sxz ;
  double *syy ;
  double *syz ;
  double *szz ;

  double *eps ;

} State_t ;

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
#ifndef Stringnam_H
#define Stringnam_H

/*------------------------------------------------------------------------------
- STRUCTURE
------------------------------------------------------------------------------*/

typedef struct {

  char name[24];

} Stringnam_t;


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
#ifndef Tagorder_H
#define Tagorder_H

/*------------------------------------------------------------------------------
- STRUCTURE
------------------------------------------------------------------------------*/

typedef struct {

   int len;
   int *blk;
   int *tag;

} Tagorder_t ;

/*------------------------------------------------------------------------------
- PROTOTYPES
------------------------------------------------------------------------------*/

#endif

/*------------------------------------------------------------------------------
- GLOBAL VARS
------------------------------------------------------------------------------*/
extern Tagorder_t *vsame_order;

/*******************************************************************************
* END OF FILE
*******************************************************************************/
#ifndef Thermo_H
#define Thermo_H

/*------------------------------------------------------------------------------
- STRUCTURE
------------------------------------------------------------------------------*/

typedef struct {

  double *p       ; 
  double *dpdr    ;
  double *dpde    ; 
  double *dpdt    ; 

  double *pion    ;
  double *dpidr   ;
  double *dpidei  ; 
  double *dpidti  ; 

  double *dtdr    ;
  double *dtde    ; 

  double *dtidr   ;
  double *dtidei  ; 
  double *dtedei  ;

  double *drdp    ; 
  double *drde    ;
  double *drdt    ;
  double *drdti   ; 

  double *dedp    ; 
  double *dedr    ;
  double *dedt    ;
  double *dedti   ;
  double *dedt_v  ;

  double *deidp   ; 
  double *deidr   ; 
  double *deidti  ; 
  double *deidte  ; 
  double *deidt_v ; 

  double *den     ; 
  double *emat    ; 
  double *tmat    ; 

  double *eion    ; 
  double *tion    ; 

  double *p_cold  ; 
  double *e_cold  ; 
  double *dp_cdr  ; 
  double *cs      ;  
  double *cs2     ; 
  double *work3   ;  
  double *work1   ;  
  double *work2   ;

  double *abar    ; 
  double *zbar    ; 
  double *zstar   ; 

  double *tdedte  ; 
  double *tdedti  ; 
  double *tdedp   ; 
  double *tdeidte ; 
  double *tdeidti ; 
  double *tdeidp  ; 
  double *tdrdte  ; 
  double *tdrdti  ; 
  double *tdrdp   ; 

  double *dtlast  ;  
  double *delast  ; 
  double *deilast ; 
  double *drlast  ; 

  double *cdmin   ; 
  double *cdmax   ; 

  double *cpmin   ; 
  double *cpmax   ; 

  double *ceemin  ; 
  double *ceemax  ; 

  double *ctemin  ; 
  double *ctemax  ; 

  double *ceimin  ; 
  double *ceimax  ; 

  double *ctimin  ;  
  double *ctimax  ; 

} Thermo_t ;


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
#ifndef TimePlot_H
#define TimePlot_H

/* RGST_START */

#include "FreqMesg.h"
#include "CycleMesg.h"

/* RGST_END */

/*------------------------------------------------------------------------------
- TIME PLOT EDIT DATA STRUCTURES
-
- TimePlotCurve_t and TimePlot_t hold the time plot edit data.  This data is gathered
- while the program runs and is written to and read from the silo restart
- file.
-
- TimePlot_t is instantiated by the global var *tpdata which is declared
- in irs.h.   tpdata[] is therefore a global array of time plot data
- structures.
-
- TimePlotCurve_t is only instantiated from the *tp_curs reference in TimePlot_t.
- There is no global var of type TimePlotCurve_t
-
------------------------------------------------------------------------------*/

/* RGST_START */

typedef struct {

   char *name;                  /* Unique name for this time plot curve */

   char *eval_string;           /* String to be evaluated which generates the data
                                   for the curves */
   int   num_vals;              /* The evaluation string may generate multiple values
                                   -- each value will be a separate curve.
                                   This is how many it generates.  This
                                   is also the size of the tpc_labels and tpc_data
                                   arrays since we need a label and data for each
                                   curve */

   char **labels;               /* RGST_LEN num_vals */
                                /* Curve labels */

   double **data;               /* RGST_LEN num_vals alloc_data_pts */
                                /* Curve data -- the actual data which forms the curve */

   int  *alloc_data_pts;        /* RGST_LEN num_vals */
                                /* The allocated size of the tpc_data arrays */

} TimePlotCurve_t;

typedef struct {

   char        *name;           /* Unique name for this time plot */

                                /* NOTE: The edits are done on either a
                                   time frequency or a cycle frequency.
                                   2 of the following 4 fields will hold
                                   data and the other 2 will be NULL */

   char        *fq_name;        /* Unique name of time frequency data
                                   structure for this time plot */

   FreqMesg_t  *fq_dat;         /* RGST_LEN 1 */
                                /* Pointer to time frequency data
                                   structure for this time plot */

   char        *cyc_name;       /* Unique name of the cycle frequency data
                                   structure for this time plot */

   CycleMesg_t *cyc_dat;        /* RGST_LEN 1 */
                                /* Pointer to cycle frequency data structure
                                   for this time plot */

   TimePlotCurve_t  **tp_curs;  /* RGST_LEN num_tp_curs */
                                /* Array of time plot curve pointers */

   char        **tp_curs_names; /* RGST_LEN num_tp_curs */
                                /* Names of each time plot curve */

   int num_data_pts;            /* Current number of entries stored in
                                   each time plot in the above tpc_data[]
                                   array */

   int max_data_pts;            /* max num of pts on each time plot in the
                                   above tpc_data[] arrays.  This is derived
                                   using the begin, end, and delta times
                                   from the timeplot command */

   int alloc_data_pts;          /* Actual number of pts allocated in the
                                   above tpc_data[] array.  This will be
                                   <= data_pts_max.  If data_pts_max is very
                                   large (due to a very small time step
                                   like .001), then this will be set
                                   to a value smaller than data_pts_max.
                                   This is because, it is very probable
                                   that each cycle will span many time
                                   steps, so there is no way that data_pts_max
                                   values will every be saved--and the
                                   space would just be wasted. */

   int inc_data_pts;            /* As data in the tpc_data arrays grows,
                                   the arrays will be incremented in steps
                                   of this size */

   int num_tp_curs;             /* Num of entries in the above tp_curs[] array */

} TimePlot_t;


/* RGST_END */


/*------------------------------------------------------------------------------
- PROTOTYPES
------------------------------------------------------------------------------*/

#ifdef SILO
struct DBfile ;
extern int TimePlotCurve_post_read(struct DBfile *idbid, TimePlotCurve_t *ptr, char *field_name);
extern int TimePlot_post_read(struct DBfile *idbid, TimePlot_t *ptr, char *field_name);
extern int TimePlot_write(struct DBfile *idbid, TimePlot_t *ptr, char *field_name);
#endif

extern TimePlotCurve_t * TimePlotCurve_construct(int num);
extern TimePlotCurve_t * TimePlotCurve_create(char *sym, int tpc_num);
extern TimePlotCurve_t * TimePlotCurve_destruct(TimePlotCurve_t *ptr);
extern TimePlotCurve_t * free_TimePlotCurve_t(TimePlotCurve_t *tp);
extern TimePlot_t * TimePlot_construct(int num);
extern TimePlot_t * TimePlot_destruct(TimePlot_t *ptr);
extern TimePlot_t * free_TimePlot_t (TimePlot_t *tp) ;
extern int TimePlotCurve_init(TimePlotCurve_t *ptr);
extern int TimePlotCurve_setup_attrs(void);
extern int TimePlot_init(TimePlot_t *ptr);
extern int TimePlot_setup_attrs(void);
extern void TimePlot_expand(TimePlot_t *tp);
extern void printtimeplot(TimePlot_t *tp);
extern void printtpcurve(TimePlotCurve_t *tpc);

#endif

/*------------------------------------------------------------------------------
- GLOBAL VARS
------------------------------------------------------------------------------*/
        /*----------------------------------------------------------------------
        - time plot parms 
        -
        - These global scalar vars are used in conjuction with the global array
        - tpdata[] 
        ----------------------------------------------------------------------*/
extern int ntp ;		/* Current num of time plot data structures */
extern int maxtpdata ;		/* Maximum num of time plot data structures.  
				   This is therefore the number of entries
				   allocated for the global array tpdata[]. 
				   As of 09/10/97, this is set to 20 in
				   parminit.c */
extern int itp ;		/* This is used as an index into the time 
				   plot array tpdata[] */

extern int maxtplot;		/* Max number of tplot lines within a */
				/* timeplot or cycleplot loop */

extern int maxtimeplot ;

	/*-----------------------------------------------------------------------
	- time plot structure
	-----------------------------------------------------------------------*/
extern TimePlot_t **tpdata ;    /* Array of ptrs to time plot data structs */

/*******************************************************************************
* END OF FILE
*******************************************************************************/
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
#ifndef UserList_H
#define UserList_H

/*------------------------------------------------------------------------------
- STRUCTURE
------------------------------------------------------------------------------*/

/* RGST_START */

struct UserList_ {

   char name[32];
   struct UserList_ *next;

};

typedef struct UserList_ UserList_t;

/* RGST_END */


/*------------------------------------------------------------------------------
- PROTOTYPES
------------------------------------------------------------------------------*/
#ifdef SILO
struct DBfile ;
extern void UserList_wtsilo( struct DBfile *idbid ) ;
extern void UserList_rdsilo( struct DBfile *idbid ) ;
#endif

extern UserList_t *UserList_find(char *attr) ;

extern int     UserList_input( void ) ;
extern int     UserList_parse( char *listname ) ;
extern int     UserList_print( void ) ;

extern void    UserList_add(char *name, char *attr) ;
extern void    UserList_del(char *attr) ;
extern void    UserList_remove(char *name, char *attr) ;
extern void    UserList_free( void ) ;


#endif

/*------------------------------------------------------------------------------
- GLOBAL VARS
------------------------------------------------------------------------------*/

/*******************************************************************************
* END OF FILE
*******************************************************************************/
#ifndef VdenData_H
#define VdenData_H

/*------------------------------------------------------------------------------
- STRUCTURE
------------------------------------------------------------------------------*/
typedef struct {

  double *xnebar ;
  double *xnex ;
  double *xney ;
  double *xnez ;
  double *xtebar ;
  double *xtex ;
  double *xtey ;
  double *xtez ;

} VdenData_t ;


/*------------------------------------------------------------------------------
- PROTOTYPES
------------------------------------------------------------------------------*/

#endif

/*------------------------------------------------------------------------------
- GLOBAL VARS
------------------------------------------------------------------------------*/

extern VdenData_t *vnedat;         /* HH_INIT NULL */


/*******************************************************************************
* END OF FILE
*******************************************************************************/
#ifndef VectorStruct_H
#define VectorStruct_H

/*------------------------------------------------------------------------------
- STRUCTURE
------------------------------------------------------------------------------*/

typedef struct {

   char   *namevec;
   char    namelab[50];
   int     type;
   int     palen;
   int 	  *ipa;
   double *fpa;
   int    *iloc;
   double *floc;
   double  min;
   double  max;

} VectorStruct_t ;



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
#ifndef VersionData_H
#define VersionData_H

/*------------------------------------------------------------------------------
- STRUCTURE
------------------------------------------------------------------------------*/

/* RGST_START */

typedef struct {
   char *node_compiled;
   char *date_compiled;
   char *time_compiled;
   char *os_compiled;
   char *opt_compiled;
   char *dump_version;
   char *person;
} VersionData_t ;

/* RGST_END */


/*------------------------------------------------------------------------------
- PROTOTYPES
------------------------------------------------------------------------------*/
extern VersionData_t * VersionData_destruct(VersionData_t *ptr);

#endif

/*------------------------------------------------------------------------------
- GLOBAL VARS
------------------------------------------------------------------------------*/

extern VersionData_t gv_ver;            /* global version data structure */

/*******************************************************************************
* END OF FILE
*******************************************************************************/
#ifndef pint_H
#define pint_H

/* RGST_START */

typedef int *pint;
typedef double *pdouble;

/* RGST_END */

#endif


/*******************************************************************************
* END OF FILE
*******************************************************************************/
