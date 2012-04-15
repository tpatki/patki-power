#ifndef irsdmp_H
#define irsdmp_H

#include "Extents.h"

/*******************************************************************************
* DEFINES
*******************************************************************************/
#define RESTART_KERNEL_LEN      256
#define VER_DUMP 		"010117"
#define MAXOPTS 		20

/* endblk macro */

#define endblk(a)  \
   strcpy(block,a) ;  \
   fwrite(block,sizeof(char),8,fpdmp)

/*  getblk macro */

#define getblk(a)   \
   fread(block,sizeof(char),8,fpdmp)  ;   \
   if (strcmp(block,a))   \
      {   \
      PRINT(stdout,"dump record missmatch in %s\n",a) ;   \
      PRINT(fpout,"dump record missmatch in %s\n",a) ;   \
      printf("   found %d %e %s\n",block,block,block) ;  \
      goto out ; \
      }

#define WRITE(array,type,num) \
   { if (num != fwrite(array,sizeof(type),num,fpdmp)) { \
      PRINT(stdout,"dump write error\n") ;          \
      PRINT(fpout,"dump write error\n") ; }}

#define READ(array,type,num) \
   { if (num != fread(array,sizeof(type),num,fpdmp)) { \
      PRINT(stdout,"dump read error\n") ;          \
      PRINT(fpout,"dump read error\n") ; }}

#define READ2(array,type,num) \
   {  array = (type *) calloc(num,sizeof(type)) ; \
      if (num != fread(array,sizeof(type),num,fpdmp)) { \
      PRINT(stdout,"dump read error\n") ;          \
      PRINT(fpout,"dump read error\n") ; }}

/*******************************************************************************
* PROTOTYPES
*******************************************************************************/

struct Domain_s ;

#ifdef SILO
DBfile * openpdmp(char *kern, int cyc, int num, int mode, char *dmpname);
int Restart_read_domain(DBfile *idbid, int dblk, int iblk);
int Restart_read_global(DBfile *idbid);
int Restart_write_domain(DBfile *idbid, int iblk);
int rdmaterial(DBfile *idbid, char *material_name, char *species_name, int spec_read_flag, Extents_t ext, struct Domain_s *domain);
int rdparms(DBfile *idbid);
int rgfxstate(DBfile *idbid);
int rwgdmp(DBfile *idbidin, DBfile *idbidout, char * *qvarnames, int *nqvar, char * *ucdnames, int *nucdvar, int iblk, int gblk);
int wgfxstate(DBfile *idbid);
int wtmaterial(DBfile *idbid, DBoptlist *ioptnod, char *material_name, char *species_name, char *mesh_name, int *zdx, int *zdx_len, int spec_write_flag, struct Domain_s *domain);
int wtparms(DBfile *idbid);
int wtsilomesh(DBfile *idbid, DBoptlist *ioptnod, char *mesh_name, double *x, double *y, double *z, Extents_t ext, int jp, int kp);
void Restart_write_global( DBfile *idbid);

int Restart_read(void);
int Restart_read_driver(char *dmpname, int mdmpflag, int memflag);
int Restart_write(int flag);
int Restart_write_driver(char *kern, int cyc, int alldump);
int conddmp(int cyc);
int condgdmp(int cyc);
int wgdmp(void);
void dmpattr_set(void);
void dmpattr_unset(void);
void getdmplst_last(char *dmpname, char *extention, int mode, int mdmpflag);
void getdmplst_numbers(char *dmpname, int mycyc, int *lenout, int * *listout);
void rdmeshvar(void *var, int var_type, int var_cent, char *var_name, int len, int mixlen, DBfile *idbid, struct Domain_s *domain);
void rdmeshvar_ext(void *var, int var_type, int var_cent, char *var_name, int len, int mixlen, DBfile *idbid, Extents_t ext, struct Domain_s *domain);
void rdsilomesh(DBfile *idbid, char *mesh_name, double *x, double *y, double *z, int *node, Extents_t ext, int jp, int kp);
void rdspecies(char *name, DBfile *idbid, DBmaterial *material, Extents_t ext, struct Domain_s *domain);
void rootfile_read(char *kern, int cyc_in);
void rootfile_write(DBfile *idbidin, char *kern, int cyc_in);
void set_silo_option(DBoptlist *ioptnod, int gblk);
void wtmeshvar(void *var, int var_type, int var_cent, char *var_name, char *mesh_name, int *mixzdx, int mixlen, DBfile *idbid, DBoptlist *ioptnod, struct Domain_s *domain);
void wtspecies(char *specname, char *matname, DBfile *idbid, int *lnkmix, int *matlist, int mixlen, DBoptlist *ioptnod, struct Domain_s *domain);

#endif

#endif
/*******************************************************************************
* GLOBALS
*******************************************************************************/

char meshlink_codesys[10];
int multi_dump_write =  1 ;
int iffamily =  0 ;
int dmp_nbaton =  -1 ;

char RestartKernel[RESTART_KERNEL_LEN];
int  RestartCycle;

int lopt[3];
int hopt[3];
int intopt;
int intopt2;

/*******************************************************************************
* END OF FILE
*******************************************************************************/
