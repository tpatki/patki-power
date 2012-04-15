#include "irs.h"
#include "irsbndry.h"
#include "BoundaryCondition.h"
void bndcopy(Domain_t *domain1, int* mapin, Domain_t *domain2, int *mapout, 
             int lenmap, int irep)
{
   int i;
   int ir;
   int ibc;
   int nbc;
   int len;
   int len1;
   int len2;
   int *flag;
   int *ndx;
   int *ndx1;
   int *ndx2;
   int *mapoutp;
   char op[MAXWORD];
   BoundaryCondition_t *bc1;
   BoundaryCondition_t *bc2;
   flag = ALLOT(int,domain1->nnalls);
   for (i=0;i<domain1->nnalls;i++) {
      flag[i] = 0;
   }
   lenmap = lenmap/irep;
   for (i=0;i<lenmap;i++) {
      flag[mapin[i]] = i + 1 ;
   }
   ndx2 = ALLOT(int,domain2->nnalls);
   bc1 = domain1->bc;
   bc2 = domain2->bc;
   for (ibc = 0; ibc < domain1->nbc; ibc++) {
      len1 = bc1[ibc].len;
      ndx1 = bc1[ibc].ndx;
      len2 = 0;
      for (i=0;i<len1;i++) {
         if (flag[ndx1[i]]>0) {
            ndx2[len2] = flag[ndx1[i]]-1;
            len2++;
         }
      }
      if (len2 > 0) {
         nbc = domain2->nbc;
	 if (nbc >= nbcx) {
             domain2->bc = REALLOT(domain2->bc, BoundaryCondition_t, nbc + 1);
             bc2 = domain2->bc;
	 }
         bc2[nbc].ndx = ALLOT(int,len2*irep);
         len = 0;
         mapoutp = mapout;
         ndx = bc2[nbc].ndx;
         for (ir=1;ir<=irep;ir++) {
            for (i=0;i<len2;i++) {
               ndx[len] = mapoutp[ndx2[i]];
               len++;
            }
            mapoutp = mapoutp+lenmap;
         }
         getbcname(op,ibc,domain1);
         bcin0(len,ndx,nbc,op,domain2);
	 domain2->bc[nbc].rtype = domain1->bc[ibc].rtype ;
	 strcpy(domain2->bc[nbc].ndxName,domain1->bc[ibc].ndxName) ;
         if (bc1[ibc].id > 0) {
            vsamein0(len,ndx,nbc,domain2);
            bc2[nbc].id = bc1[ibc].id;
         }
         domain2->nbc++;
      }
   }
   FREEMEM(flag);
   FREEMEM(ndx2);
}
