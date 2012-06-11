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
