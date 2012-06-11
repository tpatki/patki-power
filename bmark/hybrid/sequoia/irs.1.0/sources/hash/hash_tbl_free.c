#include <stdio.h>                      
#include <stdlib.h>                     
#include <string.h>                     
#include "irsdefs.h"
#include "Hash.h"
#include "irsdefs.h"
 #include "Hash.h"
HashTable_t *hash_tbl_free (
  HashTable_t *ht,	
  int free_obj_flag)    
{
  int i;
  HashElm_t *ptr, *next;
  if (ht != NULL) {
    for (i=0; i<ht->size; i++) {	
      ptr = ht->tbl[i];
      while (ptr != NULL) {		
        next = ptr->next;		
        FREEMEM(ptr->name);
        FREEMEM(ptr->type);
	if (free_obj_flag == TRUE) { 
          FREEMEM(ptr->obj); 
	}
        FREEMEM(ptr); 
        ptr = next;
      } 
    }
    FREEMEM(ht->name);			
    FREEMEM(ht->tbl);
    FREEMEM(ht);			
  }
  return((HashTable_t *)NULL);
}
