#include <stdio.h>                      
#include <stdlib.h>                     
#include <string.h>                     
#include "irsdefs.h"
#include "Hash.h"
#include "irsdefs.h"
 #include "Hash.h"
#define DASH_20         "--------------------"
#define DASH_59         "-----------------------------------------------------------"
void hash_cond_print_by_type(
  HashTable_t *ht,	
  char *name)		
{
  int i,num_objs, chars_printed_on_line;
  HashElm_t *next, *ptr;
  HashElm_t **hash_elm_array;
  char last_type[128];
  if (ht      == NULL) { return; }
  if (ht->tbl == NULL) { return; }
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
  fprintf(stdout,"\n%-20s %-59s\n","TYPE","NAME");
  fprintf(stdout,"%20s %59s",DASH_20,DASH_59);
  strcpy(last_type,"");
  for (i=0; i<num_objs; i++) {
    if (strcmp(last_type,hash_elm_array[i]->type) != 0) {
      fprintf(stdout,"\n\n%-20s %s",
              hash_elm_array[i]->type,hash_elm_array[i]->name);
      chars_printed_on_line = 21 + strlen(hash_elm_array[i]->name);
      strcpy(last_type,hash_elm_array[i]->type);
    }
    else {
      if (chars_printed_on_line + strlen(hash_elm_array[i]->name) >= 80) {
        fprintf(stdout,"\n%-20s %s","",hash_elm_array[i]->name);
	chars_printed_on_line = 21 + strlen(hash_elm_array[i]->name);
      }
      else {
        fprintf(stdout," %s",hash_elm_array[i]->name);
	chars_printed_on_line += 1 + strlen(hash_elm_array[i]->name);
      }
    }
  }
  fprintf(stdout,"\n");
  FREEMEM(hash_elm_array);
}
