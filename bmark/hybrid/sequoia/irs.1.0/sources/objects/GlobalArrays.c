#include "irs.h"
#include "irsobjects.h"
#include "irsrgst.h"
#include "irsreg.h"
#include "ProblemArray.h"
#include "Rgst.h"
void GlobalArrays_register( void ) {
   char *name;
   int i;

   ProblemArray_add("regetot", NULL, nregx+1, R_DOUBLE, NULL);
   rgst_add_attr(A_OBJECT,"regetot","GlobalArray");
   rgst_add_attr(A_OBJECT,"regetot","DomainVar");
   rgst_add_attr(A_OBJECT,"regetot","OnDump");
   ProblemArray_add("regke", NULL, nregx+1, R_DOUBLE, NULL);
   rgst_add_attr(A_OBJECT,"regke","GlobalArray");
   rgst_add_attr(A_OBJECT,"regke","DomainVar");
   rgst_add_attr(A_OBJECT,"regke","OnDump");
   ProblemArray_add("regie", NULL, nregx+1, R_DOUBLE, NULL);
   rgst_add_attr(A_OBJECT,"regie","GlobalArray");
   rgst_add_attr(A_OBJECT,"regie","DomainVar");
   rgst_add_attr(A_OBJECT,"regie","OnDump");
   ProblemArray_add("regpe", NULL, nregx+1, R_DOUBLE, NULL);
   rgst_add_attr(A_OBJECT,"regpe","GlobalArray");
   rgst_add_attr(A_OBJECT,"regpe","DomainVar");
   rgst_add_attr(A_OBJECT,"regpe","OnDump");
   ProblemArray_add("regtke", NULL, nregx+1, R_DOUBLE, NULL);
   rgst_add_attr(A_OBJECT,"regtke","GlobalArray");
   rgst_add_attr(A_OBJECT,"regtke","DomainVar");
   rgst_add_attr(A_OBJECT,"regtke","OnDump");
   ProblemArray_add("regmass", NULL, nregx+1, R_DOUBLE, NULL);
   rgst_add_attr(A_OBJECT,"regmass","GlobalArray");
   rgst_add_attr(A_OBJECT,"regmass","DomainVar");
   rgst_add_attr(A_OBJECT,"regmass","OnDump");
   ProblemArray_add("regvol", NULL, nregx+1, R_DOUBLE, NULL);
   rgst_add_attr(A_OBJECT,"regvol","GlobalArray");
   rgst_add_attr(A_OBJECT,"regvol","DomainVar");
   rgst_add_attr(A_OBJECT,"regvol","OnDump");
   ProblemArray_add("regxmom", NULL, nregx+1, R_DOUBLE, NULL);
   rgst_add_attr(A_OBJECT,"regxmom","GlobalArray");
   rgst_add_attr(A_OBJECT,"regxmom","DomainVar");
   rgst_add_attr(A_OBJECT,"regxmom","OnDump");
   ProblemArray_add("regymom", NULL, nregx+1, R_DOUBLE, NULL);
   rgst_add_attr(A_OBJECT,"regymom","GlobalArray");
   rgst_add_attr(A_OBJECT,"regymom","DomainVar");
   rgst_add_attr(A_OBJECT,"regymom","OnDump");
   ProblemArray_add("regzmom", NULL, nregx+1, R_DOUBLE, NULL);
   rgst_add_attr(A_OBJECT,"regzmom","GlobalArray");
   rgst_add_attr(A_OBJECT,"regzmom","DomainVar");
   rgst_add_attr(A_OBJECT,"regzmom","OnDump");
   ProblemArray_add("regxmomp", NULL, nregx+1, R_DOUBLE, NULL);
   rgst_add_attr(A_OBJECT,"regxmomp","GlobalArray");
   rgst_add_attr(A_OBJECT,"regxmomp","DomainVar");
   rgst_add_attr(A_OBJECT,"regxmomp","OnDump");
   ProblemArray_add("regymomp", NULL, nregx+1, R_DOUBLE, NULL);
   rgst_add_attr(A_OBJECT,"regymomp","GlobalArray");
   rgst_add_attr(A_OBJECT,"regymomp","DomainVar");
   rgst_add_attr(A_OBJECT,"regymomp","OnDump");
   ProblemArray_add("regzmomp", NULL, nregx+1, R_DOUBLE, NULL);
   rgst_add_attr(A_OBJECT,"regzmomp","GlobalArray");
   rgst_add_attr(A_OBJECT,"regzmomp","DomainVar");
   rgst_add_attr(A_OBJECT,"regzmomp","OnDump");
   ProblemArray_add("regxmomn", NULL, nregx+1, R_DOUBLE, NULL);
   rgst_add_attr(A_OBJECT,"regxmomn","GlobalArray");
   rgst_add_attr(A_OBJECT,"regxmomn","DomainVar");
   rgst_add_attr(A_OBJECT,"regxmomn","OnDump");
   ProblemArray_add("regymomn", NULL, nregx+1, R_DOUBLE, NULL);
   rgst_add_attr(A_OBJECT,"regymomn","GlobalArray");
   rgst_add_attr(A_OBJECT,"regymomn","DomainVar");
   rgst_add_attr(A_OBJECT,"regymomn","OnDump");
   ProblemArray_add("regzmomn", NULL, nregx+1, R_DOUBLE, NULL);
   rgst_add_attr(A_OBJECT,"regzmomn","GlobalArray");
   rgst_add_attr(A_OBJECT,"regzmomn","DomainVar");
   rgst_add_attr(A_OBJECT,"regzmomn","OnDump");
   ProblemArray_add("regtmatavg", NULL, nregx+1, R_DOUBLE, NULL);
   rgst_add_attr(A_OBJECT,"regtmatavg","GlobalArray");
   rgst_add_attr(A_OBJECT,"regtmatavg","DomainVar");
   rgst_add_attr(A_OBJECT,"regtmatavg","OnDump");
   ProblemArray_add("regtionavg", NULL, nregx+1, R_DOUBLE, NULL);
   rgst_add_attr(A_OBJECT,"regtionavg","GlobalArray");
   rgst_add_attr(A_OBJECT,"regtionavg","DomainVar");
   rgst_add_attr(A_OBJECT,"regtionavg","OnDump");
   ProblemArray_add("regtradavg", NULL, nregx+1, R_DOUBLE, NULL);
   rgst_add_attr(A_OBJECT,"regtradavg","GlobalArray");
   rgst_add_attr(A_OBJECT,"regtradavg","DomainVar");
   rgst_add_attr(A_OBJECT,"regtradavg","OnDump");
   ProblemArray_add("regcveavg", NULL, nregx+1, R_DOUBLE, NULL);
   rgst_add_attr(A_OBJECT,"regcveavg","GlobalArray");
   rgst_add_attr(A_OBJECT,"regcveavg","DomainVar");
   rgst_add_attr(A_OBJECT,"regcveavg","OnDump");
   ProblemArray_add("regcviavg", NULL, nregx+1, R_DOUBLE, NULL);
   rgst_add_attr(A_OBJECT,"regcviavg","GlobalArray");
   rgst_add_attr(A_OBJECT,"regcviavg","DomainVar");
   rgst_add_attr(A_OBJECT,"regcviavg","OnDump");
   ProblemArray_add("regdtnetot", NULL, nregx+1, R_DOUBLE, NULL);
   rgst_add_attr(A_OBJECT,"regdtnetot","GlobalArray");
   rgst_add_attr(A_OBJECT,"regdtnetot","DomainVar");
   rgst_add_attr(A_OBJECT,"regdtnetot","OnDump");
   ProblemArray_add("regtnetot", NULL, nregx+1, R_DOUBLE, NULL);
   rgst_add_attr(A_OBJECT,"regtnetot","GlobalArray");
   rgst_add_attr(A_OBJECT,"regtnetot","DomainVar");
   rgst_add_attr(A_OBJECT,"regtnetot","OnDump");
   ProblemArray_add("regpartmass", NULL, nregx+1, R_DOUBLE, NULL);
   rgst_add_attr(A_OBJECT,"regpartmass","GlobalArray");
   rgst_add_attr(A_OBJECT,"regpartmass","DomainVar");
   rgst_add_attr(A_OBJECT,"regpartmass","OnDump");
   ProblemArray_add("regpartke", NULL, nregx+1, R_DOUBLE, NULL);
   rgst_add_attr(A_OBJECT,"regpartke","GlobalArray");
   rgst_add_attr(A_OBJECT,"regpartke","DomainVar");
   rgst_add_attr(A_OBJECT,"regpartke","OnDump");
   ProblemArray_add("regpartdke", NULL, nregx+1, R_DOUBLE, NULL);
   rgst_add_attr(A_OBJECT,"regpartdke","GlobalArray");
   rgst_add_attr(A_OBJECT,"regpartdke","DomainVar");
   rgst_add_attr(A_OBJECT,"regpartdke","OnDump");
   ProblemArray_add("regpartnum", NULL, nregx+1, R_DOUBLE, NULL);
   rgst_add_attr(A_OBJECT,"regpartnum","GlobalArray");
   rgst_add_attr(A_OBJECT,"regpartnum","DomainVar");
   rgst_add_attr(A_OBJECT,"regpartnum","OnDump");
   ProblemArray_add("regpartnump", NULL, nregx+1, R_DOUBLE, NULL);
   rgst_add_attr(A_OBJECT,"regpartnump","GlobalArray");
   rgst_add_attr(A_OBJECT,"regpartnump","DomainVar");
   rgst_add_attr(A_OBJECT,"regpartnump","OnDump");
   ProblemArray_add("regpartxmom", NULL, nregx+1, R_DOUBLE, NULL);
   rgst_add_attr(A_OBJECT,"regpartxmom","GlobalArray");
   rgst_add_attr(A_OBJECT,"regpartxmom","DomainVar");
   rgst_add_attr(A_OBJECT,"regpartxmom","OnDump");
   ProblemArray_add("regpartymom", NULL, nregx+1, R_DOUBLE, NULL);
   rgst_add_attr(A_OBJECT,"regpartymom","GlobalArray");
   rgst_add_attr(A_OBJECT,"regpartymom","DomainVar");
   rgst_add_attr(A_OBJECT,"regpartymom","OnDump");
   ProblemArray_add("regpartzmom", NULL, nregx+1, R_DOUBLE, NULL);
   rgst_add_attr(A_OBJECT,"regpartzmom","GlobalArray");
   rgst_add_attr(A_OBJECT,"regpartzmom","DomainVar");
   rgst_add_attr(A_OBJECT,"regpartzmom","OnDump");
}
void GlobalArrays_free( HashTable_t *hash ) {
   char *name;
   int i;
   ProblemArray_t *prb;
   RGST_AttributeElem_t *globalvars;
   globalvars = rgst_list_attr(A_OBJECT, "GlobalArray");
   while (globalvars != NULL) {
      name = ATTR_GET_OBJECT_NAME(globalvars);
      prb  = ProblemArray_find(name, hash);
      globalvars = globalvars->next;
      if (prb != NULL) {
         FREEMEM(prb->ptr);
         ProblemArray_del(name, hash);
      }
   }
}
void GlobalArrays_allot( HashTable_t *hash ) {
   char *name;
   int i;
   double *dptr;
   int *iptr;
   ProblemArray_t *prb;
   RGST_AttributeElem_t *globalvars;
   globalvars = rgst_list_attr(A_OBJECT, "GlobalArray");
   while (globalvars != NULL) {
      name = ATTR_GET_OBJECT_NAME(globalvars);
      prb  = ProblemArray_find(name, NULL);
      if (prb->type == R_DOUBLE) {
         dptr = MALLOT(double, prb->len);
         for (i = 0; i < prb->len; i++) {
            dptr[i] = 0.;
         }
	 if (hash == NULL) {
	    prb->ptr = (void *)dptr;
	 } else {
            if ( RGST_QUERY_OBJECT_ATTR(name,"DomainVar")) {
                ProblemArray_add(name, dptr, prb->len, R_DOUBLE, hash);
            } else {
               FREEMEM(dptr);
            } 
	 } 
      } else if (prb->type == R_INT) {
         iptr = MALLOT(int, prb->len);
         for (i = 0; i < prb->len; i++) {
            iptr[i] = 0;
         }
	 if (hash == NULL) {
	    prb->ptr = (void *)iptr;
	 } else {
            if ( RGST_QUERY_OBJECT_ATTR(name,"DomainVar")) {
                ProblemArray_add(name, iptr, prb->len, R_INT, hash);
            } else {
               FREEMEM(iptr);
            } 
	 } 
      } 
      globalvars = globalvars->next;
   }
}
