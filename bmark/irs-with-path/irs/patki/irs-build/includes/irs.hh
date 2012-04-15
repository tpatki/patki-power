#ifndef irs_H
#define irs_H

#include <stdio.h>
#include <stdlib.h>	
#include <sys/times.h>  
#include <time.h>

#ifdef USE_DMALLOC   
#include "dmalloc.h"
#endif

#ifdef SILO
#include <silo.h>
#endif

#include "irsdefs.h"		
#include "irsctl.h"    	
#include "Domain.h"		
#include "mach.h"      		

/*
 ***********************************************************************
 *  file:    trace_prepend.c
 *  authors: Terry Jones (LLNL) & Robert Blackmore (IBM)
 *  notes:   Please see README.tracing
 ***********************************************************************
*/

#ifdef TERRY_TRACE

#include <sys/trcctl.h>
#include <sys/trcmacros.h>
#include <sys/trchkid.h>

#define MYHOOKWORD HKWD_USER2

#define START_IRS_TEST			( 1 | MYHOOKWORD)
#define BEFORE_MPI_Allreduce		( 2 | MYHOOKWORD)
#define AFTER_MPI_Allreduce		( 3 | MYHOOKWORD)
#define BEFORE_MPI_Barrier		( 4 | MYHOOKWORD)
#define AFTER_MPI_Barrier		( 5 | MYHOOKWORD)
#define BEFORE_MPI_Waitall		( 6 | MYHOOKWORD)
#define AFTER_MPI_Waitall		( 7 | MYHOOKWORD)
#define BEFORE_MPI_Wait			( 8 | MYHOOKWORD)
#define AFTER_MPI_Wait			( 9 | MYHOOKWORD)
#define BEFORE_MPI_Waitany		( 10 | MYHOOKWORD)
#define AFTER_MPI_Waitany		( 11 | MYHOOKWORD)
#define BEFORE_MPI_Bcast		( 12 | MYHOOKWORD)
#define AFTER_MPI_Bcast 		( 13 | MYHOOKWORD)
#define BEFORE_MPI_Isend		( 14 | MYHOOKWORD)
#define AFTER_MPI_Isend			( 15 | MYHOOKWORD)
#define BEFORE_MPI_Irecv		( 16 | MYHOOKWORD)
#define AFTER_MPI_Irecv			( 17 | MYHOOKWORD)
#define BEFORE_MPI_Send			( 18 | MYHOOKWORD)
#define AFTER_MPI_Send			( 19 | MYHOOKWORD)
#define BEFORE_MPI_Recv			( 20 | MYHOOKWORD)
#define AFTER_MPI_Recv			( 21 | MYHOOKWORD)

#define ENTERING_IRS_MAIN               ( 1  | HKWD_USER3)
#define EXITING_IRS_MAIN                ( 2  | HKWD_USER3)
#define ENTERING_IRS_ROUTINE1           ( 3  | HKWD_USER3)
#define EXITING_IRS_ROUTINE1            ( 4  | HKWD_USER3)
#define ENTERING_IRS_ROUTINE2           ( 5  | HKWD_USER3)
#define EXITING_IRS_ROUTINE2            ( 6  | HKWD_USER3)
#define ENTERING_IRS_ROUTINE3           ( 7  | HKWD_USER3)
#define EXITING_IRS_ROUTINE3            ( 8  | HKWD_USER3)
#define ENTERING_IRS_ROUTINE4           ( 9  | HKWD_USER3)
#define EXITING_IRS_ROUTINE4            ( 10 | HKWD_USER3)
#define ENTERING_IRS_ROUTINE5           ( 11 | HKWD_USER3)
#define EXITING_IRS_ROUTINE5            ( 12 | HKWD_USER3)
#define ENTERING_IRS_ROUTINE6           ( 13 | HKWD_USER3)
#define EXITING_IRS_ROUTINE6            ( 14 | HKWD_USER3)
#define ENTERING_IRS_ROUTINE7           ( 15 | HKWD_USER3)
#define EXITING_IRS_ROUTINE7            ( 16 | HKWD_USER3)
#define ENTERING_IRS_ROUTINE8           ( 17 | HKWD_USER3)
#define EXITING_IRS_ROUTINE8            ( 18 | HKWD_USER3)
#define ENTERING_IRS_ROUTINE9           ( 19 | HKWD_USER3)
#define EXITING_IRS_ROUTINE9            ( 20 | HKWD_USER3)
#define ENTERING_IRS_ROUTINE10          ( 21 | HKWD_USER3)
#define EXITING_IRS_ROUTINE10           ( 22 | HKWD_USER3)
#define ENTERING_IRS_ROUTINE11          ( 23 | HKWD_USER3)
#define EXITING_IRS_ROUTINE11           ( 24 | HKWD_USER3)
#define ENTERING_IRS_ROUTINE12          ( 25 | HKWD_USER3)
#define EXITING_IRS_ROUTINE12           ( 26 | HKWD_USER3)
#define ENTERING_IRS_ROUTINE13          ( 27 | HKWD_USER3)
#define EXITING_IRS_ROUTINE13           ( 28 | HKWD_USER3)
#define ENTERING_IRS_ROUTINE14          ( 29 | HKWD_USER3)
#define EXITING_IRS_ROUTINE14           ( 30 | HKWD_USER3)
#define ENTERING_IRS_ROUTINE15          ( 31 | HKWD_USER3)
#define EXITING_IRS_ROUTINE15           ( 32 | HKWD_USER3)
#define ENTERING_IRS_ROUTINE16          ( 33 | HKWD_USER3)
#define EXITING_IRS_ROUTINE16           ( 34 | HKWD_USER3)
#define ENTERING_IRS_ROUTINE17          ( 35 | HKWD_USER3)
#define EXITING_IRS_ROUTINE17           ( 36 | HKWD_USER3)
#define ENTERING_IRS_ROUTINE18          ( 37 | HKWD_USER3)
#define EXITING_IRS_ROUTINE18           ( 38 | HKWD_USER3)
#define ENTERING_IRS_ROUTINE19          ( 39 | HKWD_USER3)
#define EXITING_IRS_ROUTINE19           ( 40 | HKWD_USER3)
#define ENTERING_IRS_ROUTINE20          ( 41 | HKWD_USER3)
#define EXITING_IRS_ROUTINE20           ( 42 | HKWD_USER3)


#define ZAP_OLD_TRACE(doit)                                       \
if (terry_trace_flag == TRUE)                                     \
{                                                                 \
        /* Turn off trace if it was left on */                    \
        if((doit) && (ctlfd = open(ctl_file,0))>=0){              \
               ioctl(ctlfd,TRCSTOP,0);                            \
               close(ctlfd);                                      \
                }                                                 \
}


/* OLD
if (trcstart("-ad -o /var/tmp/trcfile -T104857600 -L209715200 -j001,002,006,020,030,0AC,100,102,103,106,10C,134,139,200,306,307,308,309,465")){ \
if (trcstart("-ad -o /var/tmp/trcfile -Call -T16777216 -L33554432 -j001,002,006,020,030,0AC,100,102,103,106,10C,134,139,200,306,307,308,309,465")){ \
if (trcstart("-ad -o /var/tmp/trcfile -T104857600 -L3000000000 -j001,002,006,020,030,0AC,100,102,103,106,10C,134,139,200,306,307,308,309,465")){ \
*/

/* OLD before March 9, 2004 and beta testing of new aix kernel
 
#define INIT_TRACING(doit)                                        \
{                                                                 \
    if((doit)) {                                                  \
	if (trcstart("-ad -o /var/tmp/trcfile -T104857600 -L3000000000 -j001,002,006,020,030,0AC,100,102,103,106,10C,134,139,200,306,307,308,309,465")){ \
                perror("trcstart");                               \
                exit(1);                                          \
        }                                                         \
        if((ctlfd = open(ctl_file,0))<0){                         \
                perror(ctl_file);                                 \
                exit(1);                                          \
        }                                                         \
    }                                                             \
}
*/

#define INIT_TRACING(doit)                                        \
if (terry_trace_flag == TRUE)                                     \
{                                                                 \
    if((doit)) {                                                  \
        if (trcstart(opts_buffer)){                               \
                perror("trcstart");                               \
                exit(1);                                          \
        }                                                         \
        if((ctlfd = open(ctl_file,0))<0){                         \
                perror(ctl_file);                                 \
                exit(1);                                          \
        }                                                         \
    }                                                             \
}



#define START_TRACING(doit)                                       \
if (terry_trace_flag == TRUE)                                     \
{                                                                 \
             if((doit) )                                          \
                if( ioctl(ctlfd,TRCON,0)){                        \
                        perror("TRCON");                          \
                        exit(1);                                  \
                }                                                 \
}

#define STOP_TRACING(doit)                                        \
if (terry_trace_flag == TRUE)                                     \
{                                                                 \
             if((doit) )                                          \
                if( ioctl(ctlfd,TRCOFF,0)){                       \
                        perror("TRCOFF");                         \
                        exit(1);                                  \
                }                                                 \
}

#define HALT_TRACING(doit)                                        \
if (terry_trace_flag == TRUE)                                     \
{                                                                 \
             if((doit) )                                          \
                if( ioctl(ctlfd,TRCSTOP,0)){                      \
                        perror("TRCSTOP");                        \
                        exit(1);                                  \
                }                                                 \
}

char *ctl_file;
int   ctlfd;
int   loop_count, mytraceid, iam_leadtask, leadtask;

void trace_init(char *opts_buffer);
void trace_finalize(void);

#endif
			/*******************************************************
			* END OF TERRY_TRACE SECTION
			*******************************************************/
#ifdef HPMCOUNTERS

#include <libhpm.h>

#define HPM_IRS_MAIN            1
#define HPM_IRS_ROUTINE1        2
#define HPM_IRS_ROUTINE2        3
#define HPM_IRS_ROUTINE3        4
#define HPM_IRS_ROUTINE4        5
#define HPM_IRS_ROUTINE5        6
#define HPM_IRS_ROUTINE6        7
#define HPM_IRS_ROUTINE7        8
#define HPM_IRS_ROUTINE8        9
#define HPM_IRS_ROUTINE9        10
#define HPM_IRS_ROUTINE10       11
#define HPM_IRS_ROUTINE11       12
#define HPM_IRS_ROUTINE12       13
#define HPM_IRS_ROUTINE13       14
#define HPM_IRS_ROUTINE14       15

#endif


#define PRINT fprintf

#define NPNL 2
#define NPNR 1

#define NHEAD_NUM_FPA	0	
#define NHEAD_NUM_IPA   1	
#define NHEAD_NUM_PPA	2
#define NHEAD_NUM	3	

#define CORNER   12

#define EDGE     13
#define FACE     14
#define AREA     15
#define VOLUME   16

#define HALF_STEP 0
#define FULL_STEP 1

#define CROSSPROD(cx,cy,cz,ax,ay,az,bx,by,bz)   \
   cx = ay * bz - az * by ;    \
   cy = az * bx - ax * bz ;    \
   cz = ax * by - ay * bx

#define NDSET2D(v,v1,v2,v3,v4)  \
   v4 = v ;   \
   v1 = v4 + 1 ;  \
   v2 = v1 + domain->jp ;  \
   v3 = v4 + domain->jp ;

#define NDSET2D_STRCT(a,v,v1,v2,v3,v4)  \
   v4 = v ;   \
   v1 = v4 + 1 ;  \
   v2 = v1 + a.jp ;  \
   v3 = v4 + a.jp ;

#define NDSET3D(v,v1,v2,v3,v4,v5,v6,v7,v8)  \
   v4 = v ;   \
   v1 = v4 + 1 ;  \
   v2 = v1 + domain->jp ; \
   v3 = v4 + domain->jp ; \
   v5 = v1 + domain->kp ; \
   v6 = v2 + domain->kp ; \
   v7 = v3 + domain->kp ; \
   v8 = v4 + domain->kp ;

#define NDSET3D_STRCT(a,v,v1,v2,v3,v4,v5,v6,v7,v8)  \
   v4 = v ;   \
   v1 = v4 + 1 ;  \
   v2 = v1 + a.jp ; \
   v3 = v4 + a.jp ; \
   v5 = v1 + a.kp ; \
   v6 = v2 + a.kp ; \
   v7 = v3 + a.kp ; \
   v8 = v4 + a.kp ;

#define NDSET82D(v,v1,v2,v3,v4,v5,v6,v7,v8)       \
   v1 = v + 1 ;                                   \
   v2 = v1 + domain->jp ;                                \
   v3 = v2 - 1 ;                                  \
   v4 = v3 - 1 ;                                  \
   v5 = v4 - domain->jp ;                                \
   v6 = v5 - domain->jp ;                                \
   v7 = v6 + 1 ;                                  \
   v8 = v7 + 1 ;

#define NDSET263D(v,v1,v2,v3,v4,v5,v6,v7,v8,            \
                  v9,v10,v11,v12,v13,v14,v15,v16,v17,   \
                  v18,v19,v20,v21,v22,v23,v24,v25,v26)  \
   v1  = v + 1 ;                                        \
   v2  = v1 + domain->jp ;                                     \
   v3  = v2 - 1 ;                                       \
   v4  = v3 - 1 ;                                       \
   v5  = v4 - domain->jp ;                                     \
   v6  = v5 - domain->jp ;                                     \
   v7  = v6 + 1 ;                                       \
   v8  = v7 + 1 ;                                       \
   v9  = v  + domain->kp ;                                     \
   v10 = v1 + domain->kp ;                                     \
   v11 = v2 + domain->kp ;                                     \
   v12 = v3 + domain->kp ;                                     \
   v13 = v4 + domain->kp ;                                     \
   v14 = v5 + domain->kp ;                                     \
   v15 = v6 + domain->kp ;                                     \
   v16 = v7 + domain->kp ;                                     \
   v17 = v8 + domain->kp ;                                     \
   v18 = v  - domain->kp ;                                     \
   v19 = v1 - domain->kp ;                                     \
   v20 = v2 - domain->kp ;                                     \
   v21 = v3 - domain->kp ;                                     \
   v22 = v4 - domain->kp ;                                     \
   v23 = v5 - domain->kp ;                                     \
   v24 = v6 - domain->kp ;                                     \
   v25 = v7 - domain->kp ;                                     \
   v26 = v8 - domain->kp ; 

#define ZNSET2D(v,v1,v2,v3,v4)   \
   v2 = v ;   \
   v3 = v2 - 1 ;   \
   v4 = v3 - domain->jp ;   \
   v1 = v4 + 1 ;

#define ZNSET3D(v,v1,v2,v3,v4,v5,v6,v7,v8) \
   v2 = v - domain->kp ;  \
   v3 = v2 - 1 ;   \
   v4 = v3 - domain->jp ; \
   v1 = v4 + 1 ;   \
   v5 = v1 + domain->kp ; \
   v6 = v2 + domain->kp ; \
   v7 = v3 + domain->kp ; \
   v8 = v4 + domain->kp ;

#define ZNSET2D_STRCT(a,v,v1,v2,v3,v4)   \
   v2 = v ;   \
   v3 = v2 - 1 ;   \
   v4 = v3 - a.jp ;   \
   v1 = v4 + 1 ;

#define ZNSET3D_STRCT(a,v,v1,v2,v3,v4,v5,v6,v7,v8) \
   v2 = v - a.kp ;  \
   v3 = v2 - 1 ;   \
   v4 = v3 - a.jp ; \
   v1 = v4 + 1 ;   \
   v5 = v1 + a.kp ; \
   v6 = v2 + a.kp ; \
   v7 = v3 + a.kp ; \
   v8 = v4 + a.kp ;

#define NDSET27(v, \
   v000,v100,v200,v010,v110,v210,v020,v120,v220, \
   v001,v101,v201,v011,v111,v211,v021,v121,v221, \
   v002,v102,v202,v012,v112,v212,v022,v122,v222) \
   v000 = v - domain->kp - domain->jp - 1 ; v100 = v000 + 1 ; v200 = v000 + 2 ; \
   v010 = v000 + domain->jp ; v110 = v010 + 1 ;   v210 = v010 + 2 ;      \
   v020 = v010 + domain->jp ; v120 = v020 + 1 ;   v220 = v020 + 2;       \
   v001 = v000 + domain->kp ; v101 = v100 + domain->kp ; v201 = v200 + domain->kp ;    \
   v011 = v010 + domain->kp ; v111 = v110 + domain->kp ; v211 = v210 + domain->kp ;    \
   v021 = v020 + domain->kp ; v121 = v120 + domain->kp ; v221 = v220 + domain->kp ;    \
   v002 = v001 + domain->kp ; v102 = v101 + domain->kp ; v202 = v201 + domain->kp ;    \
   v012 = v011 + domain->kp ; v112 = v111 + domain->kp ; v212 = v211 + domain->kp ;    \
   v022 = v021 + domain->kp ; v122 = v121 + domain->kp ; v222 = v221 + domain->kp ;

#define STRCLONE(x) (char *)(x?(strcpy((char *)calloc(strlen(x)+2,sizeof(char)),x)):NULL)

#define LENEXT(a) (a.imax-a.imin+1)*(a.jmax-a.jmin+1)*(a.kmax-a.kmin+1);
#define LENZEXT(a) (a.imax-a.imin)*(a.jmax-a.jmin)*(a.kmax-a.kmin);

#define STREXT(a,b,c) \
b = a.imax - a.imin + 1 + NPNL + NPNR; \
c = b*(a.jmax - a.jmin + 1 + NPNL + NPNR);

#define ZONEXT(a) \
a.imax--; \
a.jmax--; \
if (ndims == 3) a.kmax--;

#define NDXEXT2D(n,i,j,a)  \
   j = (n) / (a.jp); \
   i = (n) - (j) * (a.jp);

#define NDXEXT3D(n,i,j,k,a)  \
   k = (n) / (a.kp); \
   j = ((n) - (k) * (a.kp)) / (a.jp); \
   i = (n) - (j)*(a.jp) - (k) * (a.kp);

#define CPYEXT(a,b) \
a.imin = b.imin; \
a.imax = b.imax; \
a.jmin = b.jmin; \
a.jmax = b.jmax; \
a.kmin = b.kmin; \
a.kmax = b.kmax;

#define TRSEXT(c,a,b) \
c.imin = a.imin - b.imin + NPNL; \
c.imax = a.imax - b.imin + NPNL; \
c.jmin = a.jmin - b.jmin + NPNL; \
c.jmax = a.jmax - b.jmin + NPNL; \
c.kmin = a.kmin - b.kmin + NPNL; \
c.kmax = a.kmax - b.kmin + NPNL;

#define RELEXT(d,a,b,c) \
d.imin = a.imin - b.imin + c.imin; \
d.imax = a.imax - b.imin + c.imin; \
d.jmin = a.jmin - b.jmin + c.jmin; \
d.jmax = a.jmax - b.jmin + c.jmin; \
d.kmin = a.kmin - b.kmin + c.kmin; \
d.kmax = a.kmax - b.kmin + c.kmin;

#define SUMEXT(c,a,b) \
c.imin = a.imin + b.imin; \
c.imax = a.imax + b.imax; \
c.jmin = a.jmin + b.jmin; \
c.jmax = a.jmax + b.jmax; \
c.kmin = a.kmin + b.kmin; \
c.kmax = a.kmax + b.kmax;

#define SETEXT(a, i1, i2, j1, j2, k1, k2) \
a.imin = i1; \
a.imax = i2; \
a.jmin = j1; \
a.jmax = j2; \
a.kmin = k1; \
a.kmax = k2;

#define CMPEXT(a,b) \
   ( (a.imin == b.imin) && \
     (a.jmin == b.jmin) && \
     (a.kmin == b.kmin) && \
     (a.imax == b.imax) && \
     (a.jmax == b.jmax) && \
     (a.kmax == b.kmax) )

#define FREE     0
#define XVCNST   1
#define YVCNST   2
#define ZVCNST   3
#define FIXED    4
#define WALL     5
#define XVSAME   6
#define BBND     7
#define PLANE    8
#define CYLINDER 9
#define SPHERE  10
#define CONE    11
#define LINE    12

#define OPEN     0
#define CLOSED   1
#define POLE     2

#define ZERO	0

#endif

double tsplit  =  0 ;
char *codename  =  "irs" ;
char outpath[MAXLINE] ;  
Domain_t *domains  =  NULL ;
FILE *fpout  =  NULL ;
int genmd  =  -1 ;


int mixmax ;
int nblkx  ;
int nblk   ;
int blknum ;
int ndims  ;
int nzones ;
int ntdif ;
int ntdifx ;
double sclnamix;

char box[MAXWORD] ;
char title[MAXWORD] ;
char pbnm[MAXWORD] ;

#define IRS_VERSION     "1.0"

/* char version[MAXWORD] ;  */

int rdate ;
int pdmd ;
int ifhilite;
int ifdivgrad ;
int ifkrwgt ;
int ifplane ;
int ifpolar ;
int iftion  ;
int ifeden  ;
int iftmode ;
int ifvol72 ;
int neosgroup ;
int ngroup ;
int ngroupbd ;
int nkappa ;
int igroup ;
int solver ;
int ifprecon ;
int wainwright ;
int lmax ;
double ptiny  =  PTINY ;
double plarge ;

double xcut ;
double ucut ;
double volcut ;
double xgrav ;

double ygrav ;
double zgrav ;
int  ntemppa ;
int ifedif ;
int ifidif ;
int sblock_select[MAXBLKS];
int sblock_select_all =   TRUE ;

double ttime   ;
double tstop   ;
double deltat  ;
double ndeltat ;
double deltatSubcycle ;
int cycle ;
int cstop ;

#ifdef TERRY_TRACE
int  TERRY_MPI_Allreduce_cntr =  0 ;
int  TERRY_MPI_Barrier_cntr =  0 ;
int  TERRY_MPI_Waitall_cntr =  0 ;
int  TERRY_MPI_Wait_cntr =  0 ;
int  TERRY_MPI_Waitany_cntr =  0 ;
int  TERRY_MPI_Bcast_cntr =  0 ;
int  TERRY_MPI_Isend_cntr =  0 ;
int  TERRY_MPI_Irecv_cntr =  0 ;
int  TERRY_MPI_Send_cntr =  0 ;
int  TERRY_MPI_Recv_cntr =  0 ;
int  IRS_MAIN_cntr =  0 ;
int  IRS_ROUTINE1_cntr =  0 ;
int  IRS_ROUTINE2_cntr =  0 ;
int  IRS_ROUTINE3_cntr =  0 ;
int  IRS_ROUTINE4_cntr =  0 ;
int  IRS_ROUTINE5_cntr =  0 ;
int  IRS_ROUTINE6_cntr =  0 ;
int  IRS_ROUTINE7_cntr =  0 ;
int  IRS_ROUTINE8_cntr =  0 ;
int  IRS_ROUTINE9_cntr =  0 ;
int  IRS_ROUTINE10_cntr =  0 ;
int  IRS_ROUTINE11_cntr =  0 ;
int  IRS_ROUTINE12_cntr =  0 ;
int  IRS_ROUTINE13_cntr =  0 ;
int  IRS_ROUTINE14_cntr =  0 ;
int  IRS_ROUTINE15_cntr =  0 ;
int  IRS_ROUTINE16_cntr =  0 ;
int  IRS_ROUTINE17_cntr =  0 ;
int  IRS_ROUTINE18_cntr =  0 ;
int  IRS_ROUTINE19_cntr =  0 ;
int  IRS_ROUTINE20_cntr =  0 ;
#endif

int    ifhgfb  ;
int    hgiter  ;
int    pdviter ;
int    qmode   ;
int    nditer  ;
double xquad   ;
double qlin    ;
double qprlx   ;
double qneg    ;
double hgfrac  ;
double hgheat  ;
double qdvfrac ;
double srcfi   ;
double srcfe   ;

int neos  ;
int neosx ;
double sndmin ;
double tscale ;
int ioneq ;
int ifconvert ;

int ifdynspec ;  
int nspec ;      

int nbq  ;
int nbqx ;

double sbc ;
int    planckwt ;

double tfloor ;

int    kapsav ;
double lphot  ;
double lphot1 ;
double lphot2 ;
int    npbin  ;
int    rdifcgmd ;
double rdifeps  ;
double rdifepsx ;
int    rdifit   ;
int    edifit   ;
int    idifit   ;
int    rdifitn  ;
int    rdifitx  ;
int    rdifoutn ;
int    rdifoutx ;
int    radsubcycles ;
int    radsubcycles_max ;
double rdifloss ;
double rdifmiln ;
int    rdifmix  ;
double rflx     ;
double trcool   ;
double phifloor ;
double eifrac   ;
double ktfloor  ;

int irvoid ;
double denvoid ;
double ematvoid ;

double mass0 ;
double etot0 ;
double masstot ;
double xmomtot ;
double ymomtot ;
double zmomtot ;
double xmomtotp ;
double ymomtotp ;
double zmomtotp ;
double xmomtotn ;
double ymomtotn ;
double zmomtotn ;
double ketot   ;
double ietot   ;
double etot    ;
double petot   ;
double qdvtot  ;
double eleak   ;
double engsrc  ;
double eloss   ;
double echk    ;
double echkx   ;
double delag   ;
double deadv   ;
double tketot  ;
double dkeadv  ;
double dieadv  ;
double volumetot ;
double tnetot  ;
double dtnetot ;

int  child_io_off =  FALSE ;
int  child_io_todir =  FALSE ;
char child_outpath[256]; 

int  ifcomsummary =  FALSE ;


int ifthreads ; 
int ifparallel ; 
int ifmpi  =  FALSE ;
int myid  =  0 ;
int ifcom ; 
int ifsewbnd ; 
int ifvsame ;
int vsame_max_id ; 
int warntime;
double com_physics_time =  0.0 ;

int nbcx ;
int nbndx ;

int nsrc ;
int nsrcx ;

double tpmult ;


int ifkwgt ;    
double tkewgt ; 
double tkecut ;  

int noerrflag =  FALSE ;
int debugflag =  FALSE ;
int cycflag =  FALSE ;
int coredumpflag =  TRUE ;

int ifbarrier  =  0 ;

int gv_alldump =  TRUE ;

int terry_trace_flag =  FALSE ;

double gv_maxdouble =   1e+300  ;
double gv_mindouble =   -(1e+300) ;

char **gv_int_varlist =  NULL ;
char **gv_dbl_varlist =  NULL ;
int    gv_int_varlist_size =  0 ;
int    gv_dbl_varlist_size =  0 ;

char *gv_errmsg_DBAddOption =  "DBAddOption failed" ;
char *gv_errmsg_DBClearOptlist =  "DBClearOptlist failed" ;
char *gv_errmsg_DBFreeOptlist =  "DBFreeOptlist failed" ;
char *gv_errmsg_DBMkDir =  "DBMkDir failed" ;
char *gv_errmsg_DBPutMaterial =  "DBPutMaterial failed" ;
char *gv_errmsg_DBPutQuadmesh =  "DBPutQuadmesh failed" ;
char *gv_errmsg_DBPutQuadvar1 =  "DBPutQuadvar1 failed" ;
char *gv_errmsg_DBReadVar =  "DBReadVar failed" ;
char *gv_errmsg_DBSetDir =  "DBSetdir failed" ;
char *gv_errmsg_DBGetDir =  "DBGetdir failed" ;
char *gv_errmsg_DBWrite =  "DBWrite failed" ;
char *gv_errmsg_DBPutCompoundarray =  "DBPutCompoundarray failed " ;
char *gv_errmsg_DBGetCompoundarray =  "DBGetCompoundarray failed " ;
char *gv_errmsg_DBOpen =  "DBOpen failed" ;

char *gv_errmsg_rgst_read_struct =  "rgst_read_struct failed" ;
char *gv_errmsg_rgst_read_struct_in_dir =  "rgst_read_struct_in_dir failed" ;
char *gv_errmsg_rgst_write_struct =  "rgst_write_struct failed" ;
char *gv_errmsg_rgst_write_struct_in_dir =  "rgst_write_structin_dir failed" ;
char *gv_errmsg_rgst_write_linked_list =  "rgst_write_linked_list failed" ;
char *gv_errmsg_rgst_write_linked_list_in_dir =  "rgst_write_linked_list_in_dir failed" ;
char *gv_errmsg_rgst_add_mult_attrs =  "rgst_add_mult_attrs failed" ;
char *gv_errmsg_rgst_conv_enum_type_to_str =  "rgst_conv_enum_type_to_str failed" ;
char *gv_errmsg_rgst_del_attrs_from_fields =  "rgst_del_attrs_from_fields failed" ;
char *gv_errmsg_rgst_del_attr =  "rgst_del_attr failed" ;
char *gv_errmsg_rgst_add_attrs_to_fields =  "rgst_add_attrs_to_fields failed" ;

char *logic_err =  "LOGIC ERROR - tell programmer to see core" ;
char *gv_errmsg_memory =  "ALLOT or other memory allocation routine returned NULL" ;
char *gv_errmsg_not_null =  "Possible memory leak?  About to allocate memory to pointer that is not null" ;
char *gv_errmsg_not_done =  "This section of code not completed yet, contact programmer" ;

/*******************************************************************************
* END OF FILE
*******************************************************************************/
