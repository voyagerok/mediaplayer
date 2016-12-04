dnl Process this file with autoconf to produce a configure script.

AC_PREREQ(2.59)
AC_INIT(mediaplayer, 1.0)

CXXFLAGS='-g3 -O0 -pipe'

AC_CANONICAL_SYSTEM
AM_INIT_AUTOMAKE([subdir-objects -Wno-portability])

LT_INIT

AC_PROG_CXX

PKG_CHECK_MODULES([gtkmm3], [gtkmm-3.0 glib-2.0])
PKG_CHECK_MODULES([mpv], [mpv])

AC_CONFIG_FILES([
	Makefile 
	src/Makefile
	src/Views/Makefile 
])
AC_OUTPUT

