#include "irsdefs.h"
#include "irs.h"
#include "irstdiff.h"
#include "irs.h"
#include "RadiationData.h"
RadiationData_t newMatrix(int size, int dimensionality, int jp, int kp)
{
  int i;
  RadiationData_t matrix ;
  matrix.cbl = MALLOT(double, size) ;
  matrix.cbc = MALLOT(double, size) ;
  matrix.cbr = MALLOT(double, size) ;
  matrix.ccl = MALLOT(double, size) ;
  matrix.ccc = MALLOT(double, size) ;
  matrix.ccr = matrix.ccl + 1 ;
  matrix.cfl = matrix.cbr + jp - 1 ;   
  matrix.cfc = matrix.cbc + jp ;   
  matrix.cfr = matrix.cbl + jp + 1 ;   
  matrix.dbl = NULL;
  matrix.dbc = NULL;
  matrix.dbr = NULL;
  matrix.dcl = NULL;
  matrix.dcc = NULL;
  matrix.dcr = NULL;
  matrix.dfl = NULL;
  matrix.dfc = NULL;
  matrix.dfr = NULL;
  matrix.ubl = NULL;
  matrix.ubc = NULL;
  matrix.ubr = NULL;
  matrix.ucl = NULL;
  matrix.ucc = NULL;
  matrix.ucr = NULL;
  matrix.ufl = NULL;
  matrix.ufc = NULL;
  matrix.ufr = NULL;
  for (i = 0 ; i < size ; i++){
    matrix.cbl[i] = 0.0;
    matrix.cbc[i] = 0.0;
    matrix.cbr[i] = 0.0;
    matrix.ccl[i] = 0.0;
    matrix.ccc[i] = 0.0;
  }
  if (dimensionality == 3) {
    matrix.dbl = MALLOT(double, size) ;
    matrix.dbc = MALLOT(double, size) ;
    matrix.dbr = MALLOT(double, size) ;
    matrix.dcl = MALLOT(double, size) ;
    matrix.dcc = MALLOT(double, size) ;
    matrix.dcr = MALLOT(double, size) ;
    matrix.dfl = MALLOT(double, size) ;
    matrix.dfc = MALLOT(double, size) ;
    matrix.dfr = MALLOT(double, size) ;
    matrix.ubl = matrix.dfr + kp - jp - 1 ;
    matrix.ubc = matrix.dfc + kp - jp ;
    matrix.ubr = matrix.dfl + kp - jp + 1 ;
    matrix.ucl = matrix.dcr + kp - 1 ;
    matrix.ucc = matrix.dcc + kp ;
    matrix.ucr = matrix.dcl + kp + 1 ;
    matrix.ufl = matrix.dbr + kp + jp - 1 ;
    matrix.ufc = matrix.dbc + kp + jp ;
    matrix.ufr = matrix.dbl + kp + jp + 1 ;
    for (i = 0 ; i < size ; i++){
      matrix.dbl[i] = 0.0 ;
      matrix.dbc[i] = 0.0 ;
      matrix.dbr[i] = 0.0 ;
      matrix.dcl[i] = 0.0 ;
      matrix.dcc[i] = 0.0 ;
      matrix.dcr[i] = 0.0 ;
      matrix.dfl[i] = 0.0 ;
      matrix.dfc[i] = 0.0 ;
      matrix.dfr[i] = 0.0 ;
    }
  }
  return matrix;
}
#include "irs.h"
void freeMatrix(RadiationData_t *matrix, int dimensionality)
{
  FREEMEM(matrix->cbl);
  FREEMEM(matrix->cbc);
  FREEMEM(matrix->cbr);
  FREEMEM(matrix->ccl);
  FREEMEM(matrix->ccc);
  matrix->ccr = NULL;
  matrix->cfl = NULL;
  matrix->cfc = NULL;
  matrix->cfr = NULL;
  if (dimensionality == 3) {
    FREEMEM(matrix->dbl);
    FREEMEM(matrix->dbc);
    FREEMEM(matrix->dbr);
    FREEMEM(matrix->dcl);
    FREEMEM(matrix->dcc);
    FREEMEM(matrix->dcr);
    FREEMEM(matrix->dfl);
    FREEMEM(matrix->dfc);
    FREEMEM(matrix->dfr);
    matrix->ubl = NULL;
    matrix->ubc = NULL;
    matrix->ubr = NULL;
    matrix->ucl = NULL;
    matrix->ucc = NULL;
    matrix->ucr = NULL;
    matrix->ufl = NULL;
    matrix->ufc = NULL;
    matrix->ufr = NULL;
  }
}
void CopyMatrix(RadiationData_t *copyMatrix,
		RadiationData_t *originalMatrix,
		int size, int dimensionality)
{
  int i;
  for (i = 0 ; i < size ; i++){
    copyMatrix->cbl[i] = originalMatrix->cbl[i];
    copyMatrix->cbc[i] = originalMatrix->cbc[i];
    copyMatrix->cbr[i] = originalMatrix->cbr[i];
    copyMatrix->ccl[i] = originalMatrix->ccl[i];
    copyMatrix->ccc[i] = originalMatrix->ccc[i];
  }
  if (dimensionality == 3) {
    for (i = 0 ; i < size ; i++){
      copyMatrix->dbl[i] = originalMatrix->dbl[i];
      copyMatrix->dbc[i] = originalMatrix->dbc[i];
      copyMatrix->dbr[i] = originalMatrix->dbr[i];
      copyMatrix->dcl[i] = originalMatrix->dcl[i];
      copyMatrix->dcc[i] = originalMatrix->dcc[i];
      copyMatrix->dcr[i] = originalMatrix->dcr[i];
      copyMatrix->dfl[i] = originalMatrix->dfl[i];
      copyMatrix->dfc[i] = originalMatrix->dfc[i];
      copyMatrix->dfr[i] = originalMatrix->dfr[i];
    }
  }
}
