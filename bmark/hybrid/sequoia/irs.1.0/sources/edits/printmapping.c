#include "irs.h"
#include "irsedits.h"
#include "BlockMapping.hh"
void printmapping(BlockMapping_t *map)
{
  if (myid != 0) { return; }
  if (map == NULL) { return; }
  printf("  map.gblk = %d\n",map->gblk);
  printf("  map.lblk = %d\n",map->lblk);
  printf("  map.ublk = %d\n",map->ublk);
  printf("  map.imax = %d\n",map->imax);
  printf("  map.jmax = %d\n",map->jmax);
  printf("  map.kmax = %d\n",map->kmax);
  printf("  map.imin = %d\n",map->imin);
  printf("  map.jmin = %d\n",map->jmin);
  printf("  map.kmin = %d\n",map->kmin);
  printf("  map.jp   = %d\n",map->jp);
  printf("  map.kp   = %d\n",map->kp);
  printf("  map.nbnd = %d\n",map->nbnd);
}
