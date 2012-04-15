#include "irs.h"
#include "irsedits.h"
#include "FreqMesg.h"
void printtimefreq (FreqMesg_t *fq)
{
  int i;
  if (myid != 0) { return; }
  if (fq == NULL) { return; }
  printf("\n PRINT OF TIME FREQUENCY '%s'\n",fq->name);
  printf("  name                     = %s\n",fq->name);
  printf("  time start               = %-10.5f\n",fq->t1);
  printf("  time stop                = %-10.5f\n",fq->t2);
  printf("  time step                = %-10.5f\n",fq->dt);
  printf("  next time for edit       = %-10.5f\n",fq->nextTime);
  printf("  msg = '%s'\n",fq->msg);
}
