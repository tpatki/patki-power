#include "irs.h"
#include "irsedits.h"
#include "CycleMesg.h"
void printcyclefreq (CycleMesg_t *fq)
{
  int i;
  if (myid != 0) { return; }
  if (fq == NULL) return;
  printf("\n PRINT OF CYCLE FREQUENCY '%s'\n",fq->name);
  printf("  name                     = %s\n",fq->name);
  printf("  cycle start               = %d\n",fq->c1);
  printf("  cycle stop                = %d\n",fq->c2);
  printf("  cycle step                = %d\n",fq->dc);
  printf("  next cycle for edit       = %d\n",fq->nextCycle);
  printf("  msg = '%s'\n",fq->msg);
}
