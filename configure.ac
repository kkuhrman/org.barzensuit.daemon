## Process this file with autoconf to produce a configure script.
# @copyright:	Copyright (C) 2017 Kuhrman Technology Solutions LLC.
#
# This file is part bzend.
#
# @license:	GPLv3+: GNU GPL version 3
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
#
# @author:	Karl Kuhrman
#

AC_INIT([bzend], [0.1.0], [bugs@barzensuit.org])

# Must come before AM_INIT_AUTOMAKE.
AC_CONFIG_AUX_DIR([build-aux])

# These settings have automake report all warnings as errors during early 
# development and ignore several requirements of Gnu distros that will be 
# added later such as ChangeLog, AUTHORS, etc.
# @see: https://www.gnu.org/software/automake/manual/automake.html#Hello-World
AM_INIT_AUTOMAKE([-Wall -Werror foreign])

# @todo: Specify location of local autoconf macros
# AC_CONFIG_MACRO_DIR([lib/glib/m4])

# Minimum Autoconf version required.
AC_PREREQ([2.69])

# Where to generate output; srcdir location.
AC_CONFIG_HEADERS([inc/config.h:config.in])

# Safety check - make sure directory autoconf is told contains file in fact does.
AC_CONFIG_SRCDIR([src/bzend.c])
AC_CONFIG_SRCDIR([inc/bzend.h])

# @todo: Copyright will apply as long as these sources are in use, e.g., are
# being compiled, which is reasonable year to claim the copyright.
# AC_DEFINE([BZENXMPP_COPYRIGHT_YEAR], [m4_esyscmd([date +%Y])], [year in copyright message])
# AC_DEFINE([BZENXMPP_COPYRIGHT_HOLDER], ["Kuhrman Technology Solutions LLC"], [copyright holder])

# Checks for programs.
AC_PROG_CC

# @todo: Since we use gnulib: gl_EARLY must be called as soon as possible after
# the C compiler is checked.  The others could be later, but we just
# keep everything together.
# gl_EARLY

# @todo: For gnulib.
# gl_INIT

# Check for libbzenc API header file directory
AC_MSG_CHECKING([for API header file directory])
for l in /usr/include /usr/local/include; do
    if test -d "${l}/bzenc";then
        ac_bzenc_inc="${l}/bzenc"
        break
    fi
done
if test -z "$ac_bzenc_inc"; then
    AC_MSG_ERROR([[
  ***
  *** unable to find API header files
  ***
  ]])
else
  AC_MSG_RESULT([
	...using "$ac_bzenc_inc"
])
fi
AC_DEFINE_UNQUOTED([BZENC_INC], ["$ac_bzenc_inc"], [location of API header files])
AC_SUBST([BZENC_INC], [$ac_bzenc_inc])

# Check for libbzenc
AC_MSG_CHECKING([for libbzenc])
for l in /usr/lib64 /usr/lib /lib64 /lib /usr/lib/x86_64-linux-gnu /usr/local/lib; do
    if test -f "${l}/libbzenc.so";then
        ac_bzenc_lib="${l}/libbzenc.so"
        break
    fi
done
if test -z "$ac_bzenc_lib"; then
    AC_MSG_ERROR([[
  ***
  *** unable to find libbzenc
  ***
  ]])
else
  AC_MSG_RESULT([
	...using "$ac_bzenc_lib"
])
fi
AC_DEFINE_UNQUOTED([BZENC_LIB], ["$ac_bzenc_lib"], [location of libbzenc])
AC_SUBST([BZENC_LIB], [$ac_bzenc_lib])

# @todo: i18n support from GNU gettext.
# AM_GNU_GETTEXT_VERSION([0.19.8])
# AM_GNU_GETTEXT([external])

AC_CONFIG_FILES([
 Makefile
 src/Makefile
 src/bzend.pc
 tests/Makefile
])

AC_OUTPUT

AC_MSG_NOTICE([summary of build options:

  version:          ${VERSION}
  Host type:        ${host}
  Install prefix:   ${prefix}
  Compiler:         ${CC}
  Warning flags:    errors: ${WERROR_CFLAGS} warnings: ${WARN_CFLAGS}
  Library types:    Shared=${enable_shared}, Static=${enable_static}
])
