#include <math.h>
#include "irs.h"
#include "irstdiff.h"
static void Dscal(double *array, double scale, int len);
static int  Idamax(double *array, int len);
static void Daxpy(double *vector1, double *vector2, double scale, int len);
static void Dswap(double *vector1, double *vector2, int len);
static int Idamax(double *array, int len)
{
  int i;
  int index = 0;
  double large = fabs(array[0]);
  for (i = 1 ; i < len ; i++){
    double trial = fabs(array[i]);
    if (large < trial){
      large = trial;
      index = i;
    }
  }
  return index;
}
static void Dscal(double *array, double scale, int len)
{
  int i;
  for (i = 0 ; i < len ; i++){
    array[i] *= scale;
  }
}
static void Daxpy(double *vector1, double *vector2, double scale, int len)
{
  int i;
  for (i = 0 ; i < len ; i++){
    vector2[i] += scale * vector1[i];
  }
}
static void Dswap(double *vector1, double *vector2, int len)
{
  int i;
  for (i = 0 ; i < len ; i++){
    double temp1 = vector1[i];
    double temp2 = vector2[i];
    vector1[i] = temp2;
    vector2[i] = temp1;
  }
}
int  Dgefa(double *matrix, int *pivot, int len)
{
  int j, k;
  int error = 0;
  double scale;
  for (k = 0 ; k < len-1 ; k++){
    int index = k * len + k;
    int kp1 = k + 1;
    int l = Idamax(&matrix[index], len-k) + k;
    pivot[k] = l;
    if (matrix[l+k*len] == 0.0){
      error = k;
    }
    if ( l != k){
      double temp1 = matrix[l+k*len];
      double temp2 = matrix[index];
      matrix[index] = temp1;
      matrix[l+k*len] = temp2;
    }
    scale = -1. / matrix[index];
    Dscal(&matrix[k*len+k+1], scale, len-k-1);
    for (j = k+1 ; j < len ; j++){
      double temp1 = matrix[j*len+ l];
      double temp2 = matrix[j*len+ k];
      matrix[j*len+k] = temp1;
      matrix[j*len+l] = temp2;
      Daxpy(&matrix[k*len+k+1], &matrix[j*len+k+1], temp1, len-k-1);
    }
    pivot[len-1] = len-1;
  }
  if (matrix[len*len-1] == 0.0){
    error = len-1;
  }
  return error;
}
void Dgedi(double *matrix, int *pivot, double *work, int len)
{
  int i, j, k, l;
  double scale;
  for (k = 0 ; k < len ; k++){
    scale = matrix[k*len+k];
    scale = 1./scale;
    matrix[k*len+k] = scale;
    scale *= -1.;
    Dscal(&matrix[k*len], scale, k);
    for (j = k+1 ; j < len ; j++){
      scale = matrix[k + j*len];
      matrix[k + j*len] = 0.0;
      Daxpy(&matrix[k*len], &matrix[j*len], scale, k+1);
    }
  }    
  for (j = 0 ; j < len-1; j++){
    k = len - j - 2;
    for (i = k+1 ; i < len ; i++){
      work[i] = matrix[i + k*len];
      matrix[i + k*len] = 0.0;
    }
    for (i = k+1 ; i < len ; i++){
      scale = work[i];
      Daxpy(&matrix[i*len], &matrix[k*len], scale, len);
    }
    l = pivot[k];
    if (l != k){
      Dswap(&matrix[k*len], &matrix[l*len], len);
    }
  }
}
