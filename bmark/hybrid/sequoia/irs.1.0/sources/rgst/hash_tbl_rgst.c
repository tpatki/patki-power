#include <stdlib.h>                     
#include "irs.h"
#include "irsctl.h"
#include "Hash.h"
#include "irsrgst.h"
#include "Rgst.h"
int hash_tbl_rgst(
  HashTable_t **htp,             
  char *name)                    
{
  char *me = "hash_tbl_rgst";
  char msg[512], *ps_save, *line_save, sym_save[MAXLINE];
  int error, symflag_save;
  if (name == NULL) {
    ctlerror(me,"name must be specified to register hash table");
  } 
  if ((htp == NULL) || (*htp == NULL)) {
    ctlerror(me,"hash table pointer is NULL");
  }
  if ((*htp)->name != NULL) {
    if (rgst_check_for_obj((*htp)->name) == TRUE) { 
      rgst_del((*htp)->name);
      sprintf(msg,"\nHash table '%s' being re-registered as"
                  "\nHash table '%s'",(*htp)->name,name);
      ctlnotice(me,msg);
    }
    FREEMEM((*htp)->name);
  }
  (*htp)->name = strsave(name);  
  rgst_add(name, "HashTable_t *", htp, NULL);
  return(0);
}
