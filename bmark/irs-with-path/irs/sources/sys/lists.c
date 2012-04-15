#include "irs.h"
#include "irssys.h"     
int  lists_overlap(int *list1, int nlist1,
                    int *list2, int nlist2,
                    int *list3) {
   int i;
   int i1;
   int i2;
   int ic;
   int len;
   int *mylist1;
   int *mylist2;
   int *junk;
   if ((nlist1 == 0) || (nlist2 == 0)) return(0);
   len = MAX(nlist1, nlist2);
   mylist1 = MALLOT(int, nlist1);
   mylist2 = MALLOT(int, nlist2);
   junk    = MALLOT(int, len);
   for (i = 0; i < nlist1; i++) {
      mylist1[i] = list1[i];
   }
   for (i = 0; i < nlist2; i++) {
      mylist2[i] = list2[i];
   }
   sort2_int(nlist1, mylist1 - 1, junk - 1);
   sort2_int(nlist2, mylist2 - 1, junk - 1);
   i1 = i2 = ic = 0;
   while ((i1 < nlist1) && (i2 < nlist2)) {
      if (mylist1[i1] == mylist2[i2]) {   
         list3[ic++] = mylist1[i1];
         i1++;
         i2++;
      } else if (mylist1[i1] < mylist2[i2]) {   
         i1++;
      } else if (mylist1[i1] > mylist2[i2]) {   
         i2++;
      } 
   }
   FREEMEM(mylist1);
   FREEMEM(mylist2);
   FREEMEM(junk);
   return(ic);
}
