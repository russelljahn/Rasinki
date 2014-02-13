noinst_HEADERS = src/Game.h

bin_PROGRAMS = Rasinki
Rasinki_CPPFLAGS = -I$(top_srcdir)/src
Rasinki_SOURCES = src/Game.cpp src/main.cpp
Rasinki_CXXFLAGS = $(OGRE_CFLAGS) $(OIS_CFLAGS) $(bullet_CFLAGS)
Rasinki_LDADD = $(OGRE_LIBS) $(OIS_LIBS) $(bullet_LIBS)

EXTRA_DIST = buildit makeit
AUTOMAKE_OPTIONS = foreign