#include "irs.h"
#include "irsblk.h"
#include "irsgen.h"
#include "irsreg.h"
#include "irsrgst.h"
#include "BlockMapping.h"
#include "Extents.h"
#include "NodeList.h"
#include "Hash.h"
#include "ProblemArray.h"
#include "Rgst.h"
#define ALTMESH_SETSTR(ind, ptr) \
   ind[0][2] = 1; \
   ind[1][2] = ptr->jp; \
   ind[2][2] = ptr->kp;
#define ALTMESH_SETIND(ind, ptr) \
   ind[0][0] = ptr->imin; \
   ind[0][1] = ptr->imax; \
   ind[1][0] = ptr->jmin; \
   ind[1][1] = ptr->jmax; \
   ind[2][0] = ptr->kmin; \
   ind[2][1] = ptr->kmax; 
#define ALTMESH_CPYIND(ind1, ind2) \
   ind1[0][0] = ind2[0][0]; \
   ind1[0][1] = ind2[0][1]; \
   ind1[0][2] = ind2[0][2]; \
   ind1[1][0] = ind2[1][0]; \
   ind1[1][1] = ind2[1][1]; \
   ind1[1][2] = ind2[1][2]; \
   ind1[2][0] = ind2[2][0]; \
   ind1[2][1] = ind2[2][1]; \
   ind1[2][2] = ind2[2][2]; 
#define ALTMESH_SPLIT    0
#define ALTMESH_KEEP     1
#define ALTMESH_REMOVE   2
struct AltMeshInput_t_ {
   int type;
   NodeWindow_t *afflicted;
   int      len;
   int     *alter;
   int      nfrac;
   double  *frac;
} ;
typedef struct AltMeshInput_t_ AltMeshInput_t;
typedef struct {
   NodeWindow_t *ndxin;
   int nnalls_old;
   int *ireg_old;
   int *lnkmix_old;
   int *grdpnt_old;
   int len;
   int *tag;
   int *old;
   int *new;
   int *high;
   int *low;
   double *frac;
   int i1;
   int i2;
   int i3;
   int in[3][3];
   int ing[3][3];
   int inold[3][3];
   Extents_t gext;
} AltMeshDomain_t ;
static int  altmesh_validate( AltMeshInput_t *altm) ;
static void altmesh_free( AltMeshInput_t *altlist ) ;
static void altmesh_init(AltMeshInput_t *altm_ptr) ;
static void altmesh_fixNodeList(AltMeshInput_t *altm) ;
static void altmesh_fixNodeWindow( NodeWindow_t *ndxin, AltMeshInput_t *altm) ;
static void altmesh_split( AltMeshInput_t *altm ) ;
static void altmesh_domain_split( Domain_t *domain, NodeWindow_t *ndxin,  AltMeshInput_t *altm ) ;
static void altmesh_splitvars(AltMeshDomain_t *altdom, AltMeshInput_t *altm, Domain_t *domain);
static void altmesh_extents_alter(Extents_t *extin, NodeWindow_t *ndxin, AltMeshInput_t *altm ) ;
static void altmesh_fixdecomp(AltMeshInput_t * altm) ;
static void altmesh_copy( void *ptr1, void *ptr2, int zonal, int mixed, RGST_Datatype_t type, AltMeshDomain_t *altdom, Domain_t *domain);
static void altmesh_setindex(AltMeshDomain_t *altdom, NodeWindow_t *ndxin, AltMeshInput_t *altm);
static void altmesh_interp(double *x, AltMeshDomain_t *altdom, AltMeshInput_t *altm);
static void altmesh_setmixmat(AltMeshDomain_t *altdom, Domain_t *domain, AltMeshInput_t *altm) ;
int altmesh( void ) {
   char *me = "altmesh";
   char op[MAXLINE];
   char name[MAXLINE];
   char msg[MAXLINE];
   int gotone;
   int cflag;
   int error;
   int imin, imax;
   int i,j,k;
   AltMeshInput_t *altm = NULL;
   AltMeshInput_t *altm_ptr = NULL;
   NodeWindow_t *start  = NULL;
   NodeWindow_t *finish = NULL;
   NodeWindow_t *ndxin = NULL;
   gotone = 1;
   while (gotone) {
      peekc(op);
      if ((!strcmp("split",op)) ||
          (!strcmp("keep",op)) ||
          (!strcmp("add",op)) ||
          (!strcmp("remove",op))) {
         int nlines, logical;
         geta(op);
         sprintf(name,op);
         altm_ptr = MALLOT(AltMeshInput_t,1);
         altmesh_init(altm_ptr);
         error  = 0;
         error += NodeWindow_read(name,&altm_ptr->afflicted);
         error += NodeWindow_read(name,&finish);
         error += NodeWindow_range(altm_ptr->afflicted,finish, 0, 0);
         if (error != 0) {
            sprintf(msg,"Bad index list given in altmesh block.");
            ctlwarning(me,msg);
            return(-1);
         }
         NodeWindow_free(finish);
         ndxin = altm_ptr->afflicted;
         logical = ndxin->logical;
         imin = MIN(ndxin->in[logical][0], ndxin->in[logical][1]);
         imax = MAX(ndxin->in[logical][0], ndxin->in[logical][1]);
         altm_ptr->len   = imax - imin + 1;
         if ( altm_ptr->len <= 0) {
            sprintf(msg,"Bad index range in altmesh block.");
            ctlwarning(me,msg);
            altmesh_free( altm_ptr);
            return(-1);
         }
         altm_ptr->alter    = MALLOT(int, altm_ptr->len);
         for (i = 0; i < altm_ptr->len; i++) {
            altm_ptr->alter[i] = 0;
         }
         if (!strcmp("split",op)) {
            nlines = geti(&cflag);
            altm_ptr->type   = ALTMESH_SPLIT;
            for (i = 0; i < altm_ptr->len - 1; i++) {
               altm_ptr->alter[i] = nlines;
            }
            altm_ptr->alter[i] = 0;
	    altm_ptr->nfrac = nlines * altm_ptr->len;
	    altm_ptr->frac = MALLOT(double, altm_ptr->nfrac);
	    for (i = 0; i < altm_ptr->nfrac; i++) altm_ptr->frac[i] = -1.;
            k = 0;
            for (i = 0; i < altm_ptr->len - 1; i++) {
               double denom = 1.0 / ((double) (altm_ptr->alter[i] + 1));
               for (j = 1; j <= altm_ptr->alter[i]; j++) {
                   altm_ptr->frac[k++] = j * denom;
               }
            }
         } else if (!strcmp("add",op)) {
            int    n      = 0;
	    double *fsave = MALLOT(double,altm_ptr->len);
	    int    *lsave = MALLOT(int,altm_ptr->len);
	    int    *csave = MALLOT(int,altm_ptr->len);
            altm_ptr->type   = ALTMESH_SPLIT;
            peekc(op);
            while (!isalpha(op[0])) {
               double val  = getf(&cflag);
	       int    line = (int )val;
               fsave[n] = (val - (double)line);
               lsave[n] = line - 1;
               csave[n] = altm_ptr->alter[line - 1];
	       altm_ptr->alter[line - 1] += 1;
               n++;
               peekc(op);
            }
	    altm_ptr->nfrac = n * altm_ptr->len;
	    altm_ptr->frac = MALLOT(double, altm_ptr->nfrac);
	    for (i = 0; i < altm_ptr->nfrac; i++) altm_ptr->frac[i] = -1.;
	    for (i = 0; i < n; i++) {
	       int ip = 0;
	       for (j = 0; j < lsave[i]; j++) {
	          ip += altm_ptr->alter[j];
	       }
	       ip += csave[i];
	       altm_ptr->frac[ip] = fsave[i];
	    }
	    FREEMEM(csave);
	    FREEMEM(lsave);
	    FREEMEM(fsave);
         } else if (!strcmp("keep",op)) {
            nlines = geti(&cflag);
            altm_ptr->type   = ALTMESH_KEEP;
            for (i = 0; i < altm_ptr->len; i += nlines) {
               altm_ptr->alter[i] = -1;
            }
         } else if (!strcmp("remove",op)) {
            altm_ptr->type   = ALTMESH_REMOVE;
            for (i = 0; i < altm_ptr->len; i ++) {
               altm_ptr->alter[i] = -1;
            }
         } 
      } else if (!strcmp("end",op)) {
         geta(op);
         gotone = 0;
      } else {
         gotone = 0;
      } 
   }
   error = altmesh_validate(altm_ptr);
   if (error != 0) return(-1);
   if (altm_ptr->type == ALTMESH_KEEP) {
   } else if (altm_ptr->type == ALTMESH_REMOVE) {
   } else if (altm_ptr->type == ALTMESH_SPLIT) {
      altmesh_split(altm_ptr);
   } 
   altmesh_free(altm_ptr);
   return(0);
}
static void altmesh_free( AltMeshInput_t *altlist ) {
   NodeWindow_free(altlist->afflicted);
   if (altlist->len > 0) FREEMEM(altlist->alter);
   if (altlist->nfrac > 0) FREEMEM(altlist->frac);
   FREEMEM(altlist);
}
static int altmesh_validate( AltMeshInput_t *altm) {
   if (altm == NULL) return(-1);
   return(0);
}
static void altmesh_init(AltMeshInput_t *altm_ptr) {
   altm_ptr->type      = -1;
   altm_ptr->len       = 0;
   altm_ptr->nfrac     = 0;
   altm_ptr->alter     = NULL;
   altm_ptr->frac      = NULL;
   altm_ptr->afflicted = NULL;
}
static void altmesh_fixNodeList(AltMeshInput_t *altm) {
   NodeList_t *NodeList_ptr;
   NodeWindow_t *ndxin;
   NodeWindow_t *ndxin_prev;
   int i,n;
   char **list;
   list = rgst_list_objs_by_type(&n,"NodeList_t");
   if (n == 0) return;
   ndxin_prev = NULL;
   for (i = 0; i < n; i++) {
      NodeList_ptr = (NodeList_t *)rgst_get_t(list[i],"NodeList_t");
      ndxin = NodeList_ptr->list;
      while (ndxin != NULL) {
         int len;
         altmesh_fixNodeWindow(ndxin, altm);
         if (ndims == 2) {
            len = (ndxin->imax - ndxin->imin + 1) *
                  (ndxin->jmax - ndxin->jmin + 1);
         } else {
            len = (ndxin->imax - ndxin->imin + 1) *
                  (ndxin->jmax - ndxin->jmin + 1) *
                  (ndxin->kmax - ndxin->kmin + 1);
         }
         if (len <= 0) {
            FREEMEM(ndxin);
         } else {
            ndxin_prev = ndxin;
         }
         ndxin = ndxin->next;
      }
      FREEMEM(list[i]);
   }
   FREEMEM(list);
}
static void altmesh_fixNodeWindow( NodeWindow_t *ndxin, AltMeshInput_t *altm) {
   int logical ;
   Extents_t  ext;
   NodeWindow_t *andxin;
   int in[3][3];
   andxin = altm->afflicted;
   while (andxin != NULL) {
      if (andxin->ublk == ndxin->ublk) {
         logical = andxin->logical;
         CPYEXT(ext,(*ndxin));      
         altmesh_extents_alter(&ext, andxin, altm);
         CPYEXT((*ndxin),ext);      
         ALTMESH_SETIND(in, (&ext));
         if (ndxin->in[logical][2] > 0) {
            ndxin->in[logical][0] = in[logical][0];
            ndxin->in[logical][1] = in[logical][1];
         } else {
            ndxin->in[logical][0] = in[logical][1];
            ndxin->in[logical][1] = in[logical][0];
         } 
      }
      andxin = andxin->next;
   }
}
static void altmesh_split( AltMeshInput_t *altm ) {
   int iblk;
   int gblk;
   int len;
   NodeWindow_t *ndxin;
   Extents_t ext1, ext2, ext3;
   regen_pregen();
   regen_reset();
   ndxin = altm->afflicted;
   while (ndxin != NULL) {
      CPYEXT(ext1, (*ndxin));
      for (iblk = 0; iblk < nblk; iblk++) {
         gblk = domains[iblk].gblk;
         if (gmap[gblk].ublk != ndxin->ublk) continue;
         CPYEXT(ext2, gmap[gblk]);
         len = extents_overlap(&ext1, &ext2, &ext3);
         if (len > 0) altmesh_domain_split(&domains[iblk], ndxin, altm) ;
      }
      ndxin = ndxin->next;
   }
   altmesh_fixNodeList(altm);
   altmesh_fixdecomp(altm);
   for (iblk = 0; iblk < nblk; iblk++) {
      BoundaryCondition_merge(&domains[iblk]);
      Source_merge(&domains[iblk]);
   }
   regen();
}
static void altmesh_domain_split( Domain_t *domain, NodeWindow_t *ndxin,  AltMeshInput_t *altm ) {
   int gblk;
   int i1, i2, i3;
   int i,j,k,io;
   AltMeshDomain_t *altdom;
   altdom = MALLOT(AltMeshDomain_t, 1);
   altdom->ndxin = ndxin;
   regndx(domain);
   gblk = domain->gblk;
   CPYEXT(altdom->gext, gmap[gblk]);
   ALTMESH_SETIND(altdom->ing,(&gmap[gblk]));
   ALTMESH_SETSTR(altdom->ing,(&gmap[gblk]));
   ALTMESH_SETIND(altdom->inold,domain);
   ALTMESH_SETSTR(altdom->inold,domain);
   altmesh_extents_alter(&altdom->gext, ndxin, altm);
   altdom->nnalls_old = domain->nnalls;
   domain->nnodes = 0;
   domain_setlimits(domain, altdom->gext.imax - altdom->gext.imin + 1,
                            altdom->gext.jmax - altdom->gext.jmin + 1,
                            altdom->gext.kmax - altdom->gext.kmin + 1);
   ALTMESH_SETIND(altdom->in,domain);
   ALTMESH_SETSTR(altdom->in,domain);
   domain_allot_fields(domain);
   domain_setpa(domain);
   meshgen_setlogical(ndxin->logical, &i1, &i2, &i3);
   altdom->i1 = i1;
   altdom->i2 = i2;
   altdom->i3 = i3;
   altdom->len  = altdom->in[i1][1] - altdom->in[i1][0] + 1 + NPNL + NPNR;
   altdom->old  = MALLOT(int, altdom->len); 
   altdom->tag  = MALLOT(int, altdom->len); 
   altdom->new  = MALLOT(int, altdom->len); 
   altdom->high = MALLOT(int, altdom->len); 
   altdom->low  = MALLOT(int, altdom->len); 
   altdom->frac = MALLOT(double, altdom->len); 
   for (i = 0; i < altdom->len; i++) {
      altdom->tag[i]  = 0;
      altdom->new[i]  = i;
      altdom->old[i]  = 0;
      altdom->high[i] = i + 1;
      altdom->low[i]  = i - 1;
      altdom->frac[i] = -1.;
   }
   altmesh_setindex(altdom, ndxin, altm);
   altmesh_splitvars(altdom, altm, domain);
   domain_setpa(domain);
   altmesh_interp(domain->x,altdom, altm);
   altmesh_interp(domain->y,altdom, altm);
   altmesh_interp(domain->xdot,altdom, altm);
   altmesh_interp(domain->ydot,altdom, altm);
   if (ndims == 3) {
      altmesh_interp(domain->z,altdom, altm);
      altmesh_interp(domain->zdot,altdom, altm);
   }

   FREEMEM(altdom->old);
   FREEMEM(altdom->tag);
   FREEMEM(altdom->new);
   FREEMEM(altdom->high);
   FREEMEM(altdom->low);
   FREEMEM(altdom->frac);
   FREEMEM(altdom);
}
static void altmesh_splitvars(AltMeshDomain_t *altdom, AltMeshInput_t *altm, Domain_t *domain)
{
   char *name;	 
   int i,j,k,n;
   int len;
   int mixed;
   int in[3][3];
   int i1 = altdom->i1;
   int i2 = altdom->i2;
   int i3 = altdom->i3;
   int    *iptr;
   void **ptr;
   double *dptr;
   RGST_AttributeElem_t *permvars;
   RGST_AttributeElem_t *permvars_ptr;
   ProblemArray_t *prb;
   ALTMESH_CPYIND(in,altdom->in);
   altdom->ireg_old   = MALLOT(int, domain->namix);
   altdom->lnkmix_old = MALLOT(int, domain->mixmax);
   altdom->grdpnt_old = MALLOT(int, domain->mixmax);
   for (i = 0; i < domain->namix; i++) {
      altdom->ireg_old[i] = domain->ireg[i];
      domain->ireg[i] = 0;
   }
   for (i = 0; i < domain->mixmax; i++) {
      altdom->lnkmix_old[i] = domain->lnkmix[i];
      altdom->grdpnt_old[i] = domain->grdpnt[i];
   }
   altmesh_setmixmat(altdom, domain, altm);
   permvars     = rgst_list_attr(A_OBJECT, "Zonal");
   permvars_ptr = permvars;
   while ( permvars_ptr != NULL ) {
      name    = ATTR_GET_OBJECT_NAME(permvars_ptr)
      prb     = ProblemArray_find(name, NULL);
      ptr     = ATTR_GET_FIELD_ADDR(domain, "Domain_t", name);
      mixed      = 0;
      len = domain->nnalls;
      if  (RGST_QUERY_OBJECT_ATTR(name, "Mixed")) {
 	 len = domain->namix;
	 mixed = 1;
      }
      if (prb->type == R_DOUBLE) {
         dptr = MALLOT(double,len);
         for (i = 0; i < len; i++) {
            dptr[i] = 0.;
         }
         altmesh_copy(*ptr, (void *)dptr, 1, mixed, prb->type, altdom, domain);
         FREEMEM(*ptr);
         *ptr = dptr;
      } else if (prb->type == R_INT) {
	 if (strcmp("ireg",name)) {
            iptr = MALLOT(int,len);
            for (i = 0; i < len; i++) {
               iptr[i] = 0;
            }
            altmesh_copy(*ptr, (void *)iptr, 1, mixed, prb->type, altdom, domain);
            FREEMEM(*ptr);
            *ptr = iptr;
	 }
      }
      permvars_ptr = permvars_ptr->next;
   }
   permvars     = rgst_list_attr(A_OBJECT, "Nodal");
   permvars_ptr = permvars;
   while ( permvars_ptr != NULL ) {
      name    = ATTR_GET_OBJECT_NAME(permvars_ptr)
      prb     = ProblemArray_find(name, NULL);
      ptr     = ATTR_GET_FIELD_ADDR(domain, "Domain_t", name);
      len = domain->nnalls;
      if  (RGST_QUERY_OBJECT_ATTR(name, "SlideData")) {
 	 len = domain->nnodes;
      }
      if (prb->type == R_DOUBLE) {
         dptr = MALLOT(double,len);
         for (i = 0; i < len; i++) {
            dptr[i] = 0.;
         }
         altmesh_copy(*ptr, (void *)dptr, 0, 0, prb->type, altdom, domain);
         FREEMEM(*ptr);
         *ptr = dptr;
      } else if (prb->type == R_INT) {
         iptr = MALLOT(int,len);
         for (i = 0; i < len; i++) {
            iptr[i] = 0;
         }
         altmesh_copy(*ptr, (void *)iptr, 0, 0, prb->type, altdom, domain);
         FREEMEM(*ptr);
         *ptr = iptr;
      }
      permvars_ptr = permvars_ptr->next;
   }
   for (i = 0; i < domain->nnalls; i++) {
      if (domain->ireg[i] < 0) domain->ireg[i] = -1;
   }
   regndx(domain);
   FREEMEM(altdom->ireg_old);
   FREEMEM(altdom->lnkmix_old);
   FREEMEM(altdom->grdpnt_old);
}
static void altmesh_copy( void *ptr1, void *ptr2, int zonal, int mixed, RGST_Datatype_t type, AltMeshDomain_t *altdom, 
                      Domain_t *domain)
{
   int i, j, k;
   int ipold, ipnew;
   int in[3][3];
   int inold[3][3];
   int i1 = altdom->i1;
   int i2 = altdom->i2;
   int i3 = altdom->i3;
   int    *ireg1   = altdom->ireg_old;
   int    *lnkmix1 = altdom->lnkmix_old;
   int    *ireg2   = domain->ireg;
   int    *lnkmix2 = domain->lnkmix;
   int    *iptr1;
   int    *iptr2;
   double *dptr1;
   double *dptr2;
   int *old = altdom->old;
   int *new = altdom->new;
   ALTMESH_CPYIND(in,altdom->in);
   ALTMESH_CPYIND(inold,altdom->inold);
   if (zonal) {
      in[i1][1]--;
      in[i2][1]--;
      in[i3][1]--;
   }
   if (type == R_INT) {
      iptr1 = (int *)ptr1;
      iptr2 = (int *)ptr2;
   } else if (type == R_DOUBLE) {
      dptr1 = (double *)ptr1;
      dptr2 = (double *)ptr2;
   } 
   if (ndims == 2) {
      for (j = in[i2][0]; j <= in[i2][1]; j++) {
         for (i = in[i1][0]; i <= in[i1][1]; i++) {
            ipold = old[i] * inold[i1][2] + j * inold[i2][2];
            ipnew = new[i] * in[i1][2] + j * in[i2][2];
            if (type == R_INT) {
               iptr2[ipnew] = iptr1[ipold];
            } else if (type == R_DOUBLE) {
               dptr2[ipnew] = dptr1[ipold];
            } 
            if ((mixed) && (ireg2[ipnew] < 0)) {
               int grd_old = -ireg1[ipold];
               int grd_new = -ireg2[ipnew];
               while (grd_old > 0) {
                  if (type == R_INT) {
                     iptr2[grd_new] = iptr1[grd_old];
                  } else if (type == R_DOUBLE) {
                     dptr2[grd_new] = dptr1[grd_old];
                  } 
                  grd_old = lnkmix1[grd_old - altdom->nnalls_old];
                  grd_new = lnkmix2[grd_new - domain->nnalls];
               }
            }
         }
      }
   } else {
      for (k = in[i3][0]; k <= in[i3][1]; k++) {
         for (j = in[i2][0]; j <= in[i2][1]; j++) {
            for (i = in[i1][0]; i <= in[i1][1]; i++) {
               ipold = old[i] * inold[i1][2] + j * inold[i2][2] + k * inold[i3][2];
               ipnew = new[i] * in[i1][2] + j * in[i2][2] + k * in[i3][2];
               if (type == R_INT) {
                 iptr2[ipnew] = iptr1[ipold];
               } else if (type == R_DOUBLE) {
                 dptr2[ipnew] = dptr1[ipold];
               }   
               if ((mixed) && (ireg2[ipnew] < 0)) {
                  int grd_old = -ireg1[ipold];
                  int grd_new = -ireg2[ipnew];
                  while (grd_old > 0) {
                     if (type == R_INT) {
                        iptr2[grd_new] = iptr1[grd_old];
                     } else if (type == R_DOUBLE) {
                        dptr2[grd_new] = dptr1[grd_old];
                     } 
                     grd_old = lnkmix1[grd_old - altdom->nnalls_old];
                     grd_new = lnkmix2[grd_new - domain->nnalls];
                  }
               }
            }
         }
      }
   }
}
static void altmesh_extents_alter(Extents_t *extin, NodeWindow_t *ndxin, AltMeshInput_t *altm ) {
   int i,j;
   int imin, imax;
   int imin0, imax0;
   int logical;
   logical = ndxin->logical;
   extents_getlogical(extin, logical, &imin0, &imax0);
   imin = imin0;
   imax = imax0;
   j = ndxin->in[logical][0];
   for (i = 0; i < altm->len; i++) {
      if (j < imin0) {
         imin += altm->alter[i];
         imax += altm->alter[i];
      }
      if ((j < imax0) && (j >= imin0)) {
         if (imax0 != imin0) imax += altm->alter[i];
      }
      j += ndxin->in[logical][2];
   }
   extents_setlogical(extin, logical, &imin, &imax);
}
static void altmesh_fixdecomp(AltMeshInput_t * altm) {
   int ublk;
   int gblk;
   int ibnd;
   NodeWindow_t *ndxin;
   Extents_t ext;
   ndxin = altm->afflicted;
   while (ndxin != NULL) {
      ublk = ndxin->ublk;
      CPYEXT(ext,umap[ublk]);
      altmesh_extents_alter(&ext, ndxin, altm);
      CPYEXT(umap[ublk],ext);
      STREXT(umap[ublk],umap[ublk].jp, umap[ublk].kp);
      for (ibnd = 0; ibnd < umap[ublk].nbnd; ibnd++) {
         CPYEXT(ext,umap[ublk].bnd[ibnd]);
         altmesh_extents_alter(&ext, ndxin, altm);
         CPYEXT(umap[ublk].bnd[ibnd],ext);
      }
      for (gblk = 0; gblk < gnblk; gblk++) {
         if (gmap[gblk].ublk != ublk) continue;
         CPYEXT(ext,gmap[gblk]);
         altmesh_extents_alter(&ext, ndxin, altm);
         CPYEXT(gmap[gblk],ext);
         STREXT(gmap[gblk],gmap[gblk].jp, gmap[gblk].kp);
         for (ibnd = 0; ibnd < gmap[gblk].nbnd; ibnd++) {
            CPYEXT(ext,gmap[gblk].bnd[ibnd]);
            altmesh_extents_alter(&ext, ndxin, altm);
            CPYEXT(gmap[gblk].bnd[ibnd],ext);
         }
      }
      ndxin = ndxin->next;
   }
}
static void altmesh_setindex(AltMeshDomain_t *altdom, NodeWindow_t *ndxin, 
                      AltMeshInput_t *altm) 
{
   int i1;
   int m, n, j, k, i;
   int *new  = altdom->new;
   int *old  = altdom->old;
   int *high = altdom->high;
   int *low  = altdom->low;
   int *tag  = altdom->tag;
   int *alter;
   double *frac = altdom->frac;
   i1 = altdom->i1;
   alter = MALLOT(int, altdom->len);
   for (i = 0; i < altdom->len; i++) {
      alter[i] = 0;
   }
   j = ndxin->in[i1][0];
   m = 0;
   n  = MAX(altdom->ing[i1][0],ndxin->in[i1][0]);
   if (ndxin->in[i1][2] < 0) n = altdom->ing[i1][1];
   for (i = 0; i < altm->len; i++) {
      if ((j >= altdom->ing[i1][0]) && (j <= altdom->ing[i1][1])) {
         alter[j - altdom->ing[i1][0] + NPNL] = altm->alter[i];
         for (k = 0; k <= altm->alter[i]; k++) {
            if (k > 0) {
               frac[n - altdom->ing[i1][0] + NPNL] = altm->frac[m + k - 1];
            }
            n +=  ndxin->in[i1][2];
         }
      }
      j += ndxin->in[i1][2];
      if (altm->alter[i] > 0) m += altm->alter[i];
   }
   n = altdom->in[i1][0];
   for (i = altdom->inold[i1][0]; i <= altdom->inold[i1][1]; i++) {
      for (k = 0; k <= alter[i]; k++) {
         old[n] = i;
         n++;
      }
   }
   for (i = altdom->in[i1][0]; i <= altdom->in[i1][1]; i++) {
      if (alter[old[i]] < 0) tag[i] = 1;
      if ((alter[old[i]] > 0) && (old[i] == old[i - 1])) tag[i] = 1;
   }
   for (i = 0; i < altdom->len; i++) {
      if (tag[i] > 0) {
          n = i;
          while ((n < altdom->len - 1) && (old[n] == old[i])) n++;
          high[i] = new[n];
          n = i;
          while ((n > 0) && (old[n] == old[i])) n--;
          low[i] = new[n + 1];
      }
   }
   FREEMEM(alter);
}
static void altmesh_setmixmat(AltMeshDomain_t *altdom, Domain_t *domain, 
                       AltMeshInput_t *altm) 
{
   int i, j, k, n; 
   int ipold, ipnew;
   int grd, grd_new, grd_old;
   int *ireg1   = altdom->ireg_old;
   int *lnkmix1 = altdom->lnkmix_old;
   int *grdpnt1 = altdom->grdpnt_old;
   int *ireg2   = domain->ireg;
   int *lnkmix2 = domain->lnkmix;
   int *grdpnt2 = domain->grdpnt;
   int *old = altdom->old;
   int *new = altdom->new;
   int i1   = altdom->i1;
   int i2   = altdom->i2;
   int i3   = altdom->i3;
   int in[3][3];
   int inold[3][3];
   ALTMESH_CPYIND(in,altdom->in);
   ALTMESH_CPYIND(inold,altdom->inold);
   if (ndims == 2) {
      for (j = in[i2][0]; j < in[i2][1]; j++) {
         for (i = in[i1][0]; i < in[i1][1]; i++) {
            ipold = old[i] * inold[i1][2] + j * inold[i2][2];
            ipnew = new[i] * in[i1][2] + j * in[i2][2];  
            ireg2[ipnew] = ireg1[ipold];
            if (ireg1[ipold] < 0) {
               grd_old = -ireg1[ipold]; 
               for (n = domain->nnalls; n < domain->namix; n++) {
                  if (ireg2[n] == 0) break;
               }
               grd_new = n;
               ireg2[ipnew]                      = -grd_new;
               grdpnt2[grd_new - domain->nnalls] = ipnew;
               ireg2[grd_new]                    = ireg1[grd_old];
               grd_old = lnkmix1[grd_old - altdom->nnalls_old];
               while (grd_old > 0) {
                  grd = grd_new;
                  for (n = domain->nnalls; n < domain->namix; n++) {
                     if (ireg2[n] == 0) break;
                  }
                  grd_new = n;
                  ireg2[grd_new]                    = ireg1[grd_old];
                  lnkmix2[grd - domain->nnalls]     = grd_new;
                  grdpnt2[grd_new - domain->nnalls] = ipnew;
                  grd_old = lnkmix1[grd_old - altdom->nnalls_old];
               }
               lnkmix2[grd_new - domain->nnalls] = -1;
            }
         }
      }
   } else {
      for (k = in[i3][0]; k < in[i3][1]; k++) {
         for (j = in[i2][0]; j < in[i2][1]; j++) {
            for (i = in[i1][0]; i < in[i1][1]; i++) {
               ipold = old[i] * inold[i1][2] + j * inold[i2][2] + k * inold[i3][2];
               ipnew = new[i] * in[i1][2] + j * in[i2][2] + k * in[i3][2];
               ireg2[ipnew] = ireg1[ipold];
               if (ireg1[ipold] < 0) {
                  grd_old = -ireg1[ipold]; 
                  for (n = domain->nnalls; n < domain->namix; n++) {
                     if (ireg2[n] == 0) break;
                  }
                  grd_new = n;
                  ireg2[ipnew]                      = -grd_new;
                  grdpnt2[grd_new - domain->nnalls] = ipnew;
                  ireg2[grd_new]                    = ireg1[grd_old];
                  while (grd_old > 0) {
                     grd = grd_new;
                     for (n = domain->nnalls; n < domain->namix; n++) {
                        if (ireg2[n] == 0) break;
                     }
                     grd_new = n;
                     ireg2[grd_new]                    = ireg1[grd_old];
                     lnkmix2[grd - domain->nnalls]     = grd_new;
                     grdpnt2[grd_new - domain->nnalls] = ipnew;
                     grd_old = lnkmix1[grd_old - altdom->nnalls_old];
                  }
                  lnkmix2[grd_new - domain->nnalls] = -1;
               }
            }
         }
      }
   }
}
static void altmesh_interp(double *x, AltMeshDomain_t *altdom, AltMeshInput_t *altm) 
{
   int i,j,k,ip;
   int in[3][3];
   int inold[3][3];
   int ipl, iph;
   int i1 = altdom->i1;
   int i2 = altdom->i2;
   int i3 = altdom->i3;
   int *old  = altdom->old;
   int *new  = altdom->new;
   int *tag  = altdom->tag;
   int *high = altdom->high;
   int *low  = altdom->low;
   double *frac = altdom->frac;
   ALTMESH_CPYIND(in,altdom->in);
   ALTMESH_CPYIND(inold,altdom->inold);
   if (ndims == 2) {
      for (j = in[i2][0]; j <= in[i2][1]; j++) {
         for (i = in[i1][0]; i <= in[i1][1]; i++) {
            ip = new[i] * in[i1][2] + j * in[i2][2];
            if (tag[i] > 0) {
               iph = high[i] * in[i1][2] + j * in[i2][2];
               ipl =  low[i] * in[i1][2] + j * in[i2][2];
               x[ip]    = frac[i] * x[iph] + (1. - frac[i]) * x[ipl];
            }
         }
      }
   } else {
      for (k = in[i3][0]; k <= in[i3][1]; k++) {
         for (j = in[i2][0]; j <= in[i2][1]; j++) {
            for (i = in[i1][0]; i <= in[i1][1]; i++) {
               ip = new[i] * in[i1][2] + j * in[i2][2] + k * in[i3][2];
               if (tag[i] > 0) {
                  iph = high[i] * in[i1][2] + j * in[i2][2] + k * in[i3][2];
                  ipl =  low[i] * in[i1][2] + j * in[i2][2] + k * in[i3][2];
                  x[ip]    = frac[i] * x[iph] + (1. - frac[i]) * x[ipl];
               }
            }
         }  
      }
   }
}
