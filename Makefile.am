## Process this file with automake to produce Makefile.in
# @copyright:	Copyright (C) 2017 Kuhrman Technology Solutions LLC.
#
# This file is part of bzend.
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

# @todo: Find libtool macros.
# ACLOCAL_AMFLAGS = -I glib/m4 -I m4

# @todo: DISTCHECK_CONFIGURE_FLAGS

# Add source file sub-directories to compiler search path
AM_CPPFLAGS = \
	-Isrc -I$(top_srcdir)/src

# automake will search for MakefileS in the following subdirs.
SUBDIRS = src tests
