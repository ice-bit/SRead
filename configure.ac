#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([sread], [0.3])
AM_INIT_AUTOMAKE
AC_PROG_RANLIB

# Checks for programs.
AC_LANG(C)
AC_PROG_CC

# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([fcntl.h stdlib.h string.h termios.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_SIZE_T
AC_TYPE_SSIZE_T

# Checks for library functions.
AC_CHECK_FUNCS([memset strerror])
AC_CONFIG_FILES([Makefile include/Makefile src/Makefile])
AC_OUTPUT
