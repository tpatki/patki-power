#include "irs.h"
#include "irsdmp.h"
#include "BlockMapping.h"
#ifdef SILO
void set_silo_option(DBoptlist *ioptnod, int gblk) {
   char *me = "set_silo_option";
   char msg[MAXLINE];
   static int bindx[3];
   int ierr;
   lopt[0] = 0;
   lopt[1] = 0;
   lopt[2] = 0;
   hopt[0] = 0;
   hopt[1] = 0;
   hopt[2] = 0;
   if (ndims == 3) {
     intopt = DB_CARTESIAN;
     ierr  = DBAddOption( ioptnod, DBOPT_DTIME, &ttime );
     ierr += DBAddOption( ioptnod, DBOPT_CYCLE, &cycle );
     ierr += DBAddOption( ioptnod, DBOPT_LO_OFFSET, lopt );
     ierr += DBAddOption( ioptnod, DBOPT_HI_OFFSET, hopt );
     ierr += DBAddOption( ioptnod, DBOPT_COORDSYS, &intopt );
     ierr += DBAddOption( ioptnod, DBOPT_XLABEL, "X");
     ierr += DBAddOption( ioptnod, DBOPT_YLABEL, "Y");
     ierr += DBAddOption( ioptnod, DBOPT_ZLABEL, "Z");
     ierr += DBAddOption( ioptnod, DBOPT_XUNITS, "cm");
     ierr += DBAddOption( ioptnod, DBOPT_YUNITS, "cm");
     ierr += DBAddOption( ioptnod, DBOPT_ZUNITS, "cm");
     if (ierr != 0) ctlerror(me,gv_errmsg_DBAddOption);
   } else {
     ierr  = DBAddOption( ioptnod, DBOPT_DTIME, &ttime );
     ierr += DBAddOption( ioptnod, DBOPT_CYCLE, &cycle );
     ierr += DBAddOption( ioptnod, DBOPT_LO_OFFSET, lopt );
     ierr += DBAddOption( ioptnod, DBOPT_HI_OFFSET, hopt );
     if (ifplane) {
        intopt = DB_CARTESIAN;
        ierr += DBAddOption( ioptnod, DBOPT_COORDSYS, &intopt );
        intopt2 = DB_AREA;
        ierr += DBAddOption( ioptnod, DBOPT_PLANAR, &intopt2 );
        ierr += DBAddOption( ioptnod, DBOPT_XLABEL, "X");
        ierr += DBAddOption( ioptnod, DBOPT_YLABEL, "Y");
     } else {
        intopt = DB_CYLINDRICAL;
        ierr += DBAddOption( ioptnod, DBOPT_COORDSYS, &intopt );
        intopt2 = DB_VOLUME;
        ierr += DBAddOption( ioptnod, DBOPT_PLANAR, &intopt2 );
        ierr += DBAddOption( ioptnod, DBOPT_XLABEL, "Z");
        ierr += DBAddOption( ioptnod, DBOPT_YLABEL, "R");
     }
     ierr += DBAddOption( ioptnod, DBOPT_XUNITS, "cm");
     ierr += DBAddOption( ioptnod, DBOPT_YUNITS, "cm");
     if (ierr != 0) ctlerror(me,gv_errmsg_DBAddOption);
   } 
   if(gblk != -1){
       bindx[0] = gmap[gblk].imin - NPNL + 1;
       bindx[1] = gmap[gblk].jmin - NPNL + 1;
       if(ndims == 3)
           bindx[2] = gmap[gblk].kmin - NPNL + 1;
       else
           bindx[2] = 0;
       ierr += DBAddOption( ioptnod, DBOPT_GROUPNUM, &gmap[gblk].ublk); 
       ierr += DBAddOption( ioptnod, DBOPT_BASEINDEX, bindx); 
   }
} 
#endif
