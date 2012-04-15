#include "irs.h"
#include "irsblk.h"
#include "irsgen.h"
#include "irsbndry.h"
#include "irsctl.h"
#include "irsdmp.h"
#include "irsobjects.h"
#include "irsrgst.h"
#include "BlockMapping.h"
#include "Command.h"
#include "Domain.h"
#include "Extents.h"
#include "FunctionTimer.h"
#include "ProblemArray.h"
#include "Rgst.h"
int Domain_setup_attrs(void)
{
  char *me = "Domain_setup_attrs";
  static int first_time_thru = TRUE;
  char *fields[100] = {
        "gblk",         "type",        
        "imin",         "jmin",         "kmin",
        "imax",         "jmax",         "kmax",
        "nnalls",       "nnodes",       "namix",        
        "mixmax",       "nmixcnt",
        "imaxmix",      "nmixzn",       "nzones",
        "jp",           "kp",           "fpn",          "lpn",
        "fpz",          "lpz",          "frn",          "lrn",
        "frz",          "lrz",
        "sclnamix",     "ndeltat",      "dtg",          "dtcon",
        "dti",          "dtj",          "dtk",
        "rlen",         "rlencln",      "rlenmix",
        "nsrc",         "src",
        "phonlen",      "phondx",       "bndndx",       "phonbc",
        "phozlen",      "phozdx",       "bndzdx",
        "nbc",          "bc",
        "nbnd",         "bnd",          
	"cpu_secs",     "wall_secs",    "flops",
	NULL};
  char *attrs[2] = {"dump", NULL};
  if (RGST_ADD_MULT_FIELD_ATTRS("Domain_t",fields,attrs) != 0)
     ctlerror(me,gv_errmsg_rgst_add_mult_attrs);
  if (first_time_thru == TRUE) {
    inst_c("Domain_init",     Domain_init,      zargse, 0, symtab);
    inst_c("Domain_construct",Domain_construct, zargse, 0, symtab);
#ifdef SILO
    inst_c("Domain_write",    Domain_write,     zargse, 0, symtab);
    inst_c("Domain_pre_read", Domain_pre_read,  zargse, 0, symtab);
    inst_c("Domain_post_read",Domain_post_read, zargse, 0, symtab);
#endif
    first_time_thru = FALSE;
  }
  return(0);
}
int Domain_init(Domain_t *ptr)
{
  ptr->nnodes    = 0;
  ptr->cpu_secs  = 0.0;
  ptr->wall_secs = 0.0;
  ptr->flops     = 0;
  return(0);
}
Domain_t *Domain_construct(int num)
{
  char *me = "Domain_construct";
  int i;
  Domain_t *ptr;
  if (num < 1) ctlerror(me,logic_err);
  ptr = ALLOT(Domain_t, num);
  if (ptr == NULL) ctlerror(me,logic_err);
  for (i=0; i<num; i++) {
    Domain_init(&(ptr[i]));
  }
  return(ptr);
}
#ifdef SILO
int Domain_write(
  DBfile *idbid,        
  Domain_t *domain,  
  char *field_name)     
{
  char *me = "Domain_write";
  int   mixlen, ir, array_type, indout, i, j;
  int   dims[3];
  int   *zdx;
  Extents_t      ext;
  DBoptlist   *ioptnod;
  RGST_AttributeElem_t *dumpvar;
  RGST_AttributeElem_t *dumpvar_ptr;
  ioptnod = DBMakeOptlist(MAXOPTS);
  set_silo_option(ioptnod, domain->gblk);
  CPYEXT(ext,(*domain));
  wtsilomesh(idbid, ioptnod, "hydro_mesh", domain->x, domain->y, domain->z,
             ext, domain->jp, domain->kp);
  zdx = MALLOT(int,domain->mixmax);
  wtmaterial(idbid, ioptnod, "Materials", "Species", "hydro_mesh", zdx, &mixlen,
             ifdynspec, domain);
  dumpvar = rgst_list_attr(A_OBJECT,"dDomainDumpVar");
  dumpvar_ptr = dumpvar;
  while (dumpvar_ptr != NULL) {
     char *name   = ATTR_GET_OBJECT_NAME(dumpvar_ptr)
     double *dptr = (double *)ProblemArray_ptr(name, domain->hash);
     array_type = ZONAL_ARRAY;
     if (RGST_QUERY_OBJECT_ATTR(name,"Nodal") == TRUE) array_type = NODAL_ARRAY;
     if (RGST_QUERY_OBJECT_ATTR(name,"Mixed") == TRUE) {
       wtmeshvar(dptr, FLOAT, array_type, name,
                 "hydro_mesh", zdx, mixlen, idbid, ioptnod, domain);
     } else {
       wtmeshvar(dptr, FLOAT, array_type, name,
                 "hydro_mesh", NULL, 0, idbid, ioptnod, domain);
     }
     dumpvar_ptr = dumpvar_ptr->next;
  }
  dumpvar = rgst_list_attr(A_OBJECT,"iDomainDumpVar");
  dumpvar_ptr = dumpvar;
  while (dumpvar_ptr != NULL) {
     char *name  = ATTR_GET_OBJECT_NAME(dumpvar_ptr)
     int  *iptr  = (int *)ProblemArray_ptr(name, domain->hash);
     array_type = ZONAL_ARRAY;
     if (RGST_QUERY_OBJECT_ATTR(name,"Nodal") == TRUE) array_type = NODAL_ARRAY;
     if (RGST_QUERY_OBJECT_ATTR(name,"Mixed") == TRUE) {
       wtmeshvar(iptr, INT, array_type, name,
                 "hydro_mesh", zdx, mixlen, idbid, ioptnod, domain);
     } else {
       wtmeshvar(iptr, INT, array_type, name,
                 "hydro_mesh", NULL, 0, idbid, ioptnod, domain);
     }
     dumpvar_ptr = dumpvar_ptr->next;
  }
  FREEMEM(zdx);
  dumpvar = rgst_list_attr(A_OBJECT,"dDumpVar");
  dumpvar_ptr = dumpvar;
  while (dumpvar_ptr != NULL) {
     char *name   = ATTR_GET_OBJECT_NAME(dumpvar_ptr)
     ProblemArray_t *prb = ProblemArray_find(name, domain->hash);
     double *dptr = (double *)prb->ptr;
     dims[0]      = prb->len;
     DBWrite(idbid, name, dptr, dims, 1, DB_DOUBLE);
     dumpvar_ptr = dumpvar_ptr->next;
  }
  dumpvar = rgst_list_attr(A_OBJECT,"iDumpVar");
  dumpvar_ptr = dumpvar;
  while (dumpvar_ptr != NULL) {
     char *name   = ATTR_GET_OBJECT_NAME(dumpvar_ptr)
     ProblemArray_t *prb = ProblemArray_find(name, domain->hash);
     int  *iptr   = (int *)prb->ptr;
     dims[0]      = prb->len;
     DBWrite(idbid, name, iptr, dims, 1, DB_INT);
     dumpvar_ptr = dumpvar_ptr->next;
  }
  dims[0] = domain->imax - domain->imin + 1;
  dims[1] = domain->jmax - domain->jmin + 1;
  dims[2] = domain->kmax - domain->kmin + 1;
  if (DBClearOptlist(ioptnod) != 0) ctlerror(me,gv_errmsg_DBClearOptlist);
  if (DBFreeOptlist(ioptnod)  != 0) ctlerror(me,gv_errmsg_DBFreeOptlist);
  SubMesh_wtdomain(idbid, domain);
  if (gv_alldump == 0) return(-1);
  if ( (ngroup > 0) || (ifedif) || (ifidif)  ) {
    RGST_ADD_FIELD_ATTR("Domain_t","rphonlen", "dump");
    RGST_ADD_FIELD_ATTR("Domain_t","rbndndx",  "dump");
    RGST_ADD_FIELD_ATTR("Domain_t","rphondx",  "dump");
    RGST_ADD_FIELD_ATTR("Domain_t","rphonbc",  "dump");
    RGST_ADD_FIELD_ATTR("Domain_t","rphozlen", "dump");
    RGST_ADD_FIELD_ATTR("Domain_t","rbndzdx",  "dump");
    RGST_ADD_FIELD_ATTR("Domain_t","rphozdx",  "dump");
  } else {
    RGST_DEL_FIELD_ATTR("Domain_t","rphonlen", "dump");
    RGST_DEL_FIELD_ATTR("Domain_t","rbndndx",  "dump");
    RGST_DEL_FIELD_ATTR("Domain_t","rphondx",  "dump");
    RGST_DEL_FIELD_ATTR("Domain_t","rphonbc",  "dump");
    RGST_DEL_FIELD_ATTR("Domain_t","rphozlen", "dump");
    RGST_DEL_FIELD_ATTR("Domain_t","rbndzdx",  "dump");
    RGST_DEL_FIELD_ATTR("Domain_t","rphozdx",  "dump");
  }
  FunctionTimer_wtsilo(idbid, domain->hash);
  return(0);
}
#endif

#ifdef SILO
int Domain_pre_read(
  DBfile *idbid,        
  Domain_t *domain,     
  char *field_name)     
{
  char *me = "Domain_pre_read";
  double dummy;
  char *slide_fields[100] = {
        "type",         "gid",          "imin",         "imax",    
        "jmin",         "jmax",         "kmin",         "kmax",
        "min1",         "max1",         "min2",         "max2",
        "stride",       "start",        "len",          "master",
        "offn",         "offt1",        "offt2",
        "onoff",        "ndx",          "ndxName",
	NULL};
  char *slide_attrs[2] = {"dump", NULL};
  domain_allot_arrays1(domain);
  if ( (ngroup > 0) || (ifedif) || (ifidif)  ) {
    RGST_ADD_FIELD_ATTR("Domain_t","rphonlen", "dump");
    RGST_ADD_FIELD_ATTR("Domain_t","rbndndx",  "dump");
    RGST_ADD_FIELD_ATTR("Domain_t","rphondx",  "dump");
    RGST_ADD_FIELD_ATTR("Domain_t","rphonbc",  "dump");
    RGST_ADD_FIELD_ATTR("Domain_t","rphozlen", "dump");
    RGST_ADD_FIELD_ATTR("Domain_t","rbndzdx",  "dump");
    RGST_ADD_FIELD_ATTR("Domain_t","rphozdx",  "dump");
  }
  else {
    RGST_DEL_FIELD_ATTR("Domain_t","rphonlen", "dump");
    RGST_DEL_FIELD_ATTR("Domain_t","rbndndx",  "dump");
    RGST_DEL_FIELD_ATTR("Domain_t","rphondx",  "dump");
    RGST_DEL_FIELD_ATTR("Domain_t","rphonbc",  "dump");
    RGST_DEL_FIELD_ATTR("Domain_t","rphozlen", "dump");
    RGST_DEL_FIELD_ATTR("Domain_t","rbndzdx",  "dump");
    RGST_DEL_FIELD_ATTR("Domain_t","rphozdx",  "dump");
  }
  return(0);
}
#endif

#ifdef SILO
int Domain_post_read(
  DBfile *idbid,        
  Domain_t *domain,     
  char *field_name)     
{
  char *me = "Domain_post_read";
  char **varlist, dirname[128];
  int      i;
  int      array_type, nmixzn, num_vars, ibc, off, len, *ndx;
  Extents_t  ext;
  RGST_AttributeElem_t *dumpvar;
  RGST_AttributeElem_t *dumpvar_ptr;
     ProblemArray_t *prblocal;
     double *dptrlocal;
  char *slide_fields[20] = {
        "xt",     "xb",     "yt",     "yb",
        "xvt",    "xvb",    "yvt",    "yvb",
        "mnodet", "mnodeb", "xn",     "yn",
        NULL};
  char *slide_fields_3d[10] = {"zt", "zb", "zvt", "zvb", "zn", NULL};
  char *slide_attrs[2] = {"dump", NULL};
  FunctionTimer_rdsilo(idbid, domain->hash);
  domain_allot_arrays2(domain);
  domain_setpa(domain);
  CPYEXT(ext,(*domain));
  rdsilomesh(idbid, "hydro_mesh", domain->x, domain->y, domain->z,
             domain->node, ext, domain->jp, domain->kp);
  dumpvar = rgst_list_attr(A_OBJECT,"dDomainDumpVar");
  dumpvar_ptr = dumpvar;
  while (dumpvar_ptr != NULL) {
     char *name          = ATTR_GET_OBJECT_NAME(dumpvar_ptr)
     ProblemArray_t *prb = ProblemArray_find(name, domain->hash);
     nmixzn = 0;
     if (RGST_QUERY_OBJECT_ATTR(name,"Mixed") == TRUE) {
         nmixzn = domain->nmixzn;
     }
     if (RGST_QUERY_OBJECT_ATTR(name,"Nodal") == TRUE) {
       rdmeshvar(prb->ptr, FLOAT, NODAL_ARRAY, name,
                 prb->len, nmixzn, idbid, domain);
     } else {
       rdmeshvar(prb->ptr, FLOAT, ZONAL_ARRAY, name,
                 prb->len, nmixzn, idbid, domain);
     }
     dumpvar_ptr = dumpvar_ptr->next;
  }
  dumpvar = rgst_list_attr(A_OBJECT,"iDomainDumpVar");
  dumpvar_ptr = dumpvar;
  while (dumpvar_ptr != NULL) {
     char *name          = ATTR_GET_OBJECT_NAME(dumpvar_ptr)
     ProblemArray_t *prb = ProblemArray_find(name, domain->hash);
     nmixzn = 0;
     if (RGST_QUERY_OBJECT_ATTR(name,"Mixed") == TRUE) {
         nmixzn = domains->nmixzn;
     }
     if (RGST_QUERY_OBJECT_ATTR(name,"Nodal") == TRUE) {
       rdmeshvar(prb->ptr, INT, NODAL_ARRAY, name,
                 prb->len, nmixzn, idbid, domain);
     } else {
       rdmeshvar(prb->ptr, INT, ZONAL_ARRAY, name,
                 prb->len, nmixzn, idbid, domain);
     }
     dumpvar_ptr = dumpvar_ptr->next;
  }
  dumpvar = rgst_list_attr(A_OBJECT,"dDumpVar");
  dumpvar_ptr = dumpvar;
  DBShowErrors(DB_NONE, NULL);
  while (dumpvar_ptr != NULL) {
     char *name   = ATTR_GET_OBJECT_NAME(dumpvar_ptr)
     prblocal = ProblemArray_find(name, domain->hash);
     dptrlocal = (double *)prblocal->ptr;
     DBReadVar(idbid, name, dptrlocal);
     dumpvar_ptr = dumpvar_ptr->next;
  }
  dumpvar = rgst_list_attr(A_OBJECT,"iDumpVar");
  dumpvar_ptr = dumpvar;
  while (dumpvar_ptr != NULL) {
     char *name   = ATTR_GET_OBJECT_NAME(dumpvar_ptr)
     ProblemArray_t *prb = ProblemArray_find(name, domain->hash);
     int  *iptr   = (int *)prb->ptr;
     DBReadVar(idbid, name, iptr);
     dumpvar_ptr = dumpvar_ptr->next;
  }
  DBShowErrors(DB_TOP, NULL);
  
  CPYEXT(ext,(*domain));
  rdmaterial(idbid, "Materials", "Species", ifdynspec, ext, domain);
 ; 
  if ( domain->type == QUAD2D ) {
    refnd2d(domain->x,    domain->y,    domain) ;
    refnd2d(domain->xdot, domain->ydot, domain) ;
      volcal2d (domain->vol, domain->area, domain->x, domain->y, domain);
  }
  else if (domain->type == HEX3D) {
    refnd3d( domain->x,    domain->y,    domain->z,     domain) ;
    refnd3d( domain->xdot, domain->ydot, domain->zdot,  domain) ;
      volcal3d (domain->vol, domain->x, domain->y,  domain->z, domain) ;
  }
  if (unblk > 1) {
  }
  setphony(domain->zmass, 0.0, domain);
  return(0);
}
#endif
