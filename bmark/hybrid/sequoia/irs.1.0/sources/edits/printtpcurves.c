#include "irs.h"
#include "irsedits.h"
#include "Hash.h"
#include "TimePlot.h"
int printtpcurves(void) { 
  hash_print_structs_of_type(gv_hash_tbl,"tp_curve");
  return(0);
}
