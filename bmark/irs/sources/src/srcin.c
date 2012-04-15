#include "irs.h"
#include "irssrc.h"
#include "BlockMapping.h"
#include "Extents.h"
#include "NodeList.h"
#include "UserList.h"
int srcin( int mode )
{
   char *me = "srcin" ;
   char op[MAXWORD], msg[128] ;
   int error = 0 ;
   NodeWindow_t *ndxin = NULL ;
   if ( mode == 0 ) {
      strcpy( op, "src" ) ;
   } else {
      strcpy( op, "ale" ) ;
   } 
   error = NodeWindow_read( op, &ndxin ) ;
   if ( error != 0 ) {
      sprintf( msg, "Error reading index list for %s", op ) ;
      ctlwarning( me, msg ) ;
      return( error ) ;
   }
   geta( op ) ;
   geta( op ) ;
   error = srcin_init( mode, op, ndxin ) ;
   return( error ) ;
}
int srcin_init( int mode, char *srctype, NodeWindow_t *ndxin )
{
   char *me = "srcin_init";
   char lab[30], msg[128];
   char ndxname[MAXLINE];
   char op[MAXLINE];
   int error, cflag ;
   int gblk ;
   int iblk, len ;
   int ifread ;
   int isrc, isrc2, isrc3 ;
   int i, j ;
   int type ;
   int cent ;
   int nidat1 ;
   int nfdat1 ;
   int ndat2 ;
   int ivalue ;
   int bndflag ;
   int iflag ;
   int jflag ;
   int kflag ;
   int *ndx ;
   int *idat1 ;
   double *fdat1, *fdat2 ;
   NodeWindow_t *ndxptr = NULL ;
   Extents_t ext1 ;
   Extents_t ext2 ;
   Extents_t ext3 ;
   error   = 0 ; 
   isrc2   = 0 ;
   isrc3   = 0 ;
   bndflag = 0 ;
   if        (!strcmp(srctype,"dsrc1")) {
      type   = DSRC1 ;
      cent   = ZONAL_ARRAY ;
      nidat1 = 0 ;
      nfdat1 = 1 ;
   } else if (!strcmp(srctype,"esrc1")) {
      type   = ESRC1 ;
      cent   = ZONAL_ARRAY ;
      nidat1 = 0 ;
      nfdat1 = 1 ;
   } else if (!strcmp(srctype,"psrc1")) {
      type   = PSRC1 ;
      cent   = ZONAL_ARRAY ;
      nidat1 = 0 ;
      nfdat1 = 1 ;
   } else if (!strcmp(srctype,"tesrc1")) {
      type   = TESRC1 ;
      cent   = ZONAL_ARRAY ;
      nidat1 = 0 ;
      nfdat1 = 1 ;
   } else if (!strcmp(srctype,"tisrc1")) {
      type   = TISRC1 ;
      cent   = ZONAL_ARRAY ;
      nidat1 = 0 ;
      nfdat1 = 1 ;
   } else if (!strcmp(srctype,"tesrcint1")) {
      type   = TESRCINT1 ;
      cent   = ZONAL_ARRAY ;
      nidat1 = 1 ;
      nfdat1 = 1 ;
   } else if (!strcmp(srctype,"tisrcint1")) {
      type   = TISRCINT1 ;
      cent   = ZONAL_ARRAY ;
      nidat1 = 1 ;
      nfdat1 = 1 ;
   } else if (!strcmp(srctype,"tesrcint2")) {
      isrc2  = 1 ;
      type   = TESRCINT2 ;
      cent   = ZONAL_ARRAY ;
      nidat1 = 2 ;
      nfdat1 = 0 ;
   } else if (!strcmp(srctype,"tisrcint2")) {
      isrc2  = 1 ;
      type   = TISRCINT2 ;
      cent   = ZONAL_ARRAY ;
      nidat1 = 2 ;
      nfdat1 = 0 ;
   } else if (!strcmp(srctype,"xvsrc1")) {
      type   = XVSRC1 ;
      cent   = NODAL_ARRAY ;
      nidat1 = 0 ;
      nfdat1 = 1 ;
   } else if (!strcmp(srctype,"yvsrc1")) {
      type   = YVSRC1 ;
      cent   = NODAL_ARRAY ;
      nidat1 = 0 ;
      nfdat1 = 1 ;
   } else if (!strcmp(srctype,"zvsrc1")) {
      type   = ZVSRC1 ;
      cent   = NODAL_ARRAY ;
      nidat1 = 0 ;
      nfdat1 = 1 ;
   } else if (!strcmp(srctype,"xasrc1")) {
      type   = XASRC1 ;
      cent   = NODAL_ARRAY ;
      nidat1 = 0 ;
      nfdat1 = 1 ;
   } else if (!strcmp(srctype,"yasrc1")) {
      type   = YASRC1 ;
      cent   = NODAL_ARRAY ;
      nidat1 = 0 ;
      nfdat1 = 1 ;
   } else if (!strcmp(srctype,"zasrc1")) {
      type   = ZASRC1 ;
      cent   = NODAL_ARRAY ;
      nidat1 = 0 ;
      nfdat1 = 1 ;
   } else if (!strcmp(srctype,"xasrc3")) {
      type   = XASRC3 ;
      cent   = NODAL_ARRAY ;
      nidat1 = 0 ;
      nfdat1 = 1 ;
   } else if (!strcmp(srctype,"yasrc3")) {
      type   = YASRC3 ;
      cent   = NODAL_ARRAY ;
      nidat1 = 0 ;
      nfdat1 = 1 ;
   } else if (!strcmp(srctype,"zasrc3")) {
      type   = ZASRC3 ;
      cent   = NODAL_ARRAY ;
      nidat1 = 0 ;
      nfdat1 = 1 ;
   } else if (!strcmp(srctype,"xeuler")) {
      type   = XEULER ;
      cent   = NODAL_ARRAY ;
      nidat1 = 0 ;
      nfdat1 = 0 ;
   } else if (!strcmp(srctype,"yeuler")) {
      type   = YEULER ;
      cent   = NODAL_ARRAY ;
      nidat1 = 0 ;
      nfdat1 = 0 ;
   } else if (!strcmp(srctype,"zeuler")) {
      type   = ZEULER ;
      cent   = NODAL_ARRAY ;
      nidat1 = 0 ;
      nfdat1 = 0 ;
   } else if (!strcmp(srctype,"xminsrc")) {
      type   = XMINSRC ;
      cent   = NODAL_ARRAY ;
      nidat1 = 0 ;
      nfdat1 = 1 ;
   } else if (!strcmp(srctype,"yminsrc")) {
      type   = YMINSRC ;
      cent   = NODAL_ARRAY ;
      nidat1 = 0 ;
      nfdat1 = 1 ;
   } else if (!strcmp(srctype,"zminsrc")) {
      type   = ZMINSRC ;
      cent   = NODAL_ARRAY ;
      nidat1 = 0 ;
      nfdat1 = 1 ;
   } else if (!strcmp(srctype,"xmaxsrc")) {
      type   = XMAXSRC ;
      cent   = NODAL_ARRAY ;
      nidat1 = 0 ;
      nfdat1 = 1 ;
   } else if (!strcmp(srctype,"ymaxsrc")) {
      type   = YMAXSRC ;
      cent   = NODAL_ARRAY ;
      nidat1 = 0 ;
      nfdat1 = 1 ;
   } else if (!strcmp(srctype,"zmaxsrc")) {
      type   = ZMAXSRC ;
      cent   = NODAL_ARRAY ;
      nidat1 = 0 ;
      nfdat1 = 1 ;
   } else if (!strcmp(srctype,"dsrc2")) {
      isrc2  = 1 ;
      type   = DSRC2 ;
      cent   = ZONAL_ARRAY ;
      nidat1 = 1 ;
      nfdat1 = 0 ;
   } else if (!strcmp(srctype,"esrc2")) {
      isrc2  = 1 ;
      type   = ESRC2 ;
      cent   = ZONAL_ARRAY ;
      nidat1 = 1 ;
      nfdat1 = 0 ;
   } else if (!strcmp(srctype,"erate2")) {
      isrc2  = 1 ;
      type   = ERATE2 ;
      cent   = ZONAL_ARRAY ;
      nidat1 = 2 ;
      nfdat1 = 0 ;
   } else if (!strcmp(srctype,"erate4")) {
      isrc2  = 1 ;
      type   = ERATE4 ;
      cent   = ZONAL_ARRAY ;
      nidat1 = 2 ;
      nfdat1 = 0 ;
   } else if (!strcmp(srctype,"psrc2")) {
      isrc2  = 1 ;
      type   = PSRC2 ;
      cent   = ZONAL_ARRAY ;
      nidat1 = 1 ;
      nfdat1 = 0 ;
   } else if (!strcmp(srctype,"tesrc2")) {
      isrc2  = 1 ;
      type   = TESRC2 ;
      cent   = ZONAL_ARRAY ;
      nidat1 = 1 ;
      nfdat1 = 0 ;
   } else if (!strcmp(srctype,"tisrc2")) {
      isrc2  = 1 ;
      type   = TISRC2 ;
      cent   = ZONAL_ARRAY ;
      nidat1 = 1 ;
      nfdat1 = 0 ;
   } else if (!strcmp(srctype,"xvsrc2")) {
      isrc2  = 1 ;
      type   = XVSRC2 ;
      cent   = NODAL_ARRAY ;
      nidat1 = 1 ;
      nfdat1 = 0 ;
   } else if (!strcmp(srctype,"yvsrc2")) {
      isrc2  = 1 ;
      type   = YVSRC2 ;
      cent   = NODAL_ARRAY ;
      nidat1 = 1 ;
      nfdat1 = 0 ;
   } else if (!strcmp(srctype,"zvsrc2")) {
      isrc2  = 1 ;
      type   = ZVSRC2 ;
      cent   = NODAL_ARRAY ;
      nidat1 = 1 ;
      nfdat1 = 0 ;
   } else if (!strcmp(srctype,"xasrc2")) {
      isrc2  = 1 ;
      type   = XASRC2 ;
      cent   = NODAL_ARRAY ;
      nidat1 = 1 ;
      nfdat1 = 0 ;
   } else if (!strcmp(srctype,"yasrc2")) {
      isrc2  = 1 ;
      type   = YASRC2 ;
      cent   = NODAL_ARRAY ;
      nidat1 = 1 ;
      nfdat1 = 0 ;
   } else if (!strcmp(srctype,"zasrc2")) {
      isrc2  = 1 ;
      type   = ZASRC2 ;
      cent   = NODAL_ARRAY ;
      nidat1 = 1 ;
      nfdat1 = 0 ;
   } else if (!strcmp(srctype,"tsrc")) {
      isrc2  = 1 ;
      type   = TSRC ;
      cent   = ZONAL_ARRAY ;
      nidat1 = 1 ;
      nfdat1 = 0 ;
   } else if (!strcmp(srctype,"tsrcint")) {
      isrc2  = 1 ;
      type   = TSRCINT ;
      cent   = ZONAL_ARRAY ;
      nidat1 = 2 ;
      nfdat1 = 0 ;
   } else if (!strcmp(srctype,"bnd")) {
      isrc3  = 1 ;
      type   = ALE_BND ;
      cent   = NODAL_ARRAY ;
      bndflag = 1;
      nidat1 = 1 ;
      nfdat1 = 0 ;
   } else {
      error = 1 ;
      sprintf(msg,"illegal source type %s",srctype);
      ctlwarning(me,msg);
      NodeWindow_free(ndxin);
      return(error) ;
   }
   NodeList_addnextseq( "NL_SRC", ndxin, ndxname ) ;
   if ( nidat1 > 0 ) {
      idat1 = MALLOT(int,nidat1) ;
      if (isrc3) {
         idat1[0] = ivalue;
      } else {
         j = 0 ;
         for ( i = 0 ; i < nidat1 ; i++ ) {
            idat1[i] = geti(&cflag) ;
            if ( cflag == 0 ) j++ ;
         }
         if ( j != nidat1 ) {
            error = 1 ;
            sprintf(msg,"Not enough integer data in source type %s",srctype);
            ctlerror(me,msg);
            return(error) ;
	 }
      }
   }
   peekc(op);
   if (!strcmp(op,"species")) {
      geta(op);
      error = UserList_parse(ndxname);
      if (error != 0) {
         ctlwarning(me,"Failed to read in list of species.");
      }
   }
   if ( nfdat1 > 0 ) {
      fdat1 = MALLOT(double,nfdat1) ;
      j = 0 ;
      for ( i = 0 ; i < nfdat1 ; i++ ) {
         fdat1[i] = getf(&cflag) ;
         if ( cflag == 0 ) j++ ;
      }
      if ( j != nfdat1 ) {
         error = 1 ;
         sprintf(msg,"Not enough real data in source type %s",srctype);
         ctlerror(me,msg);
         return(error) ;
      }
   }
   ifread = 0 ;
   ndat2  = 0 ;
   if ( isrc2 ) {
      ifread = 1 ;
      ndat2  = 2 * idat1[0] ;
   }
   if ( ndat2 > 0 ) {
      fdat2 = MALLOT(double,ndat2) ;
   }
   if (ifread) {
      j = 0 ;
      for ( i = 0 ; i < ndat2 ; i++ ) {
         fdat2[i] = getf(&cflag) ;
         if ( cflag == 0 ) j++ ;
      }
      if ( j != ndat2 ) {
         error = 1 ;
         sprintf(msg,"Not enough real data in source type %s",srctype);
         ctlerror(me,msg);
         return(error) ;
      }
   }
   ndxptr = ndxin ;
   while (ndxptr != NULL) {
      if (bndflag == 1) {
         iflag = 0 ;
         jflag = 0 ;
         kflag = 0 ;
         if (ndxptr->imin == ndxptr->imax) iflag = 1;
         if (ndxptr->jmin == ndxptr->jmax) jflag = 1;
         if (ndxptr->kmin == ndxptr->kmax) kflag = 1;
         ivalue = 0 ;
      }
      for (iblk = 0; iblk < nblk; iblk++) {
         gblk = domains[iblk].gblk;
         if ( cent == ZONAL_ARRAY ) {
            len = NodeWindow_fastndx(ndxptr,gblk,NDX_GLBL_PHONY, NDX_ZONAL);
         } else {
            len = NodeWindow_fastndx(ndxptr,gblk, NDX_GLBL_PHONY, NDX_NODAL);
         }
         if (len > 0) {
            isrc  = domains[iblk].nsrc ;
            if ( isrc >= nsrcx ) {
               error = 1 ;
               sprintf(msg,"number of src's exceeds nsrcx = %d",nsrcx);
               ctlwarning(me,msg);
               return(error) ;
            }
            domains[iblk].src[isrc].nzsrc  = len    ;
            domains[iblk].src[isrc].type   = type   ;
            domains[iblk].src[isrc].cent   = cent   ;
            domains[iblk].src[isrc].nidat1 = nidat1 ;
            domains[iblk].src[isrc].nfdat1 = nfdat1 ;
            strcpy(domains[iblk].src[isrc].ndxName,ndxname);
            domains[iblk].src[isrc].ndxsrc = MALLOT(int,len) ;
            ndx = domains[iblk].src[isrc].ndxsrc ;
            for ( i = 0 ; i < len ; i++ ) {
               ndx[i] = ndxptr->ndx[i] ;
            }
            CPYEXT(ext1,gmap[gblk]) ;
            CPYEXT(ext2,(*ndxptr))  ;
            if ( cent == ZONAL_ARRAY ) {
               ext1.imin-- ;
               ext1.jmin-- ;
               ext1.imax++ ;
               ext1.jmax++ ;
               if ( ndims == 3 ) {
                 ext1.kmin-- ;
                 ext1.kmax++ ;
               } 
            }
            extents_overlap(&ext1,&ext2,&ext3) ;
            TRSEXT(domains[iblk].src[isrc],ext3,gmap[gblk]) ;
            if ( ndims == 2 ) {
               domains[iblk].src[isrc].kmin = 0 ;
               domains[iblk].src[isrc].kmax = 0 ;
            }
            if ( nidat1 > 0 ) {
               domains[iblk].src[isrc].nidat1 = nidat1 ;
               domains[iblk].src[isrc].idat1  = MALLOT(int,nidat1) ;
               for ( i = 0 ; i < nidat1 ; i++ ) {
                  domains[iblk].src[isrc].idat1[i] = idat1[i] ;
               }
	       if (bndflag) {
                  domains[iblk].src[isrc].idat1[0] = ivalue;
	       }
            }
            if ( nfdat1 > 0 ) {
               domains[iblk].src[isrc].nfdat1 = nfdat1 ;
               domains[iblk].src[isrc].fdat1  = MALLOT(double,nfdat1) ;
               for ( i = 0 ; i < nfdat1 ; i++ ) {
                  domains[iblk].src[isrc].fdat1[i] = fdat1[i] ;
               }
            }
            if ( ndat2 > 0 ) {
               domains[iblk].src[isrc].ndat2 = ndat2 ;
               domains[iblk].src[isrc].dat2  = MALLOT(double,ndat2) ;
            }
            if (ifread) {
               for ( i = 0 ; i < ndat2 ; i++ ) {
                  domains[iblk].src[isrc].dat2[i] = fdat2[i] ;
               }
            }
            domains[iblk].nsrc++ ;
            NodeWindow_freendx(ndxptr) ;
         }
      }
      ndxptr = ndxptr->next;
   }
   if ( nfdat1 > 0 ) FREEMEM(fdat1) ;
   if ( nidat1 > 0 ) FREEMEM(idat1) ;
   if ( ndat2  > 0 ) FREEMEM(fdat2) ;
   return(error) ;
}
