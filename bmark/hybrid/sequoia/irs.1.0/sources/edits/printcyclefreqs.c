#include "irs.h"
#include "irsedits.h"
#include "Hash.h"
int printcyclefreqs(void) { 
  if (myid != 0) { return(0); }
  hash_print_structs_of_type(gv_hash_tbl,"cycle_freq");
  return(0);
}
