#include "irs.h"
#include "irsrgst.h"
#include "irsctl.h"
#include "UserList.h"
#include "Hash.h"
#include "Rgst.h"
int UserList_input( void ) {
   char *me = "UserList_input";
   char msg[MAXLINE];
   char listname[MAXWORD];
   char op[MAXWORD];
   int error;
   geta(listname);
   geta(op);
   if (strcmp(op,"=")) {
     sprintf(msg,"Expecting equal sign after list %s",listname);
     ctlwarning(me,msg);
   }
   error = UserList_parse(listname);
   return(error);
}
int UserList_parse( char *listname ) {
   char *me = "UserList_parse";
   char op[MAXWORD];
   int gotone;
   int listop;
   int count;
   int paren;
   UserList_t *ul = NULL;
   gotone = 1;
   count  = 0;
   listop = 0;
   paren = 0;
   while (gotone) {
      peekc2(op);
      if (!strcmp(op,"(")) {
         geta(op);
         count++;
         paren++;
         while (strcmp(op,")")) {
            geta(op);
            if ((ul = UserList_find(op)) != NULL) {
               UserList_t *ul_ptr = ul;
               while (ul_ptr != NULL) {
                  if (listop == -1) {
                     UserList_remove(ul_ptr->name,"Current");
                  } else {
                     UserList_add(ul_ptr->name,"Current");
                  } 
                  ul_ptr = ul_ptr->next;
               }
            }  else if (strcmp(op,")")) {
               if (listop == -1) {
                  UserList_remove(op,"Current");
               } else {
                  UserList_add(op,"Current");
               } 
            } 
            if (!strcmp(op,")")) paren--;
            listop = 0;
         }
      } else if ((ul = UserList_find(op)) != NULL) {
         UserList_t *ul_ptr = ul;
         geta(op);
         count++;
         while (ul_ptr != NULL) {
            if (listop == -1) {
               UserList_remove(ul_ptr->name,"Current");
            } else {
               UserList_add(ul_ptr->name,"Current");
            } 
            ul_ptr = ul_ptr->next;
         }
         listop = 0;
      } else if (iplusmin != 0) {
         listop = iplusmin;
         geta(op);
      } else {
        gotone = 0;
      } 
      if ((iplusmin == 0) && (paren == 0)) gotone = 0;
   }
   if (count == 0) return(1);
   UserList_del(listname);
   ul = UserList_find("Current");
   while (ul != NULL) {
      UserList_add(ul->name,listname);
      ul = ul->next;
   }
   UserList_del("Current");
   return(0);
}
void UserList_add(char *name, char *attr) {
   char lattr[MAXLINE];
   char lname[MAXLINE];
   UserList_t *ul;
   sprintf(lname,"UL_%s",name);
   sprintf(lattr,"UserList_%s",attr);
   if (!rgst_check_for_obj(lname)) {
     ul = MALLOT(UserList_t,1);
     strcpy(ul->name,name);
     ul->next = NULL;
     rgst_add(lname,"UserList_t",ul,NULL);
     hash_add(lname,"UserList_t",ul,gv_hash_tbl);
   } 
   RGST_ADD_OBJECT_ATTR(lname,lattr);
   RGST_ADD_OBJECT_ATTR(lname,"AllUserLists");
}
UserList_t *UserList_find(char *attr) {
   char lattr[MAXLINE];
   RGST_AttributeElem_t *ulattr;   
   RGST_AttributeElem_t *ulattr_ptr;   
   UserList_t *ul_top   = NULL;
   UserList_t *ul       = NULL;
   sprintf(lattr,"UserList_%s",attr);
   ulattr = rgst_list_attr(A_OBJECT,lattr);
   ulattr_ptr = ulattr;
   while (ulattr_ptr != NULL) {
      char *lname = ATTR_GET_OBJECT_NAME(ulattr_ptr) 
      if (ul_top == NULL) {
         ul_top   = rgst_get_t(lname,"UserList_t");
         ul       = ul_top;
         ul->next = NULL;
      } else {
         ul->next = rgst_get_t(lname,"UserList_t");
         ul       = ul->next;
         ul->next = NULL; 
      } 
      ulattr_ptr = ulattr_ptr->next;
   }
   return(ul_top);
}
void UserList_del(char *attr) {
   char lattr[MAXLINE];
   sprintf(lattr,"UserList_%s",attr);
   rgst_del_attr_all(lattr);
}
void UserList_remove(char *name, char *attr) {
   char lattr[MAXLINE];
   char lname[MAXLINE];
   sprintf(lattr,"UserList_%s",attr);
   sprintf(lname,"UL_%s",name);
   if (rgst_check_for_obj(lname)) {
      rgst_del_attr(A_OBJECT, lname, lattr);
   }
}
void UserList_free( void ) {
   char lattr[MAXLINE];
   RGST_AttributeElem_t *ulattr;   
   RGST_AttributeElem_t *ulattr_ptr;   
   UserList_t *ul_top   = NULL;
   UserList_t *ul       = NULL;
   ulattr = rgst_list_attr(A_OBJECT,"AllUserLists");
   ulattr_ptr = ulattr;
   while (ulattr_ptr != NULL) {
      char *lname = ATTR_GET_OBJECT_NAME(ulattr_ptr) 
      ulattr_ptr = ulattr_ptr->next;
      ul = rgst_get_t(lname,"UserList_t");
      hash_del2(lname, "UserList_t", gv_hash_tbl);
      rgst_del(lname);
      FREEMEM(ul);
   }
}
int UserList_print( void ) {
   char *me = "UserList_print";
   char msg[MAXLINE];
   char op[MAXLINE];
   UserList_t *ul;
   int i;
   int len;
   int len0;
   geta(op);
   ul = UserList_find(op);
   if (ul == NULL) {
      sprintf(msg,"List %s cannot be found.",op);
      ctlwarning(me,msg);
      return(0);
   } 
   sprintf(msg,"%s = ",op);
   ctlmsg1(msg);
   len0 = strlen(msg) + 1;
   len  = len0;
   while (ul != NULL) {
      len += (strlen(ul->name) + 1);
      if (len >= 80) {
         len = len0;
         ctlmsg1("\n");
         for (i = 0; i < len0; i++) ctlmsg1(" ");
      }
      sprintf(msg,"%s ",ul->name);
      ctlmsg1(msg);
      ul = ul->next;
   }
   ctlmsg1("\n");
   return(0);
}

#ifdef SILO
void UserList_wtsilo(DBfile *idbid) {
   char dirname[MAXLINE];
   int error = 0;
   int i;
   int count;
   int dims[1];
   RGST_AttributeElem_t *ulattr;   
   RGST_AttributeElem_t *ulattr_ptr;   
   ulattr = rgst_list_attr(A_OBJECT,"AllUserLists");
   ulattr_ptr = ulattr;
   if (ulattr == NULL) return;
   error += DBMkDir(idbid,"/Global/UserList");
   error += DBSetDir(idbid,"/Global/UserList");
   count = 0;
   while (ulattr_ptr != NULL) {
      char *name = ATTR_GET_OBJECT_NAME(ulattr_ptr) 
      RGST_Object_t *ro = rgst_get_RGST_Object_t(name);
      sprintf(dirname,"Object_%i",count);
      error += DBMkDir(idbid,dirname);
      error += DBSetDir(idbid,dirname);
      dims[0] = strlen(name) + 1;
      error += DBWrite(idbid, "Name", name,dims,1,DB_CHAR);
      for (i = 0; i < ro->attributes->num_attrs; i++) {
          char *aname = ro->attributes->attrs[i]->attr_name;
	  dims[0] = strlen(aname) + 1;
          sprintf(dirname,"Attribute_%i",i);
	  error += DBWrite(idbid, dirname, aname, dims, 1, DB_CHAR);
      }
      dims[0] = 1;
      error += DBWrite(idbid, "NumAttributes", &i, dims, 1, DB_INT);
      error += DBSetDir(idbid,"../");
      count++;
      ulattr_ptr = ulattr_ptr->next;
   }
   dims[0] = 1;
   error += DBWrite(idbid, "NumObjects", &count, dims, 1, DB_INT);
   if (error != 0) {
      ctlwarning("UserList_wtsilo","Error occured while writing UserLists");
   }
}
#endif

#ifdef SILO
void UserList_rdsilo(DBfile *idbid) {
   char dirname[MAXLINE];
   char name[MAXLINE];
   char attr[MAXLINE];
   int error;
   int i,j;
   int numobj, numattr;
   DBShowErrors(DB_NONE, NULL);
   error = DBSetDir(idbid,"/Global/UserList");
   DBShowErrors(DB_TOP, NULL);
   if (error != 0) return;
   error = 0;
   error += DBReadVar(idbid, "NumObjects", &numobj);
   for (i = 0; i < numobj; i++) {
      char *lname;
      char *lattr;
      sprintf(dirname,"Object_%i",i);
      error += DBSetDir(idbid,dirname);
      error += DBReadVar(idbid, "Name", name);
      lname = name + strlen("UL_");
      error += DBReadVar(idbid, "NumAttributes", &numattr);
      for (j = 0; j < numattr; j++) {
          sprintf(dirname,"Attribute_%i",j);
	  error += DBReadVar(idbid, dirname, attr);
          lattr = attr + strlen("UserList_");
	  UserList_add(lname,lattr);
      }
      error += DBSetDir(idbid,"../");
   }
   if (error != 0) {
      ctlwarning("UserList_rdsilo","Error occured while reading UserLists");
   }
}
#endif
