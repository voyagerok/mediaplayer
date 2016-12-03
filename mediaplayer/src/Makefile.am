bin_PROGRAMS=mediaplayer
mediaplayer_SOURCES=main.cpp Application.cpp MpvHandleWrapper.cpp
mediaplayer_LDADD=$(MEDIAPLAYER_LIBS) \
                    Widgets/libmediaplayer-widgets.la \
                    Factories/libmediaplayer-factories.la \
                    Dialogs/libmediaplayer-dialogs.la \
                    Utils/libmediaplayer-utils.la
mediaplayer_CXXFLAGS=$(MEDIAPLAYER_CFLAGS)
SUBDIRS = Widgets Dialogs Factories Utils