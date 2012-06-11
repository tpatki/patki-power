#
# Standard UNIX commands and definitions for use by make
#

# Remove command and flags
rm := rm
RmFlags := -f

# Create a portable archive command
ar := ar
ArFlags := -rv

# Tape archive command and flags
tar := tar
TarFlags := -cvf

# Concatenate a file
cat := cat

# Copy command
cp := cp

# Create links
ln := ln

# Make directories
mkdir := mkdir

# Move command
mv := mv

# Stream editor
sed := sed

# Touch command to update access time of a file
touch := touch

# Translate characters
tr := tr

# Pass commands and flags to sub-make
export rm RmFlags ar ArFlags tar TarFlags cat cp ln mkdir mv sed touch tr

# Standard useful variables
comma := ,
empty :=
space := $(empty) $(empty)
export comma space

# Standard Defines, Library, Module and Include directories

StdDef = 
StdLib = $(RelativePath)/objs/$(ObjDir)/*.o
StdInc = -I. \
         $(addprefix -I$$(RelativePath)/, $(IncDirs))
StdMod = $(ModDirSearch). \
         $(addprefix $(ModDirSearch)$$(RelativePath)/, $(ModDirs))
