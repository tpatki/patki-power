#include "irs.h"
#include "irsbndry.h"
void getbcname( char* op, int ibc, Domain_t *domain )
{
   if (domain->bc[ibc].type==FIXED) {
      strcpy(op,"fixed");
   } else if (domain->bc[ibc].type==FREE) {
      strcpy(op,"free");
   } else if (domain->bc[ibc].type==OPEN) {
      strcpy(op,"open");
   } else if (domain->bc[ibc].type==XVCNST) {
      strcpy(op,"xvcnst");
   } else if (domain->bc[ibc].type==YVCNST) {
      strcpy(op,"yvcnst");
   } else if (domain->bc[ibc].type==ZVCNST) {
      strcpy(op,"zvcnst");
   } else if (domain->bc[ibc].type==WALL) {
      strcpy(op,"wall");
   } else if (domain->bc[ibc].type==PLANE) {
      strcpy(op,"plane");
   } else if (domain->bc[ibc].type==CYLINDER) {
      if (domain->bc[ibc].nz==0.0) {
         strcpy(op,"z-cylinder");
      } else  if (domain->bc[ibc].ny==0.0) {
         strcpy(op,"y-cylinder");
      } else  if (domain->bc[ibc].nx==0.0) {
         strcpy(op,"x-cylinder");
      }
   } else if (domain->bc[ibc].type==SPHERE) {
      strcpy(op,"sphere");
   } else if (domain->bc[ibc].type==CONE) {
      strcpy(op,"cone");
   } else if (domain->bc[ibc].type==LINE) {
      strcpy(op,"line");
   } else {
      strcpy(op,"unknown");
   }
}
