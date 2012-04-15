#include "irs.h"
#include "irsrgst.h"
#include "ProblemArray.h"
#include "Rgst.h"
void ProblemArray_add(char *name, void *ptr, int len, RGST_Datatype_t type, 
                      HashTable_t *hash) {
   char *me = "ProblemArray_add";
   char msg[MAXLINE];
   int exists;
   ProblemArray_t *prb = NULL;
   exists = 0;
   if (hash == NULL) {
      if (rgst_check_for_obj(name)) {
         exists = 1;
         prb = (ProblemArray_t *) rgst_get_t(name,"ProblemArray_t");
#ifdef DEBUG
         sprintf(msg,"Attempting to over write problem array %s",name);
         ctlwarning(me,msg);
#endif
      } else {
         prb = MALLOT(ProblemArray_t,1);
      } 
   } else {
      prb = (ProblemArray_t *) hash_lookup_obj(name, hash);
      if (prb != NULL) {
         exists = 1;
#ifdef DEBUG
         sprintf(msg,"Attempting to over write problem array %s",name);
         ctlwarning(me,msg);
#endif
      } else {
         prb = MALLOT(ProblemArray_t,1);
      } 
   }
   if (exists) {
      if (ptr != NULL)  {
         prb->ptr  = ptr;
	 prb->len  = len;
      }
      if (prb->type != type) {
         sprintf(msg,"Attempting to change type of problem array %s.",name);
         ctlerror(me,msg);
      }
   } else {
      prb->ptr  = ptr;
      prb->len  = len;
      prb->type = type;
      prb->hash = NULL;
      strcpy(prb->name, name);
   } 
   if (hash == NULL) {
      if (!exists) rgst_add(name,"ProblemArray_t", prb, NULL);
   } else {
      if (!exists) hash_add(name, "ProblemArray", prb, hash);
   } 
}
void ProblemArray_del(char *name, HashTable_t *hash) {
   ProblemArray_t *prb;
   if (hash == NULL) {
      if (!rgst_check_for_obj(name)) return;
      prb = (ProblemArray_t *) rgst_get_t(name,"ProblemArray_t");
      FREEMEM(prb);
      rgst_del(name);
   } else {
      prb = (ProblemArray_t *) hash_lookup_obj(name, hash);
      if (prb != NULL) {
         hash_del2(name,"ProblemArray",hash);
         FREEMEM(prb);
      }
   }
}
void *ProblemArray_ptr(char *name, HashTable_t *hash) {
   ProblemArray_t *prb;
   if (hash == NULL) {
      if (rgst_check_for_obj(name)) {
         prb = (ProblemArray_t *) rgst_get_t(name,"ProblemArray_t");
         if (prb != NULL) return(prb->ptr);
      }
   } else {
      prb = (ProblemArray_t *) hash_lookup_obj(name, hash);
      if (prb != NULL) return(prb->ptr);
   }
   return(NULL);
}
ProblemArray_t  *ProblemArray_find(char *name, HashTable_t *hash) {
   ProblemArray_t *prb;
   if (hash == NULL) {
      if (rgst_check_for_obj(name)) {
         prb = (ProblemArray_t *) rgst_get_t(name,"ProblemArray_t");
         if (prb != NULL) return(prb);
      }
   } else {
      prb = (ProblemArray_t *) hash_lookup_obj(name, hash);
      if (prb != NULL) return(prb);
   }
   return(NULL);
}
void ProblemArray_del_all(HashTable_t* hash) {
   int i,numelm;
   HashElm_t **hashelm;
   char **varlist;
   if (hash == NULL) {
      varlist = rgst_list_objs_by_type( &numelm, "ProblemArray_t");
      if (varlist == NULL) return;
      for (i = 0; i < numelm; i++) {
         ProblemArray_t *prb = ProblemArray_find(varlist[i],NULL);
         if (prb->ptr != NULL) FREEMEM(prb->ptr);
         ProblemArray_del(varlist[i],NULL);
	 FREEMEM(varlist[i]);
      }
      FREEMEM(varlist);
   } else {
      hashelm = hash_get_elm_list(&numelm, "ProblemArray", hash);
      for (i = 0; i < numelm; i++) {
         ProblemArray_t *prb = (ProblemArray_t *) hashelm[i]->obj;
         hash_del2(prb->name,"ProblemArray",hash);
         FREEMEM(prb);
      }
      FREEMEM(hashelm);
   }
}
ProblemArray_t *ProblemArray_setblk(char *name) { 
    char *me = "ProblemArray_setblk";
    int iblk;
    ProblemArray_t *prb;
    ProblemArray_t *parray;
    parray = MALLOT(ProblemArray_t, nblk);
    if (parray == NULL) ctlerror(me,gv_errmsg_memory);
    for (iblk = 0; iblk < nblk; iblk++) {
       prb = ProblemArray_find(name,domains[iblk].hash);
       if (prb == NULL) {
         FREEMEM(parray);
         break;
       }
       parray[iblk].ptr = prb->ptr;
       parray[iblk].len = prb->len;
       memset (parray[iblk].name,'\0',MAXWORD);
       strncpy(parray[iblk].name,name,MAXWORD-1);
    }
    return(parray);
}
void ProblemArray_free(char *name) {
   void *ptr;
   int iblk;
   ProblemArray_FreeHash(name, NULL);
   for (iblk = 0; iblk < nblk; iblk++) {
      ptr = ProblemArray_ptr(name,domains[iblk].hash);
      if (ptr != NULL) FREEMEM(ptr);
      ProblemArray_del(name,domains[iblk].hash);
   }
   ptr = ProblemArray_ptr(name,NULL);
   if (ptr != NULL) FREEMEM(ptr);
   ProblemArray_del(name,NULL);
}
void* ProblemArray_allotptr(char *name, HashTable_t *hash) {
   char *me = "ProblemArray_allotptr";
   char msg[MAXLINE];
   int i;
   ProblemArray_t *prb = ProblemArray_find(name, hash);
   if (prb == NULL) {
      sprintf(msg, "Attempt to allocate pointer for %s failed because ProblemArray does not exist for it.",name);
      ctlerror(me,msg);
   }
   if (prb->ptr != NULL) {
      sprintf(msg, "An attempt has been made to allocate pointer a non-null pointer for %s.", name);
      ctlerror(me,msg);
   }
   if (prb->type == R_INT) {
      int *iptr = MALLOT(int, prb->len);
      for (i = 0; i < prb->len; i++) {
         iptr[i] = 0;
      }
      prb->ptr = (void *) iptr;
   } else if (prb->type == R_DOUBLE) {
      double *dptr = MALLOT(double, prb->len);
      for (i = 0; i < prb->len; i++) {
         dptr[i] = 0.;
      }
      prb->ptr = (void *) dptr;
   }
   return(prb->ptr);
}
HashTable_t* ProblemArray_GetHash(char *name, HashTable_t *hash) {
  ProblemArray_t * obj = ProblemArray_find(name, hash);
  return obj->hash;
}
void ProblemArray_CreateHash(char *name, HashTable_t *hash,
				     int size) {
  ProblemArray_t * obj = ProblemArray_find(name, hash);
  obj->hash = hash_tbl_create(size, NULL);
}
void ProblemArray_FreeHash(char *name, HashTable_t *hash)
{
  ProblemArray_t * obj = ProblemArray_find(name, hash);
  if (obj->hash != NULL){
    hash_tbl_free(obj->hash, TRUE);
  }
}
