#include "irs.h"
#include "irsedits.h"
#include "irsrgst.h"
#include "NodeList.h"
int printnodelist(void) 
{
  int num_lists;
  int i;
  int count;
  char name[MAXLINE];
  char op[MAXLINE];
  char **list;
  NodeList_t *ndxlistptr;
  if ( !lfchk( ) ) {
     peekc(op);
     ndxlistptr = NodeList_find(op);
     if (ndxlistptr != NULL) {
        geta(op);
        NodeList_print(ndxlistptr);
     }
  } else {
     list = rgst_list_objs_by_type(&num_lists,"NodeList_t");
     for (i = 0; i < num_lists; i++) {
        ndxlistptr = (NodeList_t *) rgst_get_t(list[i],"NodeList_t");
        NodeList_print(ndxlistptr);
        FREEMEM(list[i]);
     }
     FREEMEM(list);
  } 
  return(0);
}
