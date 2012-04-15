#include "irs.h"
#include "irscom.h"
#include "Boundary.h"
#include "FunctionTimer.h" 
#include "Region.h" 
#include "SpeciesFraction.h"
void speccom_pack(double *buf, Boundary_t *mbnd, Boundary_t *bnd, 
                  Domain_t *domain, SpeciesFraction_t *specmf) ;
void speccom_unpack(double *buf, Boundary_t *mbnd, Boundary_t *bnd, 
                    Domain_t *domain, SpeciesFraction_t *specmf) ;
int speccom_count(Boundary_t *mbnd, Boundary_t *bnd, int comtype, 
                  Domain_t *domain);
int speccom_count(Boundary_t *mbnd, Boundary_t *bnd, int comtype, 
                  Domain_t *domain) {
   int len;
   int i;
   int mat;
   int lenspec;
   int *zdx;
   lenspec = 0;
   len = 0;
   if (comtype == COM_RECV) {
     len = COM_LEN_ALLZ_R((*bnd));
     zdx = COM_ZDX_ALLZ_R((*bnd));
   } else if (comtype == COM_SEND) {
     len = COM_LEN_ALLZ_S((*bnd));
     zdx = COM_ZDX_ALLZ_S((*bnd));
   }
   for (i = 0; i < len; i++) {
      mat = domain->ireg[zdx[i]];
      if (mat > 0) {
         lenspec += reg[mat].nspec;
      }
   }
   len = 0;
   if (comtype == COM_RECV) {
     len = COM_LEN_ALLZ_R((*mbnd));
     zdx = COM_ZDX_ALLZ_R((*mbnd));
   } else if (comtype == COM_SEND) {
     len = COM_LEN_ALLZ_S((*mbnd));
     zdx = COM_ZDX_ALLZ_S((*mbnd));
   }
   for (i = 0; i < len; i++) {
      mat = domain->ireg[zdx[i]];
      if (mat > 0) {
         lenspec += reg[mat].nspec;
      }
   }
   return(lenspec);
}
void speccom_pack(double *buf, Boundary_t *mbnd, Boundary_t *bnd, 
                  Domain_t *domain, SpeciesFraction_t *specmf) {
   int len;
   int i,j;
   int mat;
   int lenspec;
   int *zdx;
   lenspec = 0;
   len = COM_LEN_ALLZ_S((*bnd));
   zdx = COM_ZDX_ALLZ_S((*bnd));
   for (i = 0; i < len; i++) {
      mat = domain->ireg[zdx[i]];
      if (mat > 0) {
	 for (j = 0; j < reg[mat].nspec; j++) {
	    buf[lenspec] = specmf[zdx[i]].mass_frac[j];
	    lenspec++;
	 }
      }
   }
   len = COM_LEN_ALLZ_S((*mbnd));
   zdx = COM_ZDX_ALLZ_S((*mbnd));
   for (i = 0; i < len; i++) {
      mat = domain->ireg[zdx[i]];
      if (mat > 0) {
	 for (j = 0; j < reg[mat].nspec; j++) {
	    buf[lenspec] = specmf[zdx[i]].mass_frac[j];
	    lenspec++;
	 }
      }
   }
}
void speccom_unpack(double *buf, Boundary_t *mbnd, Boundary_t *bnd, 
                    Domain_t *domain, SpeciesFraction_t *specmf) {
   char *me = "speccom_unpack";
   char msg[MAXLINE]; 
   int len;
   int i,j;
   int mat;
   int lenspec;
   int *zdx;
   lenspec = 0;
   len = COM_LEN_ALLZ_R((*bnd));
   zdx = COM_ZDX_ALLZ_R((*bnd));
   for (i = 0; i < len; i++) {
      mat = domain->ireg[zdx[i]];
      if (mat > 0) {
	 if (specmf[zdx[i]].mass_frac != NULL) {
	    sprintf(msg,"Error unpacking species in domain %i from domain  %i.\n",
	                 domain->gblk,bnd->blk_send);
	    ctlerror(me,msg);
	 } else {
	    specmf[zdx[i]].mass_frac = MALLOT(double,reg[mat].nspec);
	    for (j = 0; j < reg[mat].nspec; j++) {
	       specmf[zdx[i]].mass_frac[j] = buf[lenspec];
	       lenspec++;
	    }
	 } 
      }
   }
   len = COM_LEN_ALLZ_R((*mbnd));
   zdx = COM_ZDX_ALLZ_R((*mbnd));
   for (i = 0; i < len; i++) {
      mat = domain->ireg[zdx[i]];
      if (mat > 0) {
	 if (specmf[zdx[i]].mass_frac != NULL) {
	    sprintf(msg,"Error unpacking species in domain %i from domain %i.\n",
	                 domain->gblk,bnd->blk_send);
	    ctlerror(me,msg);
	 } else {
	    specmf[zdx[i]].mass_frac = MALLOT(double,reg[mat].nspec);
	    for (j = 0; j < reg[mat].nspec; j++) {
	       specmf[zdx[i]].mass_frac[j] = buf[lenspec];
	       lenspec++;
	    }
	 } 
      }
   }
}
