#include "irs.h"
#include "irsreg.hh"
#include "Hash.h"
#include "Region.h"
static void species_compparse(Species_t *species);
static void species_compexp(Species_t *species, int newcomp);
int species_input(int regionNumber) {
   char *me = "species_input";
   char msg[MAXLINE];
   char op[MAXLINE];
   char name[MAXLINE];
   int error = 0;
   int gotone;
   int is;
   int clyde;
   int cflag;
   double atwt;
   Species_t *species;
   geta(op);
   species = species_find(op);
   if (species == NULL) {
      if (regionNumber < 0) {
	 species = Species_construct(1);
         sprintf(species->name,op);
         species_add(species);
         nspecies++;
         nspec++;
      } else {
         sprintf(msg,"Species name %s is not defined.",op);
         ctlwarning(me,msg);
         return(-1);
      } 
   } else {
      if (regionNumber < 0) {
         sprintf(msg,"Species %s is being re-defined.",op);
         ctlnotice(me,msg);
	 if (species->ncomp > 0) FREEMEM(species->comp);
         Species_init(species);
	 strcpy(species->name, op);
      } else {
        is = reg[regionNumber].nspec;
        reg[regionNumber].nspec++;
	reg[regionNumber].species = REALLOT(reg[regionNumber].species,
	                                   Species_t, reg[regionNumber].nspec);
        species_copy(&reg[regionNumber].species[is], species);
	species = &reg[regionNumber].species[is];
      } 
   }
   gotone = 1;
   while (gotone) {
      peekc(op);
      if (!strcmp(op,"clyde")) {
         geta(op);
	 if (species->ncomp > 1) {
	    sprintf(msg,"Attempting to set clyde number for multi-component species %s",species->name);
	    ctlwarning(me,msg);
	 }
         clyde = geti(&cflag);
	 if (species->ncomp == 0) species_compexp(species,1);
	 strcpy(species->comp[0].name,species->name);
	 species->comp[0].clyde_number = clyde;
	 species->comp[0].atom_fraction = 1.;
      } else if (!strcmp(op,"atwt")) {
         geta(op);
	 if (species->ncomp > 1) {
	    sprintf(msg,"Attempting to set atomic weight for multi-component species %s",species->name);
	    ctlwarning(me,msg);
	 }
         atwt = getf(&cflag);
	 if (species->ncomp == 0) species_compexp(species,1);
	 strcpy(species->comp[0].name,species->name);
	 species->comp[0].atomic_weight = atwt;
	 species->comp[0].atom_fraction = 1.;
      } else if (!strcmp(op,"mfrac")) {
         geta(op);
	 species->massFraction0 = getf(&cflag);
      } else if (!strcmp(op,"afrac")) {
         geta(op);
	 species->atomFraction0 = getf(&cflag);
      } else if (!strcmp(op,"abar")) {
         geta(op);
	 species->abar = getf(&cflag);
      } else if (!strcmp(op,"zbar")) {
         geta(op);
	 species->zbar = getf(&cflag);
      } else if (!strcmp(op,"reaction")) {
         geta(op);
	 species->reaction = geti(&cflag);
      } else if (!strcmp(op,"component")) {
	 if (regionNumber >= 0) {
	    sprintf(msg,"Attempting set components for species %s inside region command.",species->name);
	    ctlwarning(me,msg);
	    gotone = 0;
	    break;
	 }
         geta(op);
	 species_compparse(species);
      } else {
         gotone = 0;
      } 
   }
   return(0);
}
static void species_compparse(Species_t *species) {
   char op[MAXLINE];
   int gotone;
   int ic;
   Component_t *comp;
   ic = species->ncomp;
   species_compexp(species,1);
   comp = &species->comp[ic];
   geta(comp->name);
   gotone = 1;
   while (gotone) {
      peekc(op);
      if (!strcmp(op,"afrac")) {
         geta(op);
         comp->atom_fraction = getf(&ic);
      } else if (!strcmp(op,"mfrac")) {
         geta(op);
         comp->mass_fraction = getf(&ic);
      } else if (!strcmp(op,"atwt")) {
         geta(op);
         comp->atomic_weight = getf(&ic);
      } else if (!strcmp(op,"clyde")) {
         geta(op);
         comp->clyde_number = geti(&ic);
      } else {
         gotone = 0;
      } 
   }
}
static void species_compexp(Species_t *species, int newcomp) {
   int ic;
   int ic_last;
   ic_last = species->ncomp;
   species->ncomp += newcomp;
   species->comp = REALLOT(species->comp, Component_t, species->ncomp);
   for (ic = ic_last; ic < species->ncomp; ic++) {
      species->comp[ic].atom_fraction = -1.;
      species->comp[ic].mass_fraction = -1.;
      species->comp[ic].clyde_number  = -1;
      species->comp[ic].atomic_weight =  0.;
      species->comp[ic].atomic_number =  0;
   }
}
void species_copy(Species_t *spec1, Species_t *spec2) {
   int i;
   spec1->id             = spec2->id;
   spec1->ncomp          = spec2->ncomp;
   spec1->abar           = spec2->abar ;
   spec1->zbar           = spec2->zbar ;
   spec1->massFraction0  = spec2->massFraction0 ;
   spec1->atomFraction0  = spec2->atomFraction0 ;
   spec1->reaction       = spec2->reaction      ;
   spec1->comp           = NULL;
   spec1->next           = NULL;
   strcpy(spec1->name, spec2->name);
   if (spec1->ncomp > 0) {
      spec1->comp = MALLOT(Component_t, spec1->ncomp);
      for (i = 0; i < spec1->ncomp; i++) {
         strcpy(spec1->comp[i].name,spec2->comp[i].name);
         spec1->comp[i].clyde_number  = spec2->comp[i].clyde_number;
         spec1->comp[i].atomic_number = spec2->comp[i].atomic_number;
         spec1->comp[i].atomic_weight = spec2->comp[i].atomic_weight;
         spec1->comp[i].atom_fraction = spec2->comp[i].atom_fraction;
         spec1->comp[i].mass_fraction = spec2->comp[i].mass_fraction;
      }
   }
}
Species_t* species_find(char *name) {
   Species_t *species = NULL;
   char hashname[MAXLINE];
   sprintf(hashname,"Species_%s",name);
   species =  (Species_t *) hash_lookup_obj(hashname,gv_hash_tbl);
   return(species);
}
void species_add(Species_t *species) {
   char hashname[MAXLINE];
   Species_t *species_root;
   Species_t *species_ptr;
   species_root = (Species_t *) hash_lookup_obj("Species_root",gv_hash_tbl);
   if (species_root == NULL) {
      hash_add("Species_root", "Species_t", species, gv_hash_tbl);
      species->next = NULL;
      sprintf(hashname,"Species_%s",species->name);
      hash_add(hashname,"Species_t",species,gv_hash_tbl);
      return;
   }
   species_ptr = species_root;
   while (species_ptr->next != NULL) species_ptr = species_ptr->next;
   species->next = NULL;    
   sprintf(hashname,"Species_%s",species->name);
   hash_add(hashname,"Species_t",species,gv_hash_tbl);
}
void species_free(void) {
   char name[MAXLINE];
   Species_t *species_root;
   Species_t *species_ptr;
   Species_t *species_next_ptr;
   if (nspecies == 0) return;
   species_root = (Species_t *)hash_lookup_obj("Species_root",gv_hash_tbl);
   species_ptr = species_root;
   hash_del2("Species_root","Species_t",gv_hash_tbl);
   while (species_ptr != NULL) {
      species_next_ptr = species_ptr->next;
      sprintf(name,"Species_%s",species_ptr->name);
      hash_del2(name,"Species_t",gv_hash_tbl);
      if (species_ptr->ncomp > 0) {
         FREEMEM(species_ptr->comp);
      }
      FREEMEM(species_ptr);
      species_ptr = species_next_ptr;
   }
   nspecies = 0;
}

#ifdef SILO
int species_wtsilo(DBfile *inFile, Region_t *regin) {
   char name[MAXLINE];
   int error = 0;
   int is,ic;
   int dims[1];
   Species_t *species;
   Component_t *comp;
   dims[0] = 1;
   error += DBWrite(inFile, "nspec", &regin->nspec, dims, 1, DB_INT);
   species = regin->species;
   for (is = 0; is < regin->nspec; is++) {
      dims[0] = 1;
      sprintf(name,"Species%i",is);
      error += DBMkDir(inFile,name);
      error += DBSetDir(inFile,name);
      error += DBWrite(inFile, "abar", &species[is].abar, dims, 1, DB_DOUBLE);
      error += DBWrite(inFile, "zbar", &species[is].zbar, dims, 1, DB_DOUBLE);
      error += DBWrite(inFile, "massFraction0", &species[is].massFraction0, dims, 1, DB_DOUBLE);
      error += DBWrite(inFile, "atomFraction0", &species[is].atomFraction0, dims, 1, DB_DOUBLE);
      error += DBWrite(inFile, "id", &species[is].id, dims, 1, DB_INT);
      error += DBWrite(inFile, "ncomp", &species[is].ncomp, dims, 1, DB_INT);
      error += DBWrite(inFile, "reaction", &species[is].reaction, dims, 1, DB_INT);
      comp = species[is].comp;
      for (ic = 0; ic < species[is].ncomp; ic++) {
         dims[0] = 1;
         sprintf(name,"Component%i",ic);
         error += DBMkDir(inFile,name);
         error += DBSetDir(inFile,name);
         error += DBWrite(inFile, "clyde_number", &comp[ic].clyde_number, dims, 1, DB_INT);
         error += DBWrite(inFile, "atomic_weight", &comp[ic].atomic_weight, dims, 1, DB_DOUBLE);
         error += DBWrite(inFile, "atom_fraction", &comp[ic].atom_fraction, dims, 1, DB_DOUBLE);
         error += DBWrite(inFile, "mass_fraction", &comp[ic].mass_fraction, dims, 1, DB_DOUBLE);
         dims[0] = strlen(comp[ic].name) + 1;
         error += DBWrite(inFile, "name", comp[ic].name, dims, 1, DB_CHAR);
         error += DBSetDir(inFile,"../");
      }
      dims[0] = strlen(species[is].name) + 1;
      error += DBWrite(inFile, "name", species[is].name, dims, 1, DB_CHAR);
      error += DBSetDir(inFile,"../");
   }
   return(error);
}
#endif

#ifdef SILO
int species_rdsilo(DBfile *inFile, Region_t *regin) {
   char name[MAXLINE];
   int error = 0;
   int is,ic;
   int dims[1];
   Species_t *species;
   Species_t *spec;
   Component_t *comp;
   dims[0] = 1;
   error += DBReadVar(inFile, "nspec", &regin->nspec);
   regin->species = MALLOT(Species_t, regin->nspec);
   species = regin->species;
   for (is = 0; is < regin->nspec; is++) {
      sprintf(name,"Species%i",is);
      error += DBSetDir(inFile,name);
      error += DBReadVar(inFile, "name", &species[is].name);
      error += DBReadVar(inFile, "abar", &species[is].abar);
      error += DBReadVar(inFile, "zbar", &species[is].zbar);
      error += DBReadVar(inFile, "massFraction0", &species[is].massFraction0);
      error += DBReadVar(inFile, "atomFraction0", &species[is].atomFraction0);
      error += DBReadVar(inFile, "ncomp", &species[is].ncomp);
      error += DBReadVar(inFile, "id", &species[is].id);
      error += DBReadVar(inFile, "reaction", &species[is].reaction);
      species[is].comp = MALLOT(Component_t, species[is].ncomp);
      comp = species[is].comp;
      for (ic = 0; ic < species[is].ncomp; ic++) {
         sprintf(name,"Component%i",ic);
         error += DBSetDir(inFile,name);
         error += DBReadVar(inFile, "name", &comp[ic].name);
         error += DBReadVar(inFile, "clyde_number", &comp[ic].clyde_number);
         error += DBReadVar(inFile, "atomic_weight", &comp[ic].atomic_weight);
         error += DBReadVar(inFile, "atom_fraction", &comp[ic].atom_fraction);
         error += DBReadVar(inFile, "mass_fraction", &comp[ic].mass_fraction);
         error += DBSetDir(inFile,"../");
      }
      error += DBSetDir(inFile,"../");
      spec = species_find(species[is].name);
      if (spec == NULL) {
	 spec = Species_construct(1);
         species_copy(spec, &species[is]);
         species_add(spec);
         nspecies++;
      }
   }
   return(error);
}
#endif

#include "irs.h"
void species_init(void) {
   char *me = "species_init";
   char msg[MAXLINE];
   int i;
   int ir;
   int is, ic;
   int imass;
   int iatom;
   double frac;
   double abar;
   double diff;
   Species_t *species;
   Component_t *comp;
   for (ir = 1; ir <= nreg; ir++) {
      species = reg[ir].species;
      for (is = 0; is < reg[ir].nspec; is++) {
         if ((species[is].reaction != 0) && (species[is].ncomp > 1)) {
            sprintf(msg,"Reactions cannot occur in multi-component species %s",
                         species[is].name);
            ctlerror(me,msg);
         }
         comp = species[is].comp;
         imass = 0;
         iatom = 0;
	 for (ic = 0; ic < species[is].ncomp; ic++) {
            if (comp[ic].mass_fraction < 0) imass++;
            if (comp[ic].atom_fraction < 0) iatom++;
         }
         if ((imass > 0) && (iatom > 0)) {
            sprintf(msg,"Mix of mass and atom fraction settings for species %s",
                         species[is].name);
            ctlerror(me,msg);
         }
         if (imass > 0) {
            frac = 0.0;
	    for (ic = 0; ic < species[is].ncomp; ic++) {
	       frac += comp[ic].atom_fraction;
	    }
	    diff = fabs(1.0 - frac);
	    if (diff > 2e-2) {
	       sprintf(msg,"Atom fractions for species %s do not add to one.",species[is].name);
	       ctlerror(me,msg);
	    } else if (diff > 1e-8) {
	       sprintf(msg,"Atom fractions for species %s do not add to one.  \n\t\tRenormalizing",species[is].name);
	       ctlnotice(me,msg);
	    } 
	    for (ic = 0; ic < species[is].ncomp; ic++) {
	      comp[ic].atom_fraction /= frac;
	    }
            frac = 0.0;
	    for (ic = 0; ic < species[is].ncomp; ic++) {
               comp[ic].mass_fraction = comp[ic].atom_fraction*
                                            comp[ic].atomic_weight;
               frac += comp[ic].mass_fraction;
            }
            frac = 1./(frac + ptiny);
	    for (ic = 0; ic < species[is].ncomp; ic++) {
               comp[ic].mass_fraction *= frac;
            }
         } else if (iatom > 0) {
            frac = 0.0;
	    for (ic = 0; ic < species[is].ncomp; ic++) {
	       frac += comp[ic].mass_fraction;
	    }
	    diff = fabs(1.0 - frac);
	    if (diff > 2e-2) {
	       sprintf(msg,"Mass fractions for species %s do not add to one.",species[is].name);
	       ctlerror(me,msg);
	    } else if (diff > 1e-8) {
	       sprintf(msg,"Mass fractions for species %s do not add to one.  \n\t\tRenormalizing",species[is].name);
	       ctlnotice(me,msg);
	    } 
	    for (ic = 0; ic < species[is].ncomp; ic++) {
	      comp[ic].mass_fraction /= frac;
	    }
            frac = 0.0;
	    for (ic = 0; ic < species[is].ncomp; ic++) {
               comp[ic].atom_fraction = comp[ic].mass_fraction /
                                            comp[ic].atomic_weight;
               frac += comp[ic].atom_fraction;
            }
            frac = 1./(frac + ptiny);
	    for (ic = 0; ic < species[is].ncomp; ic++) {
               comp[ic].atom_fraction *= frac;
            }
         } 
         if (species[is].abar < 0.0) {
            abar = 0.0;
            for (ic = 0; ic < species[is].ncomp; ic++) {
               abar += comp[ic].atom_fraction * comp[ic].atomic_weight;
            }
           species[is].abar = abar;
         }
         for (ic = 0; ic < species[is].ncomp; ic++) {
            if (comp[ic].clyde_number < 0) {
               sprintf(msg,"Component %s in species %s has no clyde number",
                            comp[ic].name,species[is].name);
               ctlerror(me,msg);
            }
         }
      }
   }
   for (ir = 1; ir <= nreg; ir++) {
      species = reg[ir].species;
      iatom = 0;
      imass = 0;
      for (is = 0; is < reg[ir].nspec; is++) {
         if (species[is].atomFraction0 < 0) iatom++;
         if (species[is].massFraction0 < 0) imass++;
      }
      if ((imass > 0) && (iatom > 0)) {
         sprintf(msg,"Mix of mass and atom fraction settings for region %i",ir);
         ctlerror(me,msg);
      }
      if (imass > 0) {
	 frac = 0.;
	 for (is = 0; is < reg[ir].nspec; is++) {
	    frac += species[is].atomFraction0;
	 }
	 diff = fabs(1.0 - frac);
	 if (diff > 2e-2) {
	    sprintf(msg,"Atom fractions for material %d do not add to one.",ir);
	    ctlerror(me,msg);
	 } else if (diff > 1e-8) {
	    sprintf(msg,"Atom fractions for material %d do not add to one. \n\t\tRenormalizing.",ir);
	    ctlnotice(me,msg);
	 } 
	 for (is = 0; is < reg[ir].nspec; is++) {
	   species[is].atomFraction0 /= frac;
	 }
         frac = 0.0;
         for (is = 0; is < reg[ir].nspec; is++) {
            species[is].massFraction0 = species[is].atomFraction0 * species[is].abar;
            frac += species[is].massFraction0;
         }
         frac = 1.0 / (frac + ptiny);
         for (is = 0; is < reg[ir].nspec; is++) {
            species[is].massFraction0 *= frac;
         }
      } else if (iatom > 0) {
	 frac = 0.;
	 for (is = 0; is < reg[ir].nspec; is++) {
	    frac += species[is].massFraction0;
	 }
	 diff = fabs(1.0 - frac);
	 if (diff > 2e-2) {
	    sprintf(msg,"Mass fractions for material %d do not add to one.",ir);
	    ctlerror(me,msg);
	 } else if (diff > 1e-8) {
	    sprintf(msg,"Mass fractions for material %d do not add to one. \n\t\tRenormalizing.",ir);
	    ctlnotice(me,msg);
	 } 
	 for (is = 0; is < reg[ir].nspec; is++) {
	   species[is].massFraction0 /= frac;
	 }
         frac = 0.0;
         for (is = 0; is < reg[ir].nspec; is++) {
            species[is].atomFraction0 = species[is].massFraction0 / 
                                        species[is].abar;
            frac += species[is].atomFraction0;
         }
         frac = 1.0 / (frac + ptiny);
         for (is = 0; is < reg[ir].nspec; is++) {
            species[is].atomFraction0 *= frac;
         }
      }
   }
}
