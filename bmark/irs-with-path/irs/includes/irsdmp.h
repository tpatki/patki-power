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
extern DBfile * openpdmp(char *kern, int cyc, int num, int mode, char *dmpname);
extern int Restart_read_domain(DBfile *idbid, int dblk, int iblk);
extern int Restart_read_global(DBfile *idbid);
extern int Restart_write_domain(DBfile *idbid, int iblk);
extern int rdmaterial(DBfile *idbid, char *material_name, char *species_name, int spec_read_flag, Extents_t ext, struct Domain_s *domain);
extern int rdparms(DBfile *idbid);
extern int rgfxstate(DBfile *idbid);
extern int rwgdmp(DBfile *idbidin, DBfile *idbidout, char * *qvarnames, int *nqvar, char * *ucdnames, int *nucdvar, int iblk, int gblk);
extern int wgfxstate(DBfile *idbid);
extern int wtmaterial(DBfile *idbid, DBoptlist *ioptnod, char *material_name, char *species_name, char *mesh_name, int *zdx, int *zdx_len, int spec_write_flag, struct Domain_s *domain);
extern int wtparms(DBfile *idbid);
extern int wtsilomesh(DBfile *idbid, DBoptlist *ioptnod, char *mesh_name, double *x, double *y, double *z, Extents_t ext, int jp, int kp);
extern void Restart_write_global( DBfile *idbid);

extern int Restart_read(void);
extern int Restart_read_driver(char *dmpname, int mdmpflag, int memflag);
extern int Restart_write(int flag);
extern int Restart_write_driver(char *kern, int cyc, int alldump);
extern int conddmp(int cyc);
extern int condgdmp(int cyc);
extern int wgdmp(void);
extern void dmpattr_set(void);
extern void dmpattr_unset(void);
extern void getdmplst_last(char *dmpname, char *extention, int mode, int mdmpflag);
extern void getdmplst_numbers(char *dmpname, int mycyc, int *lenout, int * *listout);
extern void rdmeshvar(void *var, int var_type, int var_cent, char *var_name, int len, int mixlen, DBfile *idbid, struct Domain_s *domain);
extern void rdmeshvar_ext(void *var, int var_type, int var_cent, char *var_name, int len, int mixlen, DBfile *idbid, Extents_t ext, struct Domain_s *domain);
extern void rdsilomesh(DBfile *idbid, char *mesh_name, double *x, double *y, double *z, int *node, Extents_t ext, int jp, int kp);
extern void rdspecies(char *name, DBfile *idbid, DBmaterial *material, Extents_t ext, struct Domain_s *domain);
extern void rootfile_read(char *kern, int cyc_in);
extern void rootfile_write(DBfile *idbidin, char *kern, int cyc_in);
extern void set_silo_option(DBoptlist *ioptnod, int gblk);
extern void wtmeshvar(void *var, int var_type, int var_cent, char *var_name, char *mesh_name, int *mixzdx, int mixlen, DBfile *idbid, DBoptlist *ioptnod, struct Domain_s *domain);
extern void wtspecies(char *specname, char *matname, DBfile *idbid, int *lnkmix, int *matlist, int mixlen, DBoptlist *ioptnod, struct Domain_s *domain);

#endif

#endif
/*******************************************************************************
* GLOBALS
*******************************************************************************/

extern char meshlink_codesys[10];
extern int multi_dump_write;  /* HH_INIT 1 */
extern int iffamily;  /* HH_INIT 0 */
extern int dmp_nbaton;  /* HH_INIT -1 */

extern char RestartKernel[RESTART_KERNEL_LEN];
extern int  RestartCycle;

extern int lopt[3];
extern int hopt[3];
extern int intopt;
extern int intopt2;

/*******************************************************************************
* END OF FILE
*******************************************************************************/
