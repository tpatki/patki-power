#include <stdio.h>                      
#include <stdlib.h>                     
#include <string.h>                     
#include "irsdefs.h"
#include "Hash.h"
#include "irsdefs.h"
 #include "Hash.h"
void hash_del (
  char *name,		
  HashTable_t *ht)	
{
  int            hashval;
  HashElm_t *prev_ptr = NULL;
  HashElm_t *curr_ptr;
  if ((ht == NULL) || (ht->tbl == NULL)) { return; }
  HASH(hashval,ht,name); 
  curr_ptr = ht->tbl[hashval];
  while (curr_ptr != NULL) {
    if (strcmp(name, curr_ptr->name) == 0) {
      if (prev_ptr == NULL) { ht->tbl[hashval] = curr_ptr->next; }
      else                  { prev_ptr->next   = curr_ptr->next; }
      FREEMEM(curr_ptr->name);
      FREEMEM(curr_ptr->type);
      FREEMEM(curr_ptr);
      break;
    }
    else {
      prev_ptr = curr_ptr;
      curr_ptr = curr_ptr->next;     
    }
  }
}
