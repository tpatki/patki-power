#include "irs.h"
#include "irsbndry.h"
static int MatchTwoNodes(int node1, int node2, int *NodeList, int len);
void bndzonelist(Domain_t *domain ) {
   int i, ibc, j, len;
   int stride, allFound, node1, node2, node3, node4;
   int *zonelist, *ndx;
   int lenNdx;
   int node1Offset ;
   int node2Offset ;
   int node3Offset ;
   int node4Offset ;
   int jp = domain->jp;
   int kp = domain->kp;
   int numPhonyZones = domain->phozlen;
   int *boundaryZone = domain->bndzdx;
   for (ibc = 0 ; ibc < domain->nbc ; ibc++){
     len = 0;
     zonelist = MALLOT(int, numPhonyZones);
     stride = domain->bc[ibc].pn;
     ndx    = domain->bc[ibc].ndx;
     lenNdx = domain->bc[ibc].len;
     if (stride == -1){ 
       node1Offset = 0;
       node2Offset = jp;
       node3Offset = kp;
       node4Offset = jp + kp;
     } else if (stride == 1){ 
       node1Offset = 1;
       node2Offset = jp + 1 ;
       node3Offset = kp + 1;
       node4Offset = jp + kp + 1;
     } else if (stride == -jp){
       node1Offset = 0;
       node2Offset = 1;
       node3Offset = kp;
       node4Offset = 1 + kp;
     } else if (stride == jp){  
       node1Offset = jp;
       node2Offset = 1 + jp;
       node3Offset = kp + jp;
       node4Offset = 1 + jp + kp;
     } else if (stride == -kp){ 
       node1Offset = 0;
       node2Offset = jp;
       node3Offset = 1;
       node4Offset = jp + 1; 
     } else if (stride == kp){  
       node1Offset = kp;
       node2Offset = jp + kp ;
       node3Offset = 1 + kp;
       node4Offset = 1 + jp + kp;
     }
     if (ndims == 3){
       for (i = 0 ; i < numPhonyZones ; i++){
	 int zone = boundaryZone[i];
	 node1 = zone + node1Offset;
	 node2 = zone + node2Offset;
	 node3 = zone + node3Offset;
	 node4 = zone + node4Offset;
	 allFound = MatchFourNodes(node1, node2, node3, node4,
				   ndx, lenNdx);
	 if (allFound == 1){
	   for (j = 0 ; j < len ; j++){
	     if (zone == zonelist[j]){
	       break;
	     }
	   } 
	   if (j == len){
	     zonelist[len] = zone;
	     len++;
	   }
	 }
       }
     } else {
       for (i = 0 ; i < numPhonyZones ; i++){
	 int zone = boundaryZone[i];
	 node1 = zone + node1Offset;
	 node2 = zone + node2Offset;
	 node3 = zone + node3Offset;
	 node4 = zone + node4Offset;
	 allFound = MatchTwoNodes(node1, node2, ndx, lenNdx);
	 if (allFound == 1){
	   for (j = 0 ; j < len ; j++){
	     if (zone == zonelist[j]){
	       break;
	     }
	   } 
	   if (j == len){
	     zonelist[len] = zone;
	     len++;
	   }
	 }
       }
     } 
     domain->bc[ibc].lenZonelist = len;
     domain->bc[ibc].zonelist = REALLOT(zonelist, int, len);
   }
}
int MatchFourNodes(int node1, int node2, int node3, int node4,
		   int *NodeList, int len){
  int i;
  int count = 0;
  for (i = 0 ; i < len ; i++){
    int node = NodeList[i];
    if (node == node1){
      count++;
    } else if (node == node2){
      count++;
    } else if (node == node3){
      count++;
    } else if (node == node4){
      count++;
    }
    if (count == 4){
      return 1;
    }
  }
  return 0;
}
static int MatchTwoNodes(int node1, int node2, int *NodeList, int len){
  int i;
  int count = 0;
  for (i = 0 ; i < len ; i++){
    int node = NodeList[i];
    if (node == node1){
      count++;
    } else if (node == node2){
      count++;
    } 
    if (count == 2){
      return 1;
    }
  }
  return 0;
}
