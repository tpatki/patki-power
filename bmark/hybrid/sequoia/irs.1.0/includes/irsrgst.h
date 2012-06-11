#ifndef irsrgst_H
#define irsrgst_H

#include "Rgst.h"

/*******************************************************************************
* DEFINES
*******************************************************************************/

#define ATTR_GET_FIELD_TYPE(attr) attr->rgst_field->type;
#define ATTR_GET_FIELD_NAME(attr) attr->rgst_field->name;
#define ATTR_GET_OBJECT_NAME(attr) attr->rgst_obj->name;

#define ATTR_GET_FIELD_ADDR(ptr, ptr_type, field) \
    (((void **)(rgst_get_field_addr(ptr, ptr_type, field, NULL))))


#define RGST_GET_FIELD(ptr, ptr_type, field) \
    (*((void **)(rgst_get_field_addr(ptr, ptr_type, field, NULL))))

#define RGST_QUERY_OBJECT_ATTR(object, attr) \
    rgst_query_attr(A_OBJECT, object, attr, NULL)

#define RGST_QUERY_TYPE_ATTR(type, attr) \
    rgst_query_attr(A_TYPE, type, attr, NULL)

#define RGST_QUERY_FIELD_ATTR(type, field, attr) \
    rgst_query_attr(A_FIELD, type, field, attr, NULL)

#define RGST_ADD_OBJECT_ATTR(object, attr) \
    rgst_add_attr(A_OBJECT, object, attr)

#define RGST_ADD_TYPE_ATTR(type, attr) \
    rgst_add_attr(A_TYPE, type, attr)

#define RGST_ADD_FIELD_ATTR(type, field, attr) \
    rgst_add_attr(A_FIELD, type, field, attr)

#define RGST_ADD_MULT_OBJECT_ATTRS(objects, attrs) \
    rgst_add_mult_attrs(A_OBJECT, objects, attrs)

#define RGST_ADD_MULT_TYPE_ATTRS(types, attrs) \
    rgst_add_mult_attrs(A_TYPE, types, attrs)

#define RGST_ADD_MULT_FIELD_ATTRS(type, fields, attrs) \
    rgst_add_mult_attrs(A_FIELD, type, fields, attrs)

#define RGST_ADD_ATTR_TO_FIELDS(type, attr)	\
    rgst_add_attrs_to_fields(type, attr, NULL) 

#define RGST_DEL_ATTR_FROM_FIELDS(type, attr)   \
    rgst_del_attrs_from_fields(type, attr, NULL)

#define RGST_DEL_OBJECT_ATTR(object, attr) \
    rgst_del_attr(A_OBJECT, object, attr)

#define RGST_DEL_TYPE_ATTR(type, attr) \
    rgst_del_attr(A_TYPE, type, attr)

#define RGST_DEL_FIELD_ATTR(type, field, attr) \
    rgst_del_attr(A_FIELD, type, field, attr)

#define RGST_NUM_OBJECTS_WITH_ATTR(attr) \
    rgst_num_with_attr(A_OBJECT, attr)

#define RGST_LIST_OBJECTS_WITH_ATTR(attr) \
    rgst_list_attr(A_OBJECT, attr)

/*------------------------------------------------------------------------------
- This code was duplicated a lot so I made it a macro
- It gets the "zonal", "nodal", or "global",  attribute of a ProbArray_t variable.
- By the time the programmer calls this macro, he is sure that the variable
- exists as an zfpa, zipa, ipa, or fpa type var.  So if it doesn't have one of 
- the attributes, it is a logic error.
------------------------------------------------------------------------------*/
#define RGST_GET_PA_CENTERING(myname, myarraytype) \
{     \
  if      (rgst_query_attr(A_OBJECT, myname, "zonal",  NULL) == TRUE) \
    myarraytype = ZONAL_ARRAY; \
  else if (rgst_query_attr(A_OBJECT, myname, "nodal",  NULL) == TRUE) \
    myarraytype = NODAL_ARRAY; \
  else if (rgst_query_attr(A_OBJECT, myname, "global", NULL) == TRUE) \
    myarraytype = GLOBAL_ARRAY; \
  else  \
    ctlerror(me,logic_err); \
}

/*------------------------------------------------------------------------------
- This code was duplicated a lot so I made it a macro
- By the time this macro is called, the programmer knows that the name
- is a zipa var and just wants to get the pointer to it.  So, if this
- call fails, it is indeed a logic error.
------------------------------------------------------------------------------*/
#define RGST_GET_PA_PTR(myname, myptr) \
  if ((myptr = rgst_get_t(myname, "ProbArray_t")) == NULL) { ctlerror(me,logic_err); }

/*------------------------------------------------------------------------------
- DEFINES - used in registry routines 
------------------------------------------------------------------------------*/
#define RGST_TYPES_HT_NAME      	"rgst_types"
#define RGST_OBJS_HT_NAME       	"rgst_objs"
#define RGST_Field_t_NDX_HT_NAME	"rgst_field_ndx"
#define RGST_Attribute_t_STR      	"RGST_Attribute_t"
#define NUM_TYPES_SILO_KNOWS_OF 	6
#define STR_DELIMITER			"~"

/*******************************************************************************
* PROTOTYPES
*******************************************************************************/
#ifdef SILO
extern DBtoc * copy_toc(DBtoc *in_toc);
extern DBtoc * free_toc(DBtoc *toc);
#endif

extern GENERIC_ENUM_TYPEDEF rgst_conv_str_to_enum_type(char *enum_typedef_name, char *enum_type_str);
extern RGST_AttributeElem_t * rgst_list_attr(ATTR_Assoc_t assoc, char *attr_name);
extern RGST_AttributeElem_t * rgst_list_attr_and(ATTR_Assoc_t assoc, char *attr_name, ...);
extern RGST_Attribute_t * rgst_get_attr_type(char *attr_name);
extern RGST_Datatype_t rgst_get_object_datatype(char *name);
extern RGST_Object_t * rgst_get_RGST_Object_t(char *name);
extern RGST_StructTypeDef_t * rgst_get_RGST_StructTypeDef_t(char *name);
extern char * * rgst_list_objs_by_type(int *num_objs, char *type);
extern char * * rgst_list_vars_with_attr(char *attr_name, int *num_vars);
extern int * rgst_get_field_array_sizes(unsigned char *sptr, RGST_StructTypeDef_t *sd, RGST_Field_t *fd);
extern int hash_tbl_create_n_rgst(HashTable_t * *htp, int size, char *name);
extern int hash_tbl_rgst(HashTable_t * *htp, char *name);
extern int printattr(void);
extern int printattrlist(void);
extern int printhash(void);
extern int printrgst(void);
extern int rgst_add(char *name, char *type, void *ptr, char *array_size_var);
extern int rgst_add_attr(ATTR_Assoc_t assoc, ...);
extern int rgst_add_attrs(ATTR_Assoc_t assoc, ...);
extern int rgst_add_attrs_to_fields(char *type, ...);
extern int rgst_add_ctype_td_defn(RGST_CTypeDef_t in_cd);
extern int rgst_add_enum_td_defn(RGST_EnumTypeDef_t in_ed);
extern int rgst_add_mult_attrs(ATTR_Assoc_t assoc, ...);
extern int rgst_add_struct_td_defn(RGST_Datatype_t datatype, char *name, RGST_Field_t *fields, int num_fields, size_t struct_size);
extern int rgst_check_attr_name(char *attr_name, char *obj_name);
extern int rgst_check_for_obj(char *name);
extern int rgst_check_for_td_defn(char *name);
extern int rgst_check_ndxs(long nelms, long lo_ndx, long hi_ndx, long *ret_lo_ndx, long *ret_hi_ndx);
extern int rgst_cleanup(void);
extern int rgst_conv_enum_type_to_str(char *enum_typedef_name, GENERIC_ENUM_TYPEDEF enum_type, char *enum_type_str);
extern int rgst_del(char *name);
extern int rgst_del_attr(ATTR_Assoc_t assoc, ...);
extern int rgst_del_attrs_from_fields(char *type, ...);
extern int rgst_extract_array_ndxs(char *str, long *lo_ndx, long *hi_ndx);
extern int rgst_get_ds_field_ndx(RGST_StructTypeDef_t *sd, char *fld_name);
extern int rgst_get_nelms_in_field(unsigned char *sp, RGST_StructTypeDef_t *sd, RGST_Field_t *fd, long *ret_dim_nelms, long *ret_ptr_nelms, long *ret_nelms);
extern int rgst_get_nelms_in_rgst_obj(RGST_Object_t *ro, long *ret_dim_nelms, long *ret_ptr_nelms, long *ret_nelms);
extern int rgst_init(void);
extern int rgst_init_struct(char *type, void *ptr);
extern int rgst_num_with_attr(ATTR_Assoc_t assoc, char *attr_name);
extern int rgst_obj_is_dim_array(RGST_Object_t *ro);
extern int rgst_obj_is_ptr_array(RGST_Object_t *ro);
extern int rgst_print(char *name, long lo_ndx, long hi_ndx);
extern int rgst_print_addr(long addr, char *type);
extern int rgst_print_addr_member(void *sp, char *usertype, char *str, char *in_label);
extern int rgst_print_ds_member(char *str);
extern int rgst_print_obj(RGST_Object_t *rgst_obj, long dim_nelms, long ptr_nelms, long nelms, long lo_ndx, long hi_ndx);
extern int rgst_print_type(char *name);
extern int rgst_query_attr(ATTR_Assoc_t assoc, ...);

extern int rgst_split_type_n_fld(char *type_n_fld, char *type, char *field);

#ifdef SILO
extern int rgst_read_field(DBfile *idbid, char *field);
extern int rgst_write_linked_list(DBfile *idbid, char *dir_name, char *struct_name, void *ll);
extern int rgst_write_struct(DBfile *idbid, char *struct_name, void *sp, char *field_name);
extern int rgst_write_struct_array(DBfile *idbid, char *dir_name, char *struct_name, void * *spp, int spp_num);
extern int rgst_write_struct_in_dir(DBfile *idbid, char *dir_name, char *struct_name, void *sp, char *field_name);
extern void * * rgst_read_struct_array(DBfile *idbid, char *dir_name, char *struct_name, int *num_structs);
extern void * rgst_read_linked_list(DBfile *idbid, char *dir_name, char *struct_name);
extern void * rgst_read_struct(DBfile *idbid, char *struct_name, void *in_sp, char *field_name);
extern void * rgst_read_struct_in_dir(DBfile *idbid, char *dir_name, char *struct_name, void *in_sp, char *field_name);
#endif


extern long rgst_get_field_array_size(unsigned char *sptr, RGST_StructTypeDef_t *sd, RGST_Field_t *fd);
extern long rgst_get_long(char *name);
extern long rgst_get_object_len(char *name);
extern long rgst_get_ro_len(RGST_Object_t *ro);
extern size_t rgst_get_datatype_size(RGST_Datatype_t type, char *struct_name);
extern unsigned char * rgst_get_field_array_elm_ptr(unsigned char *fp, RGST_Field_t *fd, long dim_nelms, long ptr_nelms, long ndx);
extern unsigned char * rgst_get_struct_array_elm_ptr(RGST_Object_t *ro, RGST_StructTypeDef_t *sd, long dim_nelms, long ptr_nelms, long ndx);
extern void * rgst_alloc(char *name, char *type);
extern void * rgst_construct(RGST_Datatype_t type, char *struct_name, int num);
extern void * rgst_copy(char *name);
extern void * rgst_get(char *name);
extern void * rgst_get_field_addr(void *obj_ptr, char *type_name, char *fld_name, RGST_Field_t * *fd);
extern void * rgst_get_t(char *name, char *type);
extern void * rgst_get_td_defn(char *name, RGST_Datatype_t in_dt, RGST_Datatype_t *out_dt);
extern void get_words_at_prompt(char *str, int str_len);
extern void hash_print_obj(HashElm_t *ptr);
extern void hash_print_structs_of_type(HashTable_t *ht, char *type);
extern void rgst_create_typedef_name_str(RGST_Datatype_t type, char *type_name, int nptrs, int ndims, int *dims, char *buff);
extern void rgst_del_attr_all(char *attr_name);
extern void rgst_get_dims_of_type(char *type_str, int *nptrs, int *ndims, int *dims);
extern void rgst_print_0_ptr_array(RGST_Datatype_t dt, char *dt_name, void *ptr, long nelms, long lo_ndx, long hi_ndx);
extern void rgst_print_1_ptr_array(RGST_Datatype_t dt, char *dt_name, void *ptr, long dim_nelms, long ptr_nelms, long lo_ndx, long hi_ndx);
extern void rgst_print_2_ptr_array(RGST_Datatype_t dt, char *dt_name, void * * *ptr, long nelms);
extern void rgst_print_ctype_td_defn(RGST_CTypeDef_t *cd);
extern void rgst_print_field(unsigned char *sptr, RGST_StructTypeDef_t *sd, unsigned char *ptr, RGST_Field_t *fd, long lo_ndx, long hi_ndx);
extern void rgst_print_ptrs(void * *ptrs, long nelms);
extern void rgst_print_struct(unsigned char *sptr, RGST_StructTypeDef_t *sd);
extern void rgst_print_struct_td_defn(RGST_StructTypeDef_t *sd);
extern void rgst_print_structs(RGST_Object_t *ro, long dim_nelms, long ptr_nelms, long lo_ndx, long hi_ndx);
extern void rgst_verify_struct_td_defn(char *name, RGST_StructTypeDef_t *sd, int struct_size);
extern void rgst_add_h_file_types(void);

#endif

/*******************************************************************************
* GLOBALS
*******************************************************************************/
extern char          	*rgst_datatype_strs[NUM_RGST_Datatype_t];
extern size_t         	rgst_datatype_sizes[R_VOID];
extern HashTable_t 	*rgst_types_hash_tbl;
extern HashTable_t 	*rgst_objs_hash_tbl;
extern HashTable_t 	*rgst_field_ndx_hash_tbl;
extern RGST_Datatype_t  rgst_types_silo_knows_of[NUM_TYPES_SILO_KNOWS_OF];

#ifdef SILO
extern DBdatatype     	rgst_silo_types[NUM_TYPES_SILO_KNOWS_OF];
#endif

/*******************************************************************************
* END OF FILE
*******************************************************************************/
