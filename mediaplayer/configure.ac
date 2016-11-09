dnl Process this file with autoconf to produce a configure script.

AC_PREREQ(2.59)
AC_INIT(mediaplayer, 1.0)


AC_CANONICAL_SYSTEM
AM_INIT_AUTOMAKE([subdir-objects])

LT_INIT

AC_PROG_CXX

PKG_CHECK_MODULES([MEDIAPLAYER], [gtkmm-3.0 mpv])

AC_CONFIG_FILES(Makefile src/Makefile src/Widgets/Makefile src/Dialogs/Makefile src/Factories/Makefile)
AC_OUTPUT

