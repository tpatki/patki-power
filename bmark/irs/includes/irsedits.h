
#ifndef IRSEDITS_H
#define IRSEDITS_H

/*******************************************************************************
* DEFINES
*******************************************************************************/

/*******************************************************************************
* PROTOTYPES
*******************************************************************************/
extern int editor(int stepflag);
extern int flagedit(void);
extern int matedit(void);
extern int mpi_edit(void);
extern int print(void);
extern int printcyclefreqs(void);
extern int printtimefreqs(void);
extern int printtpcurves(void);
extern int printtimeplots(void);
extern int query_timer(void);
extern int reducevar(int type);
extern int regedit(int stepflag);
extern int stateedit(void);
extern void printspec(char *lab, double *field, int i0, int j0, int n, Domain_t *domain);
extern void regenrgy2d(double *x, double *y, double *xv, double *yv, Domain_t *domain);
extern void regenrgy3d(double *x, double *y, double *z, double *xv, double *yv, double *zv, Domain_t *domain);

#endif
/*******************************************************************************
* GLOBALS
*******************************************************************************/

/*******************************************************************************
* END OF FILE
*******************************************************************************/

