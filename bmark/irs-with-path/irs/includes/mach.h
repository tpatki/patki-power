#define vec
#define restrict   

#define CABS(x) fabs(x)
#define LOG(x)  log(x)
#define POW     pow

#ifdef UNIX
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

#ifndef COM_THREADS
#ifndef SIG_DFL
#define SIG_DFL noop
#endif
#endif

#endif

#ifdef MSDOS
#define IBM
#define MSC
#define ANSI
#include <conio.h>
#include <malloc.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <stdarg.h>
#endif

#ifdef macintosh
#define MACPLUS
#include <ctype.h>
#include <math.h>
#endif
