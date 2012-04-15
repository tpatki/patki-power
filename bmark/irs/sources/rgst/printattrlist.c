#include "irs.h"
#include "irsctl.h"
#include "irsdefs.h"
#include "Hash.h"
#include "irsrgst.h"
#include "Rgst.h"
#define MAX_TOKENS 20
int printattrlist(void) {
  char *me = "printattrlist";
  char str[STRLEN],  msg[512];
  int  i, num_tokens;
  char *tokens[MAX_TOKENS], *token;
  RGST_Attribute_t     *attr       = NULL;
  RGST_AttributeElem_t *elm        = NULL,
                     *elm_objs   = NULL,
                     *elm_types  = NULL,
                     *elm_fields = NULL;
  get_words_at_prompt(str, STRLEN);
  tokens[0] = strtok(str," ");
  if (strcmp(tokens[0],"help") == 0) {
    sprintf(msg,"\n\t'%s' prints the list of items with a specific attribute\n\t"
                "\n\tExample:\n\t"
                "\n\tpal global_scalar        Prints all items that are global scalars"
                "\n\tpal advect               Prints all items that are to be advected"
                "\n\tpal advect global_scalar Prints all items taht are both"
                "\n\t                         global scalars and advected",
                me);
    ctlnotice(me,msg);
    return(0);
  }
  num_tokens = 1;
  while ((tokens[num_tokens] = strtok(NULL," ")) != NULL) num_tokens++;
  switch(num_tokens) {
    case 1: elm_objs   = rgst_list_attr_and(A_OBJECT,tokens[0], NULL);
            elm_types  = rgst_list_attr_and(A_TYPE,  tokens[0], NULL);
            elm_fields = rgst_list_attr_and(A_FIELD, tokens[0], NULL);
            break;
    case 2: elm_objs   = rgst_list_attr_and(A_OBJECT,tokens[0],tokens[1], NULL);
            elm_types  = rgst_list_attr_and(A_TYPE,  tokens[0],tokens[1], NULL);
            elm_fields = rgst_list_attr_and(A_FIELD, tokens[0],tokens[1], NULL);
            break;
    case 3: elm_objs   = rgst_list_attr_and(A_OBJECT,tokens[0],tokens[1],tokens[2], NULL);
            elm_types  = rgst_list_attr_and(A_TYPE,  tokens[0],tokens[1],tokens[2], NULL);
            elm_fields = rgst_list_attr_and(A_FIELD, tokens[0],tokens[1],tokens[2], NULL);
            break;
    case 4: elm_objs   = rgst_list_attr_and(A_OBJECT,tokens[0],tokens[1],tokens[2],tokens[3], NULL);
            elm_types  = rgst_list_attr_and(A_TYPE,  tokens[0],tokens[1],tokens[2],tokens[3], NULL);
            elm_fields = rgst_list_attr_and(A_FIELD, tokens[0],tokens[1],tokens[2],tokens[3], NULL);
            break;
    case 5: elm_objs   = rgst_list_attr_and(A_OBJECT,tokens[0],tokens[1],tokens[2],tokens[3],tokens[4], NULL);
            elm_types  = rgst_list_attr_and(A_TYPE,  tokens[0],tokens[1],tokens[2],tokens[3],tokens[4], NULL);
            elm_fields = rgst_list_attr_and(A_FIELD, tokens[0],tokens[1],tokens[2],tokens[3],tokens[4], NULL);
            break;
    default:sprintf(msg,"'%s' currently works with only 1 - 5 attributes",me);
            ctlnotice(me,msg);
            return(0);
  }
  if (elm_objs != NULL) {
    elm = elm_objs;
    printf("\nThe following objects have the attributes requested\n");
    while (elm != NULL) {
      printf("\n\t%s of type '%s'",elm->name,elm->rgst_obj->usertype);
      elm = elm->next;
    }
    printf("\n");
    elm_objs = rgst_free_attr_elm_list(elm_objs);
  }
  if (elm_types != NULL) {
    elm = elm_types;
    printf("\nThe following type definitions have the attributes requested\n");
    while (elm != NULL) {
      printf("\n\t%s",elm->name);
      elm = elm->next;
    }
    printf("\n");
    elm_types = rgst_free_attr_elm_list(elm_types);
  }
  if (elm_fields != NULL) {
    elm = elm_fields;
    printf("\nThe following fields have the attributes requested\n");
    while (elm != NULL) {
      printf("\n\t%s",elm->name);
      elm = elm->next;
    }
    printf("\n");
    elm_fields = rgst_free_attr_elm_list(elm_fields);
  }
  return(0);
}
