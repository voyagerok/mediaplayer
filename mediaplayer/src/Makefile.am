bin_PROGRAMS=mediaplayer
mediaplayer_SOURCES=main.cpp Application.cpp MpvHandleWrapper.cpp
mediaplayer_LDADD=$(MEDIAPLAYER_LIBS) \
                    Widgets/libmpv-widgets.la \
                    Factories/libmpv-factories.la \
                    Dialogs/libmpv-dialogs.la
mediaplayer_CXXFLAGS=$(MEDIAPLAYER_CFLAGS)
SUBDIRS = Widgets Dialogs Factories