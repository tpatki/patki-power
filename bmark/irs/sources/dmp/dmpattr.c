#include "irs.h"
#include "irsdmp.h"
#include "irsrgst.h"
#include "ProblemArray.h"
#include "Rgst.h"

#ifdef SILO
void dmpattr_set( void ) {
   RGST_AttributeElem_t *dmpvars;
   RGST_AttributeElem_t *dmpvars_ptr;
   dmpvars = rgst_list_attr(A_OBJECT, "OnDump");
   dmpvars_ptr = dmpvars;
   while (dmpvars_ptr != NULL) {
      char *name          = ATTR_GET_OBJECT_NAME(dmpvars_ptr)
      ProblemArray_t *prb = ProblemArray_find(name,NULL);
      if (RGST_QUERY_OBJECT_ATTR(name, "DomainVar") == TRUE) {
         if ((RGST_QUERY_OBJECT_ATTR(name, "Zonal") == TRUE) ||
             (RGST_QUERY_OBJECT_ATTR(name, "Nodal") == TRUE)) {
            if (prb->type == R_DOUBLE) {
               rgst_add_attr(A_OBJECT, name, "dDomainDumpVar");
            } else if (prb->type == R_INT) {
               rgst_add_attr(A_OBJECT, name, "iDomainDumpVar");
            } 
            rgst_add_attr(A_OBJECT, name, "DomainDumpVar");
         } else {
            if (prb->type == R_DOUBLE) {
               rgst_add_attr(A_OBJECT, name, "dDumpVar");
            } else if (prb->type == R_INT) {
               rgst_add_attr(A_OBJECT, name, "iDumpVar");
            } 
            rgst_add_attr(A_OBJECT, name, "DumpVar");
         } 
      } else {
         if (prb->type == R_DOUBLE) {
            rgst_add_attr(A_OBJECT, name, "dGlobalDumpVar");
         } else if (prb->type == R_INT) {
            rgst_add_attr(A_OBJECT, name, "iGlobalDumpVar");
         } 
         rgst_add_attr(A_OBJECT, name, "GlobalDumpVar");
      } 
      dmpvars_ptr = dmpvars_ptr->next;
   }
}
void dmpattr_unset( void ) {
   rgst_del_attr_all("DumpVar");
   rgst_del_attr_all("iDumpVar");
   rgst_del_attr_all("dDumpVar");
   rgst_del_attr_all("DomainDumpVar");
   rgst_del_attr_all("iDomainDumpVar");
   rgst_del_attr_all("dDomainDumpVar");
   rgst_del_attr_all("dGlobalDumpVar");
   rgst_del_attr_all("iGlobalDumpVar");
   rgst_del_attr_all("GlobalDumpVar");
}
#endif
