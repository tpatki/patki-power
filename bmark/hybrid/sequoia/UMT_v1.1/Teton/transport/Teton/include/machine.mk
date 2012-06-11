#
# Machine-specific control Makefile for TETON
#

# Determine the Machine Operating System

SystemName := $(shell uname -s)
ifeq ($(SystemName),HP-UX)
  MajorOSVersion := $(word 2,$(subst ., ,$(shell uname -r)))
else
  MajorOSVersion := $(word 1,$(subst ., ,$(shell uname -r)))
endif

MachineOS := $(strip $(SystemName) $(MajorOSVersion))

# DEC OSF/1
ifeq ($(MachineOS),OSF1 V4)
  include include/osf1_4.mk
endif

# HP HP-UX 10
ifeq ($(MachineOS),HP-UX 10)
  include include/hpux_10.mk
endif

# IBM AIX 2
ifeq ($(MachineOS),AIX 2)
  include include/aix_2.mk
endif

# IBM AIX 3
ifeq ($(MachineOS),AIX 3)
  include include/aix_3.mk
endif

# SGI IRIX64
ifeq ($(MachineOS),IRIX64 6)
  include include/irix64_6.mk
endif

# Sun Solaris 2.x
ifeq ($(MachineOS),SunOS 5)
  include include/solaris_2.mk
endif

# CRAY J90
#   uname on UNICOS 9.x is pretty useless: "uname -s" returns the
#   nodename rather than the operating system name.  The following
#   block of code uses the hardware name to allow for the J90's.
HardwareName := $(firstword $(shell uname -m))

ifeq ($(HardwareName),CRAY)
  MachineOS := $(strip UNICOS $(MajorOSVersion))
endif

ifeq ($(MachineOS),UNICOS 9)
  include include/unicos_9.mk
endif

export MachineOS
