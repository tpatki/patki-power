#include <unistd.h>             
#include "irs.h"
#include "irsctl.h"
#include "irscom.h"
#include "irsdmp.h"
#include "BlockMapping.h"
#include "Hash.h"
#include "FunctionTimer.h"
int printmap (void)
{
  char *me = "printmap", msg[256];
  int   i;
  for (i=0; i<unblk; i++) {
    sprintf(msg,"%d:%d %s: umap[%3d].gblk=%3d .lblk=%3d .ublk=%3d",
      myid,getpid(),me,i,umap[i].gblk,umap[i].lblk,umap[i].ublk);
    ctlmsg(msg);
  }
  for (i=0; i<gnblk; i++) {
    sprintf(msg,"%d:%d %s: gmap[%3d].gblk=%3d .lblk=%3d .ublk=%3d proc=%3d",
      myid,getpid(),me,i,gmap[i].gblk,gmap[i].lblk,gmap[i].ublk,gmap[i].proc);
    ctlmsg(msg);
  }
  return(0);
}
