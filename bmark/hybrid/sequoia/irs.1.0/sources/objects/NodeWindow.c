#include "irs.h"
#include "irsgen.h"
#include "irsctl.h"
#include "irsrgst.h"
#include "BlockMapping.h"
#include "Extents.h"
#include "Tracer.h"
#include "NodeList.h"
#include "Hash.h"
#include "ProblemArray.h"
#include "UserList.h"
static void NodeWindow_zonalize(NodeWindow_t *in_ndx);	
int NodeWindow_read(char *name, NodeWindow_t **in_ndx) {
   char *me = "NodeWindow_read";
   char msg[512], msg2[512];
   char op[MAXLINE];
   char tracername[MAXLINE];
   char ps_copy[MAXLINE];
   char *tmplist   = NULL;
   char *indexlist = NULL;
   char *ps_save = NULL;
   int i,j,k,n;
   int irank,rank;
   int lrank;
   int gblk;
   int ublk;
   int ublk_set;
   int iblk;
   int gotnamed;
   int lguess1, lguess2;
   int cflag;
   int count;
   int error = 0;
   int badtracer = 0;
   int my_ndx_plusmin[3];
   int ind   [NRANKX];
   int min_in[NRANKX];
   int max_in[NRANKX];
   int def_in[NRANKX][3];
   int my_in [NRANKX][3];
   NodeWindow_t *my_ndx;
   NodeWindow_t *my_ndx_ptr;
   NodeWindow_t *my_ndx_rank[3];
   NodeWindow_t *named_ndx;
   NodeList_t *my_ndxlst;
   Tracer_t *tracer;
   HashElm_t *hashel;
   ProblemArray_t *prb;
   Extents_t  ext, exts[6];
   UserList_t *list;
   memset (ps_copy, '\0', MAXLINE);
   strncpy(ps_copy, name, MAXLINE - 1);
   if (ps != NULL) {
     strncat(ps_copy, ps,   MAXLINE - (strlen(ps_copy) + 1));
   }
   for (i=0; i<strlen(ps_copy); i++) {
     if (ps_copy[i] == '\n') { ps_copy[i] = '\0'; }  
   }
   memset (op, '\0', MAXLINE);
   geta(op);
   ublk = blknum;
   ublk_set = 0;
   if (!strcmp(":",op)) {
     peekc(op);
     if (!strcmp(op,"(")) {
        sprintf(msg2,"NL_%s",name);
        error = UserList_parse(msg2);
        if (error != 0) {
          sprintf(msg,"Error trying to parse block list object in index list");
          ctlwarning(me,msg);
          return(-1);
        }
	ps_save = ps;
	while (*ps != ')') {
           if (ps == NULL) {
              sprintf(msg,"Error trying to parse block list object in index list");
              ctlwarning(me,msg);
              return(-1);
           }
           ps++;
	}
	ps++;
	n = ps - ps_save + 2;
	tmplist   = MALLOT(char,n);
	indexlist = MALLOT(char,n + 6);
        memset(tmplist,'\0',n); 
        strncpy(tmplist,ps_save, n - 2);
	list = UserList_find(msg2);
	lineop_push();
	while (list != NULL) {
	  n = atoi(list->name);
	  sprintf(indexlist,":%i%s",n,tmplist);
          line = indexlist;
          ps   = line;
          error = NodeWindow_read(name, in_ndx);
          if (error != 0) {
             return(error);
          }
	  list = list->next;
	}
        lineop_pop();
	if (tmplist != NULL) FREEMEM(tmplist);
	if (indexlist != NULL) FREEMEM(indexlist);
	return(error);
     } else {
        ublk = geti(&cflag);
        ublk_set = 1;
        if (cflag != 0) {
          sprintf(msg,"Expected to find integer after ':' in following line"
                      "\n\t'%s'",ps_copy);
          ctlnotice(me,msg);
          return(-1);
        }
        geta(op);  
      }
   }
   if ((ublk < 0) || (ublk >= unblk)) {
      sprintf(msg,"\n\t%d is invalid block number in following line"
                  "\n\tThere are %d blocks numbered %d through %d"
                   "\n\t'%s'",
                  ublk,unblk,0,unblk-1,ps_copy);
      ctlnotice(me,msg);
      return(-1);
   }
   if (strcmp(op,"(") != 0) {
      sprintf(msg,"Expected '(' after %s instead of '%s'",name,op);
      ctlnotice(me,msg);
      return(-1) ;
   }
   def_in[0][0] = 0;
   def_in[0][1] = umap[ublk].imax + 1;
   def_in[0][2] = 1;
   def_in[1][0] = 0;
   def_in[1][1] = umap[ublk].jmax + 1;
   def_in[1][2] = 1;
   if (ndims == 2) {
      def_in[2][0] = 0;
      def_in[2][1] = ngroup - 1;
      def_in[2][2] = 1;
   } else {
      def_in[2][0] = 0;
      def_in[2][1] = umap[ublk].kmax + 1;
      def_in[2][2] = 1;
   } 
   def_in[3][0] = 0;
   def_in[3][1] = ngroup - 1;
   def_in[3][2] = 1;
   my_ndx_rank[0] = NULL;
   my_ndx_rank[1] = NULL;
   my_ndx_rank[2] = NULL;
   my_ndx_plusmin[0] = 0;
   my_ndx_plusmin[1] = 0;
   my_ndx_plusmin[2] = 0;
   min_in[0] = umap[ublk].imin;
   min_in[1] = umap[ublk].jmin;
   min_in[2] = umap[ublk].kmin;
   max_in[0] = umap[ublk].imax;
   max_in[1] = umap[ublk].jmax;
   max_in[2] = umap[ublk].kmax;
   for (i = 0; i < NRANKX; i++) {
      ind[i] = 0;
      my_in[i][0] = def_in[i][0];
      my_in[i][1] = def_in[i][1];
      my_in[i][2] = def_in[i][2];
   }
   rank = 0;
   gotnamed = 0;
   lrank = -1;
   peekc(op);
   if (!strcmp("zones",op)) {
      geta(op);
      error = NodeWindow_read(name, in_ndx);
      geta(op);
      if (strcmp(")",op)) {
         sprintf(msg,"Error parsing index list for %s",name);       
         ctlwarning(me,msg);
         return(-1);
      }
      NodeWindow_zonalize(*in_ndx);	
      return(error);
   }
   count = 0;
   while (strcmp(")",op)) {
      sprintf(tracername,"Tracer_%s",op);
      if (!strcmp(",",op)) {
         geta(op);
         rank++;
         if (rank > (ndims + ngroup)) {
            error = -1;
            break;
         }
      } else if (!strcmp(":",op)) {
         geta(op);
         if (ind[rank] > 2) {
            error = -1;
            break;
         }
      } else if (!strcmp("%",op)) {
         geta(op);
         lrank = rank;
      } else if (!strcmp("(",op)) {
         error = NodeWindow_read(name, in_ndx);
      } else if (( hashel = hash_lookup_elm(tracername, gv_hash_tbl)) != NULL) {
	 geta(op);
         tracer = (Tracer_t *)hashel->obj;	
         gblk   = tracer->owner;
         badtracer = 0;
	 if (ndims == 2) {
	   if (gblk >= 0) {
	      ublk = gmap[gblk].ublk;
	      NDXEXT2D(tracer->zone,i,j,gmap[gblk]);
	      i = i + gmap[gblk].imin - 2 * NPNL + 1;
	      j = j + gmap[gblk].jmin - 2 * NPNL + 1;
              my_in[0][0] = i;
              my_in[1][0] = j;
              def_in[0][0] = umap[ublk].imin;
              def_in[1][0] = umap[ublk].jmin;
              def_in[0][1] = umap[ublk].imax;
              def_in[1][1] = umap[ublk].jmax;
              min_in[0] = umap[ublk].imin;
              min_in[1] = umap[ublk].jmin;
              min_in[2] = umap[ublk].kmin;
              max_in[0] = umap[ublk].imax;
              max_in[1] = umap[ublk].jmax;
              max_in[2] = umap[ublk].kmax;
	   } else {
              my_in[0][0] = -1;
              my_in[1][0] = -1;
              def_in[0][0] = -1;
              def_in[1][0] = -1;
              def_in[0][1] = -1;
              def_in[1][1] = -1;
              min_in[0] = -1;
              min_in[1] = -1;
              min_in[2] = -1;
              max_in[0] = -1;
              max_in[1] = -1;
              max_in[2] = -1;
              badtracer = 1;
	   } 
           ind[0] = 1;
           ind[1] = 1;
  	   rank++;
	} else {
	   if (gblk >= 0) {
	      NDXEXT3D(tracer->zone,i,j,k,gmap[gblk]);
	      i = i + gmap[gblk].imin - 2*NPNL + 1;
	      j = j + gmap[gblk].jmin - 2*NPNL + 1;
	      k = k + gmap[gblk].kmin - 2*NPNL + 1;
              my_in[0][0] = i;
              my_in[1][0] = j;
              my_in[2][0] = k;
              def_in[0][0] = umap[ublk].imin;
              def_in[1][0] = umap[ublk].jmin;
              def_in[2][0] = umap[ublk].kmin;
              def_in[0][1] = umap[ublk].imax;
              def_in[1][1] = umap[ublk].jmax;
              def_in[2][1] = umap[ublk].kmax;
              min_in[0] = umap[ublk].imin;
              min_in[1] = umap[ublk].jmin;
              min_in[2] = umap[ublk].kmin;
              max_in[0] = umap[ublk].imax;
              max_in[1] = umap[ublk].jmax;
              max_in[2] = umap[ublk].kmax;
	   } else {
              my_in[0][0] = -1;
              my_in[1][0] = -1;
              my_in[2][0] = -1;
              def_in[0][0] = -1;
              def_in[1][0] = -1;
              def_in[2][0] = -1;
              def_in[0][1] = -1;
              def_in[1][1] = -1;
              def_in[2][1] = -1;
              min_in[0] = -1;
              min_in[1] = -1;
              min_in[2] = -1;
              max_in[0] = -1;
              max_in[1] = -1;
              max_in[2] = -1;
              badtracer = 1;
	   } 
           ind[0] = 1;
           ind[1] = 1;
           ind[2] = 1;
	   rank++;
	   rank++;
	}
      } else if ((my_ndxlst = NodeList_find(op)) != NULL) {
          geta(op);
          gotnamed = 1;
          named_ndx = my_ndxlst->list;
          if (named_ndx == NULL) {
             sprintf(msg, "Node list %s appears to be empty.",op);
             ctlnotice(me,msg);
             return(-1);
          }
          while (named_ndx != NULL) {
             if (ublk_set) {
                if (named_ndx->ublk == ublk) {
                   my_ndx = ALLOT(NodeWindow_t,1);
                   my_ndx->len     = 0;
                   my_ndx->logical = -1;
                   NodeWindow_copy(my_ndx,named_ndx);
                   NodeWindow_add(my_ndx,&my_ndx_rank[ind[rank]]);
                }
             } else {
                my_ndx = ALLOT(NodeWindow_t,1);
                my_ndx->len     = 0;
                my_ndx->logical = -1;
                NodeWindow_copy(my_ndx,named_ndx);
                NodeWindow_add(my_ndx,&my_ndx_rank[ind[rank]]);
             } 
             named_ndx = named_ndx->next;
          }
          my_ndx_plusmin[ind[rank]] = iplusmin;
          ind[rank]++;
      } else if (!strcmp(op,"i")) {
	 geta(op);
	 geta(op);
	 if (strcmp(op,"=")) {
            sprintf(msg, "Expected equal sign after i for node list.");
            ctlwarning(me,msg);
            return(-1);
	 }
	 i = geti(&cflag);
         my_in[0][0] = i + iplusmin;
         my_in[0][1] = i + iplusmin;
         if (ndims == 2) {
            my_in[1][0] = umap[ublk].jmin - NPNL + 1;
            my_in[1][1] = umap[ublk].jmax - NPNL + 1;
            ind[0] = 1;
            ind[1] = 2;
	    rank++;
         } else {
            my_in[1][0] = umap[ublk].jmin - NPNL + 1;
            my_in[1][1] = umap[ublk].jmax - NPNL + 1;
            my_in[2][0] = umap[ublk].kmin - NPNL + 1;
            my_in[2][1] = umap[ublk].kmax - NPNL + 1;
            ind[0] = 1;
            ind[1] = 2;
            ind[2] = 2;
	    rank++;
	    rank++;
         } 
      } else if (!strcmp(op,"j")) {
	 geta(op);
	 geta(op);
	 if (strcmp(op,"=")) {
            sprintf(msg, "Expected equal sign after j for node list.");
            ctlwarning(me,msg);
            return(-1);
	 }
	 j = geti(&cflag);
         my_in[1][0] = j + iplusmin;
         my_in[1][1] = j + iplusmin;
         if (ndims == 2) {
            my_in[0][0] = umap[ublk].imin - NPNL + 1;
            my_in[0][1] = umap[ublk].imax - NPNL + 1;
            ind[0] = 2;
            ind[1] = 1;
	    rank++;
         } else {
            my_in[0][0] = umap[ublk].imin - NPNL + 1;
            my_in[0][1] = umap[ublk].imax - NPNL + 1;
            my_in[2][0] = umap[ublk].kmin - NPNL + 1;
            my_in[2][1] = umap[ublk].kmax - NPNL + 1;
            ind[0] = 2;
            ind[1] = 1;
            ind[2] = 2;
	    rank++;
	    rank++;
         } 
      } else if (!strcmp(op,"k")) {
	 geta(op);
	 geta(op);
	 if (strcmp(op,"=")) {
            sprintf(msg, "Expected equal sign after k for node list.");
            ctlwarning(me,msg);
            return(-1);
	 }
	 k = geti(&cflag);
         my_in[2][0] = k + iplusmin;
         my_in[2][1] = k + iplusmin;
         my_in[0][0] = umap[ublk].imin - NPNL + 1;
         my_in[0][1] = umap[ublk].imax - NPNL + 1;
         my_in[1][0] = umap[ublk].jmin - NPNL + 1;
         my_in[1][1] = umap[ublk].jmax - NPNL + 1;
         ind[0] = 2;
         ind[1] = 2;
         ind[2] = 1;
         rank++;
         rank++;
      } else if (!strcmp(op,"face")) {
	 geta(op);
	 geta(op);
	 if (strcmp(op,"=")) {
            sprintf(msg, "Expected equal sign after face for node list.");
            ctlwarning(me,msg);
            return(-1);
	 }
	 i = geti(&cflag);
	 if ((ndims == 2) && ((i  >  3) || (i < 0))) {
            sprintf(msg, "In 2D face values must be between 0 and 3.");
            ctlwarning(me,msg);
            return(-1);
	 }
	 if ((ndims == 3) && ((i  >  5) || (i < 0))) {
            sprintf(msg, "In 3D face values must be between 0 and 5.");
            ctlwarning(me,msg);
            return(-1);
	 }
         CPYEXT(ext, umap[ublk]);
         if (ndims == 2) {
            n = extents_redext(exts, ext, EDGE);
         } else {
            n = extents_redext(exts, ext, FACE);
         } 
         my_in[0][0] = exts[i].imin - NPNL + 1;
         my_in[0][1] = exts[i].imax - NPNL + 1;
         my_in[1][0] = exts[i].jmin - NPNL + 1;
         my_in[1][1] = exts[i].jmax - NPNL + 1;
         if (ndims == 2) {
            ind[0] = 2;
            ind[1] = 2;
            if ((i == 0) || (i == 1)) ind[0] = 1;
            if ((i == 2) || (i == 3)) ind[1] = 1;
	    rank++;
         } else {
            my_in[2][0] = exts[i].kmin - NPNL + 1;
            my_in[2][1] = exts[i].kmax - NPNL + 1;
            ind[0] = 2;
            ind[1] = 2;
            ind[2] = 2;
            if ((i == 0) || (i == 1)) ind[0] = 1;
            if ((i == 2) || (i == 3)) ind[1] = 1;
            if ((i == 4) || (i == 5)) ind[2] = 1;
	    rank++;
	    rank++;
         } 
      } else {
         geta(op);
	 if ((('0' <= op[0]) && (op[0] <= '9')) || 
	      (op[0] == '-') || (op[0] == '+')) {
            my_in[rank][ind[rank]] = atoi(op) + iplusmin;
	 } else {
            sprintf(msg,"Unrecognized index - %s found while parsing %s",op,name);
            ctlwarning(me,msg);
            return(-1);
	 } 
         ind[rank]++;
      }
      if (ind[rank] >  3) {
         sprintf(msg,"Error trying to parse index list for %s. Perhaps there is a missing comma.",name);
         ctlwarning(me,msg);
         return(-1);
      }
      if (count > 100) {
         sprintf(msg,"Error trying to parse index list for %s. Perhaps there is a missing closed paren",name);
         ctlwarning(me,msg);
         return(-1);
      }
      count++;
      peekc(op);
   } 
   if (iplusmin == 1) {
      geta(op);
      error = NodeWindow_read(name, in_ndx);
   }
   if (strcmp(")",op) == 0) {
      geta(op);
      rank++;
   } else {
      sprintf(msg,"\n\tDid not find ')' at end of index list in following line"
                  "\n\t'%s'",ps_copy);
      ctlwarning(me,msg);
      return(-1);
   }
   if ((ind[0] == 0) && (rank == 1)) {
      if (ndims == 2) {
         my_in[0][0] = umap[ublk].imin - NPNL + 1;
         my_in[0][1] = umap[ublk].imax - NPNL + 1;
         my_in[1][0] = umap[ublk].jmin - NPNL + 1;
         my_in[1][1] = umap[ublk].jmax - NPNL + 1;
	 ind[0] = 2;
	 ind[1] = 2;
	 rank = 2;
      } else {
         my_in[0][0] = umap[ublk].imin - NPNL + 1;
         my_in[0][1] = umap[ublk].imax - NPNL + 1;
         my_in[1][0] = umap[ublk].jmin - NPNL + 1;
         my_in[1][1] = umap[ublk].jmax - NPNL + 1;
         my_in[2][0] = umap[ublk].kmin - NPNL + 1;
         my_in[2][1] = umap[ublk].kmax - NPNL + 1;
	 ind[0] = 2;
	 ind[1] = 2;
	 ind[2] = 2;
	 rank = 3;
      } 
   }
   if ((rank < ndims) && (rank > 1)) {
     sprintf(msg,"\n\tFollowing line only specified %d dimensions in a %d "
                 "dimensional problem. "
                 "\n\tUsing defaults for other dimensions"
                 "\n\t'%s'",rank,ndims,ps_copy);
     ctlnotice(me,msg);
   }
   if ((error == 0) && (gotnamed == 1)) {
      if (ind[0] > 1) {
         error = NodeWindow_range(my_ndx_rank[0],my_ndx_rank[1],my_ndx_plusmin[0],
                               my_ndx_plusmin[1]);
         NodeWindow_free(my_ndx_rank[1]);
         if (error != 0) { 
            NodeWindow_free(my_ndx_rank[0]);
            return(error);
         }
      }
      my_ndx = my_ndx_rank[0];
      while (my_ndx != NULL) {
         my_ndx_ptr = my_ndx->next;
         NodeWindow_add(my_ndx,in_ndx);
         my_ndx = my_ndx_ptr;
      }
   }
   if ((error == 0) && (gotnamed == 0)) {
      my_ndx = ALLOT(NodeWindow_t,1);
      my_ndx->len     = 0;
      my_ndx->logical = -1;
      my_ndx->rank = rank;
      my_ndx->ublk = ublk;
      for (irank = 0; irank < rank; irank++) {
         if (ind[irank] == 1) my_in[irank][1] = my_in[irank][0];
      }
      if ((ndims == 2) && (rank >= 2)) {
         my_in[0][0] += NPNL - 1;
         my_in[0][1] += NPNL - 1;
         my_in[1][0] += NPNL - 1;
         my_in[1][1] += NPNL - 1;
      } else if ((ndims == 3) && (rank >= 3)) {
         my_in[0][0] += NPNL - 1;
         my_in[0][1] += NPNL - 1;
         my_in[1][0] += NPNL - 1;
         my_in[1][1] += NPNL - 1;
         my_in[2][0] += NPNL - 1;
         my_in[2][1] += NPNL - 1;
      }
      if (lrank >= 0) {
         ninlen   = (my_in[lrank][1] - my_in[lrank][0]) / (my_in[lrank][2]) + 1;
         ninloops = 1 ;
         lguess1  = my_in[lrank][0] + nincount * my_in[lrank][2] ;
         lguess2  = lguess1 + my_in[lrank][2] ;
         if ( lguess2 > my_in[lrank][1] ) { ninloops = 0 ; }
         my_in[lrank][0] = lguess1 ;
         my_in[lrank][1] = my_in[lrank][0] ;
         my_in[lrank][2] = 1 ;
      }
      sprintf(msg2,"\n\tTaking ghost nodes into account,"
                   "\n\tBlock %d has dimensions %d x %d x %d."
                   "\n\tValid index ranges are"
                   "\n\t[%d:%d][%d:%d][%d:%d]",
                   ublk,
                   def_in[0][1] + 1,
                   def_in[1][1] + 1,
                   (ndims > 2) ? def_in[2][1] + 1 : 0,
                   def_in[0][0] - NPNL + 1,
                   def_in[0][1] - NPNL + 1,
                   def_in[1][0] - NPNL + 1,
                   def_in[1][1] - NPNL + 1,
                   (ndims > 2) ? def_in[2][0] - NPNL + 1 : 0,
                   (ndims > 2) ? def_in[2][1] - NPNL + 1 : 0 );
      if ((badtracer == 0) && (rank > 1)) {
         for (irank = 0; irank < rank; irank++) {
            if (my_in[irank][0] < def_in[irank][0]) {
               sprintf(msg,"\n\tIndex %d with a value of %d is too low"
                           "\n%s"
                           "\n\n\tLine being parsed is"
                           "\n\n\t%s",
                           irank+1,
                           my_in[irank][0] - NPNL + 1,
                           msg2,
                           ps_copy);
               ctlnotice(me,msg);
               return(-1);
            }
            else if (   (my_in[irank][0] < min_in[irank])
                     && (irank < ndims) ) {
               sprintf(msg,"\n\tIndex %d with a value of %d"
                           " refers to a ghost zone/node"
                           "\n\n\tLine being parsed is"
                           "\n\n\t%s",
                           irank+1,
                           my_in[irank][0] - NPNL + 1,
                           ps_copy);
               ctlnotice(me,msg);
            }
            if (my_in[irank][1] > def_in[irank][1]) {
               sprintf(msg,"\n\tIndex %d with a value of %d is too high"
                           "\n%s"
                           "\n\n\tLine being parsed is"
                           "\n\n\t%s",
                           irank+1,
                           my_in[irank][1] - NPNL + 1,
                           msg2,
                           ps_copy);
               ctlnotice(me,msg);
               return(-1);
            }
            else if (   (my_in[irank][1] > max_in[irank])
                     && (irank < ndims) ) {
               sprintf(msg,"\n\tIndex %d with a value of %d"
                           " refers to a ghost node"
                           "\n\n\tLine being parsed is"
                           "\n\n\t%s",
                           irank+1,
                           my_in[irank][0] - NPNL + 1,
                           ps_copy);
               ctlnotice(me,msg);
            }
         }
      }
      mkpalab(my_ndx->label,name,ublk,my_in,rank,0,"") ;
      for (irank = 0; irank < rank; irank++) {
         my_ndx->in[irank][0] = my_in[irank][0];
         my_ndx->in[irank][1] = my_in[irank][1];
         my_ndx->in[irank][2] = my_in[irank][2];
         my_ndx->imin = MIN(my_in[0][0],my_in[0][1]);
         my_ndx->imax = MAX(my_in[0][0],my_in[0][1]);
         my_ndx->jmin = MIN(my_in[1][0],my_in[1][1]);
         my_ndx->jmax = MAX(my_in[1][0],my_in[1][1]);
         if (ndims == 3) {
            my_ndx->kmin = MIN(my_in[2][0],my_in[2][1]);
            my_ndx->kmax = MAX(my_in[2][0],my_in[2][1]);
         } else {
            my_ndx->kmin = 0;
            my_ndx->kmax = 0;
         } 
      }
      NodeWindow_add(my_ndx,in_ndx);
   }
   return(error);
}
int NodeWindow_range(NodeWindow_t *ndxin1, NodeWindow_t *ndxin2, int plusmin1, 
                  int plusmin2)
{ 
   char *me = "NodeWindow_range";
   char msg[MAXLINE];
   int error;
   int ndeg;
   int iflag;
   int jflag;
   int kflag;
   int type1;
   int type2;
   Extents_t ext;
   NodeWindow_t *ndx_ptr1;
   NodeWindow_t *ndx_ptr2;
   error = 0;
   ndx_ptr1 = ndxin1;
   ndx_ptr2 = ndxin2;
   while ((ndx_ptr1 != NULL) && (ndx_ptr2 != NULL)) {
      if (ndx_ptr1->ublk != ndx_ptr2->ublk) {
         sprintf(msg,"Nodelists %s and %s are not one to one in block number.",ndx_ptr1->label,ndx_ptr2->label);
         ctlwarning(me,msg);
         return(1);
      }
      CPYEXT(ext,(*ndx_ptr1));
      type1 = extents_gettype(ext);
      CPYEXT(ext,(*ndx_ptr2));
      type2 = extents_gettype(ext);
      if (((ndims == 3) && (type1 == VOLUME)) || 
          ((ndims == 2) && (type1 == AREA)) || 
          ((ndims == 3) && (type2 == VOLUME)) || 
          ((ndims == 2) && (type2 == AREA)) || (type1 != type2)) {
         sprintf(msg,"Nodelists %s and %s cannot be differenced.",
                      ndx_ptr1->label,ndx_ptr2->label);
         ctlwarning(me,msg);
         return(1);
      }
      ndeg = 0;
      iflag = ndx_ptr1->imax - ndx_ptr2->imax;
      if (iflag != 0) ndeg++; 
      jflag = ndx_ptr1->jmax - ndx_ptr2->jmax;
      if (jflag != 0) ndeg++; 
      kflag = ndx_ptr1->kmax - ndx_ptr2->kmax;
      if (kflag != 0) ndeg++; 
      if (ndeg != 1) {
         sprintf(msg,"Nodelists %s and %s cannot be differenced.",
                      ndx_ptr1->label,ndx_ptr2->label);
         ctlwarning(me,msg);
         return(1);
      }
      if (iflag != 0) {
         if (ndx_ptr1->imax < ndx_ptr2->imax) {
            ndx_ptr1->imin = ndx_ptr1->imin + plusmin1;
            ndx_ptr1->imax = ndx_ptr1->imax + plusmin1;
            ndx_ptr2->imin = ndx_ptr2->imin + plusmin2;
            ndx_ptr2->imax = ndx_ptr2->imax + plusmin2;
         } else {
            ndx_ptr1->imin = ndx_ptr1->imin + plusmin2;
            ndx_ptr1->imax = ndx_ptr1->imax + plusmin2;
            ndx_ptr2->imin = ndx_ptr2->imin + plusmin1;
            ndx_ptr2->imax = ndx_ptr2->imax + plusmin1;
         }
         ndx_ptr1->imin = MIN(ndx_ptr1->imin,ndx_ptr2->imin);
         ndx_ptr1->imax = MAX(ndx_ptr1->imax,ndx_ptr2->imax);
         ndx_ptr1->in[0][0] = ndx_ptr1->imin;
         ndx_ptr1->in[0][1] = ndx_ptr1->imax;
         ndx_ptr1->in[0][2] = 1;
         ndx_ptr1->logical  = 0;
      } else if (jflag != 0) {
         if (ndx_ptr1->jmax < ndx_ptr2->jmax) {
            ndx_ptr1->jmin = ndx_ptr1->jmin + plusmin1;
            ndx_ptr1->jmax = ndx_ptr1->jmax + plusmin1;
            ndx_ptr2->jmin = ndx_ptr2->jmin + plusmin2;
            ndx_ptr2->jmax = ndx_ptr2->jmax + plusmin2;
         } else {
            ndx_ptr1->jmin = ndx_ptr1->jmin + plusmin2;
            ndx_ptr1->jmax = ndx_ptr1->jmax + plusmin2;
            ndx_ptr2->jmin = ndx_ptr2->jmin + plusmin1;
            ndx_ptr2->jmax = ndx_ptr2->jmax + plusmin1;
         }
         ndx_ptr1->jmin = MIN(ndx_ptr1->jmin,ndx_ptr2->jmin);
         ndx_ptr1->jmax = MAX(ndx_ptr1->jmax,ndx_ptr2->jmax);
         ndx_ptr1->in[1][0] = ndx_ptr1->jmin;
         ndx_ptr1->in[1][1] = ndx_ptr1->jmax;
         ndx_ptr1->in[1][2] = 1;
         ndx_ptr1->logical  = 1;
      } else if (kflag != 0) {
         if (ndx_ptr1->kmax < ndx_ptr2->kmax) {
            ndx_ptr1->kmin = ndx_ptr1->kmin + plusmin1;
            ndx_ptr1->kmax = ndx_ptr1->kmax + plusmin1;
            ndx_ptr2->kmin = ndx_ptr2->kmin + plusmin2;
            ndx_ptr2->kmax = ndx_ptr2->kmax + plusmin2;
         } else {
            ndx_ptr1->kmin = ndx_ptr1->kmin + plusmin2;
            ndx_ptr1->kmax = ndx_ptr1->kmax + plusmin2;
            ndx_ptr2->kmin = ndx_ptr2->kmin + plusmin1;
            ndx_ptr2->kmax = ndx_ptr2->kmax + plusmin1;
         }
         ndx_ptr1->kmin = MIN(ndx_ptr1->kmin,ndx_ptr2->kmin);
         ndx_ptr1->kmax = MAX(ndx_ptr1->kmax,ndx_ptr2->kmax);
         ndx_ptr1->in[2][0] = ndx_ptr1->kmin;
         ndx_ptr1->in[2][1] = ndx_ptr1->kmax;
         ndx_ptr1->in[2][2] = 1;
         ndx_ptr1->logical  = 2;
      } 
      ndx_ptr1 = ndx_ptr1->next;
      ndx_ptr2 = ndx_ptr2->next;
   }
   if (((ndx_ptr1 == NULL) && (ndx_ptr2 != NULL)) ||
       ((ndx_ptr1 != NULL) && (ndx_ptr2 == NULL))) {
      sprintf(msg,"Nodelists %s and %s are of different length.\n They cannot be differenced.",
                      ndxin1->label,ndxin2->label);
      ctlwarning(me,msg);
      return(1);
   }    
   return(error);
}
void NodeWindow_copy(NodeWindow_t *ndxout, NodeWindow_t *ndxin) {
   int i;
   strcpy(ndxout->label,ndxin->label);
   ndxout->ublk     = ndxin->ublk;
   ndxout->rank     = ndxin->rank;
   ndxout->len      = ndxin->len;
   ndxout->logical  = ndxin->logical;
   if (ndxout->len > 0) {
      ndxout->ndx = MALLOT(int,ndxout->len);
      ndxout->blk = MALLOT(int,ndxout->len);
      for (i = 0; i < ndxout->len; i++) {
         ndxout->ndx[i]  = ndxin->ndx[i];
         ndxout->blk[i]  = ndxin->blk[i];
         ndxout->udx[i]  = ndxin->udx[i];
         ndxout->pos[i]  = ndxin->pos[i];
      }
   }
   CPYEXT((*ndxout),(*ndxin));
   for (i = 0; i < NRANKX; i++) {
      ndxout->in[i][0] = ndxin->in[i][0];
      ndxout->in[i][1] = ndxin->in[i][1];
      ndxout->in[i][2] = ndxin->in[i][2];
   }
}
void NodeWindow_free(NodeWindow_t *ndxin) {
   NodeWindow_t *tmp;
   while(ndxin != NULL) {
      tmp = ndxin->next;         
      NodeWindow_freendx(ndxin);
      FREEMEM(ndxin);
      ndxin = tmp;
   }
   ndxin = NULL;
}
void NodeWindow_add(NodeWindow_t *new_ndx, NodeWindow_t **list) {
   NodeWindow_t *local_list;
   local_list = *list;
   if (local_list != NULL) { 
      while (local_list->next != NULL) local_list = local_list->next; 
      local_list->next = new_ndx; 
   } else {
      *list = new_ndx; 
   } 
   new_ndx->next = NULL;
}
int NodeWindow_getndx(NodeWindow_t *inndx, int gblk_in, int ndx_ovlp, int ndx_incl,
                   int ndx_cent ) {
   int len;
   int n;
   int i,j,k,g;
   int idndx, idblk;
   int iblk, gblk;
   int ublk_in;
   int namix;
   int signi = 1;
   int signj = 1;
   int signk = 1;
   int *my_in[4];
   ublk_in = inndx->ublk;
   len = NodeWindow_getlen(inndx,gblk_in,ndx_ovlp,ndx_incl,ndx_cent);
   if (len == 0) return(len);
   inndx->len  = 200;
   inndx->len_total  = 0;
   inndx->ndx = ALLOT(int,inndx->len);
   inndx->udx = ALLOT(int,inndx->len);
   inndx->pos = ALLOT(int,inndx->len);
   inndx->blk = ALLOT(int,inndx->len);
   my_in[0] = inndx->in[0];
   my_in[1] = inndx->in[1];
   my_in[2] = inndx->in[2];
   my_in[3] = inndx->in[3];
   if (my_in[0][2] < 0) signi = -1 ;
   if (my_in[1][2] < 0) signj = -1 ;
   if (my_in[2][2] < 0) signk = -1 ;
   n = 0;
   if (inndx->rank == 1) {
      for ( i = my_in[0][0]; i*signi <= signi*my_in[0][1]; i += my_in[0][2] ) {
         inndx->blk[n] = ublk_in ;
         inndx->ndx[n] = i ;
         inndx->pos[n] = n ;
         inndx->len_total++;
         if (n >= inndx->len - 1) {
            inndx->len = (int) (1.5 * inndx->len);
            inndx->ndx = REALLOT(inndx->ndx,int,inndx->len);
            inndx->udx = REALLOT(inndx->udx,int,inndx->len);
            inndx->blk = REALLOT(inndx->blk,int,inndx->len);
            inndx->pos = REALLOT(inndx->pos,int,inndx->len);
         }
         n++ ;
      }
   } else if (inndx->rank == 2) {
      for (i = my_in[0][0]; i*signi <= signi*my_in[0][1]; i += my_in[0][2] ) {
         for (j = my_in[1][0]; j*signj <= signj*my_in[1][1]; j += my_in[1][2]) {
            NodeWindow_setndx(ublk_in, gblk_in, i, j, 0, &n, inndx, ndx_ovlp,
                        ndx_incl, ndx_cent); 
         }
      }
   } else if ((inndx->rank == 3) && (ndims == 3)) {
      for (i = my_in[0][0]; i*signi <= signi*my_in[0][1]; i += my_in[0][2] ) {
         for (j = my_in[1][0]; j*signj <= signj*my_in[1][1]; j += my_in[1][2]) {
            for (k = my_in[2][0]; k*signk <= signk*my_in[2][1]; k += my_in[2][2] ) {
               NodeWindow_setndx(ublk_in, gblk_in, i, j, k, &n, inndx,  
                        ndx_ovlp, ndx_incl, ndx_cent); 
            }
         }
      } 
   } else if ((inndx->rank == 3) && (ndims == 2)) {
      for ( i = my_in[0][0] ; i <= my_in[0][1] ; i += my_in[0][2] ) {
         for ( j = my_in[1][0] ; j <= my_in[1][1] ; j += my_in[1][2] ) {
            NodeWindow_setndx(ublk_in, gblk_in, i, j, 0, &n, inndx,  
                        ndx_ovlp, ndx_incl, ndx_cent); 
            idndx = inndx->ndx[n-1];
            idblk = inndx->blk[n-1];
            namix = 0;
            if (idblk >= 0) {
               namix = domains[idblk].namix;
            }
            for ( g = my_in[2][0] ; g <= my_in[2][1] ; g += my_in[2][2] ) {
               if (idblk >= 0) {
                  inndx->ndx[n] = idndx + g*namix;
                  inndx->blk[n] = idblk;
                  inndx->pos[n] = inndx->len_total;
                  n++;
               }
               inndx->len_total++;
               if (n >= inndx->len - 1) {
                  inndx->len = (int) (1.5 * inndx->len);
                  inndx->ndx = REALLOT(inndx->ndx,int,inndx->len);
                  inndx->udx = REALLOT(inndx->udx,int,inndx->len);
                  inndx->blk = REALLOT(inndx->blk,int,inndx->len);
                  inndx->pos = REALLOT(inndx->pos,int,inndx->len);
               }
            } 
         } 
      } 
   } else if ((inndx->rank == 4) && (ndims == 3)) {
      for ( i = my_in[0][0] ; i <= my_in[0][1] ; i += my_in[0][2] ) {
         for ( j = my_in[1][0] ; j <= my_in[1][1] ; j += my_in[1][2] ) {
            for ( k = my_in[2][0] ; k <= my_in[2][1] ; k += my_in[2][2] ) {
               NodeWindow_setndx(ublk_in, gblk_in, i, j, k, &n, inndx,
                           ndx_ovlp, ndx_incl, ndx_cent); 
               idndx = inndx->ndx[n-1];
               idblk = inndx->blk[n-1];
               namix = 0;
               if (idblk >= 0) {
                  namix = domains[idblk].namix;
               }
               for ( g = my_in[3][0] ; g <= my_in[3][1] ; g += my_in[3][2] ) {
                  if (idblk >= 0) {
                     inndx->ndx[n] = idndx + g*namix;
                     inndx->blk[n] = idblk;
                     inndx->pos[n] = inndx->len_total;
                     n++;
                  }
                  inndx->len_total++;
                  if (n >= inndx->len - 1) {
                     inndx->len = (int) (1.5 * inndx->len);
                     inndx->ndx = REALLOT(inndx->ndx,int,inndx->len);
                     inndx->udx = REALLOT(inndx->udx,int,inndx->len);
                     inndx->blk = REALLOT(inndx->blk,int,inndx->len);
                     inndx->pos = REALLOT(inndx->pos,int,inndx->len);
                  }
               }
            }
         }
      }
   } 
   if (n == 0) {
      NodeWindow_freendx(inndx);
   }
   inndx->len = n;
   return(n);
} 
int NodeWindow_getlen(NodeWindow_t *inndx, int gblk_in, int ndx_ovlp, int ndx_incl,
                   int ndx_cent) {
   int gblk;
   int ublk;
   int len;
   Extents_t ext1;
   Extents_t ext2;
   Extents_t ext3;
   len = 0;
   inndx->len = 0;
   ublk = inndx->ublk;
   if (inndx->rank == 1) {
     len = (inndx->in[0][1] - inndx->in[0][0]) / (inndx->in[0][2]) + 1;
     inndx->len = len;
     return(len);
   }
   if (gblk_in >= 0) {
      if (ublk != gmap[gblk_in].ublk) {
         len = 0;
      } else {
         CPYEXT(ext1,gmap[gblk_in]);
         CPYEXT(ext2,(*inndx));
         NodeWindow_setext(&ext1, ublk, ndx_incl, ndx_cent) ;
         len = extents_overlap(&ext1,&ext2,&ext3);
      } 
   } else if (ndx_ovlp == NDX_NO_OVERLAP) {
      len = LENEXT((*inndx));
   } else if (ndx_ovlp == NDX_OVERLAP) {
      for (gblk = 0; gblk < gnblk; gblk++) {
         if (gmap[gblk].ublk == ublk) {
            CPYEXT(ext1,gmap[gblk]);
            CPYEXT(ext2,(*inndx));
            NodeWindow_setext(&ext1, ublk, ndx_incl, ndx_cent) ;
            len += extents_overlap(&ext1,&ext2,&ext3);
         }
      }
   }
   if ((inndx->rank == 3) && (ndims == 2))  {
      len = len * (inndx->in[2][1] - inndx->in[2][0]) / (inndx->in[2][2]) + 1;
   }
   if ((inndx->rank == 4) && (ndims == 3))  {
      len = len * (inndx->in[3][1] - inndx->in[3][0]) / (inndx->in[3][2]) + 1;
   }
   inndx->len = len;
   return(len);
}
void NodeWindow_setext(Extents_t *ext, int ublk, int ndx_incl, int ndx_cent) 
{
   if (ndx_cent == NDX_ZONAL) {
      ext->imax--;
      ext->jmax--;
      if (ndims == 3) ext->kmax--;
   }
   if (ndx_incl == NDX_USER_PHONY) {
      if (ext->imin == umap[ublk].imin) ext->imin--;
      if (ext->jmin == umap[ublk].jmin) ext->jmin--;
      if (ext->imax == umap[ublk].imax) ext->imax++;
      if (ext->jmax == umap[ublk].jmax) ext->jmax++;
      if (ndims == 3) {
         if (ext->kmin == umap[ublk].kmin) ext->kmin--;
         if (ext->kmax == umap[ublk].kmax) ext->kmax++;
      }
   } else if (ndx_incl == NDX_GLBL_PHONY) {
      ext->imin--;
      ext->jmin--;
      ext->imax++;
      ext->jmax++;
      if (ndims == 3) {
         ext->kmin--;
         ext->kmax++;
      }
   }
}
void NodeWindow_setndx(int ublk_in, int gblk_in, int i, int j, int k, int* n, 
                 NodeWindow_t *inndx, int ndx_ovlp, int ndx_incl, int ndx_cent) {
   int i0;
   int j0;
   int k0;
   int id;
   int gblk;
   int iblk;
   int flag;
   Extents_t ext;
   id = *n;
   flag = 0;
   if (ndims == 2) {
      for (gblk = 0; gblk < gnblk; gblk++) {
         iblk = gmap[gblk].lblk;
         if ((gblk_in >= 0) && (gblk != gblk_in)) continue;
         if (gmap[gblk].ublk == ublk_in) {
            CPYEXT(ext,gmap[gblk]);
            NodeWindow_setext(&ext, ublk_in, ndx_incl, ndx_cent) ;
            if ((i >= ext.imin) && (i <= ext.imax) &&
                (j >= ext.jmin) && (j <= ext.jmax)) {
               i0 = i - gmap[gblk].imin + NPNL;
               j0 = j - gmap[gblk].jmin + NPNL;
               if (iblk >= 0) {
                  flag = 1;			 
                  inndx->blk[id] = iblk;
                  inndx->ndx[id] = i0 + j0*gmap[gblk].jp;
                  inndx->udx[id] = i + j*umap[ublk_in].jp;
                  inndx->pos[id] = inndx->len_total;
                  if (ndx_ovlp == NDX_OVERLAP)  {
	             id++;
                  }
               } 
               if (ndx_ovlp == NDX_OVERLAP)  {
                  inndx->len_total++;
               }
               if (id >= inndx->len - 1) {
                  inndx->len = (int)(1.5 * inndx->len);
                  inndx->ndx = REALLOT(inndx->ndx,int,inndx->len);
                  inndx->udx = REALLOT(inndx->udx,int,inndx->len);
                  inndx->blk = REALLOT(inndx->blk,int,inndx->len);
                  inndx->pos = REALLOT(inndx->pos,int,inndx->len);
               }
            }
         }
      }
   } else {
      for (gblk = 0; gblk < gnblk; gblk++) {
         iblk = gmap[gblk].lblk;
         if ((gblk_in >= 0) && (gblk != gblk_in)) continue;
         if (gmap[gblk].ublk == ublk_in) {
            CPYEXT(ext,gmap[gblk]);
            NodeWindow_setext(&ext, ublk_in, ndx_incl, ndx_cent) ;
            if ((i >= ext.imin) && (i <= ext.imax) &&
                (j >= ext.jmin) && (j <= ext.jmax) &&
                (k >= ext.kmin) && (k <= ext.kmax)) {
               i0 = i - gmap[gblk].imin + NPNL;
               j0 = j - gmap[gblk].jmin + NPNL;
               k0 = k - gmap[gblk].kmin + NPNL;
               if (iblk >= 0) {
                  flag = 1;			 
                  inndx->blk[id] = iblk;
                  inndx->ndx[id] = i0 + j0*gmap[gblk].jp + k0*gmap[gblk].kp;
                  inndx->udx[id] = i + j*umap[ublk_in].jp + k*umap[ublk_in].kp;
                  inndx->pos[id] = inndx->len_total;
                  if (ndx_ovlp == NDX_OVERLAP)  {
	             id++;
                  }
               } 
               if (ndx_ovlp == NDX_OVERLAP)  {
                  inndx->len_total++;
               }
               if (id >= inndx->len - 1) {
                  inndx->len = (int) (1.5 * inndx->len);
                  inndx->ndx = REALLOT(inndx->ndx,int,inndx->len);
                  inndx->udx = REALLOT(inndx->udx,int,inndx->len);
                  inndx->blk = REALLOT(inndx->blk,int,inndx->len);
                  inndx->pos = REALLOT(inndx->pos,int,inndx->len);
               }
            }
         }
      }
   }
   if (ndx_ovlp == NDX_NO_OVERLAP) {
      inndx->len_total++;
      if (flag == 1) id++;
   }
   *n = id;
}

#ifdef SILO
int NodeWindow_wtsilo(DBfile *idbid, char *name, NodeWindow_t *ndxin) {
   NodeWindow_t *ndxptr;
   int i;
   int n;
   int dims[2];
   int error;
   int ublk;
   int myext[6];
   int myin[12];
   char outname[MAXLINE];
   error = 0;
   n = 0;
   ndxptr = ndxin;
   while (ndxptr != NULL) {
      dims[0] = 1;
      sprintf(outname,"Block%i",n);
      error += DBWrite(idbid,outname,&ndxptr->ublk,dims,1,DB_INT);
      ublk = ndxptr->ublk;
      dims[0] = 6;
      sprintf(outname,"Extents%i",n);
      i = 0;
      myext[i++] = ndxptr->imin - umap[ublk].imin;
      myext[i++] = ndxptr->imax - umap[ublk].imin;
      myext[i++] = ndxptr->jmin - umap[ublk].jmin;
      myext[i++] = ndxptr->jmax - umap[ublk].jmin;
      myext[i++] = ndxptr->kmin - umap[ublk].kmin;
      myext[i++] = ndxptr->kmax - umap[ublk].kmin;
      error += DBWrite(idbid,outname,myext,dims,1,DB_INT);
      dims[0] = 1;
      sprintf(outname,"Rank%i",n);
      error += DBWrite(idbid,outname,&ndxptr->rank,dims,1,DB_INT);
      i = 0;
      myin[i++] = ndxptr->in[0][0];
      myin[i++] = ndxptr->in[0][1];
      myin[i++] = ndxptr->in[0][2];
      myin[i++] = ndxptr->in[1][0];
      myin[i++] = ndxptr->in[1][1];
      myin[i++] = ndxptr->in[1][2];
      myin[i++] = ndxptr->in[2][0];
      myin[i++] = ndxptr->in[2][1];
      myin[i++] = ndxptr->in[2][2];
      myin[i++] = ndxptr->in[3][0];
      myin[i++] = ndxptr->in[3][1];
      myin[i++] = ndxptr->in[3][2];
      dims[0] = 12;
      sprintf(outname,"Stride%i",n);
      error += DBWrite(idbid,outname,myin,dims,1,DB_INT);
      ndxptr = ndxptr->next; 
      n++;
   }
   dims[0] = 1;
   error += DBWrite(idbid,"NumberWindows",&n,dims,1,DB_INT);
   return(error);
}
#endif
#ifdef SILO
int NodeWindow_rdsilo(DBfile *idbid, char *name, NodeWindow_t **ndxin, int ublk0) {
   NodeWindow_t *ndxptr;
   int i;
   int j;
   int n;
   int error;
   int ublk;
   int myext[6];
   int myin[12];
   char inname[MAXLINE];
   error = 0;
   n = 0;
   error += DBReadVar(idbid,"NumberWindows",&n);
   ndxptr = *ndxin;
   DBShowErrors(DB_NONE, NULL);
   for (j = 0; j < n; j++) {
      ndxptr = MALLOT(NodeWindow_t,1);
      sprintf(inname,"Block%i",j);
      error += DBReadVar(idbid,inname,&ndxptr->ublk);
      ndxptr->ublk += ublk0;
      ublk = ndxptr->ublk;
      sprintf(inname,"Extents%i",j);
      error += DBReadVar(idbid,inname,myext);
      i = 0;
      ndxptr->imin     = myext[i++] + umap[ublk].imin;
      ndxptr->imax     = myext[i++] + umap[ublk].imin;
      ndxptr->jmin     = myext[i++] + umap[ublk].jmin;
      ndxptr->jmax     = myext[i++] + umap[ublk].jmin;
      ndxptr->kmin     = myext[i++] + umap[ublk].kmin;
      ndxptr->kmax     = myext[i++] + umap[ublk].kmin;
      sprintf(inname,"Rank%i",j);
      error = DBReadVar(idbid,inname,&ndxptr->rank);
      if (error != 0) {
         ndxptr->rank = ndims;
         error = 0;
      }
      sprintf(inname,"Stride%i",j);
      error = DBReadVar(idbid,inname,myin);
      if (error != 0) {
	 i = 0;
         myin[i++] = ndxptr->imin;
         myin[i++] = ndxptr->imax;
         myin[i++] = 1;
         myin[i++] = ndxptr->jmin;
         myin[i++] = ndxptr->jmax;
         myin[i++] = 1;
         myin[i++] = ndxptr->kmin;
         myin[i++] = ndxptr->kmax;
         myin[i++] = 1;
         myin[i++] = 0;
         myin[i++] = 0;
         myin[i++] = 0;
         error = 0;
      }
      i = 0;
      ndxptr->in[0][0] = myin[i++];
      ndxptr->in[0][1] = myin[i++];
      ndxptr->in[0][2] = myin[i++];
      ndxptr->in[1][0] = myin[i++];
      ndxptr->in[1][1] = myin[i++];
      ndxptr->in[1][2] = myin[i++];
      ndxptr->in[2][0] = myin[i++];
      ndxptr->in[2][1] = myin[i++];
      ndxptr->in[2][2] = myin[i++];
      ndxptr->in[3][0] = myin[i++];
      ndxptr->in[3][1] = myin[i++];
      ndxptr->in[3][2] = myin[i++];
      ndxptr->len      = 0;
      mkpalab(ndxptr->label,name,ndxptr->ublk,ndxptr->in,ndxptr->rank,0,"") ; 
      NodeWindow_add(ndxptr,ndxin);
   }
   DBShowErrors(DB_TOP, NULL);
   return(error);
}
#endif
void NodeWindow_freendx(NodeWindow_t *ndxin) {
   if (ndxin->len > 0) {
      FREEMEM(ndxin->udx);
      FREEMEM(ndxin->ndx);
      FREEMEM(ndxin->blk);
      FREEMEM(ndxin->pos);
      ndxin->len = 0;
   }
}
static void NodeWindow_zonalize(NodeWindow_t *in_ndx) {
   NodeWindow_t *my_ndx_ptr;
   my_ndx_ptr = in_ndx;
   while (my_ndx_ptr != NULL) {
      if (my_ndx_ptr->imin < my_ndx_ptr->imax) my_ndx_ptr->imax--;
      if (my_ndx_ptr->jmin < my_ndx_ptr->jmax) my_ndx_ptr->jmax--;
      if (ndims == 3) {
         if (my_ndx_ptr->kmin < my_ndx_ptr->kmax) my_ndx_ptr->kmax--;
      }
      if ((my_ndx_ptr->in[0][1] - my_ndx_ptr->in[0][0]) > 0) {
         my_ndx_ptr->in[0][1]--;
      } else if ((my_ndx_ptr->in[0][1] - my_ndx_ptr->in[0][0]) < 0) {
         my_ndx_ptr->in[0][0]--;
      } 
      if ((my_ndx_ptr->in[1][1] - my_ndx_ptr->in[1][0]) > 0) {
         my_ndx_ptr->in[1][1]--;
      } else if ((my_ndx_ptr->in[1][1] - my_ndx_ptr->in[1][0]) < 0) {
         my_ndx_ptr->in[1][0]--;
      } 
      if ((my_ndx_ptr->in[2][1] - my_ndx_ptr->in[2][0]) > 0) {
        my_ndx_ptr->in[2][1]--;
      } else if ((my_ndx_ptr->in[2][1] - my_ndx_ptr->in[2][0]) < 0) {
        my_ndx_ptr->in[2][0]--;
      } 
      my_ndx_ptr = my_ndx_ptr->next;
   }
}
int NodeWindow_compact(NodeWindow_t *in_ndx, NodeWindow_t *out_ndx, 
                    int gblk_in, 
		    int ndx_ovlp, 
		    int ndx_incl,
                    int ndx_cent ) {
   int i,j;
   int len;
   int len_total;
   NodeWindow_t *ndxptr;
   len = 0;
   ndxptr = in_ndx;
   while (ndxptr != NULL) {
      len += NodeWindow_getndx(ndxptr,gblk_in,ndx_ovlp,ndx_incl,ndx_cent);
      ndxptr = ndxptr->next;
   }
   out_ndx->pos = MALLOT(int,len);
   out_ndx->ndx = MALLOT(int,len);
   out_ndx->udx = MALLOT(int,len);
   out_ndx->blk = MALLOT(int,len);
   out_ndx->len_total = 0;
   out_ndx->len = 0;
   ndxptr = in_ndx;
   j = 0;
   while (ndxptr != NULL) {
      for (i = 0; i < ndxptr->len; i++) {
         out_ndx->ndx[j] = ndxptr->ndx[i];
         out_ndx->blk[j] = ndxptr->blk[i];
         out_ndx->udx[j] = ndxptr->udx[i];
         out_ndx->pos[j] = ndxptr->pos[i] + out_ndx->len_total;
         j++;
      }
      out_ndx->len_total += ndxptr->len_total;
      out_ndx->len += ndxptr->len;
      NodeWindow_freendx(ndxptr);
      ndxptr = ndxptr->next;
   }
   out_ndx->next = NULL;
   return(out_ndx->len);
}
void NodeWindow_getstr(int ndx, char *string, int gblk) {
   int i,j,k;   
   int ublk;
   ublk = gmap[gblk].ublk;
   if (ndims == 2) {
      NDXEXT2D(ndx, i, j, gmap[gblk]);
      i = i + gmap[gblk].imin - 2 * NPNL + 1;
      j = j + gmap[gblk].jmin - 2 * NPNL + 1;
      sprintf(string,":%i(%i,%i)",ublk, i, j);
   } else {
      NDXEXT3D(ndx, i, j, k, gmap[gblk]);
      i = i + gmap[gblk].imin - 2 * NPNL + 1;
      j = j + gmap[gblk].jmin - 2 * NPNL + 1;
      k = k + gmap[gblk].kmin - 2 * NPNL + 1;
      sprintf(string,":%i(%i,%i,%i)",ublk, i, j, k);
   } 
}
int NodeWindow_fastndx(NodeWindow_t *in_ndx, int gblk, int ndx_incl, int ndx_cent) {
   int i;
   int ublk;
   int len;
   Extents_t ext1,ext2,ext3;
   CPYEXT(ext1,(*in_ndx));
   CPYEXT(ext2,gmap[gblk]);
   ublk = in_ndx->ublk;
   if (gmap[gblk].ublk != ublk) return(0);
   NodeWindow_setext(&ext2, ublk, ndx_incl, ndx_cent);
   len = extents_overlap(&ext2, &ext1, &ext3);
   in_ndx->len_total = len;
   in_ndx->len       = len;
   if (len > 0) {
      in_ndx->ndx = MALLOT(int,len);
      in_ndx->udx = MALLOT(int,len);
      in_ndx->blk = MALLOT(int,len);
      in_ndx->pos = MALLOT(int,len);
      CPYEXT(ext2,gmap[gblk]);
      TRSEXT(ext1, ext3, ext2);
      extents_getndx(ext1, gmap[gblk].jp, gmap[gblk].kp, in_ndx->ndx);
   }
   return(len);
}
void NodeWindow_copyall(NodeWindow_t *in_ndx, NodeWindow_t **out_ndx) {
   NodeWindow_t *ndxptr1 = NULL;
   NodeWindow_t *ndxptr2 = NULL;
   ndxptr1 = in_ndx;
   while (ndxptr1 != NULL) {
       ndxptr2 = MALLOT(NodeWindow_t, 1);
       NodeWindow_copy(ndxptr2, ndxptr1);
       NodeWindow_add(ndxptr2,out_ndx);
       ndxptr1 = ndxptr1->next;
   }
}
void NodeWindow_make( NodeWindow_t **ndxin, int imin, int imax, 
                   int jmin, int jmax, int kmin, int kmax, int ublk, 
		   char *name) 
{
   NodeWindow_t *ndxlocal;
   ndxlocal = *ndxin;
   if (ndxlocal == NULL) {
      ndxlocal = MALLOT(NodeWindow_t,1);
      strcpy(ndxlocal->label,name);
      ndxlocal->next = NULL;
      ndxlocal->len  = 0;
      ndxlocal->len_total  = 0;
      ndxlocal->logical  = -1;
      *ndxin = ndxlocal;
   }
   if (imax < 0) imax = 0;
   if (imin < 0) imin = 0;
   if (jmax < 0) jmax = 0;
   if (jmin < 0) jmin = 0;
   if (kmax < 0) kmax = 0;
   if (kmin < 0) kmin = 0;
   if (ublk < 0) ublk = 0;
   SETEXT((*ndxlocal),imin,imax,jmin,jmax,kmin,kmax);
   ndxlocal->ublk = ublk;
   ndxlocal->in[0][0] = imin;
   ndxlocal->in[0][1] = imax;
   ndxlocal->in[0][2] = 1;
   ndxlocal->in[1][0] = jmin;
   ndxlocal->in[1][1] = jmax;
   ndxlocal->in[1][2] = 1;
   ndxlocal->in[2][0] = kmin;
   ndxlocal->in[2][1] = kmax;
   ndxlocal->in[2][2] = 1;
   ndxlocal->rank     = 3;
   if (ndims == 2) {
      ndxlocal->kmin     = NPNL;
      ndxlocal->kmax     = NPNL;
      ndxlocal->in[2][0] = NPNL;
      ndxlocal->in[2][1] = NPNL;
      ndxlocal->in[2][2] = 1;
      ndxlocal->rank = 2;
   }
}
void NodeWindow_buildndx( NodeWindow_t *ndxin, int ndx_incl, int ndx_cent,
                      int gblk, int *inlen, int **inndx) {
   int size, i;
   int ublk;
   int len = 0; 
   int *ndx = NULL;
   Extents_t ext1,ext2,ext3;   
   NodeWindow_t *ndxin_ptr = ndxin;
   while (ndxin_ptr != NULL) {
      CPYEXT(ext1,(*ndxin_ptr));
      CPYEXT(ext2,gmap[gblk]);     
      ublk = ndxin_ptr->ublk;
      if (gmap[gblk].ublk == ublk) {
         NodeWindow_setext(&ext2, ublk, ndx_incl, ndx_cent); 
         size = extents_overlap(&ext2, &ext1, &ext3);
         len += size;
      }
      ndxin_ptr = ndxin_ptr->next;
   }
   if (len > 0) {
      ndx = MALLOT(int, len);
      len = 0;
      ndxin_ptr = ndxin;
      while (ndxin_ptr != NULL) {
         CPYEXT(ext1,(*ndxin_ptr));
         CPYEXT(ext2,gmap[gblk]);     
         ublk = ndxin_ptr->ublk;
         if (gmap[gblk].ublk == ublk) {
            NodeWindow_setext(&ext2, ublk, ndx_incl, ndx_cent); 
            size = extents_overlap(&ext2, &ext1, &ext3);
            if (size > 0) {
               int *lndx = MALLOT(int, size);
               CPYEXT(ext2,gmap[gblk]);     
               TRSEXT(ext1, ext3, ext2); 
               extents_getndx(ext1, gmap[gblk].jp, gmap[gblk].kp, lndx);  
               for (i = 0; i < size; i++) {
                  ndx[len++] = lndx[i];
               }
               FREEMEM(lndx);
            }
         }
         ndxin_ptr = ndxin_ptr->next;
      }
   }
   *inndx = ndx;
   *inlen = len;
}
void NodeWindow_intersect(char *name, NodeWindow_t *ndxin1, 
                         NodeWindow_t *ndxin2, 
                         NodeWindow_t **ndxout) {
   char *me = "NodeWindow_intersect";
   char msg[MAXLINE];
   int error;
   int len;
   NodeWindow_t *ndx1;
   NodeWindow_t *ndx2;
   NodeWindow_t *ndxtmp = NULL;
   NodeWindow_t *ndxnew = NULL;
   Extents_t ext1, ext2, ext3;
   ndxnew = *ndxout;
   ndx1 = ndxin1;
   while (ndx1 != NULL) {
      CPYEXT(ext1,(*ndx1));
      ndx2 = ndxin2;
      while (ndx2 != NULL) {
         if (ndx1->ublk == ndx2->ublk) {
            CPYEXT(ext2,(*ndx2));
            len = extents_overlap(&ext1,&ext2,&ext3);
            if (len > 0) {
               ndxtmp = NULL;
               NodeWindow_make(&ndxtmp, ext3.imin, ext3.imax, ext3.jmin, 
	                       ext3.jmax, ext3.kmin, ext3.kmax, ndx1->ublk, 
			       name);
               if (ndxnew == NULL) {
                  ndxnew = ndxtmp;
                 *ndxout = ndxnew;
               } else {
                  ndxnew->next = ndxtmp;
                  ndxnew = ndxnew->next;
               } 
            }
         }
         ndx2 = ndx2->next;
      }
      ndx1 = ndx1->next;
   }
}
