#include "irs.h"
#include "irsgenrd.h"
#include "Command.h"
int  zargs(Command_t *cp)
{
  return((*(cp->proc))());
}
