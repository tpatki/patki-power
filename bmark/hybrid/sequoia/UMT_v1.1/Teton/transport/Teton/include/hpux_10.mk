#
# HP-UX 10.x UNIX commands and definitions for use by make
#

# Fortran90 compiler definitions
SerialF90     := f90
PThreadF90    := f90
MPIF90        := f90
MPIPThreadF90 := f90

# C compiler definitions
SerialCC     := cc
PThreadCC    := cc
MPICC        := cc
MPIPThreadCC := cc

# Local compiler optimize, debug and profile flags
LocalOptFFlags := -O
LocalDebugFFlags :=
LocalProfileFFlags := +gprof

# Local C compiler optimize, debug and profile flags
LocalOptCFlags := -O
LocalDebugCFlags := 
LocalProfileCFlags := -G

# Local compiler free-format with cpp directives flags
FreeFormFlags := +source=free +cpp=yes

# Local compiler fixed-format with cpp directives flags
FixedFormFlags := +source=fixed +cpp=yes

# Suffix applied by the compiler to module files
ModSuffix := mod

# Local compiler module directory search path flag
ModDirSearch := -I

# Convert archives to random libraries
ranlib := ranlib

# make dependencies in Makefiles
makedepend := /usr/bin/X11/makedepend

# Pass commands and flags to sub-make
export SerialF90 PThreadF90 MPIF90 MPIPThreadF90
export SerialCC PThreadCC MPICC MPIPThreadCC
export FreeFormFlags FixedFormFlags ModSuffix
export rmdir RmdirFlags ranlib makedepend

# Local Defines, Library, Include and Module directories

LocalDef := -DHP_
LocalLib :=
LocalInc :=
LocalMod :=

# Local MPI, PThreads, and SILO directories

LocalMPILib :=
LocalMPIInc :=
LocalMPIMod :=
LocalMPIFFlags :=
LocalMPICFlags :=

LocalPThreadsLib :=
LocalPThreadsInc :=
LocalPThreadsMod :=
LocalPThreadsFFlags :=
LocalPThreadsCFlags :=

LocalSILOLib :=
LocalSILOInc :=
LocalSILOMod :=
LocalSILOFFlags :=
LocalSILOCFlags :=

# Construct the pre-processor and Fortran90 flags and pass to sub-make
#   CppFlags -- C pre-processor flags for C compiler and makedepend
#   F90Flags -- Fortran90 pre-processor and module flags for Fortran90
#               compiler.  Syntax:
#                 defined variables:    -DFOO -DBAR
#                 include directories:  -I. -I../include
#                 module directories:   -I. -I../mods

CppFlags = $(Def) $(Inc)
F90Flags = $(Def) $(Inc) $(Mod)
export CppFlags F90Flags
