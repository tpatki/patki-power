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
void hash_print(
  HashTable_t *ht)	
{
  int i;
  HashElm_t *next;
  char name[64];
  if ((ht == NULL) || (ht->tbl == NULL)) { return; }
  fprintf(stdout,"\n+ + + + + + + PRINT OF HASH TABLE %s  + + + + + + + +\n\n",ht->name); 
  fprintf(stdout,"%5s %10s %35s %20s %10s %10s\n",
                 "ENTRY","ELM PTR","NAME","TYPE","OBJ PTR","NEXT PTR");
  fprintf(stdout,"%5s %10s %35s %20s %10s %10s\n",
                 DASH_5,DASH_10,DASH_35,DASH_20,DASH_10,DASH_10);
  for (i=0; i<ht->size; i++) {
    if (ht->tbl[i] != NULL) {
      name[63] = '\0';
      strncpy(name,ht->tbl[i]->name,63);
      if (strlen(name) > 35) {
        strcpy(&name[32],">>>");
      }
      fprintf(stdout,"%5d %10p %35s %20s %10p %10p\n",
        i,ht->tbl[i],name,ht->tbl[i]->type,ht->tbl[i]->obj,ht->tbl[i]->next);
      next = ht->tbl[i]->next;
      while (next != NULL) {
        name[63] = '\0';
        strncpy(name,next->name,63);
        if (strlen(name) > 35) {
          strcpy(&name[32],">>>");
        }
        fprintf(stdout,"%5s %10p %35s %20s %10p %10p\n",
          "-",next,name,next->type,next->obj,next->next);
        next = next->next;
      }
    }
  }
  fprintf(stdout,"\n\n+ + + + + + + + +  END OF PRINT OF HASH TABLE %s + + + + + + + + +\n",ht->name);
}
