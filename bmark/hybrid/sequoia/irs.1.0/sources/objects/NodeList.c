#include "irs.h"
#include "irsrgst.h"
#include "irsgen.h"
#include "irsctl.h"
#include "NodeList.hh"
#include "ProblemArray.h"
#include "Rgst.h"
int NodeList_read( void ) {
   char *me = "NodeList_read";
   char msg[MAXLINE];
   char op[MAXLINE];
   char name[MAXLINE];
   int i,len;
   int gotone;
   int error;
   int getnext;
   NodeList_t *NodeList;
   NodeList_t *NodeList_tmp;
   NodeWindow_t *my_ndx;
   NodeWindow_t *my_ndx_tmp;
   NodeWindow_t *last;
   NodeWindow_t *ndxnew;
   error = 0;
   geta(op);
   if (!strcmp(op,"delete")) {
      geta(op);
      NodeList_del(op);
      return(0);
   }
   len = strlen(op);   
   for (i = 0; i < len; i++) {
      if (isalpha(op[i])) break;
   }
   if (i == len) {
      sprintf(msg,"Nodelist name %s is invalid.  Nodelists names must contain a character.",op);
      ctlwarning(me,msg);
      return(-1);
   }
   NodeList = NodeList_find(op);
   if (NodeList == NULL) {
      NodeList = MALLOT(NodeList_t,1);
      strcpy(NodeList->name,op);
      NodeList_add(NodeList);
      NodeList->list = NULL;
   } else {
      sprintf(msg,"Node list %s is being redefined.",op);
      ctlwarning(me,msg);
      NodeWindow_free(NodeList->list);
      NodeList->list = NULL;
   }
   geta(op);
   peekc(op);
   NodeList_tmp = NodeList_find(op);
   if (NodeList_tmp != NULL) {
      geta(op);
      my_ndx_tmp = NodeList_tmp->list;
      while (my_ndx_tmp != NULL) {
         my_ndx = MALLOT(NodeWindow_t,1);
         NodeWindow_copy(my_ndx,my_ndx_tmp);
         NodeWindow_add(my_ndx,&NodeList->list);
         my_ndx_tmp = my_ndx_tmp->next;
      }
   } else {
      error = NodeWindow_read(NodeList->name, &NodeList->list) ;
      if (error != 0) return(error);
   }
   gotone  = 1;
   getnext = 0;
   while (gotone) {
      peekc(op);
      if ((getnext == 1) || (iplusmin == 1)) {
         geta(op);
         peekc(op);
	 last = NULL;
         NodeList_tmp = NodeList_find(op);
         if (NodeList_tmp != NULL) {
            geta(op);
            my_ndx_tmp = NodeList_tmp->list;
            while (my_ndx_tmp != NULL) {
               my_ndx = MALLOT(NodeWindow_t,1);
               NodeWindow_copy(my_ndx,my_ndx_tmp);
               if (getnext == 1) {
                  NodeWindow_add(my_ndx,&last);
               } else {
                  NodeWindow_add(my_ndx,&NodeList->list);
               } 
               my_ndx_tmp = my_ndx_tmp->next;
            }
         } else {
            if (getnext == 1) {
               error = NodeWindow_read(NodeList->name, &last) ;
            } else {
               error = NodeWindow_read(NodeList->name, &NodeList->list) ;
            } 
            if (error != 0) return(error);
         }
         if (getnext == 1) {
            NodeWindow_t *ndx1 = NodeList->list;
            NodeWindow_t *ndx2 = last;
            ndxnew = NULL;
            NodeWindow_intersect(NodeList->name, ndx1, ndx2, &ndxnew);
            NodeWindow_free(NodeList->list);
            NodeWindow_free(last);
            NodeList->list = ndxnew;
         }
         getnext = 0;
      } else if (!strcmp(op,"x")) {
         getnext = 1;
      } else {
         gotone = 0;
      }
   }
   return(error);
}
void NodeList_add(NodeList_t *new_ndx) {
   char name[MAXLINE];
   NodeList_t *local_list;
   sprintf(name,"NodeList_%s",new_ndx->name);
   if (!rgst_check_for_obj(name)) {
      rgst_add(name, "NodeList_t", new_ndx, NULL) ;
   }
}
void NodeList_free(void) {
   NodeList_t *ndx_list;
   int  i,n;
   char **list;
   list = rgst_list_objs_by_type( &n, "NodeList_t" );
   for (i = 0; i < n; i++) {
      ndx_list = (NodeList_t *) rgst_get_t(list[i],"NodeList_t");
      rgst_del( list[i] );
      NodeWindow_free(ndx_list->list);
      FREEMEM(ndx_list);
      FREEMEM(list[i]);
   }
   FREEMEM(list);
}

#ifdef SILO
int NodeList_wtsilo(DBfile *idbid) {
   char *me = "NodeList_wtsilo";
   char msg[MAXLINE]; 
   char outname[MAXLINE]; 
   int dims[2];
   int error;
   int i,n;
   char **list;
   NodeList_t *NodeListptr;
   list = rgst_list_objs_by_type( &n, "NodeList_t" );
   error = 0;
   if (n == 0) return(error);
   error = DBMkDir(idbid, "Nodelists");
   error = DBSetDir(idbid, "Nodelists");
   for (i = 0; i < n; i++) {
      sprintf(outname,"Nodelist%i",i);
      error = DBMkDir(idbid,outname);
      error = DBSetDir(idbid,outname);
      NodeListptr = (NodeList_t *)rgst_get_t(list[i],"NodeList_t");
      dims[0] = strlen(NodeListptr->name) + 1;
      error = DBWrite(idbid,"Name",NodeListptr->name,dims,1,DB_CHAR);
      error = NodeWindow_wtsilo(idbid,NodeListptr->name,NodeListptr->list);
      if (error != 0) {
         sprintf(msg,"Error writing nodelist %s",NodeListptr->name);
         ctlwarning(me,msg);
      }
      error = DBSetDir(idbid,"../");
      FREEMEM(list[i]);
   }
   FREEMEM(list);
   dims[0] = 1;
   error = DBWrite(idbid,"NumberNodelists",&n,dims,1,DB_INT);
   error = DBSetDir(idbid, "../");
   return(error);
}
#endif

#ifdef SILO
int NodeList_rdsilo(DBfile *idbid, int ublk0) {
   char *me = "NodeList_rdsilo";
   char msg[MAXLINE]; 
   char inname[MAXLINE]; 
   char name[MAXLINE]; 
   int i;
   int n;
   int error;
   NodeList_t *NodeListptr;
   error = 0;
   error = DBReadVar(idbid,"NumberNodelists",&n);
   for (i = 0; i < n; i++) {
      sprintf(inname,"Nodelist%i",i);
      error = DBSetDir(idbid,inname);
      error = DBReadVar(idbid,"Name",name);
      NodeListptr = NodeList_find(name);
      if (NodeListptr == NULL) {
         NodeListptr = MALLOT(NodeList_t,1);
         NodeListptr->list = NULL;
	 strcpy(NodeListptr->name,name);
         NodeList_add(NodeListptr);
      }
      error = NodeWindow_rdsilo(idbid,NodeListptr->name,&NodeListptr->list,ublk0);
      if (error != 0) {
         sprintf(msg,"Error reading nodelist %s",NodeListptr->name);
         ctlwarning(me,msg);
      }
      error = DBSetDir(idbid,"../");
   }
   return(error);
}
#endif

void NodeList_print(NodeList_t *NodeList) {
   NodeWindow_t *ndxptr;
   char name[MAXLINE];
   int count;
   PRINT(stdout,"%s =   \t",NodeList->name);
   ndxptr = NodeList->list;
   count = 0;
   while (ndxptr != NULL) {
      mkpalab(name,"",ndxptr->ublk,ndxptr->in,ndxptr->rank,0,"");
      if (ndxptr->next != NULL) {
          PRINT(stdout,"%s + ",name);
       } else {
          PRINT(stdout,"%s ",name);
       }
       ndxptr = ndxptr->next;
       count++;
       if ((ndims == 2) && (count > 3)) {
          PRINT(stdout,"\n        \t");
          count = 0;
       }
       if ((ndims == 3) && (count > 2)) {
          PRINT(stdout,"\n        \t");
          count = 0;
       }
   }
   PRINT(stdout,"\n");
}
void NodeList_make( NodeWindow_t *ndxin, char *name ) {
   char *me = "NodeList_make";
   char msg[MAXLINE];
   NodeList_t *NodeList;
   NodeList = NodeList_find(name);
   if (NodeList == NULL) {
      NodeList = MALLOT(NodeList_t,1);
      strcpy(NodeList->name,name);
      NodeList_add(NodeList);
   } else {
      sprintf(msg,"Node list %s is being redefined.",name);
      ctlwarning(me,msg);
      NodeWindow_free(NodeList->list);
   } 
   NodeList->list = ndxin;
}
NodeList_t *NodeList_find( char *name ) {
   char myname[MAXLINE];
   NodeList_t *NodeList = NULL;
   sprintf(myname,"NodeList_%s",name);
   if (rgst_check_for_obj(myname)) {
      NodeList = (NodeList_t *)rgst_get_t(myname, "NodeList_t");
   }
   return(NodeList);
}
void NodeList_addnextseq( char *name, NodeWindow_t *ndxin, char *result ) {
   int  num;
   char myname[MAXLINE];
   NodeList_t *NodeList;
   num = 0;
   sprintf(myname,"%s%i",name,num);
   NodeList = (NodeList_t *) NodeList_find(myname);
   while (NodeList != NULL) {
      num++;
      sprintf(myname,"%s%i",name,num);
      NodeList = (NodeList_t *) NodeList_find(myname);
   }
   sprintf(result, "%s%i", name, num);
   NodeList_make(ndxin, result);
}
void NodeList_pack( int **data, int *outlen, int *stroutlen, int oldlen ) {
   int i, n, inx, indx, jndx;
   int len;
   int *mydata, *numwins;
   NodeList_t *ndx_list;
   NodeWindow_t *list;
   char **ndlist;
   ndlist = rgst_list_objs_by_type( &n, "NodeList_t" );
   numwins = MALLOT(int,n);
   len = n + n + 1;
   for (inx = 0; inx < n; inx++) {
      numwins[inx] = 0;
      ndx_list = (NodeList_t *) rgst_get_t(ndlist[inx], "NodeList_t");
      list = ndx_list->list;
      while (list != NULL) {
         numwins[inx]++;
         len += 24 + 4 * list->len;
         list = list->next;
      }
   }
   *outlen = len;
   data[0] = REALLOT(data[0], int, oldlen + len);
   mydata = data[0];
   i = oldlen;
   *stroutlen = 0;
   mydata[i++] = n;
   for (inx = 0; inx < n; inx++) {
      ndx_list = (NodeList_t *) rgst_get_t(ndlist[inx], "NodeList_t");
      *stroutlen += (mydata[i++] = strlen(ndx_list->name));
      mydata[i++] = numwins[inx];
      list = ndx_list->list;
      while (list != NULL) {
         *stroutlen += (mydata[i++] = strlen(list->label));
         mydata[i++] = list->ublk;
         mydata[i++] = list->imin;
         mydata[i++] = list->imax;
         mydata[i++] = list->jmin;
         mydata[i++] = list->jmax;
         mydata[i++] = list->kmin;
         mydata[i++] = list->kmax;
         for (indx = 0; indx < 4; indx++) {
            for (jndx = 0; jndx < 3; jndx++) {
                mydata[i++] = list->in[indx][jndx];
            }
         }
         mydata[i++] = list->rank;
         mydata[i++] = list->len;
         mydata[i++] = list->len_total;
         mydata[i++] = list->logical;
         for (indx = 0; indx < list->len; indx++) {
            mydata[i++] = list->blk[indx];
            mydata[i++] = list->ndx[indx];
            mydata[i++] = list->pos[indx];
            mydata[i++] = list->udx[indx];
         }
         list = list->next;
      }
      FREEMEM(ndlist[inx]);
   }
   FREEMEM(ndlist);
   FREEMEM(numwins);
}
void NodeList_cpack( char **data ) {
   int inx, n;
   NodeList_t *ndx_list;
   NodeWindow_t *list;
   char **ndlist;
   char *mydata;
   ndlist = rgst_list_objs_by_type( &n, "NodeList_t" );
   mydata = data[0];
   for (inx = 0; inx < n; inx++) {
      ndx_list = (NodeList_t *) rgst_get_t(ndlist[inx], "NodeList_t");
      strcat(mydata, ndx_list->name);
      list = ndx_list->list;
      while (list != NULL) {
         strcat(mydata, list->label);
         list = list->next;
      }
      FREEMEM(ndlist[inx]);
   }
   FREEMEM(ndlist);
}
void NodeList_unpack( int *data, int len, char *ndx_names ) {
   int i, ni, n, inx, jnx, indx, jndx, slen;
   int numwins, delnl;
   NodeList_t *ndx_list;
   NodeWindow_t *list;
   i = 0;
   ni = 0;
   n = data[i++];
   for (inx = 0; inx < n; inx++) {
      ndx_list = ALLOT(NodeList_t,1);
      slen = data[i++];
      strncpy(ndx_list->name, &ndx_names[ni], slen);
      ni += slen;
      delnl = 0;
      if (!strncmp(ndx_list->name, "NL_", 3)) {
         delnl = 1;
      } else {
         NodeList_add(ndx_list);
      }
      ndx_list->list = NULL;
      numwins = data[i++];
      for (jnx = 0; jnx < numwins; jnx++) {
         list = ALLOT(NodeWindow_t,1);
         slen = data[i++];
         strncpy(list->label, &ndx_names[ni], slen);
         ni += slen;
         list->ublk = data[i++];
         list->imin = data[i++];
         list->imax = data[i++];
         list->jmin = data[i++];
         list->jmax = data[i++];
         list->kmin = data[i++];
         list->kmax = data[i++];
         for (indx = 0; indx < 4; indx++) {
            for (jndx = 0; jndx < 3; jndx++) {
                list->in[indx][jndx] = data[i++];
            }
         }
         list->rank = data[i++];
         list->len = data[i++];
         list->len_total = data[i++];
         list->logical = data[i++];
         for (indx = 0; indx < list->len; indx++) {
            list->blk[indx] = data[i++];
            list->ndx[indx] = data[i++];
            list->pos[indx] = data[i++];
            list->udx[indx] = data[i++];
         }
         if (delnl) {
            FREEMEM( list );
         } else {
            NodeWindow_add(list, &ndx_list->list);
         }
      }
      if (delnl) FREEMEM( ndx_list );
   }
}
char *NodeList_cunpack( char *data, int len ) {
   char *ndx_names;
   ndx_names = (char *) ALLOT(char,len+1); 
   strncpy(ndx_names, data, len);
   return ndx_names;
}
void NodeList_rename( char *name1, char *name2 ) {
   char name[MAXLINE];
   NodeList_t *NodeList = NULL;
   NodeList = NodeList_find(name1);
   if (NodeList != NULL) {
      sprintf(name,"NodeList_%s",NodeList->name);
      rgst_del( name );
      strcpy(NodeList->name,name2);
      NodeList_add(NodeList);
   }
}
void NodeList_del( char *name) {
   char myname[MAXLINE];
   NodeList_t *NodeList;
   NodeList = NodeList_find(name);
   if (NodeList != NULL) {
      sprintf(myname,"NodeList_%s",NodeList->name);
      rgst_del( myname );
      NodeWindow_free(NodeList->list);
      FREEMEM(NodeList);
   }
}
int NodeList_plnl( void ) {
   char *me = "NodeList_plnl";
   char op[MAXLINE];
   char name[MAXLINE];
   NodeList_t *nl;
   int count ;
   int gotone ;
   count = 0;
   gotone = 1;
   while (gotone) {
      peekc(op);
      nl = NodeList_find(op);
      if (nl == NULL) {
         geta(op);
         gotone = 0;
      } else {
         geta(op);
         sprintf(name,"NodeList_%s",op);
         rgst_add_attr(A_OBJECT, name, "NodeListPlotObj");
         count++;
      }
      if (lfchk() > 0) gotone = 0;
   }
   if (count == 0) {
      sprintf(name,"Could not find nodelist name %s.",op);
      ctlwarning(me,name);
   } else {
   } 
   return(0);
}
int NodeList_plnloff( void ) {
   rgst_del_attr_all("NodeListPlotObj");
   return(0);                            
}
void NodeList_plot( int iflab ) {
   char lab[MAXWORD];
   char *me = "NodeList_plot";
   char msg[2048];
   char name[MAXLINE];
   int i, count;
   int err;
   int len;
   int iblk;
   int *node;
   int *ndx;
   RGST_AttributeElem_t  *nlobjs;
   RGST_AttributeElem_t  *nlobjs_ptr;
   NodeList_t *nl;
   sprintf(msg," ");
   ProblemArray_add("NLPLOT_node", NULL, 0, R_INT, NULL);
   for (iblk = 0; iblk < nblk; iblk++) {
      ProblemArray_add("NLPLOT_node", NULL, domains[iblk].nnalls, R_INT, 
                        domains[iblk].hash);
      node = ProblemArray_allotptr("NLPLOT_node", domains[iblk].hash);
      for (i = 0; i < domains[iblk].nnalls; i++) {
         node[i] = domains[iblk].node[i];
      }
   }
   nlobjs = rgst_list_attr(A_OBJECT,"NodeListPlotObj");
   nlobjs_ptr = nlobjs;
   while (nlobjs_ptr != NULL) {
      nl = (NodeList_t *)nlobjs_ptr->rgst_obj->obj;
      for (iblk = 0; iblk < nblk; iblk++) {
         for (i = 0; i < domains[iblk].nnalls; i++) {
            domains[iblk].node[i] = 0;
         }
         NodeWindow_buildndx(nl->list, NDX_REAL, NDX_NODAL, domains[iblk].gblk, 
	                     &len, &ndx);
         for (i = 0; i < len; i++) {
            domains[iblk].node[ndx[i]] = 1;
         }
      }
      if (ndims == 2) {
      } else {
      } 
      sprintf(name,"%s ",nl->name);
      strcat(msg,name);
      nlobjs_ptr = nlobjs_ptr->next;
   }
   if (iflab) {
      sprintf(lab,"plnl %s",msg) ;
   }
   for (iblk = 0; iblk < nblk; iblk++) {
      node = ProblemArray_ptr("NLPLOT_node", domains[iblk].hash);
      for (i = 0; i < domains[iblk].nnalls; i++) {
         domains[iblk].node[i] = node[i];
      }
   }
   ProblemArray_free("NLPLOT_node");
}
