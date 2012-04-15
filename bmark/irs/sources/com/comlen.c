#include "irs.h"
#include "Boundary.h"
#include "FunctionTimer.h"
#include "irscom.h"
int comlen( Boundary_t *bnd, int **ndx_in, int com_type, int mesg_type) {
   int len;
   int *ndx;
   if (mesg_type == COM_SEND) {
      switch(com_type) {
         case COM_LAYER1N:
            ndx = COM_NDX_1N_S((*bnd));
            len = COM_LEN_1N_S((*bnd));
            break;
         case COM_LAYER1Z:
            ndx = COM_ZDX_1Z_S((*bnd));
            len = COM_LEN_1Z_S((*bnd));
            break;
         case COM_LAYER1ZC:
            ndx = COM_ZDX_1ZC_S((*bnd));
            len = COM_LEN_1ZC_S((*bnd));
            break;
         case COM_LAYER2N:
            ndx = COM_NDX_2N_S((*bnd));
            len = COM_LEN_2N_S((*bnd));
            break;
         case COM_LAYER2NC:
            ndx = COM_NDX_2NC_S((*bnd));
            len = COM_LEN_2NC_S((*bnd));
            break;
         case COM_LAYER2Z:
            ndx = COM_ZDX_2Z_S((*bnd));
            len = COM_LEN_2Z_S((*bnd));
            break;
         case COM_LAYER_ALLN:
            ndx = COM_NDX_ALLN_S((*bnd));
            len = COM_LEN_ALLN_S((*bnd));
            break;
         case COM_LAYER_ALLZ:
            ndx = COM_ZDX_ALLZ_S((*bnd));
            len = COM_LEN_ALLZ_S((*bnd));
            break;
         case COM_LAYER_CZ:
            ndx = COM_ZDX_ZC_S((*bnd));
            len = COM_LEN_ZC_S((*bnd));
            break;
         case COM_LAYER_CN:
            ndx = COM_NDX_NC_S((*bnd));
            len = COM_LEN_NC_S((*bnd));
            break;
         case COM_ACCUM:
            ndx = COM_NDX_1N_S((*bnd));
            len = COM_LEN_1N_S((*bnd));
            break;
         case COM_DIRECT:
            len=0;
            break;
         default:
            len=0;
            break;
      }
   } else {
      switch(com_type) {
         case COM_LAYER1N:
            ndx = COM_NDX_1N_R((*bnd));
            len = COM_LEN_1N_R((*bnd));
            break;
         case COM_LAYER1Z:
            ndx = COM_ZDX_1Z_R((*bnd));
            len = COM_LEN_1Z_R((*bnd));
            break;
         case COM_LAYER1ZC:
            ndx = COM_ZDX_1ZC_R((*bnd));
            len = COM_LEN_1ZC_R((*bnd));
            break;
         case COM_LAYER2N:
            ndx = COM_NDX_2N_R((*bnd));
            len = COM_LEN_2N_R((*bnd));
            break;
         case COM_LAYER2NC:
            ndx = COM_NDX_2NC_R((*bnd));
            len = COM_LEN_2NC_R((*bnd));
            break;
         case COM_LAYER2Z:
            ndx = COM_ZDX_2Z_R((*bnd));
            len = COM_LEN_2Z_R((*bnd));
            break;
         case COM_LAYER_ALLN:
            ndx = COM_NDX_ALLN_R((*bnd));
            len = COM_LEN_ALLN_R((*bnd));
            break;
         case COM_LAYER_ALLZ:
            ndx = COM_ZDX_ALLZ_R((*bnd));
            len = COM_LEN_ALLZ_R((*bnd));
            break;
         case COM_LAYER_CZ:
            ndx = COM_ZDX_ZC_R((*bnd));
            len = COM_LEN_ZC_R((*bnd));
            break;
         case COM_LAYER_CN:
            ndx = COM_NDX_NC_R((*bnd));
            len = COM_LEN_NC_R((*bnd));
            break;
         case COM_ACCUM:
            ndx = COM_NDX_1N_R((*bnd));
            len = COM_LEN_1N_R((*bnd));
            break;
         case COM_DIRECT:
            len = 0;
            break;
         default:
            len = 0;
            break;
      }
   }
   ndx_in[0] = ndx;
   return(len);
}
