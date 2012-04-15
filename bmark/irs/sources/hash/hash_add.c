#include <stdio.h>                      
#include <stdlib.h>                     
#include <string.h>                     
#include "irsdefs.h"
#include "Hash.hh"
#include "irsdefs.h"
void hash_add (
  char *name,		
  char *type,		
  void *obj,		
  HashTable_t *ht)	
{
  char *me = "hash_add";
  char msg[128];
  HashElm_t *ptr;
  int hashval;
  if ((ht == NULL) || (ht->tbl == NULL)) {
    fprintf(stderr,"%s - hash table is null\n",me);
    exit(EXIT_FAILURE);
  }
  ptr = hash_lookup_elm(name,ht);
  if (ptr == NULL) {
    if ((ptr = (HashElm_t *)calloc(1,sizeof(HashElm_t))) == NULL) {
      fprintf(stderr,"%s - out of memory\n",me);
      exit(EXIT_FAILURE);
    }    
    HASH(hashval,ht,name);  
    ptr->name        = strsave(name);
    ptr->type        = strsave(type);
    ptr->obj         = obj;
    ptr->next        = ht->tbl[hashval];
    ht->tbl[hashval] = ptr;
  }
  else {
    if (ptr->obj != obj) {
      sprintf(msg,"%s: '%s' object is being replaced in hash table '%s'\n",
              me,name,ht->name);
      fprintf(stderr,msg);
      ptr->obj = obj;
    }
    if (strcmp(ptr->type,type) != 0) {
      sprintf(msg,"%s: '%s' type is being changed from '%s' to '%s' in hash table '%s'\n",
              me,name,ptr->type,type,ht->name);
      fprintf(stderr,msg);
      FREEMEM(ptr->type);
      ptr->type = strsave(type);
    }
  }
}
