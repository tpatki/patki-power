#include <stdio.h>
#include <stdlib.h>
#include "Hash.h"
#include "FunctionTimer.h"
FunctionTimer_t *FunctionTimer_lookup(
  char *name,           
  HashTable_t *ht)      
{
  FunctionTimer_t *ft;
  char namefield[128];
  sprintf(namefield, "FTS_%s", name);
  ft = (FunctionTimer_t *) hash_lookup_obj(namefield, ht);
  return(ft);
}
