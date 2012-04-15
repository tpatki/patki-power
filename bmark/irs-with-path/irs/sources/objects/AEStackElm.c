#include <stdarg.h>
#include "irs.h"
#include "irsctl.h"
#include "irsrgst.h"
#include "AEStackElm.hh"
#include "Rgst.h"
int AEStackElm_init(AEStackElm_t *ptr)
{
  ptr->routine  = NULL;
  ptr->type 	= NUM_RGST_Datatype_t;
  ptr->nval     = -1;
  ptr->i_value 	= 0;
  ptr->d_value 	= 0.0;
  ptr->len      = 0;
  ptr->i_array  = NULL;
  ptr->d_array  = NULL;
  ptr->label 	= NULL;
  ptr->next     = NULL;
  ptr->prev     = NULL;
  return(0);
}
AEStackElm_t *AEStackElm_construct(int num)
{
  char *me = "AEStackElm_construct";
  int i;
  AEStackElm_t *ptr;
  if (num < 1) ctlerror(me,logic_err);
  ptr = ALLOT(AEStackElm_t, num);
  if (ptr == NULL) ctlerror(me,gv_errmsg_memory);
  for (i=0; i<num; i++) {
    AEStackElm_init(&(ptr[i]));
  }
  return(ptr);
}
AEStackElm_t *AEStackElm_destruct(AEStackElm_t *ptr)
{
  char *me = "AEStackElm_destruct";
  if (ptr == NULL) {
    ctlnotice(me,"Attempt to destroy null pointer");
  }
  else {
    FREEMEM(ptr->routine);
    FREEMEM(ptr->label);
    FREEMEM(ptr->i_array);
    FREEMEM(ptr->d_array);
    FREEMEM(ptr);
  }
  return (AEStackElm_t *)(NULL);
}
int AEStack_push (AEStackElm_t *ptr)
{
  char *me = "AEStack_push";
  ptr->next = NULL;
  ptr->prev = gv_ae_stack_top;
  if (ptr->prev == NULL) {
    ptr->nval = 1;
  }
  else {
    if (strcmp(ptr->routine,ptr->prev->routine) == 0) {
      ptr->nval = ptr->prev->nval + 1;
    }
    else {
      ptr->nval = 1;
    }
  }
  if (gv_ae_stack_bottom == NULL) {
    if (gv_ae_stack_top != NULL) ctlerror(me,logic_err);
    gv_ae_stack_bottom = ptr;
  }
  else {
    gv_ae_stack_top->next = ptr;
  }
  gv_ae_stack_top = ptr;
  return(0);
}
AEStackElm_t *AEStack_pop (void)
{
  char *me = "AEStack_pop";
  AEStackElm_t *ptr;
  if (gv_ae_stack_top == NULL) {
    return(NULL);
  }
  ptr = gv_ae_stack_top;
  gv_ae_stack_top = gv_ae_stack_top->prev;
  if (gv_ae_stack_top == NULL) {
    gv_ae_stack_bottom = NULL;
  }
  else {
    gv_ae_stack_top->next = NULL;
  }
  ptr->next = NULL;
  ptr->prev = NULL;
  return(ptr);
}
int ae_stack_num_vals (
   char *routine)  
{
  char *me = "ae_stack_num_vals";
  if (gv_ae_stack_top == NULL) {
    return(0);
  }
  if (routine != NULL) {
    strcpy(routine,gv_ae_stack_top->routine);
  }
  return(gv_ae_stack_top->nval);
}
void ae_stack_empty_check (void)
{
  char *me = "ae_stack_empty_check";
  if (gv_ae_stack_bottom != NULL) {
    ctlerror(me,"Programmer Error - Stack should be empty!");
  }
}
int ae_stack_push (
  char *          routine, 
  char *          label,   
  RGST_Datatype_t type,    
   ...)
{
  char *me = "ae_stack_push";
  AEStackElm_t *ptr;
  int *iptr, i;
  double *dptr;
  va_list ap;
  ptr = AEStackElm_construct(1);
  if (routine != NULL) ptr->routine = strsave(routine);
  if (label   != NULL) ptr->label   = strsave(label);
  ptr->type = type;
  va_start(ap, type);
  switch (type) {
    case R_INT:
      ptr->i_value = va_arg(ap, int);
      break;
    case R_DOUBLE:
      ptr->d_value = va_arg(ap, double);
      break;
    case R_INT_ARRAY:
      iptr = va_arg(ap, int *);
      ptr->len  = va_arg(ap, int);
      if (ptr->len > 0) {
        ptr->i_array = MALLOT(int, ptr->len);
        for (i=0; i<ptr->len; i++) {
          ptr->i_array[i] = iptr[i];
        }
      }
      break;
    case R_DOUBLE_ARRAY:
      dptr = va_arg(ap, double *);
      ptr->len  = va_arg(ap, int);
      if (ptr->len > 0) {
        ptr->d_array = MALLOT(double,ptr->len);
        for (i=0; i<ptr->len; i++) {
          ptr->d_array[i] = dptr[i];
        }
      }
      break;
    default:
      ctlerror(me,"type must be R_INT, R_DOUBLE, R_INT_ARRAY, or R_DOUBLE_ARRAY");
  }
  va_end(ap);
  AEStack_push(ptr);
  return(0);
}
AEStackElm_t *ae_stack_pop(void)
{
  char *me = "ae_stack_pop";
  AEStackElm_t *ptr = NULL;
  ptr = AEStack_pop();
  if (ptr == NULL) {
    ctlnotice(me,"Attempted to pop element off of empty stack");
    return(NULL);
  }
  return(ptr);
}
int ae_stack_pop_int(void)
{
  char *me = "ae_stack_pop_int";
  AEStackElm_t *ptr;
  int ival;
  ptr = ae_stack_pop();
  if ( (ptr == NULL) || (ptr->type != R_INT) ) {
    ctlnotice(me,"next stack item was not an int");
    ival = 0;
  }
  else {
    ival = ptr->i_value;
  }
  ptr = AEStackElm_destruct(ptr);
  return(ival);
}
double ae_stack_pop_dbl(void)
{
  char *me = "ae_stack_pop_dbl";
  AEStackElm_t *ptr;
  double dval;
  ptr = ae_stack_pop();
  if ( (ptr == NULL) || (ptr->type != R_DOUBLE) ) {
    ctlnotice(me,"next stack item was not a double");
    dval = 0.0;
  }
  else {
    dval = ptr->d_value;
  }
  ptr = AEStackElm_destruct(ptr);
  return(dval);
}
double * ae_stack_pop_dbl_array(void)
{
  char *me = "ae_stack_pop_dbl_array";
  AEStackElm_t *ptr;
  double *darray;
  ptr = ae_stack_pop();
  if ( (ptr == NULL) || (ptr->type != R_DOUBLE_ARRAY) ) {
    ctlnotice(me,"next stack item was not an array of doubles");
    darray = NULL;
  }
  else {
    darray = ptr->d_array;
    ptr->d_array = NULL;       
  }
  ptr = AEStackElm_destruct(ptr);
  return(darray);
}
int * ae_stack_pop_int_array(void)
{
  char *me = "ae_stack_pop_int_array";
  AEStackElm_t *ptr;
  int *iarray;
  ptr = ae_stack_pop();
  if ( (ptr == NULL) || (ptr->type != R_INT_ARRAY) ) {
    ctlnotice(me,"next stack item was not an array of ints");
    iarray = NULL;
  }
  else {
    iarray = ptr->i_array;
    ptr->i_array = NULL;       
  }
  ptr = AEStackElm_destruct(ptr);
  return(iarray);
}
