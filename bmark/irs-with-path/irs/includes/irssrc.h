#ifndef IRSSRC_H
#define IRSSRC_H

#include "NodeList.h"
#include "Extents.h"

/*******************************************************************************
* DEFINES
*******************************************************************************/


#define PSRC1    1
#define PSRC2    2
#define TSRC     3
#define TSRCINT  4
#define DSRC1    5
#define DSRC2    6
#define ESRC1    7
#define ESRC2    8
#define XVSRC1   9
#define YVSRC1  10
#define ZVSRC1  11
#define XVSRC2  12
#define YVSRC2  13
#define ZVSRC2  14
#define XASRC1  15
#define YASRC1  16
#define ZASRC1  17
#define XASRC2  18
#define YASRC2  19
#define ZASRC2  20
#define TESRC1  21
#define TISRC1  22
#define TESRC2  23
#define TISRC2  24
#define ERATE2  25
#define XMINSRC 26
#define XMAXSRC 27
#define YMINSRC 28
#define YMAXSRC 29
#define ZMINSRC 30
#define ZMAXSRC 31
#define XASRC3  32
#define YASRC3  33
#define ZASRC3  34

#define ALE_BND     35

#define XEULER      48
#define YEULER      49
#define ZEULER      50

#define TESRCINT1   51
#define TISRCINT1   52
#define TESRCINT2   53
#define TISRCINT2   54

#define ERATE4      55

/*******************************************************************************
* PROTOTYPES
*******************************************************************************/
extern int srcin(int mode);
extern int srcin_init(int mode, char *srctype, NodeWindow_t *ndxin);
extern void asrc(double atime, double *xa, double *ya, double *za, Domain_t *domain);
extern void dsrc(double dtime, double *den, Domain_t *domain);
extern void erate(double etime, double dterate, double *dele, int type, Domain_t *domain);
extern void esrc(double etime, double *emat, Domain_t *domain);
extern void psrc(double ptime, Domain_t *domain);
extern void srccopy(Domain_t *domain1, Extents_t *ext1, Domain_t *domain2, Extents_t *ext2, int irep);
extern void tmsrc(double stime, double *ee, double *te, double *dedt, double *ei, double *ti, double *deidt, Domain_t *domain);
extern void vsrc(double vtime, double *xv, double *yv, double *zv, Domain_t *domain);

#endif
/*******************************************************************************
* GLOBALS
*******************************************************************************/

/*******************************************************************************
* END OF FILE
*******************************************************************************/



















