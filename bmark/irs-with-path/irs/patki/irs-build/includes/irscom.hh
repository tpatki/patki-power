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

int ComNodalZonal(int stepflag, char *kernel, int comflag);
int acumnm(int comflag);
int checkpara(int *argc, char * *argv, char * * *myargv);
int combarrier(void);
int combcast(void *inbuf, int len, int type, int sender);
int comlen(Boundary_t *bnd, int * *ndx_in, int com_type, int mesg_type);
int commpigather(void *buf, int count, int com_type, int data_type);
int commpigatherv(void *buf, int send_count, int *recv_count, int com_type, int data_type);
int comreduce(void *inbuf, int count, int op, int com_type, int data_type);
int facecom(int stepflag, int comflag);
int getdata(void *buf, int len, int type, int gblk, Boundary_t *bnd, int com_type);
int initcom(char *dmpname, int mdmpflag);
int postbuf(int bufnum, int comtype);
int putdata(void *buf, int len, int type, int gblk, Boundary_t *bnd, int com_type);
int qbnd(int stepflag, int comflag);
int radcom(int stepflag, int comflag);
int rbndcom(int stepflag, int comflag, int igrp);
int setstdout(int id);
int speccom_count(Boundary_t *mbnd, Boundary_t *bnd, int comtype, Domain_t *domain);
int varcom(int comflag);
int vsamecom(int stepflag, int comflag);
int waitbuf(int bufnum, int comtype, int number);
void allotcom(void);
void calculate_mappings(void);
void combuf_initlen(int stepflag);
void combuf_setlen(int comflag, int stepflag, int type, int gblk, int len);
void comcleanup(void);
void comgather(void *buf, char *name, NodeWindow_t *ndxin, int root);
void comlock(int nbaton);
void comsummary(double *timeproc);
void comunlock(int nbaton);
void comverify(void);
void decomp_free(void);
void decomp_new(int numBlocks, int numDomains);
void decomp_pack(int * *data, int *outlen);

#ifdef SILO
void decomp_read(DBfile *idbid, char *name, int ublk0, int gblk0);
void decomp_setdir(DBfile *idbid);
void decomp_write(DBfile *idbid, char *name);
#endif

void decomp_unpack(int *data, int len, int ublk0, int gblk0);
void freebuf(int bufnum, int comtype);
void freecom(void);
void freecombuf(Combuffer_t *combuffer);
void initbuf(int bufnum, int comtype);
void initbuforder(void);
void initcombufs(void);
void matcom_clear(Domain_t *domain, int mode, SpeciesFraction_t *specmf);
void matcom_final(void);
void matcom_init(int stepflag);
void matcom_setbnd(Boundary_t *mbnd, Boundary_t *bnd, int comtype, Domain_t *domain);
void newcombuf(Combuffer_t *combuffer, int size);
void setbuflen(int bufnum, int comtype, int datatype, int *len);
void setbuforder(int bufnum, int * *blk_order, int * *tag_order, int *len_order, int len_order_send);
void setumap(Domain_t *domain);
void setvsamegrp(void);
void setvsameorder(void);
void speccom_pack(double *buf, Boundary_t *mbnd, Boundary_t *bnd, Domain_t *domain, SpeciesFraction_t *specmf);
void speccom_unpack(double *buf, Boundary_t *mbnd, Boundary_t *bnd, Domain_t *domain, SpeciesFraction_t *specmf);
void swapcoords(void);
void varcom_bufinit(void);
void varcomset(void *data, int len, char *name, int var_type, int com_type, int com_op, int gblk);

#endif
/*******************************************************************************
* GLOBALS
*******************************************************************************/

MPI_Group *vsame_group;
MPI_Group global_group;

int num_procs =  1 ;
int hackblocking =  0 ;

double com_start_time;
double com_finish_time;
double com_barrier_time =  0.0 ;
double com_brdcst_time =  0.0 ;
double com_reduce_time =  0.0 ;
double com_start =  0.0 ;

int   *len_sendd; /* length of double data to be sent to each proc */
int   *len_recvd; /* length of double data to be recv'd from each proc */
int   *len_sendi; /* length of int data to be sent to each proc */
int   *len_recvi; /* length of int data to be recv'd from each proc */

pint  *hydro_tag_order =  NULL ;
                                /* tag of recv'd data from each proc          */
pint  *hydro_blk_order =  NULL ;
                                /* block number of recv'd data from each proc */
int   *hydro_len_order =  NULL ;
                                /* length of order info for each proc         */
int   hydro_len_order_send;  /* length of send order info              */

int *vsame_procs; 

Combuffer_t * combuf =  NULL ;
                              /* array of communication structs */

int curcombuf;         /* current communications buffer */

/*******************************************************************************
* END OF FILE
*******************************************************************************/
