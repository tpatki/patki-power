#ifndef irscom_H
#define irscom_H

#include "pint.h"
#include "Boundary.h"
#include "Combuffer.h"
#include "SpeciesFraction.h"
#include "NodeList.h"

#define ZONE_INACTIVE   -1
#define ZONE_ACTIVE      1
#define ZONE_MIXED       2

#define COM_DOUBLE 		1
#define COM_CHAR 		2
#define COM_INT 		3
#define COM_SUM 		4
#define COM_MIN 		5
#define COM_MAX 		6
#define COM_OVR 		7
#define COM_NOOP 		8

#define COM_LAYER1N 		1
#define COM_LAYER1Z 		2
#define COM_LAYER1ZC 		3
#define COM_LAYER2N 		4
#define COM_LAYER2NC 		5
#define COM_LAYER2Z 		6
#define COM_LAYER_ALLN 		7
#define COM_LAYER_ALLZ 		8
#define COM_LAYER_CZ 		9
#define COM_LAYER_CN 	       10
#define COM_ACCUM 	       11
#define COM_ALL 	       13
#define COM_ANY 	       14
#define COM_ONE 	       15
#define COM_DIRECT             16
#define COM_DIRECT_ID 	       17

#define COM_RECV 	        1	
#define COM_SEND 	        2	
#define COM_WAIT_RECV 	        3
#define COM_WAIT_SEND 	        4
#define COM_COLLECT   	        5
#define COM_SET_SIZE_DOUBLE     6
#define COM_SET_SIZE_INT        7
#define COM_SET_SIZE            8
#define COM_SEND_RECV 	        9
#define COM_NCALL_FLGS         10 

#define QBND			1
#define ACUMNM			3
#define RADCOM0                 21
#define RADCOM1                 22
#define RADCOM2                 23
#define VSAMECOM                24
#define RBNDCOM0                25
#define RBNDCOM1                26
#define RBNDCOM2                27
#define RBNDCOM3                28
#define RBNDCOM4                29
#define RBNDCOM5                30
#define RBNDCOM6                31
#define RBNDCOM7                32
#define RBNDCOM8                33
#define RBNDCOM9                34
#define FACECOM0                43
#define FACECOM1                44
#define FACECOM2                45
#define VARCOM                  49   /* keep VARCOM as last label in list */

#define NCOMROUTINES		49   /* number of routine labels above */

#define VSAMECOM0		1
#define VSAMECOM1		2
#define VSAMECOM2		3

#define COM_LEN_1N_S(b) (b.len_nsend1)
#define COM_LEN_1N_R(b) (b.len_nrecv1)
#define COM_LEN_1Z_S(b) (b.len_zsend1)
#define COM_LEN_1Z_R(b) (b.len_zrecv1)
#define COM_LEN_1ZC_S(b) (b.len_zsend1 + b.len_zsendc)
#define COM_LEN_1ZC_R(b) (b.len_zrecv1 + b.len_zrecvc)
#define COM_LEN_ZC_S(b) (b.len_zsendc)
#define COM_LEN_ZC_R(b) (b.len_zrecvc)
#define COM_LEN_NC_S(b) (b.len_nsendc)
#define COM_LEN_NC_R(b) (b.len_nrecvc)
#define COM_LEN_2N_S(b) (b.len_nsend2 )
#define COM_LEN_2N_R(b) (b.len_nrecv2 )
#define COM_LEN_2NC_S(b) (b.len_nsend2 + b.len_nsendc )
#define COM_LEN_2NC_R(b) (b.len_nrecv2 + b.len_nrecvc )
#define COM_LEN_2Z_S(b) (b.len_zsend2)
#define COM_LEN_2Z_R(b) (b.len_zrecv2)
#define COM_LEN_ALLN_S(b) (b.len_nsend1 + b.len_nsend2 + b.len_nsendc)
#define COM_LEN_ALLZ_S(b) (b.len_zsend1 + b.len_zsend2 + b.len_zsendc)
#define COM_LEN_ALLN_R(b) (b.len_nrecv1 + b.len_nrecv2 + b.len_nrecvc)
#define COM_LEN_ALLZ_R(b) (b.len_zrecv1 + b.len_zrecv2 + b.len_zrecvc)

#define COM_NDX_1N_S(b) b.ndx_send
#define COM_NDX_1N_R(b) b.ndx_recv
#define COM_ZDX_1Z_S(b) b.zdx_send
#define COM_ZDX_1Z_R(b) b.zdx_recv
#define COM_ZDX_ZC_R(b) (b.zdx_recv + b.len_zrecv1)
#define COM_ZDX_ZC_S(b) (b.zdx_send + b.len_zsend1)
#define COM_ZDX_1ZC_R(b) b.zdx_recv
#define COM_ZDX_1ZC_S(b) b.zdx_send

#define COM_NDX_1Z_S(b) b.zdx_send
#define COM_NDX_1Z_R(b) b.zdx_recv
#define COM_NDX_ZC_R(b) (b.zdx_recv + b.len_zrecv1)
#define COM_NDX_ZC_S(b) (b.zdx_send + b.len_zsend1)
#define COM_NDX_1ZC_R(b) b.zdx_recv
#define COM_NDX_1ZC_S(b) b.zdx_send

#define COM_NDX_2N_S(b) (b.ndx_send + b.len_nsend1)
#define COM_NDX_2N_R(b) (b.ndx_recv + b.len_nrecv1)
#define COM_NDX_2NC_S(b) (b.ndx_send + b.len_nsend1)
#define COM_NDX_2NC_R(b) (b.ndx_recv + b.len_nrecv1)

#define COM_ZDX_2Z_S(b) (b.zdx_send + b.len_zsend1 + b.len_zsendc)
#define COM_ZDX_2Z_R(b) (b.zdx_recv + b.len_zrecv1 + b.len_zrecvc)
#define COM_ZDX_ALLZ_S(b) b.zdx_send
#define COM_ZDX_ALLZ_R(b) b.zdx_recv 

#define COM_NDX_2Z_S(b) (b.zdx_send + b.len_zsend1 + b.len_zsendc)
#define COM_NDX_2Z_R(b) (b.zdx_recv + b.len_zrecv1 + b.len_zrecvc)
#define COM_NDX_ALLZ_S(b) b.zdx_send
#define COM_NDX_ALLZ_R(b) b.zdx_recv 


#define COM_NDX_ALLN_S(b) b.ndx_send
#define COM_NDX_ALLN_R(b) b.ndx_recv 
#define COM_NDX_NC_S(b) (b.ndx_send + b.len_nsend1 + b.len_nsend2 )
#define COM_NDX_NC_R(b) (b.ndx_recv + b.len_nrecv1 + b.len_nrecv2 )

#define COM_ZDX_ZC_S(b) (b.zdx_send + b.len_zsend1)
#define COM_ZDX_ZC_R(b) (b.zdx_recv + b.len_zrecv1) 

#define COM_NDX_ZC_S(b) (b.zdx_send + b.len_zsend1)
#define COM_NDX_ZC_R(b) (b.zdx_recv + b.len_zrecv1) 

#define STARTTIMER(bufnum) \
    combuf[bufnum].starttime = MPI_Wtime_Wrapper();

#define STOPTIMER(bufnum,comtype) \
    combuf[bufnum].comtimer[comtype] += MPI_Wtime_Wrapper() - combuf[bufnum].starttime;

extern int ComNodalZonal(int stepflag, char *kernel, int comflag);
extern int acumnm(int comflag);
extern int checkpara(int *argc, char * *argv, char * * *myargv);
extern int combarrier(void);
extern int combcast(void *inbuf, int len, int type, int sender);
extern int comlen(Boundary_t *bnd, int * *ndx_in, int com_type, int mesg_type);
extern int commpigather(void *buf, int count, int com_type, int data_type);
extern int commpigatherv(void *buf, int send_count, int *recv_count, int com_type, int data_type);
extern int comreduce(void *inbuf, int count, int op, int com_type, int data_type);
extern int facecom(int stepflag, int comflag);
extern int getdata(void *buf, int len, int type, int gblk, Boundary_t *bnd, int com_type);
extern int initcom(char *dmpname, int mdmpflag);
extern int postbuf(int bufnum, int comtype);
extern int putdata(void *buf, int len, int type, int gblk, Boundary_t *bnd, int com_type);
extern int qbnd(int stepflag, int comflag);
extern int radcom(int stepflag, int comflag);
extern int rbndcom(int stepflag, int comflag, int igrp);
extern int setstdout(int id);
extern int speccom_count(Boundary_t *mbnd, Boundary_t *bnd, int comtype, Domain_t *domain);
extern int varcom(int comflag);
extern int vsamecom(int stepflag, int comflag);
extern int waitbuf(int bufnum, int comtype, int number);
extern void allotcom(void);
extern void calculate_mappings(void);
extern void combuf_initlen(int stepflag);
extern void combuf_setlen(int comflag, int stepflag, int type, int gblk, int len);
extern void comcleanup(void);
extern void comgather(void *buf, char *name, NodeWindow_t *ndxin, int root);
extern void comlock(int nbaton);
extern void comsummary(double *timeproc);
extern void comunlock(int nbaton);
extern void comverify(void);
extern void decomp_free(void);
extern void decomp_new(int numBlocks, int numDomains);
extern void decomp_pack(int * *data, int *outlen);

#ifdef SILO
extern void decomp_read(DBfile *idbid, char *name, int ublk0, int gblk0);
extern void decomp_setdir(DBfile *idbid);
extern void decomp_write(DBfile *idbid, char *name);
#endif

extern void decomp_unpack(int *data, int len, int ublk0, int gblk0);
extern void freebuf(int bufnum, int comtype);
extern void freecom(void);
extern void freecombuf(Combuffer_t *combuffer);
extern void initbuf(int bufnum, int comtype);
extern void initbuforder(void);
extern void initcombufs(void);
extern void matcom_clear(Domain_t *domain, int mode, SpeciesFraction_t *specmf);
extern void matcom_final(void);
extern void matcom_init(int stepflag);
extern void matcom_setbnd(Boundary_t *mbnd, Boundary_t *bnd, int comtype, Domain_t *domain);
extern void newcombuf(Combuffer_t *combuffer, int size);
extern void setbuflen(int bufnum, int comtype, int datatype, int *len);
extern void setbuforder(int bufnum, int * *blk_order, int * *tag_order, int *len_order, int len_order_send);
extern void setumap(Domain_t *domain);
extern void setvsamegrp(void);
extern void setvsameorder(void);
extern void speccom_pack(double *buf, Boundary_t *mbnd, Boundary_t *bnd, Domain_t *domain, SpeciesFraction_t *specmf);
extern void speccom_unpack(double *buf, Boundary_t *mbnd, Boundary_t *bnd, Domain_t *domain, SpeciesFraction_t *specmf);
extern void swapcoords(void);
extern void varcom_bufinit(void);
extern void varcomset(void *data, int len, char *name, int var_type, int com_type, int com_op, int gblk);

#endif
/*******************************************************************************
* GLOBALS
*******************************************************************************/

extern MPI_Group *vsame_group;
extern MPI_Group global_group;

extern int num_procs; /* HH_INIT 1 */
extern int hackblocking; /* HH_INIT 0 */

extern double com_start_time;
extern double com_finish_time;
extern double com_barrier_time; /* HH_INIT 0.0 */
extern double com_brdcst_time;  /* HH_INIT 0.0 */
extern double com_reduce_time;  /* HH_INIT 0.0 */
extern double com_start;        /* HH_INIT 0.0 */

extern int   *len_sendd; /* length of double data to be sent to each proc */
extern int   *len_recvd; /* length of double data to be recv'd from each proc */
extern int   *len_sendi; /* length of int data to be sent to each proc */
extern int   *len_recvi; /* length of int data to be recv'd from each proc */

extern pint  *hydro_tag_order;  /* HH_INIT NULL */
                                /* tag of recv'd data from each proc          */
extern pint  *hydro_blk_order;  /* HH_INIT NULL */
                                /* block number of recv'd data from each proc */
extern int   *hydro_len_order;  /* HH_INIT NULL */
                                /* length of order info for each proc         */
extern int   hydro_len_order_send;  /* length of send order info              */

extern int *vsame_procs; 

extern Combuffer_t * combuf;  /* HH_INIT NULL */
                              /* array of communication structs */

extern int curcombuf;         /* current communications buffer */

/*******************************************************************************
* END OF FILE
*******************************************************************************/
