#include <stdlib.h>                     
#include "irs.h"
#include "irsctl.h"
#include "Hash.h"
#include "irsrgst.h"
#include "Rgst.h"
int hash_tbl_create_n_rgst(
  HashTable_t **htp,             
  int size,                      
  char *name)                    
{
  char *me = "hash_tbl_create_n_rgst";
  HashTable_t *ht;
  if (name == NULL) {
    ctlerror(me,"name must be specified to register hash table");
  } 
  ht = hash_tbl_create(size,name);
  if (ht == NULL) { 
    *htp = NULL;
    return(-1); 
  }
  rgst_add(name, "HashTable_t *", htp, NULL);
  *htp = ht;
  return(0);
}
