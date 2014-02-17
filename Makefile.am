noinst_HEADERS = src/Game.h src/GameObject.h src/Components/Component.h src/PhysicsSimulator.h src/Components/Transform.h src/Components/Script.h src/Scripts/PaddleScript.h

bin_PROGRAMS = Rasinki
Rasinki_CPPFLAGS = -I$(top_srcdir)/src
Rasinki_SOURCES = src/Game.cpp src/main.cpp src/GameObject.cpp src/Components/Component.cpp src/PhysicsSimulator.cpp src/Components/Transform.cpp src/Components/Script.cpp src/Scripts/PaddleScript.cpp src/Components/Physics.cpp

Rasinki_CXXFLAGS = $(OGRE_CFLAGS) $(OIS_CFLAGS) $(bullet_CFLAGS) -std=c++0x
Rasinki_LDADD = $(OGRE_LIBS) $(OIS_LIBS) $(bullet_LIBS)

EXTRA_DIST = buildit makeit
AUTOMAKE_OPTIONS = foreign
