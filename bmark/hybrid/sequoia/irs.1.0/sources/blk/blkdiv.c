#include <unistd.h>		
#include "irs.h"
#include "irsgen.h"
#include "irsblk.h"
#include "irsreg.h"
#include "BlockMapping.h"
#include "Extents.h"
int blkdiv(void) {
   int    ip, iblk, gblk, ublk, base, i, j, k, count, error;
   int    nnalls, num_blks, imax, jmax, kmax ;
   int   *blk;
   double scl;
   double dummy;
   Extents_t ext_tmp;
   Extents_t ext;
   Domain_t *domain_tmp;
   error=0;
   blk = ALLOT(int,nblkx);
   base = unblk;
   for (ublk=0;ublk<unblk;ublk++) {
      num_blks = 0;
      for (gblk=0;gblk<gnblk;gblk++) {
         if (gmap[gblk].ublk == ublk) {
            blk[num_blks] = gblk;
            num_blks++;
         }
      }
      if (num_blks == 1) {
         for (gblk=0;gblk<gnblk;gblk++) {
            if (gmap[gblk].ublk == ublk) {
               domains[ublk].gblk = gblk;
               domain_hash_tbl_rgst(&(domains[ublk]));
            }
         }
         continue;
      }
      domain_tmp = Domain_construct(num_blks);
      for (iblk = 0; iblk < num_blks; iblk++) {
         gblk = blk[iblk];
         imax = gmap[gblk].imax-gmap[gblk].imin+1;
         jmax = gmap[gblk].jmax-gmap[gblk].jmin+1;
         kmax = gmap[gblk].kmax-gmap[gblk].kmin+1;
         count  = 0;
         TRSEXT(ext,gmap[gblk],gmap[gblk]);
         if (ndims == 2) {
            for (j = ext.jmin; j < ext.jmax; j++) {
               for (i = ext.imin; i < ext.imax; i++) {
                  ip = i + j*domains[ublk].jp; 
                  if (domains[ublk].ireg[ip]<0) {
                     count += nreg;
                  }
               }
            }
            nnalls=(imax+NPNR+1)*(jmax+NPNR+1);
         } else {
            for (k = ext.kmin; k < ext.kmax; k++) {
               for (j = ext.jmin; j < ext.jmax; j++) {
                  for (i = ext.imin; i < ext.imax; i++) {
                     ip = i + j*domains[ublk].jp + k*domains[ublk].kp;
                     if (domains[ublk].ireg[ip]<0) {
                        count += nreg;
                     }
                  }
               }
            }
            nnalls=(imax+NPNR+1)*(jmax+NPNR+1)*(kmax+NPNR+1);
         }
         if (ndims == 2) {
            scl = MAX(2*( (double)count/(double)nnalls ),2*domains[ublk].sclnamix);
         } else {
            scl = MAX(2*( (double)count/(double)nnalls ),3*domains[ublk].sclnamix);
         } 
         domain_tmp[iblk].type     = domains[ublk].type;
         domain_tmp[iblk].sclnamix = scl;
         domain_allot(&domain_tmp[iblk],imax,jmax,kmax);
         CPYEXT(ext_tmp,domain_tmp[iblk]);
         CPYEXT(ext,gmap[gblk]);
         domaincopy(&domains[ublk],&ext,&domain_tmp[iblk],&ext_tmp);
      }
      domain_free(&domains[ublk]);
      domains[ublk]      = domain_tmp[0];
      domains[ublk].gblk = blk[0];
      domain_hash_tbl_rgst(&(domains[ublk]));
      gmap[blk[0]].lblk  = ublk;
      domain_setpa(&domains[ublk]);
        for (iblk = 0; iblk < num_blks-1; iblk++) {
         domains[base+iblk] = domain_tmp[iblk+1];
         domains[base+iblk].gblk = blk[iblk+1];
	 domain_hash_tbl_rgst(&(domains[base+iblk]));
         gmap[blk[iblk+1]].lblk  = base + iblk;
         domain_setpa(&domains[base+iblk]);
        }      
      base += (num_blks - 1);
   }  
   nblk = gnblk;
   FREEMEM(blk);
   return(error) ;
}
