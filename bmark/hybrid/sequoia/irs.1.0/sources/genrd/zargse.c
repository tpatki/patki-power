#include "irs.h"
#include "irsgenrd.h"
#include "Command.h"
int zargse(Command_t *cp )
{
  error += (*(cp->proc))();
  return(0);
}
