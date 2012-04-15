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
