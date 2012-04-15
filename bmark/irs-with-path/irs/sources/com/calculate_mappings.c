static void calculate_mappings_hack( void ) ;
#include "irs.h"
#include "irscom.h"
#include "FunctionTimer.h"
#include "BlockMapping.h"
void calculate_mappings(void)
{
  char *me = "calculate_mappings";
  int leftovers, localblocks, gblk, proc, count, numlocalblks;
  if (hackblocking) {
     calculate_mappings_hack( ) ;
     return;
  }
  leftovers = gnblk % num_procs;
  if (leftovers != 0) { 
    ctlnotice(me,"Number of blocks is not evenly divisible among processors"
                 "\n\tWinging it.");
  }
  localblocks = gnblk / num_procs;
  if (localblocks == 0) {
     localblocks = 1;
     leftovers = 0;
  }
  gblk=0;
  proc=0;
  count=0;
  while (gblk < gnblk) {
     gmap[gblk].proc  = proc;    
     gmap[gblk].lblk = -1;
     if (proc == myid) gmap[gblk].lblk = count;
     count++;
     gblk++;
     if (count == localblocks) {
       if (leftovers > 0) {
         gmap[gblk].proc  = proc;   
         gmap[gblk].lblk = -1;
         if (proc == myid) gmap[gblk].lblk = count;
         gblk++;
         leftovers--;
       }
       count=0;
       proc++;
    }
  }
}
static void calculate_mappings_hack( void ) {
    char *me = "calculate_mappings_hack";
    int *iplane;
    int *jplane;
    int *kplane;
    int i,j,k;
    int gblk;
    int niblk;
    int njblk;
    int nkblk;
    int max;
    int proc;
    int count;
    int istep, jstep, kstep;
    niblk = 0;
    njblk = 0;
    nkblk = 0;
    if (unblk > 1) {
       ctlerror(me,
               "You may not use blocking hack with more than one user block.");
    }
    if ( ((gnblk / num_procs) != 4) && 
         ((gnblk % num_procs) != 0) )  {
       ctlerror(me,
               "The number of domains does not allow hack blocking.");
    }
    iplane = MALLOT(int, gnblk);
    jplane = MALLOT(int, gnblk);
    kplane = MALLOT(int, gnblk);
    max  = umap[0].imin;
    iplane[niblk] = max;
    while (max != umap[0].imax) {
       for (gblk = 0; gblk < gnblk; gblk++) {
          if (gmap[gblk].imin == max) {
              break;
          }
       }
       max = gmap[gblk].imax;
       niblk++;
       iplane[niblk] = max;
    }
    max  = umap[0].jmin;
    jplane[njblk] = max;
    while (max != umap[0].jmax) {
       for (gblk = 0; gblk < gnblk; gblk++) {
          if (gmap[gblk].jmin == max) {
              break;
          }
       }
       max = gmap[gblk].jmax;
       njblk++;
       jplane[njblk] = max;
    }
    if (ndims == 3) {
       max  = umap[0].kmin;
       kplane[nkblk] = max;
       while (max != umap[0].kmax) {
          for (gblk = 0; gblk < gnblk; gblk++) {
             if (gmap[gblk].kmin == max) {
                 break;
             }
          }
          max = gmap[gblk].kmax;
          nkblk++;
          kplane[nkblk] = max;
       }
    }
    istep = 1;
    jstep = 1;
    kstep = 1;
    if (( niblk % 2  == 0) && ( njblk % 2 == 0)) { 
       istep = 2;
       jstep = 2;
    } else if (( niblk % 2 == 0 ) && ( nkblk % 2 == 0)) { 
       istep = 2;
       kstep = 2;
    } else if (( njblk % 2 == 0 ) && ( nkblk % 2 == 0)) { 
       jstep = 2;
       kstep = 2;
    } else if ( niblk % 4 == 0 ) {
       istep = 4;
    } else if ( njblk % 4 == 0 ) {
       jstep = 4;
    } else if ( nkblk % 4 == 0 ) {
       kstep = 4;
    } 
    if ((istep == 1) && (jstep == 1) && (kstep == 1)) {
       ctlerror(me,"Decomposition doesn't allow for blocking.");
    }
    proc  = 0;
    count = 0;
    if (ndims == 2) {
       for (j = 0; j < njblk; j += jstep) {
          for (i = 0; i < niblk; i += istep) {
             for (gblk = 0; gblk < gnblk; gblk++) {
                if ((gmap[gblk].imin >= iplane[i    ]) &&
                    (gmap[gblk].jmin >= jplane[j    ]) &&
                    (gmap[gblk].imax <= iplane[i + istep]) &&
                    (gmap[gblk].jmax <= jplane[j + jstep])) {
                       gmap[gblk].proc = proc;
                       gmap[gblk].lblk = -1;
                       if (proc == myid) gmap[gblk].lblk = count;
                       count++;
                 }
                 if (count == 4) {
                    count = 0;
                    proc++;
                 }
             }
          }
       }
    } else {
       for (k = 0; k < nkblk; k += kstep) {
          for (j = 0; j < njblk; j += jstep) {
             for (i = 0; i < niblk; i += istep) {
                for (gblk = 0; gblk < gnblk; gblk++) {
                   if ((gmap[gblk].imin >= iplane[i    ]) &&
                       (gmap[gblk].jmin >= jplane[j    ]) &&
                       (gmap[gblk].kmin >= kplane[k    ]) &&
                       (gmap[gblk].imax <= iplane[i + istep]) &&
                       (gmap[gblk].jmax <= jplane[j + jstep]) &&
                       (gmap[gblk].kmax <= kplane[k + kstep])) {
                          gmap[gblk].proc = proc;
                          gmap[gblk].lblk = -1;
                          if (proc == myid) gmap[gblk].lblk = count;
                          count++;
                    }
                    if (count == 4) {
                       count = 0;
                       proc++;
                    }
                }
             }
          }
       }
    } 
    FREEMEM(iplane);
    FREEMEM(jplane);
    FREEMEM(kplane);
}
