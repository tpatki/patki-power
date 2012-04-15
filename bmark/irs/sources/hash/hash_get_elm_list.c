#include <stdio.h>                      
#include <stdlib.h>                     
#include <string.h>                     
#include "irsdefs.h"
#include "Hash.h"
#include "irsdefs.h"
 #include "Hash.h"
HashElm_t **hash_get_elm_list(
  int           *num_elms, 
  char          *type,     
  HashTable_t *ht)         
{
  int i,num_objs;
  HashElm_t *next, *ptr;
  HashElm_t **hash_elm_list = NULL;
  *num_elms = 0;
  if (ht      == NULL) { return (hash_elm_list); }
  if (ht->tbl == NULL) { return (hash_elm_list); }
  if ((num_objs = get_num_elms_in_hashtable(ht)) == 0) { 
    return (hash_elm_list);
  }
  hash_elm_list = ALLOT(HashElm_t *, num_objs);
  num_objs = 0;
  for (i=0; i<ht->size; i++) {
    ptr = ht->tbl[i];
    while (ptr != NULL) {
      if ((type == NULL) || (strcmp(ptr->type,type) == 0)) {
        hash_elm_list[num_objs] = ptr;
        num_objs++;
      }
      ptr = ptr->next;
    }
  }
  *num_elms = num_objs;
  return (hash_elm_list);
}
