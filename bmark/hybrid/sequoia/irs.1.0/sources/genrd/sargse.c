#include "irs.h"
#include "irsgenrd.h"
#include "Command.h"
int sargse(Command_t *cp )
{
  error = (*(cp->proc))(cp->arg);
  return(0);
}
