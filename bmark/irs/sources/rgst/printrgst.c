#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include "irs.h"
#include "irs.h"
#include "irsctl.h"		
#include "irsdefs.h"
#include "irsrgst.h"
#include "Rgst.h"
#ifndef _POSIX_SOURCE
#define _POSIX_SOURCE 1
#endif
int printrgst(void)
{
  char *me = "printrgst";
  char str[STRLEN], tmpstr[STRLEN], msg[256], errmsg[256], *nextword;
  char *empty_type_tbl_msg = "\tNo types are currently in the registry\n";
  char *empty_obj_tbl_msg  = "\tNo objects are currently in the registry\n";
  int  i, err, address, hex_address, dec_address;
  long addr, lo_ndx, hi_ndx;
  memset(str,'\0',STRLEN);   
  while (ctlflag != iflf) {
    geta(tmpstr);
    if (strlen(str) > 0) {
      if (  (strcmp(tmpstr,"(") == 0)		
         || (strcmp(tmpstr,")") == 0) 		
         || (strcmp(tmpstr,"[") == 0) 
         || (strcmp(tmpstr,"]") == 0) 
	 || (str[strlen(str)-1] == '(')
	 || (str[strlen(str)-1] == ')')
	 || (str[strlen(str)-1] == '[')
	 || (str[strlen(str)-1] == ']') ) {
      }
      else {					
        strcat(str," ");			
      }	 
    }
    strcat(str,tmpstr);			
  }
  if (strcmp(str,"") == 0 || strcmp(str,"help") == 0) {
    sprintf(msg,"\n\t'printrgst' prints types and objects in the registry\n\t"
                "\n\tUsage:\n\t"
                "\n\tpr objs   to list all objects"
                "\n\tpr types  to list all types"
                "\n\tpr xyz    to print type or object 'xyz'");
    ctlnotice(me,msg);
    return(0);
  }
  else if (strcmp(str,"objs") == 0) {
    if (get_num_elms_in_hashtable(rgst_objs_hash_tbl) == 0) {
      printf("%s",empty_obj_tbl_msg);
    }
    else { 
      hash_cond_print_by_type(rgst_objs_hash_tbl, "Registry Objects");
    }
    return(0);
  }
  else if (strcmp(str,"types") == 0) {
    if (get_num_elms_in_hashtable(rgst_types_hash_tbl) == 0) {
      printf("%s",empty_type_tbl_msg);
    }
    else {
      hash_cond_print_by_type(rgst_types_hash_tbl, "Registry Types");
    }
    return(0);
  }
  else if (strcmp(str,"unsigned") == 0) {
    strcpy(msg,str);
    geta(str);
    strcat(msg," ");
    strcat(msg,str);
  }
  else if (isdigit(str[0])) {
    strcpy(msg,str);
    address     = TRUE;
    hex_address = FALSE;
    dec_address = FALSE;
    if (strlen(str) > 6) {
      if (str[1] == 'x')  hex_address = TRUE;
      else                dec_address = TRUE;
      nextword = NULL;
      if (hex_address == TRUE) {
	for (i=2; i<strlen(str); i++) {
          if (str[i] == ' ') {
            nextword = &str[i+1];  
            break;    
          }  
          else { 
            if (!isxdigit(str[i])) {
              address = FALSE;
	      break;
            }
          }
        }
      }
      else {
        for (i=1; i<strlen(str); i++) {
          if (str[i] == ' ') { 
            nextword = &str[i+1]; 
	    break;  
	  }
	  else { 
            if (!isdigit(str[i])) {
              address = FALSE;       
	      break; 
            }
          }
        }
      }
      if (address == TRUE) {
        if (hex_address == TRUE) addr = strtol(str, NULL, 16);
        else                     addr = strtol(str, NULL, 10);
        if ((addr == LONG_MIN) || (addr == LONG_MAX)) {
          sprintf(msg,"'%s' is not a valid decimal or hexadecimal address",str);
          ctlnotice(me,msg);
          return(-1);
        }
	if ((nextword == NULL) || (nextword[0] == '\0')) {
          sprintf(msg,"No type specified after address '%s'",str);
          ctlnotice(me,msg);
          return(-1);
        }
        rgst_print_addr(addr, nextword);
        return(0);
      }
    }
  }
  else {
    strcpy(msg,str);
  }
  if (rgst_types_hash_tbl != NULL) {
    if (hash_lookup_elm(msg, rgst_types_hash_tbl) != NULL) {
      err = rgst_print_type(msg);
      return(err);
    }
  }
  if (rgst_objs_hash_tbl != NULL) {
    if (hash_lookup_elm(msg, rgst_objs_hash_tbl) != NULL) {
      err = rgst_print(msg, -1, -1);
      return(err);
    }
  }
  if (strchr(msg,'.') != NULL) {
    err = rgst_print_ds_member(msg);
    return(err);
  }
  if ((strchr(msg,'[') != NULL) || (strchr(msg,'(') != NULL) ){
    if (rgst_extract_array_ndxs(&msg[0], &lo_ndx, &hi_ndx) != 0) return(-1);
    err = rgst_print(msg, lo_ndx, hi_ndx);
    return(err);
  }
  if (  (get_num_elms_in_hashtable(rgst_types_hash_tbl) == 0)
     && (get_num_elms_in_hashtable(rgst_objs_hash_tbl)  == 0)) {
    ctlnotice(me,"\tNo types or objects are currently in the registry\n");
    return(-1);
  }
  sprintf(errmsg,"\n\tType or object '%s' not found in the registry\n",msg);
  ctlnotice(me,errmsg);
  return(-1);
}
