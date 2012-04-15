#include <math.h>
#include "irs.h"
#include "irsreg.h"
#include "irstdiff.h"
#include "FunctionTimer.h"
static void SetFaceTemperature_WainwrightAverage
                 (Domain_t *domain,
                  double *zoneCenteredT1, double *zoneCenteredT2,
		  double *faceCenteredT1, double *faceCenteredT2,
		  int firstFace, int lastFace);
static void SetFaceTemperature_TiptonAverage
                 (Domain_t *domain,
                  double *zoneCenteredT1, double *zoneCenteredT2,
		  double *faceCenteredT1, double *faceCenteredT2,
		  double *volume1       , double *volume2,
		  int firstFace, int lastFace);
void SetFaceTemperature_Driver
                 (Domain_t *domain, double *volume, double *tCenter,
		  double *tUp,      double *tDown,  double *tLeft,
		  double *tRight,   double *tFront, double *tBack)
{
  char *me = "SetFaceTemperature_Driver";
  int i;
  int firstFace  = domain->frn;
  int lastFace   = domain->lrn;
  int firstZone  = domain->frz;
  int lastZone   = domain->lrz;
  int iStride    = 1;
  int jStride    = domain->jp;
  int kStride    = domain->kp;
  int numMixZone = domain->nmixzn;
  double myflops = 0.0;
  FT_INITIALIZE(me, domain->hash)
  if (wainwright == 1){
    SetFaceTemperature_WainwrightAverage
      (domain, tCenter, (tCenter - iStride), tLeft, (tRight - iStride),
       firstFace, lastFace);
    SetFaceTemperature_WainwrightAverage
      (domain, tCenter, (tCenter - jStride), tBack, (tFront - jStride),
       firstFace, lastFace);
    if (ndims == 3){
      SetFaceTemperature_WainwrightAverage
	(domain, tCenter, (tCenter - kStride), tDown, (tUp - kStride),
	 firstFace, lastFace);
    }
  } else {
    SetFaceTemperature_TiptonAverage
      (domain, tCenter, (tCenter - iStride), tLeft, (tRight - iStride),
       volume, (volume - iStride), firstFace, lastFace);
    SetFaceTemperature_TiptonAverage
      (domain, tCenter, (tCenter - jStride), tBack, (tFront - jStride),
       volume, (volume - jStride), firstFace, lastFace);
    if (ndims == 3){
      SetFaceTemperature_TiptonAverage
	(domain, tCenter, (tCenter - kStride), tDown, (tUp - kStride),
	 volume, (volume - kStride), firstFace, lastFace);
    }
  }
  if (ndims == 2){
    for (i = firstZone ; i <= lastZone ; i++){
      double phiAve = 0.25 * 
	( (tLeft[i]*tLeft[i])   *   (tLeft[i]*tLeft[i])   +
	  (tRight[i]*tRight[i]) *   (tRight[i]*tRight[i]) +
	  (tFront[i]*tFront[i]) *   (tFront[i]*tFront[i]) +
	  (tBack[i]*tBack[i])   *   (tBack[i]*tBack[i])   );
      double tAve = sqrt(sqrt(phiAve));
      tCenter[i]  = MAX(tAve, tfloor);
    }
    myflops += 20 * (lastZone + 1 - firstZone);
  } else {
    double sixth = 1.0 / 6.0;
    for (i = firstZone ; i <= lastZone ; i++){
      double phiAve = sixth * 
	( (tLeft[i]*tLeft[i])   *   (tLeft[i]*tLeft[i])   +
	  (tRight[i]*tRight[i]) *   (tRight[i]*tRight[i]) +
	  (tFront[i]*tFront[i]) *   (tFront[i]*tFront[i]) +
	  (tBack[i]*tBack[i])   *   (tBack[i]*tBack[i])   +
	  (tUp[i]*tUp[i])       *   (tUp[i]*tUp[i])       +
	  (tDown[i]*tDown[i])   *   (tDown[i]*tDown[i])   );
      double tAve = sqrt(sqrt(phiAve));
      tCenter[i]  = MAX(tAve, tfloor);
    }
    myflops += 20 * (lastZone + 1 - firstZone);
  }
  if (numMixZone > 0){
    int ir;
    for (ir = 1 ; ir <= nreg ; ir++){
      int length  = domain->rlenmix[ir];
      int *grdmix = domain->rgrdmix[ir];
      int *ndxmix = domain->rndxmix[ir];
      if (length > 0){
	if (ndims == 2){
	  for (i = 0 ; i < length ; i++){
	    int mixZoneIndex = ndxmix[i];
	    int zoneIndex    = grdmix[i];
	    tCenter[mixZoneIndex] = tCenter[zoneIndex];
	    tLeft[mixZoneIndex]   = tCenter[zoneIndex];
	    tRight[mixZoneIndex]  = tCenter[zoneIndex];
	    tFront[mixZoneIndex]  = tCenter[zoneIndex];
	    tBack[mixZoneIndex]   = tCenter[zoneIndex];
	  }
	} else {
	  for (i = 0 ; i < length ; i++){
	    int mixZoneIndex = ndxmix[i];
	    int zoneIndex    = grdmix[i];
	    tCenter[mixZoneIndex] = tCenter[zoneIndex];
	    tLeft[mixZoneIndex]   = tCenter[zoneIndex];
	    tRight[mixZoneIndex]  = tCenter[zoneIndex];
	    tFront[mixZoneIndex]  = tCenter[zoneIndex];
	    tBack[mixZoneIndex]   = tCenter[zoneIndex];
	    tUp[mixZoneIndex]     = tCenter[zoneIndex];
	    tDown[mixZoneIndex]   = tCenter[zoneIndex];
	  }
	}
      }
    }
  }
  FT_FINALIZE(me, domain->hash, myflops)
}
static void SetFaceTemperature_WainwrightAverage
                 (Domain_t *domain,
                  double *zoneCenteredT1, double *zoneCenteredT2,
		  double *faceCenteredT1, double *faceCenteredT2,
		  int firstFace, int lastFace)
{
  char *me = "SetFaceTemperature_WainwrightAverage";
  int i;
  double fourSevenths = 4. / 7.;
  double third        = 1. / 3.;
  double myflops = 0.0;
  FT_INITIALIZE(me, domain->hash)
  for (i = firstFace ; i <= lastFace ; i++){
    double t11 = zoneCenteredT1[i];
    double t12 = t11 * t11;
    double t13 = t12 * t11;
    double t14 = t13 * t11;
    double t15 = t14 * t11;
    double t16 = t15 * t11;
    double t21 = zoneCenteredT2[i];
    double t22 = t21 * t21;
    double t23 = t22 * t21;
    double t24 = t23 * t21;
    double t25 = t24 * t21;
    double t26 = t25 * t21;
    double t3bar = (t11 + t21) * (t12 + t22);
    double t6bar = t16 + t15*t21 + t14*t22 + t13*t23
      + t12*t24 + t11*t25 + t26;
    double tFace = fourSevenths * t6bar /(t3bar + ptiny);
    tFace = pow(tFace, third);
    faceCenteredT1[i] = tFace;
    faceCenteredT2[i] = tFace;
  }
  myflops = 46.0 * (lastFace + 1 - firstFace);
  FT_FINALIZE(me, domain->hash, myflops)
}
static void SetFaceTemperature_TiptonAverage
                 (Domain_t *domain,
                  double *zoneCenteredT1, double *zoneCenteredT2,
		  double *faceCenteredT1, double *faceCenteredT2,
		  double *volume1       , double *volume2,
		  int firstFace, int lastFace)
{
  char *me = "SetFaceTemperature_TiptonAverage";
  int i;
  double tFace, phiAverage;
  double myflops = 0.0;
  FT_INITIALIZE(me, domain->hash)
  for (i = firstFace ; i <= lastFace ; i++){
    double phi1 = zoneCenteredT1[i];
    double phi2 = zoneCenteredT2[i];
    phi1 = phi1 * phi1;
    phi1 = phi1 * phi1;
    phi2 = phi2 * phi2;
    phi2 = phi2 * phi2;
    phiAverage = (phi1 * volume1[i] + phi2 * volume2[i]) /
                 (volume1[i] + volume2[i] + ptiny);
    tFace = sqrt(sqrt(phiAverage));
    tFace = MAX(tFace, tfloor);
    faceCenteredT1[i] = tFace;
    faceCenteredT2[i] = tFace;
  }
  myflops= 21.0 * (lastFace + 1 - firstFace);
  FT_FINALIZE(me, domain->hash, myflops)
}
