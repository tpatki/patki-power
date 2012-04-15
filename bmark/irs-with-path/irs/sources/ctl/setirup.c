#include <signal.h>
#include "irs.h"
void setirup( int i ) {
  printf ("WARNING:  %s no longer stops after seeing a Control-C\n",codename);
  printf ("          If you want to stop the code and get the prompt, type \"stop\".\n");
  printf ("          Type \"c\", \"t\", \"cycle\", or \"time\" for report of current time\n");
  printf ("          and cycle without stoping the run, or \"?\" or \"h\" for more help.\n");
  signal(SIGINT,setirup) ;
}
