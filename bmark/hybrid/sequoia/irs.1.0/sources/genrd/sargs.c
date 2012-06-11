#include "irs.h"
#include "irsgenrd.h"
#include "Command.h"
int sargs(Command_t *cp )
{
  (*(cp->proc))(cp->arg);
  return(0);
}
