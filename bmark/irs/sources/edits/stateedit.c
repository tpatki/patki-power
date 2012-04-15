#include "irs.h"
#include "irslag.h"
#include "irsbndry.h"
#include "irsedits.h"
#include "irsparm.h"
#include "BlockMapping.h"
int stateedit( void )
{
   char *me = "stateedit";
   char msg[256];
   int i1,i2,j1,j2,k1,k2;
   int imin, imax, jmin,jmax, kmin, kmax;
   int len, iblk, ibc;
   int numzones, numnodes, ns;
   int *ndx;
   char bcname[10];
   char blktype[10];
   char bcind[20];
   ctlmsg("-------------------------------------------------------------------------------"); 
   sprintf(msg,"State edit:  Cycle: %i   Time step: %e",cycle,ttime);	
   ctlmsg(msg);
   ctlmsg("-------------------------------------------------------------------------------\n"); 
   sprintf(msg,"Irs Version: %s   Run name: %s \n",IRS_VERSION,pbnm);	
   ctlmsg(msg);
   sprintf(msg,"deltat = %.6e  Lagrange subcycles = %i",deltat,ndtg);	
   ctlmsg(msg);
   sprintf(msg,"ndims = %i     # of blocks = %i \n",ndims,nblk);	
   ctlmsg(msg);
   ctlmsg("Block Data:");
   for (iblk=0;iblk<nblk;iblk++) {
      if (domains[iblk].type==QUAD2D) {
	 strcpy(blktype,"quad 2D");
      } else {
	 strcpy(blktype,"hex 3D");
      }
      sprintf(msg,"\n   Block %i (user blk %i, global blk %i)   Type: %s",iblk,gmap[domains[iblk].gblk].ublk,domains[iblk].gblk,blktype);
      ctlmsg(msg);
      if (ndims==2) {
         sprintf(msg,"      imin: %i  imax: %i  jmin: %i  jmax: %i  jp: %i",
	    domains[iblk].imin,domains[iblk].imax,domains[iblk].jmin,domains[iblk].jmax,
	    domains[iblk].jp);
         ctlmsg(msg);
         numnodes=((domains[iblk].imax-domains[iblk].imin+1)*
                  (domains[iblk].jmax-domains[iblk].jmin+1));
         numzones=((domains[iblk].imax-domains[iblk].imin)*
                  (domains[iblk].jmax-domains[iblk].jmin));
      } else {
         sprintf(msg,"      imin: %i  imax: %i  jmin: %i  jmax: %i  kmin: %i  kmax: %i", domains[iblk].imin,domains[iblk].imax,domains[iblk].jmin,domains[iblk].jmax,domains[iblk].kmin,domains[iblk].kmax);
         ctlmsg(msg);
         sprintf(msg,"      jp: %i  kp: %i",domains[iblk].jp,domains[iblk].kp);
         ctlmsg(msg);
	 numnodes=((domains[iblk].imax-domains[iblk].imin+1)*
                   (domains[iblk].jmax-domains[iblk].jmin+1)*
                   (domains[iblk].kmax-domains[iblk].kmin+1));
	 numzones=((domains[iblk].imax-domains[iblk].imin)*
                   (domains[iblk].jmax-domains[iblk].jmin)*
                   (domains[iblk].kmax-domains[iblk].kmin));
      }
      sprintf(msg,"      # zones = %i  # nodes = %i",numzones, numnodes); 
      ctlmsg(msg);
      sprintf(msg,"      # phony zones = %i  # total zones = %i",domains[iblk].nnalls-numzones,domains[iblk].nnalls);
      ctlmsg(msg);
      sprintf(msg,"      # mixed zone slots = %i  # mixed zones = %i",domains[iblk].mixmax,domains[iblk].nmixzn);
      ctlmsg(msg);
      sprintf(msg,"      Boundary Conditions:");
      ctlmsg(msg);
      for (ibc=0;ibc<domains[iblk].nbc;ibc++) {
         sprintf(msg,"         Cond: %i  ",ibc);
         ctlmsg1(msg);
         ndx=domains[iblk].bc[ibc].ndx;
         len=domains[iblk].bc[ibc].len;
         if (ndims==2) {
            NDXEXT2D(ndx[0],i1,j1,domains[iblk]);
            NDXEXT2D(ndx[len-1],i2,j2,domains[iblk]);
            imin=MIN(i1,i2);
            imax=MAX(i1,i2);
            jmin=MIN(j1,j2);
            jmax=MAX(j1,j2);
            sprintf(bcind,"(%i:%i,%i:%i) ",imin,imax,jmin,jmax);
         } else {
            NDXEXT3D(ndx[0],i1,j1,k1,domains[iblk]);
            NDXEXT3D(ndx[len-1],i2,j2,k2,domains[iblk]);
            imin=MIN(i1,i2);
            imax=MAX(i1,i2);
            jmin=MIN(j1,j2);
            jmax=MAX(j1,j2);
            kmin=MIN(k1,k2);
            kmax=MAX(k1,k2);
            sprintf(bcind,"(%i:%i,%i:%i,%i:%i) ",imin,imax,jmin,jmax,kmin,kmax);
         }
         getbcname(bcname,ibc,&domains[iblk]);
         sprintf(msg,"Type: %s %s ",bcname,bcind);
         ctlmsg(msg);
      }
      for (ibc=0;ibc<domains[iblk].nbnd;ibc++) {
         sprintf(msg,"         Cond: %i  ",ibc);
         ctlmsg1(msg);
         ndx=domains[iblk].bnd[ibc].ndx_send;
         len=domains[iblk].bnd[ibc].len_nsend1;
         if (len == 0) len = domains[iblk].bnd[ibc].len_nsendc;
         if (len == 0) len = domains[iblk].bnd[ibc].len_nrecvc;
         if (ndims==2) {
            NDXEXT2D(ndx[0],i1,j1,domains[iblk]);
            NDXEXT2D(ndx[len-1],i2,j2,domains[iblk]);
            imin=MIN(i1,i2);
            imax=MAX(i1,i2);
            jmin=MIN(j1,j2);
            jmax=MAX(j1,j2);
            sprintf(bcind,"(%i:%i,%i:%i) ",imin,imax,jmin,jmax);
         } else {
            NDXEXT3D(ndx[0],i1,j1,k1,domains[iblk]);
            NDXEXT3D(ndx[len-1],i2,j2,k2,domains[iblk]);
            imin=MIN(i1,i2);
            imax=MAX(i1,i2);
            jmin=MIN(j1,j2);
            jmax=MAX(j1,j2);
            kmin=MIN(k1,k2);
            kmax=MAX(k1,k2);
            sprintf(bcind,"(%i:%i,%i:%i,%i:%i) ",imin,imax,jmin,jmax,kmin,kmax);
         }
         strcpy(bcname,"bnd");
         sprintf(msg,"Type: %s %s with block: %i\n",bcname,bcind,domains[iblk].bnd[ibc].blk_send);
         ctlmsg1(msg);
      }
   }
   ctlmsg("\n-------------------------------------------------------------------------------\n"); 
   return(0);
}
