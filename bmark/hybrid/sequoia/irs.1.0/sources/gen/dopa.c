#include "irs.h"
#include "irscom.h"
#include "irscur.h"
#include "irsgen.h"
#include "irsrgst.h"
#include "NodeList.h"
#include "ProblemArray.h"
int dopa(char *aname)
{
  char *me = "dopa";
  int    i, j, count, ndxlen, gndx_old, len, larg, array_type;
  int    *idata, *iarg, *lndx, *gndx, *lblk, *idata_compressed;
  char   op[MAXLINE], lab[MAXLINE], msg[MAXLINE];
  char   redostr[8000];
  double result[2];
  double *fdata, *farg, *fdata_compressed;
  int    error = 0, termflag = 1, docount=0;
  NodeWindow_t  *ndxin   = NULL,
            *ndxptr  = NULL;
  ProblemArray_t   *prb = NULL;
  ProblemArray_t   *prb_array = NULL;
  prb = ProblemArray_find(aname,NULL);
  if ( prb == NULL) {
    ctlerror(me,logic_err);
  }
  if (prb->ptr == NULL) {
     prb_array = ProblemArray_setblk(aname);
  }
  setiomrk(redostr,800) ;
  nincount = 0 ;
  ninloops = 0 ;
  while(termflag) {
    if (NodeWindow_read(aname,&ndxin) != 0) {
      return(1);
    }
    peekc2(op) ;
    if (!strcmp(op,"=")) {
      geta(op) ;
      ndxptr = ndxin;
      while (ndxptr != NULL) {
	if (RGST_QUERY_OBJECT_ATTR(aname,"Zonal") == TRUE) {
          ndxlen = NodeWindow_getndx(ndxptr,-1,NDX_OVERLAP,   NDX_REAL,NDX_ZONAL);
          len    = NodeWindow_getlen(ndxptr,-1,NDX_NO_OVERLAP,NDX_REAL,NDX_ZONAL);
        } else {
          ndxlen = NodeWindow_getndx(ndxptr,-1,NDX_OVERLAP,   NDX_REAL,NDX_NODAL);
          len    = NodeWindow_getlen(ndxptr,-1,NDX_NO_OVERLAP,NDX_REAL,NDX_NODAL);
        }
        memset(lab,'\0',MAXLINE);
        mkpalab(lab,aname,ndxptr->ublk,ndxptr->in,ndxptr->rank,0,"");
        gndx = ndxptr->udx;
        lndx = ndxptr->ndx;
        lblk = ndxptr->blk;
	if ((prb->ptr != NULL) && (prb->type == R_DOUBLE)) {
          farg  = ALLOT(double,len) ;
          larg  = getarg("double",farg,len);
          fdata = (double *)prb->ptr;
          if (larg == 1) {
            for (i = 0 ; i < ndxlen ; i++) { fdata[lndx[i]] = farg[0]; }
          } else if (larg == len) {
            for (i = 0 ; i < ndxlen ; i++) { fdata[lndx[i]] = farg[i]; }
          } else {
            error = 1 ;
            sprintf(msg,"arg len %d not equal target len %d in %s",larg,len,aname);
            ctlwarning(me,msg);
          }
          FREEMEM(farg) ;
        } else if ((prb->ptr == NULL) && (prb->type == R_DOUBLE)) {
          farg = ALLOT(double,len) ;
          larg = getarg("double",farg,len);
          if (larg == 1) {
            for ( i = 0 ; i < ndxlen ; i++ ) {
               fdata = (double *)prb_array[lblk[i]].ptr;
               fdata[lndx[i]] = farg[0] ;
            }
            if ((aname[0]=='x') || (aname[0]=='y') ||(aname[0]=='z')) {
              for ( i = 0 ; i < ndxlen ; i++ ) {
                 domains[lblk[i]].node[lndx[i]] = 1;
              }
            }
          } else if (larg == len) {
            j = -1;
	    if (ndxlen > 0) gndx_old = gndx[0] - 1;
            for ( i = 0 ; i < ndxlen ; i++ ) {
               if (gndx[i] != gndx_old) {
                  j++;
                  gndx_old = gndx[i];
               }
               fdata = (double *)prb_array[lblk[i]].ptr;
               fdata[lndx[i]] = farg[j] ;
            }
            if ((aname[0]=='x') || (aname[0]=='y') || (aname[0]=='z')) {
              for ( i = 0 ; i < ndxlen ; i++ ) {
                 domains[lblk[i]].node[lndx[i]] = 1 ;
              }
            }
          } else {
            error = 1 ;
            sprintf(msg,"arg len %d not equal target len %d in %s",
                        larg,len,aname) ;
            ctlwarning(me,msg);
          }
          FREEMEM(farg) ;
        } else if ((prb->ptr != NULL) && (prb->type == R_INT)) {
          iarg  = ALLOT(int,len) ;
          larg  = getarg("int",iarg,len);
          idata = (int *)prb->ptr;
          if (larg == 1) {
            for ( i = 0 ; i < ndxlen ; i++ ) { idata[lndx[i]] = iarg[0]; }
          } else if (larg == len) {
            for ( i = 0 ; i < ndxlen ; i++ ) { idata[lndx[i]] = iarg[i]; }
          } else {
            error = 1 ;
            sprintf(msg,"arg len %d not equal target len %d in %s",
                        larg,len,aname) ;
            ctlwarning(me,msg);
          }
          FREEMEM(iarg) ;
        } else if ((prb->ptr == NULL) && (prb->type == R_INT)) {
          iarg = ALLOT(int,len) ;
          larg = getarg("int",iarg,len);
          if (larg == 1) {
            for ( i = 0 ; i < ndxlen ; i++ ) {
               idata  = (int *)prb_array[lblk[i]].ptr;
               idata[lndx[i]] = iarg[0] ;
            }
          } else if (larg == len) {
            j = -1;
            if (ndxlen > 0) gndx_old = gndx[0] - 1;
            for ( i = 0 ; i < ndxlen ; i++ ) {
               if (gndx[i] != gndx_old) {
                 j++;
                 gndx_old = gndx[i];
               }
               idata = (int *)prb_array[lblk[i]].ptr;
               idata[lndx[i]] = iarg[j] ;
            }
          } else {
            error = 1 ;
            sprintf(msg,"arg len %d not equal target len %d in %s",
                         larg,len,aname) ;
            ctlwarning(me,msg);
          }
          FREEMEM(iarg) ;
        } else  {
          ctlerror(me,logic_err);
        }
        ndxptr = ndxptr->next;
      } 
    } 
    else {
      ndxptr = ndxin;
      while (ndxptr != NULL) {
	if (RGST_QUERY_OBJECT_ATTR(aname,"Zonal") == TRUE) {
          len    = NodeWindow_getndx(ndxptr,-1,NDX_NO_OVERLAP,NDX_REAL,NDX_ZONAL);
        } else {
          len    = NodeWindow_getndx(ndxptr,-1,NDX_NO_OVERLAP,NDX_REAL,NDX_NODAL);
        }
        len = ndxptr->len_total;
        mkpalab(lab,aname,ndxptr->ublk,ndxptr->in,ndxptr->rank,0,"");
        gndx = ndxptr->udx;
        lndx = ndxptr->ndx;
        lblk = ndxptr->blk;
        if ((prb->ptr != NULL) && (prb->type == R_DOUBLE)) {
          fdata = prb->ptr;
          if (roptype > 0) {
             dorop(result,fdata,lndx,len,roptype) ;
             fdata = result ;
             lndx[0] = 0 ;
             len = 1 ;
          }
          if (len == 1) {
            ctloutput(me,lab,R_DOUBLE,fdata[lndx[0]]);
          }
          else {
            fdata_compressed = ALLOT(double,len);
            for (i=0; i<len; i++) {
              fdata_compressed[i] = fdata[lndx[i]];
            }
            ctloutput(me,lab,R_DOUBLE_ARRAY,fdata_compressed,len);
            FREEMEM(fdata_compressed);
          }
        }
        else  if ((prb->ptr == NULL) && (prb->type == R_DOUBLE)) {
          fdata_compressed = ALLOT(double,len);
          comgather(fdata_compressed,aname,ndxptr,0);
          if (roptype > 0) {
            dorop(result,prb_array[blknum].ptr,lndx,len,roptype) ;
            fdata_compressed[0] = result[0] ;
            len = 1 ;
          }
          if (len == 1) {
            ctloutput(me,lab,R_DOUBLE,fdata_compressed[0]);
          }
          else {
            ctloutput(me,lab,R_DOUBLE_ARRAY,fdata_compressed,len);
          }
          FREEMEM(fdata_compressed);
        }
        else  if ((prb->ptr != NULL) && (prb->type == R_INT)) {
          idata = (int *)prb->ptr;
          if (len == 1) {
            ctloutput(me,lab,R_INT,idata[lndx[0]]);
          }
          else {
            idata_compressed = ALLOT(int,len);
            for (i=0; i<len; i++) {
              idata_compressed[i] = idata[lndx[i]];
            }
            ctloutput(me,lab,R_INT_ARRAY,idata_compressed,len);
            FREEMEM(idata_compressed);
          }
        }
        else  if ((prb->ptr == NULL) && (prb->type == R_INT)) {
          idata_compressed = ALLOT(int,len);
          comgather(idata_compressed,aname,ndxptr,0);
          if (len == 1) {
            ctloutput(me,lab,R_INT,idata_compressed[0]);
          }
          else {
            ctloutput(me,lab,R_INT_ARRAY,idata_compressed,len);
          }
          FREEMEM(idata_compressed);
        }
        ndxptr = ndxptr->next;
      } 
    } 
    NodeWindow_free(ndxin);
    ndxin = NULL;
    if (ninloops == 0) break ;
    resetio() ;
    nincount++ ;
    docount++ ;
  } 
  if (prb->ptr == NULL) {
     FREEMEM(prb_array);
  }
  unsetio() ;
  return(error) ;
}
