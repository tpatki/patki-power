
How to use the new make system:

        When you setup your build space with irs_setup you will now
find some new stuff in the build directory.   There is a Makefile.header
which contains some basic stuff that will end up in the master makefile.
In addition to that, there is a Makefile.targets which has all of the
machine-independent targets.  There are now only four targets in that
file and we should resist adding more:

                opt:    builds the optimized code
                debug:  builds the debug code
                lint:   runs lint on the code
                gcc:    runs gcc as a syntax checker on the code

You will also find an arch directory under the build directory.  Within that
directory are the architecture specific files which contain all of the
appropriate compiler flags, lib paths, etc. for that platform.  Each
platform has its default setting.  If you wish modify the defaults
(eg. link with gang scheduling turned off) you can modify the master
Makefile after it is built.

The master makefile is built by a script called irs_config.  Go into the
build directory and run irs_config.  This will list all of the available
machine dependent configurations.  To build the master makefile just
run irs_config followed by your configuration of choice.  You need only
run irs_config if any of the makefile template files change or you are
moving to a new platform.


