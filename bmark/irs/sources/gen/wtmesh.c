static int wtmesh_silo(char *filename);
#include "irs.h"
#include "irscom.h"
#include "irsdmp.h"
#include "irsgen.h"
#include "Extents.h"
#include "NodeList.h"

#ifdef SILO
int wtmesh( void )
{
   char *me = "wtmesh";
   int error = 0;
   char op[MAXLINE];
   char msg[MAXLINE];
   geta(op);
   if (!strcmp("silo",op)) {
      geta(op);
      error = wtmesh_silo(op);
   } else {
      sprintf(msg,"Output Mesh Format - %s not supported.\n",op);
      ctlnotice(me,msg);
      error = 1;
   }
   return(error);
}
static int wtmesh_silo(char *filename) {
    char *me = "wtmesh_silo";
    char msg[MAXLINE];
    char dumpname[MAXLINE];
    char name[MAXLINE];
    char **meshnames;
    int iblk;
    int error;
    int *meshtypes;
    Extents_t ext;
    DBfile    *outFile;
    DBoptlist *options;
    error = 0;
    if (ifparallel) {
       outFile = openpdmp(filename, -1, myid, 1, dumpname);
    } else {
       outFile = openpdmp(filename, -1, -1, 1, dumpname);
    } 
    if (outFile == NULL) {
       sprintf(msg,"Cannot open mesh file %s.",filename);
       ctlwarning(me,msg);
       return(-1);
    }
    sprintf(name,"Decomposition");
    if (DBMkdir(outFile, name) != 0) ctlerror(me,gv_errmsg_DBMkDir);
    if (DBSetDir(outFile, name) != 0) ctlerror(me,gv_errmsg_DBSetDir);
    decomp_write(outFile,"domain");
    if (DBSetDir(outFile, "../") != 0) ctlerror(me,gv_errmsg_DBSetDir);
    NodeList_wtsilo(outFile);
    for (iblk = 0; iblk < nblk; iblk++) {
       options = DBMakeOptlist( MAXOPTS );
       set_silo_option(options, iblk);
       sprintf(name,"/domain%i",iblk);
       if (DBMkdir(outFile, name) != 0) ctlerror(me,gv_errmsg_DBMkDir);
       if (DBSetDir(outFile, name) != 0) ctlerror(me,gv_errmsg_DBSetDir);
       CPYEXT(ext,domains[iblk]);
       wtsilomesh(outFile, options, "hydro_mesh", domains[iblk].x, 
                  domains[iblk].y, domains[iblk].z, ext, 
		  domains[iblk].jp, domains[iblk].kp);
    }
   DBFreeOptlist(options);
   options = DBMakeOptlist( MAXOPTS );
   meshnames = (char **) calloc(nblk, sizeof(char *));
   meshtypes = MALLOT(int,nblk);
   for (iblk = 0; iblk < nblk; iblk++) {
      meshnames[iblk] = MALLOT(char,100);
      sprintf(meshnames[iblk],"/domain%i/hydro_mesh",iblk);
      meshtypes[iblk] = DB_QUADMESH;
   }
   error += DBAddOption( options, DBOPT_DTIME, &ttime );
   error += DBAddOption( options, DBOPT_CYCLE, &cycle );
   error += DBSetDir(outFile, "/");   
   error += DBPutMultimesh(outFile,"hydro_mesh", nblk, meshnames,
                           meshtypes, options);
   for (iblk = 0; iblk < nblk; iblk++) {
      FREEMEM(meshnames[iblk]);  
   }
   DBClose(outFile);
   sprintf(msg,"Silo mesh %s has been written.",dumpname);
   ctlmsg(msg);
   return(error);
}
#endif
