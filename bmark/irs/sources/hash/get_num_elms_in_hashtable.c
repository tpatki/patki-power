#include <stdio.h>                      
#include <stdlib.h>                     
#include <string.h>                     
#include "irsdefs.h"
#include "Hash.h"
#include "irsdefs.h"
 #include "Hash.h"
int get_num_elms_in_hashtable(
  HashTable_t *ht)          
{
  HashElm_t *ptr;
  int i, elm_cnt = 0;
  if ((ht == NULL) || (ht->tbl == NULL)) return (0);
  for (i=0; i<ht->size; i++) {
    ptr = ht->tbl[i];
    while (ptr != NULL) {
      elm_cnt++;
      ptr = ptr->next;
    }
  }
  return(elm_cnt);
}
