#include <stdio.h>
#include <stdlib.h>
#include "Hash.h"
#include "FunctionTimer.h"
void FunctionTimer_free(HashTable_t *ht)
{
   int i, numelm ;
   HashElm_t **hashelm ;
   FunctionTimer_t *ft = NULL;
   hashelm = hash_get_elm_list(&numelm, "FunctionTimer_t", ht) ;
   for (i = 0 ; i < numelm ; i++) {
     ft = (FunctionTimer_t *) hashelm[i]->obj ;
     hash_del2(ft->name, "FunctionTimer_t", ht) ;
     FREEMEM(ft->agg_thr_flops_start);
     FREEMEM(ft) ;
   }
   FREEMEM(hashelm) ;
}
