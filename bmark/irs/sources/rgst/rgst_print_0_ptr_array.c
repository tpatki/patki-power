#include <stdio.h>
#include <string.h>
#include "irs.h"
#include "irs.h"
#include "Hash.h"
#include "Rgst.h"
#include "irsrgst.h"
#ifndef _POSIX_SOURCE
#define _POSIX_SOURCE 1
#endif
static void print_char_array (char *array, long lo_ndx, long hi_ndx)	
{
  long i;
  if (hi_ndx < lo_ndx) printf("\n");
  if (lo_ndx == hi_ndx) {
    if      (array[lo_ndx] == TRUE)  { printf("TRUE\n"); return; }
    else if (array[lo_ndx] == FALSE) { printf("FALSE\n"); return; }
  }
  for (i=lo_ndx; i<=hi_ndx; i++) {
    printf("%c",array[i]);
    if      (i == hi_ndx)   printf("\n");
    else if ((i+1) % 60 == 0) printf("\n%20s","");
  }
}
static void print_unsigned_char_array (unsigned char *array, long lo_ndx, long hi_ndx) 
{
  long i;
  if (hi_ndx < lo_ndx) printf("\n");
  if (lo_ndx == hi_ndx) {
    if      (array[lo_ndx] == TRUE)  { printf("TRUE\n"); return; }
    else if (array[lo_ndx] == FALSE) { printf("TRUE\n"); return; }
  }
  for (i=lo_ndx; i<=hi_ndx; i++) {
    printf("%u ",array[i]);
    if      (i == hi_ndx)   printf("\n");
    else if ((i+1) % 5 == 0) printf("\n%20s","");
  }
}
static void print_short_array (short *array, long lo_ndx, long hi_ndx)	
{
  long i;
  if (hi_ndx < lo_ndx) printf("\n");
  for (i=lo_ndx; i<=hi_ndx; i++) {
    printf("%-7d ",array[i]);
    if      (i == hi_ndx)   printf("\n");
    else if ((i+1) % 5 == 0) printf("\n%20s","");
  }
}
static void print_unsigned_short_array (unsigned short *array, long lo_ndx, long hi_ndx)
{
  long i;
  if (hi_ndx < lo_ndx) printf("\n");
  for (i=lo_ndx; i<=hi_ndx; i++) {
    printf("%7u ",array[i]);
    if      (i == hi_ndx)   printf("\n");
    else if ((i+1) % 5 == 0) printf("\n%20s","");
  }
}
static void print_int_array (int *array, long lo_ndx, long hi_ndx)	
{
  long i;
  if (hi_ndx < lo_ndx) printf("\n");
  for (i=lo_ndx; i<=hi_ndx; i++) {
    printf("%-7d ",array[i]);
    if      (i == hi_ndx)   printf("\n");
    else if ((i+1) % 5 == 0) printf("\n%20s","");
  }
}
static void print_unsigned_int_array (unsigned int *array, long lo_ndx, long hi_ndx)
{
  long i;
  if (hi_ndx < lo_ndx) printf("\n");
  for (i=lo_ndx; i<=hi_ndx; i++) {
    printf("%7u ",array[i]);
    if      (i == hi_ndx)   printf("\n");
    else if ((i+1) % 5 == 0) printf("\n%20s","");
  }
}
static void print_long_array (long *array, long lo_ndx, long hi_ndx)
{
  long i;
  if (hi_ndx < lo_ndx) printf("\n");
  for (i=lo_ndx; i<=hi_ndx; i++) {
    printf("%7ld ",array[i]);
    if      (i == hi_ndx)   printf("\n");
    else if ((i+1) % 5 == 0) printf("\n%20s","");
  }
}
static void print_unsigned_long_array (unsigned long *array, long lo_ndx, long hi_ndx)
{
  long i;
  if (hi_ndx < lo_ndx) printf("\n");
  for (i=lo_ndx; i<=hi_ndx; i++) {
    printf("%7lu ",array[i]);
    if      (i == hi_ndx)   printf("\n");
    else if ((i+1) % 5 == 0) printf("\n%20s","");
  }
}
static void print_long_long_array (long *array, long lo_ndx, long hi_ndx)
{
  printf("Print of long long not done yet\n");
}
static void print_unsigned_long_long_array (long *array, long lo_ndx, long hi_ndx)
{
  printf("Print of unsigned long long not done yet\n");
}
static void print_float_array (float *array, long lo_ndx, long hi_ndx)
{
  long i;
  if (hi_ndx < lo_ndx) printf("\n");
  for (i=lo_ndx; i<=hi_ndx; i++) {
    printf("%10.5f ",array[i]);
    if      (i == hi_ndx)   printf("\n");
    else if ((i+1) % 5 == 0) printf("\n%20s","");
  }
}
static void print_double_array (double *array, long lo_ndx, long hi_ndx)
{
  long i;
  if (hi_ndx < lo_ndx) printf("\n");
  for (i=lo_ndx; i<=hi_ndx; i++) {
    printf("%10.5f ",array[i]);
    if      (i == hi_ndx)   printf("\n");
    else if ((i+1) % 5 == 0) printf("\n%20s","");
  }
}
static void print_ctype_array (
  void *ptr,
  char *dt_name,
  long lo_ndx, long hi_ndx)
{
  char *me = "print_ctype_array";
  char my_type_str[128], msg[128];
  long i;
  long dim_nelms, nelms, my_lo_ndx, my_hi_ndx;
  HashElm_t *hash_elm;
  RGST_CTypeDef_t *td;
  void *myptr;
  if ((hash_elm = hash_lookup_elm(dt_name, rgst_types_hash_tbl)) == NULL) 
    ctlerror(me,"PROGRAMMER ERROR ctype not in registry");
  td = (RGST_CTypeDef_t *)hash_elm->obj;
  if ((td->nptrs > 0) && (td->ndims > 0)) {
    printf("Print of ctype with both ptrs and dimensions not done yet\n");
    return;
  }
  dim_nelms = 1;
  for (i=0; i<td->ndims; i++) dim_nelms = dim_nelms * td->dims[i];
  rgst_create_typedef_name_str(td->type, NULL, td->nptrs, td->ndims, 
                               td->dims, my_type_str);
  nelms = (hi_ndx - lo_ndx) + 1;
  if (nelms < 0) nelms = 0;
  if (td->nptrs == 0) {
    rgst_print_0_ptr_array(td->type, NULL, ptr, nelms, lo_ndx, hi_ndx);
  }
  else if (td->nptrs == 1) {
    printf("%d %s each of length %d\n",(int)nelms,my_type_str,(int)dim_nelms);
    for (i=lo_ndx; i<=hi_ndx; i++) {
      sprintf(msg,"[%d]",(int)i);
      printf("%19s ",msg);
      myptr = (void *)((void **)ptr)[i];
      rgst_print_0_ptr_array(td->type, NULL, myptr, dim_nelms, -1, -1);
    }
  }
  else if (td->nptrs == 2) {
    printf("Print of 2-ptr ctype not done yet\n");
  }
  else {
    ctlerror(me,"Programmer Error - npts > 2");
  }
}
void rgst_print_0_ptr_array (
  RGST_Datatype_t dt,             
  char          *dt_name,       
  void          *ptr,           
  long          nelms,            
  long          lo_ndx,         
  long          hi_ndx)          
{
  char *me = "rgst_print_0_ptr_array";
  long my_lo_ndx, my_hi_ndx;
  if (ptr == NULL) {
    printf("%p\n",ptr);
    return;
  }
  if (rgst_check_ndxs (nelms, lo_ndx, hi_ndx, &my_lo_ndx, &my_hi_ndx) != 0)
    return;
  if      (dt == R_CHAR)                   print_char_array               ((char *)          ptr, my_lo_ndx, my_hi_ndx);
  else if (dt == R_UNSIGNED_CHAR)          print_unsigned_char_array      ((unsigned char *) ptr, my_lo_ndx, my_hi_ndx);
  else if (dt == R_SHORT)                  print_short_array              ((short *)         ptr, my_lo_ndx, my_hi_ndx);
  else if (dt == R_UNSIGNED_SHORT)         print_unsigned_short_array     ((unsigned short *)ptr, my_lo_ndx, my_hi_ndx);  
  else if (dt == R_SHORT_INT)              print_short_array              ((short *)         ptr, my_lo_ndx, my_hi_ndx);
  else if (dt == R_UNSIGNED_SHORT_INT)     print_unsigned_short_array     ((unsigned short *)ptr, my_lo_ndx, my_hi_ndx);    
  else if (dt == R_INT)                    print_int_array                ((int  *)          ptr, my_lo_ndx, my_hi_ndx);
  else if (dt == R_UNSIGNED_INT)           print_unsigned_int_array       ((unsigned int*)   ptr, my_lo_ndx, my_hi_ndx); 
  else if (dt == R_LONG)                   print_long_array               ((long  *)         ptr, my_lo_ndx, my_hi_ndx);
  else if (dt == R_UNSIGNED_LONG)          print_unsigned_long_array      ((unsigned long *) ptr, my_lo_ndx, my_hi_ndx);
  else if (dt == R_LONG_INT)               print_long_array               ((long *)          ptr, my_lo_ndx, my_hi_ndx); 
  else if (dt == R_UNSIGNED_LONG_INT)      print_unsigned_long_array      ((unsigned long *) ptr, my_lo_ndx, my_hi_ndx); 
  else if (dt == R_LONG_LONG)              print_long_long_array          ((long *)          ptr, my_lo_ndx, my_hi_ndx);
  else if (dt == R_UNSIGNED_LONG_LONG)     print_unsigned_long_long_array ((long *)          ptr, my_lo_ndx, my_hi_ndx);
  else if (dt == R_LONG_LONG_INT)          print_long_long_array          ((long *)          ptr, my_lo_ndx, my_hi_ndx);
  else if (dt == R_UNSIGNED_LONG_LONG_INT) print_unsigned_long_long_array ((long *)          ptr, my_lo_ndx, my_hi_ndx);  
  else if (dt == R_FLOAT)                  print_float_array              ((float  *)        ptr, my_lo_ndx, my_hi_ndx);
  else if (dt == R_DOUBLE)                 print_double_array             ((double  *)       ptr, my_lo_ndx, my_hi_ndx);
  else if (dt == R_ENUM_TYPEDEF)           print_int_array                ((int  *)          ptr, my_lo_ndx, my_hi_ndx);
  else if (dt == R_VOID)                   rgst_print_ptrs                (                 &ptr, nelms);
  else if (dt == R_CTYPE_TYPEDEF) {
    print_ctype_array (ptr, dt_name, my_lo_ndx, my_hi_ndx);
  }
  else if ((dt == R_STRUCT) || (dt == R_STRUCT_TYPEDEF)) {
    if (dt_name != NULL) {
      printf("%ld ['pr %ld %s' will print this struct]\n",(long)ptr,(long)ptr,dt_name);
    }
    else {
      printf("%ld\n",(long)ptr);
    } 
  }
  else {
    ctlnotice(me,"programmer error: bad datatype");
  }
}
