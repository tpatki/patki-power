#
# Pattern Rule Makefile for TETON
#   These are the `standard' pattern rules are required to build TETON.
#   They are machine-dependent due to irreconcilable differences among
#   the various support operating systems.

#      +-------------------------------------------------------+
#      |  Nothing Below This Line Should Require Modification  |
#      +-------------------------------------------------------+

# Module and object files from free-format Fortran90 module source
#   o Sun compiler produces a module file name based on the intermediate
#     preprocessed file name.
#   o IRIX compiler produces a module file name based on the module
#     file name in all upper case.
#   Rename the module file to correspond with the module source file.
#   GNU Make does not have a case statement (yet); the if structure
#   is a bit of a kludge.

%_mod.$(ModSuffix) %_mod.o: %_mod.f90
    ifeq ($(MachineOS),SunOS 5)
	@$(rm) $(RmFlags) .$*_mod.F90
	$(cp) $*_mod.f90 .$*_mod.F90 
	$(F90) $(FFLAGS) $(F90Flags) $(FreeFormFlags) \
	  -o $(RelObjDir)/$*_mod.o -c .$*_mod.F90 
	-$(mv) `ls fpp.*.?.$(ModSuffix)` $*_mod.$(ModSuffix)
    else
    ifeq ($(MachineOS),IRIX64 6)
	$(F90) $(FFLAGS) $(F90Flags) $(FreeFormFlags) \
	  -o $(RelObjDir)/$*_mod.o -c $<
	-$(mv) $(shell echo $*_mod | \
	  $(tr) "[a-z]" "[A-Z]").$(ModSuffix) $*_mod.$(ModSuffix)
    else
	$(F90) $(FFLAGS) $(F90Flags) $(FreeFormFlags) \
	  -o $(RelObjDir)/$*_mod.o -c $<
    endif
    endif

# Module and object files from fixed-format Fortran90 module source
#   o Sun compiler produces a module file name based on the intermediate
#     preprocessed file name.
#   o IRIX compiler produces a module file name based on the module
#     file name in all upper case.
#   Rename the module file to correspond with the module source file.
#   GNU Make does not have a case statement (yet); the if structure
#   is a bit of a kludge.

%_mod.$(ModSuffix) %_mod.o: %_mod.f
    ifeq ($(MachineOS),SunOS 5)
	@$(rm) $(RmFlags) .$*_mod.F
	$(cp) $*_mod.f .$*_mod.F
	$(F90) $(FFLAGS) $(F90Flags) $(FixedFormFlags) \
	  -o $(RelObjDir)/$*_mod.o -c .$*_mod.F
	-$(mv) $(wildcard fpp.*.?.$(ModSuffix)) $*_mod.$(ModSuffix)
    else
    ifeq ($(MachineOS),IRIX64 6)
	$(F90) $(FFLAGS) $(F90Flags) $(FreeFormFlags) \
	  -o $(RelObjDir)/$*_mod.o -c $<
	-$(mv) $(shell echo $*_mod | \
	  $(tr) "[a-z]" "[A-Z]").$(ModSuffix) $*_mod.$(ModSuffix)
    else
	$(F90) $(FFLAGS) $(F90Flags) $(FixedFormFlags) \
	  -o $(RelObjDir)/$*_mod.o -c $<
    endif
    endif

# Object file from free-format Fortran90 source
#   Sun compiler requires a .F90 suffix for preprocessing, all other
#   platforms allow for a command-line option.

%.o: %.f90
    ifeq ($(MachineOS),SunOS 5)
	@$(rm) $(RmFlags) .$*.F90
	$(cp) $*.f90 .$*.F90
	$(F90) $(FFLAGS) $(F90Flags) $(FreeFormFlags) \
	  -o $(RelObjDir)/$@ -c .$*.F90
    else
	$(F90) $(FFLAGS) $(F90Flags) $(FreeFormFlags) \
	  -o $(RelObjDir)/$@ -c $<
    endif

# Object file from fixed-format Fortran90 source
#   Sun compiler requires a .F suffix for preprocessing, all other
#   platforms allow for a command-line option.

%.o: %.f
    ifeq ($(MachineOS),SunOS 5)
	@$(rm) $(RmFlags) .$*.F
	$(cp) $*.f .$*.F
	$(F90) $(FFLAGS) $(F90Flags) $(FixedFormFlags) \
	  -o $(RelObjDir)/$@ -c .$*.F
    else
	$(F90) $(FFLAGS) $(F90Flags) $(FixedFormFlags) \
	  -o $(RelObjDir)/$@ -c $<
    endif

# Object file from C source

%.o: %.c
	$(CC) -o $(RelObjDir)/$@ $(CppFlags) $(CFLAGS) -c $<
