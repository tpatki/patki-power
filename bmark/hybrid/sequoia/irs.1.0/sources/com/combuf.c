#include "irs.h"
#include "irscom.h"
#include "BlockMapping.h"
#include "FunctionTimer.h"
#include "Combuffer.h"
void initbuf(int bufnum, int comtype)
{
   int i;
   int size;
   size = combuf[bufnum].size;
   for (i = 0; i < size; i++ ) {
      if (comtype == COM_SEND) {
         combuf[bufnum].sendi_ptr[i] =  combuf[bufnum].sendi_buf[i] = NULL;
         combuf[bufnum].send_request[i+size] = MPI_REQUEST_NULL;
         if (combuf[bufnum].len_sendi[i]>0) {
            combuf[bufnum].sendi_buf[i] = 
                       MALLOT(int,combuf[bufnum].len_sendi[i]);
            combuf[bufnum].sendi_ptr[i] = combuf[bufnum].sendi_buf[i];
         }
         combuf[bufnum].sendd_ptr[i] =  combuf[bufnum].sendd_buf[i] = NULL;
         combuf[bufnum].send_request[i] = MPI_REQUEST_NULL;
         if (combuf[bufnum].len_sendd[i]>0) {
            combuf[bufnum].sendd_buf[i] = 
                       MALLOT(double,combuf[bufnum].len_sendd[i]);
            combuf[bufnum].sendd_ptr[i] = combuf[bufnum].sendd_buf[i];
         }
      }
      if (comtype == COM_RECV) {
         combuf[bufnum].recvi_ptr[i] =  combuf[bufnum].recvi_buf[i] = NULL;
         combuf[bufnum].recv_request[i+size] = MPI_REQUEST_NULL;
         if (combuf[bufnum].len_recvi[i]>0) {
            combuf[bufnum].recvi_buf[i] = 
                       MALLOT(int,combuf[bufnum].len_recvi[i]);
            combuf[bufnum].recvi_ptr[i] = combuf[bufnum].recvi_buf[i];
         }
         combuf[bufnum].recvd_ptr[i] =  combuf[bufnum].recvd_buf[i] = NULL;
         combuf[bufnum].recv_request[i] = MPI_REQUEST_NULL;
         if (combuf[bufnum].len_recvd[i]>0) {
            combuf[bufnum].recvd_buf[i] = 
                       MALLOT(double,combuf[bufnum].len_recvd[i]);
            combuf[bufnum].recvd_ptr[i] = combuf[bufnum].recvd_buf[i];
         }
      }
      if (comtype == COM_COLLECT) {
         combuf[bufnum].recvi_ptr[i] =  combuf[bufnum].recvi_buf[i] = NULL;
         if (combuf[bufnum].len_recvi[i]>0) {
            combuf[bufnum].recvi_buf[i] =
                       MALLOT(int,combuf[bufnum].len_recvi[i]);
            combuf[bufnum].recvi_ptr[i] = combuf[bufnum].recvi_buf[i];
         }
         combuf[bufnum].recvd_ptr[i] =  combuf[bufnum].recvd_buf[i] = NULL;
         if (combuf[bufnum].len_recvd[i]>0) {
            combuf[bufnum].recvd_buf[i] =
                       MALLOT(double,combuf[bufnum].len_recvd[i]);
            combuf[bufnum].recvd_ptr[i] = combuf[bufnum].recvd_buf[i];
         }
         combuf[bufnum].sendi_ptr[i] =  combuf[bufnum].sendi_buf[i] = NULL;
         if (combuf[bufnum].len_sendi[i]>0) {
            combuf[bufnum].sendi_buf[i] =
                       MALLOT(int,combuf[bufnum].len_sendi[i]);
            combuf[bufnum].sendi_ptr[i] = combuf[bufnum].sendi_buf[i];
         }
         combuf[bufnum].sendd_ptr[i] =  combuf[bufnum].sendd_buf[i] = NULL;
         if (combuf[bufnum].len_sendd[i]>0) {
            combuf[bufnum].sendd_buf[i] =
                       MALLOT(double,combuf[bufnum].len_sendd[i]);
            combuf[bufnum].sendd_ptr[i] = combuf[bufnum].sendd_buf[i];
         }
      }
   }
}
void allotcom( void )
{
   int i;
   int size;
   if (combuf != NULL) freecom();
   combuf = ALLOT(Combuffer_t,NCOMROUTINES+1);
   for (i=0;i<=NCOMROUTINES;i++) {
      combuf[i].size = num_procs;
   }
   combuf[VSAMECOM].size = vsame_max_id;
   size = MAX(num_procs,vsame_max_id);
   for (i=0;i<=NCOMROUTINES;i++) {
      newcombuf(&combuf[i],combuf[i].size);
   }
   len_sendi = ALLOT(int,size);
   len_recvi = ALLOT(int,size);
   len_sendd = ALLOT(int,size);
   len_recvd = ALLOT(int,size);
   hydro_blk_order = ALLOT(pint,num_procs);
   hydro_tag_order = ALLOT(pint,num_procs);
   hydro_len_order = ALLOT(int,num_procs);
   for (i=0;i<num_procs;i++) {
      if (i == myid ) {
         hydro_blk_order[i] = ALLOT(int,2*nbndx*nblk);
         hydro_tag_order[i] = ALLOT(int,2*nbndx*nblk);
      } else {
         hydro_blk_order[i] = ALLOT(int,nbndx*nblk);
         hydro_tag_order[i] = ALLOT(int,nbndx*nblk);
      }
   }
}
void freebuf(int bufnum, int comtype)
{
   int i;
   int size;
   size = combuf[bufnum].size;
   for (i = 0; i < size; i++ ) {
      if (comtype == COM_SEND) {
         combuf[bufnum].send_request[i+size] = MPI_REQUEST_NULL;
         if (combuf[bufnum].len_sendi[i]>0) {
            FREEMEM(combuf[bufnum].sendi_buf[i]);
         }
         combuf[bufnum].send_request[i] = MPI_REQUEST_NULL;
         if (combuf[bufnum].len_sendd[i]>0) {
            FREEMEM(combuf[bufnum].sendd_buf[i]);
         }
      }
      if (comtype == COM_RECV) {
         combuf[bufnum].recv_request[i+size] = MPI_REQUEST_NULL;
         if (combuf[bufnum].len_recvi[i]>0) {
            FREEMEM(combuf[bufnum].recvi_buf[i]);
         }
         combuf[bufnum].recv_request[i] = MPI_REQUEST_NULL;
         if (combuf[bufnum].len_recvd[i]>0) {
            FREEMEM(combuf[bufnum].recvd_buf[i]);
         }
      }
      if (comtype == COM_COLLECT) {
         if (combuf[bufnum].len_sendi[i]>0) {
            FREEMEM(combuf[bufnum].sendi_buf[i]);
         }
         if (combuf[bufnum].len_recvi[i]>0) {
            FREEMEM(combuf[bufnum].recvi_buf[i]);
         }
         if (combuf[bufnum].len_sendd[i]>0) {
            FREEMEM(combuf[bufnum].sendd_buf[i]);
         }
         if (combuf[bufnum].len_recvd[i]>0) {
            FREEMEM(combuf[bufnum].recvd_buf[i]);
         }
      }
   }
}
void freecombuf (Combuffer_t* combuffer)
{
   if (combuffer != NULL) {
     FREEMEM(combuffer->proc);
     FREEMEM(combuffer->len_sendi);
     FREEMEM(combuffer->len_sendd);
     FREEMEM(combuffer->len_recvi);
     FREEMEM(combuffer->len_recvd);
     FREEMEM(combuffer->sendi_buf);
     FREEMEM(combuffer->sendd_buf);
     FREEMEM(combuffer->recvi_buf);
     FREEMEM(combuffer->recvd_buf);
     FREEMEM(combuffer->sendi_ptr);
     FREEMEM(combuffer->sendd_ptr);
     FREEMEM(combuffer->recvi_ptr);
     FREEMEM(combuffer->recvd_ptr);
     FREEMEM(combuffer->blk_order);
     FREEMEM(combuffer->tag_order);
     FREEMEM(combuffer->len_order);
     FREEMEM(combuffer->comtimer);
     FREEMEM(combuffer->send_request);
     FREEMEM(combuffer->recv_request);
     FREEMEM(combuffer->send_status);
     FREEMEM(combuffer->recv_status);
     FREEMEM(combuffer->comm);
   }
}
void initbuforder(void)
{
   int iblk;
   int gblk;
   int ibc;
   int ibc_out;
   int proc;
   int count;
   MPI_Status status;
   for (proc = 0; proc < num_procs; proc++) {
      hydro_len_order[proc] = 0;
   }
   count = 0;
   for (iblk=0;iblk<nblk;iblk++) {
      for (ibc=0;ibc<domains[iblk].nbnd;ibc++) {
         gblk=domains[iblk].bnd[ibc].blk_send;
         if (gmap[gblk].proc == myid) {
            ibc_out=domains[iblk].bnd[ibc].bndnbc;
            count = hydro_len_order[myid];
            hydro_tag_order[myid][count]=ibc_out;
            hydro_blk_order[myid][count]=gblk;
            hydro_len_order[myid]++;
         }
      }
   }
   hydro_len_order_send = 0;
   for (iblk=0;iblk<nblk;iblk++) {
      for (ibc=0;ibc<domains[iblk].nbnd;ibc++) {
         gblk=domains[iblk].bnd[ibc].blk_send;
         proc=gmap[gblk].proc;
         count = hydro_len_order[myid]+hydro_len_order_send ;
         hydro_tag_order[myid][count]=ibc;
         hydro_blk_order[myid][count]=domains[iblk].gblk;
         hydro_len_order_send++ ;
         if (proc != myid ) {
            ibc_out=domains[iblk].bnd[ibc].bndnbc;
            count = hydro_len_order[proc];
            hydro_tag_order[proc][count]=ibc_out;
            hydro_blk_order[proc][count]=gblk;
            hydro_len_order[proc]++;
         }
      }
   }
   for (proc = 0; proc < num_procs; proc++) {
      if (proc != myid) {
         MPI_Send_Wrapper(&hydro_len_order[proc],1, MPI_INT, proc, myid, 
                          MPI_COMM_WORLD);
         if (hydro_len_order[proc]>0) {
            MPI_Send_Wrapper(hydro_tag_order[proc],hydro_len_order[proc],
                          MPI_INT, proc, myid, MPI_COMM_WORLD);
            MPI_Send_Wrapper(hydro_blk_order[proc],hydro_len_order[proc],
                          MPI_INT, proc, myid, MPI_COMM_WORLD);
         }
      }
   }
   for (proc = 0; proc < num_procs; proc++) {
      if (proc != myid) {
         MPI_Recv_Wrapper(&hydro_len_order[proc],1, MPI_INT, proc, proc, 
                          MPI_COMM_WORLD,&status);
         if (hydro_len_order[proc]>0) {
            MPI_Recv_Wrapper(hydro_tag_order[proc],hydro_len_order[proc],
                          MPI_INT, proc, proc, MPI_COMM_WORLD,&status);
            MPI_Recv_Wrapper(hydro_blk_order[proc],hydro_len_order[proc],
                          MPI_INT, proc, proc, MPI_COMM_WORLD,&status);
         }
      }
   }
}
void newcombuf (Combuffer_t* combuffer, int size)
{
   int i;
   combuffer->size = size;
   combuffer->proc = ALLOT(int,size);
   combuffer->len_sendi = ALLOT(int,size);
   combuffer->len_sendd = ALLOT(int,size);
   combuffer->len_recvi = ALLOT(int,size);
   combuffer->len_recvd = ALLOT(int,size);
   for (i=0;i<size;i++) {
      combuffer->len_sendi[i] = 0;
      combuffer->len_sendd[i] = 0;
      combuffer->len_recvi[i] = 0;
      combuffer->len_recvd[i] = 0;
   }
   combuffer->sendi_buf = ALLOT(pint,size);
   combuffer->sendi_ptr = ALLOT(pint,size);
   combuffer->recvi_buf = ALLOT(pint,size);
   combuffer->recvi_ptr = ALLOT(pint,size);
   combuffer->sendd_buf = ALLOT(pdouble,size);
   combuffer->sendd_ptr = ALLOT(pdouble,size);
   combuffer->recvd_buf = ALLOT(pdouble,size);
   combuffer->recvd_ptr = ALLOT(pdouble,size);
   combuffer->blk_order = ALLOT(pint,size);
   combuffer->tag_order = ALLOT(pint,size);
   combuffer->len_order = ALLOT(int,size);
   combuffer->send_request = ALLOT(MPI_Request,2*size);
   combuffer->recv_request = ALLOT(MPI_Request,2*size);
   combuffer->send_status = ALLOT(MPI_Status,2*size);
   combuffer->recv_status = ALLOT(MPI_Status,2*size);
   combuffer->comtimer = ALLOT(double,COM_NCALL_FLGS+1);
   for (i=0;i<=COM_NCALL_FLGS;i++) {
      combuffer->comtimer[i] = 0.0;
   }
   combuffer->comm = ALLOT(MPI_Comm,size);
}
int postbuf (int bufnum, int comtype)
{
   int i,j;
   int error = 0;
   int proc;
   int len;
   int lenr;
   int lens;
   int tag;
   int size;
   int* idata;
   int* idata_out;
   int* idatar;
   int* idatas;
   double* ddata;
   double* ddatar;
   double* ddatas;
   double* ddata_out;
   MPI_Request request;
   MPI_Comm comm;
   tag = combuf[bufnum].mesgtag;
   size = combuf[bufnum].size;
   for (i = 0; i < size; i++) {
      comm = combuf[bufnum].comm[i];
      proc = combuf[bufnum].proc[i];
      if (comtype == COM_SEND) {
         len = combuf[bufnum].len_sendi[i];
         idata = combuf[bufnum].sendi_buf[i];
         if (( len > 0) && (proc != myid)) {
            error += MPI_Isend_Wrapper(idata,len,MPI_INT,proc,tag, comm,&request);
            combuf[bufnum].send_request[i+size] = request;
         } else if ((len > 0) && (proc == myid)) {
            idata_out = combuf[bufnum].recvi_buf[i];
            for (j = 0; j < len; j++) {
               idata_out[j] = idata[j];
            }
         }
         len = combuf[bufnum].len_sendd[i];
         ddata = combuf[bufnum].sendd_buf[i];
         if ((len > 0) &&(proc != myid)) {
            error += MPI_Isend_Wrapper(ddata,len,MPI_DOUBLE,proc,tag, comm,&request);
            combuf[bufnum].send_request[i] = request;
         } else if ((len > 0)&&(proc == myid)) {
            ddata_out = combuf[bufnum].recvd_buf[i];
            for (j = 0; j < len; j++) {
               ddata_out[j]=ddata[j];
            }
         }
      }
      if (comtype == COM_RECV) {
         len = combuf[bufnum].len_recvi[i];
         idata = combuf[bufnum].recvi_buf[i];
         if ((len > 0) && (proc != myid)) {
            error += MPI_Irecv_Wrapper(idata,len,MPI_INT,proc,tag, comm,&request);
            combuf[bufnum].recv_request[i+size] = request;
         }
         len = combuf[bufnum].len_recvd[i];
         ddata = combuf[bufnum].recvd_buf[i];
         if ((len > 0) && (proc != myid)) {
            error += MPI_Irecv_Wrapper(ddata,len,MPI_DOUBLE,proc,tag, comm,&request);
            combuf[bufnum].recv_request[i] = request;
         }
      }
      if (comtype == COM_COLLECT) {
         lenr = combuf[bufnum].len_recvi[i];
         lens = combuf[bufnum].len_sendi[i];
         idatar = combuf[bufnum].recvi_buf[i];
         idatas = combuf[bufnum].sendi_buf[i];
         if ( lens > 0) {
            error += MPI_Allreduce_Wrapper(idatas,idatar,lens,MPI_INT,MPI_SUM,comm);
         }
         lenr = combuf[bufnum].len_recvd[i];
         lens = combuf[bufnum].len_sendd[i];
         ddatar = combuf[bufnum].recvd_buf[i];
         ddatas = combuf[bufnum].sendd_buf[i];
         if (lens > 0) {
            error += MPI_Allreduce_Wrapper(ddatas,ddatar,lens,MPI_DOUBLE,MPI_SUM,comm);
         }
      }
   }
   if ((comtype == COM_RECV) && (ifparallel) && (ifbarrier)) {
      combarrier();
   }
   return(error);
}
void setbuflen(int bufnum, int comtype, int datatype, int* len)
{
   int i;
   int size;
   size = combuf[bufnum].size;
   if (comtype == COM_SEND) {
      if (datatype == COM_INT) {
         for (i = 0; i < size; i++ ) {
            combuf[bufnum].len_sendi[i]=len[i];
         } 
      } 
      if (datatype == COM_DOUBLE) {
         for (i = 0; i < size; i++ ) {
            combuf[bufnum].len_sendd[i]=len[i];
         } 
      } 
   }
   if (comtype == COM_RECV) {
      if (datatype == COM_INT) {
         for (i = 0; i < size; i++ ) {
            combuf[bufnum].len_recvi[i]=len[i];
         } 
      } 
      if (datatype == COM_DOUBLE) {
         for (i = 0; i < size; i++ ) {
            combuf[bufnum].len_recvd[i]=len[i];
         } 
      } 
   }
}
void setbuforder(int bufnum, int** blk_order, int** tag_order, int* len_order, 
                 int len_order_send)
{
   int i;
   combuf[bufnum].len_order_send = len_order_send;
   for (i = 0; i < combuf[bufnum].size; i++ ) {
      combuf[bufnum].blk_order[i] = blk_order[i];
      combuf[bufnum].tag_order[i] = tag_order[i];
      combuf[bufnum].len_order[i] = len_order[i];
   }
}
int waitbuf(int bufnum, int comtype, int number)
{
   int index;
   int error=0;
   int len;
   int size;
   int waitnext;
   int waitnode;
   MPI_Status *status;
   MPI_Status status_temp;
   MPI_Request *request;
   waitnext = 0;
   if (comtype == COM_WAIT_RECV) {
      request = combuf[bufnum].recv_request;
      status = combuf[bufnum].recv_status;
   } 
   if (comtype == COM_WAIT_SEND) {
      request = combuf[bufnum].send_request;
      status = combuf[bufnum].send_status;
   } 
   size = combuf[bufnum].size;
   len = 2*size;
   if ((!ifparallel) || (number == COM_ONE)) {
      return(myid);
   }
   if (number == COM_ANY) {
      error += MPI_Waitany_Wrapper(len,request,&index,&status_temp);
      if (index == MPI_UNDEFINED) {
	 index = -1;
      } else if (index >= size) {
         index = index - size; 
         if (request[index] != MPI_REQUEST_NULL) {
            waitnext = 1;
            waitnode = index;
         }
      } else if (index <= size) {
         if (request[index+size] != MPI_REQUEST_NULL) {
            waitnext = 1;
            waitnode = index + size;
         }
      }
      if (waitnext) {
         error += MPI_Wait_Wrapper(&request[waitnode], &status_temp);
      }
   }
   if (number == COM_ALL) {
      error += MPI_Waitall_Wrapper(len,request,status);
      index = error;
   }
   return(index);
}
#define ZEROARRAYS(size) \
   for (i=0;i<size;i++) { \
      len_sendd[i] = 0; \
      len_sendi[i] = 0; \
      len_recvd[i] = 0; \
      len_recvi[i] = 0; \
   }
void initcombufs(void)
{
   int i;
   int stepflag;
   ZEROARRAYS(num_procs) ;
   for (i=0;i<num_procs;i++) combuf[QBND].proc[i] = i; 
   qbnd(0,COM_SET_SIZE_DOUBLE);
   qbnd(0,COM_SET_SIZE_INT);
   setbuflen(QBND,COM_SEND,COM_INT,len_sendi);
   setbuflen(QBND,COM_SEND,COM_DOUBLE,len_sendd);
   setbuflen(QBND,COM_RECV,COM_INT,len_recvi);
   setbuflen(QBND,COM_RECV,COM_DOUBLE,len_recvd);
   setbuforder(QBND, hydro_blk_order, hydro_tag_order, hydro_len_order, 
                     hydro_len_order_send);
   combuf[QBND].mesgtag = QBND;
   for (i=0;i<num_procs;i++) combuf[QBND].comm[i] = MPI_COMM_WORLD;
   strcpy(combuf[QBND].bufname,"qbnd");

   ZEROARRAYS(num_procs) ;
   for (i=0;i<num_procs;i++) combuf[ACUMNM].proc[i] = i; 
   acumnm(COM_SET_SIZE_DOUBLE);
   acumnm(COM_SET_SIZE_INT);
   setbuflen(ACUMNM,COM_SEND,COM_INT,len_sendi);
   setbuflen(ACUMNM,COM_SEND,COM_DOUBLE,len_sendd);
   setbuflen(ACUMNM,COM_RECV,COM_INT,len_recvi);
   setbuflen(ACUMNM,COM_RECV,COM_DOUBLE,len_recvd);
   setbuforder(ACUMNM, hydro_blk_order, hydro_tag_order, hydro_len_order, 
                     hydro_len_order_send);
   combuf[ACUMNM].mesgtag = ACUMNM;
   for (i=0;i<num_procs;i++) combuf[ACUMNM].comm[i] = MPI_COMM_WORLD;
   strcpy(combuf[ACUMNM].bufname,"acumnm");
   for (stepflag=RADCOM0; stepflag <= RADCOM2 ; stepflag++ ) {
      ZEROARRAYS(num_procs) ;
      for (i=0;i<num_procs;i++) combuf[stepflag].proc[i] = i; 
      radcom(stepflag,COM_SET_SIZE_DOUBLE) ;
      radcom(stepflag,COM_SET_SIZE_INT) ;
      setbuflen(stepflag,COM_SEND,COM_INT,len_sendi) ;
      setbuflen(stepflag,COM_SEND,COM_DOUBLE,len_sendd) ;
      setbuflen(stepflag,COM_RECV,COM_INT,len_recvi) ;
      setbuflen(stepflag,COM_RECV,COM_DOUBLE,len_recvd) ;
      setbuforder(stepflag, hydro_blk_order, hydro_tag_order, hydro_len_order,
		  hydro_len_order_send) ;
      combuf[stepflag].mesgtag = stepflag ;
      for (i=0;i<num_procs;i++) combuf[stepflag].comm[i] = MPI_COMM_WORLD;
      sprintf(combuf[stepflag].bufname,"radcom%i",stepflag-RADCOM0) ;
   }
   if (ifdivgrad != 4){
     for (stepflag=RBNDCOM0; stepflag <= RBNDCOM8 ; stepflag++ ) {
       ZEROARRAYS(num_procs) ;
       for (i=0;i<num_procs;i++) combuf[stepflag].proc[i] = i; 
       rbndcom(stepflag, COM_SET_SIZE_DOUBLE, 0) ;
       rbndcom(stepflag, COM_SET_SIZE_INT, 0) ;
       setbuflen(stepflag,COM_SEND,COM_INT,len_sendi) ;
       setbuflen(stepflag,COM_SEND,COM_DOUBLE,len_sendd) ;
       setbuflen(stepflag,COM_RECV,COM_INT,len_recvi) ;
       setbuflen(stepflag,COM_RECV,COM_DOUBLE,len_recvd) ;
       setbuforder(stepflag, hydro_blk_order, hydro_tag_order, hydro_len_order,
		   hydro_len_order_send) ;
       combuf[stepflag].mesgtag = stepflag ;
       for (i=0;i<num_procs;i++) combuf[stepflag].comm[i] = MPI_COMM_WORLD;
       sprintf(combuf[stepflag].bufname,"rbndcom%i",stepflag-RBNDCOM0) ;
     }
   } else {
     for (stepflag=RBNDCOM1; stepflag <= RBNDCOM9 ; stepflag++ ) {
       char *name = "RBNDCOM";
       ZEROARRAYS(num_procs) ;
       for (i=0;i<num_procs;i++) combuf[stepflag].proc[i] = i; 
       ComNodalZonal(stepflag, name, COM_SET_SIZE_DOUBLE) ;
       ComNodalZonal(stepflag, name, COM_SET_SIZE_INT) ;
       setbuflen(stepflag,COM_SEND,COM_INT,len_sendi) ;
       setbuflen(stepflag,COM_SEND,COM_DOUBLE,len_sendd) ;
       setbuflen(stepflag,COM_RECV,COM_INT,len_recvi) ;
       setbuflen(stepflag,COM_RECV,COM_DOUBLE,len_recvd) ;
       setbuforder(stepflag, hydro_blk_order, hydro_tag_order, hydro_len_order,
		   hydro_len_order_send) ;
       combuf[stepflag].mesgtag = stepflag ;
       for (i=0;i<num_procs;i++) combuf[stepflag].comm[i] = MPI_COMM_WORLD;
       sprintf(combuf[stepflag].bufname,"rbndcom%i",stepflag-RBNDCOM0) ;
     }
   }
   ZEROARRAYS(vsame_max_id) ;
   for (i=0;i<vsame_max_id;i++) combuf[VSAMECOM].proc[i] = i; 
   vsamecom(VSAMECOM0,COM_SET_SIZE_DOUBLE);
   vsamecom(VSAMECOM0,COM_SET_SIZE_INT);
   setbuflen(VSAMECOM,COM_SEND,COM_INT,len_sendi);
   setbuflen(VSAMECOM,COM_SEND,COM_DOUBLE,len_sendd);
   setbuflen(VSAMECOM,COM_RECV,COM_INT,len_recvi);
   setbuflen(VSAMECOM,COM_RECV,COM_DOUBLE,len_recvd);
   combuf[VSAMECOM].mesgtag = VSAMECOM;
   if ((ifparallel) && (ifvsame)) {
      setvsamegrp();
   }
   strcpy(combuf[VSAMECOM].bufname,"vsamecom");
   for (stepflag=FACECOM0; stepflag <= FACECOM2 ; stepflag++ ) {
     ZEROARRAYS(num_procs) ;
     for (i=0;i<num_procs;i++) combuf[stepflag].proc[i] = i;
     facecom(stepflag,COM_SET_SIZE_DOUBLE);
     facecom(stepflag,COM_SET_SIZE_INT);
     setbuflen(stepflag,COM_SEND,COM_INT,len_sendi);
     setbuflen(stepflag,COM_SEND,COM_DOUBLE,len_sendd);
     setbuflen(stepflag,COM_RECV,COM_INT,len_recvi);
     setbuflen(stepflag,COM_RECV,COM_DOUBLE,len_recvd);
     setbuforder(stepflag, hydro_blk_order, hydro_tag_order, hydro_len_order,
		 hydro_len_order_send);
     combuf[stepflag].mesgtag = stepflag;
     combuf[stepflag].comm[0] = MPI_COMM_WORLD;
     for (i=0;i<num_procs;i++) combuf[stepflag].comm[i] = MPI_COMM_WORLD;
     sprintf(combuf[stepflag].bufname,"facecom%i",stepflag-FACECOM0);   
   }
}
#undef ZEROARRAYS
void freecom( void )
{
   int i;
    for (i = 0; i <= NCOMROUTINES; i++) {
       if (combuf != NULL) { freecombuf(&combuf[i]); }
    }
   FREEMEM(combuf);
   FREEMEM(len_sendi);
   FREEMEM(len_recvi);
   FREEMEM(len_sendd);
   FREEMEM(len_recvd);
   for (i = 0; i < num_procs; i++) {
      if (hydro_blk_order != NULL) { FREEMEM(hydro_blk_order[i]); }
      if (hydro_tag_order != NULL) { FREEMEM(hydro_tag_order[i]); }
   }
   FREEMEM(hydro_blk_order);
   FREEMEM(hydro_tag_order);
   FREEMEM(hydro_len_order);
}
void combuf_initlen(int stepflag) {
   int proc;
   if (ifparallel) {
      for (proc = 0; proc < num_procs; proc++) {
         len_recvd[proc] = 0;
         len_recvi[proc] = 0;
         len_sendd[proc] = 0;
         len_sendi[proc] = 0;
      }
      setbuflen(stepflag,COM_SEND,COM_INT,len_sendi);
      setbuflen(stepflag,COM_SEND,COM_DOUBLE,len_sendd);
      setbuflen(stepflag,COM_RECV,COM_INT,len_recvi);
      setbuflen(stepflag,COM_RECV,COM_DOUBLE,len_recvd);
   }
}
void combuf_setlen(int comflag, int stepflag, int type, int gblk, int len) {
   int proc;
   proc = gmap[gblk].proc;
   if (comflag == COM_RECV) {
      if (type == COM_INT) {
         combuf[stepflag].len_recvi[proc] += len;
      } else {
         combuf[stepflag].len_recvd[proc] += len;
      } 
   } else if (comflag == COM_SEND) {
      if (type == COM_INT) {
         combuf[stepflag].len_sendi[proc] += len;
      } else {
         combuf[stepflag].len_sendd[proc] += len;
      } 
   }
}
