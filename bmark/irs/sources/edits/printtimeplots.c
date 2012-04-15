#include "irs.h"
#include "irsedits.h"
#include "Hash.h"
int printtimeplots(void) { 
  if (myid != 0) { return(0); }
  hash_print_structs_of_type(gv_hash_tbl,"time_plot");
  return(0);
}
