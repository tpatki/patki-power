#include <stdio.h>                      
#include <stdlib.h>                     
#include <string.h>                     
#include "irsdefs.h"
#include "Hash.h"
#include "irsdefs.h"
 #include "Hash.h"
void hash_sort_array(
  HashElm_t *hash_elm_array[],       
  int           num_objs)            
{
  register int i, j, l=1;
  register HashElm_t *temp_ptr;
  for (i=l; i<num_objs; i++) {
    temp_ptr = hash_elm_array[i];
    for ( j=i-l; 
          ((j>=0) && (strcmp(hash_elm_array[j]->name,temp_ptr->name) > 0)); 
          j--) {
      hash_elm_array[j+l] = hash_elm_array[j];
    }   
    hash_elm_array[j+l] = temp_ptr;
  }
}
