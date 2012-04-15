#include "irs.h"
#include "irsobjects.h"
#include "irsrgst.h"
#include "BlockMapping.h"
#include "Extents.h"
#include "NodeList.h"
#include "UserList.h"
#include "ProblemArray.h"
#include "Hash.h"
typedef struct {
   char name[MAXLINE];
   int  type;
   NodeWindow_t *ndxin;
} SubMesh_t;
static SubMesh_t* SubMesh_find( char *name );
static void SubMesh_add( SubMesh_t *subm );
static void SubMesh_del( char *name ) ;

#ifdef SILO
static void SubMesh_wtdomain_quad ( DBfile *idbid, Domain_t *domain, SubMesh_t *subm);
static void SubMesh_wtdomain_point ( DBfile *idbid, Domain_t *domain, SubMesh_t *subm);
#endif

int SubMesh_parse( void ) {
   char *me = "SubMesh_parse";
   char op[MAXLINE];
   char type[MAXLINE];
   char msg[MAXLINE];
   int error = 0;
   SubMesh_t    *subm  = NULL;
   subm        = MALLOT(SubMesh_t, 1);
   subm->ndxin = NULL;
   sprintf(op,"submesh");
   error =  NodeWindow_read(op, &subm->ndxin);
   if (error != 0) {
      ctlwarning(me, "Error reading index list for submesh.");
      FREEMEM(subm);
      return(error);
   }
   geta(op);
   geta(subm->name);
   sprintf(op,"SubMesh_%s",subm->name);
   geta(type);
   subm->type = 0;
   if (!strcmp(type,"point")) {
      subm->type = 0;
   } else if (!strcmp(type,"quad")) {
      subm->type = 1;
   } else {
      sprintf(msg, "Type %s not a recognized type of sub mesh.",type);
      ctlwarning(me,msg);
   } 
   error = UserList_parse(op);
   if (error != 0) {
      ctlwarning(me,"Failed to read in list of variables for submesh.");
      NodeWindow_free(subm->ndxin);
      FREEMEM(subm);
      return(-1);
   }
   SubMesh_add(subm);
   return(0);
}
static void SubMesh_add( SubMesh_t *subm) {
   char *me = "SubMesh_add";
   char name[MAXLINE];
   char msg[MAXLINE];
   SubMesh_t *subm_ptr;
   subm_ptr = SubMesh_find(subm->name);
   sprintf(name,"SubMesh_%s",subm->name);
   if (subm_ptr != NULL) {
      sprintf(msg,"Attempting to replace submesh %s.",subm->name);
      ctlwarning(me,msg);
      SubMesh_del(subm->name);
   }
   hash_add(name, "SubMesh_t", subm, gv_hash_tbl);
}
static SubMesh_t *SubMesh_find( char *name ) {
   char myname[MAXLINE];
   SubMesh_t *subm;
   sprintf(myname,"SubMesh_%s",name);
   subm = (SubMesh_t *) hash_lookup_obj(myname, gv_hash_tbl);
   return(subm);
}
static void SubMesh_del( char *name ) {
   char myname[MAXLINE];
   SubMesh_t *subm;
   subm = SubMesh_find(name);
   if (subm != NULL) {
      sprintf(myname,"SubMesh_%s",name);
      NodeWindow_free(subm->ndxin);
      UserList_del(myname);
      hash_del2(myname, "SubMesh_t", gv_hash_tbl);
      FREEMEM(subm);
   }
}

#ifdef SILO
void SubMesh_wtroot ( DBfile *idbid, DBoptlist *ioptnod, char **rootnames ) {
   char *me = "SubMesh_wtroot";	 
   int i,j,k,n;
   int len;
   int gblk;
   int nw = 0;
   int *tag;
   int error = 0;
   char name[MAXLINE];
   char msg[MAXLINE];
   UserList_t *ul;
   SubMesh_t  *subm;
   HashElm_t **hashelm;
   NodeWindow_t *ndxin;
   char **meshnames;
   int *meshtypes;
   int *vartypes;
   hashelm = hash_get_elm_list(&n, "SubMesh_t", gv_hash_tbl);
   if (n == 0) {
      FREEMEM(hashelm);
      return;
   }
   tag = MALLOT(int, gnblk);
   for (j = 0; j < n; j++) {
      subm = (SubMesh_t *) hashelm[j]->obj;
      sprintf(name,"SubMesh_%s",subm->name);
      nw = 0;
      for (gblk = 0; gblk < gnblk; gblk++) {
         Extents_t ext1, ext2, ext3;
         tag[gblk] = 0;
         CPYEXT(ext2,gmap[gblk]);
         ndxin = subm->ndxin;
         while (ndxin != NULL) {
            if (gmap[gblk].ublk == ndxin->ublk) {
               CPYEXT(ext1,(*ndxin));
               len = extents_overlap(&ext2, &ext1, &ext3);
               if (len > 0) tag[gblk]++;
            }
            ndxin = ndxin->next;
         }
         nw = nw + tag[gblk];
      }
      meshtypes = MALLOT(int, nw);
      vartypes  = MALLOT(int, nw);
      meshnames = MALLOT(char *, nw);
      for (i = 0; i < nw; i++) {
          meshtypes[i] = 0;
          vartypes[i]  = 0;
      }
      i = 0;
      for(gblk = 0; gblk < gnblk; gblk++){
         if (tag[gblk] > 0) {
            for(k=0; k < tag[gblk]; k++){
                if(subm->type == 0){
                    sprintf(msg,"%s/SubMesh_%s",rootnames[gblk],subm->name);
                    meshtypes[i] = DB_POINTMESH;
                    vartypes[i] = DB_POINTVAR;
                }
                else{
                    sprintf(msg,"%s/SubMesh_%s_%d",rootnames[gblk],subm->name, k);
                    meshtypes[i] = DB_QUADMESH; 
                    vartypes[i]  = DB_QUADVAR;
                }
                meshnames[i] = strsave(msg);
                i++;
            }
         }
      } 
      if (i > 0)  {
         error += DBPutMultimesh(idbid, name, i, meshnames, meshtypes, ioptnod);
      } 
      ul = UserList_find(name);
      while (ul != NULL) {
         i = 0;
         for (gblk = 0; gblk < gnblk; gblk++) {
            if (tag[gblk] > 0) {
                for(k=0; k < tag[gblk]; k++){
                   FREEMEM(meshnames[i]);
                   if(subm->type == 0){
                       sprintf(msg,"%s/SubMesh_%s_%s",rootnames[gblk],subm->name,
                                ul->name);
                   }
                   else{
                       sprintf(msg,"%s/SubMesh_%s_%s_%d",rootnames[gblk],subm->name,
                                ul->name, k);
                   }
                   meshnames[i] = strsave(msg);
                   i++;
               }
            }
         }
         if (i > 0)  {
            char varn[MAXLINE];
            sprintf(varn,"SubMesh_%s_%s",subm->name, ul->name);
            error += DBPutMultivar(idbid, varn, i, meshnames, vartypes, 
	                            ioptnod);
         }
         ul = ul->next;
      }
      for(gblk = 0; gblk < gnblk; gblk++){
         if (tag[gblk] > 0){
              for(i = 0; i < tag[gblk]; i++){
                  FREEMEM(meshnames[i]);
              }
         }
      }
   }
   if (error != 0) {
      ctlwarning(me,"Error writing out sub mesh root info.");
   }
   FREEMEM(hashelm);
   FREEMEM(tag);
   FREEMEM(meshnames);
   FREEMEM(vartypes);
   FREEMEM(meshtypes);
}
#endif

#ifdef SILO
void SubMesh_wtdomain ( DBfile *idbid, Domain_t *domain) {
   int j, n;
   SubMesh_t  *subm;
   HashElm_t **hashelm;
   hashelm = hash_get_elm_list(&n, "SubMesh_t", gv_hash_tbl);
   if (n == 0) {
      FREEMEM(hashelm);
      return;
   }
    for(j=0; j<n; j++){
        subm = (SubMesh_t *) hashelm[j]->obj;
        if(subm->type == 0)
            SubMesh_wtdomain_point ( idbid, domain, subm);
        else
            SubMesh_wtdomain_quad ( idbid, domain, subm);
    }
   FREEMEM(hashelm);
}
#endif

#ifdef SILO
static void SubMesh_wtdomain_quad ( DBfile *idbid, Domain_t *domain, SubMesh_t *subm) {
   char *me = "SubMesh_wtdomain_quad";
   int i, j, k, m;
   int imax, jmax, kmax;
   int ii, jj, kk, ip;
   int error = 0;
   int dims[3];
   int node_c;
   int len = 0;
   int *ndx = NULL;
   double *x, *y, *z;
   double *val;
   double *coords[3];
   int gblk = domain->gblk;
   char name[MAXLINE];
   char meshnm[MAXLINE];
   UserList_t *ul;
   NodeWindow_t *ndxin;
   Extents_t ext1, ext2, ext3, newext;
      for(i=0; i<ndims; i++)
          dims[i] = 0;
      CPYEXT(ext2, gmap[gblk]);
      ndxin = subm->ndxin;
      m = 0;
      sprintf(meshnm, "SubMesh_%s", subm->name);
      while(ndxin != NULL){
          if(gmap[gblk].ublk == ndxin->ublk){
              CPYEXT(ext1, (*ndxin));
              len = extents_overlap(&ext2, &ext1, &ext3);
              if(len > 0){
                  sprintf(name,"SubMesh_%s_%d", subm->name, m);
                  dims[0] = ext3.imax - ext3.imin + 1;
                  dims[1] = ext3.jmax - ext3.jmin + 1;
                  if(ndims > 2)
                      dims[2] = ext3.kmax - ext3.kmin + 1;
             x   = MALLOT(double, len);
             y   = MALLOT(double, len);
             z   = MALLOT(double, len);
             val = MALLOT(double, len);
             TRSEXT(newext, ext3, gmap[gblk]);
             k = 0;
             if(ndims == 2){
                 for(jj = newext.jmin; jj <= newext.jmax; jj++){
                     for(ii = newext.imin; ii <= newext.imax; ii++){
                         ip = ii + domain->jp*jj;
                         x[k] = domain->x[ip];
                         y[k] = domain->y[ip];
                         k++;
                     }
                 }
                coords[0] = x;
                coords[1] = y;
                coords[2] = NULL;
             }
             else{
                for(kk = newext.kmin; kk <= newext.kmax; kk++){
                    for(jj = newext.jmin; jj <= newext.jmax; jj++){
                        for(ii = newext.imin; ii <= newext.imax; ii++){
                            ip = ii + domain->jp*jj + domain->kp*kk;
                            x[k] = domain->x[ip];
                            y[k] = domain->y[ip];
                            z[k] = domain->z[ip];
                            k++;
                        }
                    }
                }
                coords[0] = x;
                coords[1] = y;
                coords[2] = z;
             }
             error += DBPutQuadmesh(idbid, name, NULL, (float **) coords, dims,
                                ndims, DB_DOUBLE, DB_NONCOLLINEAR, NULL);
             ul = UserList_find(meshnm);
             while (ul != NULL) {
                char varn[MAXLINE];
                double *ptr = (double *)ProblemArray_ptr(ul->name, domain->hash);
                sprintf(varn,"SubMesh_%s_%s_%d",subm->name, ul->name, m);
                if (ptr != NULL) {
                   k = 0;
                   if(ndims == 2){
                         if((node_c = RGST_QUERY_OBJECT_ATTR(ul->name, "Nodal")) == TRUE){
                             jmax = newext.jmax;
                             imax = newext.imax;
                         }
                         else{
                             jmax = newext.jmax - 1;
                             imax = newext.imax - 1;
                         }
                         for(jj = newext.jmin; jj <= jmax; jj++){
                             for(ii = newext.imin; ii <= imax; ii++){
                                 ip = ii + domain->jp*jj;
                                 val[k] = ptr[ip];
                                 k++;
                             }
                         }
                     }
                   else{
                         if((node_c = RGST_QUERY_OBJECT_ATTR(ul->name, "Nodal")) == TRUE){
                             kmax = newext.kmax;
                             jmax = newext.jmax;
                             imax = newext.imax;
                         }
                         else{
                             kmax = newext.kmax - 1;
                             jmax = newext.jmax - 1;
                             imax = newext.imax - 1;
                         }
                        for(kk = newext.kmin; kk <= kmax; kk++){
                            for(jj = newext.jmin; jj <= jmax; jj++){
                                for(ii = newext.imin; ii <= imax; ii++){
                                    ip = ii + domain->jp*jj + domain->kp*kk;
                                    val[k] = ptr[ip];
                                    k++;
                                }
                            }
                        }
                   }
                   if(node_c)
                       error += DBPutQuadvar1(idbid, varn, name, (float *) val,
                                              dims, ndims, NULL, 0, DB_DOUBLE,
                                              DB_NODECENT, NULL);
                   else
                       error += DBPutQuadvar1(idbid, varn, name, (float *) val,
                                              dims, ndims, NULL, 0, DB_DOUBLE,
                                              DB_ZONECENT, NULL);
                }
                ul = ul->next;
             }
             FREEMEM(x);
             FREEMEM(y);
             FREEMEM(z);
             FREEMEM(val);
             FREEMEM(ndx);
          }
          m++;
       } 
          ndxin = ndxin->next;
       }
   if (error != 0) {
      ctlwarning(me, "Error writing sub mesh data.");
   }
}
#endif

#ifdef SILO
static void SubMesh_wtdomain_point ( DBfile *idbid, Domain_t *domain, SubMesh_t *subm) {
   char *me = "SubMesh_wtdomain_point";
   int i,j;
   int error = 0;
   double *x, *y, *z;
   double *val;
   double *coords[3];
   int gblk = domain->gblk;
   char name[MAXLINE];
   UserList_t *ul;
      int len = 0;
      int *ndx = NULL;
      sprintf(name,"SubMesh_%s",subm->name);
      NodeWindow_buildndx(subm->ndxin, NDX_REAL, NDX_NODAL, domain->gblk, &len,
                          &ndx);
      if (len > 0) {
         x   = MALLOT(double, len);
         y   = MALLOT(double, len);
         z   = MALLOT(double, len);
         val = MALLOT(double, len);
         if (ndims == 2) {
            for (i = 0; i < len; i++) {
               x[i] = domain->x[ndx[i]];
               y[i] = domain->y[ndx[i]];
            }
            coords[0] = x;
            coords[1] = y;
            coords[2] = NULL;
         } else {
            for (i = 0; i < len; i++) {
               x[i] = domain->x[ndx[i]];
               y[i] = domain->y[ndx[i]];
               z[i] = domain->z[ndx[i]];
            }
            coords[0] = x;
            coords[1] = y;
            coords[2] = z;
         }
         error += DBPutPointmesh(idbid,name, ndims,( float **) coords,
                            len, DB_DOUBLE, NULL);
         ul = UserList_find(name);
         while (ul != NULL) {
            char varn[MAXLINE];
            double *ptr = (double *)ProblemArray_ptr(ul->name, domain->hash);
            sprintf(varn,"SubMesh_%s_%s",subm->name, ul->name);
            if (ptr != NULL) {
               for (i = 0; i < len; i++) {
                  val[i] = ptr[ndx[i]];
               }
               error += DBPutPointvar1(idbid, varn, name,
                          (float *) val, len,  DB_DOUBLE, NULL);
            }
            ul = ul->next;
         }
         FREEMEM(x);
         FREEMEM(y);
         FREEMEM(z);
         FREEMEM(val);
         FREEMEM(ndx);
      }
   if (error != 0) {
      ctlwarning(me, "Error writing sub mesh data.");
   }
   return;
}
#endif

void SubMesh_free ( void ) {
   int i,n;
   char name[MAXLINE];
   SubMesh_t  *subm;
   HashElm_t **hashelm;
   hashelm = hash_get_elm_list(&n, "SubMesh_t", gv_hash_tbl);
   for (i = 0; i < n; i++) {
      subm = (SubMesh_t *) hashelm[i]->obj;
      SubMesh_del(subm->name);
   }
   FREEMEM(hashelm);
}
