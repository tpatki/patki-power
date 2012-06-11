
################################################################################
#
# Makefile for irs library hash
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
B = ../$(LIB_DIR)/libhash.a
BI = ../$(LIB_DIR)/libhash_inst.a

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
SRCDIR = ../sources/hash

# Relative path to the output file for lint
#------------------------------------------
# LO = ../../build/lint.out

# library objects list
#---------------------

libhash:$(B)(get_num_elms_in_hashtable.o) $(B)(hash_add.o) $(B)(hash_analyze.o)   \
	  $(B)(hash_cond_print_by_type.o) $(B)(hash_del.o) $(B)(hash_del2.o)      \
	  $(B)(hash_del_objs_of_type.o) $(B)(hash_get_elm_list.o)                 \
	  $(B)(hash_lookup_elm.o) $(B)(hash_lookup_obj.o) $(B)(hash_optimize.o)   \
	  $(B)(hash_print.o) $(B)(hash_print_by_name.o)                           \
	  $(B)(hash_print_by_type.o) $(B)(hash_print_obj.o)                       \
	  $(B)(hash_print_structs_of_type.o) $(B)(hash_sort_array.o)              \
	  $(B)(hash_sort_array_by_type.o) $(B)(hash_tbl_create.o)                 \
	  $(B)(hash_tbl_free.o) $(B)(printhash.o) $(B)(strsave.o)
	  @if test -f object_file_flag; then  \
		(echo $$irs_ar ar $(B) *.o; \
		$$irs_ar $(B) *.o; \
		rm *.o object_file_flag); \
	  fi
	  @echo 'hash library current'

# creation deps
#---------------
$(B)(get_num_elms_in_hashtable.o):get_num_elms_in_hashtable.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/get_num_elms_in_hashtable.c $(DB)/get_num_elms_in_hashtable.c 

../../includes/Hash.hh:../../includes/Hash.h
	cp ../../includes/Hash.h ../../includes/Hash.hh
	perl -p -i -e 's/extern\s+//g' ../../includes/Hash.hh
	irs_hhinit ../../includes/Hash.hh

$(B)(hash_add.o):../../includes/Hash.hh

$(B)(hash_add.o):hash_add.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/hash_add.c $(DB)/hash_add.c 

$(B)(hash_analyze.o):hash_analyze.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/hash_analyze.c $(DB)/hash_analyze.c 

$(B)(hash_cond_print_by_type.o):hash_cond_print_by_type.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/hash_cond_print_by_type.c $(DB)/hash_cond_print_by_type.c 

$(B)(hash_del.o):hash_del.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/hash_del.c $(DB)/hash_del.c 

$(B)(hash_del2.o):hash_del2.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/hash_del2.c $(DB)/hash_del2.c 

$(B)(hash_del_objs_of_type.o):hash_del_objs_of_type.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/hash_del_objs_of_type.c $(DB)/hash_del_objs_of_type.c 

$(B)(hash_get_elm_list.o):hash_get_elm_list.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/hash_get_elm_list.c $(DB)/hash_get_elm_list.c 

$(B)(hash_lookup_elm.o):hash_lookup_elm.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/hash_lookup_elm.c $(DB)/hash_lookup_elm.c 

$(B)(hash_lookup_obj.o):hash_lookup_obj.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/hash_lookup_obj.c $(DB)/hash_lookup_obj.c 

$(B)(hash_optimize.o):hash_optimize.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/hash_optimize.c $(DB)/hash_optimize.c 

$(B)(hash_print.o):hash_print.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/hash_print.c $(DB)/hash_print.c 

$(B)(hash_print_by_name.o):hash_print_by_name.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/hash_print_by_name.c $(DB)/hash_print_by_name.c 

$(B)(hash_print_by_type.o):hash_print_by_type.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/hash_print_by_type.c $(DB)/hash_print_by_type.c 

$(B)(hash_print_obj.o):hash_print_obj.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/hash_print_obj.c $(DB)/hash_print_obj.c 

$(B)(hash_print_structs_of_type.o):hash_print_structs_of_type.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/hash_print_structs_of_type.c $(DB)/hash_print_structs_of_type.c 

$(B)(hash_sort_array.o):hash_sort_array.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/hash_sort_array.c $(DB)/hash_sort_array.c 

$(B)(hash_sort_array_by_type.o):hash_sort_array_by_type.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/hash_sort_array_by_type.c $(DB)/hash_sort_array_by_type.c 

$(B)(hash_tbl_create.o):hash_tbl_create.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/hash_tbl_create.c $(DB)/hash_tbl_create.c 

$(B)(hash_tbl_free.o):hash_tbl_free.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/hash_tbl_free.c $(DB)/hash_tbl_free.c 

$(B)(printhash.o):printhash.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/printhash.c $(DB)/printhash.c 

$(B)(strsave.o):strsave.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/strsave.c $(DB)/strsave.c 

#---------------------
# lint pass one target 
#---------------------
lint:get_num_elms_in_hashtable.ln hash_add.ln hash_analyze.ln                     \
	  hash_cond_print_by_type.ln hash_del.ln hash_del2.ln                     \
	  hash_del_objs_of_type.ln hash_get_elm_list.ln hash_lookup_elm.ln        \
	  hash_lookup_obj.ln hash_optimize.ln hash_print.ln hash_print_by_name.ln \
	  hash_print_by_type.ln hash_print_obj.ln hash_print_structs_of_type.ln   \
	  hash_sort_array.ln hash_sort_array_by_type.ln hash_tbl_create.ln        \
	  hash_tbl_free.ln printhash.ln strsave.ln

#------------------------------
# individual lint .ln file deps
#------------------------------
get_num_elms_in_hashtable.ln:get_num_elms_in_hashtable.c ../../includes/irsdefs.h \
	  ../../includes/Hash.h ../../includes/irsdefs.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON get_num_elms_in_hashtable.c ***' >> $(LO)
	$$irs_lint get_num_elms_in_hashtable.c 2>&1 | tee -a $(LO)

hash_add.ln:hash_add.c ../../includes/irsdefs.h ../../includes/Hash.hh            \
	  ../../includes/irsdefs.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON hash_add.c ***' >> $(LO)
	$$irs_lint hash_add.c 2>&1 | tee -a $(LO)

hash_analyze.ln:hash_analyze.c ../../includes/irs.h ../../includes/irsdefs.h      \
	  ../../includes/Hash.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON hash_analyze.c ***' >> $(LO)
	$$irs_lint hash_analyze.c 2>&1 | tee -a $(LO)

hash_cond_print_by_type.ln:hash_cond_print_by_type.c ../../includes/irsdefs.h     \
	  ../../includes/Hash.h ../../includes/irsdefs.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON hash_cond_print_by_type.c ***' >> $(LO)
	$$irs_lint hash_cond_print_by_type.c 2>&1 | tee -a $(LO)

hash_del.ln:hash_del.c ../../includes/irsdefs.h ../../includes/Hash.h             \
	  ../../includes/irsdefs.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON hash_del.c ***' >> $(LO)
	$$irs_lint hash_del.c 2>&1 | tee -a $(LO)

hash_del2.ln:hash_del2.c ../../includes/irsdefs.h ../../includes/Hash.h           \
	  ../../includes/irsdefs.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON hash_del2.c ***' >> $(LO)
	$$irs_lint hash_del2.c 2>&1 | tee -a $(LO)

hash_del_objs_of_type.ln:hash_del_objs_of_type.c ../../includes/irsdefs.h         \
	  ../../includes/Hash.h ../../includes/irsdefs.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON hash_del_objs_of_type.c ***' >> $(LO)
	$$irs_lint hash_del_objs_of_type.c 2>&1 | tee -a $(LO)

hash_get_elm_list.ln:hash_get_elm_list.c ../../includes/irsdefs.h                 \
	  ../../includes/Hash.h ../../includes/irsdefs.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON hash_get_elm_list.c ***' >> $(LO)
	$$irs_lint hash_get_elm_list.c 2>&1 | tee -a $(LO)

hash_lookup_elm.ln:hash_lookup_elm.c ../../includes/irsdefs.h                     \
	  ../../includes/Hash.h ../../includes/irsdefs.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON hash_lookup_elm.c ***' >> $(LO)
	$$irs_lint hash_lookup_elm.c 2>&1 | tee -a $(LO)

hash_lookup_obj.ln:hash_lookup_obj.c ../../includes/irsdefs.h                     \
	  ../../includes/Hash.h ../../includes/irsdefs.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON hash_lookup_obj.c ***' >> $(LO)
	$$irs_lint hash_lookup_obj.c 2>&1 | tee -a $(LO)

hash_optimize.ln:hash_optimize.c ../../includes/irs.h ../../includes/irsctl.h     \
	  ../../includes/irsrgst.h ../../includes/Hash.h                          \
	  ../../includes/FunctionTimer.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON hash_optimize.c ***' >> $(LO)
	$$irs_lint hash_optimize.c 2>&1 | tee -a $(LO)

hash_print.ln:hash_print.c ../../includes/irsdefs.h ../../includes/Hash.h         \
	  ../../includes/irsdefs.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON hash_print.c ***' >> $(LO)
	$$irs_lint hash_print.c 2>&1 | tee -a $(LO)

hash_print_by_name.ln:hash_print_by_name.c ../../includes/irsdefs.h               \
	  ../../includes/Hash.h ../../includes/irsdefs.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON hash_print_by_name.c ***' >> $(LO)
	$$irs_lint hash_print_by_name.c 2>&1 | tee -a $(LO)

hash_print_by_type.ln:hash_print_by_type.c ../../includes/irsdefs.h               \
	  ../../includes/Hash.h ../../includes/irsdefs.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON hash_print_by_type.c ***' >> $(LO)
	$$irs_lint hash_print_by_type.c 2>&1 | tee -a $(LO)

hash_print_obj.ln:hash_print_obj.c ../../includes/irs.h ../../includes/irsdefs.h  \
	  ../../includes/irsdefs.h ../../includes/irsrgst.h                       \
	  ../../includes/CycleMesg.h ../../includes/FreqMesg.h                    \
	  ../../includes/Hash.h ../../includes/TimePlot.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON hash_print_obj.c ***' >> $(LO)
	$$irs_lint hash_print_obj.c 2>&1 | tee -a $(LO)

hash_print_structs_of_type.ln:hash_print_structs_of_type.c                        \
	  ../../includes/irsdefs.h ../../includes/Hash.h                          \
	  ../../includes/irsdefs.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON hash_print_structs_of_type.c ***' >> $(LO)
	$$irs_lint hash_print_structs_of_type.c 2>&1 | tee -a $(LO)

hash_sort_array.ln:hash_sort_array.c ../../includes/irsdefs.h                     \
	  ../../includes/Hash.h ../../includes/irsdefs.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON hash_sort_array.c ***' >> $(LO)
	$$irs_lint hash_sort_array.c 2>&1 | tee -a $(LO)

hash_sort_array_by_type.ln:hash_sort_array_by_type.c ../../includes/irsdefs.h     \
	  ../../includes/Hash.h ../../includes/irsdefs.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON hash_sort_array_by_type.c ***' >> $(LO)
	$$irs_lint hash_sort_array_by_type.c 2>&1 | tee -a $(LO)

hash_tbl_create.ln:hash_tbl_create.c ../../includes/irsdefs.h                     \
	  ../../includes/Hash.h ../../includes/irsdefs.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON hash_tbl_create.c ***' >> $(LO)
	$$irs_lint hash_tbl_create.c 2>&1 | tee -a $(LO)

hash_tbl_free.ln:hash_tbl_free.c ../../includes/irsdefs.h ../../includes/Hash.h   \
	  ../../includes/irsdefs.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON hash_tbl_free.c ***' >> $(LO)
	$$irs_lint hash_tbl_free.c 2>&1 | tee -a $(LO)

printhash.ln:printhash.c ../../includes/irs.h ../../includes/irsrgst.h            \
	  ../../includes/irsrgst.h ../../includes/irsctl.h                        \
	  ../../includes/Hash.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON printhash.c ***' >> $(LO)
	$$irs_lint printhash.c 2>&1 | tee -a $(LO)

strsave.ln:strsave.c ../../includes/irs.h ../../includes/irsdefs.h                \
	  ../../includes/Hash.h ../../includes/irsdefs.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON strsave.c ***' >> $(LO)
	$$irs_lint strsave.c 2>&1 | tee -a $(LO)

#------------------------------------------
# preprocess files and create .i files 
#------------------------------------------
preprocess:$(PREDIR)/get_num_elms_in_hashtable.inst.i $(PREDIR)/hash_add.inst.i   \
	  $(PREDIR)/hash_analyze.inst.i $(PREDIR)/hash_cond_print_by_type.inst.i  \
	  $(PREDIR)/hash_del.inst.i $(PREDIR)/hash_del2.inst.i                    \
	  $(PREDIR)/hash_del_objs_of_type.inst.i                                  \
	  $(PREDIR)/hash_get_elm_list.inst.i $(PREDIR)/hash_lookup_elm.inst.i     \
	  $(PREDIR)/hash_lookup_obj.inst.i $(PREDIR)/hash_optimize.inst.i         \
	  $(PREDIR)/hash_print.inst.i $(PREDIR)/hash_print_by_name.inst.i         \
	  $(PREDIR)/hash_print_by_type.inst.i $(PREDIR)/hash_print_obj.inst.i     \
	  $(PREDIR)/hash_print_structs_of_type.inst.i                             \
	  $(PREDIR)/hash_sort_array.inst.i                                        \
	  $(PREDIR)/hash_sort_array_by_type.inst.i                                \
	  $(PREDIR)/hash_tbl_create.inst.i $(PREDIR)/hash_tbl_free.inst.i         \
	  $(PREDIR)/printhash.inst.i $(PREDIR)/strsave.inst.i

#---------------------------------------
# individual preprocessed .i file deps
#---------------------------------------
$(PREDIR)/get_num_elms_in_hashtable.inst.i:get_num_elms_in_hashtable.c            \
	  ../../includes/irsdefs.h ../../includes/Hash.h                          \
	  ../../includes/irsdefs.h
	@rm -f get_num_elms_in_hashtable.i
	$$irs_pre get_num_elms_in_hashtable.c >> get_num_elms_in_hashtable.i
	@mv -f get_num_elms_in_hashtable.i $(PREDIR)/get_num_elms_in_hashtable.inst.i

$(PREDIR)/hash_add.inst.i:hash_add.c ../../includes/irsdefs.h                     \
	  ../../includes/Hash.hh ../../includes/irsdefs.h
	@rm -f hash_add.i
	$$irs_pre hash_add.c >> hash_add.i
	@mv -f hash_add.i $(PREDIR)/hash_add.inst.i

$(PREDIR)/hash_analyze.inst.i:hash_analyze.c ../../includes/irs.h                 \
	  ../../includes/irsdefs.h ../../includes/Hash.h
	@rm -f hash_analyze.i
	$$irs_pre hash_analyze.c >> hash_analyze.i
	@mv -f hash_analyze.i $(PREDIR)/hash_analyze.inst.i

$(PREDIR)/hash_cond_print_by_type.inst.i:hash_cond_print_by_type.c                \
	  ../../includes/irsdefs.h ../../includes/Hash.h                          \
	  ../../includes/irsdefs.h
	@rm -f hash_cond_print_by_type.i
	$$irs_pre hash_cond_print_by_type.c >> hash_cond_print_by_type.i
	@mv -f hash_cond_print_by_type.i $(PREDIR)/hash_cond_print_by_type.inst.i

$(PREDIR)/hash_del.inst.i:hash_del.c ../../includes/irsdefs.h                     \
	  ../../includes/Hash.h ../../includes/irsdefs.h
	@rm -f hash_del.i
	$$irs_pre hash_del.c >> hash_del.i
	@mv -f hash_del.i $(PREDIR)/hash_del.inst.i

$(PREDIR)/hash_del2.inst.i:hash_del2.c ../../includes/irsdefs.h                   \
	  ../../includes/Hash.h ../../includes/irsdefs.h
	@rm -f hash_del2.i
	$$irs_pre hash_del2.c >> hash_del2.i
	@mv -f hash_del2.i $(PREDIR)/hash_del2.inst.i

$(PREDIR)/hash_del_objs_of_type.inst.i:hash_del_objs_of_type.c                    \
	  ../../includes/irsdefs.h ../../includes/Hash.h                          \
	  ../../includes/irsdefs.h
	@rm -f hash_del_objs_of_type.i
	$$irs_pre hash_del_objs_of_type.c >> hash_del_objs_of_type.i
	@mv -f hash_del_objs_of_type.i $(PREDIR)/hash_del_objs_of_type.inst.i

$(PREDIR)/hash_get_elm_list.inst.i:hash_get_elm_list.c ../../includes/irsdefs.h   \
	  ../../includes/Hash.h ../../includes/irsdefs.h
	@rm -f hash_get_elm_list.i
	$$irs_pre hash_get_elm_list.c >> hash_get_elm_list.i
	@mv -f hash_get_elm_list.i $(PREDIR)/hash_get_elm_list.inst.i

$(PREDIR)/hash_lookup_elm.inst.i:hash_lookup_elm.c ../../includes/irsdefs.h       \
	  ../../includes/Hash.h ../../includes/irsdefs.h
	@rm -f hash_lookup_elm.i
	$$irs_pre hash_lookup_elm.c >> hash_lookup_elm.i
	@mv -f hash_lookup_elm.i $(PREDIR)/hash_lookup_elm.inst.i

$(PREDIR)/hash_lookup_obj.inst.i:hash_lookup_obj.c ../../includes/irsdefs.h       \
	  ../../includes/Hash.h ../../includes/irsdefs.h
	@rm -f hash_lookup_obj.i
	$$irs_pre hash_lookup_obj.c >> hash_lookup_obj.i
	@mv -f hash_lookup_obj.i $(PREDIR)/hash_lookup_obj.inst.i

$(PREDIR)/hash_optimize.inst.i:hash_optimize.c ../../includes/irs.h               \
	  ../../includes/irsctl.h ../../includes/irsrgst.h ../../includes/Hash.h  \
	  ../../includes/FunctionTimer.h
	@rm -f hash_optimize.i
	$$irs_pre hash_optimize.c >> hash_optimize.i
	@mv -f hash_optimize.i $(PREDIR)/hash_optimize.inst.i

$(PREDIR)/hash_print.inst.i:hash_print.c ../../includes/irsdefs.h                 \
	  ../../includes/Hash.h ../../includes/irsdefs.h
	@rm -f hash_print.i
	$$irs_pre hash_print.c >> hash_print.i
	@mv -f hash_print.i $(PREDIR)/hash_print.inst.i

$(PREDIR)/hash_print_by_name.inst.i:hash_print_by_name.c ../../includes/irsdefs.h \
	  ../../includes/Hash.h ../../includes/irsdefs.h
	@rm -f hash_print_by_name.i
	$$irs_pre hash_print_by_name.c >> hash_print_by_name.i
	@mv -f hash_print_by_name.i $(PREDIR)/hash_print_by_name.inst.i

$(PREDIR)/hash_print_by_type.inst.i:hash_print_by_type.c ../../includes/irsdefs.h \
	  ../../includes/Hash.h ../../includes/irsdefs.h
	@rm -f hash_print_by_type.i
	$$irs_pre hash_print_by_type.c >> hash_print_by_type.i
	@mv -f hash_print_by_type.i $(PREDIR)/hash_print_by_type.inst.i

$(PREDIR)/hash_print_obj.inst.i:hash_print_obj.c ../../includes/irs.h             \
	  ../../includes/irsdefs.h ../../includes/irsdefs.h                       \
	  ../../includes/irsrgst.h ../../includes/CycleMesg.h                     \
	  ../../includes/FreqMesg.h ../../includes/Hash.h                         \
	  ../../includes/TimePlot.h
	@rm -f hash_print_obj.i
	$$irs_pre hash_print_obj.c >> hash_print_obj.i
	@mv -f hash_print_obj.i $(PREDIR)/hash_print_obj.inst.i

$(PREDIR)/hash_print_structs_of_type.inst.i:hash_print_structs_of_type.c          \
	  ../../includes/irsdefs.h ../../includes/Hash.h                          \
	  ../../includes/irsdefs.h
	@rm -f hash_print_structs_of_type.i
	$$irs_pre hash_print_structs_of_type.c >> hash_print_structs_of_type.i
	@mv -f hash_print_structs_of_type.i $(PREDIR)/hash_print_structs_of_type.inst.i

$(PREDIR)/hash_sort_array.inst.i:hash_sort_array.c ../../includes/irsdefs.h       \
	  ../../includes/Hash.h ../../includes/irsdefs.h
	@rm -f hash_sort_array.i
	$$irs_pre hash_sort_array.c >> hash_sort_array.i
	@mv -f hash_sort_array.i $(PREDIR)/hash_sort_array.inst.i

$(PREDIR)/hash_sort_array_by_type.inst.i:hash_sort_array_by_type.c                \
	  ../../includes/irsdefs.h ../../includes/Hash.h                          \
	  ../../includes/irsdefs.h
	@rm -f hash_sort_array_by_type.i
	$$irs_pre hash_sort_array_by_type.c >> hash_sort_array_by_type.i
	@mv -f hash_sort_array_by_type.i $(PREDIR)/hash_sort_array_by_type.inst.i

$(PREDIR)/hash_tbl_create.inst.i:hash_tbl_create.c ../../includes/irsdefs.h       \
	  ../../includes/Hash.h ../../includes/irsdefs.h
	@rm -f hash_tbl_create.i
	$$irs_pre hash_tbl_create.c >> hash_tbl_create.i
	@mv -f hash_tbl_create.i $(PREDIR)/hash_tbl_create.inst.i

$(PREDIR)/hash_tbl_free.inst.i:hash_tbl_free.c ../../includes/irsdefs.h           \
	  ../../includes/Hash.h ../../includes/irsdefs.h
	@rm -f hash_tbl_free.i
	$$irs_pre hash_tbl_free.c >> hash_tbl_free.i
	@mv -f hash_tbl_free.i $(PREDIR)/hash_tbl_free.inst.i

$(PREDIR)/printhash.inst.i:printhash.c ../../includes/irs.h                       \
	  ../../includes/irsrgst.h ../../includes/irsrgst.h                       \
	  ../../includes/irsctl.h ../../includes/Hash.h
	@rm -f printhash.i
	$$irs_pre printhash.c >> printhash.i
	@mv -f printhash.i $(PREDIR)/printhash.inst.i

$(PREDIR)/strsave.inst.i:strsave.c ../../includes/irs.h ../../includes/irsdefs.h  \
	  ../../includes/Hash.h ../../includes/irsdefs.h
	@rm -f strsave.i
	$$irs_pre strsave.c >> strsave.i
	@mv -f strsave.i $(PREDIR)/strsave.inst.i

#-----------------------------------------------------------
# post-process files and create library from .i files 
#-----------------------------------------------------------
postprocess:libhash_inst

libhash_inst:$(BI)(get_num_elms_in_hashtable.inst.o) $(BI)(hash_add.inst.o)       \
	  $(BI)(hash_analyze.inst.o) $(BI)(hash_cond_print_by_type.inst.o)        \
	  $(BI)(hash_del.inst.o) $(BI)(hash_del2.inst.o)                          \
	  $(BI)(hash_del_objs_of_type.inst.o) $(BI)(hash_get_elm_list.inst.o)     \
	  $(BI)(hash_lookup_elm.inst.o) $(BI)(hash_lookup_obj.inst.o)             \
	  $(BI)(hash_optimize.inst.o) $(BI)(hash_print.inst.o)                    \
	  $(BI)(hash_print_by_name.inst.o) $(BI)(hash_print_by_type.inst.o)       \
	  $(BI)(hash_print_obj.inst.o) $(BI)(hash_print_structs_of_type.inst.o)   \
	  $(BI)(hash_sort_array.inst.o) $(BI)(hash_sort_array_by_type.inst.o)     \
	  $(BI)(hash_tbl_create.inst.o) $(BI)(hash_tbl_free.inst.o)               \
	  $(BI)(printhash.inst.o) $(BI)(strsave.inst.o)
	  @if test -f object_file_flag; then  \
		(echo $$irs_ar ar $(BI) *.o; \
		$$irs_ar $(BI) *.o; \
		rm *.o object_file_flag; \
		echo ln -sf libhash_inst.a $(B); \
		ln -sf libhash_inst.a $(B)); \
	  fi
	  @echo 'libhash_inst library current'


#-------------------------------------------------------------------------------
# individual rules to compile .i files into .o files within instrumented library
#-------------------------------------------------------------------------------
$(BI)(get_num_elms_in_hashtable.inst.o):$(INSTDIR)/get_num_elms_in_hashtable.inst.i
	$$irs_post $(INSTDIR)/get_num_elms_in_hashtable.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/get_num_elms_in_hashtable.inst.i $(DB)/get_num_elms_in_hashtable.c 

$(BI)(hash_add.inst.o):$(INSTDIR)/hash_add.inst.i
	$$irs_post $(INSTDIR)/hash_add.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/hash_add.inst.i $(DB)/hash_add.c 

$(BI)(hash_analyze.inst.o):$(INSTDIR)/hash_analyze.inst.i
	$$irs_post $(INSTDIR)/hash_analyze.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/hash_analyze.inst.i $(DB)/hash_analyze.c 

$(BI)(hash_cond_print_by_type.inst.o):$(INSTDIR)/hash_cond_print_by_type.inst.i
	$$irs_post $(INSTDIR)/hash_cond_print_by_type.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/hash_cond_print_by_type.inst.i $(DB)/hash_cond_print_by_type.c 

$(BI)(hash_del.inst.o):$(INSTDIR)/hash_del.inst.i
	$$irs_post $(INSTDIR)/hash_del.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/hash_del.inst.i $(DB)/hash_del.c 

$(BI)(hash_del2.inst.o):$(INSTDIR)/hash_del2.inst.i
	$$irs_post $(INSTDIR)/hash_del2.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/hash_del2.inst.i $(DB)/hash_del2.c 

$(BI)(hash_del_objs_of_type.inst.o):$(INSTDIR)/hash_del_objs_of_type.inst.i
	$$irs_post $(INSTDIR)/hash_del_objs_of_type.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/hash_del_objs_of_type.inst.i $(DB)/hash_del_objs_of_type.c 

$(BI)(hash_get_elm_list.inst.o):$(INSTDIR)/hash_get_elm_list.inst.i
	$$irs_post $(INSTDIR)/hash_get_elm_list.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/hash_get_elm_list.inst.i $(DB)/hash_get_elm_list.c 

$(BI)(hash_lookup_elm.inst.o):$(INSTDIR)/hash_lookup_elm.inst.i
	$$irs_post $(INSTDIR)/hash_lookup_elm.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/hash_lookup_elm.inst.i $(DB)/hash_lookup_elm.c 

$(BI)(hash_lookup_obj.inst.o):$(INSTDIR)/hash_lookup_obj.inst.i
	$$irs_post $(INSTDIR)/hash_lookup_obj.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/hash_lookup_obj.inst.i $(DB)/hash_lookup_obj.c 

$(BI)(hash_optimize.inst.o):$(INSTDIR)/hash_optimize.inst.i
	$$irs_post $(INSTDIR)/hash_optimize.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/hash_optimize.inst.i $(DB)/hash_optimize.c 

$(BI)(hash_print.inst.o):$(INSTDIR)/hash_print.inst.i
	$$irs_post $(INSTDIR)/hash_print.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/hash_print.inst.i $(DB)/hash_print.c 

$(BI)(hash_print_by_name.inst.o):$(INSTDIR)/hash_print_by_name.inst.i
	$$irs_post $(INSTDIR)/hash_print_by_name.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/hash_print_by_name.inst.i $(DB)/hash_print_by_name.c 

$(BI)(hash_print_by_type.inst.o):$(INSTDIR)/hash_print_by_type.inst.i
	$$irs_post $(INSTDIR)/hash_print_by_type.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/hash_print_by_type.inst.i $(DB)/hash_print_by_type.c 

$(BI)(hash_print_obj.inst.o):$(INSTDIR)/hash_print_obj.inst.i
	$$irs_post $(INSTDIR)/hash_print_obj.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/hash_print_obj.inst.i $(DB)/hash_print_obj.c 

$(BI)(hash_print_structs_of_type.inst.o):$(INSTDIR)/hash_print_structs_of_type.inst.i
	$$irs_post $(INSTDIR)/hash_print_structs_of_type.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/hash_print_structs_of_type.inst.i $(DB)/hash_print_structs_of_type.c 

$(BI)(hash_sort_array.inst.o):$(INSTDIR)/hash_sort_array.inst.i
	$$irs_post $(INSTDIR)/hash_sort_array.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/hash_sort_array.inst.i $(DB)/hash_sort_array.c 

$(BI)(hash_sort_array_by_type.inst.o):$(INSTDIR)/hash_sort_array_by_type.inst.i
	$$irs_post $(INSTDIR)/hash_sort_array_by_type.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/hash_sort_array_by_type.inst.i $(DB)/hash_sort_array_by_type.c 

$(BI)(hash_tbl_create.inst.o):$(INSTDIR)/hash_tbl_create.inst.i
	$$irs_post $(INSTDIR)/hash_tbl_create.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/hash_tbl_create.inst.i $(DB)/hash_tbl_create.c 

$(BI)(hash_tbl_free.inst.o):$(INSTDIR)/hash_tbl_free.inst.i
	$$irs_post $(INSTDIR)/hash_tbl_free.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/hash_tbl_free.inst.i $(DB)/hash_tbl_free.c 

$(BI)(printhash.inst.o):$(INSTDIR)/printhash.inst.i
	$$irs_post $(INSTDIR)/printhash.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/printhash.inst.i $(DB)/printhash.c 

$(BI)(strsave.inst.o):$(INSTDIR)/strsave.inst.i
	$$irs_post $(INSTDIR)/strsave.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/strsave.inst.i $(DB)/strsave.c 

DEP_SRCS = \
	get_num_elms_in_hashtable.c hash_add.c hash_analyze.c hash_cond_print_by_type.c  \
	hash_del.c hash_del2.c hash_del_objs_of_type.c hash_get_elm_list.c hash_lookup_elm.c  \
	hash_lookup_obj.c hash_optimize.c hash_print.c hash_print_by_name.c hash_print_by_type.c  \
	hash_print_obj.c hash_print_structs_of_type.c hash_sort_array.c hash_sort_array_by_type.c  \
	hash_tbl_create.c hash_tbl_free.c printhash.c strsave.c  

depend:
	@cp -f Makefile.hash Makefile
	makedepend -- $(DEPFLAGS) -- $(DEP_SRCS)
	irs_fixdepend Makefile

