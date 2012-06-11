#include "transport/TetonInterface/TetonNT.hh"

extern "C"
{

int compr(const void *a,
          const void *b){
   int answer = 0, ta = 0, tb = 0;

   ta = *((int *)a);
   tb = *((int *)b);
   if(ta < tb){
      answer = -1;
   }
   if(ta == tb){
      answer = 0;
   }
   if(ta > tb){
      answer = 1;
   }
   return(answer);
}

void
rmdupsort(int *list,
          int *num) {

   int i,  n, entry, entrylast, nentries;
   int *tmplist;
   void  *entryptr;

   tmplist = new int [*num];
   nentries = *num;

// use qsort and bsearch to vastly speed up sort and rm of dups.
   qsort (list, nentries, 4, compr);

   entrylast = -1;
   n = 0;
   for(i=0; i< *num; i++) {
      entry = list[i];
      if( entry == entrylast){
         continue;
      }
      entryptr = bsearch (&entry, list, nentries, 4, compr);
      if (entryptr  ==  0){
         tmplist[n++] = entry;
      }
      else {
         entrylast = entry;
         tmplist[n++] = entry;
      }
   }

   for(i=0; i < n; i++) {
      list[i] = tmplist[i];
   }
   for(i=n; i < *num; i++) {
      list[i] = -1;
   }

   *num = n;
   delete [] tmplist;

   return;
}

}

extern "C" {
   void
   F77_ID(getiterpointer_, getiterpointer, GETITERPOINTER)
          (void *resIterControls, void **keepIterControls) {
      *keepIterControls = resIterControls;
   }
}

extern "C" {
   void
   F77_ID(getdtpointer_, getdtpointer, GETDTPOINTER)
          (void *resDtControls, void **keepDtControls) {
      *keepDtControls   = resDtControls;
   }
}

extern "C" {
   void
   F77_ID (getgeompointer_, getgeompointer, GETGEOMPOINTER)
          (void *resGeom, void **keepGeom) {
      *keepGeom = resGeom;
   }
}

extern "C" {
   void
   F77_ID (getmatpointer_, getmatpointer, GETMATPOINTER)
          (void *resMat, void **keepMat) {
      *keepMat = resMat;
   }
}

extern "C" {
   void
   F77_ID (getsizepointer_, getsizepointer, GETSIZEPOINTER)
          (void *resSize, void **keepSize) {
      *keepSize = resSize;
   }
}

extern "C" {
   void
   F77_ID (geteditpointer_, geteditpointer, GETEDITPOINTER)
          (void *resEdit, void **keepEdit) {
      *keepEdit = resEdit;
   }
}

extern "C" {
   void
   F77_ID (getprofilepointer_, getprofilepointer, GETPROFILEPOINTER)
          (void *resProf, void **keepProf) {
      *keepProf = resProf;
   }
}

extern "C" {
   void
   F77_ID (getquadpointer_, getquadpointer, GETQUADPOINTER)
          (void *resQuad, void **keepQuad) {
      *keepQuad = resQuad;
   }
}


