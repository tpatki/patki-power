#ifndef irstdiff_h
#define irstdiff_h

#include "SpeciesFraction.h"
#include "RadiationData.h"
#include "BlockMapping.h"
#include "DiffusionData.h"
#include "Region.h"

/*------------------------------------------------------------------------------
- DEFINES AND MACROS
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
- PROTOTYPES
------------------------------------------------------------------------------*/

extern double FluxLimiterPrism(double *x, double *y, double *z, double *variable, double umin);
extern double FluxLimiterTetrahedron(double *x, double *y, double *z, double *variable, double umin);
extern double norml2(Domain_t *domain, double *x);
extern int Dgefa(double *matrix, int *pivot, int len);
extern void ChemPotCalc(double *den, double *tmat, Domain_t *domain);
extern void ChemPot_fm1(double *mu, double *den, double *tmat, double *zstar, double *abar, int n, Domain_t *domain);
extern void CopyArrayDouble(double *copyArray, double *array, int length);
extern void Dgedi(double *matrix, int *pivot, double *work, int len);
extern void DiffCoef(RadiationData_t *rblk, DiffusionData_t *tblk, Domain_t *domain);
extern void DivgradDriver(double *x, double *y, double *z, Domain_t *domain, RadiationData_t *rblk);
extern void Econ_fm1(double *coef, double value, int length, Domain_t *domain);
extern void Econ_fm2(double *coef, double *t52, double value, int *ndx, int length, Domain_t *domain);
extern void Econ_fm3(double *coef, double *t52, double *cden, double *zstar, double *abar, int *ndx, int length, Domain_t *domain);
extern void ElectronConduction(RadiationData_t *rblk, RadiationData_t *cblk, DiffusionData_t *tblk, Domain_t *domains, double dtrad, double radtime);
extern void ElectronConductionCoef(double *diffCoef, double *t52, Domain_t *domain);
extern void FemDivgrad3Boundary(RadiationData_t *rblk, double *xc, double *yc, double *zc, double *volc, Domain_t *domain, int *regConList, int regConListLength);
extern void FemDivgrad3Interior(RadiationData_t *rblk, double *xc, double *yc, double *zc, double *volc, Domain_t *domain, int kMin, int kMax, int jMin, int jMax, int iMin, int iMax);
extern void FemHexahedron(double *x, double *y, double *z, double *gradX, double *gradY, double *gradZ);
extern void FemPrism(double *x, double *y, double *z, double *gradX, double *gradY, double *gradZ);
extern void FemTetrahedron(double *x, double *y, double *z, double *gradX, double *gradY, double *gradZ);
extern void FluxLimiterDriver(double *x, double *y, double *z, double *phi, double *flmt, double fscl, double umin, Domain_t *domain);
extern void FluxLimiterPert2Bnd(double *zc, double *rc, Domain_t *domain, double *phi, double *flmt, double umin, double fscl, int *nodelist, int numNodes);
extern void FluxLimiterPert2d(double *zc, double *rc, Domain_t *domain, double *phi, double *flmt, double umin, double fscl, int imin, int imax, int jmin, int jmax);
extern void FluxLimiterPert3Bnd(double *flmt, double *phi, double *xc, double *yc, double *zc, double *volc, Domain_t *domain, double fscl, double umin, int *regConList, int regConListLength);
extern void FluxLimiterPert3d(double *flmt, double *phi, double *xc, double *yc, double *zc, double *volc, Domain_t *domain, double fscl, double umin, int kMin, int kMax, int jMin, int jMax, int iMin, int iMax);
extern void Icon_fm1(double *coef, double value, int length, Domain_t *domain);
extern void Icon_fm2(double *coef, double *t52, double value, int *ndx, int length, Domain_t *domain);
extern void Icon_fm3(double *coef, double *t52, double *cden, double *zstar, double *abar, int *ndx, int length, Domain_t *domain);
extern void IonConduction(RadiationData_t *rblk, RadiationData_t *cblk, DiffusionData_t *tblk, Domain_t *domains, double dtrad, double radtime);
extern void IonConductionCoef(double *diffCoef, double *t52, Domain_t *domain);
extern void KpAnalytic_fm1(double *xplnk, double *den, double *coef, double dtrad, int ir, Domain_t *domain, OpacityGroup_t *opacityGroup);
extern void KpAnalytic_fm2(double *xplnk, double *den, double *abar, double *zbar, double *zstar, double *mu, double dtrad, int ir, double *phi, Domain_t *domain, OpacityGroup_t *opacityGroup);
extern void KpAnalytic_fm3(Domain_t *domain, double *kros, double *xplnk, double *den, double *tmax, double dtrad, int ir, double *coef, double *abar, OpacityGroup_t *opacityGroup);
extern void KpAnalytic_fm5(double *xplnk, double *den, double *abar, double *zstar, double dtrad, int ir, Domain_t *domain, OpacityGroup_t *opacityGroup);
extern void KpAnalytic_fm6(Domain_t *domain, double *kros, double *xplnk, double *den, double *tmax, double dtrad, int ir, double *coef, double *abar, double *zbar, OpacityGroup_t *opacityGroup);
extern void KpAnalytic_fm7(double *xplnk, double *den, double *temp, double *coef, double dtrad, int ir, Domain_t *domain, OpacityGroup_t *opacityGroup);
extern void KpAnalytic_fm8(double *xplnk, double *den, double *abar, double *zbar, double dtrad, int ir, double *phi, Domain_t *domain, OpacityGroup_t *opacityGroup);
extern void KpAnalytic_fm9(double *xplnk, double *den, double *abar, double *zbar, double dtrad, int ir, double *phi, Domain_t *domain, OpacityGroup_t *opacityGroup);
extern void KrAnalytic_fm1(double *kros, double *den, double *coef, double dtrad, int ir, Domain_t *domain, OpacityGroup_t *opacityGroup);
extern void KrAnalytic_fm3(double *kros, double *den, double *tmax, double *abar, double *coef, double dtrad, int ir, Domain_t *domain, OpacityGroup_t *opacityGroup);
extern void KrAnalytic_fm5(double *kros, double *den, double *tmax, double *abar, double *zbar, double dtrad, int ir, Domain_t *domain, OpacityGroup_t *opacityGroup);
extern void KrAnalytic_fm6(double *kros, double *den, double *tmax, double *abar, double *zbar, double *coef, double dtrad, int ir, Domain_t *domain, OpacityGroup_t *opacityGroup);
extern void KrAnalytic_fm7(double *kros, double *den, double *tmax, double *coef, double dtrad, int ir, Domain_t *domain, OpacityGroup_t *opacityGroup);
extern void KrAnalytic_fm8(double *kros, double *den, double *coef, double dtrad, int ir, Domain_t *domain, OpacityGroup_t *opacityGroup);
extern void KrAnalytic_fm9(double *kros, double *den, double *abar, double *data, double refd, double dtrad, int ir, Domain_t *domain, OpacityGroup_t *opacityGroup);
extern void MatrixSolveDriver(RadiationData_t *rblk, RadiationData_t *cblk, DiffusionData_t *tblk, Domain_t *domains, int *iterations, double *error);
extern void MatterDiagonal(RadiationData_t *rblk, DiffusionData_t *tblk, double *dedt, Domain_t *domain, double dtrad);
extern void MatterUpdateTemperature(double dtrad, double *newTemperature, double *conductivity, double *energy, double *temperature, double *heatCapacity, Domain_t *domain);
extern void MatterWainwright(double *t52, double *temperature, int stride, Domain_t *domain);
extern void PrismVolume(double *x, double *y, double *z, double *VolumePrism);
extern void RadiationAllocate(RadiationData_t * *rblk, RadiationData_t * *rblkbak, RadiationData_t * *cblk, DiffusionData_t * *tblk, int needRblkBak);
extern void RadiationFree(RadiationData_t *rblk, RadiationData_t *rblkbak, RadiationData_t *cblk, DiffusionData_t *tblk, int needRblkBak);
extern void RadiationSourceBC_2d(RadiationData_t *rblk, DiffusionData_t *tblk, Domain_t *domain);
extern void RadiationSourceBC_3d(RadiationData_t *rblk, DiffusionData_t *tblk, Domain_t *domain);
extern void ResortPrism(double *a, double *b, double *c, double *d, int *indexlist);
extern void SetFaceTemperature_Driver(Domain_t *domain, double *volume, double *tCenter, double *tUp, double *tDown, double *tLeft, double *tRight, double *tFront, double *tBack);
extern void TetVolume(double *x, double *y, double *z, double *VolumeTet);
extern void bound_free(double *kbf, double *den, double *zbar, double *abar, double *mu, int *ndx, int n, double *zstar, double *phi, Domain_t *domain);
extern void cblkbc(RadiationData_t *cblk, Domain_t *domain);
extern void cblkbc2(RadiationData_t *cblk, Domain_t *domain);
extern void cblkbc3(RadiationData_t *cblk, Domain_t *domain);
extern void diagonal(RadiationData_t *rblk, DiffusionData_t *tblk, Domain_t *domain, double dtrad, double depositionFraction);
extern void diff1g(void);
extern void divgrad2(double *x, double *y, Domain_t *domain, double *a1, double *b0, double *b1, double *bm1, double *phi, double *flmt, double umin, double fscl);
extern void divgrad3(double *x, double *y, double *z, RadiationData_t *rblk, Domain_t *domain, double *phi, double *flmt, double umin, double fscl);
extern void divgradpert2bnd(double *zc, double *rc, Domain_t *domain, RadiationData_t *rblk, int *nodelist, int numNodes);
extern void divgradpert2d(double *zc, double *rc, Domain_t *domain, RadiationData_t *rblk, int imin, int imax, int jmin, int jmax);
extern void divgradpert3bnd(RadiationData_t *rblk, double *xc, double *yc, double *zc, double *volc, int *regConList, int regConListLength, Domain_t *domain);
extern void divgradpert3d(RadiationData_t *rblk, double *xc, double *yc, double *zc, double *volc, int iMin, int iMax, int jMin, int jMax, int kMin, int kMax, Domain_t *domain);
extern void freeMatrix(RadiationData_t *matrix, int dimensionality);
extern void geteicouple(double *rate, double *tmat, double *den, double dtcup, Domain_t *domain);
extern void gettfzstar(double *cden, double *czstar, double *tmat, double *abar, double *zbar, int *ndx, int n, Domain_t *domain);
extern void getzabar0(double *zbar, double *abar, double *wgt, int ir, Domain_t *domain);
extern void gtkappabnd(Domain_t *domain, double dtrad);
extern void kapmlt(double *kros, double *xplnk, double *t, int *ndx, int n, double *data, int ndata);
extern void opac2t(double *phi, Domain_t *domain, double *kros, double *tmax, double dtrad);
extern void opaclmt(double *kros, double kroslmt, int *ndx, int n, Domain_t *domain);
extern void planck_opacity(double *xplnk, double *tcen, double dtrad, double *phi, Domain_t *domain);
extern void radfree(DiffusionData_t *tblk);
extern void radinit(DiffusionData_t *tblk);
extern void rdiff(RadiationData_t *rblk, RadiationData_t *cblk, DiffusionData_t *tblk, Domain_t *domains, double dtrad, double radtime, double depositionFraction);
extern void rdiffbc(RadiationData_t *rblk, DiffusionData_t *tblk, Domain_t *domain);
extern void rdiffbc2(RadiationData_t *rblk, DiffusionData_t *tblk, Domain_t *domain);
extern void rdiffbc3(RadiationData_t *rblk, DiffusionData_t *tblk, Domain_t *domain);
extern void rdiffset(Domain_t *domain, double dtrad);
extern void rdiffsrc(DiffusionData_t *tblk, Domain_t *domain, double radtime);
extern void reicouple(double *rate, double *den, double *tmat, int *ndx, int n, double *zstar, double *abar, double *mu, double eimlt, double dtrad, Domain_t *domain);
extern void retransfer(double dtrad, double depositionFraction, DiffusionData_t *tblk, Domain_t *domain);
extern void rmatmult(Domain_t *domain, RadiationData_t *rblk, double *x, double *y);
extern void rmatmult2(Domain_t *domain, RadiationData_t *rblk, double *x, double *y);
extern void rmatmult3(Domain_t *domain, RadiationData_t *rblk, double *x, double *b);
extern void rsrcbc(RadiationData_t *rblk, DiffusionData_t *tblk, Domain_t *domain);
extern void rsrcbc2(RadiationData_t *rblk, DiffusionData_t *tblk, Domain_t *domain);
extern void rsrcbc3(RadiationData_t *rblk, DiffusionData_t *tblk, Domain_t *domain);
extern void setpz1(double *v, double s, Domain_t *domain);
extern void setpz2(double *v, double s, Domain_t *domain);
extern void tblkinit(DiffusionData_t *tblk);
extern void tdiff(double dtrad, double radtime, double depositionFraction);
extern void teicouple(double *emat, double *tmat, double *dedt, double *eion, double *tion, double *deidt, double *den, double scale, double dtcup, Domain_t *domain);
extern void zstarcal(double *den, double *tmat, Domain_t *domain);
extern void RegionTableInitialize(Domain_t *domain, Region_t *reg, int nreg, SpeciesFraction_t *specfrac);

#endif

/*------------------------------------------------------------------------------
- GLOBAL VARS
------------------------------------------------------------------------------*/

/*******************************************************************************
* END OF FILE
*******************************************************************************/
