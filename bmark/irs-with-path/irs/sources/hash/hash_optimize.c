#include <stdio.h>             	
#include <stdlib.h>            	
#ifdef SILO
#include <silo.h>	
#endif
#include "irs.h"
#include "irsctl.h"	
#include "irsrgst.h"
#include "Hash.h"
#include "FunctionTimer.h"
#define NUM_PRIMES 15
#define AVG_LIMIT  3.0
#define MAX_LIMIT  30
static int primes[NUM_PRIMES] =
  {  13,   31,   61,  127,  251, 509, 1021, 2039, 3067, 4093,
   5119, 6143, 7159, 8191, 9209};
int hash_optimize_all(void)
{
  char *me = "hash_optimize_all";
  char **ht_names;
  int  num_ht, i;
  HashTable_t **htp = NULL;
  ht_names = rgst_list_objs_by_type(&num_ht, "HashTable_t *");
  for (i=0; i<num_ht; i++) {
    htp = (HashTable_t **)rgst_get_t(ht_names[i],"HashTable_t *");
    if (htp == NULL) { ctlerror(me,logic_err); }
    hash_optimize(htp);  
    FREEMEM(ht_names[i]);
  }
  FREEMEM(ht_names);
  return(0);
}
int hash_optimize(
  HashTable_t **htp)  
{
  char *me = "hash_optimize";
  char msg[256];
  int  max_chain, i;
  double avg_chain;
  HashTable_t *old_ht, *new_ht;
  HashElm_t   *hash_elm;
  if ((htp == NULL) || (*htp == NULL)) return(-1); 
  old_ht = *htp;
  hash_analyze(old_ht,FALSE,NULL,&avg_chain,&max_chain);
  if ((avg_chain <= AVG_LIMIT) && (max_chain <= MAX_LIMIT)) { 
    return(0);
  }
  if (debugflag == TRUE) {
    sprintf(msg,"Table '%s' before : "
                "%4d slots  : "
		"%.2f avg chain length : "
                "%4d max chain length",
		old_ht->name,old_ht->size,avg_chain,max_chain);
    ctlnotice(me,msg);
  }
  while ((avg_chain > AVG_LIMIT) || (max_chain > MAX_LIMIT)) {
    for (i=0; i<NUM_PRIMES; i++) {
      if (primes[i] > old_ht->size) break;
    }
    if (i >= NUM_PRIMES) {
      sprintf(msg,"\n\tCould not increase size of hash table '%s'.  It already"
                  "\n\thas %d slots.  Current largest prime number is %d.  Have"
                  "\n\tprogrammer add more primes to prime array",
                  old_ht->name,old_ht->size,primes[NUM_PRIMES - 1]);
      ctlwarning(me,msg);
      return(-1);
    }
    new_ht = hash_tbl_create(primes[i],NULL);
    if (old_ht->name != NULL) { new_ht->name = strsave(old_ht->name); }
    for (i=0; i<old_ht->size; i++)   {
      hash_elm = old_ht->tbl[i];
      while (hash_elm != NULL) {
        hash_add(hash_elm->name,hash_elm->type,hash_elm->obj,new_ht);
        hash_elm = hash_elm->next;
      }
    }
    FunctionTimer_ht_update(old_ht, new_ht);
    hash_tbl_free(old_ht,FALSE);
    *htp   = new_ht;
    old_ht = new_ht;
    hash_analyze(new_ht,FALSE,NULL,&avg_chain,&max_chain);
  }
  if (debugflag == TRUE) {
    sprintf(msg,"Table '%s' after  : "
                "%4d slots : "
		"%.2f avg chain length : "
                "%4d max chain length",
		old_ht->name,old_ht->size,avg_chain,max_chain);
    ctlnotice(me,msg);
  }
  return(0);
}
