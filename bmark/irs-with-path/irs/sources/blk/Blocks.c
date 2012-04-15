#include "irs.h"
#include "irsblk.h"
#include "irsbndry.h"
#include "irsctl.h"
#include "irsobjects.h"
#include "irscom.h"
#include "BlockMapping.h"
#include "Extents.h"
#include "FunctionTimer.h"
#include "UserList.h"
#define BLOCKS_OCTANT   3
#define BLOCKS_QUADRANT 4
#define BLOCKS_HALF     5
#define BLOCKS_FULL     6
#define BLOCKS_BALL     0
#define BLOCKS_SHELL    1
#define BLOCKS_CYL      2
static void Blocks_addblock(int imax, int jmax, int kmax) ;
static void Blocks_setbnd(int ublk1, int face1, int ublk2, int face2,  int or1,
                   int or2, int or3);
static int Blocks_ballshell( int mode);
static void Blocks_ballshell2d( int mode, int type, int rads, int angs, int *dblk,
                                int imax_in, int jmax_in);
static void Blocks_ballshell3d( int mode, int type, int rads, int angs, int *dblk,
                         int imax_in, int jmax_in, int kmax_in) ;
static void Blocks_cylinder3d( int mode, int type, int rads, int angs, int len, 
                        int *dblk, int imax_in, int jmax_in);
static void Blocks_matchballshell3d( int type, int ublk_start, int *dblk, int repeat) ;
static void Blocks_matchcyl3d( int type, int ublk_start, int *dblk, int repeat) ;
static char listname_base[MAXLINE];
static int  current_blk;
static int  repeat_num;
int Blocks_parse( void ) {
   char *me = "Blocks_/parse temp";
   char op[MAXLINE],msg[MAXLINE];
   char *oname;
   int i, repeat;
   int cflag;
   int imax, jmax, kmax;
   int gblk;
   int gotone;
   int error = 0;
   int ifblkdiv;
   int count = 0;
   if (nblk > 0) {
      sprintf(msg,"It appears that blocks already exist in the problem.\n\t\tThe blocks command may only be used once.");
      ctlerror(me,msg);
   }
   gotone = 1;
   ifblkdiv = 0;
   while (gotone) {
      peekc(op);
      if (!strcmp(op,"block")) {
         geta(op);
         imax = geti(&cflag) + NPNL - 1;
         jmax = geti(&cflag) + NPNL - 1;
	 if (ndims == 3) kmax = geti(&cflag) + NPNL - 1;
         repeat = 1;
         peekc(op);
         if (!strcmp(op,"repeat")) {
            geta(op);
            repeat = geti(&cflag);
         }
         sprintf(listname_base,"BLK%i_",count);
         oname = ObjectName_get();
         if (oname != NULL) strcpy(listname_base,oname);
         current_blk = 1;
         for (repeat_num = 0; repeat_num < repeat; repeat_num++) {
	    Blocks_addblock(imax, jmax, kmax);
         }
	 count++;
      } else if (!strcmp(op,"ball")) {
         geta(op);
         sprintf(listname_base,"ball%i_",count);
         oname = ObjectName_get();
         if (oname != NULL) strcpy(listname_base,oname);
         error = Blocks_ballshell(BLOCKS_BALL);
	 if (error != 0) gotone = 0;
	 count++;
      } else if (!strcmp(op,"shell")) {
         geta(op);
         sprintf(listname_base,"shell%i_",count);
         oname = ObjectName_get();
         if (oname != NULL) strcpy(listname_base,oname);
         error = Blocks_ballshell(BLOCKS_SHELL);
	 if (error != 0) gotone = 0;
	 count++;
      } else if (!strcmp(op,"cyl")) {
         geta(op);
         sprintf(listname_base,"cyl%i_",count);
         oname = ObjectName_get();
         if (oname != NULL) strcpy(listname_base,oname);
         error = Blocks_ballshell(BLOCKS_CYL);
	 if (error != 0) gotone = 0;
	 count++;
      } else if (!strcmp(op,"bnd")) {
         geta(op);
         error = bndin();
	 if (error != 0) gotone = 0;
      } else if (!strcmp(op,"matchbnd")) {
         geta(op);
         error = Blocks_match();
	 if (error != 0) gotone = 0;
      } else if (!strcmp(op,"blkdiv")) {
         geta(op);
         blkdivin(0);
         ifblkdiv = 1;
      } else if (!strcmp(op,"name")) {
         geta(op);
         error = ObjectName_input();
      } else if (!strcmp(op,"done")) {
         geta(op);
         gotone = 0;
      } else {
         sprintf(msg,"Command %s not recognized in blocks command.",op);
         ctlwarning(me,msg);
         gotone = 0;
         error = 1;
      } 
   }
   if (error != 0) return(-1);
   if ((ifparallel) && (ifblkdiv == 0)) blkdivin(1);
   if (nblkx <= gnblk) {
      sprintf(msg,"Number of domains (%i) exceeds nblkx (%i).  Please increase nblkx.",num_procs,nblkx);
      ctlerror(me,msg);
   }
   calculate_mappings();
   nblk = 0;
   for (gblk = 0; gblk < gnblk; gblk++) {
      if (gmap[gblk].proc == myid) {
         domains[nblk].type     = HEX3D ;
         domains[nblk].sclnamix = sclnamix ;
         TRSEXT(domains[nblk],gmap[gblk],gmap[gblk]);
         if (ndims == 2) {
            domains[nblk].type     = QUAD2D ;
            domains[nblk].kmin = 0;
            domains[nblk].kmax = 0;
         } 
         initblk(nblk,&domains[nblk]);
         domains[nblk].gblk = gblk;
         domain_hash_tbl_rgst(&(domains[nblk]));
         nblk++;
      }
   }
   bndry_init();
   initcom( NULL, 0);
   if (ifcom) varcom_bufinit();
   return(0) ;
}
static int Blocks_ballshell( int mode) {
   char *me = "Blocks_ballshell";
   char *oname;
   char op[MAXLINE];
   char msg[MAXLINE];
   char number[MAXLINE];
   int i,j;
   int error = 0;
   int rads;
   int angs;
   int cflag;
   int gotone;
   int type;
   int len;
   int imax, jmax, kmax;
   int repeat = 1;
   int ifmatch = 0;
   int ublk_start;
   int dblk[7];
   rads = -1;
   angs = -1;
   len  = -1;
   imax = -1;
   jmax = -1;
   kmax = -1;
   dblk[0] = 0;
   dblk[1] = 0;
   dblk[2] = 0;
   dblk[3] = 0;
   dblk[4] = 0;
   dblk[5] = 0;
   dblk[6] = 0;
   geta(op);
   if (!strcmp(op,"oct")) {
      type = BLOCKS_OCTANT;
      dblk[4] = 1;
      dblk[5] = 1;
      dblk[6] = 1;
   } else if (!strcmp(op,"quad")) {
      type = BLOCKS_QUADRANT;
      dblk[5] = 1;
      dblk[6] = 1;
      if (mode == BLOCKS_CYL) {
         dblk[3] = 1;
         dblk[4] = 1;
      }
   } else if (!strcmp(op,"half")) {
      type = BLOCKS_HALF;
      dblk[6] = 1;
      if (mode == BLOCKS_CYL) {
         dblk[4] = 1;
         dblk[5] = 1;
      }
   } else if (!strcmp(op,"full")) {
      type = BLOCKS_FULL;
   } else {
      sprintf(msg,"Ball, Shell or Cyl type %s is not recognized.\n\t\tPlease choose from oct, quad, half, or full.",op);
      ctlwarning(me,msg);
      return(-1);
   } 
   if (ndims == 2) {
      if (mode == BLOCKS_CYL) {
         sprintf(msg,"Cylinder is not available in 2d");
         ctlwarning(me,msg);
         return(-1);
      }
      if ((type == BLOCKS_OCTANT) || (type == BLOCKS_QUADRANT)) {
         sprintf(msg,"Ball or shell in 2d must either be 'half' or 'full'");
         ctlwarning(me,msg);
         return(-1);
      }
   } else {
      if ((type == BLOCKS_OCTANT) && (mode == BLOCKS_CYL)) {
         sprintf(msg,"Cylinder must be 'quad', 'half' or 'full'");
         ctlwarning(me,msg);
         return(-1);
      }
   } 
   gotone = 1;
   while (gotone) {
      peekc(op);
      if (!strcmp(op,"del")) {
         geta(op);
         i = geti(&cflag);
         if (i > 6) {
            sprintf(msg,"Block number %i is out of range in del",i);
            ctlwarning(me,msg);
            gotone = 0;
         } else if (i < 0) {
         } else {
            dblk[i] = 1;
         }
      } else if (!strcmp(op,"box")) {
          geta(op);
          imax = geti(&cflag);
          jmax = geti(&cflag);
          if ((ndims == 3) && (mode != BLOCKS_CYL))  kmax = geti(&cflag);
      } else if (!strcmp(op,"rad")) {
         geta(op);
         rads = geti(&cflag);
      } else if (!strcmp(op,"ang")) {
         geta(op);
         angs = geti(&cflag);
      } else if (!strcmp(op,"repeat")) {
         geta(op);
         repeat = geti(&cflag);
      } else if (!strcmp(op,"match")) {
         geta(op);
         ifmatch = 1;
      } else if (!strcmp(op,"len")) {
         geta(op);
         len = geti(&cflag);
      } else {
         gotone = 0;
      } 
   }
   if (ndims == 2) {
      if (rads == -1) {
         sprintf(msg,"rad has not be specified for ball command");
         ctlerror(me,msg);
      }
      if ((angs == -1) && (imax == -1)) {
         sprintf(msg,"Either ang or box must be specified for ball command");
         ctlerror(me,msg);
      }
      for (repeat_num = 0; repeat_num < repeat; repeat_num++) {
         Blocks_ballshell2d( mode, type, rads, angs, dblk, imax, jmax);
      }
   } else {
      if (mode == BLOCKS_CYL) {
         if ((rads == -1) || (len == -1) || (angs == -1)) {
            sprintf(msg,"Either ang, len, or rad has not be specified for cyl command");
            ctlerror(me,msg);
         }
         ublk_start = unblk;
         for (repeat_num = 0; repeat_num < repeat; repeat_num++) {
            Blocks_cylinder3d( mode, type, rads, angs, len, dblk, imax, jmax);
         }
         if ((ifmatch) && (repeat > 1)) {
            Blocks_matchcyl3d( type, ublk_start, dblk, repeat) ;
         }
      } else {
         if (rads == -1) {
            sprintf(msg,"rad has not be specified for ball command");
            ctlerror(me,msg);
         }
         if ((angs == -1) && (imax == -1)) {
            sprintf(msg,"Either ang or box must be specified for ball command");
            ctlerror(me,msg);
         }
         ublk_start = unblk;
         for (repeat_num = 0; repeat_num < repeat; repeat_num++) {
            Blocks_ballshell3d( mode, type, rads, angs, dblk, imax, jmax, kmax );
         }
         if ((ifmatch) && (repeat > 1)) {
            Blocks_matchballshell3d(type, ublk_start, dblk, repeat) ;
         }
      }
   }
   return(0);
}
static void Blocks_addblock(int imax, int jmax, int kmax) {
   char *me = "Blocks_addblock";
   char msg[MAXLINE];
   char number[MAXLINE];
   if (ndims == 3) {
      domains[nblk].type = HEX3D ;
      domains[nblk].imin = NPNL ;
      domains[nblk].jmin = NPNL ;
      domains[nblk].kmin = NPNL ;
      domains[nblk].imax = imax;
      domains[nblk].jmax = jmax;
      domains[nblk].kmax = kmax;
   } else {
      kmax = 0;
      domains[nblk].type = QUAD2D ;
      domains[nblk].imin = NPNL ;
      domains[nblk].jmin = NPNL ;
      domains[nblk].kmin = 0 ;
      domains[nblk].imax = imax;
      domains[nblk].jmax = jmax;
      domains[nblk].kmax = 0 ;        
   } 
   blknum = unblk ;
   domains[nblk].jp = domains[nblk].imax - domains[nblk].imin + 
                            1 + NPNL + NPNR;
   domains[nblk].kp = 0;
   if (ndims == 3) {
      domains[nblk].kp = domains[nblk].jp * (domains[nblk].jmax - 
	                       domains[nblk].jmin + 1 + NPNL + NPNR);
   }
   sprintf(number,"%i",unblk);
   sprintf(msg,"%s.%i",listname_base,current_blk - 1);
   UserList_add(number,msg);
   sprintf(msg,"%s_%i",listname_base,repeat_num);
   UserList_add(number,msg);
   sprintf(msg,"%s_%i.%i",listname_base,repeat_num,current_blk - 1);
   UserList_add(number,msg);
   UserList_add(number,listname_base);
   setumap( &domains[nblk] ) ;
   nblk++;
   if (nblk > nblkx) {
      sprintf(msg,"Number of blocks exceeds nblkx = %d",nblkx);
      ctlerror(me,msg);
   }
}
int Blocks_match( void ) {
   char *me = "Blocks_match";
   char op[MAXLINE];
   char msg[MAXLINE];
   int ublk1, ublk2, face1, face2, or1, or2, or3;
   int cflag;
   int error = 0;
   UserList_t *ul1;
   UserList_t *ul2;
   or1 = 1;
   or2 = 2;
   or3 = 3;
   geta(op);
   peekc(op);
   ublk1 = -1;
   ublk2 = -1;
   if (!strcmp(op,"(")) {
      error = UserList_parse("MBlk1");
      if (error != 0) {
         ctlerror(me,"Failed to parse first user block list in matchbnd command.");
      }
   } else {
      ublk1 = geti(&cflag);
      if ((ublk1 < 0) || (ublk1 >= unblk)) {
         sprintf(msg,"Block %i is out of range.",ublk1);
         ctlerror(me,msg);
      }
   }
   geta(op);
   face1 = geti(&cflag);
   geta(op);
   peekc(op);
   if (!strcmp(op,"(")) {
      error = UserList_parse("MBlk2");
      if (error != 0) {
         ctlerror(me,"Failed to parse second user block list in matchbnd command.");
      }
   } else {
      ublk2 = geti(&cflag);
      if ((ublk2 < 0) || (ublk2 >= unblk)) {
         sprintf(msg,"Block %i is out of range.",ublk2);
         ctlerror(me,msg);
      }
   }
   geta(op);
   face2 = geti(&cflag);
   if ((face1 < 0) || (face1 >= 6)) {
      sprintf(msg,"Face %i is out of range. It should be between 0 and 5.",face1);
      ctlerror(me,msg);
   }
   if ((face2 < 0) || (face2 >= 6)) {
      sprintf(msg,"Face %i is out of range. It should be between 0 and 5.",face2);
      ctlerror(me,msg);
   }
   peekc(op);
   if (!strcmp(op,",")) {
      geta(op);
      or1 = geti(&cflag);
      geta(op);
      or2 = geti(&cflag);
      geta(op);
      or3 = geti(&cflag);
      geta(op);
   } else if (!strcmp(op,")")) {
      geta(op);
   } else {
      sprintf(msg,"Match command must end with a closed parenthesis.");
      ctlerror(me,msg);
   } 
   if ((ublk1 == -1) && (ublk2 == -1)) {
      ul1 = UserList_find("MBlk1");
      ul2 = UserList_find("MBlk2");
      while ((ul1 != NULL) && (ul2 != NULL)) {
         ublk1 = atoi(ul1->name);
         if ((ublk1 < 0) || (ublk1 >= unblk)) {
            sprintf(msg,"Block %i is out of range.",ublk1);
            ctlerror(me,msg);
         }
         ublk2 = atoi(ul2->name);
         if ((ublk2 < 0) || (ublk2 >= unblk)) {
            sprintf(msg,"Block %i is out of range.",ublk2);
            ctlerror(me,msg);
         }
         Blocks_setbnd(ublk1, face1, ublk2, face2, or1, or2, or3);
         ul1 = ul1->next;
         ul2 = ul2->next;
      }
      if ((ul1 != NULL) || (ul2 != NULL)) {
         sprintf(msg,"Block lists are of different length in matchbnd command.");
         ctlerror(me,msg);
      }
      UserList_del("MBlk1"); 
      UserList_del("MBlk2"); 
   } else {
      Blocks_setbnd(ublk1, face1, ublk2, face2, or1, or2, or3);
   }
   return(0);
}
static void Blocks_setbnd(int ublk1, int face1, int ublk2, int face2,  int or1,
                   int or2, int or3)
{
   int sign;	 
   int n;
   int nbnd1, nbnd2;
   Extents_t exts[6], ext;
   if (ublk1 < 0) return;
   if (ublk2 < 0) return;
   nbnd1 = umap[ublk1].nbnd;
   nbnd2 = umap[ublk2].nbnd;
   if (ublk1 == ublk2) nbnd2 = nbnd1 + 1;
   umap[ublk1].bnd[nbnd1].iblk = ublk2;
   umap[ublk1].bnd[nbnd1].id   = nbnd2;
   umap[ublk2].bnd[nbnd2].iblk = ublk1;
   umap[ublk2].bnd[nbnd2].id   = nbnd1;
   umap[ublk1].bnd[nbnd1].orientation[0] = or1;
   umap[ublk1].bnd[nbnd1].orientation[1] = or2;
   umap[ublk1].bnd[nbnd1].orientation[2] = or3;
   sign = 1;
   if (or1 < 0) sign = -1;
   umap[ublk2].bnd[nbnd2].orientation[abs(or1) - 1] = sign;
   sign = 1;
   if (or2 < 0) sign = -1;
   umap[ublk2].bnd[nbnd2].orientation[abs(or2) - 1] = 2 * sign;
   sign = 1;
   if (or3 < 0) sign = -1;
   umap[ublk2].bnd[nbnd2].orientation[abs(or3) - 1] = 3 * sign;
   CPYEXT(ext,umap[ublk1]);
   if (ndims == 2) {
      n = extents_redext(exts, ext, EDGE);
   } else {
      n = extents_redext(exts, ext, FACE);
   } 
   CPYEXT(umap[ublk1].bnd[nbnd1],exts[face1]);
   if (ndims == 2) {
      umap[ublk1].bnd[nbnd1].kmin = 0;
      umap[ublk1].bnd[nbnd1].kmax = 0;
   }
   CPYEXT(ext,umap[ublk2]);
   if (ndims == 2) {
      n = extents_redext(exts, ext, EDGE);
   } else {
      n = extents_redext(exts, ext, FACE);
   } 
   CPYEXT(umap[ublk2].bnd[nbnd2],exts[face2]);
   if (ndims == 2) {
      umap[ublk2].bnd[nbnd2].kmin = 0;
      umap[ublk2].bnd[nbnd2].kmax = 0;
   }
   umap[ublk1].nbnd++;
   umap[ublk2].nbnd++;
}
static void Blocks_ballshell2d( int mode, int type, int rads, int angs, int *dblk ,
                         int imax_in, int jmax_in) {
   char *me = "Blocks_ballshell2d";
   int i,n;
   int imax, jmax;
   int ublk = unblk;
   int num[6];
   n = 0;
   for (i = 0; i < 4; i++) num[i] = -1;
   for (i = 0; i < 4; i++) {
      if (dblk[i] != 1) num[i] = ublk + n++;
   }
   current_blk = 0;
   if (type == BLOCKS_HALF) {
      if (angs != -1) {
         imax = (angs - 1) / 2  + NPNL;
         jmax = (angs - 1) / 2  + NPNL;
      } else {
         imax = imax_in;
         jmax = jmax_in;
      } 
      if ((dblk[current_blk++] != 1) && (mode == BLOCKS_BALL)) { 
         Blocks_addblock(imax, jmax, 0);
      }
      jmax = rads - 1 + NPNL;
      if (dblk[current_blk++] != 1) Blocks_addblock(imax, jmax, 0);
      if (angs == -1) imax = imax_in;
      if (dblk[current_blk++] != 1) Blocks_addblock(imax, jmax, 0);
      if (mode == BLOCKS_BALL) {
         Blocks_setbnd(num[0], 3, num[1], 2,  1,  2, 3);
         Blocks_setbnd(num[0], 1, num[2], 2, -2,  1, 3);
         Blocks_setbnd(num[1], 1, num[2], 0,  1,  2, 3);
      } else {
         Blocks_setbnd(num[0], 1, num[1], 0,  1,  2, 3);
      } 
   } else if (type == BLOCKS_FULL) {
      if (angs != -1) {
         imax = (angs - 1) / 2  + NPNL;
         jmax = (angs - 1) / 4  + NPNL;
      } else {
         imax = imax_in;
         jmax = jmax_in;
      } 
      if ((dblk[current_blk++] != 1) && (mode == BLOCKS_BALL)) { 
         Blocks_addblock(imax, jmax, 0);
      }
      jmax = rads - 1 + NPNL;
      imax = (angs - 1) / 4  + NPNL;
      if (angs == -1) imax = jmax_in;
      if (dblk[current_blk++] != 1) Blocks_addblock(imax, jmax, 0);
      imax = (angs - 1) / 2  + NPNL;
      if (angs == -1) imax = imax_in;
      if (dblk[current_blk++] != 1) Blocks_addblock(imax, jmax, 0);
      imax = (angs - 1) / 4  + NPNL;
      if (angs == -1) imax = jmax_in;
      if (dblk[current_blk++] != 1) Blocks_addblock(imax, jmax, 0);
      if (mode == BLOCKS_BALL) {
         Blocks_setbnd(num[0], 1, num[3], 2, -2,  1, 3);
         Blocks_setbnd(num[0], 3, num[2], 2,  1,  2, 3);
         Blocks_setbnd(num[0], 0, num[1], 2,  2, -1, 3);
         Blocks_setbnd(num[1], 1, num[2], 0,  1,  2, 3);
         Blocks_setbnd(num[2], 1, num[3], 0,  1,  2, 3);
      } else {
         Blocks_setbnd(num[0], 1, num[1], 0,  1,  2, 3);
         Blocks_setbnd(num[1], 1, num[2], 0,  1,  2, 3);
      } 
   } 
}
static void Blocks_ballshell3d( int mode, int type, int rads, int angs, int *dblk,
                         int imax_in, int jmax_in, int kmax_in) {
   char *me = "Blocks_ballshell3d";
   int imax, jmax, kmax;    
   int num[7];
   int i,n;
   int ublk = unblk;
   n = 0;
   for (i = 0; i < 7; i++) num[i] = -1;
   for (i = 0; i < 7; i++) {
      if (dblk[i] != 1) num[i] = ublk + n++;
   }
   current_blk = 0;
   if (type == BLOCKS_OCTANT) {
      if (angs != -1) {
         imax = (angs - 1) / 2  + NPNL;
         jmax = (angs - 1) / 2  + NPNL;
         kmax = (angs - 1) / 2  + NPNL;
      } else {
         imax = imax_in;
         jmax = jmax_in;
         kmax = kmax_in;
      } 
      if ((dblk[current_blk++] != 1) && (mode == BLOCKS_BALL)) { 
         Blocks_addblock(imax, jmax, kmax);
      }
      jmax = rads - 1 + NPNL;
      if (angs == -1) imax = imax_in;
      if (angs == -1) kmax = kmax_in;
      if (dblk[current_blk++] != 1) Blocks_addblock(imax, jmax, kmax);
      if (angs == -1) imax = jmax_in;
      if (angs == -1) kmax = kmax_in;
      if (dblk[current_blk++] != 1) Blocks_addblock(imax, jmax, kmax);
      if (angs == -1) imax = imax_in;
      if (angs == -1) kmax = jmax_in;
      if (dblk[current_blk++] != 1) Blocks_addblock(imax, jmax, kmax);
      if (mode == BLOCKS_BALL) {
         Blocks_setbnd(num[0], 3, num[1], 2,  1,  2,  3);
         Blocks_setbnd(num[0], 1, num[2], 2, -2,  1,  3);
         Blocks_setbnd(num[0], 5, num[3], 2,  1,  3, -2);
         Blocks_setbnd(num[1], 1, num[2], 0,  1,  2, 3);
         Blocks_setbnd(num[1], 5, num[3], 4,  1,  2, 3);
         Blocks_setbnd(num[2], 5, num[3], 1,  -3,  2, 1);
      } else {
         Blocks_setbnd(num[0], 1, num[1], 0,  1,  2, 3);
         Blocks_setbnd(num[0], 5, num[2], 4,  1,  2, 3);
         Blocks_setbnd(num[1], 5, num[2], 1,  -3,  2, 1);
      } 
   } else if (type == BLOCKS_QUADRANT) {
      if (angs != -1) {
         imax = (angs - 1) / 4  + NPNL;
         jmax = (angs - 1) / 4  + NPNL;
         kmax = (angs - 1) / 2  + NPNL;
      } else {
         imax = imax_in;
         jmax = jmax_in;
         kmax = kmax_in;
      } 
      if ((dblk[current_blk++] != 1) && (mode == BLOCKS_BALL)) { 
         Blocks_addblock(imax, jmax, kmax);
      }
      jmax = rads - 1 + NPNL;
      if (angs == -1) imax = imax_in;
      if (angs == -1) kmax = kmax_in;
      if (dblk[current_blk++] != 1) Blocks_addblock(imax, jmax, kmax);
      if (angs == -1) imax = jmax_in;
      if (angs == -1) kmax = kmax_in;
      if (dblk[current_blk++] != 1) Blocks_addblock(imax, jmax, kmax);
      kmax = (angs - 1) / 4  + NPNL ;
      if (angs == -1) imax = imax_in;
      if (angs == -1) kmax = jmax_in;
      if (dblk[current_blk++] != 1) Blocks_addblock(imax, jmax, kmax);
      if (angs == -1) imax = imax_in;
      if (angs == -1) kmax = jmax_in;
      if (dblk[current_blk++] != 1) Blocks_addblock(imax, jmax, kmax);
      if (mode == BLOCKS_BALL) {
         Blocks_setbnd(num[0], 3, num[1], 2,  1,  2,  3);
         Blocks_setbnd(num[0], 1, num[2], 2, -2,  1,  3);
         Blocks_setbnd(num[0], 5, num[3], 2,  1,  3, -2);
         Blocks_setbnd(num[0], 4, num[4], 2,  1, -3,  2);
         Blocks_setbnd(num[1], 1, num[2], 0,  1,  2, 3);
         Blocks_setbnd(num[1], 5, num[3], 4,  1,  2, 3);
         Blocks_setbnd(num[1], 4, num[4], 5,  1,  2, 3);
         Blocks_setbnd(num[2], 5, num[3], 1,  -3,  2,   1);
         Blocks_setbnd(num[2], 4, num[4], 1,   3,  2,  -1);
      } else {
         Blocks_setbnd(num[0], 1, num[1], 0,  1,  2, 3);
         Blocks_setbnd(num[0], 5, num[2], 4,  1,  2, 3);
         Blocks_setbnd(num[0], 4, num[2], 5,  1,  2, 3);
         Blocks_setbnd(num[1], 5, num[2], 1,  -3,  2,   1);
         Blocks_setbnd(num[1], 4, num[3], 1,   3,  2,  -1);
      } 
   } else if (type == BLOCKS_HALF) {
      if (angs != -1) {
         imax = (angs - 1) / 4  + NPNL;
         jmax = (angs - 1) / 2  + NPNL;
         kmax = (angs - 1) / 2  + NPNL;
      } else {
         imax = imax_in;
         jmax = jmax_in;
         kmax = kmax_in;
      } 
      if ((dblk[current_blk++] != 1) && (mode == BLOCKS_BALL)) { 
         Blocks_addblock(imax, jmax, kmax);
      }
      jmax = rads - 1 + NPNL;
      imax = (angs - 1) / 4  + NPNL;
      kmax = (angs - 1) / 2  + NPNL;
      if (angs == -1) imax = imax_in;
      if (angs == -1) kmax = kmax_in;
      if (dblk[current_blk++] != 1) Blocks_addblock(imax, jmax, kmax);
      imax = (angs - 1) / 2  + NPNL;
      kmax = (angs - 1) / 2  + NPNL;
      if (angs == -1) imax = jmax_in;
      if (angs == -1) kmax = kmax_in;
      if (dblk[current_blk++] != 1) Blocks_addblock(imax, jmax, kmax);
      imax = (angs - 1) / 4  + NPNL;
      kmax = (angs - 1) / 2  + NPNL;
      if (angs == -1) imax = imax_in;
      if (angs == -1) kmax = jmax_in;
      if (dblk[current_blk++] != 1) Blocks_addblock(imax, jmax, kmax);
      if (angs == -1) imax = imax_in;
      if (angs == -1) kmax = jmax_in;
      if (dblk[current_blk++] != 1) Blocks_addblock(imax, jmax, kmax);
      imax = (angs - 1) / 4  + NPNL;
      kmax = (angs - 1) / 2  + NPNL;
      if (angs == -1) imax = imax_in;
      if (angs == -1) kmax = kmax_in;
      if (dblk[current_blk++] != 1) Blocks_addblock(imax, jmax, kmax);
      if (mode == BLOCKS_BALL) {
         Blocks_setbnd(num[0], 3, num[1], 2,  1,  2,  3);
         Blocks_setbnd(num[0], 1, num[2], 2, -2,  1,  3);
         Blocks_setbnd(num[0], 5, num[3], 2,  1,  3, -2);
         Blocks_setbnd(num[0], 4, num[4], 2,  1, -3,  2);
         Blocks_setbnd(num[0], 2, num[5], 2,  1, -2, -3);
         Blocks_setbnd(num[1], 1, num[2], 0,  1,  2, 3);
         Blocks_setbnd(num[1], 5, num[3], 4,  1,  2, 3);
         Blocks_setbnd(num[1], 4, num[4], 5,  1,  2, 3);
         Blocks_setbnd(num[2], 5, num[3], 1,  -3,  2,   1);
         Blocks_setbnd(num[2], 4, num[4], 1,   3,  2,  -1);
         Blocks_setbnd(num[2], 1, num[5], 1,  -1,  2,  -3);
         Blocks_setbnd(num[3], 5, num[5], 4,   1,  2,   3);
         Blocks_setbnd(num[4], 4, num[5], 5,   1,  2,   3);
      } else {
         Blocks_setbnd(num[0], 1, num[1], 0,  1,  2, 3);
         Blocks_setbnd(num[0], 5, num[2], 4,  1,  2, 3);
         Blocks_setbnd(num[0], 4, num[3], 5,  1,  2, 3);
         Blocks_setbnd(num[1], 5, num[2], 1,  -3,  2,   1);
         Blocks_setbnd(num[1], 4, num[3], 1,   3,  2,  -1);
         Blocks_setbnd(num[1], 1, num[4], 1,  -1,  2,  -3);
         Blocks_setbnd(num[2], 5, num[4], 4,   1,  2,   3);
         Blocks_setbnd(num[3], 4, num[4], 5,   1,  2,   3);
      } 
   } else if (type == BLOCKS_FULL) {
      if (angs != -1) {
         imax = (angs - 1) / 2  + NPNL;
         jmax = (angs - 1) / 2  + NPNL;
         kmax = (angs - 1) / 2  + NPNL;
      } else {
         imax = imax_in;
         jmax = jmax_in;
         kmax = kmax_in;
      } 
      if ((dblk[current_blk++] != 1) && (mode == BLOCKS_BALL)) { 
         Blocks_addblock(imax, jmax, kmax);
      }
      jmax = rads - 1 + NPNL;
      if (angs == -1) imax = imax_in;
      if (angs == -1) kmax = kmax_in;
      if (dblk[current_blk++] != 1) Blocks_addblock(imax, jmax, kmax);
      if (angs == -1) imax = jmax_in;
      if (angs == -1) kmax = kmax_in;
      if (dblk[current_blk++] != 1) Blocks_addblock(imax, jmax, kmax);
      if (angs == -1) imax = imax_in;
      if (angs == -1) kmax = jmax_in;
      if (dblk[current_blk++] != 1) Blocks_addblock(imax, jmax, kmax);
      if (angs == -1) imax = imax_in;
      if (angs == -1) kmax = jmax_in;
      if (dblk[current_blk++] != 1) Blocks_addblock(imax, jmax, kmax);
      if (angs == -1) imax = imax_in;
      if (angs == -1) kmax = kmax_in;
      if (dblk[current_blk++] != 1) Blocks_addblock(imax, jmax, kmax);
      if (angs == -1) imax = jmax_in;
      if (angs == -1) kmax = kmax_in;
      if (dblk[current_blk++] != 1) Blocks_addblock(imax, jmax, kmax);
      if (mode == BLOCKS_BALL) {
         Blocks_setbnd(num[0], 3, num[1], 2,  1,  2,  3);
         Blocks_setbnd(num[0], 1, num[2], 2, -2,  1,  3);
         Blocks_setbnd(num[0], 5, num[3], 2,  1,  3, -2);
         Blocks_setbnd(num[0], 4, num[4], 2,  1, -3,  2);
         Blocks_setbnd(num[0], 2, num[5], 2,  1, -2, -3);
         Blocks_setbnd(num[0], 0, num[6], 2,  2, -1,  3); 
         Blocks_setbnd(num[1], 1, num[2], 0,  1,  2, 3);
         Blocks_setbnd(num[1], 5, num[3], 4,  1,  2, 3);
         Blocks_setbnd(num[1], 4, num[4], 5,  1,  2, 3);
         Blocks_setbnd(num[1], 0, num[6], 1,  1,  2, 3); 
         Blocks_setbnd(num[2], 5, num[3], 1,  -3,  2,   1);
         Blocks_setbnd(num[2], 4, num[4], 1,   3,  2,  -1);
         Blocks_setbnd(num[2], 1, num[5], 1,  -1,  2,  -3);
         Blocks_setbnd(num[3], 5, num[5], 4,   1,  2,   3);
         Blocks_setbnd(num[3], 0, num[6], 5,  -3,  2,   1); 
         Blocks_setbnd(num[4], 4, num[5], 5,   1,  2,   3);
         Blocks_setbnd(num[4], 0, num[6], 4,   3,  2,  -1); 
         Blocks_setbnd(num[5], 0, num[6], 0,   -1,  2,  -3); 
      } else {
         Blocks_setbnd(num[0], 1, num[1], 0,  1,  2, 3);
         Blocks_setbnd(num[0], 5, num[2], 4,  1,  2, 3);
         Blocks_setbnd(num[0], 4, num[3], 5,  1,  2, 3);
         Blocks_setbnd(num[0], 0, num[5], 1,  1,  2, 3); 
         Blocks_setbnd(num[1], 5, num[2], 1,  -3,  2,   1);
         Blocks_setbnd(num[1], 4, num[3], 1,   3,  2,  -1);
         Blocks_setbnd(num[1], 1, num[4], 1,  -1,  2,  -3);
         Blocks_setbnd(num[2], 5, num[4], 4,   1,  2,   3);
         Blocks_setbnd(num[2], 0, num[5], 5,  -3,  2,   1); 
         Blocks_setbnd(num[3], 4, num[4], 5,   1,  2,   3);
         Blocks_setbnd(num[3], 0, num[5], 4,   3,  2,  -1); 
         Blocks_setbnd(num[4], 0, num[5], 0,   -1,  2,  -3); 
      } 
   } 
}
static void Blocks_cylinder3d( int mode, int type, int rads, int angs, int len, 
                        int *dblk , int imax_in, int jmax_in) {
   char *me = "Blocks_cylinder3d";
   int imax, jmax, kmax;    
   int num[5];
   int i,n;
   int ublk = unblk;
   n = 0;
   for (i = 0; i < 5; i++) num[i] = -1;
   for (i = 0; i < 5; i++) {
      if (dblk[i] != 1) num[i] = ublk + n++;
   }
   current_blk = 0;
   if (type == BLOCKS_QUADRANT) {
      if (angs != -1) {
         imax = (angs - 1) / 2  + NPNL;
         jmax = (angs - 1) / 2  + NPNL;
      } else {
         imax = imax_in;
         jmax = jmax_in;
      } 
      kmax = (len - 1)       + NPNL;
      if (dblk[current_blk++] != 1) Blocks_addblock(imax, jmax, kmax);
      jmax = rads - 1 + NPNL;
      if (angs == -1) imax = imax_in;
      if (dblk[current_blk++] != 1) Blocks_addblock(imax, jmax, kmax);
      if (angs == -1) imax = jmax_in;
      if (dblk[current_blk++] != 1) Blocks_addblock(imax, jmax, kmax);
      Blocks_setbnd(num[0], 3, num[1], 2,  1,  2,  3);
      Blocks_setbnd(num[0], 1, num[2], 2, -2,  1,  3);
      Blocks_setbnd(num[1], 1, num[2], 0,  1,  2, 3);
   } else if (type == BLOCKS_HALF) {
      if (angs != -1) {
         imax = (angs - 1) / 4  + NPNL;
         jmax = (angs - 1) / 2  + NPNL;
      } else {
         imax = imax_in;
         jmax = jmax_in;
      } 
      kmax = (len - 1)       + NPNL;
      if (dblk[current_blk++] != 1) Blocks_addblock(imax, jmax, kmax);
      jmax = rads - 1 + NPNL;
      imax = (angs - 1) / 4  + NPNL;
      if (angs == -1) imax = imax_in;
      if (dblk[current_blk++] != 1) Blocks_addblock(imax, jmax, kmax);
      imax = (angs - 1) / 2  + NPNL;
      if (angs == -1) imax = jmax_in;
      if (dblk[current_blk++] != 1) Blocks_addblock(imax, jmax, kmax);
      imax = (angs - 1) / 4  + NPNL;
      if (angs == -1) imax = imax_in;
      if (dblk[current_blk++] != 1) Blocks_addblock(imax, jmax, kmax);
      Blocks_setbnd(num[0], 3, num[1], 2,  1,  2,  3);
      Blocks_setbnd(num[0], 1, num[2], 2, -2,  1,  3);
      Blocks_setbnd(num[0], 2, num[3], 2, -1, -2,  3);
      Blocks_setbnd(num[1], 1, num[2], 0,  1,  2, 3);
      Blocks_setbnd(num[2], 1, num[3], 0,  1,  2, 3);
   } else if (type == BLOCKS_FULL) {
      if (angs != -1) {
         imax = (angs - 1) / 2  + NPNL;
         jmax = (angs - 1) / 2  + NPNL;
      } else {
         imax = imax_in;
         jmax = jmax_in;
      } 
      kmax = (len - 1)       + NPNL;
      if (dblk[current_blk++] != 1) Blocks_addblock(imax, jmax, kmax);
      jmax = rads - 1 + NPNL;
      if (angs == -1) imax = imax_in;
      if (dblk[current_blk++] != 1) Blocks_addblock(imax, jmax, kmax);
      if (angs == -1) imax = jmax_in;
      if (dblk[current_blk++] != 1) Blocks_addblock(imax, jmax, kmax);
      if (angs == -1) imax = imax_in;
      if (dblk[current_blk++] != 1) Blocks_addblock(imax, jmax, kmax);
      if (angs == -1) imax = jmax_in;
      if (dblk[current_blk++] != 1) Blocks_addblock(imax, jmax, kmax);
      Blocks_setbnd(num[0], 3, num[1], 2,  1,  2,  3);
      Blocks_setbnd(num[0], 1, num[2], 2, -2,  1,  3);
      Blocks_setbnd(num[0], 2, num[3], 2, -1, -2,  3);
      Blocks_setbnd(num[0], 0, num[4], 2,  2, -1,  3); 
      Blocks_setbnd(num[1], 1, num[2], 0,  1,  2, 3);
      Blocks_setbnd(num[1], 0, num[4], 1,  1,  2, 3); 
      Blocks_setbnd(num[2], 1, num[3], 0,  1,  2, 3);
      Blocks_setbnd(num[3], 1, num[4], 0,  1,  2, 3); 
   } 
}
static void Blocks_matchballshell3d( int type, int ublk_start, int *dblk, int repeat) {
   int num[8][7];
   int i,j,n;
   int ublk = ublk_start;
   n = 0;
   for (j = 0; j < 8; j++) {
      for (i = 0; i < 7; i++) {
         num[j][i] = -1;
         if (dblk[i] != 1) num[j][i] = ublk + n++;
      }
   }
   if (type == BLOCKS_OCTANT) {
      if (repeat == 2) {
         Blocks_setbnd(num[0][0], 2, num[1][0], 0,  -2,  1,  3);
         Blocks_setbnd(num[0][3], 5, num[1][3], 0,   3,  2, -1);
         Blocks_setbnd(num[0][2], 1, num[1][1], 0,   1,  2,  3);
      } else if (repeat == 4) {
         Blocks_setbnd(num[0][0], 2, num[1][0], 0,  -2,  1,  3);
         Blocks_setbnd(num[0][3], 5, num[1][3], 0,   3,  2, -1);
         Blocks_setbnd(num[0][2], 1, num[1][1], 0,   1,  2,  3);
         Blocks_setbnd(num[1][0], 2, num[2][0], 0,  -2,  1,  3);
         Blocks_setbnd(num[1][3], 5, num[2][3], 0,   3,  2, -1);
         Blocks_setbnd(num[1][2], 1, num[2][1], 0,   1,  2,  3);
         Blocks_setbnd(num[2][0], 2, num[3][0], 0,  -2,  1,  3);
         Blocks_setbnd(num[2][3], 5, num[3][3], 0,   3,  2, -1);
         Blocks_setbnd(num[2][2], 1, num[3][1], 0,   1,  2,  3);
         Blocks_setbnd(num[3][0], 2, num[0][0], 0,  -2,  1,  3);
         Blocks_setbnd(num[3][3], 5, num[0][3], 0,   3,  2, -1);
         Blocks_setbnd(num[3][2], 1, num[0][1], 0,   1,  2,  3);
      } else if (repeat == 8) {
         Blocks_setbnd(num[0][0], 2, num[1][0], 0,  -2,  1,  3);
         Blocks_setbnd(num[0][3], 5, num[1][3], 0,   3,  2, -1);
         Blocks_setbnd(num[0][2], 1, num[1][1], 0,   1,  2,  3);
         Blocks_setbnd(num[1][0], 2, num[2][0], 0,  -2,  1,  3);
         Blocks_setbnd(num[1][3], 5, num[2][3], 0,   3,  2, -1);
         Blocks_setbnd(num[1][2], 1, num[2][1], 0,   1,  2,  3);
         Blocks_setbnd(num[2][0], 2, num[3][0], 0,  -2,  1,  3);
         Blocks_setbnd(num[2][3], 5, num[3][3], 0,   3,  2, -1);
         Blocks_setbnd(num[2][2], 1, num[3][1], 0,   1,  2,  3);
         Blocks_setbnd(num[3][0], 2, num[0][0], 0,  -2,  1,  3);
         Blocks_setbnd(num[3][3], 5, num[0][3], 0,   3,  2, -1);
         Blocks_setbnd(num[3][2], 1, num[0][1], 0,   1,  2,  3);
         Blocks_setbnd(num[4][0], 2, num[5][0], 0,  -2,  1,  3);
         Blocks_setbnd(num[4][3], 5, num[5][3], 0,   3,  2, -1);
         Blocks_setbnd(num[4][2], 1, num[5][1], 0,   1,  2,  3);
         Blocks_setbnd(num[5][0], 2, num[6][0], 0,  -2,  1,  3);
         Blocks_setbnd(num[5][3], 5, num[6][3], 0,   3,  2, -1);
         Blocks_setbnd(num[5][2], 1, num[6][1], 0,   1,  2,  3);
         Blocks_setbnd(num[6][0], 2, num[7][0], 0,  -2,  1,  3);
         Blocks_setbnd(num[6][3], 5, num[7][3], 0,   3,  2, -1);
         Blocks_setbnd(num[6][2], 1, num[7][1], 0,   1,  2,  3);
         Blocks_setbnd(num[7][0], 2, num[4][0], 0,  -2,  1,  3);
         Blocks_setbnd(num[7][3], 5, num[4][3], 0,   3,  2, -1);
         Blocks_setbnd(num[7][2], 1, num[4][1], 0,   1,  2,  3);
         Blocks_setbnd(num[0][0], 4, num[5][0], 4,   2,  1, -3);
         Blocks_setbnd(num[0][1], 4, num[5][2], 4,  -1,  2, -3);
         Blocks_setbnd(num[0][2], 4, num[5][1], 4,  -1,  2, -3);
         Blocks_setbnd(num[1][0], 4, num[4][0], 4,   2,  1, -3);
         Blocks_setbnd(num[1][1], 4, num[4][2], 4,  -1,  2, -3);
         Blocks_setbnd(num[1][2], 4, num[4][1], 4,  -1,  2, -3);
         Blocks_setbnd(num[2][0], 4, num[7][0], 4,   2,  1, -3);
         Blocks_setbnd(num[2][1], 4, num[7][2], 4,  -1,  2, -3);
         Blocks_setbnd(num[2][2], 4, num[7][1], 4,  -1,  2, -3);
         Blocks_setbnd(num[3][0], 4, num[6][0], 4,   2,  1, -3);
         Blocks_setbnd(num[3][1], 4, num[6][2], 4,  -1,  2, -3);
         Blocks_setbnd(num[3][2], 4, num[6][1], 4,  -1,  2, -3);
      } 
   } else if (type == BLOCKS_QUADRANT) {
      if (repeat == 2) {
         Blocks_setbnd(num[0][0], 2, num[1][0], 0,  -2,  1,  3);
         Blocks_setbnd(num[0][3], 5, num[1][3], 0,   3,  2, -1);
         Blocks_setbnd(num[0][4], 4, num[1][4], 0,  -3,  2,  1);
         Blocks_setbnd(num[0][2], 1, num[1][1], 0,   1,  2,  3);
      } else if (repeat == 4) {
         Blocks_setbnd(num[0][0], 2, num[1][0], 0,  -2,  1,  3);
         Blocks_setbnd(num[0][3], 5, num[1][3], 0,   3,  2, -1);
         Blocks_setbnd(num[0][4], 4, num[1][4], 0,  -3,  2,  1);
         Blocks_setbnd(num[0][2], 1, num[1][1], 0,   1,  2,  3);
         Blocks_setbnd(num[1][0], 2, num[2][0], 0,  -2,  1,  3);
         Blocks_setbnd(num[1][3], 5, num[2][3], 0,   3,  2, -1);
         Blocks_setbnd(num[1][4], 4, num[2][4], 0,  -3,  2,  1);
         Blocks_setbnd(num[1][2], 1, num[2][1], 0,   1,  2,  3);
         Blocks_setbnd(num[2][0], 2, num[3][0], 0,  -2,  1,  3);
         Blocks_setbnd(num[2][3], 5, num[3][3], 0,   3,  2, -1);
         Blocks_setbnd(num[2][4], 4, num[3][4], 0,  -3,  2,  1);
         Blocks_setbnd(num[2][2], 1, num[3][1], 0,   1,  2,  3);
         Blocks_setbnd(num[3][0], 2, num[0][0], 0,  -2,  1,  3);
         Blocks_setbnd(num[3][3], 5, num[0][3], 0,   3,  2, -1);
         Blocks_setbnd(num[3][4], 4, num[0][4], 0,  -3,  2,  1);
         Blocks_setbnd(num[3][2], 1, num[0][1], 0,   1,  2,  3);
      } 
   } else if (type == BLOCKS_HALF) {
      if (repeat == 2) {
         Blocks_setbnd(num[0][0], 0, num[1][0], 0,  -1, -2,  3);
         Blocks_setbnd(num[0][3], 0, num[1][3], 0,  -1,  2, -3);
         Blocks_setbnd(num[0][4], 0, num[1][4], 0,  -1,  2, -3);
         Blocks_setbnd(num[0][5], 0, num[1][1], 0,  -1,  2, -3);
         Blocks_setbnd(num[0][1], 0, num[1][5], 0,  -1,  2, -3);
      }
   } 
}
static void Blocks_matchcyl3d( int type, int ublk_start, int *dblk, int repeat) {
   int num[8][7];
   int i,j,n;
   int ublk = ublk_start;
   n = 0;
   for (j = 0; j < 4; j++) {
      for (i = 0; i < 4; i++) {
         num[j][i] = -1;
         if (dblk[i] != 1) num[j][i] = ublk + n++;
      }
   }
   if (type == BLOCKS_QUADRANT) {
      if (repeat == 2) {
         Blocks_setbnd(num[0][0], 2, num[1][0], 0,  -2,  1,  3);
         Blocks_setbnd(num[0][2], 1, num[1][1], 0,   1,  2,  3);
      } else if (repeat == 4) {
         Blocks_setbnd(num[0][0], 2, num[1][0], 0,  -2,  1,  3);
         Blocks_setbnd(num[0][2], 1, num[1][1], 0,   1,  2,  3);
         Blocks_setbnd(num[1][0], 2, num[2][0], 0,  -2,  1,  3);
         Blocks_setbnd(num[1][2], 1, num[2][1], 0,   1,  2,  3);
         Blocks_setbnd(num[2][0], 2, num[3][0], 0,  -2,  1,  3);
         Blocks_setbnd(num[2][2], 1, num[3][1], 0,   1,  2,  3);
         Blocks_setbnd(num[3][0], 2, num[0][0], 0,  -2,  1,  3);
         Blocks_setbnd(num[3][2], 1, num[0][1], 0,   1,  2,  3);
      } 
   } else if (type == BLOCKS_HALF) {
      if (repeat == 2) {
         Blocks_setbnd(num[0][0], 0, num[1][0], 0,  -1,  -2,  3);
         Blocks_setbnd(num[0][1], 0, num[1][3], 1,   1,   2,  3);
         Blocks_setbnd(num[0][3], 1, num[1][1], 0,   1,   2,  3);
      }
   } 
}
