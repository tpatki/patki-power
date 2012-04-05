dnl Configure SWEEP3D
dnl By Scott Pakin <pakin@lanl.gov>

dnl Initialize Autoconf.
AC_PREREQ(2.53)
AC_REVISION($Revision: $)
AC_INIT([SWEEP3D], [2.2b], [pakin@lanl.gov], [sweep3d])
AC_CONFIG_SRCDIR([msg_stuff.cpp])

dnl Initialize Automake.
AM_INIT_AUTOMAKE([1.6])
AM_CONFIG_HEADER([config.h])

dnl Look for programs that we need.
AC_PROG_F77
AC_PROG_CC
AC_PROG_CPP

dnl Ensure that cpp works.
AC_CACHE_CHECK([if cpp works as expected],
  [ax_cv_prog_cpp_works],
  [ax_cv_prog_cpp_works=no
   cat <<TESTCPP > conftest.cpp
#define QUUX baz
Hello FOO QUUX
TESTCPP
   if test `$CPP -E -DFOO=bar -P conftest.cpp | egrep -c "Hello bar baz"` -eq 1 ; then
     ax_cv_prog_cpp_works=yes
   fi])
if test $ax_cv_prog_cpp_works != yes ; then
  AC_MSG_ERROR([Using "$CPP" as the C preprocessors doesn't work as expected; try setting CPP to a different program (e.g., CPP="cpp")])
fi

dnl See if we should use PVM.
AC_ARG_WITH([pvm],
  [AC_HELP_STRING([--with-pvm], [parallelize using PVM])],
  [use_PVM=yes
   CPPFLAGS="$CPPFLAGS -DPVM"
   AC_CHECK_LIB([fpvm3], [main])
   AC_CHECK_LIB([pvm3], [main])
   AC_CHECK_LIB([gpvm3], [main])])

dnl See if we should use MPI.
AC_ARG_WITH([mpi],
  [AC_HELP_STRING([--with-mpi], [parallelize using MPI])],
  [use_MPI=yes
   CPPFLAGS="$CPPFLAGS -DMPI"
   AC_CHECK_LIB([mpi], [main])])

dnl Complain if we were told to use both PVM and MPI.
if test "$use_PVM" = yes -a "$use_MPI" = yes ; then
  AC_MSG_ERROR([--with-pvm and --with-mpi are mutually exclusive])
fi

dnl Summarize key configuration variables.
if test "$use_MPI" = yes ; then
  buildtype="parallel (MPI)"
elif test "$use_PVM" = yes ; then
  buildtype="parallel (PVM)"
else
  buildtype=sequential
fi
cat <<SHOWENV

   Build type: $buildtype

   F77       = $F77
   FFLAGS    = $FFLAGS
   CPP       = $CPP
   CC        = $CC

SHOWENV
if test "$buildtype" = sequential ; then
  AC_MSG_WARN([sequential build; specify --with-mpi or --with-pvm to build the parallel version of Sweep3D])
fi
if test -z "$FFLAGS" ; then
  AC_MSG_WARN([FFLAGS is empty; optimizations might be disabled])
fi

dnl Create a customized Makefile.
AC_CONFIG_FILES([Makefile])
AC_OUTPUT
