#include "irs.h"
#include "irsbndry.h"
#include "irscom.h"
#include "BlockMapping.h"
#include "Boundary.h"
#include "Bndlist.hh"
#include "FunctionTimer.h"
#include "VdenData.hh"
int facecom(int stepflag, int comflag) 
  {
  int i,ibc,ibc_out ;
  int j,count,stride,ist ;
  int iblk,iblk_out,gblk,gblk_in;
  int len,proc,error;
  int *ndx,*inzdx,*outzdx,*inndx,*outndx,*znptr;
  Boundary_t *bnd,*bnd2 ;
  error = 0 ;
  len = 0 ;
  if (!ifcom) {
    return(error) ;
  }
  STARTTIMER(stepflag) ;
  if (ifparallel) {
    curcombuf = stepflag ;
    if (comflag==COM_RECV) {
      initbuf(stepflag,COM_RECV);
      postbuf(stepflag,COM_RECV);
      STOPTIMER(stepflag,comflag);
      return(error);
    } else if (comflag==COM_SEND) {
      initbuf(stepflag,COM_SEND);
    } else if (comflag==COM_WAIT_SEND) {
      waitbuf(stepflag,COM_WAIT_SEND,COM_ALL);
      freebuf(stepflag,COM_SEND);
      STOPTIMER(stepflag,comflag) ;
      return(error) ;
    } else if (comflag==COM_WAIT_RECV) {
      while((proc=waitbuf(stepflag,COM_WAIT_RECV,COM_ANY))>=0) {
	for ( i = 0 ; i < hydro_len_order[proc] ; i++ ) {
	  ibc=hydro_tag_order[proc][i];
	  gblk=hydro_blk_order[proc][i];
	  iblk = gmap[gblk].lblk;
	  bnd = domains[iblk].bnd;
	  gblk = bnd[ibc].blk_send;
	  if (stepflag == FACECOM0) {
	    stride = abs(bnd[ibc].pn) ;
	    if (stride == 1) 
	      ist = 0 ;
	    else if (stride == domains[iblk].jp)
	      ist = 1 ;
	    else if (stride == domains[iblk].kp)
	      ist = 2 ;
	    else 
	      continue ;
	    znptr = bnddat[iblk].zndx[ist] ;
	    getdata(znptr,len,COM_INT,gblk,&bnd[ibc],COM_LAYER1Z) ;
	  }
	  if (stepflag == FACECOM1) {
	    getdata(domains[iblk].eden,len,COM_DOUBLE,gblk,&bnd[ibc],COM_LAYER1ZC) ;
	    getdata(domains[iblk].tmat,len,COM_DOUBLE,gblk,&bnd[ibc],COM_LAYER1ZC) ;
	    getdata(domains[iblk].vol ,len,COM_DOUBLE,gblk,&bnd[ibc],COM_LAYER1ZC) ;
	    getdata(domains[iblk].x,len,COM_DOUBLE,gblk,&bnd[ibc],COM_LAYER2NC) ;
	    getdata(domains[iblk].y,len,COM_DOUBLE,gblk,&bnd[ibc],COM_LAYER2NC) ;
	    if (ndims == 3)
	      getdata(domains[iblk].z,len,COM_DOUBLE,gblk,&bnd[ibc],COM_LAYER2NC) ;
	  }
	  if (stepflag == FACECOM2) {
	    getdata(vnedat[iblk].xnebar,len,COM_DOUBLE,gblk,&bnd[ibc],COM_LAYER2NC) ;
	    getdata(vnedat[iblk].xtebar,len,COM_DOUBLE,gblk,&bnd[ibc],COM_LAYER2NC) ;
	  }
	}
      } 
      freebuf(stepflag,COM_RECV);
    }
  }
  for ( j = 0 ; j < hydro_len_order_send ; j++ ) {
    ibc = hydro_tag_order[myid][j+hydro_len_order[myid]];
    gblk = hydro_blk_order[myid][j+hydro_len_order[myid]];
    iblk = gmap[gblk].lblk;
    bnd = domains[iblk].bnd;
    ibc_out = bnd[ibc].bndnbc;
    gblk = bnd[ibc].blk_send;
    proc = gmap[gblk].proc;
    if ((proc!=myid)&&(comflag==COM_SEND)) {
      if (stepflag==FACECOM0) {
	len = bnd[ibc].len_zsend1 ;
	ndx = bnd[ibc].zdx_send ;
	putdata(ndx,len,COM_INT,gblk,&bnd[ibc],COM_DIRECT) ;
      }
      if (stepflag==FACECOM1) {
	putdata(domains[iblk].eden,len,COM_DOUBLE,gblk,&bnd[ibc],COM_LAYER1ZC) ;
	putdata(domains[iblk].tmat,len,COM_DOUBLE,gblk,&bnd[ibc],COM_LAYER1ZC) ;
	putdata(domains[iblk].vol ,len,COM_DOUBLE,gblk,&bnd[ibc],COM_LAYER1ZC) ;
	putdata(domains[iblk].x,len,COM_DOUBLE,gblk,&bnd[ibc],COM_LAYER2NC) ;
	putdata(domains[iblk].y,len,COM_DOUBLE,gblk,&bnd[ibc],COM_LAYER2NC) ;
	if (ndims == 3)
	  putdata(domains[iblk].z,len,COM_DOUBLE,gblk,&bnd[ibc],COM_LAYER2NC) ;
      }
      if (stepflag==FACECOM2) {
	putdata(vnedat[iblk].xnebar,len,COM_DOUBLE,gblk,&bnd[ibc],COM_LAYER2NC) ;
	putdata(vnedat[iblk].xtebar,len,COM_DOUBLE,gblk,&bnd[ibc],COM_LAYER2NC) ;
      }
    } else if ((proc==myid)&&(comflag==COM_SEND)) {
      iblk_out = gmap[gblk].lblk ;
      bnd2 = domains[iblk_out].bnd ;
      if (stepflag == FACECOM0) {
	stride = abs(bnd[ibc].pn) ;
	if (stride == 1) 
	  ist = 0 ;
	else if (stride == domains[iblk].jp)
	  ist = 1 ;
	else if (stride == domains[iblk].kp)
	  ist = 2 ;
	else 
	  continue ;
	znptr = bnddat[iblk].zndx[ist] ;
	inzdx  = bnd[ibc].zdx_recv ;
	outzdx = bnd2[ibc_out].zdx_send ;
	len = bnd[ibc].len_zrecv1 ;
	for ( i = 0 ; i < len ; i++ ) {
	  znptr[inzdx[i]] = outzdx[i] ;
	}
      }
      if (stepflag == FACECOM1) {
	inzdx  = bnd[ibc].zdx_recv ;
	outzdx = bnd2[ibc_out].zdx_send ;
	inndx = bnd[ibc].ndx_recv + bnd[ibc].len_nrecv1 ;
	outndx = bnd2[ibc_out].ndx_send + bnd2[ibc_out].len_nsend1 ;
	len = bnd[ibc].len_zrecv1 + bnd[ibc].len_zrecvc ;
	for ( i = 0 ; i < len ; i++ ) {
	  domains[iblk].eden[inzdx[i]] = domains[iblk_out].eden[outzdx[i]] ;
	  domains[iblk].tmat[inzdx[i]] = domains[iblk_out].tmat[outzdx[i]] ;
	  domains[iblk].vol[inzdx[i]]  = domains[iblk_out].vol[outzdx[i]] ;
	}
	len = bnd[ibc].len_nrecv2 + bnd[ibc].len_nrecvc ;
	for ( i = 0 ; i < len ; i++ ) {
	  domains[iblk].x[inndx[i]] = domains[iblk_out].x[outndx[i]] ;
	  domains[iblk].y[inndx[i]] = domains[iblk_out].y[outndx[i]] ;
	  domains[iblk].z[inndx[i]] = domains[iblk_out].z[outndx[i]] ;
	}
      }
      if (stepflag == FACECOM2) {
	inndx = bnd[ibc].ndx_recv + bnd[ibc].len_nrecv1 ;
	outndx = bnd2[ibc_out].ndx_send + bnd2[ibc_out].len_nsend1 ;
	len = bnd[ibc].len_nrecv2 + bnd[ibc].len_nrecvc ;
	for ( i = 0 ; i < len ; i++ ) {
	  vnedat[iblk].xnebar[inndx[i]] = vnedat[iblk_out].xnebar[outndx[i]] ;
	  vnedat[iblk].xtebar[inndx[i]] = vnedat[iblk_out].xtebar[outndx[i]] ;
	}
      }
    } else if ((comflag==COM_SET_SIZE_DOUBLE)&&(proc!=myid)) {
      if (stepflag==FACECOM0) {
	len_sendd[proc] += 0 ;
	len_recvd[proc] += 0 ;
      }
      if (stepflag==FACECOM1) {
	len_sendd[proc] += 3*(bnd[ibc].len_zsend1 + bnd[ibc].len_zsendc)
	                + 3*(bnd[ibc].len_nsend2 + bnd[ibc].len_nsendc) ;
	len_recvd[proc] += 3*(bnd[ibc].len_zrecv1 + bnd[ibc].len_zrecvc)
	                + 3*(bnd[ibc].len_nrecv2 + bnd[ibc].len_nrecvc) ;
      }
      if (stepflag==FACECOM2) {
	len_sendd[proc] += 2*(bnd[ibc].len_nsend2 + bnd[ibc].len_nsendc) ;
	len_recvd[proc] += 2*(bnd[ibc].len_nrecv2 + bnd[ibc].len_nrecvc) ;
      }
    } else if ((comflag==COM_SET_SIZE_INT)&&(proc!=myid)) {
	if (stepflag==FACECOM0) {
	  len_sendi[proc] += bnd[ibc].len_zsend1 ;
	  len_recvi[proc] += bnd[ibc].len_zrecv1 ;
	}
      }
  }
  if (ifparallel) {
    if (comflag==COM_SEND) {
      postbuf(stepflag,COM_SEND);
    }
  }
  STOPTIMER(stepflag,comflag) ;
  return(error);
}
