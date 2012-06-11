#include <stdlib.h>                     
#include <stdio.h>                     
#include "irsdefs.h"
#include "Hash.h"
#include "irsdefs.h"
 #include "Hash.h"
HashTable_t *hash_tbl_create (
  int size,                             
  char *name)                           
{
  char *me = "hash_tbl_create";
  HashTable_t *ht;
  if (size < 1) size = DEFAULT_HASHSIZE;
  if ((ht      = ALLOT(HashTable_t,1))    == NULL) {
    fprintf(stderr,"%s: out of memory\n",me);
    exit(EXIT_FAILURE);
  }
  if ((ht->tbl = ALLOT(HashElm_t *,size)) == NULL) {
    fprintf(stderr,"%s: out of memory\n",me);
    exit(EXIT_FAILURE);
  }
  ht->size = size;
  if (name != NULL) { ht->name = strsave(name); }
  return(ht); 
}
