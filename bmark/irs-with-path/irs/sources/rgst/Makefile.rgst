
################################################################################
#
# Makefile for irs library rgst
#

all:
	@ echo " "
	@ echo "Error:"
	@ echo "This Makefile must be called by the driving Makefile."
	@ echo " "

################################################################################

# Must use the bourne shell
#---------------------------
SHELL = /bin/sh

# Harmless suffix rule:
#----------------------
.SUFFIXES : .U

# library relative path name
#----------------------------
B = ../$(LIB_DIR)/librgst.a
BI = ../$(LIB_DIR)/librgst_inst.a

# Relative path to the directory of sources for the debugger
#-----------------------------------------------------------
DB  = ../../debug

# Relative path to the instrumented source directory from the source directory
#-----------------------------------------------------------------------------
PREDIR = ../../mccabe/pre
INSTDIR = ../../mccabe/inst

# Relative path to the instrumented source directory from the debug directory
#-----------------------------------------------------------------------------
INSTDIR_D = ../mccabe/inst

# Relative path to the source directory from the debug directory
#----------------------------------------------------------------
SRCDIR = ../sources/rgst

# Relative path to the output file for lint
#------------------------------------------
# LO = ../../build/lint.out

# library objects list
#---------------------

librgst:$(B)(build_proc_name.o) $(B)(copy_toc.o) $(B)(domain_hash_tbl_rgst.o)     \
	  $(B)(free_toc.o) $(B)(get_words_at_prompt.o) $(B)(hash_print_obj.o)     \
	  $(B)(hash_print_structs_of_type.o) $(B)(hash_tbl_create_n_rgst.o)       \
	  $(B)(hash_tbl_rgst.o) $(B)(printattr.o) $(B)(printattrlist.o)           \
	  $(B)(printhash.o) $(B)(printrgst.o) $(B)(rgst_add.o)                    \
	  $(B)(rgst_add_attr.o) $(B)(rgst_add_ctype_td_defn.o)                    \
	  $(B)(rgst_add_enum_td_defn.o) $(B)(rgst_add_struct_td_defn.o)           \
	  $(B)(rgst_alloc.o) $(B)(rgst_check_attr_name.o)                         \
	  $(B)(rgst_check_for_obj.o) $(B)(rgst_check_for_td_defn.o)               \
	  $(B)(rgst_check_ndxs.o) $(B)(rgst_cleanup.o) $(B)(rgst_construct.o)     \
	  $(B)(rgst_conv_enum_type_to_str.o) $(B)(rgst_copy.o)                    \
	  $(B)(rgst_copy_attr_elm_list.o) $(B)(rgst_create_RGST_ATTR_ELM_TYPE.o)  \
	  $(B)(rgst_create_typedef_name_str.o) $(B)(rgst_del.o)                   \
	  $(B)(rgst_del_attr.o) $(B)(rgst_extract_array_ndxs.o)                   \
	  $(B)(rgst_free_RGST_ATTR_ELM_TYPE.o) $(B)(rgst_free_RGST_ATTR_TYPE.o)   \
	  $(B)(rgst_free_attr_elm_list.o) $(B)(rgst_get.o)                        \
	  $(B)(rgst_get_RGST_OBJECT.o) $(B)(rgst_get_RGST_STRUCT_TD_DEFN.o)       \
	  $(B)(rgst_get_attr_type.o) $(B)(rgst_get_datatype_size.o)               \
	  $(B)(rgst_get_dims_of_type.o) $(B)(rgst_get_ds_field_ndx.o)             \
	  $(B)(rgst_get_field_addr.o) $(B)(rgst_get_field_array_elm_ptr.o)        \
	  $(B)(rgst_get_field_array_size.o) $(B)(rgst_get_field_array_sizes.o)    \
	  $(B)(rgst_get_long.o) $(B)(rgst_get_nelms_in_field.o)                   \
	  $(B)(rgst_get_nelms_in_rgst_obj.o) $(B)(rgst_get_object_datatype.o)     \
	  $(B)(rgst_get_object_len.o) $(B)(rgst_get_struct_array_elm_ptr.o)       \
	  $(B)(rgst_get_t.o) $(B)(rgst_get_td_defn.o) $(B)(rgst_init.o)           \
	  $(B)(rgst_init_struct.o) $(B)(rgst_list_attr.o)                         \
	  $(B)(rgst_list_attr_and.o) $(B)(rgst_list_objs_by_type.o)               \
	  $(B)(rgst_list_vars_with_attr.o) $(B)(rgst_num_with_attr.o)             \
	  $(B)(rgst_obj_is_dim_array.o) $(B)(rgst_obj_is_ptr_array.o)             \
	  $(B)(rgst_print.o) $(B)(rgst_print_0_ptr_array.o)                       \
	  $(B)(rgst_print_1_ptr_array.o) $(B)(rgst_print_2_ptr_array.o)           \
	  $(B)(rgst_print_addr.o) $(B)(rgst_print_addr_member.o)                  \
	  $(B)(rgst_print_ctype_td_defn.o) $(B)(rgst_print_ds_member.o)           \
	  $(B)(rgst_print_field.o) $(B)(rgst_print_function.o)                    \
	  $(B)(rgst_print_obj.o) $(B)(rgst_print_ptrs.o)                          \
	  $(B)(rgst_print_struct.o) $(B)(rgst_print_struct_td_defn.o)             \
	  $(B)(rgst_print_structs.o) $(B)(rgst_print_type.o)                      \
	  $(B)(rgst_query_attr.o) $(B)(rgst_read_field.o)                         \
	  $(B)(rgst_read_struct.o) $(B)(rgst_read_struct_array.o)                 \
	  $(B)(rgst_split_type_n_fld.o) $(B)(rgst_verify_struct_td_defn.o)        \
	  $(B)(rgst_write_struct.o) $(B)(rgst_write_struct_array.o)
	  @if test -f object_file_flag; then  \
		(echo $$irs_ar ar $(B) *.o; \
		$$irs_ar $(B) *.o; \
		rm *.o object_file_flag); \
	  fi
	  @echo 'rgst library current'

# creation deps
#---------------
$(B)(build_proc_name.o):build_proc_name.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/build_proc_name.c $(DB)/build_proc_name.c 

$(B)(copy_toc.o):copy_toc.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/copy_toc.c $(DB)/copy_toc.c 

$(B)(domain_hash_tbl_rgst.o):domain_hash_tbl_rgst.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/domain_hash_tbl_rgst.c $(DB)/domain_hash_tbl_rgst.c 

$(B)(free_toc.o):free_toc.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/free_toc.c $(DB)/free_toc.c 

$(B)(get_words_at_prompt.o):get_words_at_prompt.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/get_words_at_prompt.c $(DB)/get_words_at_prompt.c 

$(B)(hash_print_obj.o):hash_print_obj.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/hash_print_obj.c $(DB)/hash_print_obj.c 

$(B)(hash_print_structs_of_type.o):hash_print_structs_of_type.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/hash_print_structs_of_type.c $(DB)/hash_print_structs_of_type.c 

$(B)(hash_tbl_create_n_rgst.o):hash_tbl_create_n_rgst.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/hash_tbl_create_n_rgst.c $(DB)/hash_tbl_create_n_rgst.c 

$(B)(hash_tbl_rgst.o):hash_tbl_rgst.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/hash_tbl_rgst.c $(DB)/hash_tbl_rgst.c 

$(B)(printattr.o):printattr.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/printattr.c $(DB)/printattr.c 

$(B)(printattrlist.o):printattrlist.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/printattrlist.c $(DB)/printattrlist.c 

$(B)(printhash.o):printhash.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/printhash.c $(DB)/printhash.c 

$(B)(printrgst.o):printrgst.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/printrgst.c $(DB)/printrgst.c 

$(B)(rgst_add.o):rgst_add.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/rgst_add.c $(DB)/rgst_add.c 

$(B)(rgst_add_attr.o):rgst_add_attr.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/rgst_add_attr.c $(DB)/rgst_add_attr.c 

$(B)(rgst_add_ctype_td_defn.o):rgst_add_ctype_td_defn.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/rgst_add_ctype_td_defn.c $(DB)/rgst_add_ctype_td_defn.c 

$(B)(rgst_add_enum_td_defn.o):rgst_add_enum_td_defn.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/rgst_add_enum_td_defn.c $(DB)/rgst_add_enum_td_defn.c 

$(B)(rgst_add_struct_td_defn.o):rgst_add_struct_td_defn.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/rgst_add_struct_td_defn.c $(DB)/rgst_add_struct_td_defn.c 

$(B)(rgst_alloc.o):rgst_alloc.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/rgst_alloc.c $(DB)/rgst_alloc.c 

$(B)(rgst_check_attr_name.o):rgst_check_attr_name.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/rgst_check_attr_name.c $(DB)/rgst_check_attr_name.c 

$(B)(rgst_check_for_obj.o):rgst_check_for_obj.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/rgst_check_for_obj.c $(DB)/rgst_check_for_obj.c 

$(B)(rgst_check_for_td_defn.o):rgst_check_for_td_defn.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/rgst_check_for_td_defn.c $(DB)/rgst_check_for_td_defn.c 

$(B)(rgst_check_ndxs.o):rgst_check_ndxs.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/rgst_check_ndxs.c $(DB)/rgst_check_ndxs.c 

$(B)(rgst_cleanup.o):rgst_cleanup.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/rgst_cleanup.c $(DB)/rgst_cleanup.c 

$(B)(rgst_construct.o):rgst_construct.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/rgst_construct.c $(DB)/rgst_construct.c 

$(B)(rgst_conv_enum_type_to_str.o):rgst_conv_enum_type_to_str.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/rgst_conv_enum_type_to_str.c $(DB)/rgst_conv_enum_type_to_str.c 

$(B)(rgst_copy.o):rgst_copy.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/rgst_copy.c $(DB)/rgst_copy.c 

$(B)(rgst_copy_attr_elm_list.o):rgst_copy_attr_elm_list.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/rgst_copy_attr_elm_list.c $(DB)/rgst_copy_attr_elm_list.c 

$(B)(rgst_create_RGST_ATTR_ELM_TYPE.o):rgst_create_RGST_ATTR_ELM_TYPE.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/rgst_create_RGST_ATTR_ELM_TYPE.c $(DB)/rgst_create_RGST_ATTR_ELM_TYPE.c 

$(B)(rgst_create_typedef_name_str.o):rgst_create_typedef_name_str.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/rgst_create_typedef_name_str.c $(DB)/rgst_create_typedef_name_str.c 

$(B)(rgst_del.o):rgst_del.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/rgst_del.c $(DB)/rgst_del.c 

$(B)(rgst_del_attr.o):rgst_del_attr.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/rgst_del_attr.c $(DB)/rgst_del_attr.c 

$(B)(rgst_extract_array_ndxs.o):rgst_extract_array_ndxs.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/rgst_extract_array_ndxs.c $(DB)/rgst_extract_array_ndxs.c 

$(B)(rgst_free_RGST_ATTR_ELM_TYPE.o):rgst_free_RGST_ATTR_ELM_TYPE.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/rgst_free_RGST_ATTR_ELM_TYPE.c $(DB)/rgst_free_RGST_ATTR_ELM_TYPE.c 

$(B)(rgst_free_RGST_ATTR_TYPE.o):rgst_free_RGST_ATTR_TYPE.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/rgst_free_RGST_ATTR_TYPE.c $(DB)/rgst_free_RGST_ATTR_TYPE.c 

$(B)(rgst_free_attr_elm_list.o):rgst_free_attr_elm_list.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/rgst_free_attr_elm_list.c $(DB)/rgst_free_attr_elm_list.c 

$(B)(rgst_get.o):rgst_get.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/rgst_get.c $(DB)/rgst_get.c 

$(B)(rgst_get_RGST_OBJECT.o):rgst_get_RGST_OBJECT.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/rgst_get_RGST_OBJECT.c $(DB)/rgst_get_RGST_OBJECT.c 

$(B)(rgst_get_RGST_STRUCT_TD_DEFN.o):rgst_get_RGST_STRUCT_TD_DEFN.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/rgst_get_RGST_STRUCT_TD_DEFN.c $(DB)/rgst_get_RGST_STRUCT_TD_DEFN.c 

$(B)(rgst_get_attr_type.o):rgst_get_attr_type.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/rgst_get_attr_type.c $(DB)/rgst_get_attr_type.c 

$(B)(rgst_get_datatype_size.o):rgst_get_datatype_size.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/rgst_get_datatype_size.c $(DB)/rgst_get_datatype_size.c 

$(B)(rgst_get_dims_of_type.o):rgst_get_dims_of_type.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/rgst_get_dims_of_type.c $(DB)/rgst_get_dims_of_type.c 

$(B)(rgst_get_ds_field_ndx.o):rgst_get_ds_field_ndx.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/rgst_get_ds_field_ndx.c $(DB)/rgst_get_ds_field_ndx.c 

$(B)(rgst_get_field_addr.o):rgst_get_field_addr.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/rgst_get_field_addr.c $(DB)/rgst_get_field_addr.c 

$(B)(rgst_get_field_array_elm_ptr.o):rgst_get_field_array_elm_ptr.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/rgst_get_field_array_elm_ptr.c $(DB)/rgst_get_field_array_elm_ptr.c 

$(B)(rgst_get_field_array_size.o):rgst_get_field_array_size.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/rgst_get_field_array_size.c $(DB)/rgst_get_field_array_size.c 

$(B)(rgst_get_field_array_sizes.o):rgst_get_field_array_sizes.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/rgst_get_field_array_sizes.c $(DB)/rgst_get_field_array_sizes.c 

$(B)(rgst_get_long.o):rgst_get_long.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/rgst_get_long.c $(DB)/rgst_get_long.c 

$(B)(rgst_get_nelms_in_field.o):rgst_get_nelms_in_field.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/rgst_get_nelms_in_field.c $(DB)/rgst_get_nelms_in_field.c 

$(B)(rgst_get_nelms_in_rgst_obj.o):rgst_get_nelms_in_rgst_obj.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/rgst_get_nelms_in_rgst_obj.c $(DB)/rgst_get_nelms_in_rgst_obj.c 

$(B)(rgst_get_object_datatype.o):rgst_get_object_datatype.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/rgst_get_object_datatype.c $(DB)/rgst_get_object_datatype.c 

$(B)(rgst_get_object_len.o):rgst_get_object_len.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/rgst_get_object_len.c $(DB)/rgst_get_object_len.c 

$(B)(rgst_get_struct_array_elm_ptr.o):rgst_get_struct_array_elm_ptr.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/rgst_get_struct_array_elm_ptr.c $(DB)/rgst_get_struct_array_elm_ptr.c 

$(B)(rgst_get_t.o):rgst_get_t.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/rgst_get_t.c $(DB)/rgst_get_t.c 

$(B)(rgst_get_td_defn.o):rgst_get_td_defn.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/rgst_get_td_defn.c $(DB)/rgst_get_td_defn.c 

$(B)(rgst_init.o):rgst_init.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/rgst_init.c $(DB)/rgst_init.c 

$(B)(rgst_init_struct.o):rgst_init_struct.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/rgst_init_struct.c $(DB)/rgst_init_struct.c 

$(B)(rgst_list_attr.o):rgst_list_attr.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/rgst_list_attr.c $(DB)/rgst_list_attr.c 

$(B)(rgst_list_attr_and.o):rgst_list_attr_and.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/rgst_list_attr_and.c $(DB)/rgst_list_attr_and.c 

$(B)(rgst_list_objs_by_type.o):rgst_list_objs_by_type.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/rgst_list_objs_by_type.c $(DB)/rgst_list_objs_by_type.c 

$(B)(rgst_list_vars_with_attr.o):rgst_list_vars_with_attr.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/rgst_list_vars_with_attr.c $(DB)/rgst_list_vars_with_attr.c 

$(B)(rgst_num_with_attr.o):rgst_num_with_attr.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/rgst_num_with_attr.c $(DB)/rgst_num_with_attr.c 

$(B)(rgst_obj_is_dim_array.o):rgst_obj_is_dim_array.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/rgst_obj_is_dim_array.c $(DB)/rgst_obj_is_dim_array.c 

$(B)(rgst_obj_is_ptr_array.o):rgst_obj_is_ptr_array.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/rgst_obj_is_ptr_array.c $(DB)/rgst_obj_is_ptr_array.c 

$(B)(rgst_print.o):rgst_print.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/rgst_print.c $(DB)/rgst_print.c 

$(B)(rgst_print_0_ptr_array.o):rgst_print_0_ptr_array.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/rgst_print_0_ptr_array.c $(DB)/rgst_print_0_ptr_array.c 

$(B)(rgst_print_1_ptr_array.o):rgst_print_1_ptr_array.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/rgst_print_1_ptr_array.c $(DB)/rgst_print_1_ptr_array.c 

$(B)(rgst_print_2_ptr_array.o):rgst_print_2_ptr_array.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/rgst_print_2_ptr_array.c $(DB)/rgst_print_2_ptr_array.c 

$(B)(rgst_print_addr.o):rgst_print_addr.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/rgst_print_addr.c $(DB)/rgst_print_addr.c 

$(B)(rgst_print_addr_member.o):rgst_print_addr_member.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/rgst_print_addr_member.c $(DB)/rgst_print_addr_member.c 

$(B)(rgst_print_ctype_td_defn.o):rgst_print_ctype_td_defn.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/rgst_print_ctype_td_defn.c $(DB)/rgst_print_ctype_td_defn.c 

$(B)(rgst_print_ds_member.o):rgst_print_ds_member.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/rgst_print_ds_member.c $(DB)/rgst_print_ds_member.c 

$(B)(rgst_print_field.o):rgst_print_field.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/rgst_print_field.c $(DB)/rgst_print_field.c 

$(B)(rgst_print_function.o):rgst_print_function.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/rgst_print_function.c $(DB)/rgst_print_function.c 

$(B)(rgst_print_obj.o):rgst_print_obj.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/rgst_print_obj.c $(DB)/rgst_print_obj.c 

$(B)(rgst_print_ptrs.o):rgst_print_ptrs.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/rgst_print_ptrs.c $(DB)/rgst_print_ptrs.c 

$(B)(rgst_print_struct.o):rgst_print_struct.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/rgst_print_struct.c $(DB)/rgst_print_struct.c 

$(B)(rgst_print_struct_td_defn.o):rgst_print_struct_td_defn.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/rgst_print_struct_td_defn.c $(DB)/rgst_print_struct_td_defn.c 

$(B)(rgst_print_structs.o):rgst_print_structs.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/rgst_print_structs.c $(DB)/rgst_print_structs.c 

$(B)(rgst_print_type.o):rgst_print_type.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/rgst_print_type.c $(DB)/rgst_print_type.c 

$(B)(rgst_query_attr.o):rgst_query_attr.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/rgst_query_attr.c $(DB)/rgst_query_attr.c 

$(B)(rgst_read_field.o):rgst_read_field.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/rgst_read_field.c $(DB)/rgst_read_field.c 

$(B)(rgst_read_struct.o):rgst_read_struct.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/rgst_read_struct.c $(DB)/rgst_read_struct.c 

$(B)(rgst_read_struct_array.o):rgst_read_struct_array.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/rgst_read_struct_array.c $(DB)/rgst_read_struct_array.c 

$(B)(rgst_split_type_n_fld.o):rgst_split_type_n_fld.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/rgst_split_type_n_fld.c $(DB)/rgst_split_type_n_fld.c 

$(B)(rgst_verify_struct_td_defn.o):rgst_verify_struct_td_defn.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/rgst_verify_struct_td_defn.c $(DB)/rgst_verify_struct_td_defn.c 

$(B)(rgst_write_struct.o):rgst_write_struct.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/rgst_write_struct.c $(DB)/rgst_write_struct.c 

$(B)(rgst_write_struct_array.o):rgst_write_struct_array.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/rgst_write_struct_array.c $(DB)/rgst_write_struct_array.c 

#---------------------
# lint pass one target 
#---------------------
lint:build_proc_name.ln copy_toc.ln domain_hash_tbl_rgst.ln free_toc.ln           \
	  get_words_at_prompt.ln hash_print_obj.ln hash_print_structs_of_type.ln  \
	  hash_tbl_create_n_rgst.ln hash_tbl_rgst.ln printattr.ln                 \
	  printattrlist.ln printhash.ln printrgst.ln rgst_add.ln rgst_add_attr.ln \
	  rgst_add_ctype_td_defn.ln rgst_add_enum_td_defn.ln                      \
	  rgst_add_struct_td_defn.ln rgst_alloc.ln rgst_check_attr_name.ln        \
	  rgst_check_for_obj.ln rgst_check_for_td_defn.ln rgst_check_ndxs.ln      \
	  rgst_cleanup.ln rgst_construct.ln rgst_conv_enum_type_to_str.ln         \
	  rgst_copy.ln rgst_copy_attr_elm_list.ln                                 \
	  rgst_create_RGST_ATTR_ELM_TYPE.ln rgst_create_typedef_name_str.ln       \
	  rgst_del.ln rgst_del_attr.ln rgst_extract_array_ndxs.ln                 \
	  rgst_free_RGST_ATTR_ELM_TYPE.ln rgst_free_RGST_ATTR_TYPE.ln             \
	  rgst_free_attr_elm_list.ln rgst_get.ln rgst_get_RGST_OBJECT.ln          \
	  rgst_get_RGST_STRUCT_TD_DEFN.ln rgst_get_attr_type.ln                   \
	  rgst_get_datatype_size.ln rgst_get_dims_of_type.ln                      \
	  rgst_get_ds_field_ndx.ln rgst_get_field_addr.ln                         \
	  rgst_get_field_array_elm_ptr.ln rgst_get_field_array_size.ln            \
	  rgst_get_field_array_sizes.ln rgst_get_long.ln                          \
	  rgst_get_nelms_in_field.ln rgst_get_nelms_in_rgst_obj.ln                \
	  rgst_get_object_datatype.ln rgst_get_object_len.ln                      \
	  rgst_get_struct_array_elm_ptr.ln rgst_get_t.ln rgst_get_td_defn.ln      \
	  rgst_init.ln rgst_init_struct.ln rgst_list_attr.ln                      \
	  rgst_list_attr_and.ln rgst_list_objs_by_type.ln                         \
	  rgst_list_vars_with_attr.ln rgst_num_with_attr.ln                       \
	  rgst_obj_is_dim_array.ln rgst_obj_is_ptr_array.ln rgst_print.ln         \
	  rgst_print_0_ptr_array.ln rgst_print_1_ptr_array.ln                     \
	  rgst_print_2_ptr_array.ln rgst_print_addr.ln rgst_print_addr_member.ln  \
	  rgst_print_ctype_td_defn.ln rgst_print_ds_member.ln rgst_print_field.ln \
	  rgst_print_function.ln rgst_print_obj.ln rgst_print_ptrs.ln             \
	  rgst_print_struct.ln rgst_print_struct_td_defn.ln rgst_print_structs.ln \
	  rgst_print_type.ln rgst_query_attr.ln rgst_read_field.ln                \
	  rgst_read_struct.ln rgst_read_struct_array.ln rgst_split_type_n_fld.ln  \
	  rgst_verify_struct_td_defn.ln rgst_write_struct.ln                      \
	  rgst_write_struct_array.ln

#------------------------------
# individual lint .ln file deps
#------------------------------
build_proc_name.ln:build_proc_name.c ../../includes/irs.h                         \
	  ../../includes/irsrgst.h ../../includes/Rgst.h                          \
	  ../../includes/Command.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON build_proc_name.c ***' >> $(LO)
	$$irs_lint build_proc_name.c 2>&1 | tee -a $(LO)

copy_toc.ln:copy_toc.c ../../includes/irs.h ../../includes/irsrgst.h              \
	  ../../includes/Rgst.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON copy_toc.c ***' >> $(LO)
	$$irs_lint copy_toc.c 2>&1 | tee -a $(LO)

domain_hash_tbl_rgst.ln:domain_hash_tbl_rgst.c ../../includes/irs.h               \
	  ../../includes/irsctl.h ../../includes/Hash.h ../../includes/Rgst.h     \
	  ../../includes/irsrgst.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON domain_hash_tbl_rgst.c ***' >> $(LO)
	$$irs_lint domain_hash_tbl_rgst.c 2>&1 | tee -a $(LO)

free_toc.ln:free_toc.c ../../includes/irs.h ../../includes/irsrgst.h              \
	  ../../includes/Rgst.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON free_toc.c ***' >> $(LO)
	$$irs_lint free_toc.c 2>&1 | tee -a $(LO)

get_words_at_prompt.ln:get_words_at_prompt.c ../../includes/irs.h                 \
	  ../../includes/irsctl.h ../../includes/irsrgst.h                        \
	  ../../includes/Rgst.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON get_words_at_prompt.c ***' >> $(LO)
	$$irs_lint get_words_at_prompt.c 2>&1 | tee -a $(LO)

hash_print_obj.ln:hash_print_obj.c ../../includes/irs.h ../../includes/irsrgst.h  \
	  ../../includes/FreqMesg.h ../../includes/Hash.h ../../includes/Rgst.h   \
	  ../../includes/TimePlot.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON hash_print_obj.c ***' >> $(LO)
	$$irs_lint hash_print_obj.c 2>&1 | tee -a $(LO)

hash_print_structs_of_type.ln:hash_print_structs_of_type.c ../../includes/irs.h   \
	  ../../includes/Hash.h ../../includes/irsrgst.h ../../includes/Rgst.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON hash_print_structs_of_type.c ***' >> $(LO)
	$$irs_lint hash_print_structs_of_type.c 2>&1 | tee -a $(LO)

hash_tbl_create_n_rgst.ln:hash_tbl_create_n_rgst.c ../../includes/irs.h           \
	  ../../includes/irsctl.h ../../includes/Hash.h ../../includes/irsrgst.h  \
	  ../../includes/Rgst.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON hash_tbl_create_n_rgst.c ***' >> $(LO)
	$$irs_lint hash_tbl_create_n_rgst.c 2>&1 | tee -a $(LO)

hash_tbl_rgst.ln:hash_tbl_rgst.c ../../includes/irs.h ../../includes/irsctl.h     \
	  ../../includes/Hash.h ../../includes/irsrgst.h ../../includes/Rgst.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON hash_tbl_rgst.c ***' >> $(LO)
	$$irs_lint hash_tbl_rgst.c 2>&1 | tee -a $(LO)

printattr.ln:printattr.c ../../includes/irs.h ../../includes/irsrgst.h            \
	  ../../includes/irsctl.h ../../includes/irsdefs.h ../../includes/Hash.h  \
	  ../../includes/Rgst.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON printattr.c ***' >> $(LO)
	$$irs_lint printattr.c 2>&1 | tee -a $(LO)

printattrlist.ln:printattrlist.c ../../includes/irs.h ../../includes/irsctl.h     \
	  ../../includes/irsdefs.h ../../includes/Hash.h ../../includes/irsrgst.h \
	  ../../includes/Rgst.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON printattrlist.c ***' >> $(LO)
	$$irs_lint printattrlist.c 2>&1 | tee -a $(LO)

printhash.ln:printhash.c ../../includes/irs.h ../../includes/irsrgst.h            \
	  ../../includes/irsrgst.h ../../includes/irsctl.h ../../includes/Hash.h  \
	  ../../includes/Hash.h ../../includes/Rgst.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON printhash.c ***' >> $(LO)
	$$irs_lint printhash.c 2>&1 | tee -a $(LO)

printrgst.ln:printrgst.c ../../includes/irs.h ../../includes/irs.h                \
	  ../../includes/irsctl.h ../../includes/irsdefs.h                        \
	  ../../includes/irsrgst.h ../../includes/Rgst.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON printrgst.c ***' >> $(LO)
	$$irs_lint printrgst.c 2>&1 | tee -a $(LO)

rgst_add.ln:rgst_add.c ../../includes/irs.h ../../includes/irs.h                  \
	  ../../includes/irsrgst.h ../../includes/Hash.h ../../includes/Rgst.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON rgst_add.c ***' >> $(LO)
	$$irs_lint rgst_add.c 2>&1 | tee -a $(LO)

rgst_add_attr.ln:rgst_add_attr.c ../../includes/irs.h ../../includes/irs.h        \
	  ../../includes/Hash.h ../../includes/Rgst.h ../../includes/irsrgst.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON rgst_add_attr.c ***' >> $(LO)
	$$irs_lint rgst_add_attr.c 2>&1 | tee -a $(LO)

rgst_add_ctype_td_defn.ln:rgst_add_ctype_td_defn.c ../../includes/irs.h           \
	  ../../includes/irs.h ../../includes/Hash.h ../../includes/Rgst.h        \
	  ../../includes/irsrgst.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON rgst_add_ctype_td_defn.c ***' >> $(LO)
	$$irs_lint rgst_add_ctype_td_defn.c 2>&1 | tee -a $(LO)

rgst_add_enum_td_defn.ln:rgst_add_enum_td_defn.c ../../includes/irs.h             \
	  ../../includes/irs.h ../../includes/Hash.h ../../includes/Rgst.h        \
	  ../../includes/irsrgst.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON rgst_add_enum_td_defn.c ***' >> $(LO)
	$$irs_lint rgst_add_enum_td_defn.c 2>&1 | tee -a $(LO)

rgst_add_struct_td_defn.ln:rgst_add_struct_td_defn.c ../../includes/irs.h         \
	  ../../includes/irs.h ../../includes/Hash.h ../../includes/Rgst.h        \
	  ../../includes/irsrgst.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON rgst_add_struct_td_defn.c ***' >> $(LO)
	$$irs_lint rgst_add_struct_td_defn.c 2>&1 | tee -a $(LO)

rgst_alloc.ln:rgst_alloc.c ../../includes/irs.h ../../includes/irs.h              \
	  ../../includes/Hash.h ../../includes/irsrgst.h ../../includes/Rgst.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON rgst_alloc.c ***' >> $(LO)
	$$irs_lint rgst_alloc.c 2>&1 | tee -a $(LO)

rgst_check_attr_name.ln:rgst_check_attr_name.c ../../includes/irs.h               \
	  ../../includes/irsrgst.h ../../includes/Rgst.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON rgst_check_attr_name.c ***' >> $(LO)
	$$irs_lint rgst_check_attr_name.c 2>&1 | tee -a $(LO)

rgst_check_for_obj.ln:rgst_check_for_obj.c ../../includes/irs.h                   \
	  ../../includes/irs.h ../../includes/Hash.h ../../includes/Rgst.h        \
	  ../../includes/irsrgst.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON rgst_check_for_obj.c ***' >> $(LO)
	$$irs_lint rgst_check_for_obj.c 2>&1 | tee -a $(LO)

rgst_check_for_td_defn.ln:rgst_check_for_td_defn.c ../../includes/irs.h           \
	  ../../includes/irs.h ../../includes/Hash.h ../../includes/Rgst.h        \
	  ../../includes/irsrgst.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON rgst_check_for_td_defn.c ***' >> $(LO)
	$$irs_lint rgst_check_for_td_defn.c 2>&1 | tee -a $(LO)

rgst_check_ndxs.ln:rgst_check_ndxs.c ../../includes/irs.h ../../includes/irs.h    \
	  ../../includes/Hash.h ../../includes/Rgst.h ../../includes/irsrgst.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON rgst_check_ndxs.c ***' >> $(LO)
	$$irs_lint rgst_check_ndxs.c 2>&1 | tee -a $(LO)

rgst_cleanup.ln:rgst_cleanup.c ../../includes/irs.h ../../includes/irs.h          \
	  ../../includes/Hash.h ../../includes/Rgst.h ../../includes/irsrgst.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON rgst_cleanup.c ***' >> $(LO)
	$$irs_lint rgst_cleanup.c 2>&1 | tee -a $(LO)

rgst_construct.ln:rgst_construct.c ../../includes/irs.h ../../includes/irs.h      \
	  ../../includes/irsrgst.h ../../includes/Hash.h ../../includes/Command.h \
	  ../../includes/Rgst.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON rgst_construct.c ***' >> $(LO)
	$$irs_lint rgst_construct.c 2>&1 | tee -a $(LO)

rgst_conv_enum_type_to_str.ln:rgst_conv_enum_type_to_str.c ../../includes/irs.h   \
	  ../../includes/irsrgst.h ../../includes/Rgst.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON rgst_conv_enum_type_to_str.c ***' >> $(LO)
	$$irs_lint rgst_conv_enum_type_to_str.c 2>&1 | tee -a $(LO)

rgst_copy.ln:rgst_copy.c ../../includes/irs.h ../../includes/irs.h                \
	  ../../includes/Hash.h ../../includes/Rgst.h ../../includes/irsrgst.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON rgst_copy.c ***' >> $(LO)
	$$irs_lint rgst_copy.c 2>&1 | tee -a $(LO)

rgst_copy_attr_elm_list.ln:rgst_copy_attr_elm_list.c ../../includes/irs.h         \
	  ../../includes/irs.h ../../includes/Hash.h ../../includes/Rgst.h        \
	  ../../includes/irsrgst.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON rgst_copy_attr_elm_list.c ***' >> $(LO)
	$$irs_lint rgst_copy_attr_elm_list.c 2>&1 | tee -a $(LO)

rgst_create_RGST_ATTR_ELM_TYPE.ln:rgst_create_RGST_ATTR_ELM_TYPE.c                \
	  ../../includes/irs.h ../../includes/irs.h ../../includes/irsrgst.h      \
	  ../../includes/Rgst.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON rgst_create_RGST_ATTR_ELM_TYPE.c ***' >> $(LO)
	$$irs_lint rgst_create_RGST_ATTR_ELM_TYPE.c 2>&1 | tee -a $(LO)

rgst_create_typedef_name_str.ln:rgst_create_typedef_name_str.c                    \
	  ../../includes/irs.h ../../includes/irs.h ../../includes/Hash.h         \
	  ../../includes/Rgst.h ../../includes/irsrgst.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON rgst_create_typedef_name_str.c ***' >> $(LO)
	$$irs_lint rgst_create_typedef_name_str.c 2>&1 | tee -a $(LO)

rgst_del.ln:rgst_del.c ../../includes/irs.h ../../includes/irs.h                  \
	  ../../includes/Hash.h ../../includes/Rgst.h ../../includes/irsrgst.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON rgst_del.c ***' >> $(LO)
	$$irs_lint rgst_del.c 2>&1 | tee -a $(LO)

rgst_del_attr.ln:rgst_del_attr.c ../../includes/irs.h ../../includes/irs.h        \
	  ../../includes/Hash.h ../../includes/Rgst.h ../../includes/irsrgst.h    \
	  ../../includes/irs.h ../../includes/irs.h ../../includes/Hash.h         \
	  ../../includes/irsrgst.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON rgst_del_attr.c ***' >> $(LO)
	$$irs_lint rgst_del_attr.c 2>&1 | tee -a $(LO)

rgst_extract_array_ndxs.ln:rgst_extract_array_ndxs.c ../../includes/irs.h         \
	  ../../includes/irs.h ../../includes/Hash.h ../../includes/Rgst.h        \
	  ../../includes/irsrgst.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON rgst_extract_array_ndxs.c ***' >> $(LO)
	$$irs_lint rgst_extract_array_ndxs.c 2>&1 | tee -a $(LO)

rgst_free_RGST_ATTR_ELM_TYPE.ln:rgst_free_RGST_ATTR_ELM_TYPE.c                    \
	  ../../includes/irs.h ../../includes/irs.h ../../includes/Hash.h         \
	  ../../includes/Rgst.h ../../includes/irsrgst.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON rgst_free_RGST_ATTR_ELM_TYPE.c ***' >> $(LO)
	$$irs_lint rgst_free_RGST_ATTR_ELM_TYPE.c 2>&1 | tee -a $(LO)

rgst_free_RGST_ATTR_TYPE.ln:rgst_free_RGST_ATTR_TYPE.c ../../includes/irs.h       \
	  ../../includes/irs.h ../../includes/Hash.h ../../includes/Rgst.h        \
	  ../../includes/irsrgst.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON rgst_free_RGST_ATTR_TYPE.c ***' >> $(LO)
	$$irs_lint rgst_free_RGST_ATTR_TYPE.c 2>&1 | tee -a $(LO)

rgst_free_attr_elm_list.ln:rgst_free_attr_elm_list.c ../../includes/irs.h         \
	  ../../includes/irs.h ../../includes/Hash.h ../../includes/Rgst.h        \
	  ../../includes/irsrgst.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON rgst_free_attr_elm_list.c ***' >> $(LO)
	$$irs_lint rgst_free_attr_elm_list.c 2>&1 | tee -a $(LO)

rgst_get.ln:rgst_get.c ../../includes/irs.h ../../includes/irs.h                  \
	  ../../includes/Hash.h ../../includes/Rgst.h ../../includes/irsrgst.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON rgst_get.c ***' >> $(LO)
	$$irs_lint rgst_get.c 2>&1 | tee -a $(LO)

rgst_get_RGST_OBJECT.ln:rgst_get_RGST_OBJECT.c ../../includes/irs.h               \
	  ../../includes/irs.h ../../includes/Hash.h ../../includes/Rgst.h        \
	  ../../includes/irsrgst.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON rgst_get_RGST_OBJECT.c ***' >> $(LO)
	$$irs_lint rgst_get_RGST_OBJECT.c 2>&1 | tee -a $(LO)

rgst_get_RGST_STRUCT_TD_DEFN.ln:rgst_get_RGST_STRUCT_TD_DEFN.c                    \
	  ../../includes/irs.h ../../includes/irs.h ../../includes/Hash.h         \
	  ../../includes/Rgst.h ../../includes/irsrgst.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON rgst_get_RGST_STRUCT_TD_DEFN.c ***' >> $(LO)
	$$irs_lint rgst_get_RGST_STRUCT_TD_DEFN.c 2>&1 | tee -a $(LO)

rgst_get_attr_type.ln:rgst_get_attr_type.c ../../includes/irs.h                   \
	  ../../includes/irs.h ../../includes/Hash.h ../../includes/Rgst.h        \
	  ../../includes/irsrgst.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON rgst_get_attr_type.c ***' >> $(LO)
	$$irs_lint rgst_get_attr_type.c 2>&1 | tee -a $(LO)

rgst_get_datatype_size.ln:rgst_get_datatype_size.c ../../includes/irs.h           \
	  ../../includes/irs.h ../../includes/Hash.h ../../includes/Rgst.h        \
	  ../../includes/irsrgst.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON rgst_get_datatype_size.c ***' >> $(LO)
	$$irs_lint rgst_get_datatype_size.c 2>&1 | tee -a $(LO)

rgst_get_dims_of_type.ln:rgst_get_dims_of_type.c ../../includes/irs.h             \
	  ../../includes/irsrgst.h ../../includes/Rgst.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON rgst_get_dims_of_type.c ***' >> $(LO)
	$$irs_lint rgst_get_dims_of_type.c 2>&1 | tee -a $(LO)

rgst_get_ds_field_ndx.ln:rgst_get_ds_field_ndx.c ../../includes/irs.h             \
	  ../../includes/irs.h ../../includes/Hash.h ../../includes/Rgst.h        \
	  ../../includes/irsrgst.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON rgst_get_ds_field_ndx.c ***' >> $(LO)
	$$irs_lint rgst_get_ds_field_ndx.c 2>&1 | tee -a $(LO)

rgst_get_field_addr.ln:rgst_get_field_addr.c ../../includes/irs.h                 \
	  ../../includes/irs.h ../../includes/Hash.h ../../includes/irsrgst.h     \
	  ../../includes/Rgst.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON rgst_get_field_addr.c ***' >> $(LO)
	$$irs_lint rgst_get_field_addr.c 2>&1 | tee -a $(LO)

rgst_get_field_array_elm_ptr.ln:rgst_get_field_array_elm_ptr.c                    \
	  ../../includes/irs.h ../../includes/irs.h ../../includes/Hash.h         \
	  ../../includes/irsrgst.h ../../includes/Rgst.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON rgst_get_field_array_elm_ptr.c ***' >> $(LO)
	$$irs_lint rgst_get_field_array_elm_ptr.c 2>&1 | tee -a $(LO)

rgst_get_field_array_size.ln:rgst_get_field_array_size.c ../../includes/irs.h     \
	  ../../includes/irs.h ../../includes/Hash.h ../../includes/Rgst.h        \
	  ../../includes/irsrgst.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON rgst_get_field_array_size.c ***' >> $(LO)
	$$irs_lint rgst_get_field_array_size.c 2>&1 | tee -a $(LO)

rgst_get_field_array_sizes.ln:rgst_get_field_array_sizes.c ../../includes/irs.h   \
	  ../../includes/irs.h ../../includes/Hash.h ../../includes/Rgst.h        \
	  ../../includes/irsrgst.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON rgst_get_field_array_sizes.c ***' >> $(LO)
	$$irs_lint rgst_get_field_array_sizes.c 2>&1 | tee -a $(LO)

rgst_get_long.ln:rgst_get_long.c ../../includes/irs.h ../../includes/irs.h        \
	  ../../includes/Hash.h ../../includes/Rgst.h ../../includes/irsrgst.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON rgst_get_long.c ***' >> $(LO)
	$$irs_lint rgst_get_long.c 2>&1 | tee -a $(LO)

rgst_get_nelms_in_field.ln:rgst_get_nelms_in_field.c ../../includes/irs.h         \
	  ../../includes/irs.h ../../includes/Hash.h ../../includes/Rgst.h        \
	  ../../includes/irsrgst.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON rgst_get_nelms_in_field.c ***' >> $(LO)
	$$irs_lint rgst_get_nelms_in_field.c 2>&1 | tee -a $(LO)

rgst_get_nelms_in_rgst_obj.ln:rgst_get_nelms_in_rgst_obj.c ../../includes/irs.h   \
	  ../../includes/irs.h ../../includes/Hash.h ../../includes/Rgst.h        \
	  ../../includes/irsrgst.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON rgst_get_nelms_in_rgst_obj.c ***' >> $(LO)
	$$irs_lint rgst_get_nelms_in_rgst_obj.c 2>&1 | tee -a $(LO)

rgst_get_object_datatype.ln:rgst_get_object_datatype.c ../../includes/irs.h       \
	  ../../includes/irs.h ../../includes/irsrgst.h ../../includes/Rgst.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON rgst_get_object_datatype.c ***' >> $(LO)
	$$irs_lint rgst_get_object_datatype.c 2>&1 | tee -a $(LO)

rgst_get_object_len.ln:rgst_get_object_len.c ../../includes/irs.h                 \
	  ../../includes/irs.h ../../includes/Hash.h ../../includes/irsrgst.h     \
	  ../../includes/Rgst.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON rgst_get_object_len.c ***' >> $(LO)
	$$irs_lint rgst_get_object_len.c 2>&1 | tee -a $(LO)

rgst_get_struct_array_elm_ptr.ln:rgst_get_struct_array_elm_ptr.c                  \
	  ../../includes/irs.h ../../includes/irs.h ../../includes/Hash.h         \
	  ../../includes/Rgst.h ../../includes/irsrgst.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON rgst_get_struct_array_elm_ptr.c ***' >> $(LO)
	$$irs_lint rgst_get_struct_array_elm_ptr.c 2>&1 | tee -a $(LO)

rgst_get_t.ln:rgst_get_t.c ../../includes/irs.h ../../includes/irs.h              \
	  ../../includes/Hash.h ../../includes/Rgst.h ../../includes/irsrgst.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON rgst_get_t.c ***' >> $(LO)
	$$irs_lint rgst_get_t.c 2>&1 | tee -a $(LO)

rgst_get_td_defn.ln:rgst_get_td_defn.c ../../includes/irs.h ../../includes/irs.h  \
	  ../../includes/Hash.h ../../includes/Rgst.h ../../includes/irsrgst.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON rgst_get_td_defn.c ***' >> $(LO)
	$$irs_lint rgst_get_td_defn.c 2>&1 | tee -a $(LO)

rgst_init.ln:rgst_init.c ../../includes/irs.h ../../includes/irs.h                \
	  ../../includes/Hash.h ../../includes/Rgst.h ../../includes/irsrgst.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON rgst_init.c ***' >> $(LO)
	$$irs_lint rgst_init.c 2>&1 | tee -a $(LO)

rgst_init_struct.ln:rgst_init_struct.c ../../includes/irs.h ../../includes/irs.h  \
	  ../../includes/irsrgst.h ../../includes/Command.h ../../includes/Hash.h \
	  ../../includes/Rgst.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON rgst_init_struct.c ***' >> $(LO)
	$$irs_lint rgst_init_struct.c 2>&1 | tee -a $(LO)

rgst_list_attr.ln:rgst_list_attr.c ../../includes/irs.h ../../includes/irs.h      \
	  ../../includes/irsrgst.h ../../includes/Rgst.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON rgst_list_attr.c ***' >> $(LO)
	$$irs_lint rgst_list_attr.c 2>&1 | tee -a $(LO)

rgst_list_attr_and.ln:rgst_list_attr_and.c ../../includes/irs.h                   \
	  ../../includes/irs.h ../../includes/Hash.h ../../includes/Rgst.h        \
	  ../../includes/irsrgst.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON rgst_list_attr_and.c ***' >> $(LO)
	$$irs_lint rgst_list_attr_and.c 2>&1 | tee -a $(LO)

rgst_list_objs_by_type.ln:rgst_list_objs_by_type.c ../../includes/irs.h           \
	  ../../includes/irs.h ../../includes/Hash.h ../../includes/Rgst.h        \
	  ../../includes/irsrgst.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON rgst_list_objs_by_type.c ***' >> $(LO)
	$$irs_lint rgst_list_objs_by_type.c 2>&1 | tee -a $(LO)

rgst_list_vars_with_attr.ln:rgst_list_vars_with_attr.c ../../includes/irs.h       \
	  ../../includes/irs.h ../../includes/Hash.h ../../includes/Rgst.h        \
	  ../../includes/irsrgst.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON rgst_list_vars_with_attr.c ***' >> $(LO)
	$$irs_lint rgst_list_vars_with_attr.c 2>&1 | tee -a $(LO)

rgst_num_with_attr.ln:rgst_num_with_attr.c ../../includes/irs.h                   \
	  ../../includes/irs.h ../../includes/irsrgst.h ../../includes/Rgst.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON rgst_num_with_attr.c ***' >> $(LO)
	$$irs_lint rgst_num_with_attr.c 2>&1 | tee -a $(LO)

rgst_obj_is_dim_array.ln:rgst_obj_is_dim_array.c ../../includes/irs.h             \
	  ../../includes/irs.h ../../includes/Hash.h ../../includes/irsrgst.h     \
	  ../../includes/Rgst.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON rgst_obj_is_dim_array.c ***' >> $(LO)
	$$irs_lint rgst_obj_is_dim_array.c 2>&1 | tee -a $(LO)

rgst_obj_is_ptr_array.ln:rgst_obj_is_ptr_array.c ../../includes/irs.h             \
	  ../../includes/irs.h ../../includes/Hash.h ../../includes/Rgst.h        \
	  ../../includes/irsrgst.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON rgst_obj_is_ptr_array.c ***' >> $(LO)
	$$irs_lint rgst_obj_is_ptr_array.c 2>&1 | tee -a $(LO)

rgst_print.ln:rgst_print.c ../../includes/irs.h ../../includes/irs.h              \
	  ../../includes/Hash.h ../../includes/Rgst.h ../../includes/irsrgst.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON rgst_print.c ***' >> $(LO)
	$$irs_lint rgst_print.c 2>&1 | tee -a $(LO)

rgst_print_0_ptr_array.ln:rgst_print_0_ptr_array.c ../../includes/irs.h           \
	  ../../includes/irs.h ../../includes/Hash.h ../../includes/Rgst.h        \
	  ../../includes/irsrgst.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON rgst_print_0_ptr_array.c ***' >> $(LO)
	$$irs_lint rgst_print_0_ptr_array.c 2>&1 | tee -a $(LO)

rgst_print_1_ptr_array.ln:rgst_print_1_ptr_array.c ../../includes/irs.h           \
	  ../../includes/irs.h ../../includes/Hash.h ../../includes/Rgst.h        \
	  ../../includes/irsrgst.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON rgst_print_1_ptr_array.c ***' >> $(LO)
	$$irs_lint rgst_print_1_ptr_array.c 2>&1 | tee -a $(LO)

rgst_print_2_ptr_array.ln:rgst_print_2_ptr_array.c ../../includes/irs.h           \
	  ../../includes/irs.h ../../includes/Hash.h ../../includes/Rgst.h        \
	  ../../includes/irsrgst.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON rgst_print_2_ptr_array.c ***' >> $(LO)
	$$irs_lint rgst_print_2_ptr_array.c 2>&1 | tee -a $(LO)

rgst_print_addr.ln:rgst_print_addr.c ../../includes/irs.h ../../includes/irs.h    \
	  ../../includes/Hash.h ../../includes/Rgst.h ../../includes/irsrgst.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON rgst_print_addr.c ***' >> $(LO)
	$$irs_lint rgst_print_addr.c 2>&1 | tee -a $(LO)

rgst_print_addr_member.ln:rgst_print_addr_member.c ../../includes/irs.h           \
	  ../../includes/irs.h ../../includes/Hash.h ../../includes/Rgst.h        \
	  ../../includes/irsrgst.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON rgst_print_addr_member.c ***' >> $(LO)
	$$irs_lint rgst_print_addr_member.c 2>&1 | tee -a $(LO)

rgst_print_ctype_td_defn.ln:rgst_print_ctype_td_defn.c ../../includes/irs.h       \
	  ../../includes/irs.h ../../includes/Hash.h ../../includes/Rgst.h        \
	  ../../includes/irsrgst.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON rgst_print_ctype_td_defn.c ***' >> $(LO)
	$$irs_lint rgst_print_ctype_td_defn.c 2>&1 | tee -a $(LO)

rgst_print_ds_member.ln:rgst_print_ds_member.c ../../includes/irs.h               \
	  ../../includes/irs.h ../../includes/Hash.h ../../includes/Rgst.h        \
	  ../../includes/irsrgst.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON rgst_print_ds_member.c ***' >> $(LO)
	$$irs_lint rgst_print_ds_member.c 2>&1 | tee -a $(LO)

rgst_print_field.ln:rgst_print_field.c ../../includes/irs.h ../../includes/irs.h  \
	  ../../includes/Hash.h ../../includes/Rgst.h ../../includes/irsrgst.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON rgst_print_field.c ***' >> $(LO)
	$$irs_lint rgst_print_field.c 2>&1 | tee -a $(LO)

rgst_print_function.ln:rgst_print_function.c ../../includes/irs.h                 \
	  ../../includes/irs.h ../../includes/irsrgst.h ../../includes/Command.h  \
	  ../../includes/Hash.h ../../includes/Rgst.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON rgst_print_function.c ***' >> $(LO)
	$$irs_lint rgst_print_function.c 2>&1 | tee -a $(LO)

rgst_print_obj.ln:rgst_print_obj.c ../../includes/irs.h ../../includes/irs.h      \
	  ../../includes/Command.h ../../includes/Hash.h ../../includes/Rgst.h    \
	  ../../includes/irsrgst.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON rgst_print_obj.c ***' >> $(LO)
	$$irs_lint rgst_print_obj.c 2>&1 | tee -a $(LO)

rgst_print_ptrs.ln:rgst_print_ptrs.c ../../includes/irs.h ../../includes/irs.h    \
	  ../../includes/Hash.h ../../includes/Rgst.h ../../includes/irsrgst.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON rgst_print_ptrs.c ***' >> $(LO)
	$$irs_lint rgst_print_ptrs.c 2>&1 | tee -a $(LO)

rgst_print_struct.ln:rgst_print_struct.c ../../includes/irs.h                     \
	  ../../includes/irs.h ../../includes/Hash.h ../../includes/Rgst.h        \
	  ../../includes/irsrgst.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON rgst_print_struct.c ***' >> $(LO)
	$$irs_lint rgst_print_struct.c 2>&1 | tee -a $(LO)

rgst_print_struct_td_defn.ln:rgst_print_struct_td_defn.c ../../includes/irs.h     \
	  ../../includes/irs.h ../../includes/Hash.h ../../includes/irsrgst.h     \
	  ../../includes/Rgst.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON rgst_print_struct_td_defn.c ***' >> $(LO)
	$$irs_lint rgst_print_struct_td_defn.c 2>&1 | tee -a $(LO)

rgst_print_structs.ln:rgst_print_structs.c ../../includes/irs.h                   \
	  ../../includes/irs.h ../../includes/Hash.h ../../includes/Rgst.h        \
	  ../../includes/irsrgst.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON rgst_print_structs.c ***' >> $(LO)
	$$irs_lint rgst_print_structs.c 2>&1 | tee -a $(LO)

rgst_print_type.ln:rgst_print_type.c ../../includes/irs.h ../../includes/irs.h    \
	  ../../includes/Hash.h ../../includes/Rgst.h ../../includes/irsrgst.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON rgst_print_type.c ***' >> $(LO)
	$$irs_lint rgst_print_type.c 2>&1 | tee -a $(LO)

rgst_query_attr.ln:rgst_query_attr.c ../../includes/irs.h ../../includes/irs.h    \
	  ../../includes/Hash.h ../../includes/Rgst.h ../../includes/irsrgst.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON rgst_query_attr.c ***' >> $(LO)
	$$irs_lint rgst_query_attr.c 2>&1 | tee -a $(LO)

rgst_read_field.ln:rgst_read_field.c ../../includes/irs.h                         \
	  ../../includes/irsrgst.h ../../includes/Rgst.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON rgst_read_field.c ***' >> $(LO)
	$$irs_lint rgst_read_field.c 2>&1 | tee -a $(LO)

rgst_read_struct.ln:rgst_read_struct.c ../../includes/irs.h                       \
	  ../../includes/irsctl.h ../../includes/irsdefs.h                        \
	  ../../includes/irsrgst.h ../../includes/Command.h                       \
	  ../../includes/Rgst.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON rgst_read_struct.c ***' >> $(LO)
	$$irs_lint rgst_read_struct.c 2>&1 | tee -a $(LO)

rgst_read_struct_array.ln:rgst_read_struct_array.c ../../includes/irs.h           \
	  ../../includes/irsdefs.h ../../includes/irs.h ../../includes/irsrgst.h  \
	  ../../includes/Rgst.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON rgst_read_struct_array.c ***' >> $(LO)
	$$irs_lint rgst_read_struct_array.c 2>&1 | tee -a $(LO)

rgst_split_type_n_fld.ln:rgst_split_type_n_fld.c ../../includes/irs.h             \
	  ../../includes/irs.h ../../includes/irsrgst.h ../../includes/Rgst.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON rgst_split_type_n_fld.c ***' >> $(LO)
	$$irs_lint rgst_split_type_n_fld.c 2>&1 | tee -a $(LO)

rgst_verify_struct_td_defn.ln:rgst_verify_struct_td_defn.c ../../includes/irs.h   \
	  ../../includes/irs.h ../../includes/Hash.h ../../includes/Rgst.h        \
	  ../../includes/irsrgst.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON rgst_verify_struct_td_defn.c ***' >> $(LO)
	$$irs_lint rgst_verify_struct_td_defn.c 2>&1 | tee -a $(LO)

rgst_write_struct.ln:rgst_write_struct.c ../../includes/irs.h                     \
	  ../../includes/irs.h ../../includes/irsrgst.h ../../includes/Command.h  \
	  ../../includes/Rgst.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON rgst_write_struct.c ***' >> $(LO)
	$$irs_lint rgst_write_struct.c 2>&1 | tee -a $(LO)

rgst_write_struct_array.ln:rgst_write_struct_array.c ../../includes/irs.h         \
	  ../../includes/irs.h ../../includes/irsrgst.h ../../includes/Rgst.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON rgst_write_struct_array.c ***' >> $(LO)
	$$irs_lint rgst_write_struct_array.c 2>&1 | tee -a $(LO)

#------------------------------------------
# preprocess files and create .i files 
#------------------------------------------
preprocess:$(PREDIR)/build_proc_name.inst.i $(PREDIR)/copy_toc.inst.i             \
	  $(PREDIR)/domain_hash_tbl_rgst.inst.i $(PREDIR)/free_toc.inst.i         \
	  $(PREDIR)/get_words_at_prompt.inst.i $(PREDIR)/hash_print_obj.inst.i    \
	  $(PREDIR)/hash_print_structs_of_type.inst.i                             \
	  $(PREDIR)/hash_tbl_create_n_rgst.inst.i $(PREDIR)/hash_tbl_rgst.inst.i  \
	  $(PREDIR)/printattr.inst.i $(PREDIR)/printattrlist.inst.i               \
	  $(PREDIR)/printhash.inst.i $(PREDIR)/printrgst.inst.i                   \
	  $(PREDIR)/rgst_add.inst.i $(PREDIR)/rgst_add_attr.inst.i                \
	  $(PREDIR)/rgst_add_ctype_td_defn.inst.i                                 \
	  $(PREDIR)/rgst_add_enum_td_defn.inst.i                                  \
	  $(PREDIR)/rgst_add_struct_td_defn.inst.i $(PREDIR)/rgst_alloc.inst.i    \
	  $(PREDIR)/rgst_check_attr_name.inst.i                                   \
	  $(PREDIR)/rgst_check_for_obj.inst.i                                     \
	  $(PREDIR)/rgst_check_for_td_defn.inst.i                                 \
	  $(PREDIR)/rgst_check_ndxs.inst.i $(PREDIR)/rgst_cleanup.inst.i          \
	  $(PREDIR)/rgst_construct.inst.i                                         \
	  $(PREDIR)/rgst_conv_enum_type_to_str.inst.i $(PREDIR)/rgst_copy.inst.i  \
	  $(PREDIR)/rgst_copy_attr_elm_list.inst.i                                \
	  $(PREDIR)/rgst_create_RGST_ATTR_ELM_TYPE.inst.i                         \
	  $(PREDIR)/rgst_create_typedef_name_str.inst.i $(PREDIR)/rgst_del.inst.i \
	  $(PREDIR)/rgst_del_attr.inst.i $(PREDIR)/rgst_extract_array_ndxs.inst.i \
	  $(PREDIR)/rgst_free_RGST_ATTR_ELM_TYPE.inst.i                           \
	  $(PREDIR)/rgst_free_RGST_ATTR_TYPE.inst.i                               \
	  $(PREDIR)/rgst_free_attr_elm_list.inst.i $(PREDIR)/rgst_get.inst.i      \
	  $(PREDIR)/rgst_get_RGST_OBJECT.inst.i                                   \
	  $(PREDIR)/rgst_get_RGST_STRUCT_TD_DEFN.inst.i                           \
	  $(PREDIR)/rgst_get_attr_type.inst.i                                     \
	  $(PREDIR)/rgst_get_datatype_size.inst.i                                 \
	  $(PREDIR)/rgst_get_dims_of_type.inst.i                                  \
	  $(PREDIR)/rgst_get_ds_field_ndx.inst.i                                  \
	  $(PREDIR)/rgst_get_field_addr.inst.i                                    \
	  $(PREDIR)/rgst_get_field_array_elm_ptr.inst.i                           \
	  $(PREDIR)/rgst_get_field_array_size.inst.i                              \
	  $(PREDIR)/rgst_get_field_array_sizes.inst.i                             \
	  $(PREDIR)/rgst_get_long.inst.i $(PREDIR)/rgst_get_nelms_in_field.inst.i \
	  $(PREDIR)/rgst_get_nelms_in_rgst_obj.inst.i                             \
	  $(PREDIR)/rgst_get_object_datatype.inst.i                               \
	  $(PREDIR)/rgst_get_object_len.inst.i                                    \
	  $(PREDIR)/rgst_get_struct_array_elm_ptr.inst.i                          \
	  $(PREDIR)/rgst_get_t.inst.i $(PREDIR)/rgst_get_td_defn.inst.i           \
	  $(PREDIR)/rgst_init.inst.i $(PREDIR)/rgst_init_struct.inst.i            \
	  $(PREDIR)/rgst_list_attr.inst.i $(PREDIR)/rgst_list_attr_and.inst.i     \
	  $(PREDIR)/rgst_list_objs_by_type.inst.i                                 \
	  $(PREDIR)/rgst_list_vars_with_attr.inst.i                               \
	  $(PREDIR)/rgst_num_with_attr.inst.i                                     \
	  $(PREDIR)/rgst_obj_is_dim_array.inst.i                                  \
	  $(PREDIR)/rgst_obj_is_ptr_array.inst.i $(PREDIR)/rgst_print.inst.i      \
	  $(PREDIR)/rgst_print_0_ptr_array.inst.i                                 \
	  $(PREDIR)/rgst_print_1_ptr_array.inst.i                                 \
	  $(PREDIR)/rgst_print_2_ptr_array.inst.i                                 \
	  $(PREDIR)/rgst_print_addr.inst.i                                        \
	  $(PREDIR)/rgst_print_addr_member.inst.i                                 \
	  $(PREDIR)/rgst_print_ctype_td_defn.inst.i                               \
	  $(PREDIR)/rgst_print_ds_member.inst.i $(PREDIR)/rgst_print_field.inst.i \
	  $(PREDIR)/rgst_print_function.inst.i $(PREDIR)/rgst_print_obj.inst.i    \
	  $(PREDIR)/rgst_print_ptrs.inst.i $(PREDIR)/rgst_print_struct.inst.i     \
	  $(PREDIR)/rgst_print_struct_td_defn.inst.i                              \
	  $(PREDIR)/rgst_print_structs.inst.i $(PREDIR)/rgst_print_type.inst.i    \
	  $(PREDIR)/rgst_query_attr.inst.i $(PREDIR)/rgst_read_field.inst.i       \
	  $(PREDIR)/rgst_read_struct.inst.i                                       \
	  $(PREDIR)/rgst_read_struct_array.inst.i                                 \
	  $(PREDIR)/rgst_split_type_n_fld.inst.i                                  \
	  $(PREDIR)/rgst_verify_struct_td_defn.inst.i                             \
	  $(PREDIR)/rgst_write_struct.inst.i                                      \
	  $(PREDIR)/rgst_write_struct_array.inst.i

#---------------------------------------
# individual preprocessed .i file deps
#---------------------------------------
$(PREDIR)/build_proc_name.inst.i:build_proc_name.c ../../includes/irs.h           \
	  ../../includes/irsrgst.h ../../includes/Rgst.h                          \
	  ../../includes/Command.h
	@rm -f build_proc_name.i
	$$irs_pre build_proc_name.c >> build_proc_name.i
	@mv -f build_proc_name.i $(PREDIR)/build_proc_name.inst.i

$(PREDIR)/copy_toc.inst.i:copy_toc.c ../../includes/irs.h                         \
	  ../../includes/irsrgst.h ../../includes/Rgst.h
	@rm -f copy_toc.i
	$$irs_pre copy_toc.c >> copy_toc.i
	@mv -f copy_toc.i $(PREDIR)/copy_toc.inst.i

$(PREDIR)/domain_hash_tbl_rgst.inst.i:domain_hash_tbl_rgst.c ../../includes/irs.h \
	  ../../includes/irsctl.h ../../includes/Hash.h ../../includes/Rgst.h     \
	  ../../includes/irsrgst.h
	@rm -f domain_hash_tbl_rgst.i
	$$irs_pre domain_hash_tbl_rgst.c >> domain_hash_tbl_rgst.i
	@mv -f domain_hash_tbl_rgst.i $(PREDIR)/domain_hash_tbl_rgst.inst.i

$(PREDIR)/free_toc.inst.i:free_toc.c ../../includes/irs.h                         \
	  ../../includes/irsrgst.h ../../includes/Rgst.h
	@rm -f free_toc.i
	$$irs_pre free_toc.c >> free_toc.i
	@mv -f free_toc.i $(PREDIR)/free_toc.inst.i

$(PREDIR)/get_words_at_prompt.inst.i:get_words_at_prompt.c ../../includes/irs.h   \
	  ../../includes/irsctl.h ../../includes/irsrgst.h                        \
	  ../../includes/Rgst.h
	@rm -f get_words_at_prompt.i
	$$irs_pre get_words_at_prompt.c >> get_words_at_prompt.i
	@mv -f get_words_at_prompt.i $(PREDIR)/get_words_at_prompt.inst.i

$(PREDIR)/hash_print_obj.inst.i:hash_print_obj.c ../../includes/irs.h             \
	  ../../includes/irsrgst.h ../../includes/FreqMesg.h                      \
	  ../../includes/Hash.h ../../includes/Rgst.h ../../includes/TimePlot.h
	@rm -f hash_print_obj.i
	$$irs_pre hash_print_obj.c >> hash_print_obj.i
	@mv -f hash_print_obj.i $(PREDIR)/hash_print_obj.inst.i

$(PREDIR)/hash_print_structs_of_type.inst.i:hash_print_structs_of_type.c          \
	  ../../includes/irs.h ../../includes/Hash.h ../../includes/irsrgst.h     \
	  ../../includes/Rgst.h
	@rm -f hash_print_structs_of_type.i
	$$irs_pre hash_print_structs_of_type.c >> hash_print_structs_of_type.i
	@mv -f hash_print_structs_of_type.i $(PREDIR)/hash_print_structs_of_type.inst.i

$(PREDIR)/hash_tbl_create_n_rgst.inst.i:hash_tbl_create_n_rgst.c                  \
	  ../../includes/irs.h ../../includes/irsctl.h ../../includes/Hash.h      \
	  ../../includes/irsrgst.h ../../includes/Rgst.h
	@rm -f hash_tbl_create_n_rgst.i
	$$irs_pre hash_tbl_create_n_rgst.c >> hash_tbl_create_n_rgst.i
	@mv -f hash_tbl_create_n_rgst.i $(PREDIR)/hash_tbl_create_n_rgst.inst.i

$(PREDIR)/hash_tbl_rgst.inst.i:hash_tbl_rgst.c ../../includes/irs.h               \
	  ../../includes/irsctl.h ../../includes/Hash.h ../../includes/irsrgst.h  \
	  ../../includes/Rgst.h
	@rm -f hash_tbl_rgst.i
	$$irs_pre hash_tbl_rgst.c >> hash_tbl_rgst.i
	@mv -f hash_tbl_rgst.i $(PREDIR)/hash_tbl_rgst.inst.i

$(PREDIR)/printattr.inst.i:printattr.c ../../includes/irs.h                       \
	  ../../includes/irsrgst.h ../../includes/irsctl.h                        \
	  ../../includes/irsdefs.h ../../includes/Hash.h ../../includes/Rgst.h
	@rm -f printattr.i
	$$irs_pre printattr.c >> printattr.i
	@mv -f printattr.i $(PREDIR)/printattr.inst.i

$(PREDIR)/printattrlist.inst.i:printattrlist.c ../../includes/irs.h               \
	  ../../includes/irsctl.h ../../includes/irsdefs.h ../../includes/Hash.h  \
	  ../../includes/irsrgst.h ../../includes/Rgst.h
	@rm -f printattrlist.i
	$$irs_pre printattrlist.c >> printattrlist.i
	@mv -f printattrlist.i $(PREDIR)/printattrlist.inst.i

$(PREDIR)/printhash.inst.i:printhash.c ../../includes/irs.h                       \
	  ../../includes/irsrgst.h ../../includes/irsrgst.h                       \
	  ../../includes/irsctl.h ../../includes/Hash.h ../../includes/Hash.h     \
	  ../../includes/Rgst.h
	@rm -f printhash.i
	$$irs_pre printhash.c >> printhash.i
	@mv -f printhash.i $(PREDIR)/printhash.inst.i

$(PREDIR)/printrgst.inst.i:printrgst.c ../../includes/irs.h ../../includes/irs.h  \
	  ../../includes/irsctl.h ../../includes/irsdefs.h                        \
	  ../../includes/irsrgst.h ../../includes/Rgst.h
	@rm -f printrgst.i
	$$irs_pre printrgst.c >> printrgst.i
	@mv -f printrgst.i $(PREDIR)/printrgst.inst.i

$(PREDIR)/rgst_add.inst.i:rgst_add.c ../../includes/irs.h ../../includes/irs.h    \
	  ../../includes/irsrgst.h ../../includes/Hash.h ../../includes/Rgst.h
	@rm -f rgst_add.i
	$$irs_pre rgst_add.c >> rgst_add.i
	@mv -f rgst_add.i $(PREDIR)/rgst_add.inst.i

$(PREDIR)/rgst_add_attr.inst.i:rgst_add_attr.c ../../includes/irs.h               \
	  ../../includes/irs.h ../../includes/Hash.h ../../includes/Rgst.h        \
	  ../../includes/irsrgst.h
	@rm -f rgst_add_attr.i
	$$irs_pre rgst_add_attr.c >> rgst_add_attr.i
	@mv -f rgst_add_attr.i $(PREDIR)/rgst_add_attr.inst.i

$(PREDIR)/rgst_add_ctype_td_defn.inst.i:rgst_add_ctype_td_defn.c                  \
	  ../../includes/irs.h ../../includes/irs.h ../../includes/Hash.h         \
	  ../../includes/Rgst.h ../../includes/irsrgst.h
	@rm -f rgst_add_ctype_td_defn.i
	$$irs_pre rgst_add_ctype_td_defn.c >> rgst_add_ctype_td_defn.i
	@mv -f rgst_add_ctype_td_defn.i $(PREDIR)/rgst_add_ctype_td_defn.inst.i

$(PREDIR)/rgst_add_enum_td_defn.inst.i:rgst_add_enum_td_defn.c                    \
	  ../../includes/irs.h ../../includes/irs.h ../../includes/Hash.h         \
	  ../../includes/Rgst.h ../../includes/irsrgst.h
	@rm -f rgst_add_enum_td_defn.i
	$$irs_pre rgst_add_enum_td_defn.c >> rgst_add_enum_td_defn.i
	@mv -f rgst_add_enum_td_defn.i $(PREDIR)/rgst_add_enum_td_defn.inst.i

$(PREDIR)/rgst_add_struct_td_defn.inst.i:rgst_add_struct_td_defn.c                \
	  ../../includes/irs.h ../../includes/irs.h ../../includes/Hash.h         \
	  ../../includes/Rgst.h ../../includes/irsrgst.h
	@rm -f rgst_add_struct_td_defn.i
	$$irs_pre rgst_add_struct_td_defn.c >> rgst_add_struct_td_defn.i
	@mv -f rgst_add_struct_td_defn.i $(PREDIR)/rgst_add_struct_td_defn.inst.i

$(PREDIR)/rgst_alloc.inst.i:rgst_alloc.c ../../includes/irs.h                     \
	  ../../includes/irs.h ../../includes/Hash.h ../../includes/irsrgst.h     \
	  ../../includes/Rgst.h
	@rm -f rgst_alloc.i
	$$irs_pre rgst_alloc.c >> rgst_alloc.i
	@mv -f rgst_alloc.i $(PREDIR)/rgst_alloc.inst.i

$(PREDIR)/rgst_check_attr_name.inst.i:rgst_check_attr_name.c ../../includes/irs.h \
	  ../../includes/irsrgst.h ../../includes/Rgst.h
	@rm -f rgst_check_attr_name.i
	$$irs_pre rgst_check_attr_name.c >> rgst_check_attr_name.i
	@mv -f rgst_check_attr_name.i $(PREDIR)/rgst_check_attr_name.inst.i

$(PREDIR)/rgst_check_for_obj.inst.i:rgst_check_for_obj.c ../../includes/irs.h     \
	  ../../includes/irs.h ../../includes/Hash.h ../../includes/Rgst.h        \
	  ../../includes/irsrgst.h
	@rm -f rgst_check_for_obj.i
	$$irs_pre rgst_check_for_obj.c >> rgst_check_for_obj.i
	@mv -f rgst_check_for_obj.i $(PREDIR)/rgst_check_for_obj.inst.i

$(PREDIR)/rgst_check_for_td_defn.inst.i:rgst_check_for_td_defn.c                  \
	  ../../includes/irs.h ../../includes/irs.h ../../includes/Hash.h         \
	  ../../includes/Rgst.h ../../includes/irsrgst.h
	@rm -f rgst_check_for_td_defn.i
	$$irs_pre rgst_check_for_td_defn.c >> rgst_check_for_td_defn.i
	@mv -f rgst_check_for_td_defn.i $(PREDIR)/rgst_check_for_td_defn.inst.i

$(PREDIR)/rgst_check_ndxs.inst.i:rgst_check_ndxs.c ../../includes/irs.h           \
	  ../../includes/irs.h ../../includes/Hash.h ../../includes/Rgst.h        \
	  ../../includes/irsrgst.h
	@rm -f rgst_check_ndxs.i
	$$irs_pre rgst_check_ndxs.c >> rgst_check_ndxs.i
	@mv -f rgst_check_ndxs.i $(PREDIR)/rgst_check_ndxs.inst.i

$(PREDIR)/rgst_cleanup.inst.i:rgst_cleanup.c ../../includes/irs.h                 \
	  ../../includes/irs.h ../../includes/Hash.h ../../includes/Rgst.h        \
	  ../../includes/irsrgst.h
	@rm -f rgst_cleanup.i
	$$irs_pre rgst_cleanup.c >> rgst_cleanup.i
	@mv -f rgst_cleanup.i $(PREDIR)/rgst_cleanup.inst.i

$(PREDIR)/rgst_construct.inst.i:rgst_construct.c ../../includes/irs.h             \
	  ../../includes/irs.h ../../includes/irsrgst.h ../../includes/Hash.h     \
	  ../../includes/Command.h ../../includes/Rgst.h
	@rm -f rgst_construct.i
	$$irs_pre rgst_construct.c >> rgst_construct.i
	@mv -f rgst_construct.i $(PREDIR)/rgst_construct.inst.i

$(PREDIR)/rgst_conv_enum_type_to_str.inst.i:rgst_conv_enum_type_to_str.c          \
	  ../../includes/irs.h ../../includes/irsrgst.h ../../includes/Rgst.h
	@rm -f rgst_conv_enum_type_to_str.i
	$$irs_pre rgst_conv_enum_type_to_str.c >> rgst_conv_enum_type_to_str.i
	@mv -f rgst_conv_enum_type_to_str.i $(PREDIR)/rgst_conv_enum_type_to_str.inst.i

$(PREDIR)/rgst_copy.inst.i:rgst_copy.c ../../includes/irs.h ../../includes/irs.h  \
	  ../../includes/Hash.h ../../includes/Rgst.h ../../includes/irsrgst.h
	@rm -f rgst_copy.i
	$$irs_pre rgst_copy.c >> rgst_copy.i
	@mv -f rgst_copy.i $(PREDIR)/rgst_copy.inst.i

$(PREDIR)/rgst_copy_attr_elm_list.inst.i:rgst_copy_attr_elm_list.c                \
	  ../../includes/irs.h ../../includes/irs.h ../../includes/Hash.h         \
	  ../../includes/Rgst.h ../../includes/irsrgst.h
	@rm -f rgst_copy_attr_elm_list.i
	$$irs_pre rgst_copy_attr_elm_list.c >> rgst_copy_attr_elm_list.i
	@mv -f rgst_copy_attr_elm_list.i $(PREDIR)/rgst_copy_attr_elm_list.inst.i

$(PREDIR)/rgst_create_RGST_ATTR_ELM_TYPE.inst.i:rgst_create_RGST_ATTR_ELM_TYPE.c  \
	  ../../includes/irs.h ../../includes/irs.h ../../includes/irsrgst.h      \
	  ../../includes/Rgst.h
	@rm -f rgst_create_RGST_ATTR_ELM_TYPE.i
	$$irs_pre rgst_create_RGST_ATTR_ELM_TYPE.c >> rgst_create_RGST_ATTR_ELM_TYPE.i
	@mv -f rgst_create_RGST_ATTR_ELM_TYPE.i $(PREDIR)/rgst_create_RGST_ATTR_ELM_TYPE.inst.i

$(PREDIR)/rgst_create_typedef_name_str.inst.i:rgst_create_typedef_name_str.c      \
	  ../../includes/irs.h ../../includes/irs.h ../../includes/Hash.h         \
	  ../../includes/Rgst.h ../../includes/irsrgst.h
	@rm -f rgst_create_typedef_name_str.i
	$$irs_pre rgst_create_typedef_name_str.c >> rgst_create_typedef_name_str.i
	@mv -f rgst_create_typedef_name_str.i $(PREDIR)/rgst_create_typedef_name_str.inst.i

$(PREDIR)/rgst_del.inst.i:rgst_del.c ../../includes/irs.h ../../includes/irs.h    \
	  ../../includes/Hash.h ../../includes/Rgst.h ../../includes/irsrgst.h
	@rm -f rgst_del.i
	$$irs_pre rgst_del.c >> rgst_del.i
	@mv -f rgst_del.i $(PREDIR)/rgst_del.inst.i

$(PREDIR)/rgst_del_attr.inst.i:rgst_del_attr.c ../../includes/irs.h               \
	  ../../includes/irs.h ../../includes/Hash.h ../../includes/Rgst.h        \
	  ../../includes/irsrgst.h ../../includes/irs.h ../../includes/irs.h      \
	  ../../includes/Hash.h ../../includes/irsrgst.h
	@rm -f rgst_del_attr.i
	$$irs_pre rgst_del_attr.c >> rgst_del_attr.i
	@mv -f rgst_del_attr.i $(PREDIR)/rgst_del_attr.inst.i

$(PREDIR)/rgst_extract_array_ndxs.inst.i:rgst_extract_array_ndxs.c                \
	  ../../includes/irs.h ../../includes/irs.h ../../includes/Hash.h         \
	  ../../includes/Rgst.h ../../includes/irsrgst.h
	@rm -f rgst_extract_array_ndxs.i
	$$irs_pre rgst_extract_array_ndxs.c >> rgst_extract_array_ndxs.i
	@mv -f rgst_extract_array_ndxs.i $(PREDIR)/rgst_extract_array_ndxs.inst.i

$(PREDIR)/rgst_free_RGST_ATTR_ELM_TYPE.inst.i:rgst_free_RGST_ATTR_ELM_TYPE.c      \
	  ../../includes/irs.h ../../includes/irs.h ../../includes/Hash.h         \
	  ../../includes/Rgst.h ../../includes/irsrgst.h
	@rm -f rgst_free_RGST_ATTR_ELM_TYPE.i
	$$irs_pre rgst_free_RGST_ATTR_ELM_TYPE.c >> rgst_free_RGST_ATTR_ELM_TYPE.i
	@mv -f rgst_free_RGST_ATTR_ELM_TYPE.i $(PREDIR)/rgst_free_RGST_ATTR_ELM_TYPE.inst.i

$(PREDIR)/rgst_free_RGST_ATTR_TYPE.inst.i:rgst_free_RGST_ATTR_TYPE.c              \
	  ../../includes/irs.h ../../includes/irs.h ../../includes/Hash.h         \
	  ../../includes/Rgst.h ../../includes/irsrgst.h
	@rm -f rgst_free_RGST_ATTR_TYPE.i
	$$irs_pre rgst_free_RGST_ATTR_TYPE.c >> rgst_free_RGST_ATTR_TYPE.i
	@mv -f rgst_free_RGST_ATTR_TYPE.i $(PREDIR)/rgst_free_RGST_ATTR_TYPE.inst.i

$(PREDIR)/rgst_free_attr_elm_list.inst.i:rgst_free_attr_elm_list.c                \
	  ../../includes/irs.h ../../includes/irs.h ../../includes/Hash.h         \
	  ../../includes/Rgst.h ../../includes/irsrgst.h
	@rm -f rgst_free_attr_elm_list.i
	$$irs_pre rgst_free_attr_elm_list.c >> rgst_free_attr_elm_list.i
	@mv -f rgst_free_attr_elm_list.i $(PREDIR)/rgst_free_attr_elm_list.inst.i

$(PREDIR)/rgst_get.inst.i:rgst_get.c ../../includes/irs.h ../../includes/irs.h    \
	  ../../includes/Hash.h ../../includes/Rgst.h ../../includes/irsrgst.h
	@rm -f rgst_get.i
	$$irs_pre rgst_get.c >> rgst_get.i
	@mv -f rgst_get.i $(PREDIR)/rgst_get.inst.i

$(PREDIR)/rgst_get_RGST_OBJECT.inst.i:rgst_get_RGST_OBJECT.c ../../includes/irs.h \
	  ../../includes/irs.h ../../includes/Hash.h ../../includes/Rgst.h        \
	  ../../includes/irsrgst.h
	@rm -f rgst_get_RGST_OBJECT.i
	$$irs_pre rgst_get_RGST_OBJECT.c >> rgst_get_RGST_OBJECT.i
	@mv -f rgst_get_RGST_OBJECT.i $(PREDIR)/rgst_get_RGST_OBJECT.inst.i

$(PREDIR)/rgst_get_RGST_STRUCT_TD_DEFN.inst.i:rgst_get_RGST_STRUCT_TD_DEFN.c      \
	  ../../includes/irs.h ../../includes/irs.h ../../includes/Hash.h         \
	  ../../includes/Rgst.h ../../includes/irsrgst.h
	@rm -f rgst_get_RGST_STRUCT_TD_DEFN.i
	$$irs_pre rgst_get_RGST_STRUCT_TD_DEFN.c >> rgst_get_RGST_STRUCT_TD_DEFN.i
	@mv -f rgst_get_RGST_STRUCT_TD_DEFN.i $(PREDIR)/rgst_get_RGST_STRUCT_TD_DEFN.inst.i

$(PREDIR)/rgst_get_attr_type.inst.i:rgst_get_attr_type.c ../../includes/irs.h     \
	  ../../includes/irs.h ../../includes/Hash.h ../../includes/Rgst.h        \
	  ../../includes/irsrgst.h
	@rm -f rgst_get_attr_type.i
	$$irs_pre rgst_get_attr_type.c >> rgst_get_attr_type.i
	@mv -f rgst_get_attr_type.i $(PREDIR)/rgst_get_attr_type.inst.i

$(PREDIR)/rgst_get_datatype_size.inst.i:rgst_get_datatype_size.c                  \
	  ../../includes/irs.h ../../includes/irs.h ../../includes/Hash.h         \
	  ../../includes/Rgst.h ../../includes/irsrgst.h
	@rm -f rgst_get_datatype_size.i
	$$irs_pre rgst_get_datatype_size.c >> rgst_get_datatype_size.i
	@mv -f rgst_get_datatype_size.i $(PREDIR)/rgst_get_datatype_size.inst.i

$(PREDIR)/rgst_get_dims_of_type.inst.i:rgst_get_dims_of_type.c                    \
	  ../../includes/irs.h ../../includes/irsrgst.h ../../includes/Rgst.h
	@rm -f rgst_get_dims_of_type.i
	$$irs_pre rgst_get_dims_of_type.c >> rgst_get_dims_of_type.i
	@mv -f rgst_get_dims_of_type.i $(PREDIR)/rgst_get_dims_of_type.inst.i

$(PREDIR)/rgst_get_ds_field_ndx.inst.i:rgst_get_ds_field_ndx.c                    \
	  ../../includes/irs.h ../../includes/irs.h ../../includes/Hash.h         \
	  ../../includes/Rgst.h ../../includes/irsrgst.h
	@rm -f rgst_get_ds_field_ndx.i
	$$irs_pre rgst_get_ds_field_ndx.c >> rgst_get_ds_field_ndx.i
	@mv -f rgst_get_ds_field_ndx.i $(PREDIR)/rgst_get_ds_field_ndx.inst.i

$(PREDIR)/rgst_get_field_addr.inst.i:rgst_get_field_addr.c ../../includes/irs.h   \
	  ../../includes/irs.h ../../includes/Hash.h ../../includes/irsrgst.h     \
	  ../../includes/Rgst.h
	@rm -f rgst_get_field_addr.i
	$$irs_pre rgst_get_field_addr.c >> rgst_get_field_addr.i
	@mv -f rgst_get_field_addr.i $(PREDIR)/rgst_get_field_addr.inst.i

$(PREDIR)/rgst_get_field_array_elm_ptr.inst.i:rgst_get_field_array_elm_ptr.c      \
	  ../../includes/irs.h ../../includes/irs.h ../../includes/Hash.h         \
	  ../../includes/irsrgst.h ../../includes/Rgst.h
	@rm -f rgst_get_field_array_elm_ptr.i
	$$irs_pre rgst_get_field_array_elm_ptr.c >> rgst_get_field_array_elm_ptr.i
	@mv -f rgst_get_field_array_elm_ptr.i $(PREDIR)/rgst_get_field_array_elm_ptr.inst.i

$(PREDIR)/rgst_get_field_array_size.inst.i:rgst_get_field_array_size.c            \
	  ../../includes/irs.h ../../includes/irs.h ../../includes/Hash.h         \
	  ../../includes/Rgst.h ../../includes/irsrgst.h
	@rm -f rgst_get_field_array_size.i
	$$irs_pre rgst_get_field_array_size.c >> rgst_get_field_array_size.i
	@mv -f rgst_get_field_array_size.i $(PREDIR)/rgst_get_field_array_size.inst.i

$(PREDIR)/rgst_get_field_array_sizes.inst.i:rgst_get_field_array_sizes.c          \
	  ../../includes/irs.h ../../includes/irs.h ../../includes/Hash.h         \
	  ../../includes/Rgst.h ../../includes/irsrgst.h
	@rm -f rgst_get_field_array_sizes.i
	$$irs_pre rgst_get_field_array_sizes.c >> rgst_get_field_array_sizes.i
	@mv -f rgst_get_field_array_sizes.i $(PREDIR)/rgst_get_field_array_sizes.inst.i

$(PREDIR)/rgst_get_long.inst.i:rgst_get_long.c ../../includes/irs.h               \
	  ../../includes/irs.h ../../includes/Hash.h ../../includes/Rgst.h        \
	  ../../includes/irsrgst.h
	@rm -f rgst_get_long.i
	$$irs_pre rgst_get_long.c >> rgst_get_long.i
	@mv -f rgst_get_long.i $(PREDIR)/rgst_get_long.inst.i

$(PREDIR)/rgst_get_nelms_in_field.inst.i:rgst_get_nelms_in_field.c                \
	  ../../includes/irs.h ../../includes/irs.h ../../includes/Hash.h         \
	  ../../includes/Rgst.h ../../includes/irsrgst.h
	@rm -f rgst_get_nelms_in_field.i
	$$irs_pre rgst_get_nelms_in_field.c >> rgst_get_nelms_in_field.i
	@mv -f rgst_get_nelms_in_field.i $(PREDIR)/rgst_get_nelms_in_field.inst.i

$(PREDIR)/rgst_get_nelms_in_rgst_obj.inst.i:rgst_get_nelms_in_rgst_obj.c          \
	  ../../includes/irs.h ../../includes/irs.h ../../includes/Hash.h         \
	  ../../includes/Rgst.h ../../includes/irsrgst.h
	@rm -f rgst_get_nelms_in_rgst_obj.i
	$$irs_pre rgst_get_nelms_in_rgst_obj.c >> rgst_get_nelms_in_rgst_obj.i
	@mv -f rgst_get_nelms_in_rgst_obj.i $(PREDIR)/rgst_get_nelms_in_rgst_obj.inst.i

$(PREDIR)/rgst_get_object_datatype.inst.i:rgst_get_object_datatype.c              \
	  ../../includes/irs.h ../../includes/irs.h ../../includes/irsrgst.h      \
	  ../../includes/Rgst.h
	@rm -f rgst_get_object_datatype.i
	$$irs_pre rgst_get_object_datatype.c >> rgst_get_object_datatype.i
	@mv -f rgst_get_object_datatype.i $(PREDIR)/rgst_get_object_datatype.inst.i

$(PREDIR)/rgst_get_object_len.inst.i:rgst_get_object_len.c ../../includes/irs.h   \
	  ../../includes/irs.h ../../includes/Hash.h ../../includes/irsrgst.h     \
	  ../../includes/Rgst.h
	@rm -f rgst_get_object_len.i
	$$irs_pre rgst_get_object_len.c >> rgst_get_object_len.i
	@mv -f rgst_get_object_len.i $(PREDIR)/rgst_get_object_len.inst.i

$(PREDIR)/rgst_get_struct_array_elm_ptr.inst.i:rgst_get_struct_array_elm_ptr.c    \
	  ../../includes/irs.h ../../includes/irs.h ../../includes/Hash.h         \
	  ../../includes/Rgst.h ../../includes/irsrgst.h
	@rm -f rgst_get_struct_array_elm_ptr.i
	$$irs_pre rgst_get_struct_array_elm_ptr.c >> rgst_get_struct_array_elm_ptr.i
	@mv -f rgst_get_struct_array_elm_ptr.i $(PREDIR)/rgst_get_struct_array_elm_ptr.inst.i

$(PREDIR)/rgst_get_t.inst.i:rgst_get_t.c ../../includes/irs.h                     \
	  ../../includes/irs.h ../../includes/Hash.h ../../includes/Rgst.h        \
	  ../../includes/irsrgst.h
	@rm -f rgst_get_t.i
	$$irs_pre rgst_get_t.c >> rgst_get_t.i
	@mv -f rgst_get_t.i $(PREDIR)/rgst_get_t.inst.i

$(PREDIR)/rgst_get_td_defn.inst.i:rgst_get_td_defn.c ../../includes/irs.h         \
	  ../../includes/irs.h ../../includes/Hash.h ../../includes/Rgst.h        \
	  ../../includes/irsrgst.h
	@rm -f rgst_get_td_defn.i
	$$irs_pre rgst_get_td_defn.c >> rgst_get_td_defn.i
	@mv -f rgst_get_td_defn.i $(PREDIR)/rgst_get_td_defn.inst.i

$(PREDIR)/rgst_init.inst.i:rgst_init.c ../../includes/irs.h ../../includes/irs.h  \
	  ../../includes/Hash.h ../../includes/Rgst.h ../../includes/irsrgst.h
	@rm -f rgst_init.i
	$$irs_pre rgst_init.c >> rgst_init.i
	@mv -f rgst_init.i $(PREDIR)/rgst_init.inst.i

$(PREDIR)/rgst_init_struct.inst.i:rgst_init_struct.c ../../includes/irs.h         \
	  ../../includes/irs.h ../../includes/irsrgst.h ../../includes/Command.h  \
	  ../../includes/Hash.h ../../includes/Rgst.h
	@rm -f rgst_init_struct.i
	$$irs_pre rgst_init_struct.c >> rgst_init_struct.i
	@mv -f rgst_init_struct.i $(PREDIR)/rgst_init_struct.inst.i

$(PREDIR)/rgst_list_attr.inst.i:rgst_list_attr.c ../../includes/irs.h             \
	  ../../includes/irs.h ../../includes/irsrgst.h ../../includes/Rgst.h
	@rm -f rgst_list_attr.i
	$$irs_pre rgst_list_attr.c >> rgst_list_attr.i
	@mv -f rgst_list_attr.i $(PREDIR)/rgst_list_attr.inst.i

$(PREDIR)/rgst_list_attr_and.inst.i:rgst_list_attr_and.c ../../includes/irs.h     \
	  ../../includes/irs.h ../../includes/Hash.h ../../includes/Rgst.h        \
	  ../../includes/irsrgst.h
	@rm -f rgst_list_attr_and.i
	$$irs_pre rgst_list_attr_and.c >> rgst_list_attr_and.i
	@mv -f rgst_list_attr_and.i $(PREDIR)/rgst_list_attr_and.inst.i

$(PREDIR)/rgst_list_objs_by_type.inst.i:rgst_list_objs_by_type.c                  \
	  ../../includes/irs.h ../../includes/irs.h ../../includes/Hash.h         \
	  ../../includes/Rgst.h ../../includes/irsrgst.h
	@rm -f rgst_list_objs_by_type.i
	$$irs_pre rgst_list_objs_by_type.c >> rgst_list_objs_by_type.i
	@mv -f rgst_list_objs_by_type.i $(PREDIR)/rgst_list_objs_by_type.inst.i

$(PREDIR)/rgst_list_vars_with_attr.inst.i:rgst_list_vars_with_attr.c              \
	  ../../includes/irs.h ../../includes/irs.h ../../includes/Hash.h         \
	  ../../includes/Rgst.h ../../includes/irsrgst.h
	@rm -f rgst_list_vars_with_attr.i
	$$irs_pre rgst_list_vars_with_attr.c >> rgst_list_vars_with_attr.i
	@mv -f rgst_list_vars_with_attr.i $(PREDIR)/rgst_list_vars_with_attr.inst.i

$(PREDIR)/rgst_num_with_attr.inst.i:rgst_num_with_attr.c ../../includes/irs.h     \
	  ../../includes/irs.h ../../includes/irsrgst.h ../../includes/Rgst.h
	@rm -f rgst_num_with_attr.i
	$$irs_pre rgst_num_with_attr.c >> rgst_num_with_attr.i
	@mv -f rgst_num_with_attr.i $(PREDIR)/rgst_num_with_attr.inst.i

$(PREDIR)/rgst_obj_is_dim_array.inst.i:rgst_obj_is_dim_array.c                    \
	  ../../includes/irs.h ../../includes/irs.h ../../includes/Hash.h         \
	  ../../includes/irsrgst.h ../../includes/Rgst.h
	@rm -f rgst_obj_is_dim_array.i
	$$irs_pre rgst_obj_is_dim_array.c >> rgst_obj_is_dim_array.i
	@mv -f rgst_obj_is_dim_array.i $(PREDIR)/rgst_obj_is_dim_array.inst.i

$(PREDIR)/rgst_obj_is_ptr_array.inst.i:rgst_obj_is_ptr_array.c                    \
	  ../../includes/irs.h ../../includes/irs.h ../../includes/Hash.h         \
	  ../../includes/Rgst.h ../../includes/irsrgst.h
	@rm -f rgst_obj_is_ptr_array.i
	$$irs_pre rgst_obj_is_ptr_array.c >> rgst_obj_is_ptr_array.i
	@mv -f rgst_obj_is_ptr_array.i $(PREDIR)/rgst_obj_is_ptr_array.inst.i

$(PREDIR)/rgst_print.inst.i:rgst_print.c ../../includes/irs.h                     \
	  ../../includes/irs.h ../../includes/Hash.h ../../includes/Rgst.h        \
	  ../../includes/irsrgst.h
	@rm -f rgst_print.i
	$$irs_pre rgst_print.c >> rgst_print.i
	@mv -f rgst_print.i $(PREDIR)/rgst_print.inst.i

$(PREDIR)/rgst_print_0_ptr_array.inst.i:rgst_print_0_ptr_array.c                  \
	  ../../includes/irs.h ../../includes/irs.h ../../includes/Hash.h         \
	  ../../includes/Rgst.h ../../includes/irsrgst.h
	@rm -f rgst_print_0_ptr_array.i
	$$irs_pre rgst_print_0_ptr_array.c >> rgst_print_0_ptr_array.i
	@mv -f rgst_print_0_ptr_array.i $(PREDIR)/rgst_print_0_ptr_array.inst.i

$(PREDIR)/rgst_print_1_ptr_array.inst.i:rgst_print_1_ptr_array.c                  \
	  ../../includes/irs.h ../../includes/irs.h ../../includes/Hash.h         \
	  ../../includes/Rgst.h ../../includes/irsrgst.h
	@rm -f rgst_print_1_ptr_array.i
	$$irs_pre rgst_print_1_ptr_array.c >> rgst_print_1_ptr_array.i
	@mv -f rgst_print_1_ptr_array.i $(PREDIR)/rgst_print_1_ptr_array.inst.i

$(PREDIR)/rgst_print_2_ptr_array.inst.i:rgst_print_2_ptr_array.c                  \
	  ../../includes/irs.h ../../includes/irs.h ../../includes/Hash.h         \
	  ../../includes/Rgst.h ../../includes/irsrgst.h
	@rm -f rgst_print_2_ptr_array.i
	$$irs_pre rgst_print_2_ptr_array.c >> rgst_print_2_ptr_array.i
	@mv -f rgst_print_2_ptr_array.i $(PREDIR)/rgst_print_2_ptr_array.inst.i

$(PREDIR)/rgst_print_addr.inst.i:rgst_print_addr.c ../../includes/irs.h           \
	  ../../includes/irs.h ../../includes/Hash.h ../../includes/Rgst.h        \
	  ../../includes/irsrgst.h
	@rm -f rgst_print_addr.i
	$$irs_pre rgst_print_addr.c >> rgst_print_addr.i
	@mv -f rgst_print_addr.i $(PREDIR)/rgst_print_addr.inst.i

$(PREDIR)/rgst_print_addr_member.inst.i:rgst_print_addr_member.c                  \
	  ../../includes/irs.h ../../includes/irs.h ../../includes/Hash.h         \
	  ../../includes/Rgst.h ../../includes/irsrgst.h
	@rm -f rgst_print_addr_member.i
	$$irs_pre rgst_print_addr_member.c >> rgst_print_addr_member.i
	@mv -f rgst_print_addr_member.i $(PREDIR)/rgst_print_addr_member.inst.i

$(PREDIR)/rgst_print_ctype_td_defn.inst.i:rgst_print_ctype_td_defn.c              \
	  ../../includes/irs.h ../../includes/irs.h ../../includes/Hash.h         \
	  ../../includes/Rgst.h ../../includes/irsrgst.h
	@rm -f rgst_print_ctype_td_defn.i
	$$irs_pre rgst_print_ctype_td_defn.c >> rgst_print_ctype_td_defn.i
	@mv -f rgst_print_ctype_td_defn.i $(PREDIR)/rgst_print_ctype_td_defn.inst.i

$(PREDIR)/rgst_print_ds_member.inst.i:rgst_print_ds_member.c ../../includes/irs.h \
	  ../../includes/irs.h ../../includes/Hash.h ../../includes/Rgst.h        \
	  ../../includes/irsrgst.h
	@rm -f rgst_print_ds_member.i
	$$irs_pre rgst_print_ds_member.c >> rgst_print_ds_member.i
	@mv -f rgst_print_ds_member.i $(PREDIR)/rgst_print_ds_member.inst.i

$(PREDIR)/rgst_print_field.inst.i:rgst_print_field.c ../../includes/irs.h         \
	  ../../includes/irs.h ../../includes/Hash.h ../../includes/Rgst.h        \
	  ../../includes/irsrgst.h
	@rm -f rgst_print_field.i
	$$irs_pre rgst_print_field.c >> rgst_print_field.i
	@mv -f rgst_print_field.i $(PREDIR)/rgst_print_field.inst.i

$(PREDIR)/rgst_print_function.inst.i:rgst_print_function.c ../../includes/irs.h   \
	  ../../includes/irs.h ../../includes/irsrgst.h ../../includes/Command.h  \
	  ../../includes/Hash.h ../../includes/Rgst.h
	@rm -f rgst_print_function.i
	$$irs_pre rgst_print_function.c >> rgst_print_function.i
	@mv -f rgst_print_function.i $(PREDIR)/rgst_print_function.inst.i

$(PREDIR)/rgst_print_obj.inst.i:rgst_print_obj.c ../../includes/irs.h             \
	  ../../includes/irs.h ../../includes/Command.h ../../includes/Hash.h     \
	  ../../includes/Rgst.h ../../includes/irsrgst.h
	@rm -f rgst_print_obj.i
	$$irs_pre rgst_print_obj.c >> rgst_print_obj.i
	@mv -f rgst_print_obj.i $(PREDIR)/rgst_print_obj.inst.i

$(PREDIR)/rgst_print_ptrs.inst.i:rgst_print_ptrs.c ../../includes/irs.h           \
	  ../../includes/irs.h ../../includes/Hash.h ../../includes/Rgst.h        \
	  ../../includes/irsrgst.h
	@rm -f rgst_print_ptrs.i
	$$irs_pre rgst_print_ptrs.c >> rgst_print_ptrs.i
	@mv -f rgst_print_ptrs.i $(PREDIR)/rgst_print_ptrs.inst.i

$(PREDIR)/rgst_print_struct.inst.i:rgst_print_struct.c ../../includes/irs.h       \
	  ../../includes/irs.h ../../includes/Hash.h ../../includes/Rgst.h        \
	  ../../includes/irsrgst.h
	@rm -f rgst_print_struct.i
	$$irs_pre rgst_print_struct.c >> rgst_print_struct.i
	@mv -f rgst_print_struct.i $(PREDIR)/rgst_print_struct.inst.i

$(PREDIR)/rgst_print_struct_td_defn.inst.i:rgst_print_struct_td_defn.c            \
	  ../../includes/irs.h ../../includes/irs.h ../../includes/Hash.h         \
	  ../../includes/irsrgst.h ../../includes/Rgst.h
	@rm -f rgst_print_struct_td_defn.i
	$$irs_pre rgst_print_struct_td_defn.c >> rgst_print_struct_td_defn.i
	@mv -f rgst_print_struct_td_defn.i $(PREDIR)/rgst_print_struct_td_defn.inst.i

$(PREDIR)/rgst_print_structs.inst.i:rgst_print_structs.c ../../includes/irs.h     \
	  ../../includes/irs.h ../../includes/Hash.h ../../includes/Rgst.h        \
	  ../../includes/irsrgst.h
	@rm -f rgst_print_structs.i
	$$irs_pre rgst_print_structs.c >> rgst_print_structs.i
	@mv -f rgst_print_structs.i $(PREDIR)/rgst_print_structs.inst.i

$(PREDIR)/rgst_print_type.inst.i:rgst_print_type.c ../../includes/irs.h           \
	  ../../includes/irs.h ../../includes/Hash.h ../../includes/Rgst.h        \
	  ../../includes/irsrgst.h
	@rm -f rgst_print_type.i
	$$irs_pre rgst_print_type.c >> rgst_print_type.i
	@mv -f rgst_print_type.i $(PREDIR)/rgst_print_type.inst.i

$(PREDIR)/rgst_query_attr.inst.i:rgst_query_attr.c ../../includes/irs.h           \
	  ../../includes/irs.h ../../includes/Hash.h ../../includes/Rgst.h        \
	  ../../includes/irsrgst.h
	@rm -f rgst_query_attr.i
	$$irs_pre rgst_query_attr.c >> rgst_query_attr.i
	@mv -f rgst_query_attr.i $(PREDIR)/rgst_query_attr.inst.i

$(PREDIR)/rgst_read_field.inst.i:rgst_read_field.c ../../includes/irs.h           \
	  ../../includes/irsrgst.h ../../includes/Rgst.h
	@rm -f rgst_read_field.i
	$$irs_pre rgst_read_field.c >> rgst_read_field.i
	@mv -f rgst_read_field.i $(PREDIR)/rgst_read_field.inst.i

$(PREDIR)/rgst_read_struct.inst.i:rgst_read_struct.c ../../includes/irs.h         \
	  ../../includes/irsctl.h ../../includes/irsdefs.h                        \
	  ../../includes/irsrgst.h ../../includes/Command.h                       \
	  ../../includes/Rgst.h
	@rm -f rgst_read_struct.i
	$$irs_pre rgst_read_struct.c >> rgst_read_struct.i
	@mv -f rgst_read_struct.i $(PREDIR)/rgst_read_struct.inst.i

$(PREDIR)/rgst_read_struct_array.inst.i:rgst_read_struct_array.c                  \
	  ../../includes/irs.h ../../includes/irsdefs.h ../../includes/irs.h      \
	  ../../includes/irsrgst.h ../../includes/Rgst.h
	@rm -f rgst_read_struct_array.i
	$$irs_pre rgst_read_struct_array.c >> rgst_read_struct_array.i
	@mv -f rgst_read_struct_array.i $(PREDIR)/rgst_read_struct_array.inst.i

$(PREDIR)/rgst_split_type_n_fld.inst.i:rgst_split_type_n_fld.c                    \
	  ../../includes/irs.h ../../includes/irs.h ../../includes/irsrgst.h      \
	  ../../includes/Rgst.h
	@rm -f rgst_split_type_n_fld.i
	$$irs_pre rgst_split_type_n_fld.c >> rgst_split_type_n_fld.i
	@mv -f rgst_split_type_n_fld.i $(PREDIR)/rgst_split_type_n_fld.inst.i

$(PREDIR)/rgst_verify_struct_td_defn.inst.i:rgst_verify_struct_td_defn.c          \
	  ../../includes/irs.h ../../includes/irs.h ../../includes/Hash.h         \
	  ../../includes/Rgst.h ../../includes/irsrgst.h
	@rm -f rgst_verify_struct_td_defn.i
	$$irs_pre rgst_verify_struct_td_defn.c >> rgst_verify_struct_td_defn.i
	@mv -f rgst_verify_struct_td_defn.i $(PREDIR)/rgst_verify_struct_td_defn.inst.i

$(PREDIR)/rgst_write_struct.inst.i:rgst_write_struct.c ../../includes/irs.h       \
	  ../../includes/irs.h ../../includes/irsrgst.h ../../includes/Command.h  \
	  ../../includes/Rgst.h
	@rm -f rgst_write_struct.i
	$$irs_pre rgst_write_struct.c >> rgst_write_struct.i
	@mv -f rgst_write_struct.i $(PREDIR)/rgst_write_struct.inst.i

$(PREDIR)/rgst_write_struct_array.inst.i:rgst_write_struct_array.c                \
	  ../../includes/irs.h ../../includes/irs.h ../../includes/irsrgst.h      \
	  ../../includes/Rgst.h
	@rm -f rgst_write_struct_array.i
	$$irs_pre rgst_write_struct_array.c >> rgst_write_struct_array.i
	@mv -f rgst_write_struct_array.i $(PREDIR)/rgst_write_struct_array.inst.i

#-----------------------------------------------------------
# post-process files and create library from .i files 
#-----------------------------------------------------------
postprocess:librgst_inst

librgst_inst:$(BI)(build_proc_name.inst.o) $(BI)(copy_toc.inst.o)                 \
	  $(BI)(domain_hash_tbl_rgst.inst.o) $(BI)(free_toc.inst.o)               \
	  $(BI)(get_words_at_prompt.inst.o) $(BI)(hash_print_obj.inst.o)          \
	  $(BI)(hash_print_structs_of_type.inst.o)                                \
	  $(BI)(hash_tbl_create_n_rgst.inst.o) $(BI)(hash_tbl_rgst.inst.o)        \
	  $(BI)(printattr.inst.o) $(BI)(printattrlist.inst.o)                     \
	  $(BI)(printhash.inst.o) $(BI)(printrgst.inst.o) $(BI)(rgst_add.inst.o)  \
	  $(BI)(rgst_add_attr.inst.o) $(BI)(rgst_add_ctype_td_defn.inst.o)        \
	  $(BI)(rgst_add_enum_td_defn.inst.o)                                     \
	  $(BI)(rgst_add_struct_td_defn.inst.o) $(BI)(rgst_alloc.inst.o)          \
	  $(BI)(rgst_check_attr_name.inst.o) $(BI)(rgst_check_for_obj.inst.o)     \
	  $(BI)(rgst_check_for_td_defn.inst.o) $(BI)(rgst_check_ndxs.inst.o)      \
	  $(BI)(rgst_cleanup.inst.o) $(BI)(rgst_construct.inst.o)                 \
	  $(BI)(rgst_conv_enum_type_to_str.inst.o) $(BI)(rgst_copy.inst.o)        \
	  $(BI)(rgst_copy_attr_elm_list.inst.o)                                   \
	  $(BI)(rgst_create_RGST_ATTR_ELM_TYPE.inst.o)                            \
	  $(BI)(rgst_create_typedef_name_str.inst.o) $(BI)(rgst_del.inst.o)       \
	  $(BI)(rgst_del_attr.inst.o) $(BI)(rgst_extract_array_ndxs.inst.o)       \
	  $(BI)(rgst_free_RGST_ATTR_ELM_TYPE.inst.o)                              \
	  $(BI)(rgst_free_RGST_ATTR_TYPE.inst.o)                                  \
	  $(BI)(rgst_free_attr_elm_list.inst.o) $(BI)(rgst_get.inst.o)            \
	  $(BI)(rgst_get_RGST_OBJECT.inst.o)                                      \
	  $(BI)(rgst_get_RGST_STRUCT_TD_DEFN.inst.o)                              \
	  $(BI)(rgst_get_attr_type.inst.o) $(BI)(rgst_get_datatype_size.inst.o)   \
	  $(BI)(rgst_get_dims_of_type.inst.o) $(BI)(rgst_get_ds_field_ndx.inst.o) \
	  $(BI)(rgst_get_field_addr.inst.o)                                       \
	  $(BI)(rgst_get_field_array_elm_ptr.inst.o)                              \
	  $(BI)(rgst_get_field_array_size.inst.o)                                 \
	  $(BI)(rgst_get_field_array_sizes.inst.o) $(BI)(rgst_get_long.inst.o)    \
	  $(BI)(rgst_get_nelms_in_field.inst.o)                                   \
	  $(BI)(rgst_get_nelms_in_rgst_obj.inst.o)                                \
	  $(BI)(rgst_get_object_datatype.inst.o)                                  \
	  $(BI)(rgst_get_object_len.inst.o)                                       \
	  $(BI)(rgst_get_struct_array_elm_ptr.inst.o) $(BI)(rgst_get_t.inst.o)    \
	  $(BI)(rgst_get_td_defn.inst.o) $(BI)(rgst_init.inst.o)                  \
	  $(BI)(rgst_init_struct.inst.o) $(BI)(rgst_list_attr.inst.o)             \
	  $(BI)(rgst_list_attr_and.inst.o) $(BI)(rgst_list_objs_by_type.inst.o)   \
	  $(BI)(rgst_list_vars_with_attr.inst.o) $(BI)(rgst_num_with_attr.inst.o) \
	  $(BI)(rgst_obj_is_dim_array.inst.o) $(BI)(rgst_obj_is_ptr_array.inst.o) \
	  $(BI)(rgst_print.inst.o) $(BI)(rgst_print_0_ptr_array.inst.o)           \
	  $(BI)(rgst_print_1_ptr_array.inst.o)                                    \
	  $(BI)(rgst_print_2_ptr_array.inst.o) $(BI)(rgst_print_addr.inst.o)      \
	  $(BI)(rgst_print_addr_member.inst.o)                                    \
	  $(BI)(rgst_print_ctype_td_defn.inst.o)                                  \
	  $(BI)(rgst_print_ds_member.inst.o) $(BI)(rgst_print_field.inst.o)       \
	  $(BI)(rgst_print_function.inst.o) $(BI)(rgst_print_obj.inst.o)          \
	  $(BI)(rgst_print_ptrs.inst.o) $(BI)(rgst_print_struct.inst.o)           \
	  $(BI)(rgst_print_struct_td_defn.inst.o)                                 \
	  $(BI)(rgst_print_structs.inst.o) $(BI)(rgst_print_type.inst.o)          \
	  $(BI)(rgst_query_attr.inst.o) $(BI)(rgst_read_field.inst.o)             \
	  $(BI)(rgst_read_struct.inst.o) $(BI)(rgst_read_struct_array.inst.o)     \
	  $(BI)(rgst_split_type_n_fld.inst.o)                                     \
	  $(BI)(rgst_verify_struct_td_defn.inst.o)                                \
	  $(BI)(rgst_write_struct.inst.o) $(BI)(rgst_write_struct_array.inst.o)
	  @if test -f object_file_flag; then  \
		(echo $$irs_ar ar $(BI) *.o; \
		$$irs_ar $(BI) *.o; \
		rm *.o object_file_flag; \
		echo ln -sf librgst_inst.a $(B); \
		ln -sf librgst_inst.a $(B)); \
	  fi
	  @echo 'librgst_inst library current'


#-------------------------------------------------------------------------------
# individual rules to compile .i files into .o files within instrumented library
#-------------------------------------------------------------------------------
$(BI)(build_proc_name.inst.o):$(INSTDIR)/build_proc_name.inst.i
	$$irs_post $(INSTDIR)/build_proc_name.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/build_proc_name.inst.i $(DB)/build_proc_name.c 

$(BI)(copy_toc.inst.o):$(INSTDIR)/copy_toc.inst.i
	$$irs_post $(INSTDIR)/copy_toc.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/copy_toc.inst.i $(DB)/copy_toc.c 

$(BI)(domain_hash_tbl_rgst.inst.o):$(INSTDIR)/domain_hash_tbl_rgst.inst.i
	$$irs_post $(INSTDIR)/domain_hash_tbl_rgst.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/domain_hash_tbl_rgst.inst.i $(DB)/domain_hash_tbl_rgst.c 

$(BI)(free_toc.inst.o):$(INSTDIR)/free_toc.inst.i
	$$irs_post $(INSTDIR)/free_toc.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/free_toc.inst.i $(DB)/free_toc.c 

$(BI)(get_words_at_prompt.inst.o):$(INSTDIR)/get_words_at_prompt.inst.i
	$$irs_post $(INSTDIR)/get_words_at_prompt.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/get_words_at_prompt.inst.i $(DB)/get_words_at_prompt.c 

$(BI)(hash_print_obj.inst.o):$(INSTDIR)/hash_print_obj.inst.i
	$$irs_post $(INSTDIR)/hash_print_obj.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/hash_print_obj.inst.i $(DB)/hash_print_obj.c 

$(BI)(hash_print_structs_of_type.inst.o):$(INSTDIR)/hash_print_structs_of_type.inst.i
	$$irs_post $(INSTDIR)/hash_print_structs_of_type.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/hash_print_structs_of_type.inst.i $(DB)/hash_print_structs_of_type.c 

$(BI)(hash_tbl_create_n_rgst.inst.o):$(INSTDIR)/hash_tbl_create_n_rgst.inst.i
	$$irs_post $(INSTDIR)/hash_tbl_create_n_rgst.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/hash_tbl_create_n_rgst.inst.i $(DB)/hash_tbl_create_n_rgst.c 

$(BI)(hash_tbl_rgst.inst.o):$(INSTDIR)/hash_tbl_rgst.inst.i
	$$irs_post $(INSTDIR)/hash_tbl_rgst.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/hash_tbl_rgst.inst.i $(DB)/hash_tbl_rgst.c 

$(BI)(printattr.inst.o):$(INSTDIR)/printattr.inst.i
	$$irs_post $(INSTDIR)/printattr.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/printattr.inst.i $(DB)/printattr.c 

$(BI)(printattrlist.inst.o):$(INSTDIR)/printattrlist.inst.i
	$$irs_post $(INSTDIR)/printattrlist.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/printattrlist.inst.i $(DB)/printattrlist.c 

$(BI)(printhash.inst.o):$(INSTDIR)/printhash.inst.i
	$$irs_post $(INSTDIR)/printhash.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/printhash.inst.i $(DB)/printhash.c 

$(BI)(printrgst.inst.o):$(INSTDIR)/printrgst.inst.i
	$$irs_post $(INSTDIR)/printrgst.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/printrgst.inst.i $(DB)/printrgst.c 

$(BI)(rgst_add.inst.o):$(INSTDIR)/rgst_add.inst.i
	$$irs_post $(INSTDIR)/rgst_add.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/rgst_add.inst.i $(DB)/rgst_add.c 

$(BI)(rgst_add_attr.inst.o):$(INSTDIR)/rgst_add_attr.inst.i
	$$irs_post $(INSTDIR)/rgst_add_attr.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/rgst_add_attr.inst.i $(DB)/rgst_add_attr.c 

$(BI)(rgst_add_ctype_td_defn.inst.o):$(INSTDIR)/rgst_add_ctype_td_defn.inst.i
	$$irs_post $(INSTDIR)/rgst_add_ctype_td_defn.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/rgst_add_ctype_td_defn.inst.i $(DB)/rgst_add_ctype_td_defn.c 

$(BI)(rgst_add_enum_td_defn.inst.o):$(INSTDIR)/rgst_add_enum_td_defn.inst.i
	$$irs_post $(INSTDIR)/rgst_add_enum_td_defn.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/rgst_add_enum_td_defn.inst.i $(DB)/rgst_add_enum_td_defn.c 

$(BI)(rgst_add_struct_td_defn.inst.o):$(INSTDIR)/rgst_add_struct_td_defn.inst.i
	$$irs_post $(INSTDIR)/rgst_add_struct_td_defn.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/rgst_add_struct_td_defn.inst.i $(DB)/rgst_add_struct_td_defn.c 

$(BI)(rgst_alloc.inst.o):$(INSTDIR)/rgst_alloc.inst.i
	$$irs_post $(INSTDIR)/rgst_alloc.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/rgst_alloc.inst.i $(DB)/rgst_alloc.c 

$(BI)(rgst_check_attr_name.inst.o):$(INSTDIR)/rgst_check_attr_name.inst.i
	$$irs_post $(INSTDIR)/rgst_check_attr_name.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/rgst_check_attr_name.inst.i $(DB)/rgst_check_attr_name.c 

$(BI)(rgst_check_for_obj.inst.o):$(INSTDIR)/rgst_check_for_obj.inst.i
	$$irs_post $(INSTDIR)/rgst_check_for_obj.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/rgst_check_for_obj.inst.i $(DB)/rgst_check_for_obj.c 

$(BI)(rgst_check_for_td_defn.inst.o):$(INSTDIR)/rgst_check_for_td_defn.inst.i
	$$irs_post $(INSTDIR)/rgst_check_for_td_defn.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/rgst_check_for_td_defn.inst.i $(DB)/rgst_check_for_td_defn.c 

$(BI)(rgst_check_ndxs.inst.o):$(INSTDIR)/rgst_check_ndxs.inst.i
	$$irs_post $(INSTDIR)/rgst_check_ndxs.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/rgst_check_ndxs.inst.i $(DB)/rgst_check_ndxs.c 

$(BI)(rgst_cleanup.inst.o):$(INSTDIR)/rgst_cleanup.inst.i
	$$irs_post $(INSTDIR)/rgst_cleanup.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/rgst_cleanup.inst.i $(DB)/rgst_cleanup.c 

$(BI)(rgst_construct.inst.o):$(INSTDIR)/rgst_construct.inst.i
	$$irs_post $(INSTDIR)/rgst_construct.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/rgst_construct.inst.i $(DB)/rgst_construct.c 

$(BI)(rgst_conv_enum_type_to_str.inst.o):$(INSTDIR)/rgst_conv_enum_type_to_str.inst.i
	$$irs_post $(INSTDIR)/rgst_conv_enum_type_to_str.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/rgst_conv_enum_type_to_str.inst.i $(DB)/rgst_conv_enum_type_to_str.c 

$(BI)(rgst_copy.inst.o):$(INSTDIR)/rgst_copy.inst.i
	$$irs_post $(INSTDIR)/rgst_copy.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/rgst_copy.inst.i $(DB)/rgst_copy.c 

$(BI)(rgst_copy_attr_elm_list.inst.o):$(INSTDIR)/rgst_copy_attr_elm_list.inst.i
	$$irs_post $(INSTDIR)/rgst_copy_attr_elm_list.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/rgst_copy_attr_elm_list.inst.i $(DB)/rgst_copy_attr_elm_list.c 

$(BI)(rgst_create_RGST_ATTR_ELM_TYPE.inst.o):$(INSTDIR)/rgst_create_RGST_ATTR_ELM_TYPE.inst.i
	$$irs_post $(INSTDIR)/rgst_create_RGST_ATTR_ELM_TYPE.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/rgst_create_RGST_ATTR_ELM_TYPE.inst.i $(DB)/rgst_create_RGST_ATTR_ELM_TYPE.c 

$(BI)(rgst_create_typedef_name_str.inst.o):$(INSTDIR)/rgst_create_typedef_name_str.inst.i
	$$irs_post $(INSTDIR)/rgst_create_typedef_name_str.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/rgst_create_typedef_name_str.inst.i $(DB)/rgst_create_typedef_name_str.c 

$(BI)(rgst_del.inst.o):$(INSTDIR)/rgst_del.inst.i
	$$irs_post $(INSTDIR)/rgst_del.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/rgst_del.inst.i $(DB)/rgst_del.c 

$(BI)(rgst_del_attr.inst.o):$(INSTDIR)/rgst_del_attr.inst.i
	$$irs_post $(INSTDIR)/rgst_del_attr.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/rgst_del_attr.inst.i $(DB)/rgst_del_attr.c 

$(BI)(rgst_extract_array_ndxs.inst.o):$(INSTDIR)/rgst_extract_array_ndxs.inst.i
	$$irs_post $(INSTDIR)/rgst_extract_array_ndxs.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/rgst_extract_array_ndxs.inst.i $(DB)/rgst_extract_array_ndxs.c 

$(BI)(rgst_free_RGST_ATTR_ELM_TYPE.inst.o):$(INSTDIR)/rgst_free_RGST_ATTR_ELM_TYPE.inst.i
	$$irs_post $(INSTDIR)/rgst_free_RGST_ATTR_ELM_TYPE.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/rgst_free_RGST_ATTR_ELM_TYPE.inst.i $(DB)/rgst_free_RGST_ATTR_ELM_TYPE.c 

$(BI)(rgst_free_RGST_ATTR_TYPE.inst.o):$(INSTDIR)/rgst_free_RGST_ATTR_TYPE.inst.i
	$$irs_post $(INSTDIR)/rgst_free_RGST_ATTR_TYPE.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/rgst_free_RGST_ATTR_TYPE.inst.i $(DB)/rgst_free_RGST_ATTR_TYPE.c 

$(BI)(rgst_free_attr_elm_list.inst.o):$(INSTDIR)/rgst_free_attr_elm_list.inst.i
	$$irs_post $(INSTDIR)/rgst_free_attr_elm_list.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/rgst_free_attr_elm_list.inst.i $(DB)/rgst_free_attr_elm_list.c 

$(BI)(rgst_get.inst.o):$(INSTDIR)/rgst_get.inst.i
	$$irs_post $(INSTDIR)/rgst_get.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/rgst_get.inst.i $(DB)/rgst_get.c 

$(BI)(rgst_get_RGST_OBJECT.inst.o):$(INSTDIR)/rgst_get_RGST_OBJECT.inst.i
	$$irs_post $(INSTDIR)/rgst_get_RGST_OBJECT.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/rgst_get_RGST_OBJECT.inst.i $(DB)/rgst_get_RGST_OBJECT.c 

$(BI)(rgst_get_RGST_STRUCT_TD_DEFN.inst.o):$(INSTDIR)/rgst_get_RGST_STRUCT_TD_DEFN.inst.i
	$$irs_post $(INSTDIR)/rgst_get_RGST_STRUCT_TD_DEFN.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/rgst_get_RGST_STRUCT_TD_DEFN.inst.i $(DB)/rgst_get_RGST_STRUCT_TD_DEFN.c 

$(BI)(rgst_get_attr_type.inst.o):$(INSTDIR)/rgst_get_attr_type.inst.i
	$$irs_post $(INSTDIR)/rgst_get_attr_type.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/rgst_get_attr_type.inst.i $(DB)/rgst_get_attr_type.c 

$(BI)(rgst_get_datatype_size.inst.o):$(INSTDIR)/rgst_get_datatype_size.inst.i
	$$irs_post $(INSTDIR)/rgst_get_datatype_size.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/rgst_get_datatype_size.inst.i $(DB)/rgst_get_datatype_size.c 

$(BI)(rgst_get_dims_of_type.inst.o):$(INSTDIR)/rgst_get_dims_of_type.inst.i
	$$irs_post $(INSTDIR)/rgst_get_dims_of_type.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/rgst_get_dims_of_type.inst.i $(DB)/rgst_get_dims_of_type.c 

$(BI)(rgst_get_ds_field_ndx.inst.o):$(INSTDIR)/rgst_get_ds_field_ndx.inst.i
	$$irs_post $(INSTDIR)/rgst_get_ds_field_ndx.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/rgst_get_ds_field_ndx.inst.i $(DB)/rgst_get_ds_field_ndx.c 

$(BI)(rgst_get_field_addr.inst.o):$(INSTDIR)/rgst_get_field_addr.inst.i
	$$irs_post $(INSTDIR)/rgst_get_field_addr.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/rgst_get_field_addr.inst.i $(DB)/rgst_get_field_addr.c 

$(BI)(rgst_get_field_array_elm_ptr.inst.o):$(INSTDIR)/rgst_get_field_array_elm_ptr.inst.i
	$$irs_post $(INSTDIR)/rgst_get_field_array_elm_ptr.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/rgst_get_field_array_elm_ptr.inst.i $(DB)/rgst_get_field_array_elm_ptr.c 

$(BI)(rgst_get_field_array_size.inst.o):$(INSTDIR)/rgst_get_field_array_size.inst.i
	$$irs_post $(INSTDIR)/rgst_get_field_array_size.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/rgst_get_field_array_size.inst.i $(DB)/rgst_get_field_array_size.c 

$(BI)(rgst_get_field_array_sizes.inst.o):$(INSTDIR)/rgst_get_field_array_sizes.inst.i
	$$irs_post $(INSTDIR)/rgst_get_field_array_sizes.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/rgst_get_field_array_sizes.inst.i $(DB)/rgst_get_field_array_sizes.c 

$(BI)(rgst_get_long.inst.o):$(INSTDIR)/rgst_get_long.inst.i
	$$irs_post $(INSTDIR)/rgst_get_long.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/rgst_get_long.inst.i $(DB)/rgst_get_long.c 

$(BI)(rgst_get_nelms_in_field.inst.o):$(INSTDIR)/rgst_get_nelms_in_field.inst.i
	$$irs_post $(INSTDIR)/rgst_get_nelms_in_field.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/rgst_get_nelms_in_field.inst.i $(DB)/rgst_get_nelms_in_field.c 

$(BI)(rgst_get_nelms_in_rgst_obj.inst.o):$(INSTDIR)/rgst_get_nelms_in_rgst_obj.inst.i
	$$irs_post $(INSTDIR)/rgst_get_nelms_in_rgst_obj.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/rgst_get_nelms_in_rgst_obj.inst.i $(DB)/rgst_get_nelms_in_rgst_obj.c 

$(BI)(rgst_get_object_datatype.inst.o):$(INSTDIR)/rgst_get_object_datatype.inst.i
	$$irs_post $(INSTDIR)/rgst_get_object_datatype.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/rgst_get_object_datatype.inst.i $(DB)/rgst_get_object_datatype.c 

$(BI)(rgst_get_object_len.inst.o):$(INSTDIR)/rgst_get_object_len.inst.i
	$$irs_post $(INSTDIR)/rgst_get_object_len.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/rgst_get_object_len.inst.i $(DB)/rgst_get_object_len.c 

$(BI)(rgst_get_struct_array_elm_ptr.inst.o):$(INSTDIR)/rgst_get_struct_array_elm_ptr.inst.i
	$$irs_post $(INSTDIR)/rgst_get_struct_array_elm_ptr.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/rgst_get_struct_array_elm_ptr.inst.i $(DB)/rgst_get_struct_array_elm_ptr.c 

$(BI)(rgst_get_t.inst.o):$(INSTDIR)/rgst_get_t.inst.i
	$$irs_post $(INSTDIR)/rgst_get_t.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/rgst_get_t.inst.i $(DB)/rgst_get_t.c 

$(BI)(rgst_get_td_defn.inst.o):$(INSTDIR)/rgst_get_td_defn.inst.i
	$$irs_post $(INSTDIR)/rgst_get_td_defn.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/rgst_get_td_defn.inst.i $(DB)/rgst_get_td_defn.c 

$(BI)(rgst_init.inst.o):$(INSTDIR)/rgst_init.inst.i
	$$irs_post $(INSTDIR)/rgst_init.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/rgst_init.inst.i $(DB)/rgst_init.c 

$(BI)(rgst_init_struct.inst.o):$(INSTDIR)/rgst_init_struct.inst.i
	$$irs_post $(INSTDIR)/rgst_init_struct.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/rgst_init_struct.inst.i $(DB)/rgst_init_struct.c 

$(BI)(rgst_list_attr.inst.o):$(INSTDIR)/rgst_list_attr.inst.i
	$$irs_post $(INSTDIR)/rgst_list_attr.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/rgst_list_attr.inst.i $(DB)/rgst_list_attr.c 

$(BI)(rgst_list_attr_and.inst.o):$(INSTDIR)/rgst_list_attr_and.inst.i
	$$irs_post $(INSTDIR)/rgst_list_attr_and.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/rgst_list_attr_and.inst.i $(DB)/rgst_list_attr_and.c 

$(BI)(rgst_list_objs_by_type.inst.o):$(INSTDIR)/rgst_list_objs_by_type.inst.i
	$$irs_post $(INSTDIR)/rgst_list_objs_by_type.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/rgst_list_objs_by_type.inst.i $(DB)/rgst_list_objs_by_type.c 

$(BI)(rgst_list_vars_with_attr.inst.o):$(INSTDIR)/rgst_list_vars_with_attr.inst.i
	$$irs_post $(INSTDIR)/rgst_list_vars_with_attr.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/rgst_list_vars_with_attr.inst.i $(DB)/rgst_list_vars_with_attr.c 

$(BI)(rgst_num_with_attr.inst.o):$(INSTDIR)/rgst_num_with_attr.inst.i
	$$irs_post $(INSTDIR)/rgst_num_with_attr.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/rgst_num_with_attr.inst.i $(DB)/rgst_num_with_attr.c 

$(BI)(rgst_obj_is_dim_array.inst.o):$(INSTDIR)/rgst_obj_is_dim_array.inst.i
	$$irs_post $(INSTDIR)/rgst_obj_is_dim_array.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/rgst_obj_is_dim_array.inst.i $(DB)/rgst_obj_is_dim_array.c 

$(BI)(rgst_obj_is_ptr_array.inst.o):$(INSTDIR)/rgst_obj_is_ptr_array.inst.i
	$$irs_post $(INSTDIR)/rgst_obj_is_ptr_array.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/rgst_obj_is_ptr_array.inst.i $(DB)/rgst_obj_is_ptr_array.c 

$(BI)(rgst_print.inst.o):$(INSTDIR)/rgst_print.inst.i
	$$irs_post $(INSTDIR)/rgst_print.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/rgst_print.inst.i $(DB)/rgst_print.c 

$(BI)(rgst_print_0_ptr_array.inst.o):$(INSTDIR)/rgst_print_0_ptr_array.inst.i
	$$irs_post $(INSTDIR)/rgst_print_0_ptr_array.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/rgst_print_0_ptr_array.inst.i $(DB)/rgst_print_0_ptr_array.c 

$(BI)(rgst_print_1_ptr_array.inst.o):$(INSTDIR)/rgst_print_1_ptr_array.inst.i
	$$irs_post $(INSTDIR)/rgst_print_1_ptr_array.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/rgst_print_1_ptr_array.inst.i $(DB)/rgst_print_1_ptr_array.c 

$(BI)(rgst_print_2_ptr_array.inst.o):$(INSTDIR)/rgst_print_2_ptr_array.inst.i
	$$irs_post $(INSTDIR)/rgst_print_2_ptr_array.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/rgst_print_2_ptr_array.inst.i $(DB)/rgst_print_2_ptr_array.c 

$(BI)(rgst_print_addr.inst.o):$(INSTDIR)/rgst_print_addr.inst.i
	$$irs_post $(INSTDIR)/rgst_print_addr.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/rgst_print_addr.inst.i $(DB)/rgst_print_addr.c 

$(BI)(rgst_print_addr_member.inst.o):$(INSTDIR)/rgst_print_addr_member.inst.i
	$$irs_post $(INSTDIR)/rgst_print_addr_member.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/rgst_print_addr_member.inst.i $(DB)/rgst_print_addr_member.c 

$(BI)(rgst_print_ctype_td_defn.inst.o):$(INSTDIR)/rgst_print_ctype_td_defn.inst.i
	$$irs_post $(INSTDIR)/rgst_print_ctype_td_defn.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/rgst_print_ctype_td_defn.inst.i $(DB)/rgst_print_ctype_td_defn.c 

$(BI)(rgst_print_ds_member.inst.o):$(INSTDIR)/rgst_print_ds_member.inst.i
	$$irs_post $(INSTDIR)/rgst_print_ds_member.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/rgst_print_ds_member.inst.i $(DB)/rgst_print_ds_member.c 

$(BI)(rgst_print_field.inst.o):$(INSTDIR)/rgst_print_field.inst.i
	$$irs_post $(INSTDIR)/rgst_print_field.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/rgst_print_field.inst.i $(DB)/rgst_print_field.c 

$(BI)(rgst_print_function.inst.o):$(INSTDIR)/rgst_print_function.inst.i
	$$irs_post $(INSTDIR)/rgst_print_function.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/rgst_print_function.inst.i $(DB)/rgst_print_function.c 

$(BI)(rgst_print_obj.inst.o):$(INSTDIR)/rgst_print_obj.inst.i
	$$irs_post $(INSTDIR)/rgst_print_obj.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/rgst_print_obj.inst.i $(DB)/rgst_print_obj.c 

$(BI)(rgst_print_ptrs.inst.o):$(INSTDIR)/rgst_print_ptrs.inst.i
	$$irs_post $(INSTDIR)/rgst_print_ptrs.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/rgst_print_ptrs.inst.i $(DB)/rgst_print_ptrs.c 

$(BI)(rgst_print_struct.inst.o):$(INSTDIR)/rgst_print_struct.inst.i
	$$irs_post $(INSTDIR)/rgst_print_struct.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/rgst_print_struct.inst.i $(DB)/rgst_print_struct.c 

$(BI)(rgst_print_struct_td_defn.inst.o):$(INSTDIR)/rgst_print_struct_td_defn.inst.i
	$$irs_post $(INSTDIR)/rgst_print_struct_td_defn.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/rgst_print_struct_td_defn.inst.i $(DB)/rgst_print_struct_td_defn.c 

$(BI)(rgst_print_structs.inst.o):$(INSTDIR)/rgst_print_structs.inst.i
	$$irs_post $(INSTDIR)/rgst_print_structs.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/rgst_print_structs.inst.i $(DB)/rgst_print_structs.c 

$(BI)(rgst_print_type.inst.o):$(INSTDIR)/rgst_print_type.inst.i
	$$irs_post $(INSTDIR)/rgst_print_type.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/rgst_print_type.inst.i $(DB)/rgst_print_type.c 

$(BI)(rgst_query_attr.inst.o):$(INSTDIR)/rgst_query_attr.inst.i
	$$irs_post $(INSTDIR)/rgst_query_attr.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/rgst_query_attr.inst.i $(DB)/rgst_query_attr.c 

$(BI)(rgst_read_field.inst.o):$(INSTDIR)/rgst_read_field.inst.i
	$$irs_post $(INSTDIR)/rgst_read_field.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/rgst_read_field.inst.i $(DB)/rgst_read_field.c 

$(BI)(rgst_read_struct.inst.o):$(INSTDIR)/rgst_read_struct.inst.i
	$$irs_post $(INSTDIR)/rgst_read_struct.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/rgst_read_struct.inst.i $(DB)/rgst_read_struct.c 

$(BI)(rgst_read_struct_array.inst.o):$(INSTDIR)/rgst_read_struct_array.inst.i
	$$irs_post $(INSTDIR)/rgst_read_struct_array.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/rgst_read_struct_array.inst.i $(DB)/rgst_read_struct_array.c 

$(BI)(rgst_split_type_n_fld.inst.o):$(INSTDIR)/rgst_split_type_n_fld.inst.i
	$$irs_post $(INSTDIR)/rgst_split_type_n_fld.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/rgst_split_type_n_fld.inst.i $(DB)/rgst_split_type_n_fld.c 

$(BI)(rgst_verify_struct_td_defn.inst.o):$(INSTDIR)/rgst_verify_struct_td_defn.inst.i
	$$irs_post $(INSTDIR)/rgst_verify_struct_td_defn.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/rgst_verify_struct_td_defn.inst.i $(DB)/rgst_verify_struct_td_defn.c 

$(BI)(rgst_write_struct.inst.o):$(INSTDIR)/rgst_write_struct.inst.i
	$$irs_post $(INSTDIR)/rgst_write_struct.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/rgst_write_struct.inst.i $(DB)/rgst_write_struct.c 

$(BI)(rgst_write_struct_array.inst.o):$(INSTDIR)/rgst_write_struct_array.inst.i
	$$irs_post $(INSTDIR)/rgst_write_struct_array.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/rgst_write_struct_array.inst.i $(DB)/rgst_write_struct_array.c 

DEP_SRCS = \
	build_proc_name.c copy_toc.c domain_hash_tbl_rgst.c free_toc.c get_words_at_prompt.c  \
	hash_print_obj.c hash_print_structs_of_type.c hash_tbl_create_n_rgst.c  \
	hash_tbl_rgst.c printattr.c printattrlist.c printhash.c printrgst.c rgst_add.c  \
	rgst_add_attr.c rgst_add_ctype_td_defn.c rgst_add_enum_td_defn.c rgst_add_struct_td_defn.c  \
	rgst_alloc.c rgst_check_attr_name.c rgst_check_for_obj.c rgst_check_for_td_defn.c  \
	rgst_check_ndxs.c rgst_cleanup.c rgst_construct.c rgst_conv_enum_type_to_str.c  \
	rgst_copy.c rgst_copy_attr_elm_list.c rgst_create_RGST_ATTR_ELM_TYPE.c  \
	rgst_create_typedef_name_str.c rgst_del.c rgst_del_attr.c rgst_extract_array_ndxs.c  \
	rgst_free_RGST_ATTR_ELM_TYPE.c rgst_free_RGST_ATTR_TYPE.c rgst_free_attr_elm_list.c  \
	rgst_get.c rgst_get_RGST_OBJECT.c rgst_get_RGST_STRUCT_TD_DEFN.c rgst_get_attr_type.c  \
	rgst_get_datatype_size.c rgst_get_dims_of_type.c rgst_get_ds_field_ndx.c  \
	rgst_get_field_addr.c rgst_get_field_array_elm_ptr.c rgst_get_field_array_size.c  \
	rgst_get_field_array_sizes.c rgst_get_long.c rgst_get_nelms_in_field.c  \
	rgst_get_nelms_in_rgst_obj.c rgst_get_object_datatype.c rgst_get_object_len.c  \
	rgst_get_struct_array_elm_ptr.c rgst_get_t.c rgst_get_td_defn.c rgst_init.c  \
	rgst_init_struct.c rgst_list_attr.c rgst_list_attr_and.c rgst_list_objs_by_type.c  \
	rgst_list_vars_with_attr.c rgst_num_with_attr.c rgst_obj_is_dim_array.c  \
	rgst_obj_is_ptr_array.c rgst_print.c rgst_print_0_ptr_array.c rgst_print_1_ptr_array.c  \
	rgst_print_2_ptr_array.c rgst_print_addr.c rgst_print_addr_member.c rgst_print_ctype_td_defn.c  \
	rgst_print_ds_member.c rgst_print_field.c rgst_print_function.c rgst_print_obj.c  \
	rgst_print_ptrs.c rgst_print_struct.c rgst_print_struct_td_defn.c rgst_print_structs.c  \
	rgst_print_type.c rgst_query_attr.c rgst_read_field.c rgst_read_struct.c  \
	rgst_read_struct_array.c rgst_split_type_n_fld.c rgst_verify_struct_td_defn.c  \
	rgst_write_struct.c rgst_write_struct_array.c  

depend:
	@cp -f Makefile.rgst Makefile
	makedepend -- $(DEPFLAGS) -- $(DEP_SRCS)
	irs_fixdepend Makefile

