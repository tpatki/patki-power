#include "irs.h"
#include "irscom.h"
#include "BndMapping.h"
#include "BlockMapping.h"
#include "Extents.h"
#include "FunctionTimer.h"
static int mapping_allocated = 0;

#ifdef SILO
void decomp_write(DBfile *idbid, char *name) {
   char outstr[MAXLINE];
   int i;
   int ierr;
   int gblk;
   int ublk;
   int ibnd;
   int nlocaldom;
   int dims[1];
   int *neighbor;
   int *localdom;
   dims[0] = 1;
   ierr = DBWrite(idbid, "NumBlocks", &unblk, dims, 1, DB_INT);
   ierr = DBWrite(idbid, "NumDomains", &gnblk, dims, 1, DB_INT);
   nlocaldom = 0;
   localdom = MALLOT(int,gnblk);
   for (gblk = 0; gblk < gnblk; gblk++) {
      if (gmap[gblk].lblk >= 0) {
         nlocaldom++;
         localdom[gmap[gblk].lblk] = gblk;
      }
   }
   dims[0] = 1;
   ierr = DBWrite(idbid, "NumLocalDomains", &nlocaldom, dims, 1, DB_INT);
   dims[0] = nlocaldom;
   ierr = DBWrite(idbid, "LocalDomains", localdom, dims, 1, DB_INT);
   FREEMEM(localdom);
   dims[0] = strlen(name) + 1;
   ierr = DBWrite(idbid, "LocalName", name, dims, 1, DB_CHAR);
   neighbor = MALLOT(int,11);
   for (ublk = 0; ublk < unblk; ublk++) {
      sprintf( outstr, "Block_%i",ublk);
      DBMkdir( idbid, outstr);
      DBSetDir( idbid, outstr);
      dims[0] = 1;
      ierr = DBWrite(idbid, "NumNeighbors", &umap[ublk].nbnd, dims, 1, DB_INT);
      neighbor[0] = umap[ublk].imin - NPNL + 1;
      neighbor[1] = umap[ublk].imax - NPNL + 1;
      neighbor[2] = umap[ublk].jmin - NPNL + 1;
      neighbor[3] = umap[ublk].jmax - NPNL + 1;
      neighbor[4] = umap[ublk].kmin - NPNL + 1;
      neighbor[5] = umap[ublk].kmax - NPNL + 1;
      dims[0] = 6;
      ierr = DBWrite(idbid, "Extents", neighbor, dims, 1, DB_INT);
      for (ibnd = 0; ibnd < umap[ublk].nbnd; ibnd++) {
         i = 0;
         neighbor[i++] = umap[ublk].bnd[ibnd].iblk;
         neighbor[i++] = umap[ublk].bnd[ibnd].id;
         neighbor[i++] = umap[ublk].bnd[ibnd].orientation[0];
         neighbor[i++] = umap[ublk].bnd[ibnd].orientation[1];
         neighbor[i++] = umap[ublk].bnd[ibnd].orientation[2];
         neighbor[i++] = umap[ublk].bnd[ibnd].imin - NPNL + 1;
         neighbor[i++] = umap[ublk].bnd[ibnd].imax - NPNL + 1;
         neighbor[i++] = umap[ublk].bnd[ibnd].jmin - NPNL + 1;
         neighbor[i++] = umap[ublk].bnd[ibnd].jmax - NPNL + 1;
         neighbor[i++] = umap[ublk].bnd[ibnd].kmin - NPNL + 1;
         neighbor[i++] = umap[ublk].bnd[ibnd].kmax - NPNL + 1;
         dims[0] = i;
         sprintf(outstr,"Neighbor_%i",ibnd);
         ierr = DBWrite(idbid, outstr, neighbor, dims, 1, DB_INT);
      }
      DBSetDir( idbid, "../");
   }
   for (gblk = 0; gblk < gnblk; gblk++) {
      sprintf( outstr, "Domain_%i",gblk);
      DBMkdir( idbid, outstr);
      DBSetDir( idbid, outstr);
      dims[0] = 1;
      ierr = DBWrite(idbid, "BlockNum", &gmap[gblk].ublk, dims, 1, DB_INT);
      ierr = DBWrite(idbid, "NumNeighbors", &gmap[gblk].nbnd, dims, 1, DB_INT);
      neighbor[0] = gmap[gblk].imin - NPNL + 1;
      neighbor[1] = gmap[gblk].imax - NPNL + 1;
      neighbor[2] = gmap[gblk].jmin - NPNL + 1;
      neighbor[3] = gmap[gblk].jmax - NPNL + 1;
      neighbor[4] = gmap[gblk].kmin - NPNL + 1;
      neighbor[5] = gmap[gblk].kmax - NPNL + 1;
      dims[0] = 6;
      ierr = DBWrite(idbid, "Extents", neighbor, dims, 1, DB_INT);
      for (ibnd = 0; ibnd < gmap[gblk].nbnd; ibnd++) {
         i = 0;
         neighbor[i++] = gmap[gblk].bnd[ibnd].iblk;
         neighbor[i++] = gmap[gblk].bnd[ibnd].id;
         neighbor[i++] = gmap[gblk].bnd[ibnd].orientation[0];
         neighbor[i++] = gmap[gblk].bnd[ibnd].orientation[1];
         neighbor[i++] = gmap[gblk].bnd[ibnd].orientation[2];
         neighbor[i++] = gmap[gblk].bnd[ibnd].imin - NPNL + 1;
         neighbor[i++] = gmap[gblk].bnd[ibnd].imax - NPNL + 1;
         neighbor[i++] = gmap[gblk].bnd[ibnd].jmin - NPNL + 1;
         neighbor[i++] = gmap[gblk].bnd[ibnd].jmax - NPNL + 1;
         neighbor[i++] = gmap[gblk].bnd[ibnd].kmin - NPNL + 1;
         neighbor[i++] = gmap[gblk].bnd[ibnd].kmax - NPNL + 1;
         dims[0] = i;
         sprintf(outstr,"Neighbor_%i",ibnd);
         ierr = DBWrite(idbid, outstr, neighbor, dims, 1, DB_INT);
      }
      DBSetDir( idbid, "../");
   }
   FREEMEM(neighbor);
}
#endif

#ifdef SILO
void decomp_read(DBfile *idbid, char *name, int ublk0, int gblk0) {
   char outstr[MAXLINE];
   int i;
   int nlocaldom;
   int len;
   int ierr;
   int iblk;
   int gblk;
   int ublk;
   int num_ublk;
   int num_gblk;
   int ibnd;
   int *neighbor;
   int *localdom;
   Extents_t ext;
   ierr = DBReadVar(idbid, "NumBlocks", &num_ublk);
   ierr = DBReadVar(idbid, "NumDomains", &num_gblk);
   ierr = DBReadVar(idbid, "NumLocalDomains", &nlocaldom);
   localdom = MALLOT(int,nlocaldom);
   ierr = DBReadVar(idbid, "LocalDomains", localdom);
   ierr = DBReadVar(idbid, "LocalName", name);
   neighbor = MALLOT(int,11);
   for (iblk = 0; iblk < num_ublk; iblk++) {
      sprintf( outstr, "Block_%i",iblk);
      DBSetDir( idbid, outstr);
      ublk = iblk + ublk0;
      ierr = DBReadVar(idbid, "NumNeighbors", &umap[ublk].nbnd);
      ierr = DBReadVar(idbid, "Extents", neighbor);
      umap[ublk].imin = neighbor[0] + NPNL - 1;
      umap[ublk].imax = neighbor[1] + NPNL - 1;
      umap[ublk].jmin = neighbor[2] + NPNL - 1;
      umap[ublk].jmax = neighbor[3] + NPNL - 1;
      umap[ublk].kmin = neighbor[4] + NPNL - 1;
      umap[ublk].kmax = neighbor[5] + NPNL - 1;
      if (umap[ublk].kmin != umap[ublk].kmax) ndims = 3;
      STREXT(umap[ublk],umap[ublk].jp,umap[ublk].kp);
      if (ndims == 2) umap[ublk].kp = 0;
      if (umap[ublk].bnd == NULL) {
         umap[ublk].bnd = ALLOT(BndMapping_t,umap[ublk].nbnd);
      }
      for (ibnd = 0; ibnd < umap[ublk].nbnd; ibnd++) {
         sprintf(outstr,"Neighbor_%i",ibnd);
         ierr = DBReadVar(idbid, outstr, neighbor);
         i = 0;
         umap[ublk].bnd[ibnd].iblk           = neighbor[i++] + ublk0;
         umap[ublk].bnd[ibnd].id             = neighbor[i++];
         umap[ublk].bnd[ibnd].orientation[0] = neighbor[i++];
         umap[ublk].bnd[ibnd].orientation[1] = neighbor[i++];
         umap[ublk].bnd[ibnd].orientation[2] = neighbor[i++];
         umap[ublk].bnd[ibnd].imin           = neighbor[i++] + NPNL - 1;
         umap[ublk].bnd[ibnd].imax           = neighbor[i++] + NPNL - 1;
         umap[ublk].bnd[ibnd].jmin           = neighbor[i++] + NPNL - 1;
         umap[ublk].bnd[ibnd].jmax           = neighbor[i++] + NPNL - 1;
         umap[ublk].bnd[ibnd].kmin           = neighbor[i++] + NPNL - 1;
         umap[ublk].bnd[ibnd].kmax           = neighbor[i++] + NPNL - 1;
         umap[ublk].bnd[ibnd].ndx            = NULL;
         CPYEXT(ext,umap[ublk].bnd[ibnd]);
         len = LENEXT(ext);
         umap[ublk].bnd[ibnd].len = len;
         umap[ublk].bnd[ibnd].ndx = MALLOT(int, len);
         extents_getndx(ext, umap[ublk].jp, umap[ublk].kp, 
                                                     umap[ublk].bnd[ibnd].ndx);
      }
      DBSetDir( idbid, "../");
   }
   for (iblk = 0; iblk < num_gblk; iblk++) {
      sprintf( outstr, "Domain_%i",iblk);
      DBSetDir( idbid, outstr);
      gblk = iblk + gblk0;
      ierr = DBReadVar(idbid, "BlockNum", &gmap[gblk].ublk);
      gmap[gblk].ublk += ublk0;
      ierr = DBReadVar(idbid, "NumNeighbors", &gmap[gblk].nbnd);
      if (gmap[gblk].nbnd > 0) ifcom = 1;
      gmap[gblk].gblk = gblk;
      ierr = DBReadVar(idbid, "Extents", neighbor);
      gmap[gblk].imin = neighbor[0] + NPNL - 1;
      gmap[gblk].imax = neighbor[1] + NPNL - 1;
      gmap[gblk].jmin = neighbor[2] + NPNL - 1;
      gmap[gblk].jmax = neighbor[3] + NPNL - 1;
      gmap[gblk].kmin = neighbor[4] + NPNL - 1;
      gmap[gblk].kmax = neighbor[5] + NPNL - 1;
      STREXT(gmap[gblk],gmap[gblk].jp,gmap[gblk].kp);
      if (ndims == 2) gmap[gblk].kp = 0;
      gmap[gblk].lblk = -1;
      for (i = 0; i < nlocaldom; i++) {
         if (localdom[i] == iblk) {
            gmap[gblk].lblk = i + gblk0;
         }
      }
      if (gmap[gblk].bnd == NULL) {
         gmap[gblk].bnd = ALLOT(BndMapping_t,gmap[gblk].nbnd);
      }
      for (ibnd = 0; ibnd < gmap[gblk].nbnd; ibnd++) {
         sprintf(outstr,"Neighbor_%i",ibnd);
         ierr = DBReadVar(idbid, outstr, neighbor);
         i = 0;
         gmap[gblk].bnd[ibnd].iblk           = neighbor[i++] + gblk0;
         gmap[gblk].bnd[ibnd].id             = neighbor[i++];
         gmap[gblk].bnd[ibnd].orientation[0] = neighbor[i++];
         gmap[gblk].bnd[ibnd].orientation[1] = neighbor[i++];
         gmap[gblk].bnd[ibnd].orientation[2] = neighbor[i++];
         gmap[gblk].bnd[ibnd].imin           = neighbor[i++] + NPNL - 1;
         gmap[gblk].bnd[ibnd].imax           = neighbor[i++] + NPNL - 1;
         gmap[gblk].bnd[ibnd].jmin           = neighbor[i++] + NPNL - 1;
         gmap[gblk].bnd[ibnd].jmax           = neighbor[i++] + NPNL - 1;
         gmap[gblk].bnd[ibnd].kmin           = neighbor[i++] + NPNL - 1;
         gmap[gblk].bnd[ibnd].kmax           = neighbor[i++] + NPNL - 1;
      }
      unblk = ublk0 + num_ublk;
      gnblk = gblk0 + num_gblk;
      DBSetDir( idbid, "../");
   }
   FREEMEM(neighbor);
   FREEMEM(localdom);
}
#endif

void decomp_pack( int **data, int *outlen ) {
   int i;
   int len;
   int gblk;
   int ublk;
   int iblk;
   int ibnd;
   int *mydata;
   len = 3 + nblk + 7* unblk + 8*gnblk;
   for (ublk = 0; ublk < unblk; ublk++) {
      len += 11 * umap[ublk].nbnd;
   }
   for (gblk = 0; gblk < gnblk; gblk++) {
      len += 11 * gmap[gblk].nbnd;
   }
   *outlen = len;
   data[0] = ALLOT(int,len);
   mydata = data[0];
   i = 0;
   mydata[i++] = unblk;
   mydata[i++] = gnblk;
   mydata[i++] = nblk;
   for (iblk = 0; iblk < nblk; iblk++) {
      mydata[i++] = domains[iblk].gblk;
   }
   for (ublk = 0; ublk < unblk; ublk++) {
      mydata[i++] = umap[ublk].nbnd;
      mydata[i++] = umap[ublk].imin - NPNL + 1;
      mydata[i++] = umap[ublk].imax - NPNL + 1;
      mydata[i++] = umap[ublk].jmin - NPNL + 1;
      mydata[i++] = umap[ublk].jmax - NPNL + 1;
      mydata[i++] = umap[ublk].kmin - NPNL + 1;
      mydata[i++] = umap[ublk].kmax - NPNL + 1;
      for (ibnd = 0; ibnd < umap[ublk].nbnd; ibnd++) {
         mydata[i++] = umap[ublk].bnd[ibnd].iblk;
         mydata[i++] = umap[ublk].bnd[ibnd].id;
         mydata[i++] = umap[ublk].bnd[ibnd].orientation[0];
         mydata[i++] = umap[ublk].bnd[ibnd].orientation[1];
         mydata[i++] = umap[ublk].bnd[ibnd].orientation[2];
         mydata[i++] = umap[ublk].bnd[ibnd].imin - NPNL + 1;
         mydata[i++] = umap[ublk].bnd[ibnd].imax - NPNL + 1;
         mydata[i++] = umap[ublk].bnd[ibnd].jmin - NPNL + 1;
         mydata[i++] = umap[ublk].bnd[ibnd].jmax - NPNL + 1;
         mydata[i++] = umap[ublk].bnd[ibnd].kmin - NPNL + 1;
         mydata[i++] = umap[ublk].bnd[ibnd].kmax - NPNL + 1;
      }
   }
   for (gblk = 0; gblk < gnblk; gblk++) {
      mydata[i++] = gmap[gblk].ublk;
      mydata[i++] = gmap[gblk].nbnd;
      mydata[i++] = gmap[gblk].imin - NPNL + 1;
      mydata[i++] = gmap[gblk].imax - NPNL + 1;
      mydata[i++] = gmap[gblk].jmin - NPNL + 1;
      mydata[i++] = gmap[gblk].jmax - NPNL + 1;
      mydata[i++] = gmap[gblk].kmin - NPNL + 1;
      mydata[i++] = gmap[gblk].kmax - NPNL + 1;
      for (ibnd = 0; ibnd < gmap[gblk].nbnd; ibnd++) {
         mydata[i++] = gmap[gblk].bnd[ibnd].iblk;
         mydata[i++] = gmap[gblk].bnd[ibnd].id;
         mydata[i++] = gmap[gblk].bnd[ibnd].orientation[0];
         mydata[i++] = gmap[gblk].bnd[ibnd].orientation[1];
         mydata[i++] = gmap[gblk].bnd[ibnd].orientation[2];
         mydata[i++] = gmap[gblk].bnd[ibnd].imin - NPNL + 1;
         mydata[i++] = gmap[gblk].bnd[ibnd].imax - NPNL + 1;
         mydata[i++] = gmap[gblk].bnd[ibnd].jmin - NPNL + 1;
         mydata[i++] = gmap[gblk].bnd[ibnd].jmax - NPNL + 1;
         mydata[i++] = gmap[gblk].bnd[ibnd].kmin - NPNL + 1;
         mydata[i++] = gmap[gblk].bnd[ibnd].kmax - NPNL + 1;
      }
   }
}
void decomp_unpack( int *data, int len, int ublk0, int gblk0 ) {
   int i,j;
   int nlocaldom;
   int iblk;
   int gblk;
   int ublk;
   int num_ublk;
   int num_gblk;
   int ibnd;
   int *localdom;
   i = 0;
   num_ublk = data[i++];
   num_gblk = data[i++];
   nlocaldom = data[i++];
   localdom = MALLOT(int,nlocaldom);
   for (iblk = 0; iblk < nlocaldom; iblk++) {
      localdom[iblk] = data[i++];
   }
   for (iblk = 0; iblk < num_ublk; iblk++) {
      ublk = iblk + ublk0;
      umap[ublk].nbnd = data[i++];
      umap[ublk].imin = data[i++] + NPNL - 1;
      umap[ublk].imax = data[i++] + NPNL - 1;
      umap[ublk].jmin = data[i++] + NPNL - 1;
      umap[ublk].jmax = data[i++] + NPNL - 1;
      umap[ublk].kmin = data[i++] + NPNL - 1;
      umap[ublk].kmax = data[i++] + NPNL - 1;
      if (umap[ublk].kmin != umap[ublk].kmax) ndims = 3;
      STREXT(umap[ublk],umap[ublk].jp,umap[ublk].kp);
      if (ndims == 2) umap[ublk].kp = 0;
      if (umap[ublk].bnd == NULL) {
         umap[ublk].bnd = ALLOT(BndMapping_t,umap[ublk].nbnd);
      }
      for (ibnd = 0; ibnd < umap[ublk].nbnd; ibnd++) {
         umap[ublk].bnd[ibnd].iblk           = data[i++] + ublk0;
         umap[ublk].bnd[ibnd].id             = data[i++];
         umap[ublk].bnd[ibnd].orientation[0] = data[i++];
         umap[ublk].bnd[ibnd].orientation[1] = data[i++];
         umap[ublk].bnd[ibnd].orientation[2] = data[i++];
         umap[ublk].bnd[ibnd].imin           = data[i++] + NPNL - 1;
         umap[ublk].bnd[ibnd].imax           = data[i++] + NPNL - 1;
         umap[ublk].bnd[ibnd].jmin           = data[i++] + NPNL - 1;
         umap[ublk].bnd[ibnd].jmax           = data[i++] + NPNL - 1;
         umap[ublk].bnd[ibnd].kmin           = data[i++] + NPNL - 1;
         umap[ublk].bnd[ibnd].kmax           = data[i++] + NPNL - 1;
         umap[ublk].bnd[ibnd].ndx            = NULL;
      }
   }
   for (iblk = 0; iblk < num_gblk; iblk++) {
      gblk = iblk + gblk0;
      gmap[gblk].ublk = data[i++];
      gmap[gblk].ublk += ublk0;
      gmap[gblk].nbnd = data[i++];
      if (gmap[gblk].nbnd > 0) ifcom = 1;
      gmap[gblk].gblk = gblk;
      gmap[gblk].imin = data[i++] + NPNL - 1;
      gmap[gblk].imax = data[i++] + NPNL - 1;
      gmap[gblk].jmin = data[i++] + NPNL - 1;
      gmap[gblk].jmax = data[i++] + NPNL - 1;
      gmap[gblk].kmin = data[i++] + NPNL - 1;
      gmap[gblk].kmax = data[i++] + NPNL - 1;
      STREXT(gmap[gblk],gmap[gblk].jp,gmap[gblk].kp);
      if (ndims == 2) gmap[gblk].kp = 0;
      gmap[gblk].lblk = -1;
      for (j = 0; j < nlocaldom; j++) {
         if (localdom[j] == iblk) {
            gmap[gblk].lblk = j + gblk0;
         }
      }
      if (gmap[gblk].bnd == NULL) {
         gmap[gblk].bnd = ALLOT(BndMapping_t,gmap[gblk].nbnd);
      }
      for (ibnd = 0; ibnd < gmap[gblk].nbnd; ibnd++) {
         gmap[gblk].bnd[ibnd].iblk           = data[i++] + gblk0;
         gmap[gblk].bnd[ibnd].id             = data[i++];
         gmap[gblk].bnd[ibnd].orientation[0] = data[i++];
         gmap[gblk].bnd[ibnd].orientation[1] = data[i++];
         gmap[gblk].bnd[ibnd].orientation[2] = data[i++];
         gmap[gblk].bnd[ibnd].imin           = data[i++] + NPNL - 1;
         gmap[gblk].bnd[ibnd].imax           = data[i++] + NPNL - 1;
         gmap[gblk].bnd[ibnd].jmin           = data[i++] + NPNL - 1;
         gmap[gblk].bnd[ibnd].jmax           = data[i++] + NPNL - 1;
         gmap[gblk].bnd[ibnd].kmin           = data[i++] + NPNL - 1;
         gmap[gblk].bnd[ibnd].kmax           = data[i++] + NPNL - 1;
      }
      unblk = ublk0 + num_ublk;
      gnblk = gblk0 + num_gblk;
   }
   FREEMEM(localdom);
}
void decomp_new( int numBlocks, int numDomains ) {
   int iblk;
   int mynumBlocks;
   int mynumDomains;
   if (mapping_allocated) return;
   mynumBlocks  = MAX(nblkx, numBlocks);
   mynumDomains = MAX(nblkx, numDomains);
   umap = ALLOT(BlockMapping_t, mynumBlocks);
   gmap = ALLOT(BlockMapping_t, mynumDomains);
   for (iblk = 0; iblk < mynumBlocks; iblk++) {     
      umap[iblk].nbnd = -1;
      umap[iblk].bnd = NULL;
   }
   for (iblk = 0; iblk < mynumDomains; iblk++) {     
      gmap[iblk].nbnd = -1;
      gmap[iblk].bnd = NULL;
   }
   mapping_allocated = 1;
}

void decomp_free( void  ) {
   int iblk;	 
   int ibnd;	 
   if (mapping_allocated == 0) return;
   for (iblk = 0; iblk < unblk; iblk++) {
      for (ibnd = 0; ibnd < umap[iblk].nbnd; ibnd++) {
         if (umap[iblk].bnd[ibnd].ndx != NULL) {
            FREEMEM(umap[iblk].bnd[ibnd].ndx);
         }
      }
      if (umap[iblk].nbnd >= 0) {
         FREEMEM(umap[iblk].bnd);
      }
   }
   for (iblk = 0; iblk < gnblk; iblk++) {
      for (ibnd = 0; ibnd < gmap[iblk].nbnd; ibnd++) {
         if (gmap[iblk].bnd[ibnd].ndx != NULL) {
            FREEMEM(gmap[iblk].bnd[ibnd].ndx);
         }
      }
      if (gmap[iblk].nbnd >= 0) {
         FREEMEM(gmap[iblk].bnd);
      }
   }
   FREEMEM(umap);
   FREEMEM(gmap);
   mapping_allocated = 0;
}

#ifdef SILO
void decomp_setdir( DBfile *idbid ) {
  int error = 0;
  DBShowErrors(DB_NONE, NULL);
  error = DBSetDir(idbid,"/Decomposition");
  if (error != 0) {
     error = DBSetDir(idbid,"/Global/Decomposition");
     if (error != 0) {
        ctlerror("decomp_setdir","Cannot find decomposition directory.");
     }
  }
  DBShowErrors(DB_TOP, NULL);
}
#endif
