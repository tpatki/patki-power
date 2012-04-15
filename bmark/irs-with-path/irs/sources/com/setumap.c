#include "irs.h"
#include "BlockMapping.h"
#include "BndMapping.h"
#include "Extents.h"
#include "FunctionTimer.h" 
#include "irscom.h"
void setumap(Domain_t *domain) {
   int i;
   Extents_t ext;
   umap[unblk].ublk = unblk;
   umap[unblk].lblk = -1;
   umap[unblk].gblk = -1;
   umap[unblk].imax = domain->imax;
   umap[unblk].jmax = domain->jmax;
   umap[unblk].kmax = domain->kmax;
   umap[unblk].imin = domain->imin;
   umap[unblk].jmin = domain->jmin;
   umap[unblk].kmin = domain->kmin;
   umap[unblk].jp   = domain->jp;
   umap[unblk].kp   = domain->kp;
   if (umap[unblk].nbnd < 0) {
      umap[unblk].bnd = ALLOT(BndMapping_t,nbndx);
      for (i = 0; i < nbndx; i++) {
         umap[unblk].bnd[i].ndx = NULL;
      }
      umap[unblk].nbnd = 0;
   }
   CPYEXT(ext,(*domain));
   domain->gblk =  gnblk;
   domain_hash_tbl_rgst(domain);
   setgmap(unblk,ext);
   unblk++;
}
