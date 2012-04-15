#include "irs.h"
#include "irsgen.h"
#include "irscom.h"
#include "irsreg.h"
#include "BlockMapping.h"
#include "Extents.h"
#include "FunctionTimer.h"
#include "Region.h"
void sanityck( void )
{
   char *me = "sanityck";
   char msg[MAXLINE];
   int i,j,k;
   int ip, ir, is;
   int n;
   int iface;
   int iblk;
   int gblk;
   int ibc,len;
   int missing_material;
   int missing_mesh;
   int missing_boundary;
   int missing_boundary_flag;
   int dom_largest;
   int dom_smallest;
   double nrzones,ntzones;
   double dom_avezones;
   double dom_maxzones;
   double dom_minzones;
   int *node;
   int *ndx;
   int *regchk;
   double ratio;
   Extents_t extin;
   Extents_t extout[27];


   dom_smallest = -1;
   dom_largest  = -1;
   dom_avezones = 0.;
   dom_maxzones = -plarge;
   dom_minzones = plarge;
   ntzones      = 0.0;
   for (gblk = 0; gblk < gnblk; gblk++) {
      if (ndims == 3) {
         nrzones = 1.0*(gmap[gblk].imax - gmap[gblk].imin) *
                       (gmap[gblk].jmax - gmap[gblk].jmin) *
                       (gmap[gblk].kmax - gmap[gblk].kmin);
         ntzones += 1.0*(gmap[gblk].imax - gmap[gblk].imin + NPNL + NPNR + 1)*
                        (gmap[gblk].jmax - gmap[gblk].jmin + NPNL + NPNR + 1)*
                        (gmap[gblk].kmax - gmap[gblk].kmin + NPNL + NPNR + 1);
      } else {
         nrzones = 1.0*(gmap[gblk].imax - gmap[gblk].imin) *
                       (gmap[gblk].jmax - gmap[gblk].jmin);
         ntzones += 1.0*(gmap[gblk].imax - gmap[gblk].imin + NPNL + NPNR + 1)*
                        (gmap[gblk].jmax - gmap[gblk].jmin + NPNL + NPNR + 1);
      } 
      if (nrzones > dom_maxzones) {
         dom_largest = gblk;
         dom_maxzones = nrzones;
      }
      if (nrzones < dom_minzones) {
         dom_smallest = gblk;
         dom_minzones = nrzones;
      }
      dom_avezones += nrzones;
   }
   if (ifcom) {
      ratio = (dom_avezones)/(ntzones);
      sprintf(msg,"\nRatio of real zones to total zones - %f\n",ratio);
      ctlmsg(msg);
      sprintf(msg,"Total number of domains is %4i.",gnblk);
      ctlmsg(msg);
      sprintf(msg,"Largest  domain is %4i with %10.0f zones.",
                   dom_largest,dom_maxzones);
      ctlmsg(msg);
      sprintf(msg,"Smallest domain is %4i with %10.0f zones.",
                   dom_smallest,dom_minzones);
      ctlmsg(msg);
      ratio = dom_avezones / (double) gnblk;
      sprintf(msg,"Average domain has %10.0f zones.\n",ratio);
      ctlmsg(msg);
   }
   sprintf(msg,"Total number of zones  %10.0f.\n",dom_avezones);
   ctlmsg(msg);
   missing_material = 0;
   for (iblk = 0; iblk < nblk; iblk++) {
      for (i = 0; i < domains[iblk].namix; i++) {
         if (domains[iblk].ireg[i] > nreg) {
            missing_material = domains[iblk].ireg[i];
         }
      }
   }
   if (missing_material != 0) {
      sprintf(msg,"Found a bad or undefined material number %i.",missing_material);
      coredumpflag = FALSE;
      ctlerror(me,msg);
   }
   regchk = ALLOT(int,nregx);
   missing_material = 0;
   for (iblk = 0; iblk < nblk; iblk++) {
      if (ndims == 2) {
         for (j = domains[iblk].jmin; j < domains[iblk].jmax; j++) {
            for (i = domains[iblk].imin; i < domains[iblk].imax; i++) {
               ip = i + j*domains[iblk].jp;
               ir = domains[iblk].ireg[ip];
               if (ir > 0) regchk[ir]++;
               if (ir == 0) missing_material = 1;
            }
         }
      } else {
         for (k = domains[iblk].kmin; k < domains[iblk].kmax; k++) {
            for (j = domains[iblk].jmin; j < domains[iblk].jmax; j++) {
               for (i = domains[iblk].imin; i < domains[iblk].imax; i++) {
                  ip = i + j*domains[iblk].jp + k*domains[iblk].kp;
                  ir = domains[iblk].ireg[ip];
                  if (ir > 0) regchk[ir]++;
                  if (ir == 0) missing_material = 1;
               }
            }
         }
      }
   }
   if (missing_material) {
      sprintf(msg,"Problem has zones with no material specified.\n");
      coredumpflag = FALSE;
      ctlerror(me,msg);
   }
   if (ifparallel) {
      comreduce(regchk, nreg + 1, COM_MAX, COM_ALL, COM_INT);
   }
   for (ir = 1; ir <= nreg; ir++ ) {
      if (regchk[ir] == 0) {
          sprintf(msg,"Material %i is unused.\n",ir);
          ctlmsg(msg);
      }
   }
   FREEMEM(regchk);
   for (iblk = 0; iblk < nblk; iblk++) {
      missing_mesh = 0;
      if (ndims == 2) {
         for (j = domains[iblk].jmin; j <= domains[iblk].jmax; j++) {
            for (i = domains[iblk].imin; i <= domains[iblk].imax; i++) {
               ip = i + j*domains[iblk].jp;
               if (domains[iblk].node[ip] == 0) missing_mesh = ip;
            }
         }
         if (missing_mesh > 0) {
            gblk = domains[iblk].gblk;
            NDXEXT2D(missing_mesh,i,j,domains[iblk]);
            sprintf(msg,"Missing mesh specification %i:(%i,%i)\n",
                                   gmap[gblk].ublk,
                                   i - NPNL + gmap[gblk].imin,
                                   j - NPNL + gmap[gblk].jmin);
         }
      } else {
         for (k = domains[iblk].kmin; k <= domains[iblk].kmax; k++) {
            for (j = domains[iblk].jmin; j <= domains[iblk].jmax; j++) {
               for (i = domains[iblk].imin; i <= domains[iblk].imax; i++) {
                  ip = i + j*domains[iblk].jp + k*domains[iblk].kp;
                  if (domains[iblk].node[ip] == 0) missing_mesh = ip;
               }
            }
         }
         if (missing_mesh > 0) {
            gblk = domains[iblk].gblk;
            NDXEXT3D(missing_mesh,i,j,k,domains[iblk]);
            sprintf(msg,"Missing mesh specification %i:(%i,%i,%i)\n",
                                   gmap[gblk].ublk,
                                   i - NPNL + gmap[gblk].imin,
                                   j - NPNL + gmap[gblk].jmin,
                                   k - NPNL + gmap[gblk].kmin);
         }
      } 
      if (missing_mesh > 0) {
         ctlerror(me,msg);
      }
   }
   for (iblk = 0; iblk < nblk; iblk++) {
      node = ALLOT(int,domains[iblk].nnalls);
      for (i = 0; i < domains[iblk].nnalls; i++) node[i] = 0;
      for (ibc = 0; ibc < domains[iblk].nbc; ibc++) {
         ndx = domains[iblk].bc[ibc].ndx;
         len = domains[iblk].bc[ibc].len;
         for (i = 0; i < len; i++) {
            node[ndx[i]] = 1;
         }
      }
      for (ibc = 0; ibc < domains[iblk].nbnd; ibc++) {
         ndx = domains[iblk].bnd[ibc].ndx_send;
         len = domains[iblk].bnd[ibc].len_nsend1; 
         for (i = 0; i < len; i++) {
            node[ndx[i]] = 1;
         }
      }
      CPYEXT(extin,domains[iblk]);
      missing_boundary = 0;
      if (ndims == 2) {
         n = extents_redext(extout,extin,EDGE);
         for (iface = 0; iface < n; iface++) {
            missing_boundary_flag = 0;
            for (j = extout[iface].jmin; j <= extout[iface].jmax; j++) {
               for (i = extout[iface].imin; i <= extout[iface].imax; i++) {
                  ip = i + j*domains[iblk].jp;
                  if (node[ip] == 0) missing_boundary_flag = 1;
               }
            }
            if (missing_boundary_flag) {
               missing_boundary = 1;
               sprintf(msg,"Missing boundary condition on %i:(%i:%i,%i:%i)\n",
                               gmap[domains[iblk].gblk].ublk,
                               extout[iface].imin - NPNL + 1,
                               extout[iface].imax - NPNL + 1,
                               extout[iface].jmin - NPNL + 1,
                               extout[iface].jmax - NPNL + 1);
               ctlmsg(msg);
            }
         }
      } else {
         n = extents_redext(extout,extin,FACE);
         for (iface = 0; iface < n; iface++) {
            missing_boundary_flag = 0;
            for (k = extout[iface].kmin; k <= extout[iface].kmax; k++) {
               for (j = extout[iface].jmin; j <= extout[iface].jmax; j++) {
                  for (i = extout[iface].imin; i <= extout[iface].imax; i++) {
                     ip = i + j*domains[iblk].jp + k*domains[iblk].kp;
                     if (node[ip] == 0) missing_boundary_flag = 1;
                  }
               }
            }
            if (missing_boundary_flag) {
               missing_boundary = 1;
               sprintf(msg,"Missing boundary condition on %i:(%i:%i,%i:%i,%i:%i)\n",
                               gmap[domains[iblk].gblk].ublk,
                               extout[iface].imin - NPNL + 1,
                               extout[iface].imax - NPNL + 1,
                               extout[iface].jmin - NPNL + 1,
                               extout[iface].jmax - NPNL + 1,
                               extout[iface].kmin - NPNL + 1,
                               extout[iface].kmax - NPNL + 1);
               ctlmsg(msg);
            }
         }
      } 
      if (missing_boundary) {
         sprintf(msg,"Problem has missing boundary conditions.\n");
         coredumpflag = FALSE;
         ctlerror(me,msg);
      }
      FREEMEM(node); 
   }
   n = 0;
   for (ir = 1; ir <= nreg; ir++) {
      for (is = 0; is < reg[ir].nspec; is++) {
         if (reg[ir].species[is].abar < ptiny) {
            sprintf(msg,"Species %s has abar = 0. \n\t\t Make sure that you've either set abar \n\t\tor given atomic weights for the components.",reg[ir].species[is].name);
            ctlnotice(me,msg);
            n++;
         }
      }
   }
   if (n > 0) {
      sprintf(msg,"Found species abar = 0");
      ctlerror(me,msg);
   }
   n = 0;
   for (ir = 1; ir <= nreg; ir++) {
      for (is = 0; is < reg[ir].nspec; is++) {
         if (reg[ir].species[is].zbar <= 0.) {
            sprintf(msg,"Species %s has zbar <= 0. \n\t\t Make sure that you've set zbar.",reg[ir].species[is].name);
            ctlnotice(me,msg);
            n++;
         }
      }
   }
   if (n > 0) {
      sprintf(msg,"Found species zbar <= 0");
      ctlerror(me,msg);
   }
   n = 0;
   for (ir = 1; ir <= nreg; ir++) {
      if (reg[ir].nspec > 0) n++;
   }
   if ((n != 0) && (n != nreg)) {
      for (ir = 1; ir <= nreg; ir++) {
         if (reg[ir].nspec == 0) {
            sprintf(msg,"Region %i does not have any species.",ir);
            ctlnotice(me,msg);
         }
      }
      sprintf(msg,"There are regions with no species specified.");
      ctlerror(me,msg);
   }

}
