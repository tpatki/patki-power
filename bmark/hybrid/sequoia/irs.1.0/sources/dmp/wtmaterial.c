#include "irs.h"
#include "irsreg.h"
#include "irsdmp.h"
#include "Region.h"
#ifdef SILO
int wtmaterial(
  DBfile *idbid, 
  DBoptlist *ioptnod,
  char *material_name, 
  char *species_name, 
  char *mesh_name, 
  int  *zdx,            
  int  *zdx_len,        
  int  spec_write_flag, 
  Domain_t *domain)	
{
  char *me = "wtmaterial";
  int  ir, izone, n, mixlen, mat_index;
  int  i, indout;
  int  dims[3];
  double *mix_vf;
  int *lnkmix, *mix_mat, *mix_zone, *mix_next;
  int *matnos, *matlist, *matlist_out, *ndxmix, *grdmix;
  matnos = MALLOT(int,nreg);
  for (i = 0; i < nreg; i++ ) { 
     matnos[i] = i+1; 
  }
  matlist     = MALLOT(int,domain->namix);
  matlist_out = MALLOT(int,domain->namix);
  for (i = 0; i < domain->namix; i++){
    matlist[i] = domain->ireg[i];
  }
  lnkmix = ALLOT(int,domain->mixmax);
  mixlen=0;
  for ( ir = nreg ; ir > 0 ; ir-- ) {
    ndxmix = domain->rndxmix[ir] ;
    grdmix = domain->rgrdmix[ir] ;
    n = domain->rlenmix[ir] ;
    for ( i = 0 ; i < n ; i++ ) {
      lnkmix[ndxmix[i]-domain->nnalls] = -1 ;
      mixlen++;
      if (matlist[grdmix[i]] < -1) {
        lnkmix[ndxmix[i]-domain->nnalls] = -matlist[grdmix[i]] ;
      }
      matlist[grdmix[i]] = -ndxmix[i] ;
    }
  }
  mix_mat    = NULL;
  mix_zone   = NULL;
  mix_next   = NULL;
  mix_vf     = NULL;
  if (mixlen > 0) {
     mix_mat    = ALLOT(int,mixlen);
     mix_zone   = ALLOT(int,mixlen);
     mix_next   = ALLOT(int,mixlen);
     mix_vf     = ALLOT(double,mixlen);
  }
  indout    = 0 ;
  mat_index = 1 ;
  for ( i = 0 ; i < domain->nnalls ; i++ ) {
    if ( matlist[i] > 0 ) {
      matlist_out[indout] = matlist[i] ;
      indout++ ;
    }  else if ( matlist[i] < 0 ) {
      matlist_out[indout]   = -mat_index  ;
      izone                 = -matlist[i] ;
      mix_zone[mat_index-1] = indout + 1;
      mix_vf[mat_index-1]   = domain->vol[izone] ;
      mix_mat[mat_index-1]  = domain->ireg[izone] ;
      mix_next[mat_index-1] = 0 ;
      zdx[mat_index-1]      = izone ;
      mat_index++ ;
      izone = lnkmix[izone-domain->nnalls] ;
      while ( izone > 0 ) {
        mix_next[mat_index-2] = mat_index ;
        mix_zone[mat_index-1] = indout + 1;
        mix_vf[mat_index-1]   = domain->vol[izone] ;
        mix_mat[mat_index-1]  = domain->ireg[izone] ;
        mix_next[mat_index-1] = 0 ;
        zdx[mat_index-1]      = izone ;
        mat_index++ ;
        izone = lnkmix[izone-domain->nnalls] ;
      }
      indout++ ;
    }   
  }
  dims[0] = (domain->imax - domain->imin) ;
  dims[1] = (domain->jmax - domain->jmin) ;
  dims[2] = 0;
  if (ndims == 3) {
     dims[2] = (domain->kmax - domain->kmin) ;
  } 
  if (DBPutMaterial(idbid,material_name,mesh_name,nreg,matnos,
                    matlist_out,dims,ndims,mix_next,mix_mat, mix_zone, 
                   (float *)mix_vf, mixlen,DB_DOUBLE,ioptnod) != 0) {
    ctlerror(me,gv_errmsg_DBPutMaterial);
  }
  if (spec_write_flag > 0) {
     wtspecies(species_name, material_name, idbid,lnkmix,matlist,mixlen,ioptnod,domain);
  }
  FREEMEM(lnkmix);
  FREEMEM(matlist);
  FREEMEM(matlist_out);
  FREEMEM(matnos);
  if (mixlen > 0) {
    FREEMEM(mix_mat);
    FREEMEM(mix_zone);
    FREEMEM(mix_next);
    FREEMEM(mix_vf);
  }
  *zdx_len = mixlen;
  return(0);
}
#endif
