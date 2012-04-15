#include "irs.h"
#include "irssrc.h"
#include "irsblk.h"
#include "irsbndry.h"
#include "irsrgst.h"
#include "irsreg.h"
#include "pint.h"
#include "ProblemArray.h"
#include "Rgst.h"
#include "Region.h"
#include "SpeciesFraction.h"
#include "Extents.h"
static void domaincopy_var(void *var1, void *var2, int **map, int lenmap, 
	int *mixmap, int limit,  int topmix, int irep, RGST_Datatype_t type);
void domaincopy(Domain_t *domain1, Extents_t *ext1, 
                Domain_t *domain2, Extents_t *ext2)
{
   char *name;
   int i,j,k;
   int ng;
   int my_in,my_out;
   int jtop;
   int imax,imin;
   int jmax,jmin;
   int kmax,kmin;
   int irep;
   int lenmap;
   int lenmix;
   int sldmaplen;
   int insldmaplen;
   int limit;
   int len1;
   int counter;
   int *mixmap;
   int *sldmap = NULL;
   int *mapin;
   int *mapout;
   int *ifield1;
   int *ifield2;
   int *iptr1;
   int *iptr2;
   double *dfield1;
   double *dfield2;
   double *dptr1;
   double *dptr2;
   void   *field1;
   void   *field2;
   pint *map;
   ProblemArray_t *prb;
   RGST_AttributeElem_t *znlist;
   RGST_AttributeElem_t *znlist_ptr;
   imax = ext1->imax;
   jmax = ext1->jmax;
   kmax = ext1->kmax;
   imin = ext1->imin;
   jmin = ext1->jmin;
   kmin = ext1->kmin;
   lenmix = domain1->mixmax;
   lenmap = LENEXT((*ext1));
   len1 = lenmap;
   irep = 1;
   map = ALLOT(pint,2);
   mapin = map[0] = ALLOT(int,lenmap);
   mapout = map[1] =  ALLOT(int,lenmap);
   mixmap = ALLOT(int,lenmix);
   for (i = 0; i < lenmix; i++) {
      mixmap[i] = 0;
   }
   sldmaplen = 0;
   counter = 0;
   for (k = kmin; k <= kmax; k++) {
      for (j = jmin; j <= jmax; j++) {
         for (i = imin; i <= imax; i++) {
            my_in = i + j * domain1->jp  + k * domain1->kp;
            mapin[counter] = my_in;
            counter++;
         }
      }	
   }
   imax = ext2->imax;
   jmax = ext2->jmax;
   kmax = ext2->kmax;
   imin = ext2->imin;
   jmin = ext2->jmin;
   kmin = ext2->kmin;
   counter=0;
   for (k = kmin; k <= kmax; k++) {
      for (j = jmin; j <= jmax; j++) {
         for (i = imin; i <= imax; i++) {
	    my_in = i + j * domain2->jp + k * domain2->kp;
	    mapout[counter] = my_in;
	    counter++;
         }
      }
   }
   znlist = rgst_list_attr(A_OBJECT, "Nodal");
   znlist_ptr = znlist;
   while (znlist_ptr != NULL) {
      name   = ATTR_GET_OBJECT_NAME(znlist_ptr);
      prb    = ProblemArray_find(name, NULL);
      field1 = ProblemArray_ptr(name,domain1->hash);
      field2 = ProblemArray_ptr(name,domain2->hash);
      insldmaplen = 0;
      if (field1 != NULL){
	if (RGST_QUERY_OBJECT_ATTR(name, "SlideData")) {
	  insldmaplen = sldmaplen;
	}
	domaincopy_var( field1, field2, map, lenmap, sldmap, insldmaplen, 
			domain1->nnalls, irep, prb->type ) ;
      }
      znlist_ptr = znlist_ptr->next;
   }
   bndcopy(domain1,mapin,domain2,mapout,lenmap,irep);
   imax = ext1->imax;
   jmax = ext1->jmax;
   kmax = ext1->kmax;
   imin = ext1->imin;
   jmin = ext1->jmin;
   kmin = ext1->kmin;
   if (imax != imin) imax--;
   if (jmax != jmin) jmax--;
   if (kmax != kmin) kmax--;
   lenmap = (imax - imin + 1) * (jmax - jmin + 1) * (kmax - kmin + 1);
   len1   = lenmap;
   counter = 0;
   for (k = kmin; k <= kmax; k++) {
      for (j = jmin; j <= jmax; j++) {
         for (i = imin; i <= imax; i++) {
            my_in= i + j * domain1->jp + k * domain1->kp;
            mapin[counter] = my_in;
            counter++;
         }
      }
   }
   imax = ext2->imax;
   jmax = ext2->jmax;
   kmax = ext2->kmax;
   imin = ext2->imin;
   jmin = ext2->jmin;
   kmin = ext2->kmin;
   if (imax != imin) imax--;
   if (jmax != jmin) jmax--;
   if (kmax != kmin) kmax--;
   counter=0;
   for (k = kmin; k <= kmax; k++) {
      for (j = jmin; j <= jmax; j++) {
         for (i = imin; i <= imax; i++) {
            my_in = i + j * domain2->jp + k * domain2->kp;
            mapout[counter] = my_in;
            counter++;
         }
      }
   }
   limit = domain1->mixmax;
   counter = 0;
   for (i = 0; i < lenmap; i++) {
      my_in = mapin[i];
      if (domain1->ireg[my_in] < 0) {
	 counter++;
         for (j = 0; j < limit; j++) {
            if ((domain1->ireg[j + domain1->nnalls] != 0) && 
	        (domain1->grdpnt[j] == my_in)) {
	       my_out = j + (( i / len1 ) * limit);
               mixmap[my_out] = -mapout[i];
	    }
	 }
      }
   }
   if (counter == 0) {
      lenmix = 0;
      limit  = 0;
   }
   for (i = 0; i < lenmap; i++) {
      my_in = mapout[i];
      if (domain2->ireg[my_in] < 0) {
         for (j = domain2->nnalls; j < domain2->namix; j++) {
            if (domain2->grdpnt[j - domain2->nnalls] == my_in) {
                 domain2->ireg[j] = 0;
            }
         }
      }
   } 
   jtop = domain2->nnalls;
   for (i = 0; i < lenmix; i++) {
      if (mixmap[i] < 0) {
         for (j = jtop; j < domain2->namix; j++) {
            if (domain2->ireg[j] == 0) {
	       break;
            }
	 }
	 jtop = j + 1;
         domain2->ireg[j] = -1;
         domain2->grdpnt[j-domain2->nnalls] = -mixmap[i];
         mixmap[i] = j;
      }
   }
   znlist = rgst_list_attr(A_OBJECT, "Zonal");
   znlist_ptr = znlist;
   while (znlist_ptr != NULL) {
      name   = ATTR_GET_OBJECT_NAME(znlist_ptr);
      prb    = ProblemArray_find(name, NULL);
      field1 = ProblemArray_ptr(name,domain1->hash);
      field2 = ProblemArray_ptr(name,domain2->hash);
      if (field1 != NULL){
	if (RGST_QUERY_OBJECT_ATTR( name, "Mixed")) {
	  domaincopy_var( field1, field2, map, lenmap, mixmap, limit, 
			  domain1->nnalls, irep, prb->type ) ;
	} else {
	  domaincopy_var( field1, field2, map, lenmap, mixmap, 0, 
			  domain1->nnalls, irep, prb->type ) ;
	} 
      }
      znlist_ptr = znlist_ptr->next;
   }
   if (ifdynspec) {
       SpeciesFraction_t *specmf1 = domain1->specfrac;
       SpeciesFraction_t *specmf2 = domain2->specfrac;
       int *ireg1                 = domain1->ireg;
       int *ireg2                 = domain2->ireg;
       int  mycounter             = 0;
      for (i = 0; i < lenmap; i++) {
         int ip1  = map[0][i];		
         int ip2  = map[1][i];		
	 int ir   = domain1->ireg[ip1];
         if (specmf1[ip1].mass_frac != NULL) {
            if (specmf2[ip2].mass_frac != NULL) FREEMEM(specmf2[ip2].mass_frac);
            specmf2[ip2].mass_frac = MALLOT(double,reg[ir].nspec);
            for (j = 0; j < reg[ir].nspec; j++) {
               specmf2[ip2].mass_frac[j] = specmf1[ip1].mass_frac[j];
            }
         }
      }
      for (i = 0; i < limit; i++) {
         int ip1 = i + domain1->nnalls;
         int ip2 = mixmap[mycounter];
	 mycounter++;
         if (ip2 > 0) {
   	    int ir = domain1->ireg[ip1];
            if (specmf1[ip1].mass_frac != NULL) {
               if (specmf2[ip2].mass_frac != NULL) {
		   FREEMEM(specmf2[ip2].mass_frac);
               }
               specmf2[ip2].mass_frac = MALLOT(double,reg[ir].nspec);
               for (j = 0; j < reg[ir].nspec; j++) {
                  specmf2[ip2].mass_frac[j] = specmf1[ip1].mass_frac[j];
               }
            }
         }
      }
   }
   FREEMEM(mapin);
   FREEMEM(mapout);
   if (domain1->nsrc > 0) {
      srccopy(domain1,ext1,domain2,ext2,irep);
   }
   regndx(domain2);
   FREEMEM(mixmap);
   FREEMEM(map);
}
static void domaincopy_var(void *var1, void *var2, int **map, int lenmap, 
	int *mixmap, int limit,  int topmix, int irep, RGST_Datatype_t type)
{
   int i;
   int ip;
   int counter;
   int my_in, my_out;
   int *ivar1;
   int *ivar2;
   int *mapin,*mapout;
   double *dvar1;
   double *dvar2;
   mapin  = map[0];
   mapout = map[1];
   if (type == R_INT) {
      ivar1 = (int *) var1;	 
      ivar2 = (int *) var2;	 
      for (i = 0; i < lenmap; i++) {
         my_in  = mapin[i];		
         my_out = mapout[i];		
         ivar2[my_out] = ivar1[my_in];
      }
      counter = 0;
      for (ip = 1;ip <= irep; ip++) {
         for (i = 0; i < limit; i++) {
            my_out = mixmap[counter];
	    counter++;
            if (my_out > 0) {
               ivar2[my_out] = ivar1[i+topmix];
            }
         }
      }
   } else if (type == R_DOUBLE) {
      dvar1 = (double *) var1;	 
      dvar2 = (double *) var2;	 
      for (i = 0; i < lenmap; i++) {
         my_in  = mapin[i];		
         my_out = mapout[i];		
         dvar2[my_out] = dvar1[my_in];
      }
      counter = 0;
      for (ip = 1;ip <= irep; ip++) {
         for (i = 0; i < limit; i++) {
            my_out = mixmap[counter];
	    counter++;
            if (my_out > 0) {
               dvar2[my_out] = dvar1[i+topmix];
            }
         }
      }
   } 
}
