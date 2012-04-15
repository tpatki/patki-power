#include "irs.h"
#include "irstdiff.h"
#include "RadiationData.h"
void cblkbc2( RadiationData_t *cblk, Domain_t *domain )
{
   int i ;
   int ibc ;
   int len ;
   int dir ;
   int off ;
   int *ndx ;
   double *cl ;
   double *cc ;
   double *ch ;
   for ( ibc = 0 ; ibc < domain->nbc ; ibc++ )
   {
      len = domain->bc[ibc].len ;
      ndx = domain->bc[ibc].ndx ;
      dir = domain->bc[ibc].pn ;
      off = domain->bc[ibc].rz ;
      if (dir == -1)
      {
         cl = cblk->cbl + off ;
         cc = cblk->ccl + off ;
         ch = cblk->cbr + off + domain->jp - 1 ;
      }
      if (dir ==  1)
      {
         cl = cblk->cbr + off ;
         cc = cblk->ccl + off + 1 ;
         ch = cblk->cbl + off + domain->jp + 1 ;
      }
      if (dir == -domain->jp)
      {
         cl = cblk->cbl + off ;
         cc = cblk->cbc + off ;
         ch = cblk->cbr + off ;
      }
      if (dir ==  domain->jp)
      {
         cl = cblk->cbr + off + domain->jp - 1 ;
         cc = cblk->cbc + off + domain->jp ;
         ch = cblk->cbl + off + domain->jp + 1 ;
      }
      for ( i = 0 ; i < len ; i++ )
      {
         cc[ndx[i]] = 0.0 ;
         cl[ndx[i]] = 0.0 ;
         ch[ndx[i]] = 0.0 ;
      }
   }
}
