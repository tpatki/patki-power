#include "irs.h"
#include "BlockMapping.h"
#include "irscom.h"
#include "Boundary.h"
#include "FunctionTimer.h" 
int radcom( int stepflag, int comflag )
{
   char *me = "radcom";	  
   int i,j,ibc,ibc_out ;
   int iblk_out,gblk,gblk_in ;
   int len ;
   int iblk ;
   int error ;
   int proc ;
   int *inndx,*outndx ;
   int *inzdx,*outzdx ;
   int g ;
   double *x,*y,*z,*xp,*yp,*zp ;
   double *volm,*volmp;
   double *kl,*kr,*kb,*kf,*kd,*ku ;
   double *klp,*krp,*kbp,*kfp,*kdp,*kup ;
   Boundary_t *bnd,*bnd2 ;
   error = 0 ;
   if (!ifcom) return(error) ;
   STARTTIMER(stepflag) ;
   if (ifparallel)
     {
     curcombuf = stepflag ; 
     if (comflag == COM_RECV) 
       {
       initbuf(stepflag,COM_RECV) ;
       postbuf(stepflag,COM_RECV) ;
       STOPTIMER(stepflag,comflag) ;
       return(error) ;
       }
     else if (comflag == COM_SEND)
       {
       initbuf(stepflag,COM_SEND) ;
       }
     else if (comflag == COM_WAIT_SEND) 
       {
       waitbuf(stepflag,COM_WAIT_SEND,COM_ALL) ;
       freebuf(stepflag,COM_SEND) ;
       STOPTIMER(stepflag,comflag) ;
       return(error) ;
       }
     else if (comflag == COM_WAIT_RECV) 
       {
       while((proc=waitbuf(stepflag,COM_WAIT_RECV,COM_ANY))>=0)
	 {
	 for (i=0;i<hydro_len_order[proc];i++) 
	   {
	   ibc = hydro_tag_order[proc][i];
	   gblk= hydro_blk_order[proc][i] ;
	   iblk = gmap[gblk].lblk ;
	   bnd = domains[iblk].bnd;
	   gblk_in = domains[iblk].bnd[ibc].blk_send ;
	   len=domains[iblk].bnd[ibc].len_nrecv1;
	   if (stepflag == RADCOM0)
	     {
	     x = domains[iblk].x ;
	     y = domains[iblk].y ;
	     getdata(x,len,COM_DOUBLE,gblk_in,&bnd[ibc],COM_LAYER2NC) ;
	     getdata(y,len,COM_DOUBLE,gblk_in,&bnd[ibc],COM_LAYER2NC) ;
	     if (ndims == 3)
	       {
	       z = domains[iblk].z ;
	       getdata(z,len,COM_DOUBLE,gblk_in,&bnd[ibc],COM_LAYER2NC) ;
	       }
	     if (planckwt)
	       {
	       getdata(domains[iblk].tmat,len,COM_DOUBLE,gblk_in,&bnd[ibc],
		       COM_LAYER1ZC) ;
	       getdata(domains[iblk].trad,len,COM_DOUBLE,gblk_in,&bnd[ibc],
		       COM_LAYER1ZC) ;
	       }
	     }
	   }
         }
       freebuf(stepflag,COM_RECV) ;
       }
     }
   for (j=0;j<hydro_len_order_send;j++)
     {
     ibc = hydro_tag_order[myid][j+hydro_len_order[myid]] ;
     gblk = hydro_blk_order[myid][j+hydro_len_order[myid]] ;
     iblk = gmap[gblk].lblk ;
     bnd = domains[iblk].bnd ;
     gblk = bnd[ibc].blk_send ;
     proc = gmap[gblk].proc ;
     ibc_out = bnd[ibc].bndnbc ;
     len = 0;
     if ((proc!=myid)&&(comflag==COM_SEND))
       {
       if (stepflag == RADCOM0)
	 {
	 x = domains[iblk].x ;
	 y = domains[iblk].y ;
	 putdata(x,len,COM_DOUBLE,gblk,&bnd[ibc],COM_LAYER2NC) ;
	 putdata(y,len,COM_DOUBLE,gblk,&bnd[ibc],COM_LAYER2NC) ;
	 if (ndims == 3) 
	   {
	   z = domains[iblk].z ;
	   putdata(z,len,COM_DOUBLE,gblk,&bnd[ibc],COM_LAYER2NC) ;
	   }
	 if (planckwt)
	   {
	   putdata(domains[iblk].tmat,len,COM_DOUBLE,gblk,&bnd[ibc],COM_LAYER1ZC) ;
	   putdata(domains[iblk].trad,len,COM_DOUBLE,gblk,&bnd[ibc],COM_LAYER1ZC) ;
	   }
         }
       }
     else if ((proc==myid)&&(comflag==COM_SEND))
       {
       iblk_out = gmap[gblk].lblk ;
       bnd2 = domains[iblk_out].bnd ;
       inndx = bnd[ibc].ndx_recv + bnd[ibc].len_nrecv1 ;
       outndx = bnd2[ibc_out].ndx_send + bnd2[ibc_out].len_nsend1 ;
       inzdx = bnd[ibc].zdx_recv ;
       outzdx = bnd2[ibc_out].zdx_send ;
       if (stepflag == RADCOM0) 
	 {
	 x = domains[iblk].x ;
	 y = domains[iblk].y ;
	 z = domains[iblk].z ;
	 xp = domains[iblk_out].x ;
	 yp = domains[iblk_out].y ;
	 zp = domains[iblk_out].z ;
	 len = bnd[ibc].len_nrecv2 + bnd[ibc].len_nrecvc ;
	 if (ndims == 2)
	   {
	   for ( i = 0 ; i < len ; i++ )
	     {
	     x[inndx[i]] = xp[outndx[i]] ;
	     y[inndx[i]] = yp[outndx[i]] ;
	     }
	   }
	 else
	   {
	   for ( i = 0 ; i < len ; i++ )
	     {
	     x[inndx[i]] = xp[outndx[i]] ;
	     y[inndx[i]] = yp[outndx[i]] ;
	     z[inndx[i]] = zp[outndx[i]] ;
	     }
	   }
	 len = bnd[ibc].len_zrecv1 + bnd[ibc].len_zrecvc ;
	 if (planckwt)
	   {
	   for ( i = 0 ; i < len ; i++ )
	     {
	     domains[iblk].tmat[inzdx[i]] = domains[iblk_out].tmat[outzdx[i]] ;
	     domains[iblk].trad[inzdx[i]] = domains[iblk_out].trad[outzdx[i]] ;
	     }
	   }
         }
       }
     else if (comflag == COM_SET_SIZE_DOUBLE)
       {
       if (stepflag == RADCOM0)
         {
	 len_sendd[proc] += 2*(bnd[ibc].len_nsend2 + bnd[ibc].len_nsendc)  ;
	 len_recvd[proc] += 2*(bnd[ibc].len_nrecv2 + bnd[ibc].len_nrecvc)  ;
	 if (ndims == 3) 
            {
            len_sendd[proc] += bnd[ibc].len_nsend2 + bnd[ibc].len_nsendc ;
            len_recvd[proc] += bnd[ibc].len_nrecv2 + bnd[ibc].len_nrecvc ;
	    }
	 if (planckwt) 
            {
	    len_sendd[proc] += 2*(bnd[ibc].len_zsend1 + bnd[ibc].len_zsendc) ;
	    len_recvd[proc] += 2*(bnd[ibc].len_zrecv1 + bnd[ibc].len_zrecvc) ;
	    }
	 }
       if (stepflag == RADCOM1)
	 {
	 len_sendd[proc] += (2 + 2*ngroup)*(bnd[ibc].len_zsend1 + 
                             bnd[ibc].len_zsendc) ;
	 len_recvd[proc] += (2 + 2*ngroup)*(bnd[ibc].len_zrecv1 + 
                             bnd[ibc].len_zrecvc) ;
	 len_sendd[proc] += bnd[ibc].len_nsend2 + bnd[ibc].len_nsendc ;
         len_recvd[proc] += bnd[ibc].len_nrecv2 + bnd[ibc].len_nrecvc ;
	 if (ndims == 2) 
            {
	    len_sendd[proc] += bnd[ibc].len_zsend1 + bnd[ibc].len_zsendc ;
	    len_recvd[proc] += bnd[ibc].len_zrecv1 + bnd[ibc].len_zrecvc ;
	    }
	 if (nkappa == 2) 
            {
            len_sendd[proc] += ngroup*(bnd[ibc].len_zsend1 + 
                               bnd[ibc].len_zsendc) ;
            len_recvd[proc] += ngroup*(bnd[ibc].len_zrecv1 + 
                               bnd[ibc].len_zrecvc) ;
            }
	 if (planckwt) 
            {
            if (ndims == 3) 
               {
               len_sendd[proc] += 6*ngroup*(bnd[ibc].len_zsend1 + 
                                         bnd[ibc].len_zsendc) ;
               len_recvd[proc] += 6*ngroup*(bnd[ibc].len_zrecv1 + 
                                         bnd[ibc].len_zrecvc) ;
               }
            else 
               {
               len_sendd[proc] += 4*ngroup*(bnd[ibc].len_zsend1 + 
                                         bnd[ibc].len_zsendc) ;
               len_recvd[proc] += 4*ngroup*(bnd[ibc].len_zrecv1 + 
                                         bnd[ibc].len_zrecvc) ;
               }
            }
         }
       if (stepflag == RADCOM2)
	 {
	 len_sendd[proc] += bnd[ibc].len_nsend2 + bnd[ibc].len_nsendc ;
         len_recvd[proc] += bnd[ibc].len_nrecv2 + bnd[ibc].len_nrecvc ;
         }
       }
     else if (comflag == COM_SET_SIZE_INT)
       {
       if (stepflag == RADCOM1) 
          {
          len_sendi[proc] += (bnd[ibc].len_zsend1 + bnd[ibc].len_zsendc) ;
          len_recvi[proc] += (bnd[ibc].len_zrecv1 + bnd[ibc].len_zrecvc) ;
          }
       }
   }
   if ((ifparallel)&&(comflag==COM_SEND))
     postbuf(stepflag,COM_SEND) ;
   STOPTIMER(stepflag,comflag) ;
   return(error) ;
 }
