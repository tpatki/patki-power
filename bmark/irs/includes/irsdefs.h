#ifndef irsdefs_H
#define irsdefs_H

#ifndef NULL
#define NULL 0
#endif
  
#ifndef MAXWORD
#define MAXWORD 32
#endif

#ifndef MAXLINE
#define MAXLINE 256
#endif

#ifndef TRUE
#define TRUE    1
#endif

#ifndef FALSE
#define FALSE   0
#endif

#ifndef PTINY
#define PTINY	1.0e-80
#endif

#ifndef PI
#define PI	3.14159265358979
#endif

#ifndef TWOPI
#define TWOPI	6.28318530717959
#endif

#ifndef FOURPI
#define FOURPI	12.5663706143592
#endif

/*
#ifndef MAXDOUBLE
#define MAXDOUBLE	1e+300
#endif
*/

#ifndef MIN
#define MIN(x,y)	((x)<(y)?(x):(y))
#endif

#ifndef MAX
#define MAX(x,y)	((x)>(y)?(x):(y))
#endif

#ifndef R_MAXSTR
#define R_MAXSTR	128
#endif

#ifndef R_MAXSTR_PLUS1
#define R_MAXSTR_PLUS1  129
#endif

#ifndef STRLEN
#define STRLEN		256
#endif

#define MAXBLKS    576
#define MAXLINE    256
#define NFPAX      108
#define NIPAX       33
#define MAXWORD     32
#define NRANKX       4
#define QUAD2D       2
#define HEX3D        3
#define NFIT         4

#define NODAL_ARRAY  0
#define ZONAL_ARRAY  1
#define GLOBAL_ARRAY 2

#define NO_DUMP      0
#define DUMP         1

#define INT          0
#define FLOAT        1
#define CHAR         2

#ifndef ALLOT
#define ALLOT(a,b)  (a *) calloc(b,sizeof(a))
#endif

#ifndef MALLOT
#define MALLOT(a,b)  (a *) malloc((b)*sizeof(a))
#endif

#ifndef REALLOT
#define REALLOT(a,b,c)  (b *) realloc(a,(c)*sizeof(b))
#endif

#ifndef FALLOT
#define FALLOT(b)   ftemp2 ;  ftemp2 += b
#endif

#ifndef IALLOT
#define IALLOT(b)   itemp2 ;  itemp2 += b
#endif

#ifndef FREEMEM
#define FREEMEM(iptr) if (iptr != NULL) { free(iptr); iptr = NULL; }
#endif


#endif

/*******************************************************************************
* END OF FILE
*******************************************************************************/
