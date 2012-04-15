#include "irs.h"
#include "irsedits.h"
#include "Hash.h"
int print(void) { 
  if (myid != 0) { return(0); }
  printf("\nYou may print the following items from the command line\n");
  printf("\tpm     or printmap          - Print the block mapping\n");
  printf("\tptc    or printtc           - Print time and cycle info\n");
  printf("\tptsc   or printtsc          - Print time step control info\n");
  printf("\tptf    or printtimefreqs    - Print all time frequency data structuers\n");
  printf("\tpcf    or printcyclefreqs   - Print all cycle frequency data structures\n");
  printf("\tptpc   or printtpcurves     - Print all time plot curve data structures\n");
  printf("\tptp    or printtimeplots    - Print all time plot data structures\n");
  printf("\tpe     or printedits        - Print all edit data structures\n");
  printf("\tptr    or printtracer       - Print tracer coordinates\n");
  printf("\tpnl    or printnodelist     - Print node list\n");
  printf("\tpul .. or printuserlist ..  - Print user list\n");
  printf("\tph  .. or printhash ..      - Print and analyze hash tables\n");
  printf("\t                                Type 'ph help' for usage info\n");
  printf("\tpr  .. or printrgst ..      - Print objects and types in the registry\n");
  printf("\t                                Type 'pr help' for usage info\n");
  printf("\tpa  .. or printattr ..      - Print attributes of an object or typedef (including fields) \n");
  printf("\tpal .. or printattrlist ..  - Print all items that have the given attribute\n");
  printf("\tpsp .. or printspline ..    - Print spline interpolations\n");
  printf("\tppr .. or printprobes ..    - Print probe info\n");
  printf("\nOther useful information available from the command line\n");
  printf("\th ..   or help ..           - Basic information about common commands\n");
  printf("\n");
  return(0);
}
