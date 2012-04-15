#include "irs.h"
#include "irssys.h"     
#define DSWAP(a,b) dtemp=(a) ; (a) = (b) ; (b) = dtemp
#define ISWAP(a,b) itemp=(a) ; (a) = (b) ; (b) = itemp
#define M 7
#define NSTACK 51
int sort2_double( int n, int *irr, double *xrr )
{
   int i, ir = n, j, k, l = 1, *istack, jstack = 0, ia ;
   int maxstack, itemp;
   double b, dtemp ;
   char *me = "sort2";
   int error = 0 ;
   istack = ALLOT( int, NSTACK ) ;
   maxstack = NSTACK;
   for ( ; ; ) {
      if ( ir-l < M ) {
         for ( j = l+1 ; j <= ir ; j++ ) {
	    ia = irr[j] ;
	    b  = xrr[j] ;
	    for ( i = j-1 ; i >= 1 ; i-- ) {
	       if ( irr[i] <= ia ) break ;
	       irr[i+1] = irr[i] ;
	       xrr[i+1] = xrr[i] ;
	    }
	    irr[i+1] = ia ;
	    xrr[i+1] = b  ;
	 }
	 if ( !jstack ) {
	    FREEMEM( istack ) ;
	    return( error ) ;
	 }
	 ir      = istack[jstack]  ;
	 l       = istack[jstack-1] ;
	 jstack -= 2 ;
      } else {
         k = (l+ir) >> 1 ;
	 ISWAP( irr[k], irr[l+1] ) ;
	 DSWAP( xrr[k], xrr[l+1] ) ;
	 if ( irr[l+1] > irr[ir] ) {
	    ISWAP( irr[l+1], irr[ir] ) ;
	    DSWAP( xrr[l+1], xrr[ir] ) ;
	 }
	 if ( irr[l] > irr[ir] ) {
	    ISWAP( irr[l], irr[ir] ) ;
	    DSWAP( xrr[l], xrr[ir] ) ;
	 }
	 if ( irr[l+1] > irr[l]) {
	    ISWAP( irr[l+1], irr[l] ) ;
	    DSWAP( xrr[l+1], xrr[l] ) ;
	 }
	 i  = l + 1 ;
	 j  = ir ;
	 ia = irr[l] ;
	 b  = xrr[l] ;
	 for ( ; ; ) {
	    do i++ ; while ( irr[i] < ia ) ;
	    do j-- ; while ( irr[j] > ia ) ;
	       if ( j < i ) break ;
	       ISWAP( irr[i], irr[j] ) ;
	       DSWAP( xrr[i], xrr[j] ) ;
	 }
	 irr[l]  = irr[j] ;
	 irr[j]  = ia ;
	 xrr[l]  = xrr[j] ;
	 xrr[j]  = b ;
	 jstack += 2 ;
         if ( jstack >= maxstack ) {
            maxstack += NSTACK;
            istack = REALLOT(istack, int, maxstack);
         }
	 if ( ir-i+1 >= j-l ) {
	    istack[jstack]   = ir ;
	    istack[jstack-1] = i  ;
	    ir = j - 1 ;
	 } else {
	    istack[jstack]   = j - 1 ;
	    istack[jstack-1] = l ;
	    l = i ;
	 }
      }
   }
}
int sort2_int( int n, int *irr, int *xrr )
{
   int i, ir = n, j, k, l = 1, *istack, jstack = 0, ia ;
   int maxstack, itemp;
   int b, dtemp ;
   char *me = "sort2_int";
   int error = 0 ;
   maxstack = NSTACK;
   istack = ALLOT( int, NSTACK ) ;
   for ( ; ; ) {
      if ( ir-l < M ) {
         for ( j = l+1 ; j <= ir ; j++ ) {
	    ia = irr[j] ;
	    b  = xrr[j] ;
	    for ( i = j-1 ; i >= 1 ; i-- ) {
	       if ( irr[i] <= ia ) break ;
	       irr[i+1] = irr[i] ;
	       xrr[i+1] = xrr[i] ;
	    }
	    irr[i+1] = ia ;
	    xrr[i+1] = b  ;
	 }
	 if ( !jstack ) {
	    FREEMEM( istack ) ;
	    return( error ) ;
	 }
	 ir      = istack[jstack]  ;
	 l       = istack[jstack-1] ;
	 jstack -= 2 ;
      } else {
         k = (l+ir) >> 1 ;
	 ISWAP( irr[k], irr[l+1] ) ;
	 DSWAP( xrr[k], xrr[l+1] ) ;
	 if ( irr[l+1] > irr[ir] ) {
	    ISWAP( irr[l+1], irr[ir] ) ;
	    DSWAP( xrr[l+1], xrr[ir] ) ;
	 }
	 if ( irr[l] > irr[ir] ) {
	    ISWAP( irr[l], irr[ir] ) ;
	    DSWAP( xrr[l], xrr[ir] ) ;
	 }
	 if ( irr[l+1] > irr[l]) {
	    ISWAP( irr[l+1], irr[l] ) ;
	    DSWAP( xrr[l+1], xrr[l] ) ;
	 }
	 i  = l + 1 ;
	 j  = ir ;
	 ia = irr[l] ;
	 b  = xrr[l] ;
	 for ( ; ; ) {
	    do i++ ; while ( irr[i] < ia ) ;
	    do j-- ; while ( irr[j] > ia ) ;
	       if ( j < i ) break ;
	       ISWAP( irr[i], irr[j] ) ;
	       DSWAP( xrr[i], xrr[j] ) ;
	 }
	 irr[l]  = irr[j] ;
	 irr[j]  = ia ;
	 xrr[l]  = xrr[j] ;
	 xrr[j]  = b ;
	 jstack += 2 ;
	 if ( jstack >= maxstack ) {
            maxstack += NSTACK;
            istack = REALLOT(istack, int, maxstack);
	 }
	 if ( ir-i+1 >= j-l ) {
	    istack[jstack]   = ir ;
	    istack[jstack-1] = i  ;
	    ir = j - 1 ;
	 } else {
	    istack[jstack]   = j - 1 ;
	    istack[jstack-1] = l ;
	    l = i ;
	 }
      }
   }
}
int sort_ptr_array (
  void **array_ptr,   
  int    len,         
  size_t fld_offset)  
{
  register int i, j, l=1;
  unsigned char *struct_ptr;
  double *dbl_ptr, *dbl2_ptr;
  double dbl1, dbl2;
  for (i=l; i<len; i++) {
    struct_ptr = array_ptr[i];
    dbl_ptr = (double *)((size_t)(array_ptr[i]) + fld_offset);
    dbl1 = *dbl_ptr;
    for ( j=i-l ; 
         ((j>=0) && (*(double *)((size_t)(array_ptr[j]) + fld_offset)) < dbl1);
         j--) {
      array_ptr[j+l] = array_ptr[j];
    }
     array_ptr[j+l] = (void *)struct_ptr; 
  } 
  return(0);
}
int sort2_double_int(int len, int *in, double *db){
    int i, j, indx, itemp;
    double current, dtemp;
    for(i = 0; i < len - 1; i++){
        indx = i + 1;
        current = db[i];
        for(j = indx; j < len; j++){
            if(db[j] > current){
                current = db[j];
                indx = j; 
            } 
        }
        if(current > db[i]){
            ISWAP(in[i], in[indx]);        
            DSWAP(db[i], db[indx]);
        } 
    }
    return(0);
}
#undef M
#undef NSTACK
#undef ISWAP
#undef DSWAP
