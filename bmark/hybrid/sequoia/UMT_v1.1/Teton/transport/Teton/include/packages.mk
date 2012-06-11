#
# Packages Makefile for TETON
#   This Makefile determines what packages were requested and constructs
#   the appropriate defines and library, include and module directories.

#      +-------------------------------------------------------+
#      |  Nothing Below This Line Should Require Modification  |
#      +-------------------------------------------------------+

# Package Options
PackageFile = $(RelativePath)/objs/$(ObjDir)/packages.mk

# The with-package and without-package variables should be parsed on the
# first pass through the Makefile only.

ifeq (0,$(MAKELEVEL))

# Define the default status of each package: "+" for on, "-" for off

  DefaultPackages := +METIS  +MPI +PThreads +SILO \
                     -UnderFlow +Assert -AssertMesh

# Transform the with-package variable to an all lower case version,
# WithPackage, so that the command-line option is NOT case-sensitive

WithPackage := $(strip \
       $(subst A,a, $(subst B,b, $(subst C,c, $(subst D,d, \
       $(subst E,e, $(subst F,f, $(subst G,g, $(subst H,h, \
       $(subst I,i, $(subst J,j, $(subst K,k, $(subst L,l, \
       $(subst M,m, $(subst N,n, $(subst O,o, $(subst P,p, \
       $(subst Q,q, $(subst R,r, $(subst S,s, $(subst T,t, \
       $(subst U,u, $(subst V,v, $(subst W,w, $(subst X,x, \
       $(subst Y,y, $(subst Z,z, \
       $(with-package) )))))))))))))))))))))))))) )

# Transform the without-package variable to an all lower case version,
# WithoutPackage, so that the command-line option is NOT case-sensitive

WithoutPackage := $(strip \
       $(subst A,a, $(subst B,b, $(subst C,c, $(subst D,d, \
       $(subst E,e, $(subst F,f, $(subst G,g, $(subst H,h, \
       $(subst I,i, $(subst J,j, $(subst K,k, $(subst L,l, \
       $(subst M,m, $(subst N,n, $(subst O,o, $(subst P,p, \
       $(subst Q,q, $(subst R,r, $(subst S,s, $(subst T,t, \
       $(subst U,u, $(subst V,v, $(subst W,w, $(subst X,x, \
       $(subst Y,y, $(subst Z,z, \
       $(without-package) )))))))))))))))))))))))))) )

# Set the packages variable

  Packages :=

# METIS Package
  ifneq (,$(findstring metis,$(WithoutPackage)))
    Packages += -METIS
  else
    ifneq (,$(findstring metis,$(WithPackage)))
      Packages += +METIS
    else
      ifneq (,$(findstring all,$(WithoutPackage)))
        Packages += -METIS
      else
        ifneq (,$(findstring all,$(WithPackage)))
          Packages += +METIS
        else
          Packages += $(filter %METIS,$(DefaultPackages))
        endif
      endif
    endif
  endif

# MPI Package
  ifneq (,$(findstring mpi,$(WithoutPackage)))
    Packages += -MPI
  else
    ifneq (,$(findstring mpi,$(WithPackage)))
      Packages += +MPI
    else
      ifneq (,$(findstring all,$(WithoutPackage)))
        Packages += -MPI
      else
        ifneq (,$(findstring all,$(WithPackage)))
          Packages += +MPI
        else
          Packages += $(filter %MPI,$(DefaultPackages))
        endif
      endif
    endif
  endif

# PThreads Package
  ifneq (,$(findstring pthreads,$(WithoutPackage)))
    Packages += -PThreads
  else
    ifneq (,$(findstring pthreads,$(WithPackage)))
      Packages += +PThreads
    else
      ifneq (,$(findstring all,$(WithoutPackage)))
        Packages += -PThreads
      else
        ifneq (,$(findstring all,$(WithPackage)))
          Packages += +PThreads
        else
          Packages += $(filter %PThreads,$(DefaultPackages))
        endif
      endif
    endif
  endif

# SILO Package
  ifneq (,$(findstring silo,$(WithoutPackage)))
    Packages += -SILO
  else
    ifneq (,$(findstring silo,$(WithPackage)))
      Packages += +SILO
    else
      ifneq (,$(findstring all,$(WithoutPackage)))
        Packages += -SILO
      else
        ifneq (,$(findstring all,$(WithPackage)))
          Packages += +SILO
        else
          Packages += $(filter %SILO,$(DefaultPackages))
        endif
      endif
    endif
  endif

# UnderFlow Package
  ifneq (,$(findstring underflow,$(WithoutPackage)))
    Packages += -UnderFlow
  else
    ifneq (,$(findstring underflow,$(WithPackage)))
      Packages += +UnderFlow
    else
      ifneq (,$(findstring all,$(WithoutPackage)))
        Packages += -UnderFlow
      else
        ifneq (,$(findstring all,$(WithPackage)))
          Packages += +UnderFlow
        else
          Packages += $(filter %UnderFlow,$(DefaultPackages))
        endif
      endif
    endif
  endif

# Assertion Package
  ifneq (,$(findstring assert,$(WithoutPackage)))
    Packages += -Assert
  else
    ifneq (,$(findstring assert,$(WithPackage)))
      Packages += +Assert
    else
      ifneq (,$(findstring all,$(WithoutPackage)))
        Packages += -Assert
      else
        ifneq (,$(findstring all,$(WithPackage)))
          Packages += +Assert
        else
          Packages += $(filter %Assert,$(DefaultPackages))
        endif
      endif
    endif
  endif

# Mesh Assertion Package
  ifneq (,$(findstring assertmesh,$(WithoutPackage)))
    Packages += -AssertMesh
  else
    ifneq (,$(findstring assertmesh,$(WithPackage)))
      Packages += +AssertMesh
    else
      ifneq (,$(findstring all,$(WithoutPackage)))
        Packages += -AssertMesh
      else
        ifneq (,$(findstring all,$(WithPackage)))
          Packages += +AssertMesh
        else
          Packages += $(filter %AssertMesh,$(DefaultPackages))
        endif
      endif
    endif
  endif

  export Packages

endif

# Define the necessary compiler based on the requested packages

# Serial Compiler
ifneq (,$(findstring -MPI,$(Packages)))
  ifneq (,$(findstring -PThreads,$(Packages)))
    F90 := $(SerialF90)
    CC := $(SerialCC)
  endif
endif

# PThreads Compiler
ifneq (,$(findstring -MPI,$(Packages)))
  ifneq (,$(findstring +PThreads,$(Packages)))
    F90 := $(PThreadF90)
    CC := $(PThreadCC)
  endif
endif

# MPI Compiler
ifneq (,$(findstring +MPI,$(Packages)))
  ifneq (,$(findstring -PThreads,$(Packages)))
    F90 := $(MPIF90)
    CC := $(MPICC)
  endif
endif

# MPI/PThreads Compiler
ifneq (,$(findstring +MPI,$(Packages)))
  ifneq (,$(findstring +PThreads,$(Packages)))
    F90 := $(MPIPThreadF90)
    CC := $(MPIPThreadCC)
  endif
endif

export F90 CC

# Construct the package-dependent defines and library, include and
# module directories

PackageDef :=
PackageLib :=
PackageInc :=
PackageMod :=
PackageFFlags :=
PackageCFlags :=

# METIS Package
ifneq (,$(findstring +METIS,$(Packages)))
  PackageDef += -DMETIS
  PackageLib += $(LocalMETISLib)
  PackageInc += $(LocalMETISInc)
  PackageMod += $(LocalMETISMod)
endif

# MPI Package
ifneq (,$(findstring +MPI,$(Packages)))
  PackageDef += -DMPI
  PackageLib += $(LocalMPILib)
  PackageInc += $(LocalMPIInc)
  PackageMod += $(LocalMPIMod)
  PackageFFlags += $(LocalMPIFFlags)
  PackageCFlags += $(LocalMPICFlags)
endif

# PThreads Package
ifneq (,$(findstring +PThreads,$(Packages)))
  PackageDef += -DPTHREADS
  PackageLib += $(LocalPThreadsLib)
  PackageInc += $(LocalPThreadsInc)
  PackageMod += $(LocalPThreadsMod)
  PackageFFlags += $(LocalPThreadsFFlags)
  PackageCFlags += $(LocalPThreadsCFlags)
endif

# PThreads Package
ifneq (,$(findstring +SILO,$(Packages)))
  PackageDef += -DSILO
  PackageLib += $(LocalSILOLib)
  PackageInc += $(LocalSILOInc)
  PackageMod += $(LocalSILOMod)
  PackageFFlags += $(LocalSILOFFlags)
  PackageCFlags += $(LocalSILOCFlags)
endif

# UnderFlow Package
ifneq (,$(findstring +UnderFlow,$(Packages)))
  PackageDef += -DUNDERFLOW
  PackageFFlags += $(LocalUnderFlowFFlags)
  PackageCFlags += $(LocalUnderFlowCFlags)
endif

# Assertion Package
ifneq (,$(findstring +Assert,$(Packages)))
   PackageDef += -DASSERT
endif

# Mesh Assertion Package
ifneq (,$(findstring +AssertMesh,$(Packages)))
   PackageDef += -DASSERT_MESH
endif
