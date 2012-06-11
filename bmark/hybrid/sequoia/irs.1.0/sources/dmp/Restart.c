#include <string.h>
#include "irs.h"
#include "irslag.h"
#include "irscom.h"
#include "irsdmp.h"
#include "irsedits.h"
#include "irseos.h"
#include "irsparm.h"
#include "irsrgst.h"
#include "irsreg.h"
#include "BlockMapping.h"
#include "Conditional.h"
#include "Command.h"
#include "CycleMesg.h"
#include "FunctionTimer.h"
#include "FreqMesg.h"
#include "Gparm.h"
#include "Rgst.h"
#include "Hash.h"
#include "NodeList.h"
#include "ProblemArray.h"
#include "Region.h"
#include "Stringnam.h"
#include "Spline.h"
#include "TimePlot.h"
#include "TimeStepControl.h"
#include "Tracer.h"
#include "UserList.h"
#include "VersionData.h"

#ifdef SILO
int  Restart_read( void )
{
   char *me = "Restart_read";
   char dmpname[MAXLINE], msg[256];
   int error, mdmpflag;
   geta(dmpname) ;
   if (!strcmp(dmpname,"last")) {
      strcpy(dmpname,pbnm);
      getdmplst_last(dmpname,"silo",-1,ifparallel);
   }
   if (!strcmp(dmpname,"prev")) {
      strcpy(dmpname,pbnm);
      getdmplst_last(dmpname,"silo",-2,ifparallel);
   }
   if (!strcmp(dmpname,"next")) {
      strcpy(dmpname,pbnm);
      getdmplst_last(dmpname,"silo",-3,ifparallel);
   }
   if (!strcmp(dmpname,"lastwith")) {
      geta(dmpname) ;
      getdmplst_last(dmpname,"silo",-1,ifparallel);
   }
   mdmpflag = 0;
   if (ifparallel) {
     if (strchr(dmpname,'-') != NULL) {
       mdmpflag = 1;
     }
   }
   error = Restart_read_driver(dmpname,mdmpflag,1) ;
   return(error) ;
}
int Restart_read_driver(char *dmpname, int mdmpflag, int memflag)
{
   char *me = "Restart_read_driver";
   char *kern, *rem, *infostr;
   char msg[MAXLINE];
   int  i, error = 0, ierr;
   int  num, mycyc, iblk, gblk, namelen;
   int  mynblk;
   int  numBlocks, numDomains;
   int *domainFiles;
   DBfile *idbid;
   RGST_AttributeElem_t *func;
   if (memflag == 1) {
      memclr() ;
   }
   comlock(dmp_nbaton);
   if (mdmpflag) {
     kern = strtok(dmpname,"-");
     rem = strtok(NULL,"-");
     mycyc = atoi(rem);
     RestartCycle = mycyc;
     strcpy(RestartKernel,kern);
     rootfile_read(kern,mycyc);
   } else {
      namelen = strlen(dmpname);
      if (namelen > 10) {
	 memset(msg,'\0',MAXLINE);
         strncpy(RestartKernel,dmpname,namelen - 10);
         RestartKernel[namelen - 9] = '\0';
	 i = strlen(dmpname) - 10;
         strncpy(msg,&(dmpname[i]), 5);
         RestartCycle = atoi(msg);
      } else {
      } 
      idbid = DBOpen (dmpname, DB_PDB, DB_READ);
      if (idbid == NULL) {
         error = 1 ;
         sprintf(msg,"Can't open dump %s\n",dmpname);
         ctlwarning(me,msg);
         return(error) ;
      }
      infostr = DBGetVar (idbid, "_fileinfo");
      namelen = strlen(codename);
      if (strncmp (infostr, codename, namelen) != 0) {
	sprintf(msg,"Restarting from a dump which is not %s.  This is EVIL!\n",
		codename);
	ctlwarning(me,msg);
      }
      FREEMEM(infostr);
      decomp_setdir(idbid);
      ierr  = DBReadVar(idbid,"NumBlocks",&numBlocks);
      ierr += DBReadVar(idbid,"NumDomains",&numDomains);
      if (ierr != 0) ctlerror(me,gv_errmsg_DBReadVar);
      decomp_new(numBlocks, numDomains);
      decomp_read(idbid, msg, 0, 0);
      if (DBSetDir(idbid, "/") != 0) ctlerror(me,gv_errmsg_DBSetDir);
      error += Restart_read_global(idbid); 
      dmpattr_set();
      domainFiles = MALLOT(int, gnblk);
      for (gblk = 0; gblk < gnblk; gblk++) {  
         domainFiles[gblk] = gmap[gblk].lblk;
      }
      calculate_mappings();
      mynblk = 0;
      for (gblk = 0; gblk < gnblk; gblk++) {
         if (gmap[gblk].proc != myid) continue;
         iblk = gmap[gblk].lblk;
         Restart_read_domain(idbid, domainFiles[gblk], iblk); 
         mynblk++;
      }
      nblk = mynblk;
      DBClose(idbid);
      FREEMEM(domainFiles);
   }
   dmpattr_unset();
   comunlock(dmp_nbaton);
   ifparallel = 0;
   nblk = gnblk;
   initcom(NULL,0);
   sprintf(msg,"dump '%s' read",dmpname);
   ctlmsg(msg);
   printtc() ;
   func = rgst_list_attr(A_OBJECT, "Function_Gen");
   while (func != NULL) {
      Command_t *cp = (Command_t *) func->rgst_obj->obj;
      (*(cp->proc))();  
      func = func->next;
   }
   blknum = 0 ;
   genmd = -1;
   error += qbnd(FULL_STEP,COM_RECV);
   error += qbnd(FULL_STEP,COM_SEND);
   error += qbnd(FULL_STEP,COM_WAIT_RECV);
   TimeStepControl_initialize() ;
   for ( iblk = 0 ; iblk < nblk ; iblk++ ) {
      updateblk( &domains[iblk], 0, 0.0 ) ;
   }
 ; 
   error += qbnd(FULL_STEP,COM_WAIT_SEND);
   editor(FULL_STEP);
   genmd = 0;
   hash_optimize_all();
   return(0);
}
int Restart_read_global(DBfile *idbid)
{
  char *me = "Restart_read_global";
  int ierr = 0, error = 0;
  int index, itest ;
  int i, j, k, n, gblk, irestart, num_ipas, num_fpas;
  int iblk,len2, length, nsplines;
  int numGroups, numSpec;
  int pdmdsav,npsave,nisave,nfsave,nppsave,ifthreadsave;
  char dirname[128], msg[256], pbnm_save[256], outstring[32];
  int nhead[NHEAD_NUM];
  int inttemp[100];      
  double doubtemp[100];  
  double myflops = 0.0;
  Stringnam_t *palistn;
  int         *palistv;
  VersionData_t  *file_ver;
  TimePlot_t     *my_tpd;
  RGST_AttributeElem_t *func;
  FT_INITIALIZE(me, gv_hash_tbl) 
  genmd   = 0 ;
  pdmdsav = pdmd ;
  strcpy(pbnm_save,pbnm);
  if (DBSetDir(idbid, "/Global") != 0) ctlerror(me,gv_errmsg_DBSetDir);
  file_ver = rgst_read_struct_in_dir(idbid,"Version","VersionData_t",NULL,NULL);
  if (file_ver == NULL) ctlerror(me,gv_errmsg_rgst_read_struct_in_dir);
  if (strcmp(file_ver->dump_version,VER_DUMP) != 0) {
    sprintf(msg,"Dump version %s may be incompatible with current version %s",
                 file_ver->dump_version,VER_DUMP);
    ctlnotice(me,msg);
  }
  VersionData_destruct(file_ver);
  if (DBReadVar(idbid, "nhead", nhead) != 0) ctlerror(me,gv_errmsg_DBReadVar);
  ifthreadsave = ifthreads;
  ierr = rdparms(idbid);
  if (ierr != 0) {
    ctlwarning(me,"rdparms failed");
  }
  ifthreads = ifthreadsave;
  pdmd = pdmdsav ;
  strcpy(pbnm,pbnm_save);
  memexp();
  DBShowErrors(DB_NONE, NULL);
  ierr = DBSetDir(idbid,"Nodelists");
  if (ierr == 0) {
     NodeList_rdsilo(idbid,0);
     ierr = DBSetDir(idbid,"../");
  }
  DBShowErrors(DB_TOP, NULL);
  DBShowErrors(DB_NONE, NULL);
  ierr = DBSetDir(idbid,"Tracers");
  if (ierr == 0) {
     ierr = DBSetDir(idbid,"../");
  }
  DBShowErrors(DB_TOP, NULL);
  DBShowErrors(DB_NONE, NULL);
  ierr = DBSetDir(idbid,"Probes");
  if (ierr == 0) {
     ierr = DBSetDir(idbid,"../");
  }
  DBShowErrors(DB_TOP, NULL);
  conditionals_rdsilo(idbid);
  TimeStepControl_rdsilo(idbid);
  if (DBSetDir(idbid, "/Global") != 0) ctlerror(me,gv_errmsg_DBSetDir); 
  FunctionTimer_rdsilo(idbid, gv_hash_tbl);
  spline_rdsilo(idbid);
  UserList_rdsilo(idbid);
  func = rgst_list_attr(A_OBJECT, "Function_ReadSilo");
  while (func != NULL) {
     Command_t *cp = (Command_t *) func->rgst_obj->obj;
     (*(cp->proc))(idbid);  
     func = func->next;
  }
  num_ipas = nhead[NHEAD_NUM_IPA];
  num_fpas = nhead[NHEAD_NUM_FPA];
  n        = MAX(num_ipas, num_fpas);
  if ( n > 0 ) {
     palistn = ALLOT(Stringnam_t, n);
     palistv = ALLOT(int,         n);
  }
  ierr = 0;
  if (DBSetDir(idbid, "/Global") != 0) ctlerror(me,gv_errmsg_DBSetDir);
  if ( num_fpas > 0 ) {
     ierr  = DBReadVar(idbid, "palistfn", palistn);
     ierr += DBReadVar(idbid, "palistfv", palistv);
  }
  for (i=0; i<num_fpas; i++) {
    ProblemArray_t *prb = ProblemArray_find(palistn[i].name, NULL);
    if (palistv[i] != prb->len) { ctlerror(me,logic_err); }
    ierr += DBReadVar(idbid, palistn[i].name, prb->ptr);
  }
  if ( num_ipas > 0 ) {
     ierr += DBReadVar(idbid, "palistin", palistn);
     ierr += DBReadVar(idbid, "palistiv", palistv);
  }
  for (i=0; i<num_ipas; i++) {
    ProblemArray_t *prb = ProblemArray_find(palistn[i].name, NULL);
    if (palistv[i] != prb->len) { ctlerror(me,logic_err); }
    ierr += DBReadVar(idbid, palistn[i].name, prb->ptr);
  }
  if (ierr != 0) ctlerror(me,gv_errmsg_DBReadVar);
  if ( n > 0 ) {
     FREEMEM(palistn);
     FREEMEM(palistv);
  }
  for (i=1; i<=nreg; i++) {
    sprintf(dirname,"/Regional/reg%i",i);
    if (rgst_read_struct_in_dir(idbid, dirname, "Region_t", &(reg[i]),NULL) == NULL)
      ctlerror(me,gv_errmsg_rgst_read_struct_in_dir);
  }
  for (i = 0; i < nfq; i++) {
    sprintf(dirname,"/Global/fqdat%i",i);
    fq[i].name = NULL;  
    fq[i].msg  = NULL;
    if (rgst_read_struct_in_dir(idbid, dirname,"FreqMesg_t",&(fq[i]),NULL) == NULL)
      ctlerror(me,gv_errmsg_rgst_read_struct_in_dir);
    fqtp[i] = fq[i].fqtp;
    rgst_add(fq[i].name,"FreqMesg_t",&(fq[i]),NULL);
  }
  for (i = 0; i < ncyc; i++) {
    sprintf(dirname,"/Global/cycdat%i",i);
    cyc[i].name = NULL; 
    cyc[i].msg  = NULL;
    if (rgst_read_struct_in_dir(idbid, dirname,"CycleMesg_t",&(cyc[i]),NULL) == NULL)
      ctlerror(me,gv_errmsg_rgst_read_struct_in_dir);
    cyctp[i] = cyc[i].cyctp;
    rgst_add(cyc[i].name,"CycleMesg_t",&(cyc[i]),NULL);
  }
  for (i = 0; i <= ngparm; i++) {
    sprintf(dirname,"/Global/gpdat%i",i);
    if (rgst_read_struct_in_dir(idbid, dirname,"Gparm_t",&(gparm[i]),NULL) == NULL)
      ctlerror(me,gv_errmsg_rgst_read_struct_in_dir);
  }
  resetmsg() ;
  itest = 0 ;
  for ( i = 1 ; i <= nreg ; i++ ) {
      for ( j = 0 ; j < reg[i].numGroups ; j++ ) {
         if ( (reg[i].eosGroup[j].database.form == 111) ||
              (reg[i].eosGroup[j].database.form == 211) ||
              (reg[i].eosGroup[j].database.form == 311) ||
              (reg[i].eosGroup[j].database.form == 312)  ) {
            itest = 1 ;
	 }
      }
   }
   if ( itest == 1 ) {
 ;    }
   Region_check() ;
   EosGroup_check() ;
  itest = 0 ;
  irestart = 1 ;
  for ( i = 1 ; i <= nreg ; i++ ) {
    if (reg[i].eosGroup[0].database.form == 19) {
      sprintf(msg,"\n\n\treg %d eos %d form 19 (Two Rate JWL++ EOS)",
	      i, reg[i].eosGroup[0].database.number ) ;
      ctlmsg( msg ) ;
 ;     }
  }
  error += rgfxstate(idbid) ;
  if (DBSetDir(idbid, "/Global/Edits") != 0) ctlerror(me,gv_errmsg_DBSetDir);
  ierr  = DBReadVar(idbid, "ntp",             &ntp);
  if (ierr != 0) ctlerror(me,gv_errmsg_DBReadVar);
  for (i=0; i<ntp; i++) {
    sprintf(dirname,"time_plot%i",i);
    my_tpd = rgst_read_struct_in_dir(idbid, dirname, "TimePlot_t",NULL,NULL);
    if (my_tpd == NULL) ctlerror(me,gv_errmsg_rgst_read_struct_in_dir);
    if (i >= maxtpdata) { ctlerror(me,"Increase maxtpdata"); }
    tpdata[i] = my_tpd;
  }
  FT_FINALIZE(me, gv_hash_tbl, myflops) 
  return(error) ;
}
int Restart_read_domain(
  DBfile *idbid, 
  int dblk,      
  int iblk)      
{
  char *me = "Restart_read_domain";
  char msg[128];
  int  i;
  double myflops = 0.0;
  sprintf(msg,"/domain%i",dblk);
  if (DBSetDir(idbid,msg) != 0) ctlerror(me,gv_errmsg_DBSetDir);
  if (rgst_read_struct(idbid, "Domain_t", &(domains[iblk]), NULL) == NULL)
    ctlerror(me,gv_errmsg_rgst_read_struct);
  if (DBSetDir(idbid, "../") != 0) ctlerror(me,gv_errmsg_DBSetDir);
  domain_hash_tbl_rgst(&(domains[iblk]));
  return(0);
}
int  Restart_write(int flag )
{
  char *me = "Restart_write";
  char msg[256];
  char my_kern[MAXWORD];
  int  error = 0, i;
  int  my_cyc;
  dmpattr_set();
  if (flag == 0) {
    my_cyc = cycle;
    strcpy(my_kern,pbnm);
  } else {
    my_cyc = 0;
    sprintf(my_kern,"z%s",pbnm);
  }
  RestartCycle = my_cyc;
  strcpy(RestartKernel,my_kern);
  gv_alldump = TRUE;
  error = Restart_write_driver(my_kern, my_cyc, gv_alldump);
  if (error != 0) ctlwarning(me,"Restart_write_driver did not return 0");
  if ((ifparallel) || (multi_dump_write > 1)) {
     rootfile_write(NULL, my_kern, my_cyc);
  }
  dmpattr_unset();
  return(error) ;
}
int Restart_write_driver(
  char *kern,          
  int   cyc,           
  int   alldump)
{
  char *me = "Restart_write_driver";
  char fullname[MAXLINE], infotmp[30], msg[128];
  char dmpname[MAXLINE];
  char mykern[MAXLINE];
  char outstr[MAXLINE];
  int itpc, ierr, iblk, gblk, nblk_save, ndmp, nblk_per_file, leftovers, count;
  int *sldblk;
  double myflops = 0.0;
  DBfile *idbid;
  FT_INITIALIZE(me, gv_hash_tbl)
  sldblk = ALLOT(int,nblk);
  ierr   = 0;
  strcpy(fullname,outpath);
  strcpy(mykern,kern);
  if (ifparallel) {
     multi_dump_write = 1;
     if ( iffamily ) {
        sprintf(dmpname,"%s%05d",kern,cyc);
        if (myid == 0) {
           sprintf(outstr,"rm -rf %s; mkdir %s",dmpname,dmpname);
           system(outstr);
        }
        sprintf(mykern,"%s%05d/%s",kern,cyc,kern);
        combarrier();
     }
  } else if ((multi_dump_write > 1) && (iffamily)) {
     sprintf(dmpname,"%s%05d",kern,cyc);
     sprintf(outstr,"rm -rf %s; mkdir %s",dmpname,dmpname);
     system(outstr);
     sprintf(mykern,"%s%05d/%s",kern,cyc,kern);
  }
  comlock(dmp_nbaton);
  if (multi_dump_write == 1) {
    if (ifparallel) {
       idbid = openpdmp(mykern, cyc, myid, 1, dmpname);
    } else {
       idbid = openpdmp(mykern, cyc, -1, 1, dmpname);
    }
    if (idbid == NULL) {
      sprintf(msg,"Can't create dump '%s'",dmpname);
      ctlwarning(me,msg);
      return(1) ;
    }
    nblk_per_file = nblk;
    leftovers = 0;
  }
  else {
    nblk_per_file = nblk/multi_dump_write;
    leftovers = nblk%multi_dump_write;
  }
  gblk = 0;
  for (ndmp = 0; ndmp < multi_dump_write; ndmp++) {
    if (multi_dump_write != 1) { idbid = openpdmp(mykern,cyc,ndmp,1,dmpname); }
    for (iblk = 0; iblk < nblk_per_file; iblk++) {
      ierr += Restart_write_domain(idbid, iblk); 
      gblk++;
    }
    count = nblk_per_file;
    if (leftovers > 0) {
      iblk = nblk_per_file;
      ierr += Restart_write_domain(idbid, iblk);
      leftovers--;
      gblk++;
      count++;
    }
    if (ierr != 0) ctlwarning(me,"Restart_write_domain failed");
    rootfile_write(idbid,mykern,cyc);
    nblk_save = nblk;
    nblk = count;
    if ( alldump ) {
      Restart_write_global(idbid); 
    } 
    nblk = nblk_save ;
    if (DBClose(idbid) != 0) ctlwarning(me,"DBClose did not return 0");
    sprintf(msg,"dump %s made at time = %e",dmpname,ttime);
    ctlmsg(msg);
  }
  comunlock(dmp_nbaton);
  FREEMEM(sldblk);
  FT_FINALIZE(me, gv_hash_tbl, myflops)
  return(ierr) ;
}
#define CHECK_NAME_LEN(objname,name) \
  if (strlen(name) > 23) { \
    sprintf(msg,"%s '%s' is too long--shorten to 23 chars", objname,name); \
    ctlerror(me,msg); \
  }
void Restart_write_global( DBfile *idbid)
{
  char *me = "Restart_write_global";
  char dirname[128];		
  int inttemp[100];		
  double doubtemp[100];		
  double myflops = 0.0;
  int ierr = 0;
  int dims[2];			
  int index;			
  int nhead[NHEAD_NUM];	       	
  int i,j,k,tn,npint,npfloat,npchar ;
  int ir, n, len2, num_ipas, num_fpas;
  int numGroups, numSpec ;
  char msg[256], **fpa_list, **ipa_list;
  Stringnam_t *palistn;
  int         *palistv;
  static char defvars2[] = {
    "velocity vector {xdot,ydot};"
      "slidevt vector {xvt,yvt};"
	"slidevb vector {xvb,yvb};"
	  "speed scalar sqrt(xdot*xdot + ydot*ydot);"};
  static char defvars3[] = {
    "velocity vector {xdot,ydot,zdot};"
      "slidevt vector {xvt,yvt,zvt};"
	"slidevb vector {xvb,yvb,zvb};"
	  "speed scalar sqrt(xdot*xdot + ydot*ydot + zdot*zdot)"};
  char searchpath[]="";
  RGST_AttributeElem_t *func;
  FT_INITIALIZE(me, gv_hash_tbl)
  if (DBSetDir(idbid, "/") != 0) ctlerror(me,gv_errmsg_DBSetDir);
  dims[0] = 1;
  ierr = DBWrite(idbid, "ndoms", &nblk, dims, 1, DB_INT);
  if ( ndims == 2 ) {
    dims[0] = strlen(defvars2);
    ierr += DBWrite(idbid, "_meshtv_defvars", defvars2, dims, 1, DB_CHAR);
  }
  else {
    dims[0] = strlen(defvars3);
    ierr += DBWrite(idbid, "_meshtv_defvars", defvars3, dims, 1, DB_CHAR);
  }
  dims[0] = 1;
  ierr += DBWrite(idbid, "_meshtv_searchpath", searchpath, dims, 1, DB_CHAR);
  if (ierr != 0) ctlerror(me,gv_errmsg_DBWrite);
  if (DBMkDir(idbid,  "/Regional") != 0) ctlerror(me,gv_errmsg_DBMkDir);
  if (DBMkDir(idbid,  "/Global") != 0)   ctlerror(me,gv_errmsg_DBMkDir);
  if (DBSetDir(idbid, "/Global") != 0)   ctlerror(me,gv_errmsg_DBSetDir);
  if (rgst_write_struct_in_dir(idbid, "Version","VersionData_t", &gv_ver, NULL) != 0)
    ctlerror(me,gv_errmsg_rgst_write_struct_in_dir);
  NodeList_wtsilo(idbid);
  conditionals_wtsilo(idbid);
  TimeStepControl_wtsilo(idbid);
  if (DBSetDir(idbid, "/Global") != 0) ctlerror(me,gv_errmsg_DBSetDir);
  FunctionTimer_wtsilo(idbid, gv_hash_tbl);
  wgfxstate(idbid);
  spline_wtsilo(idbid);
  UserList_wtsilo(idbid);
   func = rgst_list_attr(A_OBJECT, "Function_WriteSilo");
   while (func != NULL) {
      Command_t *cp = (Command_t *) func->rgst_obj->obj;
      (*(cp->proc))(idbid);  
      func = func->next;
   }
  ierr = wtparms(idbid);
  if (ierr != 0) {
    ctlwarning(me,"wtparms failed");
  }
  if (DBSetDir(idbid, "/Global") != 0)   ctlerror(me,gv_errmsg_DBSetDir);
  ipa_list = rgst_list_vars_with_attr("iGlobalDumpVar",&num_ipas);
  fpa_list = rgst_list_vars_with_attr("dGlobalDumpVar",&num_fpas);
  n = MAX(num_ipas, num_fpas);
  palistn = ALLOT(Stringnam_t, n);
  palistv = ALLOT(int,         n);
  ierr = 0;
  for (i = 0; i< num_fpas; i++) {
    ProblemArray_t *prb = ProblemArray_find(fpa_list[i],NULL);
    CHECK_NAME_LEN("fpa name",fpa_list[i]);
    strcpy(palistn[i].name,fpa_list[i]);
    palistv[i] = prb->len;
    if (prb->len > 0) {
      ierr += DBWrite(idbid, fpa_list[i], prb->ptr, &prb->len, 1, DB_DOUBLE);
    }
  }
  if (ierr != 0) ctlerror(me,gv_errmsg_DBWrite);
  dims[0] = num_fpas;
  dims[1] = 24;
  if ( num_fpas > 0 ) {
    ierr =  DBWrite(idbid, "palistfn", palistn, dims, 2, DB_CHAR);
    ierr += DBWrite(idbid, "palistfv", palistv, dims, 1, DB_INT);
  }
  if (ierr != 0) ctlerror(me,gv_errmsg_DBWrite);
   for (i = 0; i<num_ipas; i++) {
      ProblemArray_t *prb = ProblemArray_find(ipa_list[i],NULL);
      CHECK_NAME_LEN("ipa name",ipa_list[i]);
      strcpy(palistn[i].name,ipa_list[i]);
      palistv[i] = prb->len;
      if (prb->len > 0) {
         ierr += DBWrite(idbid, ipa_list[i], prb->ptr, &prb->len, 1, DB_INT);
      }
      if (ierr != 0) ctlwarning(me,gv_errmsg_DBWrite);
   }
  dims[0] = num_ipas;
  dims[1] = 24;
  if ( num_ipas > 0 ) {
    ierr  = DBWrite(idbid, "palistin", palistn, dims, 2, DB_CHAR);
    ierr += DBWrite(idbid, "palistiv", palistv, dims, 1, DB_INT);
  }
  if (ierr != 0) ctlerror(me,gv_errmsg_DBWrite);
  for (i=0; i<num_ipas; i++) FREEMEM(ipa_list[i]);
  for (i=0; i<num_fpas; i++) FREEMEM(fpa_list[i]);
  FREEMEM(ipa_list);
  FREEMEM(fpa_list);
  FREEMEM(palistn);
  FREEMEM(palistv);
  nhead[NHEAD_NUM_FPA] = num_fpas;
  nhead[NHEAD_NUM_IPA] = num_ipas;
  dims[0] = NHEAD_NUM;
  ierr += DBWrite(idbid, "nhead", nhead, dims, 1, DB_INT);
  if (ierr != 0) ctlerror(me,gv_errmsg_DBWrite);
  for (ir=1; ir<=nreg; ir++) {
    sprintf(msg,"/Regional/reg%i",ir);
    if (rgst_write_struct_in_dir(idbid, msg, "Region_t", &(reg[ir]),NULL) != 0)
      ctlerror(me,gv_errmsg_rgst_write_struct_in_dir);
  }
  if (rgst_check_for_obj("freqMesgData") == TRUE) {
    for (i = 0; i < nfq ; i++) {
      fq[i].fqtp = fqtp[i];
      sprintf(dirname,"/Global/fqdat%i",i);
      if (rgst_write_struct_in_dir(idbid,dirname,"FreqMesg_t",&(fq[i]),NULL) != 0) {
        ctlerror(me,gv_errmsg_rgst_write_struct_in_dir);
      }
    }
  }
  if (rgst_check_for_obj("cycleMesgData") == TRUE) {
    for (i = 0; i < ncyc; i++ ) {
      cyc[i].cyctp = cyctp[i];
      sprintf(dirname,"/Global/cycdat%i",i);
      if (rgst_write_struct_in_dir(idbid,dirname,"CycleMesg_t",&(cyc[i]),NULL) != 0) {
        ctlerror(me,gv_errmsg_rgst_write_struct_in_dir);
      }
    }
  }
  if (rgst_check_for_obj("gparmData") == TRUE) {
    for (i = 0; i <= ngparm; i++ ) {
      sprintf(dirname,"/Global/gpdat%i",i);
      if (rgst_write_struct_in_dir(idbid,dirname,"Gparm_t",&(gparm[i]),NULL) != 0) {
        ctlerror(me,gv_errmsg_rgst_write_struct_in_dir);
      }
    }
  }
  DBSetDir(idbid,"/");
  if (DBMkDir (idbid, "Global/Edits") != 0) ctlerror(me,gv_errmsg_DBMkDir);
  if (DBSetDir(idbid, "Global/Edits") != 0) ctlerror(me,gv_errmsg_DBSetDir);
  n = 1;
  ierr  = DBWrite(idbid, "ntp", &ntp, &n, 1, DB_INT);
  if (ierr != 0) ctlerror(me,gv_errmsg_DBWrite);
  for (i=0; i<ntp; i++) {
    sprintf(dirname,"time_plot%i",i);
    if (rgst_write_struct_in_dir(idbid,dirname,"TimePlot_t",tpdata[i],NULL) != 0)
      ctlerror(me,gv_errmsg_rgst_write_struct_in_dir);
  }
  FT_FINALIZE(me, gv_hash_tbl, myflops)
} 
int Restart_write_domain(
  DBfile *idbid, 
  int iblk)      
{
  char *me = "Restart_write_domain";
  char msg[128];
  int i;
  double myflops = 0.0;
  FT_INITIALIZE(me, (&(domains[iblk]))->hash)
  sprintf(msg,"/domain%i",iblk);
  if (DBMkdir( idbid, msg) != 0) ctlerror(me,gv_errmsg_DBMkDir);
  if (DBSetDir(idbid, msg) != 0) ctlerror(me,gv_errmsg_DBSetDir);
  if (rgst_write_struct(idbid, "Domain_t", &(domains[iblk]),NULL) != 0)
    ctlerror(me,gv_errmsg_rgst_write_struct);
  if (DBSetDir(idbid, "../") != 0) ctlerror(me,gv_errmsg_DBSetDir);
  FT_FINALIZE(me, (&(domains[iblk]))->hash, myflops)
  return(0);
}
#endif
