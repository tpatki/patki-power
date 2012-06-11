#include "irs.h"
#include "irsctl.h"
#include "irsrgst.h"
#include "BlockMapping.h"
#include "Command.h"
#include "Extents.h"
#include "NodeList.h"
#include "Hash.h"
#include "Source.hh"
int Source_setup_attrs(void)
{
  char *me = "Source_setup_attrs";
  static int first_time_thru = TRUE;
  if (RGST_ADD_ATTR_TO_FIELDS("Source_t","dump") != 0)
    ctlerror(me,gv_errmsg_rgst_add_attrs_to_fields);
  if (first_time_thru == TRUE) {
    inst_c("Source_init",      Source_init,      zargse, 0, symtab);
    inst_c("Source_construct", Source_construct, zargse, 0, symtab);
    first_time_thru = FALSE;
  }
  return(0);
}
int Source_init(Source_t *ptr)
{
  memset(ptr->ndxName,'\0',MAXLINE);
  ptr->imin        = 0;
  ptr->jmin        = 0;
  ptr->kmin        = 0;
  ptr->imax        = 0;
  ptr->jmax        = 0;
  ptr->kmax        = 0;
  ptr->type        = 0;
  ptr->cent        = 0;;
  ptr->nzsrc       = 0;
  ptr->ndxsrc      = NULL;
  ptr->idat1       = NULL;
  ptr->nidat1      = 0;
  ptr->fdat1       = NULL;
  ptr->nfdat1      = 0;
  ptr->dat2        = NULL;
  ptr->ndat2       = 0;
  ptr->dat3        = NULL;
  ptr->ndat3       = 0;
  return(0);
}
Source_t *Source_construct(int num)
{
  char *me = "Source_construct";
  int i;
  Source_t *ptr;
  if (num < 1) ctlerror(me,logic_err);
  ptr = ALLOT(Source_t, num);
  if (ptr == NULL) ctlerror(me,gv_errmsg_memory);
  for (i=0; i<num; i++) {
    Source_init(&(ptr[i]));
  }
  return(ptr);
}
void Source_merge(Domain_t *domain) {
   char *name;
   int isrc;
   int nsrc;
   int numsrc;
   NodeList_t *NodeList = NULL;
   NodeWindow_t *ndxin_ptr = NULL;
   Source_t *src_new;
   Source_t *src_ptr;
   Extents_t ext1;
   Extents_t ext2;
   Extents_t ext3;
   HashElm_t **hashlist;
   src_new = MALLOT(Source_t, nsrcx);
   for (isrc = 0; isrc < nsrcx; isrc++) {
      Source_init(&src_new[isrc]);
   }
   for (isrc = 0; isrc < domain->nsrc; isrc++) {
      name = domain->src[isrc].ndxName;
      src_ptr = (Source_t *) hash_lookup_obj(name, domain->hash);
      if (src_ptr == NULL) {
	 src_ptr = &domain->src[isrc];
         hash_add(name, "Source_t", src_ptr, domain->hash);
      }
   }
   hashlist = hash_get_elm_list(&numsrc, "Source_t", domain->hash);
   nsrc = 0;
   for (isrc = 0; isrc < numsrc; isrc++) {
      src_ptr = (Source_t *) hashlist[isrc]->obj;
      name   = src_ptr->ndxName;
      NodeList = NodeList_find(name);
      ndxin_ptr = NodeList->list;
      while (ndxin_ptr != NULL) {
         int gblk = domain->gblk;
         int len;
	 if (src_ptr->cent == ZONAL_ARRAY) {
	    len = NodeWindow_fastndx(ndxin_ptr,gblk,NDX_GLBL_PHONY, NDX_ZONAL);
	 } else {
	    len = NodeWindow_fastndx(ndxin_ptr,gblk,NDX_GLBL_PHONY, NDX_NODAL);
	 } 
         if (len > 0) {
            int i;
            src_new[nsrc].nzsrc  = len;
            src_new[nsrc].type   = src_ptr->type;
            src_new[nsrc].cent   = src_ptr->cent;
            src_new[nsrc].nidat1 = src_ptr->nidat1;
            src_new[nsrc].nfdat1 = src_ptr->nfdat1;
            src_new[nsrc].ndat2  = src_ptr->ndat2 ;
            strcpy(src_new[nsrc].ndxName, src_ptr->ndxName);
	    CPYEXT(ext1,gmap[gblk]);
	    CPYEXT(ext2,(*ndxin_ptr));
	    if (src_ptr->cent == ZONAL_ARRAY) {
	       ext1.imin--;
	       ext1.jmin--;
	       ext1.imax++;
	       ext1.jmax++;
	       if (ndims == 3) {
	          ext1.kmin--;
	          ext1.kmax++;
	       }
	    } 
	    extents_overlap(&ext1, &ext2, &ext3);
	    TRSEXT(src_new[nsrc], ext3, gmap[gblk]);
	    if (ndims == 2) {
	       src_new[nsrc].kmin = 0;
	       src_new[nsrc].kmax = 0;
	    }
            src_new[nsrc].ndxsrc = MALLOT(int,len);
            for (i = 0; i < len; i++) {
               src_new[nsrc].ndxsrc[i] = ndxin_ptr->ndx[i];
            }
	    if (src_new[nsrc].nidat1 > 0) {
               src_new[nsrc].idat1 = MALLOT(int,src_new[nsrc].nidat1);
               for (i = 0; i < src_new[nsrc].nidat1; i++) {
                  src_new[nsrc].idat1[i] = src_ptr->idat1[i];
               }
	    }
	    if (src_new[nsrc].nfdat1 > 0) {
               src_new[nsrc].fdat1 = MALLOT(double,src_new[nsrc].nfdat1);
               for (i = 0; i < src_new[nsrc].nfdat1; i++) {
                  src_new[nsrc].fdat1[i] = src_ptr->fdat1[i];
               }
	    }
	    if (src_new[nsrc].ndat2 > 0) {
               src_new[nsrc].dat2 = MALLOT(double,src_new[nsrc].ndat2);
               for (i = 0; i < src_new[nsrc].ndat2; i++) {
                  src_new[nsrc].dat2[i] = src_ptr->dat2[i];
               }
	    }
            nsrc++;
         }
         NodeWindow_freendx(ndxin_ptr);
         ndxin_ptr = ndxin_ptr->next;
      }
      hash_del2(name,"Source_t", domain->hash);
   }
   FREEMEM(hashlist);
   for (isrc = 0; isrc < domain->nsrc; isrc++) {
      FREEMEM(domain->src[isrc].ndxsrc);
      if (domain->src[isrc].nidat1 > 0) {
         FREEMEM(domain->src[isrc].idat1);
      }
      if (domain->src[isrc].nfdat1 > 0) {
         FREEMEM(domain->src[isrc].fdat1);
      }
      if (domain->src[isrc].ndat2 > 0) {
         FREEMEM(domain->src[isrc].dat2);
      }
   }
   FREEMEM(domain->src);
   domain->src  = src_new;
   domain->nsrc = nsrc;
}
