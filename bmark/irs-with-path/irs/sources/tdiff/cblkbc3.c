#include "irs.h"
#include "irstdiff.h"
#include "RadiationData.h"
void cblkbc3( RadiationData_t *cblk, Domain_t *domain )
{
   int i ;
   int ibc ;
   int len ;
   int dir ;
   int off ;
   int *ndx ;
   double *ccl ;
   double *ccc ;
   double *cch ;
   double *cll ;
   double *clc ;
   double *clh ;
   double *chl ;
   double *chc ;
   double *chh ;
   for ( ibc = 0 ; ibc < domain->nbc ; ibc++ )
   {
      len = domain->bc[ibc].len ;
      ndx = domain->bc[ibc].ndx ;
      dir = domain->bc[ibc].pn ;
      off = domain->bc[ibc].rz ;
      if (dir == -1)
      {
         cll = cblk->dbl + off ;
         clc = cblk->dcl + off ;
         clh = cblk->dfl + off ;
         ccl = cblk->cbl + off ;
         ccc = cblk->ccl + off ;
         cch = cblk->cbr + off + domain->jp - 1 ;
         chl = cblk->dfr + off + domain->kp - domain->jp - 1 ;
         chc = cblk->dcr + off + domain->kp - 1 ;
         chh = cblk->dbr + off + domain->kp + domain->jp - 1 ;
      }
      if (dir ==  1)
      {
         cll = cblk->dbr + off ;
         clc = cblk->dcr + off ;
         clh = cblk->dfr + off ;
         ccl = cblk->cbr + off ;
         ccc = cblk->ccl + off + 1 ;
         cch = cblk->cbl + off + domain->jp + 1 ;
         chl = cblk->dfl + off + domain->kp - domain->jp + 1 ;
         chc = cblk->dcl + off + domain->kp + 1 ;
         chh = cblk->dbl + off + domain->kp + domain->jp + 1 ;
      }
      if (dir == -domain->jp)
      {
         cll = cblk->dbl + off ;
         clc = cblk->dbc + off ;
         clh = cblk->dbr + off ;
         ccl = cblk->cbl + off ;
         ccc = cblk->cbc + off ;
         cch = cblk->cbr + off ;
         chl = cblk->dfr + off + domain->kp - domain->jp - 1 ;
         chc = cblk->dfc + off + domain->kp - domain->jp ;
         chh = cblk->dfl + off + domain->kp - domain->jp + 1 ;
      }
      if (dir ==  domain->jp)
      {
         cll = cblk->dfl + off ;
         clc = cblk->dfc + off ;
         clh = cblk->dfr + off ;
         ccl = cblk->cbr + off + domain->jp - 1 ;
         ccc = cblk->cbc + off + domain->jp ;
         cch = cblk->cbl + off + domain->jp + 1 ;
         chl = cblk->dbr + off + domain->kp + domain->jp - 1 ;
         chc = cblk->dbc + off + domain->kp + domain->jp ;
         chh = cblk->dbl + off + domain->kp + domain->jp + 1 ;
      }
      if (dir == -domain->kp)
      {
         cll = cblk->dbl + off ;
         clc = cblk->dbc + off ;
         clh = cblk->dbr + off ;
         ccl = cblk->dcl + off ;
         ccc = cblk->dcc + off ;
         cch = cblk->dcr + off ;
         chl = cblk->dfl + off ;
         chc = cblk->dfc + off ;
         chh = cblk->dfr + off ;
      }
      if (dir ==  domain->kp)
      {
         cll = cblk->dfr + off + domain->kp - domain->jp - 1 ;
         clc = cblk->dfc + off + domain->kp - domain->jp ;
         clh = cblk->dfl + off + domain->kp - domain->jp + 1 ;
         ccl = cblk->dcr + off + domain->kp - 1 ;
         ccc = cblk->dcc + off + domain->kp ;
         cch = cblk->dcl + off + domain->kp + 1 ;
         chl = cblk->dbr + off + domain->kp + domain->jp - 1 ;
         chc = cblk->dbc + off + domain->kp + domain->jp ;
         chh = cblk->dbl + off + domain->kp + domain->jp + 1 ;
      }
      for ( i = 0 ; i < len ; i++ )
      {
         cll[ndx[i]] = 0.0 ;
         clc[ndx[i]] = 0.0 ;
         clh[ndx[i]] = 0.0 ;
         ccl[ndx[i]] = 0.0 ;
         ccc[ndx[i]] = 0.0 ;
         cch[ndx[i]] = 0.0 ;
         chl[ndx[i]] = 0.0 ;
         chc[ndx[i]] = 0.0 ;
         chh[ndx[i]] = 0.0 ;
      }
   }
}
