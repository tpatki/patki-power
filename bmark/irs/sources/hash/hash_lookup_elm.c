#include <stdio.h>                      
#include <stdlib.h>                     
#include <string.h>                     
#include "irsdefs.h"
#include "Hash.h"
#include "irsdefs.h"
 #include "Hash.h"
HashElm_t *hash_lookup_elm (
  char *name,		
  HashTable_t *ht)	
{
  char *me = "hash_lookup_elm";
  HashElm_t *ptr;
  register int hashval, hashval2;
  register char *str;
  if ((ht == NULL) || (ht->tbl == NULL))  {
    fprintf(stderr,"%s: hash table pointer is null\n",me);
    exit(EXIT_FAILURE);
  }
  HASH(hashval2,ht,name); 
  ptr = ht->tbl[hashval2];
  while (ptr != NULL) {
    if (strcmp(ptr->name,name) == 0) return(ptr);
    else                             ptr  = ptr->next;
  }
  return(NULL);
}
