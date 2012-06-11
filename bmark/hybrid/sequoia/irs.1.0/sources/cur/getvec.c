#include "irs.h"
#include "irsrgst.h"
#include "irscur.h"
#include "cgl.h"
#include "Hash.h"
#include "ProblemArray.h"
#include "Rgst.h"
#include "VectorStruct.h"
int getvec(
  VectorStruct_t *vecstr, 	
  int      labflag,	
  int      allocflag)	
{
  char *me = "getvec";
  char pname[MAXWORD], msg[128];
  ProblemArray_t   *prb;
  RGST_Datatype_t datatype;
  geta(pname) ;
  vecstr->namevec = strsave(pname);
  strcpy(vecstr->namelab,pname) ;
  prb = ProblemArray_find(pname, NULL);
  if (prb != NULL) {
     if (prb->type == R_DOUBLE) {
        vecstr->type = FLOAT;
	if (prb->ptr != NULL) {
           vecstr->floc = (double *)prb->ptr;
	} else {
           vecstr->floc = (double *)ProblemArray_ptr(pname, domains[blknum].hash);
	} 
     } else if (prb->type == R_DOUBLE) {
        vecstr->type = INT;
	if (prb->ptr != NULL) {
           vecstr->iloc = (int *)prb->ptr;
	} else {
           vecstr->iloc = (int *)ProblemArray_ptr(pname, domains[blknum].hash);
	} 
     } 
     getvec1(vecstr,labflag);
     return(0);
  }
  if (RGST_QUERY_OBJECT_ATTR(pname, "int_parm") == TRUE) {
    vecstr->palen = 1;
    vecstr->type  = INT;
    vecstr->iloc  = (int *)rgst_get(pname);
    if (allocflag == 1) {
      vecstr->ipa    = ALLOT(int,1) ;
      vecstr->ipa[0] = vecstr->iloc[0] ;
    }
    return(0);
  }
  if (RGST_QUERY_OBJECT_ATTR(pname, "double_parm") == TRUE) {
    vecstr->palen = 1;
    vecstr->type  = FLOAT;
    vecstr->floc  = (double *)rgst_get(pname);
    if (allocflag == 1) {
      vecstr->fpa    = ALLOT(double,1) ;
      vecstr->fpa[0] = vecstr->floc[0] ;
    }
    return(0);
  }
  if (RGST_QUERY_OBJECT_ATTR(pname, "char_parm") == TRUE) {
    sprintf(msg,"Can't plot CHAR parm '%s'",pname);
    ctlwarning(me,msg);
    return(1);
  }
  sprintf(msg,"Do not know how to process getvec for var '%s'",pname);
  ctlwarning(me,msg);
  return(1);	
}
