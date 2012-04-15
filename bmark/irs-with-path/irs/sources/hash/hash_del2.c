#include <stdio.h>                      
#include <stdlib.h>                     
#include <string.h>                     
#include "irsdefs.h"
#include "Hash.h"
#include "irsdefs.h"
 #include "Hash.h"
void hash_del2 (
  char *name,		
  char *type,		
  HashTable_t *ht)	
{
  char *me = "hash_del2";
  int  hashval;
  HashElm_t *prev_ptr = NULL;
  HashElm_t *curr_ptr;
  if ((ht == NULL) || (ht->tbl == NULL)) { return; }
  HASH(hashval,ht,name);        
  curr_ptr = ht->tbl[hashval];
  while (curr_ptr != NULL) {
    if (strcmp(name, curr_ptr->name) == 0) {
      if (strcmp(type, curr_ptr->type) != 0)  {
        fprintf(stderr,"%s: hash library PROGRAMMER ERROR - types do not match\n",me);
        exit(EXIT_FAILURE);
      }
      if (prev_ptr == NULL) { ht->tbl[hashval]   = curr_ptr->next; }
      else                  { prev_ptr->next = curr_ptr->next; }
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
