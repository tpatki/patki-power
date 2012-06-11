#include <stdio.h>             
#include <stdlib.h>            
#include <string.h>            
#include "irs.h"
#include "irsdefs.h"
 #include "Hash.h"
#include "Hash.h"
void hash_analyze(
  HashTable_t *ht,	    
  int         print_flag,   
  FILE        *ifp,         
  double      *o_avg_chain, 
  int         *o_max_chain) 
{
  char *me = "hash_analyze";
  HashElm_t *elm;
  int i,j,elm_count, chain_length_size;
  int *chain_length;
  double avg_chain_used_slots  = 0.0;
  double avg_chain_total_slots = 0.0;
  int max_chain = 0;
  int min_chain = 99999;
  int total_elm = 0;
  int max_chain_ndx = -1;
  FILE *ofp = NULL;
  if (ifp == NULL) { ofp = stdout; }
  else             { ofp = ifp;    }
  if (ht == NULL) {
    fprintf(stderr,"%s: hash table ptr is null\n",me);
    exit(EXIT_FAILURE);
  }
  min_chain = ht->size;
  chain_length_size = 4095;
  if (ht->size > chain_length_size) { chain_length_size = ht->size; }
  chain_length = ALLOT(int, chain_length_size);
  for (i=0; i<chain_length_size; i++) chain_length[i] = 0;
  for (i=0; i<ht->size; i++) {
    elm = ht->tbl[i];
    elm_count = 0;
    while (elm != NULL) {
      elm_count++;
      elm = elm->next;
    }    
    if (elm_count > chain_length_size)  {
      fprintf(stderr,"%s: tell programmer to increase allocation of chain_length array in hash library\n",me);
      exit(EXIT_FAILURE);
    }
    chain_length[elm_count]++;
    total_elm += elm_count;
    if (elm_count > max_chain) { max_chain = elm_count; 
                                 max_chain_ndx = i; }
    if (elm_count < min_chain) { min_chain = elm_count; }
  }
  avg_chain_total_slots = (float)total_elm / (float)ht->size;
  if (ht->size != chain_length[0]) {
    avg_chain_used_slots  = (float)total_elm / ((float)ht->size - (float)chain_length[0]);
  }
  if (print_flag == TRUE) {
    fprintf(ofp,"\n+ + + + + + + ANALYSIS OF HASH TABLE %s + + + + + + + +\n\n",ht->name);
    fprintf(ofp,"  total slots in table           : %d\n",ht->size);
    fprintf(ofp,"  used slots in table            : %d\n",ht->size - chain_length[0]);
    fprintf(ofp,"  unused slots in table          : %d\n",chain_length[0]);
    fprintf(ofp,"  total entries  in table        : %d\n",total_elm);
    fprintf(ofp,"  largest chain  (within a slot) : %d\n",max_chain);
    fprintf(ofp,"  shortest chain (within a slot) : %d\n",min_chain);
    if (total_elm != 0) {
      fprintf(ofp,"  average chain (total slots)    : %.2f\n",avg_chain_total_slots);
      fprintf(ofp,"  average chain (used  slots)    : %.2f\n",avg_chain_used_slots);
    }
    fprintf(ofp,"\n  --- Summary of chain lengths ---\n");
    fprintf(ofp,"  %12s %12s\n","chain length","num of slots");
    fprintf(ofp,"  %12s %12s\n","------------","------------");
    for (i=0; i<=max_chain; i++) {
      fprintf(ofp,"  %12d %12d\n",i,chain_length[i]);
    }
    if (max_chain_ndx > -1) {
      fprintf(ofp,"  Here are the %d keys in the largest chain\n",max_chain);
      elm = ht->tbl[max_chain_ndx];
      while (elm != NULL) {
        fprintf(ofp,"\t%s\n",elm->name);
        elm = elm->next;
      }
      fprintf(ofp,"\n");
    }
    fprintf(ofp,"\n+ + + + + + + +  END OF ANALYSIS OF HASH TABLE %s + + + + + + + +\n\n",ht->name);
  }
  FREEMEM(chain_length);
  if (o_avg_chain != NULL) { *o_avg_chain = avg_chain_used_slots; }
  if (o_max_chain != NULL) { *o_max_chain = max_chain; }
}
