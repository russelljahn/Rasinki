<<<<<<< HEAD
noinst_HEADERS = Assignment2.h Ball.h ControlListener.h GameObject.h OgreMotionState.h Overlay.h Player.h PlayerCamera.h PlayingField.h Simulator.h Wall.h 

bin_PROGRAMS = assignment2
assignment2_CPPFLAGS = -I$(top_srcdir) -std=c++0x
assignment2_SOURCES = Assignment2.cpp Ball.cpp ControlListener.cpp GameObject.cpp Overlay.cpp Player.cpp PlayerCamera.cpp PlayingField.cpp Simulator.cpp Wall.cpp
assignment2_CXXFLAGS = $(OGRE_CFLAGS) $(OIS_CFLAGS) $(bullet_CFLAGS)
assignment2_LDADD = $(OGRE_LIBS) $(OIS_LIBS) $(bullet_LIBS)
=======
noinst_HEADERS = src/Game.h

bin_PROGRAMS = Rasinki
Rasinki_CPPFLAGS = -I$(top_srcdir)/src
Rasinki_SOURCES = src/Game.cpp src/main.cpp
Rasinki_CXXFLAGS = $(OGRE_CFLAGS) $(OIS_CFLAGS) $(bullet_CFLAGS)
Rasinki_LDADD = $(OGRE_LIBS) $(OIS_LIBS) $(bullet_LIBS)
>>>>>>> 4a0bc1f918006eb19707c0ba403df80095e19822

EXTRA_DIST = buildit makeit
AUTOMAKE_OPTIONS = foreign
