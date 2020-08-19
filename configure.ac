#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([FGlT], [1.00], [fcdimitr@cs.duke.edu])
AM_INIT_AUTOMAKE([-Wall, foreign])
AC_CONFIG_HEADERS([config.h])

AC_CONFIG_LINKS([lib/fglt.hpp:lib/fglt.hpp])

printf "\nSetup language to C++\n\n"

# Switch to a C++ compiler, and check if it works.
AC_LANG(C++)

# Checks for programs.
AC_PROG_CXX

# Library
AC_PROG_RANLIB
AM_PROG_AR

# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([stdlib.h sys/time.h])
dnl AC_CHECK_HEADERS(cilk/cilk.h, [], [AC_ERROR([A working Cilk installation is required])])
AC_CHECK_HEADERS(cilk/cilk.h, [CXXFLAGS="${CXXFLAGS} -fcilkplus"], [])

# Checks for typedefs, structures, and compiler characteristics.
AC_CHECK_HEADER_STDBOOL
AC_TYPE_SIZE_T

# Checks for library functions.
AC_CHECK_FUNCS([gettimeofday])

AC_CONFIG_FILES([Makefile
                 lib/Makefile
                 src/Makefile])
AC_OUTPUT
