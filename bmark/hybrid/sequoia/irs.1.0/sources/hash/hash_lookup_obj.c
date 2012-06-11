#include <stdio.h>                      
#include <stdlib.h>                     
#include <string.h>                     
#include "irsdefs.h"
#include "Hash.h"
#include "irsdefs.h"
 #include "Hash.h"
void *hash_lookup_obj (
  char *name,		
  HashTable_t *ht)	
{
  char *me = "hash_lookup_obj";
  HashElm_t *ptr;
  ptr = hash_lookup_elm(name,ht);
  if (ptr == NULL) { return(NULL); }
  else             { return(ptr->obj); }
}
