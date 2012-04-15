#include <stdio.h>                      
#include <stdlib.h>                     
#include <string.h>                     
#include "irsdefs.h"
#include "Hash.h"
#include "irsdefs.h"
 #include "Hash.h"
void hash_del_objs_of_type(
  HashTable_t *ht,            
  char *type,	              
  void (*fn_ptr) ())          
{
  char *me = "hash_del_objs_of_type";
  int i, num_objs;
  HashElm_t *ptr;
  HashElm_t **hash_elm_array;
  if (ht      == NULL) 
    { fprintf(stderr,"%s: hash table ptr is NULL\n",me); exit(EXIT_FAILURE); }
  if (ht->tbl == NULL) 
    { fprintf(stderr,"%s: hash table is NULL\n",me);     exit(EXIT_FAILURE); }
  if (type    == NULL) 
    { fprintf(stderr,"%s: type string is NULL\n",me);    exit(EXIT_FAILURE); }
  if ((num_objs = get_num_elms_in_hashtable(ht)) == 0) { return; }
  hash_elm_array = ALLOT(HashElm_t *, num_objs);
  num_objs = 0;
  for (i=0; i<ht->size; i++) {
    ptr = ht->tbl[i];
    while (ptr != NULL) {
      if (strcmp(ptr->type,type) == 0) { 
        hash_elm_array[num_objs] = ptr;
        num_objs++;
      }
      ptr = ptr->next;
    }
  }
  for (i=0; i<num_objs; i++) {
    if (fn_ptr != NULL) {
      (*fn_ptr)(hash_elm_array[i]->obj);
    }
    hash_del2(hash_elm_array[i]->name,type,ht);
  }
  FREEMEM(hash_elm_array);
}
