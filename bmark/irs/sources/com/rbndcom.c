#include "irs.h"
#include "irstdiff.h"
#include "irscom.h"
#include "BlockMapping.h"
#include "Boundary.h"
#include "FunctionTimer.h" 
#include "ProblemArray.h"
int rbndcom( int stepflag, int comflag, int igrp )
{
   char *me = "rbndcom";	  
   int i,ibc,ibc_out ;
   int j;
   int iblk_out,gblk,gblk_in;
   int len;
   int iblk;
   int error;
   int proc;
   int iorient ;
   int jorient ;
   int korient ;
   int *inzdx,*outzdx;
   int *inndx,*outndx;
   double *phi;
   double *phip;
   double *tmat;
   double *tion;
   double *trad;
   double *dphi;
   double *dphip;
   double *adphi;
   double *adphip;
   double *flmt;
   double *flmtp;
   double *diffcl;
   double *diffclp;
   double *diffcr;
   double *diffcrp;
   double *diffcb;
   double *diffcbp;
   double *diffcf;
   double *diffcfp;
   double *diffcd;
   double *diffcdp;
   double *diffcu;
   double *diffcup;
   double *ccc, *cccp, *cbl, *cblp, *cbc, *cbcp, *cbr, *cbrp, *ccl, *cclp ;
   double *dcc, *dccp, *dbl, *dblp, *dbc, *dbcp, *dbr, *dbrp, *dcl, *dclp ;
   double *dcr, *dcrp, *dfl, *dflp, *dfc, *dfcp, *dfr, *dfrp ;
   Boundary_t *bnd, *bnd2 ;
   len   = 0 ;
   error = 0 ;
   if ( !ifcom )  {
      return(error) ;
   }
   STARTTIMER( stepflag ) ;
   if ( ifparallel ) {
      curcombuf = stepflag ;
      if ( comflag == COM_RECV ) {
         initbuf( stepflag, COM_RECV ) ;
         postbuf( stepflag, COM_RECV ) ;
         STOPTIMER( stepflag, comflag ) ;
         return(error) ;
      } else if ( comflag == COM_SEND ) {
         initbuf( stepflag, COM_SEND ) ;
      } else if ( comflag == COM_WAIT_SEND ) {
         waitbuf( stepflag, COM_WAIT_SEND, COM_ALL ) ;
         freebuf( stepflag, COM_SEND ) ;
         STOPTIMER( stepflag, comflag ) ;
         return(error) ;
      } else if ( comflag == COM_WAIT_RECV ) {
         while ( (proc = waitbuf(stepflag,COM_WAIT_RECV,COM_ANY)) >= 0 ) {
            for ( i = 0 ; i < hydro_len_order[proc] ; i++ ) {
               ibc  = hydro_tag_order[proc][i] ;
               gblk = hydro_blk_order[proc][i] ;
               iblk = gmap[gblk].lblk ;
               bnd  = domains[iblk].bnd ;
               gblk_in = bnd[ibc].blk_send;
               if ( stepflag == RBNDCOM1 ) {
                  phi  = (double *)ProblemArray_ptr("phi", domains[iblk].hash);
                  dphi = (double *)ProblemArray_ptr("dphi",domains[iblk].hash);
                  getdata(phi, len,COM_DOUBLE,gblk_in,&bnd[ibc],COM_LAYER1ZC);
                  getdata(dphi,len,COM_DOUBLE,gblk_in,&bnd[ibc],COM_LAYER1ZC);
               }
               if ( stepflag == RBNDCOM2 ) {
                  getdata(domains[iblk].ireg,len,COM_INT,gblk_in,&bnd[ibc],
                          COM_LAYER1ZC) ;
                  getdata(domains[iblk].den, len,COM_DOUBLE,gblk_in,&bnd[ibc],
                          COM_LAYER1ZC) ;
                  getdata(domains[iblk].x, len, COM_DOUBLE, gblk_in, &bnd[ibc],
                          COM_LAYER2NC);
                  getdata(domains[iblk].y, len, COM_DOUBLE, gblk_in, &bnd[ibc],
                          COM_LAYER2NC);
                  if ( ndims == 3 ) {
                     getdata(domains[iblk].z, len, COM_DOUBLE, gblk_in,
                             &bnd[ibc], COM_LAYER2NC);
                  }
               }
               if ( stepflag == RBNDCOM3 ) {
                  tmat = domains[iblk].tmat ;
                  tion = domains[iblk].tion ;
                  trad = domains[iblk].trad ;
                  phi  = (double *)ProblemArray_ptr("phi", domains[iblk].hash);
                  getdata(tmat,len,COM_DOUBLE,gblk_in,&bnd[ibc],COM_LAYER1ZC) ;
                  getdata(phi, len,COM_DOUBLE,gblk_in,&bnd[ibc],COM_LAYER1ZC) ;
                  if ( iftion == 1 ) {
                     getdata(tion,len,COM_DOUBLE,gblk_in,&bnd[ibc],COM_LAYER1ZC) ;
		  }
                  if ( ngroup == 1 ) {
                     getdata(trad,len,COM_DOUBLE,gblk_in,&bnd[ibc],COM_LAYER1ZC) ;
		  }
               }
               if ( stepflag == RBNDCOM4 ) {
                  flmt   = (double *)ProblemArray_ptr
		    ("flmt", domains[iblk].hash);
                  iorient = bnd[ibc].orientation[0] ;
                  jorient = bnd[ibc].orientation[1] ;
                  if ( iorient == 1 ) {
                     diffcl  = (double *)ProblemArray_ptr
		       ("diffCoefL", domains[iblk].hash);
                     diffcr  = (double *)ProblemArray_ptr
		       ("diffCoefR", domains[iblk].hash);
                  } else if ( iorient == -1 ) {
                     diffcl  = (double *)ProblemArray_ptr
		       ("diffCoefR", domains[iblk].hash);
                     diffcr  = (double *)ProblemArray_ptr
		       ("diffCoefL", domains[iblk].hash);
                  } else if ( iorient ==  2 ) {
                     diffcl  = (double *)ProblemArray_ptr
		       ("diffCoefB", domains[iblk].hash);
                     diffcr  = (double *)ProblemArray_ptr
		       ("diffCoefF", domains[iblk].hash);
                  } else if ( iorient == -2 ) {
                     diffcl  = (double *)ProblemArray_ptr
		       ("diffCoefF", domains[iblk].hash);
                     diffcr  = (double *)ProblemArray_ptr
		       ("diffCoefB", domains[iblk].hash);
                  } else if ( iorient ==  3 ) {
                     diffcl  = (double *)ProblemArray_ptr
		       ("diffCoefD", domains[iblk].hash);
                     diffcr  = (double *)ProblemArray_ptr
		       ("diffCoefU", domains[iblk].hash);
                  } else if ( iorient == -3 ) {
                     diffcl  = (double *)ProblemArray_ptr
		       ("diffCoefU", domains[iblk].hash);
                     diffcr  = (double *)ProblemArray_ptr
		       ("diffCoefD", domains[iblk].hash);
                  } else {
                     printf("rbndcom: Error in orientation array \n") ;
                  }
                  if ( jorient == 1 ) {
                     diffcb  = (double *)ProblemArray_ptr
		       ("diffCoefL", domains[iblk].hash);
                     diffcf  = (double *)ProblemArray_ptr
		       ("diffCoefR", domains[iblk].hash);
                  } else if ( jorient == -1 ) {
                     diffcb  = (double *)ProblemArray_ptr
		       ("diffCoefR", domains[iblk].hash);
                     diffcf  = (double *)ProblemArray_ptr
		       ("diffCoefL", domains[iblk].hash);
                  } else if ( jorient ==  2 ) {
                     diffcb  = (double *)ProblemArray_ptr
		       ("diffCoefB", domains[iblk].hash);
                     diffcf  = (double *)ProblemArray_ptr
		       ("diffCoefF", domains[iblk].hash);
                  } else if ( jorient == -2 ) {
                     diffcb  = (double *)ProblemArray_ptr
		       ("diffCoefF", domains[iblk].hash);
                     diffcf  = (double *)ProblemArray_ptr
		       ("diffCoefB", domains[iblk].hash);
                  } else if ( jorient ==  3 ) {
                     diffcb  = (double *)ProblemArray_ptr
		       ("diffCoefD", domains[iblk].hash);
                     diffcf  = (double *)ProblemArray_ptr
		       ("diffCoefU", domains[iblk].hash);
                  } else if ( jorient == -3 ) {
                     diffcb  = (double *)ProblemArray_ptr
		       ("diffCoefU", domains[iblk].hash);
                     diffcf  = (double *)ProblemArray_ptr
		       ("diffCoefD", domains[iblk].hash);
                  } else {
                     printf("rbndcom: Error in orientation array \n") ;
                  }
                  getdata(flmt,  len,COM_DOUBLE,gblk_in,&bnd[ibc],COM_LAYER2NC);
                  getdata(diffcl,len,COM_DOUBLE,gblk_in,&bnd[ibc],COM_LAYER1ZC);
                  getdata(diffcr,len,COM_DOUBLE,gblk_in,&bnd[ibc],COM_LAYER1ZC);
                  getdata(diffcb,len,COM_DOUBLE,gblk_in,&bnd[ibc],COM_LAYER1ZC);
                  getdata(diffcf,len,COM_DOUBLE,gblk_in,&bnd[ibc],COM_LAYER1ZC);
                  if ( ndims == 3 ) {
                     korient = bnd[ibc].orientation[2] ;
                     if ( korient == 1 ) {
                        diffcd  = (double *)ProblemArray_ptr
			  ("diffCoefL", domains[iblk].hash);
                        diffcu  = (double *)ProblemArray_ptr
			  ("diffCoefR", domains[iblk].hash);
                     } else if ( korient == -1 ) {
                        diffcd  = (double *)ProblemArray_ptr
			  ("diffCoefR", domains[iblk].hash);
                        diffcu  = (double *)ProblemArray_ptr
			  ("diffCoefL", domains[iblk].hash);
                     } else if ( korient ==  2 ) {
                        diffcd  = (double *)ProblemArray_ptr
			  ("diffCoefB", domains[iblk].hash);
                        diffcu  = (double *)ProblemArray_ptr
			  ("diffCoefF", domains[iblk].hash);
                     } else if ( korient == -2 ) {
                        diffcd  = (double *)ProblemArray_ptr
			  ("diffCoefF", domains[iblk].hash);
                        diffcu  = (double *)ProblemArray_ptr
			  ("diffCoefB", domains[iblk].hash);
                     } else if ( korient ==  3 ) {
                        diffcd  = (double *)ProblemArray_ptr
			  ("diffCoefD", domains[iblk].hash);
                        diffcu  = (double *)ProblemArray_ptr
			  ("diffCoefU", domains[iblk].hash);
                     } else if ( korient == -3 ) {
                        diffcd  = (double *)ProblemArray_ptr
			  ("diffCoefU", domains[iblk].hash);
                        diffcu  = (double *)ProblemArray_ptr
			  ("diffCoefD", domains[iblk].hash);
                     } else {
                        printf("rbndcom: Error in orientation array \n") ;
                     }
                     getdata(diffcd,len,COM_DOUBLE,gblk_in,&bnd[ibc],
                             COM_LAYER1ZC);
                     getdata(diffcu,len,COM_DOUBLE,gblk_in,&bnd[ibc],
                             COM_LAYER1ZC);
                  }
               }
               if ( stepflag == RBNDCOM5 ) {
                  adphi = (double *)ProblemArray_ptr
		    ("adphi", domains[iblk].hash);
                  getdata(adphi,len,COM_DOUBLE,gblk_in,&bnd[ibc],COM_LAYER1ZC);
               }
               if ( stepflag == RBNDCOM6 ) {
                  ccc = cblk[iblk].ccc ;
                  getdata( ccc, len, COM_DOUBLE, gblk_in, &bnd[ibc],
                           COM_LAYER1ZC ) ;
                  if ( ifprecon >= 3 ) {
                     cbl = rblk[iblk].cbl ;
                     cbc = rblk[iblk].cbc ;
                     cbr = rblk[iblk].cbr ;
                     ccl = rblk[iblk].ccl ;
                     getdata( cbl, len, COM_DOUBLE, gblk_in, &bnd[ibc],
                              COM_LAYER1ZC ) ;
                     getdata( cbc, len, COM_DOUBLE, gblk_in, &bnd[ibc],
                              COM_LAYER1ZC ) ;
                     getdata( cbr, len, COM_DOUBLE, gblk_in, &bnd[ibc],
                              COM_LAYER1ZC ) ;
                     getdata( ccl, len, COM_DOUBLE, gblk_in, &bnd[ibc],
                              COM_LAYER1ZC ) ;
	             if ( ndims == 3 ) {
                        dbl = rblk[iblk].dbl ;
                        dbc = rblk[iblk].dbc ;
                        dbr = rblk[iblk].dbr ;
                        dcl = rblk[iblk].dcl ;
                        dcc = rblk[iblk].dcc ;
                        dcr = rblk[iblk].dcr ;
                        dfl = rblk[iblk].dfl ;
                        dfc = rblk[iblk].dfc ;
                        dfr = rblk[iblk].dfr ;
                        getdata( dbl, len, COM_DOUBLE, gblk_in, &bnd[ibc],
                                 COM_LAYER1ZC ) ;
                        getdata( dbc, len, COM_DOUBLE, gblk_in, &bnd[ibc],
                                 COM_LAYER1ZC ) ;
                        getdata( dbr, len, COM_DOUBLE, gblk_in, &bnd[ibc],
                                 COM_LAYER1ZC ) ;
                        getdata( dcl, len, COM_DOUBLE, gblk_in, &bnd[ibc],
                                 COM_LAYER1ZC ) ;
                        getdata( dcc, len, COM_DOUBLE, gblk_in, &bnd[ibc],
                                 COM_LAYER1ZC ) ;
                        getdata( dcr, len, COM_DOUBLE, gblk_in, &bnd[ibc],
                                 COM_LAYER1ZC ) ;
                        getdata( dfl, len, COM_DOUBLE, gblk_in, &bnd[ibc],
                                 COM_LAYER1ZC ) ;
                        getdata( dfc, len, COM_DOUBLE, gblk_in, &bnd[ibc],
                                 COM_LAYER1ZC ) ;
                        getdata( dfr, len, COM_DOUBLE, gblk_in, &bnd[ibc],
                                 COM_LAYER1ZC ) ;
	             }
	          }
               }
            }
         }
         freebuf( stepflag, COM_RECV ) ;
      }
   }
   for ( j = 0 ; j < hydro_len_order_send ; j++ ) {
      ibc  = hydro_tag_order[myid][j+hydro_len_order[myid]] ;
      gblk = hydro_blk_order[myid][j+hydro_len_order[myid]] ;
      iblk = gmap[gblk].lblk ;
      bnd  = domains[iblk].bnd ;
      gblk = bnd[ibc].blk_send ;
      proc = gmap[gblk].proc ;
      ibc_out = bnd[ibc].bndnbc ;
      if ( (proc != myid) && (comflag == COM_SEND) ) {
         if ( stepflag == RBNDCOM1 ) {
            phi  = (double *)ProblemArray_ptr( "phi",  domains[iblk].hash ) ;
            dphi = (double *)ProblemArray_ptr( "dphi", domains[iblk].hash ) ;
            putdata( phi,  len, COM_DOUBLE, gblk, &bnd[ibc], COM_LAYER1ZC ) ;
            putdata( dphi, len, COM_DOUBLE, gblk, &bnd[ibc], COM_LAYER1ZC ) ;
         }
         if ( stepflag == RBNDCOM2 ) {
            putdata( domains[iblk].ireg, len, COM_INT, gblk, &bnd[ibc],
                     COM_LAYER1ZC) ;
            putdata( domains[iblk].den,  len, COM_DOUBLE, gblk, &bnd[ibc],
                     COM_LAYER1ZC ) ;
            putdata( domains[iblk].x, len, COM_DOUBLE, gblk, &bnd[ibc],
                     COM_LAYER2NC ) ;
            putdata( domains[iblk].y, len, COM_DOUBLE, gblk, &bnd[ibc],
                     COM_LAYER2NC ) ;
            if ( ndims == 3 ) {
               putdata( domains[iblk].z, len, COM_DOUBLE, gblk, &bnd[ibc],
                        COM_LAYER2NC ) ;
            }
         }
         if ( stepflag == RBNDCOM3 ) {
            tmat = domains[iblk].tmat ;
            tion = domains[iblk].tion ;
            trad = domains[iblk].trad ;
            phi  = (double *)ProblemArray_ptr("phi", domains[iblk].hash);
            putdata( tmat, len, COM_DOUBLE, gblk, &bnd[ibc], COM_LAYER1ZC ) ;
            putdata( phi,  len, COM_DOUBLE, gblk, &bnd[ibc], COM_LAYER1ZC ) ;
            if ( iftion == 1 ) {
               putdata( tion, len, COM_DOUBLE, gblk, &bnd[ibc], COM_LAYER1ZC ) ;
	    }
            if ( ngroup == 1 ) {
               putdata( trad, len, COM_DOUBLE, gblk, &bnd[ibc], COM_LAYER1ZC ) ;
	    }
         }
         if ( stepflag == RBNDCOM4 ) {
            flmt   = (double *)ProblemArray_ptr("flmt", domains[iblk].hash);
            diffcl = (double *)ProblemArray_ptr
	      ("diffCoefL", domains[iblk].hash);
            diffcr = (double *)ProblemArray_ptr
	      ("diffCoefR", domains[iblk].hash);
            diffcb = (double *)ProblemArray_ptr
	      ("diffCoefB", domains[iblk].hash);
            diffcf = (double *)ProblemArray_ptr
	      ("diffCoefF", domains[iblk].hash);
            putdata( flmt,   len, COM_DOUBLE, gblk, &bnd[ibc], COM_LAYER2NC ) ;
            putdata( diffcl, len, COM_DOUBLE, gblk, &bnd[ibc], COM_LAYER1ZC ) ;
            putdata( diffcr, len, COM_DOUBLE, gblk, &bnd[ibc], COM_LAYER1ZC ) ;
            putdata( diffcb, len, COM_DOUBLE, gblk, &bnd[ibc], COM_LAYER1ZC ) ;
            putdata( diffcf, len, COM_DOUBLE, gblk, &bnd[ibc], COM_LAYER1ZC ) ;
            if ( ndims == 3 ) {
               diffcd = (double *)ProblemArray_ptr
		 ("diffCoefD", domains[iblk].hash);
               diffcu = (double *)ProblemArray_ptr
		 ("diffCoefU", domains[iblk].hash);
               putdata(diffcd,len,COM_DOUBLE,gblk,&bnd[ibc],COM_LAYER1ZC);
               putdata(diffcu,len,COM_DOUBLE,gblk,&bnd[ibc],COM_LAYER1ZC);
            }
         }
         if ( stepflag == RBNDCOM5 ) {
            adphi = (double *)ProblemArray_ptr("adphi", domains[iblk].hash);
            putdata(adphi,len,COM_DOUBLE,gblk,&bnd[ibc],COM_LAYER1ZC);
         }
         if ( stepflag == RBNDCOM6 ) {
            ccc = cblk[iblk].ccc ;
            putdata( ccc, len, COM_DOUBLE, gblk, &bnd[ibc], COM_LAYER1ZC ) ;
            if ( ifprecon >= 3 ) {
               cbl = rblk[iblk].cbl ;
               cbc = rblk[iblk].cbc ;
               cbr = rblk[iblk].cbr ;
               ccl = rblk[iblk].ccl ;
               putdata( cbl, len, COM_DOUBLE, gblk, &bnd[ibc], COM_LAYER1ZC ) ;
               putdata( cbc, len, COM_DOUBLE, gblk, &bnd[ibc], COM_LAYER1ZC ) ;
               putdata( cbr, len, COM_DOUBLE, gblk, &bnd[ibc], COM_LAYER1ZC ) ;
               putdata( ccl, len, COM_DOUBLE, gblk, &bnd[ibc], COM_LAYER1ZC ) ;
	       if ( ndims == 3 ) {
                  dbl = rblk[iblk].dbl ;
                  dbc = rblk[iblk].dbc ;
                  dbr = rblk[iblk].dbr ;
                  dcl = rblk[iblk].dcl ;
                  dcc = rblk[iblk].dcc ;
                  dcr = rblk[iblk].dcr ;
                  dfl = rblk[iblk].dfl ;
                  dfc = rblk[iblk].dfc ;
                  dfr = rblk[iblk].dfr ;
                  putdata(dbl, len, COM_DOUBLE, gblk, &bnd[ibc], COM_LAYER1ZC) ;
                  putdata(dbc, len, COM_DOUBLE, gblk, &bnd[ibc], COM_LAYER1ZC) ;
                  putdata(dbr, len, COM_DOUBLE, gblk, &bnd[ibc], COM_LAYER1ZC) ;
                  putdata(dcl, len, COM_DOUBLE, gblk, &bnd[ibc], COM_LAYER1ZC) ;
                  putdata(dcc, len, COM_DOUBLE, gblk, &bnd[ibc], COM_LAYER1ZC) ;
                  putdata(dcr, len, COM_DOUBLE, gblk, &bnd[ibc], COM_LAYER1ZC) ;
                  putdata(dfl, len, COM_DOUBLE, gblk, &bnd[ibc], COM_LAYER1ZC) ;
                  putdata(dfc, len, COM_DOUBLE, gblk, &bnd[ibc], COM_LAYER1ZC) ;
                  putdata(dfr, len, COM_DOUBLE, gblk, &bnd[ibc], COM_LAYER1ZC) ;
	       }
	    }
         }
      } else if ( (proc == myid) && (comflag == COM_SEND) ) {
         iblk_out = gmap[gblk].lblk ;
         bnd2     = domains[iblk_out].bnd ;
         inzdx  = bnd[ibc].zdx_recv ;
         outzdx = bnd2[ibc_out].zdx_send ;
         if ( stepflag == RBNDCOM1 ) {
            phi   = (double *)ProblemArray_ptr("phi", domains[iblk].hash);
            phip  = (double *)ProblemArray_ptr("phi", domains[iblk_out].hash);
            dphi  = (double *)ProblemArray_ptr("dphi", domains[iblk].hash);
            dphip = (double *)ProblemArray_ptr("dphi", domains[iblk_out].hash);
            len    = COM_LEN_1ZC_R(bnd[ibc]) ;
            inzdx  = COM_ZDX_1ZC_R(bnd[ibc]) ;
            outzdx = COM_ZDX_1ZC_S(bnd2[ibc_out]) ;
            for ( i = 0 ; i < len ; i++ ) {
               phi[inzdx[i]]  = phip[outzdx[i]]  ;
               dphi[inzdx[i]] = dphip[outzdx[i]] ;
            }
         }
         if ( stepflag == RBNDCOM2 ) {
            len    = COM_LEN_1ZC_R(bnd[ibc]) ;
            inzdx  = COM_ZDX_1ZC_R(bnd[ibc]) ;
            outzdx = COM_ZDX_1ZC_S(bnd2[ibc_out]) ;
            for ( i = 0 ; i < len ; i++ ) {
               domains[iblk].ireg[inzdx[i]] = domains[iblk_out].ireg[outzdx[i]] ;
               domains[iblk].den [inzdx[i]] = domains[iblk_out].den [outzdx[i]] ;
            }
            len    = COM_LEN_2NC_R(bnd[ibc]) ;
            inndx  = COM_NDX_2NC_R(bnd[ibc]) ;
            outndx = COM_NDX_2NC_S(bnd2[ibc_out]) ;
            if ( ndims == 2 ) {
               for ( i = 0 ; i < len ; i++ ) {
                  domains[iblk].x[inndx[i]] = domains[iblk_out].x[outndx[i]] ;
                  domains[iblk].y[inndx[i]] = domains[iblk_out].y[outndx[i]] ;
               }
            } else {
               for ( i = 0 ; i < len ; i++ ) {
                  domains[iblk].x[inndx[i]] = domains[iblk_out].x[outndx[i]] ;
                  domains[iblk].y[inndx[i]] = domains[iblk_out].y[outndx[i]] ;
                  domains[iblk].z[inndx[i]] = domains[iblk_out].z[outndx[i]] ;
               }
            }
         }
         if ( stepflag == RBNDCOM3 ) {
            phi  = (double *)ProblemArray_ptr("phi", domains[iblk].hash);
            phip = (double *)ProblemArray_ptr("phi", domains[iblk_out].hash);
            len    = COM_LEN_1ZC_R(bnd[ibc]) ;
            inzdx  = COM_ZDX_1ZC_R(bnd[ibc]) ;
            outzdx = COM_ZDX_1ZC_S(bnd2[ibc_out]) ;
            for ( i = 0 ; i < len ; i++ ) {
               domains[iblk].tmat[inzdx[i]] = domains[iblk_out].tmat[outzdx[i]] ;
               phi[inzdx[i]]                = phip[outzdx[i]]                   ;
            }
            if ( iftion == 1 ) {
               for ( i = 0 ; i < len ; i++ ) {
                  domains[iblk].tion[inzdx[i]] = domains[iblk_out].tion[outzdx[i]] ;
               }
	    }
            if ( ngroup == 1 ) {
               for ( i = 0 ; i < len ; i++ ) {
                  domains[iblk].trad[inzdx[i]] = domains[iblk_out].trad[outzdx[i]] ;
               }
	    }
         }
         if ( stepflag == RBNDCOM4 ) {
            flmt   = (double *)ProblemArray_ptr
	      ("flmt", domains[iblk].hash);
            flmtp  = (double *)ProblemArray_ptr
	      ("flmt", domains[iblk_out].hash);
            iorient = bnd[ibc].orientation[0] ;
            jorient = bnd[ibc].orientation[1] ;
            if ( iorient == 1 ) {
               diffcl  = (double *)ProblemArray_ptr
		 ("diffCoefL", domains[iblk].hash);
               diffcr  = (double *)ProblemArray_ptr
		 ("diffCoefR", domains[iblk].hash);
            } else if ( iorient == -1 ) {
               diffcl  = (double *)ProblemArray_ptr
		 ("diffCoefR", domains[iblk].hash);
               diffcr  = (double *)ProblemArray_ptr
		 ("diffCoefL", domains[iblk].hash);
            } else if ( iorient ==  2 ) {
               diffcl  = (double *)ProblemArray_ptr
		 ("diffCoefB", domains[iblk].hash);
               diffcr  = (double *)ProblemArray_ptr
		 ("diffCoefF", domains[iblk].hash);
            } else if ( iorient == -2 ) {
               diffcl  = (double *)ProblemArray_ptr
		 ("diffCoefF", domains[iblk].hash);
               diffcr  = (double *)ProblemArray_ptr
		 ("diffCoefB", domains[iblk].hash);
            } else if ( iorient ==  3 ) {
               diffcl  = (double *)ProblemArray_ptr
		 ("diffCoefD", domains[iblk].hash);
               diffcr  = (double *)ProblemArray_ptr
		 ("diffCoefU", domains[iblk].hash);
            } else if ( iorient == -3 ) {
               diffcl  = (double *)ProblemArray_ptr
		 ("diffCoefU", domains[iblk].hash);
               diffcr  = (double *)ProblemArray_ptr
		 ("diffCoefD", domains[iblk].hash);
            } else {
               printf("rbndcom: Error in orientation array \n") ;
            }
            if ( jorient == 1 ) {
               diffcb  = (double *)ProblemArray_ptr
		 ("diffCoefL", domains[iblk].hash);
               diffcf  = (double *)ProblemArray_ptr
		 ("diffCoefR", domains[iblk].hash);
            } else if ( jorient == -1 ) {
               diffcb  = (double *)ProblemArray_ptr
		 ("diffCoefR", domains[iblk].hash);
               diffcf  = (double *)ProblemArray_ptr
		 ("diffCoefL", domains[iblk].hash);
            } else if ( jorient ==  2 ) {
               diffcb  = (double *)ProblemArray_ptr
		 ("diffCoefB", domains[iblk].hash);
               diffcf  = (double *)ProblemArray_ptr
		 ("diffCoefF", domains[iblk].hash);
            } else if ( jorient == -2 ) {
               diffcb  = (double *)ProblemArray_ptr
		 ("diffCoefF", domains[iblk].hash);
               diffcf  = (double *)ProblemArray_ptr
		 ("diffCoefB", domains[iblk].hash);
            } else if ( jorient ==  3 ) {
               diffcb  = (double *)ProblemArray_ptr
		 ("diffCoefD", domains[iblk].hash);
               diffcf  = (double *)ProblemArray_ptr
		 ("diffCoefU", domains[iblk].hash);
            } else if ( jorient == -3 ) {
               diffcb  = (double *)ProblemArray_ptr
		 ("diffCoefU", domains[iblk].hash);
               diffcf  = (double *)ProblemArray_ptr
		 ("diffCoefD", domains[iblk].hash);
            } else {
               printf("rbndcom: Error in orientation array \n") ;
            }
            diffclp = (double *)ProblemArray_ptr
	      ("diffCoefL", domains[iblk_out].hash);
            diffcrp = (double *)ProblemArray_ptr
	      ("diffCoefR", domains[iblk_out].hash);
            diffcbp = (double *)ProblemArray_ptr
	      ("diffCoefB", domains[iblk_out].hash);
            diffcfp = (double *)ProblemArray_ptr
	      ("diffCoefF", domains[iblk_out].hash);
            len    = COM_LEN_2NC_R(bnd[ibc]) ;
            inzdx  = COM_NDX_2NC_R(bnd[ibc]) ;
            outzdx = COM_NDX_2NC_S(bnd2[ibc_out]) ;
            for ( i = 0 ; i < len ; i++ ) {
               flmt[inzdx[i]] = flmtp[outzdx[i]] ;
            }
            len    = COM_LEN_1ZC_R(bnd[ibc]) ;
            inzdx  = COM_ZDX_1ZC_R(bnd[ibc]) ;
            outzdx = COM_ZDX_1ZC_S(bnd2[ibc_out]) ;
            for ( i = 0 ; i < len ; i++ ) {
               diffcl[inzdx[i]] = diffclp[outzdx[i]] ;
               diffcr[inzdx[i]] = diffcrp[outzdx[i]] ;
               diffcb[inzdx[i]] = diffcbp[outzdx[i]] ;
               diffcf[inzdx[i]] = diffcfp[outzdx[i]] ;
            }
            if ( ndims == 3 ) {
               korient = bnd[ibc].orientation[2] ;
               if ( korient == 1 ) {
                  diffcd  = (double *)ProblemArray_ptr
		    ("diffCoefL", domains[iblk].hash);
                  diffcu  = (double *)ProblemArray_ptr
		    ("diffCoefR", domains[iblk].hash);
               } else if ( korient == -1 ) {
                  diffcd  = (double *)ProblemArray_ptr
		    ("diffCoefR", domains[iblk].hash);
                  diffcu  = (double *)ProblemArray_ptr
		    ("diffCoefL", domains[iblk].hash);
               } else if ( korient ==  2 ) {
                  diffcd  = (double *)ProblemArray_ptr
		    ("diffCoefB", domains[iblk].hash);
                  diffcu  = (double *)ProblemArray_ptr
		    ("diffCoefF", domains[iblk].hash);
               } else if ( korient == -2 ) {
                  diffcd  = (double *)ProblemArray_ptr
		    ("diffCoefF", domains[iblk].hash);
                  diffcu  = (double *)ProblemArray_ptr
		    ("diffCoefB", domains[iblk].hash);
               } else if ( korient ==  3 ) {
                  diffcd  = (double *)ProblemArray_ptr
		    ("diffCoefD", domains[iblk].hash);
                  diffcu  = (double *)ProblemArray_ptr
		    ("diffCoefU", domains[iblk].hash);
               } else if ( korient == -3 ) {
                  diffcd  = (double *)ProblemArray_ptr
		    ("diffCoefU", domains[iblk].hash);
                  diffcu  = (double *)ProblemArray_ptr
		    ("diffCoefD", domains[iblk].hash);
               } else {
                  printf("rbndcom: Error in orientation array \n") ;
               }
               diffcdp = (double *)ProblemArray_ptr
		 ("diffCoefD", domains[iblk_out].hash);
               diffcup = (double *)ProblemArray_ptr
		 ("diffCoefU", domains[iblk_out].hash);
               for ( i = 0 ; i < len ; i++ ) {
                  diffcd[inzdx[i]] = diffcdp[outzdx[i]] ;
                  diffcu[inzdx[i]] = diffcup[outzdx[i]] ;
               }
            }
         }
         if ( stepflag == RBNDCOM5 ) {
            adphi  = (double *)ProblemArray_ptr("adphi", domains[iblk].hash);
            adphip = (double *)ProblemArray_ptr
	      ("adphi", domains[iblk_out].hash);
            len    = COM_LEN_1ZC_R(bnd[ibc]) ;
            inzdx  = COM_ZDX_1ZC_R(bnd[ibc]) ;
            outzdx = COM_ZDX_1ZC_S(bnd2[ibc_out]) ;
            for ( i = 0 ; i < len ; i++ ) {
               adphi[inzdx[i]] = adphip[outzdx[i]] ;
            }
         }
         if ( stepflag == RBNDCOM6 ) {
            ccc    = cblk[iblk].ccc ;
            cccp   = cblk[iblk_out].ccc ;
            len    = COM_LEN_1ZC_R(bnd[ibc]) ;
            inzdx  = COM_ZDX_1ZC_R(bnd[ibc]) ;
            outzdx = COM_ZDX_1ZC_S(bnd2[ibc_out]) ;
            for ( i = 0 ; i < len; i++ ) {
               ccc[inzdx[i]] = cccp[outzdx[i]] ;
            }
            if ( ifprecon >= 3 ) {
               cbl  = rblk[iblk].cbl ;
               cbc  = rblk[iblk].cbc ;
               cbr  = rblk[iblk].cbr ;
               ccl  = rblk[iblk].ccl ;
               cblp = rblk[iblk_out].cbl ;
               cbcp = rblk[iblk_out].cbc ;
               cbrp = rblk[iblk_out].cbr ;
               cclp = rblk[iblk_out].ccl ;
               for ( i = 0 ; i < len; i++ ) {
                  cbl[inzdx[i]] = cblp[outzdx[i]] ;
                  cbc[inzdx[i]] = cbcp[outzdx[i]] ;
                  cbr[inzdx[i]] = cbrp[outzdx[i]] ;
                  ccl[inzdx[i]] = cclp[outzdx[i]] ;
               }
	       if ( ndims == 3 ) {
                  dbl  = rblk[iblk].dbl ;
                  dbc  = rblk[iblk].dbc ;
                  dbr  = rblk[iblk].dbr ;
                  dcl  = rblk[iblk].dcl ;
                  dcc  = rblk[iblk].dcc ;
                  dcr  = rblk[iblk].dcr ;
                  dfl  = rblk[iblk].dfl ;
                  dfc  = rblk[iblk].dfc ;
                  dfr  = rblk[iblk].dfr ;
                  dblp = rblk[iblk_out].dbl ;
                  dbcp = rblk[iblk_out].dbc ;
                  dbrp = rblk[iblk_out].dbr ;
                  dclp = rblk[iblk_out].dcl ;
                  dccp = rblk[iblk_out].dcc ;
                  dcrp = rblk[iblk_out].dcr ;
                  dflp = rblk[iblk_out].dfl ;
                  dfcp = rblk[iblk_out].dfc ;
                  dfrp = rblk[iblk_out].dfr ;
                  for ( i = 0 ; i < len; i++ ) {
                     dbl[inzdx[i]] = dblp[outzdx[i]] ;
                     dbc[inzdx[i]] = dbcp[outzdx[i]] ;
                     dbr[inzdx[i]] = dbrp[outzdx[i]] ;
                     dcl[inzdx[i]] = dclp[outzdx[i]] ;
                     dcc[inzdx[i]] = dccp[outzdx[i]] ;
                     dcr[inzdx[i]] = dcrp[outzdx[i]] ;
                     dfl[inzdx[i]] = dflp[outzdx[i]] ;
                     dfc[inzdx[i]] = dfcp[outzdx[i]] ;
                     dfr[inzdx[i]] = dfrp[outzdx[i]] ;
                  }
	       }
	    }
         }
      } else if ( comflag == COM_SET_SIZE_DOUBLE ) {
         if ( stepflag == RBNDCOM0 ) {
            len_sendd[proc] += COM_LEN_1ZC_S(bnd[ibc]);
            len_recvd[proc] += COM_LEN_1ZC_R(bnd[ibc]);
         } else if ( stepflag == RBNDCOM1 ) {
            len_sendd[proc] += 2*COM_LEN_1ZC_S(bnd[ibc]);
            len_recvd[proc] += 2*COM_LEN_1ZC_R(bnd[ibc]);
         } else if ( stepflag == RBNDCOM2 ) {
            len_sendd[proc] += COM_LEN_1ZC_S(bnd[ibc]);
            len_recvd[proc] += COM_LEN_1ZC_R(bnd[ibc]);
	    if ( ndims == 2 ) {
               len_sendd[proc] += 2*COM_LEN_2NC_S(bnd[ibc]);
               len_recvd[proc] += 2*COM_LEN_2NC_R(bnd[ibc]);
	    } else {
               len_sendd[proc] += 3*COM_LEN_2NC_S(bnd[ibc]);
               len_recvd[proc] += 3*COM_LEN_2NC_R(bnd[ibc]);
	    }
         } else if ( stepflag == RBNDCOM3 ) {
            len_sendd[proc] += 2*COM_LEN_1ZC_S(bnd[ibc]);
            len_recvd[proc] += 2*COM_LEN_1ZC_R(bnd[ibc]);
	    if ( iftion == 1 ) {
               len_sendd[proc] += COM_LEN_1ZC_S(bnd[ibc]);
               len_recvd[proc] += COM_LEN_1ZC_R(bnd[ibc]);
	    }
	    if ( ngroup == 1 ) {
               len_sendd[proc] += COM_LEN_1ZC_S(bnd[ibc]);
               len_recvd[proc] += COM_LEN_1ZC_R(bnd[ibc]);
	    }
         } else if ( stepflag == RBNDCOM4 ) {
            if ( ndims == 2 ) {
               len_sendd[proc] += 4*COM_LEN_1ZC_S(bnd[ibc]);
               len_recvd[proc] += 4*COM_LEN_1ZC_R(bnd[ibc]);
               len_sendd[proc] += COM_LEN_2NC_S(bnd[ibc]);
               len_recvd[proc] += COM_LEN_2NC_R(bnd[ibc]);
            } else {
               len_sendd[proc] += 6*COM_LEN_1ZC_S(bnd[ibc]);
               len_recvd[proc] += 6*COM_LEN_1ZC_R(bnd[ibc]);
               len_sendd[proc] += COM_LEN_2NC_S(bnd[ibc]);
               len_recvd[proc] += COM_LEN_2NC_R(bnd[ibc]);
            } 
         } else if ( stepflag == RBNDCOM5 ) {
            len_sendd[proc] += COM_LEN_1ZC_S(bnd[ibc]);
            len_recvd[proc] += COM_LEN_1ZC_R(bnd[ibc]);
         } else if ( stepflag == RBNDCOM6 ) {
	    if ( ifprecon < 3 ) {
               len_sendd[proc] += COM_LEN_1ZC_S(bnd[ibc]) ;
               len_recvd[proc] += COM_LEN_1ZC_R(bnd[ibc]) ;
	    }
            if ( ifprecon >= 3 ) {
	       if ( ndims == 2 ) {
                  len_sendd[proc] += 5 * COM_LEN_1ZC_S(bnd[ibc]) ;
                  len_recvd[proc] += 5 * COM_LEN_1ZC_R(bnd[ibc]) ;
	       }
               if ( ndims == 3 ) {
                  len_sendd[proc] += 14 * COM_LEN_1ZC_S(bnd[ibc]) ;
                  len_recvd[proc] += 14 * COM_LEN_1ZC_R(bnd[ibc]) ;
	       }
	    }
         } else if ( (stepflag == RBNDCOM7) || (stepflag == RBNDCOM8) ) {
            len_sendd[proc] += COM_LEN_1ZC_S(bnd[ibc]) ;
            len_recvd[proc] += COM_LEN_1ZC_R(bnd[ibc]) ;
         }
      } else if ( comflag == COM_SET_SIZE_INT ) {
         if ( stepflag == RBNDCOM2 ) {
            len_sendi[proc] += COM_LEN_1ZC_S(bnd[ibc]);
            len_recvi[proc] += COM_LEN_1ZC_R(bnd[ibc]);
         } else {
            len_sendi[proc] = 0 ;
            len_recvi[proc] = 0 ;
         }
      }
   }
   if ( (ifparallel) && (comflag == COM_SEND) ) {
      postbuf( stepflag, COM_SEND ) ;
   }
   STOPTIMER( stepflag, comflag ) ;
   return(error); 
}
