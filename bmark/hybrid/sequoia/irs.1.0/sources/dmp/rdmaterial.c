#include "irs.h"
#include "irsdmp.h"
#include "irsreg.h"
#include "Extents.h"
#ifdef SILO
int rdmaterial(
  DBfile *idbid,        
  char *material_name,
  char *species_name,
  int  spec_read_flag, 
  Extents_t ext,         
  Domain_t *domain)
{
  char *me = "rdmaterial";
  int  i,j,k, ip;
  int  indin, indout;
  int    *iregmix;
  double *volmix, *vfmix;
  DBmaterial    *material;
  material = DBGetMaterial(idbid,material_name);
  iregmix = domain->ireg + domain->nnalls;
  volmix  = domain->vol + domain->nnalls;
  vfmix   = (double *)material->mix_vf;
  for (i = domain->mixmax - 1; i >= 0; i--) {
     if (iregmix[i] != 0) break;
  }
  domain->imaxmix = MAX(0,i);
  for (i = domain->imaxmix; i < domain->mixmax; i++) {
     domain->grdpnt[i] = 0;
  }
  indin   = 0;
  if (ndims == 3) {
    for (k = ext.kmin; k < ext.kmax; k++) {
      for (j = ext.jmin; j < ext.jmax; j++) {
        for (i = ext.imin; i < ext.imax; i++) {
          indout = i + j*domain->jp + k*domain->kp;
          if (material->matlist[indin] < 0) {
            ip = (-material->matlist[indin]);
            domain->ireg[indout] = -1;
            while (ip > 0) {
              int id = ip - 1 + domain->imaxmix;		 
              domain->grdpnt[ id ] = indout;
              iregmix[ id ]        = material->mix_mat[ip - 1];
              volmix[ id ]         = vfmix[ip - 1];
              ip                   = material->mix_next[ip - 1];
            }
          } else {
            domain->ireg[indout] = material->matlist[indin];
          }
          indin++;
        }
      }
    }
  } else {
    for (j = ext.jmin; j < ext.jmax; j++) {
      for (i = ext.imin; i < ext.imax; i++) {
        indout = i + j*domain->jp;
        if (material->matlist[indin] < 0) {
           ip = (-material->matlist[indin]);
           domain->ireg[indout] = -1;
           while (ip > 0) {
             int id = ip - 1 + domain->imaxmix;		 
             domain->grdpnt[ id ] = indout;
             iregmix[ id ]        = material->mix_mat[ip - 1];
             volmix[ id ]         = vfmix[ip - 1];
             ip                   = material->mix_next[ip - 1];
          }
        } else {
          domain->ireg[indout] = material->matlist[indin];
        } 
        indin++;
      }
    }
  }
  if (spec_read_flag > 0) {
     rdspecies(species_name, idbid,material, ext, domain);
  }
  DBFreeMaterial(material);
  regndx( domain ) ;
  return(0) ;
}
#endif
