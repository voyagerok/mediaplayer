DIALOGS_SOURCES =   Dialogs/file_dialog.h \
                    Dialogs/gtk3_file_dialog.cpp \
                    Dialogs/gtk3_file_dialog.h
                  
FACTORIES_SOURCES = Factories/menu_bar_factory.cpp \
                    Factories/menu_bar_factory.h \
                    Factories/menu_factory.h
                    
UTILS_SOURCES =     Utils/key_name_translator.cpp \
                    Utils/key_name_translator.h
                
WIDGETS_SOURCES =   Widgets/control_panel.cpp \
                    Widgets/control_panel.h \
                    Widgets/mpv_container.cpp \
                    Widgets/mpv_container.h \
                    Widgets/slider.cpp \
                    Widgets/slider.h \
                    Widgets/window.cpp \
                    Widgets/window.h
                    
VIEWS_SOURCES =    Views/mediaplayer_views.cpp \
                   Views/mediaplayer_views.h
                   
GLIB_COMPILE_RESOURCES = glib-compile-resources
RESOURCE_FILES = $(shell $(GLIB_COMPILE_RESOURCES) --sourcedir=$(srcdir)/Views --generate-dependencies $(srcdir)/Views/views.gresource.xml)

Views/mediaplayer_views.cpp: Views/views.gresource.xml $(RESOURCE_FILES)
	$(AM_V_GEN) $(GLIB_COMPILE_RESOURCES) --target=Views/mediaplayer_views.cpp --sourcedir=$(srcdir)/Views --generate-source --c-name=mediaplayer_views Views/views.gresource.xml  
	$(AM_V_GEN) $(GLIB_COMPILE_RESOURCES) --target=Views/mediaplayer_views.h --sourcedir=$(srcdir)/Views --generate-header --c-name=mediaplayer_views Views/views.gresource.xml

bin_PROGRAMS=mediaplayer

nodist_mediaplayer_SOURCES = $(VIEWS_SOURCES)

dist_mediaplayer_SOURCES = $(DIALOGS_SOURCES) \
                      $(FACTORIES_SOURCES) \
                      $(UTILS_SOURCES) \
                      $(WIDGETS_SOURCES) \
                      main.cpp \
                      application.cpp \
                      application.h \
                      mpv_handle_wrapper.cpp \
                      mpv_handle_wrapper.h

mediaplayer_LDADD = $(gtkmm3_LIBS) $(mpv_LIBS)

mediaplayer_CXXFLAGS = $(gtkmm3_CFLAGS) $(mpv_CFLAGS)

BUILT_SOURCES = $(VIEWS_SOURCES)

EXTRA_DIST = Views/menubar.xml \
             Views/views.gresource.xml
             
            


