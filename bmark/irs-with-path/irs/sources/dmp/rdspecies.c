#include "irs.h"
#include "irsdmp.h"
#include "Region.h"
#include "Extents.h"
#include "SpeciesFraction.h"
#ifdef SILO
void rdspecies(char *name, DBfile *idbid, DBmaterial *material, Extents_t ext, 
               Domain_t *domain) {
   int i,j,k;
   int l,n;
   int id,ip,ir;
   int len;
   int count;
   int indin,indout;
   double *species_mf;
   SpeciesFraction_t *specmix;
   DBmatspecies *matspecies;
   for (i = 0; i < domain->namix; i++) {
      if ((domain->specfrac[i].mass_frac == NULL) && 
          (domain->ireg[i] > 0)) {
         ir  = domain->ireg[i];
         len = reg[ir].nspec;
         domain->specfrac[i].mass_frac = MALLOT(double,len);
      }
   }
   specmix = domain->specfrac + domain->nnalls;
   matspecies = DBGetMatspecies(idbid,name);
   species_mf = (double *)matspecies->species_mf;
   indin = 0;
   count = domain->imaxmix;
   if (ndims == 2) {
      for (j = ext.jmin; j < ext.jmax; j++) {
         for (i = ext.imin; i < ext.imax; i++) {
            indout = i + j*domain->jp;
            if ((ir = material->matlist[indin]) > 0) {
               ip = matspecies->speclist[indin] - 1;
               for (l = 0; l < reg[ir].nspec; l++) {
                  domain->specfrac[indout].mass_frac[l] = species_mf[ip + l];
               }
            } else { 
               n = (-material->matlist[indin]) - 1;
               id = (-matspecies->speclist[indin]) - 1;
               while (material->mix_next[n] > 0) {
                  ip = matspecies->mix_speclist[id] - 1;
                  ir = material->mix_mat[n];
                  for (l = 0; l < reg[ir].nspec; l++) {
                     specmix[count].mass_frac[l] = species_mf[ip + l];
                  }
                  n++;
                  id++;
                  count++;
               }
               ip = matspecies->mix_speclist[id] - 1;
               ir = material->mix_mat[n];
               for (l = 0; l < reg[ir].nspec; l++) {
                  specmix[count].mass_frac[l] = species_mf[ip + l];
               }
               count++;
            } 
            indin++;
         }
      }
   } else {
      for (k = ext.kmin; k < ext.kmax; k++) {
         for (j = ext.jmin; j < ext.jmax; j++) {
            for (i = ext.imin; i < ext.imax; i++) {
               indout = i + j*domain->jp + k*domain->kp;
               if ((ir = material->matlist[indin]) > 0) {
                  ip = matspecies->speclist[indin] - 1;
                  for (l = 0; l < reg[ir].nspec; l++) {
                     domain->specfrac[indout].mass_frac[l] = species_mf[ip + l];
                  }
               } else { 
                  n = (-material->matlist[indin]) - 1;
                  id = (-matspecies->speclist[indin]) - 1;
                  while (material->mix_next[n] > 0) {
                     ip = matspecies->mix_speclist[id] - 1;
                     ir = material->mix_mat[n];
                     for (l = 0; l < reg[ir].nspec; l++) {
                        specmix[count].mass_frac[l] = species_mf[ip + l];
                     }
                     n++;
                     id++;
                     count++;
                  }
                  ip = matspecies->mix_speclist[id] - 1;
                  ir = material->mix_mat[n];
                  for (l = 0; l < reg[ir].nspec; l++) {
                     specmix[count].mass_frac[l] = species_mf[ip + l];
                  }
                  count++;
               }
               indin++;
            }
         }
      }
   } 
   DBFreeMatspecies(matspecies);
}
#endif
