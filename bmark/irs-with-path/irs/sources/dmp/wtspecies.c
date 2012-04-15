#include "irs.h"
#include "irsdmp.h"
#include "irsreg.h"
#include "Region.h"
#ifdef SILO
void wtspecies(char *specname, char *matname, DBfile *idbid, int *lnkmix, 
               int *matlist, int mixlen, DBoptlist *ioptnod, Domain_t *domain) {
   char *me = "species_write_silo";
   char msg[MAXLINE];
   int i,j;
   int ir;
   int izone;
   int spec_count;
   int mix_count;
   int nspecies_mf;
   int indout;
   int error;
   int *nregspec;
   int *speclist;
   int *mix_list;
   int dims[3];
   double *species_mf;
   speclist = MALLOT(int,domain->nnalls);
   mix_list = MALLOT(int,mixlen);
   nspecies_mf = 0;
   for (i = 0; i < domain->namix; i++) {
      if ((ir = matlist[i]) > 0) {
         nspecies_mf += reg[ir].nspec;
      }
   }
   species_mf = MALLOT(double,nspecies_mf);
   spec_count = 0;
   mix_count = 0;
   indout = 0;
   for (i = 0; i < domain->nnalls; i++) {
      if ((ir = matlist[i]) > 0) {
         for (j = 0; j < reg[ir].nspec; j++) {
            species_mf[spec_count + j] = domain->specfrac[i].mass_frac[j];
         }
         speclist[indout] = spec_count + 1;
         indout++;
         spec_count += reg[ir].nspec;
      } else if ((ir = matlist[i]) < 0) {
         speclist[indout] =  -(mix_count + 1);
         indout++;
         mix_list[mix_count] = spec_count + 1; 
         mix_count++;
         izone = -matlist[i];
         ir = matlist[izone];
         for (j = 0; j < reg[ir].nspec; j++) {
            species_mf[spec_count + j] = domain->specfrac[izone].mass_frac[j];
         }
         spec_count += reg[ir].nspec;
         izone = lnkmix[izone - domain->nnalls];
         while (izone  > 0) {
            mix_list[mix_count] = spec_count + 1; 
            mix_count++;
            ir = matlist[izone];
            for (j = 0; j < reg[ir].nspec; j++) {
               species_mf[spec_count + j] = domain->specfrac[izone].mass_frac[j];
            }
            spec_count += reg[ir].nspec;
            izone = lnkmix[izone - domain->nnalls];
         }
      } 
   }
   if (mixlen != mix_count) {
      sprintf(msg,"Error writing out mixed species data.");
      ctlerror(me,msg);
   }
   dims[0] = domain->imax - domain->imin;
   dims[1] = domain->jmax - domain->jmin;
   if (ndims == 2) {
      dims[2] = 0;
   } else {
      dims[2] = domain->kmax - domain->kmin;
   } 
   nregspec = MALLOT(int,nreg);
   for (ir = 1; ir <= nreg; ir++) {
      nregspec[ir - 1] = reg[ir].nspec;
   }
   error = DBPutMatspecies(idbid, specname,matname,nreg,nregspec,
                           speclist, dims, ndims, nspecies_mf, 
                           (float *)species_mf, mix_list, mixlen,
                           DB_DOUBLE,ioptnod);
   if (error != 0) {
      sprintf(msg,"Error writing species data.");
      ctlerror(me,msg);
   }
   FREEMEM(species_mf);
   FREEMEM(speclist);
   FREEMEM(nregspec);
   if (mixlen > 0) FREEMEM(mix_list);
}
#endif
