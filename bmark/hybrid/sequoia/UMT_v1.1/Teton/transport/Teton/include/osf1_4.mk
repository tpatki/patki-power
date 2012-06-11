#
# OSF/1 v4 UNIX commands and definitions for use by make
#

# Fortran90 compiler definitions
SerialF90     := newf90
PThreadF90    := newf90
MPIF90        := newf90
MPIPThreadF90 := newf90

# C compiler definitions
SerialCC     := cc
PThreadCC    := cc
MPICC        := cc
MPIPThreadCC := cc

# Local compiler optimize, debug and profile flags
LocalOptFFlags := -fast -O4 -automatic -arch host -tune host
LocalDebugFFlags := -C -check overflow  
LocalProfileFFlags := -pg

# Local C compiler optimize, debug and profile flags
LocalOptCFlags := -O
LocalDebugCFlags := 
LocalProfileCFlags := -pg

# Local compiler free-format with cpp directives flags
FreeFormFlags := -free -cpp

# Local compiler fixed-format with cpp directives & 132-column lines
# (the -extend_source flag implies -fixed)
FixedFormFlags := -extend_source -cpp

# Suffix applied by the compiler to module files
ModSuffix := mod

# Local compiler module directory search path flag
ModDirSearch := -I

# Remove directory and flags
rmdir := rmdir
RmdirFlags := -p

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

LocalDef := -DDEC_
LocalLib := /usr/local/apps/lib/libpdb.a \
            /usr/local/apps/lib/libscore.a \
            /usr/local/apps/lib/libpml.a
LocalInc :=
LocalMod :=

# Local METIS, MPI, PThreads, and SILO directories

LocalMETISLib := -L/usr/local/apps/lib -lmetis 
LocalMETISInc :=
LocalMETISMod :=

LocalMPILib := -L/usr/local/mpich-1.1/lib/alpha/ch_shmem -lmpich -lgs -lrt
LocalMPIInc :=
LocalMPIMod :=
LocalMPIFFlags :=
LocalMPICFlags :=

LocalPThreadsLib := 
LocalPThreadsInc :=
LocalPThreadsMod :=
LocalPThreadsFFlags := -omp -pthread -reentrancy threaded
LocalPThreadsCFlags :=

LocalSILOLib := -L/usr/local/apps/lib -lsilo
LocalSILOInc := -I/usr/local/apps/include
LocalSILOMod :=
LocalSILOFFlags :=
LocalSILOCFlags :=

LocalUnderFlowFFlags := -check underflow
LocalUnderFlowCFlags := -fptm u

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
