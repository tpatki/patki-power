#include <string.h>
#include "irs.h"
#include "irscom.h"
#include "irsrgst.h" 
#include "BlockMapping.h"
#include "Boundary.h"
#include "FunctionTimer.h" 
#include "ProblemArray.h"
#include "Rgst.h"
static char *ComNodalZonal_SetOrientation(RGST_AttributeElem_t *varList,
			     int targetOrientation);
static char *ComNodalZonal_MatchOrientation(RGST_AttributeElem_t *varList,
			       int targetOrientation, int
			       *bndOrientation); 
int ComNodalZonal(int stepflag, char kernel[], int comflag)
{ 
  int i,ibc,ibc_out ;
  int j, varNumber;
  int iblk_out,gblk,gblk_in;
  int len;
  int iblk;
  int error;
  int proc;
  int iorient ;
  int jorient ;
  int korient ;
  int *inzdx,*outzdx;
  int *inndx,*outndx;
  char suffix[5] ;
  char bufferName[50] ;
  Boundary_t *bnd, *bnd2 ;
  ProblemArray_t *prb;
  sprintf(suffix, "%d", (stepflag - RBNDCOM0));
  sprintf(bufferName, "%s", kernel);
  strcat(bufferName, suffix);
  len   = 0 ;
  error = 0 ;
  if ( !ifcom )  {
    return(error) ;
  }
  STARTTIMER( stepflag ) ;
  if ( ifparallel ) {
    curcombuf = stepflag ;
    if ( comflag == COM_RECV ) {
      initbuf( stepflag, COM_RECV ) ;
      postbuf( stepflag, COM_RECV ) ;
      STOPTIMER( stepflag, comflag ) ;
      return(error) ;
    } else if ( comflag == COM_SEND ) {
      initbuf( stepflag, COM_SEND ) ;
    } else if ( comflag == COM_WAIT_SEND ) {
      waitbuf( stepflag, COM_WAIT_SEND, COM_ALL ) ;
      freebuf( stepflag, COM_SEND ) ;
      STOPTIMER( stepflag, comflag ) ;
      return(error) ;
    } else if ( comflag == COM_WAIT_RECV ) {
      while ( (proc = waitbuf(stepflag,COM_WAIT_RECV,COM_ANY)) >= 0 ) {
	for ( i = 0 ; i < hydro_len_order[proc] ; i++ ) {
	  RGST_AttributeElem_t *varList = rgst_list_attr(A_OBJECT, bufferName) ;
	  ibc  = hydro_tag_order[proc][i] ;
	  gblk = hydro_blk_order[proc][i] ;
	  iblk = gmap[gblk].lblk ;
	  bnd  = domains[iblk].bnd ;
	  gblk_in = bnd[ibc].blk_send;
	  while (varList != NULL){
	    int comLayer;
	    char *varName = varList ->rgst_obj->name;
	    ProblemArray_t *problemArray = ProblemArray_find(varName, NULL);
	    RGST_Datatype_t varType = problemArray->type; 
	    if (rgst_query_attr(A_OBJECT, varName, "Zonal", NULL)) {
	      comLayer = COM_LAYER1ZC;
	    } else {
	      comLayer = COM_LAYER2NC;
	    }
	    if (varType == R_DOUBLE){
	      double *varValue = (double *) ProblemArray_ptr
		(varName, domains[iblk].hash);
	      getdata(varValue, len, COM_DOUBLE, gblk_in, &bnd[ibc], comLayer);
	    } else if (varType == R_INT){
	      int *varValue = (int *) ProblemArray_ptr
		(varName, domains[iblk].hash);
	      getdata(varValue, len, COM_INT, gblk_in, &bnd[ibc], comLayer);
	    }
	    varList = varList->next;
	  }	       
	}
	freebuf( stepflag, COM_RECV ) ;
      }
    }
  }
  for ( j = 0 ; j < hydro_len_order_send ; j++ ) {
    ibc  = hydro_tag_order[myid][j+hydro_len_order[myid]] ;
    gblk = hydro_blk_order[myid][j+hydro_len_order[myid]] ;
    iblk = gmap[gblk].lblk ;
    bnd  = domains[iblk].bnd ;
    gblk = bnd[ibc].blk_send ;
    proc = gmap[gblk].proc ;
    ibc_out = bnd[ibc].bndnbc ;
    if ( (proc != myid) && (comflag == COM_SEND) ) {
      int comLayer;
      RGST_AttributeElem_t *varList = rgst_list_attr (A_OBJECT, bufferName) ;
      RGST_AttributeElem_t *headList = varList;
      while (varList != NULL){
	char *varName = varList->rgst_obj->name;
	char *varName2 = varName;
	ProblemArray_t *problemArray = ProblemArray_find(varName, NULL);
	RGST_Datatype_t varType = problemArray->type; 
	if (rgst_query_attr(A_OBJECT, varName, "HasOrientation", NULL)) {
	  HashTable_t *hash = ProblemArray_GetHash(varName, NULL);
	  int *orient       = hash_lookup_obj("Orientation", hash);
	  int index         = abs(orient[0]) - 1;
	  int signOrient    = (index + 1) / orient[0] ;
	  int targetOrientation = signOrient * bnd[ibc].orientation[index];
	  varName2 = ComNodalZonal_SetOrientation(headList, targetOrientation);
	}
	if (rgst_query_attr(A_OBJECT, varName, "Zonal", NULL)) {
	  comLayer = COM_LAYER1ZC;
	} else {
	  comLayer = COM_LAYER2NC;
	}
	if (varType == R_DOUBLE){
	  double *varValue = (double *) ProblemArray_ptr
	    (varName2, domains[iblk].hash);
	  putdata(varValue, len, COM_DOUBLE, gblk, &bnd[ibc], comLayer);
	} else if (varType == R_INT){
	  int *varValue = (int *) ProblemArray_ptr
	    (varName2, domains[iblk].hash);
	  putdata(varValue, len, COM_INT, gblk, &bnd[ibc], comLayer);
	}
	varList = varList->next;
      }
    } else if ( (proc == myid) && (comflag == COM_SEND) ) {
      int *inIndex ;
      int *outIndex;
      RGST_AttributeElem_t *varList = rgst_list_attr
	(A_OBJECT, bufferName) ;
      RGST_AttributeElem_t *headList = varList;
      iblk_out = gmap[gblk].lblk ;
      bnd2     = domains[iblk_out].bnd ;
      inzdx  = bnd[ibc].zdx_recv ;
      outzdx = bnd2[ibc_out].zdx_send ;
      while (varList != NULL){
	char *varName = varList->rgst_obj->name;
	char *varName2 = varName;
	ProblemArray_t *problemArray = ProblemArray_find(varName, NULL);
	RGST_Datatype_t varType = problemArray->type; 
	if (rgst_query_attr(A_OBJECT, varName, "HasOrientation", NULL)) {
	  HashTable_t *hash = ProblemArray_GetHash(varName, NULL);
	  int *orient       = hash_lookup_obj("Orientation", hash);
	  int index         = abs(orient[0]) - 1;
	  int signOrient    = (index + 1) / orient[0] ;
	  int targetOrientation = signOrient *
	    bnd[ibc].orientation[index];
	  varName2 = ComNodalZonal_MatchOrientation(headList, orient[0],
					      bnd2[ibc_out].orientation);
	}
	if (rgst_query_attr(A_OBJECT, varName, "Zonal", NULL)) {
	  len  = COM_LEN_1ZC_R(bnd[ibc]) ;
	  inIndex  = COM_ZDX_1ZC_R(bnd[ibc]) ;
	  outIndex = COM_ZDX_1ZC_S(bnd2[ibc_out]) ;
	} else {
	  len = COM_LEN_2NC_R(bnd[ibc]) ;
	  inIndex  = COM_NDX_2NC_R(bnd[ibc]) ;
	  outIndex = COM_NDX_2NC_S(bnd2[ibc_out]) ;
	}
	if (varType == R_DOUBLE){
	  double *varValue = (double *) ProblemArray_ptr
	    (varName, domains[iblk].hash);
	  double *varValue2 = (double *) ProblemArray_ptr
	    (varName2, domains[iblk_out].hash);
	  for ( i = 0 ; i < len ; i++ ) {
	    varValue[inIndex[i]] = varValue2[outIndex[i]] ;
	  }
	} else if (varType == R_INT){
	  int *varValue = (int *) ProblemArray_ptr
	    (varName, domains[iblk].hash);
	  int *varValue2 = (int *) ProblemArray_ptr
	    (varName2, domains[iblk_out].hash);
	  for ( i = 0 ; i < len ; i++ ) {
	    varValue[inIndex[i]] = varValue2[outIndex[i]] ;
	  }
	}
	varList = varList->next;
      }
    } else if (( comflag == COM_SET_SIZE_DOUBLE ) ||
               ( comflag == COM_SET_SIZE_INT )) {
      RGST_AttributeElem_t *varList = rgst_list_attr
	(A_OBJECT, bufferName) ;
      while (varList != NULL){
	char *varName = ATTR_GET_OBJECT_NAME(varList);
	prb = ProblemArray_find(varName, NULL);
	if (rgst_query_attr(A_OBJECT, varName, "Zonal", NULL)) {
	  if ((comflag == COM_SET_SIZE_DOUBLE) && (prb->type == R_DOUBLE)) {
	     len_sendd[proc]  += COM_LEN_1ZC_S(bnd[ibc]) ;
	     len_recvd[proc]  += COM_LEN_1ZC_R(bnd[ibc]) ;
	  } else if ((comflag == COM_SET_SIZE_INT) && (prb->type == R_INT)) {
	     len_sendi[proc]  += COM_LEN_1ZC_S(bnd[ibc]) ;
	     len_recvi[proc]  += COM_LEN_1ZC_R(bnd[ibc]) ;
	  } 
	}
	if (rgst_query_attr(A_OBJECT, varName, "Nodal", NULL)) {
	  if ((comflag == COM_SET_SIZE_DOUBLE) && (prb->type == R_DOUBLE)) {
	     len_sendd[proc]  += COM_LEN_2NC_S(bnd[ibc]) ;
	     len_recvd[proc]  += COM_LEN_2NC_R(bnd[ibc]) ;
	  } else if ((comflag == COM_SET_SIZE_INT) && (prb->type == R_INT)) {
	     len_sendi[proc]  += COM_LEN_2NC_S(bnd[ibc]) ;
	     len_recvi[proc]  += COM_LEN_2NC_R(bnd[ibc]) ;
	  } 
	}
	varList = varList->next;
      }
    }
  }
  if ( (ifparallel) && (comflag == COM_SEND) ) {
    postbuf( stepflag, COM_SEND ) ;
  }
  STOPTIMER( stepflag, comflag ) ;
  return(error); 
}
static char *ComNodalZonal_SetOrientation(RGST_AttributeElem_t *varList,
			     int targetOrientation)
{
  while (varList != NULL){
    char *varName = ATTR_GET_OBJECT_NAME(varList);
    varList = varList->next;
    if (rgst_query_attr(A_OBJECT, varName, "HasOrientation", NULL)) {
      HashTable_t *hash = ProblemArray_GetHash(varName, NULL);
      if (hash != NULL){
	int *orientation = hash_lookup_obj("Orientation", hash);
	if (orientation[0] == targetOrientation) {
	  return varName;
	}
      }
    }
  }
  return " ";
}
static char *ComNodalZonal_MatchOrientation(RGST_AttributeElem_t *varList,
			       int targetOrientation, int *bndOrientation)
{
  while (varList != NULL){
    char *varName = ATTR_GET_OBJECT_NAME(varList);
    varList = varList->next;
    if (rgst_query_attr(A_OBJECT, varName, "HasOrientation", NULL)) {
      HashTable_t *hash = ProblemArray_GetHash(varName, NULL);
      if (hash != NULL){
	int *orientation = hash_lookup_obj("Orientation", hash);
	int index = abs(orientation[0]) - 1;
	int signOrient = (index + 1) / orientation[0];
	int mapOrient  = signOrient * bndOrientation[index];
	if (mapOrient == targetOrientation) {
	  return varName;
	}
      }
    }
  }
  return " ";
}
