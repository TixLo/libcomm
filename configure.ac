AC_PREREQ([2.65])
AC_INIT(libcomm, 1.0, https://github.com/TixLo/CommServer)
AM_INIT_AUTOMAKE()
#AM_INIT_AUTOMAKE([subdir-objects])
AC_CONFIG_SRCDIR([src])
AC_CONFIG_HEADERS([config.h])

AC_CHECK_HEADER([sys/sockio.h])
AC_CHECK_HEADER([openssl/ssl.h])
AC_CHECK_HEADER([event2/event.h])
 
# Checks for programs.
AC_PROG_CC
AC_PROG_CXX
# AC_HEADER_STDC
AM_PROG_CC_C_O
 
RDC_REPLACE_FUNC_GETOPT_LONG
 
AC_C_CONST
AC_HEADER_STDBOOL
AM_ICONV
  
AC_SEARCH_LIBS([socket], [socket])
AC_SEARCH_LIBS([inet_pton], [nsl])
AC_SEARCH_LIBS([nanosleep], [rt])

define([AC_LIBTOOL_LANG_CXX_CONFIG], [:])dnl
define([AC_LIBTOOL_LANG_F77_CONFIG], [:])dnl
AC_PROG_LIBTOOL
 
AM_SILENT_RULES([yes])
 
AM_GNU_GETTEXT_VERSION([0.17])
 
# Checks for libraries.
requirement_auth=""
requirement_auth="${requirement_auth} openssl >= 1.0"
requirement_auth="${requirement_auth} libevent >= 2.0"

#
# DEBUG
#
AC_ARG_ENABLE(
    debug,
    [AC_HELP_STRING([--disable-debug],
                       [disable debug. (default=enabled)]
                      )
    ],
    [use_debug=$enableval],
    [use_debug="yes"]
)
 
AM_CONDITIONAL([USE_DEBUG], test "x${use_debug}" = "xyes")
if test "x$use_debug" = "xyes"; then
    AC_DEFINE(USE_DEBUG, 1, [Use Debug])
fi

PKG_CHECK_MODULES([AUTH], [${requirement_auth}])
 
# Checks for library functions.
 
AC_CONFIG_FILES([
Makefile
src/Makefile
examples/Makefile
])
 
AC_OUTPUT()
 
echo "---------------------------------------------------------------"
echo "                  version : $VERSION"
echo "---------------------------------------------------------------"
echo
echo "Installation :"
eval echo "Path...................................... : $exec_prefix"
eval echo "Binaries.................................. : $exec_prefix/bin"
echo
echo "Environment Settings :"
echo "Enable Debug................................... : $use_debug"
echo
