#include <stdio.h>                      
#include <stdlib.h>                     
#include <string.h>                     
#include "irsdefs.h"
#include "Hash.h"
#include "irsdefs.h"
 #include "Hash.h"
#define DASH_5          "-----"
#define DASH_10         "----------"
#define DASH_20         "--------------------"
#define DASH_25         "-------------------------"
#define DASH_35         "-----------------------------------"
void hash_print_by_type(
  HashTable_t *ht)	
{
  int i,num_objs;
  HashElm_t *next, *ptr;
  HashElm_t **hash_elm_array;
  char name[64];
  if ((ht == NULL) || (ht->tbl == NULL)) { return; }
  if ((num_objs = get_num_elms_in_hashtable(ht)) == 0) { return; }
  hash_elm_array = ALLOT(HashElm_t *, num_objs);
  num_objs = 0;
  for (i=0; i<ht->size; i++) {
    ptr = ht->tbl[i];
    while (ptr != NULL) {
      hash_elm_array[num_objs] = ptr;
      num_objs++;
      ptr = ptr->next;
    }
  }
  hash_sort_array(hash_elm_array,num_objs);
  hash_sort_array_by_type(hash_elm_array,num_objs);
  fprintf(stdout,"\n+ + + + + + + PRINT OF HASH TABLE %s  + + + + + + + +\n\n",ht->name); 
  fprintf(stdout,"%5s %10s %35s %20s %10s %10s\n",
                 "ENTRY","ELM PTR","NAME","TYPE","OBJ PTR","NEXT PTR");
  fprintf(stdout,"%5s %10s %35s %20s %10s %10s\n",
                 DASH_5,DASH_10,DASH_35,DASH_20,DASH_10,DASH_10);
  for (i=0; i<num_objs; i++) {
    name[63] = '\0';
    strncpy(name,hash_elm_array[i]->name,63);
    if (strlen(name) > 35) {
      strcpy(&name[32],">>>");
    }
    fprintf(stdout,"%5d %10p %35s %20s %10p %10p\n", i,
      hash_elm_array[i],
      hash_elm_array[i]->name,
      hash_elm_array[i]->type,
      hash_elm_array[i]->obj,
      hash_elm_array[i]->next);
  }
  fprintf(stdout,"\n\n+ + + + + + + + +  END OF PRINT OF HASH TABLE %s + + + + + + + + +\n",ht->name);
  FREEMEM(hash_elm_array);
}
