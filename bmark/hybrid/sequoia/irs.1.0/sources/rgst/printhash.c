#include "irs.h"
#include "irsrgst.h"
#include "irsrgst.h"
#include "irsctl.h"
#include "Hash.h"
#include "Hash.h"
#include "Rgst.h"
int printhash(void) {
  char *me = "printhash";
  char tbl_name[64], str[256], tmpstr[256], msg[512];
  char **ht_names, **htp_names, *token;
  int  i, num_ht, num_htp;
  HashTable_t *ht, **htp;
  memset(str,'\0',256);
  while (ctlflag != iflf) {
    geta(tmpstr);
    if (strlen(str) > 0) {
      strcat(str," ");   	
    }
    strcat(str,tmpstr);			
  }
  token = strtok(str," ");
  if (token == NULL || strcmp(token,"help") == 0) {
    printf("\n\t'printhash' or 'ph' prints registered hash tables\n\t"
           "\n\tUsage:\n\t"
           "\n\tph help        Prints Usage and a list of hash tables"
           "\n\tph xyz         Prints hash table 'xyz' as it is stored in memory"
           "\n\tph xyz type    Prints hash table 'xyz' sorted by type"
           "\n\tph xyz name    Prints hash table 'xyz' sorted by name"
           "\n\tph xyz analyze Prints an analysis of hash table 'xyz'"
           "\n\tph xyz opti    Optimizes hash table 'xyz' -- increasing size if needed\n\t");
    ht_names  = rgst_list_objs_by_type(&num_ht,  "HashTable_t");
    htp_names = rgst_list_objs_by_type(&num_htp, "HashTable_t *");
    if ((num_ht == 0) && (num_htp == 0 )) {
      ctlnotice(me,"\n\tThere are no registered hash tables");
    }
    else {
      printf("\n\tRegistered hash tables:\n\t");
      for (i=0; i<num_ht;  i++) { 
	printf("\n\t%s",ht_names[i]); 
	FREEMEM(ht_names[i]);
      }
      for (i=0; i<num_htp; i++) { 
        printf("\n\t%s",htp_names[i]); 
        FREEMEM(htp_names[i]);
      }
      printf("\n");
    }
    FREEMEM(ht_names);
    FREEMEM(htp_names);
    return(0);
  }
  htp = NULL;
  ht  = (HashTable_t *)rgst_get_t(token,"HashTable_t");
  if (ht == NULL) {
    htp = (HashTable_t **)rgst_get_t(token,"HashTable_t *");
    if ((htp == NULL) || (*htp == NULL)) {
      sprintf(msg,"\n\t'%s' is not a registered hash table",token);
      ctlnotice(me,msg);
      return(-1);
    }
    ht = *htp;
  }
  strncpy(tbl_name,token,63);
  token = strtok(NULL," ");
  if             (token == NULL)         { hash_print(ht); }
  else if (strcmp(token,"name")    == 0) { hash_print_by_name(ht); }
  else if (strcmp(token,"type")    == 0) { hash_print_by_type(ht); }
  else if (strcmp(token,"analyze") == 0) { hash_analyze(ht,TRUE,NULL,NULL,NULL); }
  else if (strcmp(token,"opti")    == 0) { 
    if (htp == NULL) {	
      sprintf(msg,"\n\tCan't optimize table '%s' because it wasn't"
                  "\n\tadded to the registry as type 'HashTable_t *'",
		  tbl_name);
      ctlnotice(me,msg);
      return(-1);
    }    
    else {
      hash_optimize(htp); 
    }
  }
  else {
    sprintf(msg,"\n\t'%s' is an unknown option to the printhash (ph) command\n",
                 token);
    strcat (msg,"\n\tEnter 'ph help' for the usage of this command");
    ctlnotice(me,msg);
    return(-1);
  }
  return(0);
}
