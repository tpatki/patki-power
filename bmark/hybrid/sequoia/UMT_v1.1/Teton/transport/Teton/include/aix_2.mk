#
# AIX v2.x UNIX commands and definitions for use by make
#

# Fortran90 compiler definitions
SerialF90     := xlf90
PThreadF90    := xlf90_r
MPIF90        := mpxlf90
MPIPThreadF90 := mpxlf90_r

# C compiler definitions
SerialCC     := cc
PThreadCC    := cc_r
MPICC        := mpcc
MPIPThreadCC := mpcc_r

# Local Fortran compiler optimize, debug and profile flags
LocalOptFFlags := -O4 -qhot=arraypad -qarch=auto -qtune=604 -qnosave \
                  -bmaxdata:500000000 -qflttrap=over:under:zero:impr
LocalDebugFFlags := -C -qfullpath -qnosave \
                    -bmaxdata:500000000 -qflttrap=over:under:zero:impr
LocalProfileFFlags := -pg -qnosave \
                      -bmaxdata:500000000 -qflttrap=over:under:zero:impr

# Local C compiler optimize, debug and profile flags
LocalOptCFlags := -O
LocalDebugCFlags := 
LocalProfileCFlags := -pg

# Local compiler free-format with cpp directives flags
FreeFormFlags := -qfree=f90 -qsuffix=cpp=f90

# Local compiler fixed-format with cpp directives & 132-column lines
FixedFormFlags := -qfixed=132 -qsuffix=cpp=f

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

LocalDef := -DIBM_
LocalLib := 
LocalInc :=
LocalMod :=

# Local MPI, PThreads, and SILO directories

LocalMPILib :=
LocalMPIInc :=
LocalMPIMod :=
LocalMPIFFlags :=
LocalMPICFlags :=

LocalPThreadsLib := -lxlsmp
LocalPThreadsInc :=
LocalPThreadsMod :=
LocalPThreadsFFlags := -qsmp=noauto
LocalPThreadsCFlags :=

LocalSILOLib := -L/usr/local/apps/lib -lsilo
LocalSILOInc := -I/usr/local/apps/include
LocalSILOMod :=
LocalSILOFFlags :=
LocalSILOCFlags :=

# Construct the pre-processor and Fortran90 flags and pass to sub-make
#   CppFlags -- C pre-processor flags for C compiler and makedepend
#   F90Flags -- Fortran90 pre-processor and module flags for Fortran90
#               compiler.  Syntax:
#                 defined variables:    -WF,-DFOO,-DBAR
#                 include directories:  -WF,-I.,-I../include
#                 module directories:   -I. -I../mods

CppFlags = $(Def) $(Inc)
F90Flags = -WF,$(subst $(space),$(comma),$(strip $(Def))) \
           -WF,$(subst $(space),$(comma),$(strip $(Inc))) \
           $(Mod)
export CppFlags F90Flags
