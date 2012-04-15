#include "irs.h"
#include "BlockMapping.h"
#include "Boundary.h"
#include "FunctionTimer.h" 
#include "irscom.h"
#include "Hash.h"
struct VARCOM_DATA_ {
   char  name[MAXLINE];
   void* var_ptr; 
   int len;
   int var_type;
   int com_type;
   int com_op;
   struct VARCOM_DATA_ *next;
} ;
typedef struct VARCOM_DATA_ VARCOM_DATA;
struct NAME_LIST_ {
   char name[MAXLINE];
   struct NAME_LIST_ *next;
};
typedef struct NAME_LIST_ NAME_LIST;
static VARCOM_DATA *varcom_data;
static NAME_LIST   *varcom_names;
int varcom(int comflag)
{ 
   char *me = "varcom";
   char msg[MAXLINE];
   char hashname[MAXLINE];
   int i,ibc;
   int j;
   int gblk,gblk_in;
   int len;
   int iblk;
   int error;
   int proc;
   int var_type;
   int com_type;
   int com_op;
   int *ndx;
   int *flag;
   int *itemp;
   int *idata;
   int **flagspace;
   double *dtemp;
   double *ddata;
   void *data;
   Boundary_t *bnd;
   NAME_LIST *varcom_namesp;
   NAME_LIST *varcom_names_temp;
   VARCOM_DATA *varcom_datap;
   VARCOM_DATA *varcom_data_temp;
   error = 0;
   len = 0;
   if  (!ifcom)  {
      return(error);
   }
   STARTTIMER(VARCOM) ;
   curcombuf = VARCOM;
   if (comflag == COM_SEND_RECV) {
      initbuf(VARCOM,COM_RECV);
      initbuf(VARCOM,COM_SEND);
      postbuf(VARCOM,COM_RECV);
      for (j = 0;j < hydro_len_order_send; j++) {
         ibc = hydro_tag_order[myid][j+hydro_len_order[myid]];
         gblk = hydro_blk_order[myid][j+hydro_len_order[myid]];
         iblk = gmap[gblk].lblk;
         bnd = domains[iblk].bnd;
         gblk_in = bnd[ibc].blk_send;
         varcom_namesp = varcom_names;
         while (varcom_namesp != NULL) {
            sprintf(hashname,"varcom_blk%03d_%s",gblk, varcom_namesp->name);
            varcom_datap = (VARCOM_DATA *)hash_lookup_obj(hashname,gv_hash_tbl);
            data = varcom_datap->var_ptr;
            len = varcom_datap->len;
            com_type = varcom_datap->com_type;
            var_type = varcom_datap->var_type;
            if (com_type != COM_DIRECT) {
               putdata(data,len,var_type,gblk_in,&bnd[ibc],com_type);
            } else {
               len = bnd[ibc].buf_int[0];
               if (var_type == COM_INT) {
                  data = (void *) (&bnd[ibc].buf_int[1]);
                  putdata(data,len,var_type,gblk_in,&bnd[ibc],com_type);
               } else if (var_type == COM_DOUBLE) {
                  data = (void *) bnd[ibc].buf_double;
                  putdata(data,len,var_type,gblk_in,&bnd[ibc],com_type);
               } 
            }
            varcom_namesp = varcom_namesp->next;
         }
      }
      postbuf(VARCOM,COM_SEND);
      waitbuf(VARCOM,COM_WAIT_SEND,COM_ALL);
      freebuf(VARCOM,COM_SEND);
      waitbuf(VARCOM,COM_WAIT_RECV,COM_ALL);
      flagspace = MALLOT(pint,nblk);
      for (iblk = 0; iblk < nblk; iblk++) {
         flagspace[iblk] = MALLOT(int,domains[iblk].nnalls);
         gblk = domains[iblk].gblk;
         flag = flagspace[iblk];
         for (i = 0; i < domains[iblk].nnalls; i++) {
            flag[i] = gblk;
         }
      }
      for (proc = 0; proc < num_procs; proc++ ) {
         for (i = 0; i < hydro_len_order[proc]; i++) {
            ibc = hydro_tag_order[proc][i];
            gblk = hydro_blk_order[proc][i];
            iblk = gmap[gblk].lblk;
            bnd = domains[iblk].bnd;
            gblk_in = bnd[ibc].blk_send;
            flag = flagspace[iblk];
            varcom_namesp = varcom_names;
            while (varcom_namesp != NULL) {
               sprintf(hashname,"varcom_blk%03d_%s",gblk, varcom_namesp->name);
               varcom_datap = (VARCOM_DATA *)hash_lookup_obj(hashname,gv_hash_tbl);
               data = varcom_datap->var_ptr;
               len = varcom_datap->len;
               com_type = varcom_datap->com_type;
               var_type = varcom_datap->var_type;
               com_op   = varcom_datap->com_op;
               if ((com_type == COM_ACCUM) || (com_op != COM_NOOP)) {
                  if (var_type == COM_DOUBLE) {
                     ddata = (double *) varcom_datap->var_ptr;
                     len = comlen(&bnd[ibc], &ndx, com_type, COM_RECV);
                     dtemp = MALLOT(double,len);
                     getdata(dtemp,len,var_type,gblk_in,&bnd[ibc],COM_DIRECT);
                     if ((com_type == COM_ACCUM) || (com_op == COM_SUM)) {
                        for (j = 0; j < len; j++) {
                           ddata[ndx[j]] += dtemp[j];
                        }
                     } else if (com_op == COM_MAX) {
                        for (j = 0; j < len; j++) {
                           ddata[ndx[j]] = MAX(dtemp[j],ddata[ndx[j]]);
                        }
                     } else if (com_op == COM_MIN) {
                        for (j = 0; j < len; j++) {
                           ddata[ndx[j]] = MIN(dtemp[j],ddata[ndx[j]]);
                        }
                     } else if (com_op == COM_OVR) {
                        for (j = 0; j < len; j++) {
                           if (gblk_in >= flag[ndx[j]]) {
                              ddata[ndx[j]] = dtemp[j];
                              flag[ndx[j]] = gblk_in;
                           }
                        }
                     } 
                     FREEMEM(dtemp);
                  } else if (var_type == COM_INT) {
                     idata = (int *) varcom_datap->var_ptr;
                     len = comlen(&bnd[ibc], &ndx, com_type, COM_RECV);
                     itemp = MALLOT(int,len);
                     getdata(itemp,len,var_type,gblk_in,&bnd[ibc],COM_DIRECT);
                     if ((com_type == COM_ACCUM) || (com_op == COM_SUM)) {
                        for (j = 0; j < len; j++) {
                           idata[ndx[j]] += itemp[j];
                        }
                     } else if (com_op == COM_MAX) {
                        for (j = 0; j < len; j++) {
                           idata[ndx[j]] = MAX(itemp[j],idata[ndx[j]]);
                        }
                     } else if (com_op == COM_MIN) {
                        for (j = 0; j < len; j++) {
                           idata[ndx[j]] = MIN(itemp[j],idata[ndx[j]]);
                        }
                     } else if (com_op == COM_OVR) {
                        for (j = 0; j < len; j++) {
                           if (gblk_in >= flag[ndx[j]]) {
                              idata[ndx[j]] = itemp[j];
                              flag[ndx[j]] = gblk_in;
                           }
                        }
                     } 
                     FREEMEM(itemp);
                  }
               } else if (com_type == COM_DIRECT) {
                  len = bnd[ibc].buf_int[0];
                  if (var_type == COM_INT) {
                     getdata(bnd[ibc].buf_int,len,var_type,gblk_in,&bnd[ibc],
		             com_type);
                  } else if (var_type == COM_DOUBLE) {
                     getdata(bnd[ibc].buf_double,len,var_type,gblk_in,&bnd[ibc],
		             com_type);
                  } 
               } else {
                  getdata(data,len,var_type,gblk_in,&bnd[ibc],com_type);
               } 
               varcom_namesp = varcom_namesp->next;
            }
         }
      }
      freebuf(VARCOM,COM_RECV);
      for (iblk = 0; iblk < nblk; iblk++) {
         FREEMEM(flagspace[iblk]);
      }
      FREEMEM(flagspace);
      for (iblk = 0; iblk < nblk; iblk++) {
         gblk = domains[iblk].gblk;
         varcom_namesp = varcom_names;
         while (varcom_namesp != NULL) {
            sprintf(hashname,"varcom_blk%03d_%s",gblk,
                                                      varcom_namesp->name);
            hash_del(hashname,gv_hash_tbl);
            varcom_namesp = varcom_namesp->next;
         }
      }
      varcom_namesp = varcom_names;
      while (varcom_namesp != NULL) {
         varcom_names_temp = varcom_namesp->next;
         FREEMEM(varcom_namesp);
         varcom_namesp = varcom_names_temp;
      }
      varcom_names = NULL;
      varcom_datap = varcom_data;
      while (varcom_datap != NULL) {
         varcom_data_temp = varcom_datap->next;
         FREEMEM(varcom_datap);
         varcom_datap = varcom_data_temp;
      }
      varcom_data = NULL;
   } else if (comflag == COM_SET_SIZE) {
      for (proc = 0; proc < num_procs; proc++) {
         len_sendd[proc] = 0;
         len_recvd[proc] = 0;
         len_sendi[proc] = 0;
         len_recvi[proc] = 0;
      }
      for (j = 0;j < hydro_len_order_send; j++) {
         ibc = hydro_tag_order[myid][j+hydro_len_order[myid]];
         gblk = hydro_blk_order[myid][j+hydro_len_order[myid]];
         iblk = gmap[gblk].lblk;
         bnd  = domains[iblk].bnd;
         gblk_in = bnd[ibc].blk_send;
         proc = gmap[gblk_in].proc;
         varcom_namesp = varcom_names;
         while (varcom_namesp != NULL) {
            sprintf(hashname,"varcom_blk%03d_%s",gblk, varcom_namesp->name);
            varcom_datap = (VARCOM_DATA *)hash_lookup_obj(hashname,gv_hash_tbl);
            data = varcom_datap->var_ptr;
            len = varcom_datap->len;
            com_type = varcom_datap->com_type;
            var_type = varcom_datap->var_type;
            if (var_type == COM_DOUBLE) {
               if (com_type != COM_DIRECT) {
                  len_sendd[proc] += comlen(&bnd[ibc], &ndx, com_type,COM_SEND);
                  len_recvd[proc] += comlen(&bnd[ibc], &ndx, com_type,COM_RECV);
               } else {
                  len_sendd[proc] += bnd[ibc].buf_int[0];
                  len_recvd[proc] += bnd[ibc].buf_int[0];
               }
            } else if (var_type == COM_INT) {
               if (com_type != COM_DIRECT) {
                  len_sendi[proc] += comlen(&bnd[ibc], &ndx, com_type,COM_SEND);
                  len_recvi[proc] += comlen(&bnd[ibc], &ndx, com_type,COM_RECV);
               } else {
                  len_sendi[proc] += bnd[ibc].buf_int[0];
                  len_recvi[proc] += bnd[ibc].buf_int[0];
               }
            }
            varcom_namesp = varcom_namesp->next;
         }
      }
      setbuflen(VARCOM,COM_SEND,COM_INT,len_sendi);
      setbuflen(VARCOM,COM_SEND,COM_DOUBLE,len_sendd);
      setbuflen(VARCOM,COM_RECV,COM_INT,len_recvi);
      setbuflen(VARCOM,COM_RECV,COM_DOUBLE,len_recvd);
   }
   STOPTIMER(VARCOM,comflag) ;
   return(error);
}
void varcomset(void *data, int len, char *name, int var_type, 
               int com_type, int com_op, int gblk) 
{
   NAME_LIST *varcom_namesp;
   NAME_LIST *varcom_names_temp;
   VARCOM_DATA *varcom_datap;
   VARCOM_DATA *varcom_data_temp;
   char hashname[MAXLINE];
   if  (!ifcom)  {
      return;
   }
   varcom_namesp = varcom_names;
   while (varcom_namesp != NULL) {
      if (!strcmp(name,varcom_namesp->name)) break; 
      varcom_namesp = varcom_namesp->next;
   }
   if (varcom_namesp == NULL) {
      varcom_names_temp   = MALLOT(NAME_LIST,1);
      varcom_names_temp->next = NULL;
      if (varcom_names == NULL) {
         varcom_names = varcom_names_temp;
         varcom_namesp = varcom_names;
      } else {
         varcom_namesp = varcom_names;
         while (varcom_namesp->next != NULL) varcom_namesp = varcom_namesp->next;
         varcom_namesp->next = varcom_names_temp;
         varcom_namesp       = varcom_namesp->next;
      } 
      strcpy(varcom_namesp->name, name);
   } 
   varcom_datap = varcom_data;
   if (varcom_datap == NULL) {
      varcom_data = MALLOT(VARCOM_DATA,1);
      varcom_data->next = NULL;
      varcom_datap = varcom_data;
   } else {
      while (varcom_datap->next != NULL) varcom_datap = varcom_datap->next;
      varcom_data_temp   = MALLOT(VARCOM_DATA,1);
      varcom_data_temp->next = NULL;
      varcom_datap->next = varcom_data_temp;
      varcom_datap = varcom_data_temp;
   }
   sprintf(hashname,"varcom_blk%03d_%s",gblk,name);
   strcpy(varcom_datap->name,hashname);
   varcom_datap->var_ptr = data;
   varcom_datap->var_type = var_type;
   varcom_datap->com_type = com_type;
   varcom_datap->com_op   = com_op;
   varcom_datap->len = len;
   hash_add(hashname,"varcom_data",varcom_datap,gv_hash_tbl);
}
void varcom_bufinit(void) {
   int i;
   for (i = 0; i < num_procs; i++) {
      combuf[VARCOM].proc[i] = i;
      combuf[VARCOM].comm[i] = MPI_COMM_WORLD;
   }
   setbuforder(VARCOM, hydro_blk_order, hydro_tag_order, hydro_len_order,
                     hydro_len_order_send);
   strcpy(combuf[VARCOM].bufname,"varcom");
}
