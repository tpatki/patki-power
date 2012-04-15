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

extern char *ctl_file;
extern int   ctlfd;
extern int   loop_count, mytraceid, iam_leadtask, leadtask;

extern void trace_init(char *opts_buffer);
extern void trace_finalize(void);

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

extern double tsplit ;    	/* HH_INIT 0 */
extern char *codename ;         /* HH_INIT "irs" */
extern char outpath[MAXLINE] ;  
extern Domain_t *domains ;      /* HH_INIT NULL */
extern FILE *fpout ;            /* HH_INIT NULL */
extern int genmd ;	        /* HH_INIT -1 */


extern int mixmax ;
extern int nblkx  ;
extern int nblk   ;
extern int blknum ;
extern int ndims  ;
extern int nzones ;
extern int ntdif ;
extern int ntdifx ;
extern double sclnamix;

extern char box[MAXWORD] ;
extern char title[MAXWORD] ;
extern char pbnm[MAXWORD] ;

#define IRS_VERSION     "1.0"

/* extern char version[MAXWORD] ;  */

extern int rdate ;
extern int pdmd ;
extern int ifhilite;
extern int ifdivgrad ;
extern int ifkrwgt ;
extern int ifplane ;
extern int ifpolar ;
extern int iftion  ;
extern int ifeden  ;
extern int iftmode ;
extern int ifvol72 ;
extern int neosgroup ;
extern int ngroup ;
extern int ngroupbd ;
extern int nkappa ;
extern int igroup ;
extern int solver ;
extern int ifprecon ;
extern int wainwright ;
extern int lmax ;
extern double ptiny ; /* HH_INIT PTINY */
extern double plarge ;

extern double xcut ;
extern double ucut ;
extern double volcut ;
extern double xgrav ;

extern double ygrav ;
extern double zgrav ;
extern int  ntemppa ;
extern int ifedif ;
extern int ifidif ;
extern int sblock_select[MAXBLKS];
extern int sblock_select_all; /* HH_INIT  TRUE */

extern double ttime   ;
extern double tstop   ;
extern double deltat  ;
extern double ndeltat ;
extern double deltatSubcycle ;
extern int cycle ;
extern int cstop ;

#ifdef TERRY_TRACE
extern int  TERRY_MPI_Allreduce_cntr; /* HH_INIT 0 */
extern int  TERRY_MPI_Barrier_cntr; 	/* HH_INIT 0 */
extern int  TERRY_MPI_Waitall_cntr;	/* HH_INIT 0 */
extern int  TERRY_MPI_Wait_cntr;	/* HH_INIT 0 */
extern int  TERRY_MPI_Waitany_cntr;	/* HH_INIT 0 */
extern int  TERRY_MPI_Bcast_cntr;	/* HH_INIT 0 */
extern int  TERRY_MPI_Isend_cntr;	/* HH_INIT 0 */
extern int  TERRY_MPI_Irecv_cntr;	/* HH_INIT 0 */
extern int  TERRY_MPI_Send_cntr;	/* HH_INIT 0 */
extern int  TERRY_MPI_Recv_cntr;	/* HH_INIT 0 */
extern int  IRS_MAIN_cntr; 	/* HH_INIT 0 */
extern int  IRS_ROUTINE1_cntr;	/* HH_INIT 0 */
extern int  IRS_ROUTINE2_cntr;	/* HH_INIT 0 */
extern int  IRS_ROUTINE3_cntr;	/* HH_INIT 0 */
extern int  IRS_ROUTINE4_cntr;	/* HH_INIT 0 */
extern int  IRS_ROUTINE5_cntr;	/* HH_INIT 0 */
extern int  IRS_ROUTINE6_cntr;	/* HH_INIT 0 */
extern int  IRS_ROUTINE7_cntr;	/* HH_INIT 0 */
extern int  IRS_ROUTINE8_cntr;	/* HH_INIT 0 */
extern int  IRS_ROUTINE9_cntr;	/* HH_INIT 0 */
extern int  IRS_ROUTINE10_cntr;	/* HH_INIT 0 */
extern int  IRS_ROUTINE11_cntr;	/* HH_INIT 0 */
extern int  IRS_ROUTINE12_cntr;	/* HH_INIT 0 */
extern int  IRS_ROUTINE13_cntr;	/* HH_INIT 0 */
extern int  IRS_ROUTINE14_cntr;	/* HH_INIT 0 */
extern int  IRS_ROUTINE15_cntr;	/* HH_INIT 0 */
extern int  IRS_ROUTINE16_cntr;	/* HH_INIT 0 */
extern int  IRS_ROUTINE17_cntr;	/* HH_INIT 0 */
extern int  IRS_ROUTINE18_cntr;	/* HH_INIT 0 */
extern int  IRS_ROUTINE19_cntr;	/* HH_INIT 0 */
extern int  IRS_ROUTINE20_cntr;	/* HH_INIT 0 */
#endif

extern int    ifhgfb  ;
extern int    hgiter  ;
extern int    pdviter ;
extern int    qmode   ;
extern int    nditer  ;
extern double xquad   ;
extern double qlin    ;
extern double qprlx   ;
extern double qneg    ;
extern double hgfrac  ;
extern double hgheat  ;
extern double qdvfrac ;
extern double srcfi   ;
extern double srcfe   ;

extern int neos  ;
extern int neosx ;
extern double sndmin ;
extern double tscale ;
extern int ioneq ;
extern int ifconvert ;

extern int ifdynspec ;  
extern int nspec ;      

extern int nbq  ;
extern int nbqx ;

extern double sbc ;
extern int    planckwt ;

extern double tfloor ;

extern int    kapsav ;
extern double lphot  ;
extern double lphot1 ;
extern double lphot2 ;
extern int    npbin  ;
extern int    rdifcgmd ;
extern double rdifeps  ;
extern double rdifepsx ;
extern int    rdifit   ;
extern int    edifit   ;
extern int    idifit   ;
extern int    rdifitn  ;
extern int    rdifitx  ;
extern int    rdifoutn ;
extern int    rdifoutx ;
extern int    radsubcycles ;
extern int    radsubcycles_max ;
extern double rdifloss ;
extern double rdifmiln ;
extern int    rdifmix  ;
extern double rflx     ;
extern double trcool   ;
extern double phifloor ;
extern double eifrac   ;
extern double ktfloor  ;

extern int irvoid ;
extern double denvoid ;
extern double ematvoid ;

extern double mass0 ;
extern double etot0 ;
extern double masstot ;
extern double xmomtot ;
extern double ymomtot ;
extern double zmomtot ;
extern double xmomtotp ;
extern double ymomtotp ;
extern double zmomtotp ;
extern double xmomtotn ;
extern double ymomtotn ;
extern double zmomtotn ;
extern double ketot   ;
extern double ietot   ;
extern double etot    ;
extern double petot   ;
extern double qdvtot  ;
extern double eleak   ;
extern double engsrc  ;
extern double eloss   ;
extern double echk    ;
extern double echkx   ;
extern double delag   ;
extern double deadv   ;
extern double tketot  ;
extern double dkeadv  ;
extern double dieadv  ;
extern double volumetot ;
extern double tnetot  ;
extern double dtnetot ;

extern int  child_io_off;       /* HH_INIT FALSE */
extern int  child_io_todir;     /* HH_INIT FALSE */
extern char child_outpath[256]; 

extern int  ifcomsummary;               /* HH_INIT FALSE */


extern int ifthreads ; 
extern int ifparallel ; 
extern int ifmpi ;	   /* HH_INIT FALSE */
extern int myid ;          /* HH_INIT 0 */
extern int ifcom ; 
extern int ifsewbnd ; 
extern int ifvsame ;
extern int vsame_max_id ; 
extern int warntime;
extern double com_physics_time; /* HH_INIT 0.0 */

extern int nbcx ;
extern int nbndx ;

extern int nsrc ;
extern int nsrcx ;

extern double tpmult ;


extern int ifkwgt ;    
extern double tkewgt ; 
extern double tkecut ;  

extern int noerrflag;			/* HH_INIT FALSE */
extern int debugflag;			/* HH_INIT FALSE */
extern int cycflag;                     /* HH_INIT FALSE */
extern int coredumpflag;		/* HH_INIT TRUE */

extern int ifbarrier ;                  /* HH_INIT 0 */

extern int gv_alldump;			/* HH_INIT TRUE */

extern int terry_trace_flag; 		/* HH_INIT FALSE */

extern double gv_maxdouble; /* HH_INIT  1e+300  */
extern double gv_mindouble; /* HH_INIT  -(1e+300) */

extern char **gv_int_varlist;		/* HH_INIT NULL */
extern char **gv_dbl_varlist;		/* HH_INIT NULL */
extern int    gv_int_varlist_size;	/* HH_INIT 0 */
extern int    gv_dbl_varlist_size;	/* HH_INIT 0 */

extern char *gv_errmsg_DBAddOption;         /* HH_INIT "DBAddOption failed" */
extern char *gv_errmsg_DBClearOptlist;      /* HH_INIT "DBClearOptlist failed" */
extern char *gv_errmsg_DBFreeOptlist;       /* HH_INIT "DBFreeOptlist failed" */
extern char *gv_errmsg_DBMkDir;             /* HH_INIT "DBMkDir failed" */
extern char *gv_errmsg_DBPutMaterial;       /* HH_INIT "DBPutMaterial failed" */
extern char *gv_errmsg_DBPutQuadmesh;       /* HH_INIT "DBPutQuadmesh failed" */
extern char *gv_errmsg_DBPutQuadvar1;       /* HH_INIT "DBPutQuadvar1 failed" */
extern char *gv_errmsg_DBReadVar;           /* HH_INIT "DBReadVar failed" */
extern char *gv_errmsg_DBSetDir;            /* HH_INIT "DBSetdir failed" */
extern char *gv_errmsg_DBGetDir;            /* HH_INIT "DBGetdir failed" */
extern char *gv_errmsg_DBWrite;             /* HH_INIT "DBWrite failed" */
extern char *gv_errmsg_DBPutCompoundarray;  /* HH_INIT "DBPutCompoundarray failed " */
extern char *gv_errmsg_DBGetCompoundarray;  /* HH_INIT "DBGetCompoundarray failed " */
extern char *gv_errmsg_DBOpen;              /* HH_INIT "DBOpen failed" */

extern char *gv_errmsg_rgst_read_struct;              /* HH_INIT "rgst_read_struct failed" */
extern char *gv_errmsg_rgst_read_struct_in_dir;       /* HH_INIT "rgst_read_struct_in_dir failed" */
extern char *gv_errmsg_rgst_write_struct;             /* HH_INIT "rgst_write_struct failed" */
extern char *gv_errmsg_rgst_write_struct_in_dir;      /* HH_INIT "rgst_write_structin_dir failed" */
extern char *gv_errmsg_rgst_write_linked_list;        /* HH_INIT "rgst_write_linked_list failed" */
extern char *gv_errmsg_rgst_write_linked_list_in_dir; /* HH_INIT "rgst_write_linked_list_in_dir failed" */
extern char *gv_errmsg_rgst_add_mult_attrs;           /* HH_INIT "rgst_add_mult_attrs failed" */
extern char *gv_errmsg_rgst_conv_enum_type_to_str;    /* HH_INIT "rgst_conv_enum_type_to_str failed" */
extern char *gv_errmsg_rgst_del_attrs_from_fields;    /* HH_INIT "rgst_del_attrs_from_fields failed" */
extern char *gv_errmsg_rgst_del_attr;                 /* HH_INIT "rgst_del_attr failed" */
extern char *gv_errmsg_rgst_add_attrs_to_fields;      /* HH_INIT "rgst_add_attrs_to_fields failed" */

extern char *logic_err;                    /* HH_INIT "LOGIC ERROR - tell programmer to see core" */
extern char *gv_errmsg_memory;             /* HH_INIT "ALLOT or other memory allocation routine returned NULL" */
extern char *gv_errmsg_not_null;           /* HH_INIT "Possible memory leak?  About to allocate memory to pointer that is not null" */
extern char *gv_errmsg_not_done;           /* HH_INIT "This section of code not completed yet, contact programmer" */

/*******************************************************************************
* END OF FILE
*******************************************************************************/
