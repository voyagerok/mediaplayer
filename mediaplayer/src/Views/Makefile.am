resource_files = $(shell glib-compile-resources --sourcedir=$(srcdir) --generate-dependencies $(srcdir)/views.gresource.xml)

mediaplayer_views.cpp: views.gresource.xml $(resource_files)
	$(AM_V_GEN) glib-compile-resources --target=mediaplayer_views.cpp --sourcedir=$(srcdir) --generate --c-name=mediaplayer_views $<
	$(AM_V_GEN) glib-compile-resources --target=mediaplayer_views.h --sourcedir=$(srcdir) --generate --c-name=mediaplayer_views $<

noinst_LTLIBRARIES = libmediaplayer_views.la
libmediaplayer_views_la_SOURCES = mediaplayer_views.h \
                                  mediaplayer_views.cpp
libmediaplayer_views_la_CXXFLAGS = $(MEDIAPLAYER_CFLAGS)
libmediaplayer_views_la_LIBADD = $(MEDIAPLAYER_LIBS)