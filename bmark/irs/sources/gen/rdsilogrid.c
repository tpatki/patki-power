#include "irs.h"
#include "irsblk.h"
#include "irsbndry.h"
#include "irscom.h"
#include "irsdmp.h"
#include "irsgen.h"
#include "BlockMapping.h"
#include "Extents.h"
#include "NodeList.h"

#ifdef SILO
int rdsilogrid(  void )
{
  char *me = "rdsilogrid";
  char msg[MAXLINE];
  char op[MAXLINE];
  char name[MAXLINE];
  int i;
  int gblk;
  int nlocaldom;
  int error;
  int *localdom;
  DBfile *idbid;
  Extents_t ext;
  geta(op);
  if (genmd != 1) {
     sprintf(msg, "Attempting to read silo mesh before memory has been allocated.\n\t\tAre you in merge phase?\n\t\t Did you forget the -sew on the command line?");
     ctlerror(me,msg);
  }
  comlock(dmp_nbaton);
  idbid = DBOpen (op, DB_PDB, DB_READ);
  if (idbid == NULL) {
     sprintf(msg,"Cannot open silo file %s.\n",op);
     ctlerror(me,msg);
  }
  decomp_setdir(idbid);
  decomp_read(idbid, name, 0, 0);
  error = DBSetDir(idbid,"/");
  DBShowErrors(DB_NONE, NULL);
  error = DBSetDir(idbid,"/Global/Nodelists");
  if (error != 0) error = DBSetDir(idbid,"Nodelists");
  if (error == 0) {
     NodeList_rdsilo(idbid,0);
  }
  DBShowErrors(DB_TOP, NULL);
  error = DBSetDir(idbid,"/");
  nlocaldom = 0;
  localdom = MALLOT(int,gnblk);
  for (gblk = 0; gblk < gnblk; gblk++) {
    if (gmap[gblk].lblk >= 0) {
       localdom[nlocaldom++] = gblk;
    }
  }
  calculate_mappings();
  for (i = 0; i < nlocaldom; i++) {
     gblk = localdom[i];
     if (gmap[gblk].proc == myid) {
        sprintf(op,"/%s%i",name,i);
        error = DBSetDir(idbid,op);
        TRSEXT(domains[nblk],gmap[gblk],gmap[gblk]);
        if (ndims == 2) {
           domains[nblk].kmin = 0;
           domains[nblk].kmax = 0;
           domains[nblk].type = QUAD2D;
        } else {
           domains[nblk].type = HEX3D;
        } 
        domains[nblk].sclnamix = sclnamix;
        initblk(nblk,&domains[nblk]);
        domains[nblk].gblk = gblk;
        domain_hash_tbl_rgst(&(domains[nblk]));
        CPYEXT(ext,domains[nblk]);
        rdsilomesh(idbid, "hydro_mesh", domains[nblk].x, domains[nblk].y, 
                   domains[nblk].z, domains[nblk].node, ext, domains[nblk].jp, 
                   domains[nblk].kp);
        nblk++;
        error = DBSetDir(idbid,"/");
     }
  }
  FREEMEM(localdom);
  DBClose(idbid);
  comunlock(dmp_nbaton);
  if (ifparallel) {
     bndry_init();
     initcom( NULL, 0);
     varcom_bufinit();
  }
  return(0);
}
#endif
