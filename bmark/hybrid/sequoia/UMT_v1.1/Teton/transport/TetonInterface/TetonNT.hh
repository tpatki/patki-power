#ifndef __TETON_TETONNT_HH__
#define __TETON_TETONNT_HH__


#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "scstd.h"

#undef max

extern "C"
{

// Used to get pointer back as void * from the fortran wrapper.
   void
   F77_ID(getiterpointer_, getiterpointer, GETITERPOINTER)
         (void *, void **);

   void
   F77_ID(getdtpointer_, getdtpointer, GETDTPOINTER)
         (void *, void **);

   void
   F77_ID(getgeompointer_, getgeompointer, GETGEOMPOINTER)
         (void *, void **);

   void
   F77_ID(getmatpointer_, getmatpointer, GETMATPOINTER)
         (void *, void **);

   void
   F77_ID(getsizepointer_, getsizepointer, GETSIZEPOINTER)
         (void *, void **);

   void
   F77_ID(geteditpointer_, geteditpointer, GETEDITPOINTER)
         (void *, void **);

   void
   F77_ID(getprofilepointer_, getprofilepointer, GETPROFILEPOINTER)
         (void *, void **);

   void
   F77_ID(getquadpointer_, getquadpointer, GETQUADPOINTER)
         (void *, void **);

   int
   compr(void const*, void const*);

   void
   rmdupsort(int*, int*);

}

#endif                   // __TETON_TETONNT_HH__
