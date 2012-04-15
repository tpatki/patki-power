#include <stdarg.h>
#include "irs.h"
#include "irsctl.h"
#include "irsrgst.h"
#include "Rgst.h"
int AttrArray_init(AttrArray_t *ptr)
{
  ptr->num_attrs  = 0;
  ptr->size_attrs = 0;
  ptr->attrs      =  NULL;
  return(0);
}
AttrArray_t *AttrArray_construct(int num)
{
  char *me = "AttrArray_construct";
  int i;
  AttrArray_t *ptr;
  if (num < 1) ctlerror(me,logic_err);
  ptr = ALLOT(AttrArray_t, num);
  if (ptr == NULL) ctlerror(me,gv_errmsg_memory);
  for (i=0; i<num; i++) {
    AttrArray_init(&(ptr[i]));
  }
  return(ptr);
}
AttrArray_t *AttrArray_destruct(AttrArray_t *ptr)
{
  char *me = "AttrArray_destruct";
  if (ptr == NULL) {
    ctlnotice(me,"Attempt to destroy null pointer");
  }
  else {
    FREEMEM(ptr->attrs);
    FREEMEM(ptr);
  }
  return (AttrArray_t *)(NULL);
}
void  AttrArray_add(
  RGST_Attribute_t  *new_attr, 
  AttrArray_t *ptr)            
{
  char *me = " AttrArray_add";
  int i;
  if (ptr == NULL) ctlerror(me,logic_err);
  if (ptr->num_attrs >= ptr->size_attrs) {
    ptr->size_attrs += 5;
    if (ptr->attrs == NULL) {
      ptr->attrs = (RGST_Attribute_t **)malloc(ptr->size_attrs * sizeof(void *));
    }
    else {
      ptr->attrs = (RGST_Attribute_t **)realloc(ptr->attrs, ptr->size_attrs * sizeof(void *));
    }
    if (ptr->attrs == NULL) ctlerror(me,gv_errmsg_memory);
    for (i=ptr->size_attrs-5; i<ptr->size_attrs; i++) ptr->attrs[i] = NULL;
  }
  ptr->attrs[ptr->num_attrs] = new_attr;
  ptr->num_attrs++;
}
void  AttrArray_del(
  char *attr_name,   
  AttrArray_t *ptr)  
{
  char *me = " AttrArray_del";
  int i, j;
  if (ptr == NULL) ctlerror(me,logic_err);
  for (i=0; i<ptr->num_attrs; i++) {
    if (strcmp(attr_name,ptr->attrs[i]->attr_name) == 0) {
      for(j=i; j<(ptr->num_attrs-1); j++) {
        ptr->attrs[j] = ptr->attrs[j+1];
      }
      ptr->attrs[ptr->num_attrs-1] = NULL;
      ptr->num_attrs--;
      return;
    }
  }
}
RGST_Attribute_t * AttrArray_search(
  char            *attr_name, 
  AttrArray_t *ptr)       
{
  char *me ="AttrArray_search";
  int i;
  if (ptr == NULL) ctlerror(me,logic_err);
  for (i=0; i<ptr->num_attrs; i++) {
    if (strcmp(attr_name,ptr->attrs[i]->attr_name) == 0) {
      return(ptr->attrs[i]);
    }
  }
  return(NULL);
}
