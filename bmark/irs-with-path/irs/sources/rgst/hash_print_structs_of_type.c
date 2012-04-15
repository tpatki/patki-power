#include <stdio.h>                      
#include <stdlib.h>                     
#include <string.h>                     
#include "irs.h"
#include "Hash.h"
#include "irsrgst.h"
#include "Rgst.h"
void hash_print_structs_of_type(
  HashTable_t *ht,    
  char *type)           
{
  int i, num_objs;
  HashElm_t *ptr;
  HashElm_t **hash_elm_array;
  if ((ht == NULL) || (ht->tbl == NULL)) {
    printf("\n\tHash table is null !\n");
    return;
  }
  if ((num_objs = get_num_elms_in_hashtable(ht)) == 0) {
    printf("\tNo objects exist in the hash table\n");
    return;
  }
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
  if (num_objs == 0) {
    printf("\tNo objects of type '%s' exist in the hash table\n",type);
    return;
  }
  hash_sort_array(hash_elm_array,num_objs);
  for (i=0; i<num_objs; i++) { 
    hash_print_obj(hash_elm_array[i]); 
  }
  FREEMEM(hash_elm_array);
}
