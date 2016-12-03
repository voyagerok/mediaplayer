SOME_VARIABLE=$(shell ls -l)

bin_PROGRAMS=mediaplayer
mediaplayer_SOURCES=main.cpp Application.cpp MpvHandleWrapper.cpp
mediaplayer_LDADD=$(MEDIAPLAYER_LIBS) \
                    Widgets/libmediaplayer_widgets.la \
                    Factories/libmediaplayer_factories.la \
                    Dialogs/libmediaplayer_dialogs.la \
                    Utils/libmediaplayer_utils.la \
                    Views/libmediaplayer_views.la
mediaplayer_CXXFLAGS=$(MEDIAPLAYER_CFLAGS)
SUBDIRS = Widgets Dialogs Factories Utils Views