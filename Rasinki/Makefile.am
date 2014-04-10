noinst_HEADERS = src/Game.h src/GameObject.h src/Components/Component.h src/PhysicsSimulator.h src/Components/Transform.h src/Components/Renderer.h src/Components/Script.h src/Scripts/PaddleScript.h src/Scripts/PointBlock.h src/Scripts/Wall.h src/Objects/Sphere.h src/Objects/Paddle.h src/Objects/Plane.h src/Objects/Cube.h src/Objects/Robot.h src/Player.h src/SoundManager.h src/Scripts/SphereComponent.h src/Scripts/GameplayScript.h src/Scripts/Grid.h src/Scripts/GridSquare.h src/Scripts/RobotScript.h src/Time.h src/Network.h src/Input.h

bin_PROGRAMS = Rasinki
Rasinki_CPPFLAGS = -I$(top_srcdir)/src
Rasinki_SOURCES = src/Game.cpp src/main.cpp src/GameObject.cpp src/Components/Component.cpp src/PhysicsSimulator.cpp src/Components/Transform.cpp src/Components/Renderer.cpp src/Components/Script.cpp src/Scripts/PaddleScript.cpp src/Scripts/PointBlock.cpp src/Scripts/Wall.cpp src/Components/Physics.cpp src/Objects/Sphere.cpp src/Objects/Paddle.cpp src/Objects/Plane.cpp src/Objects/Cube.cpp src/Scripts/Grid.cpp src/Scripts/GridSquare.cpp src/Objects/Robot.cpp src/Player.cpp src/SoundManager.cpp src/Scripts/SphereComponent.cpp src/Scripts/GameplayScript.cpp src/Scripts/RobotScript.cpp src/Time.cpp src/Network.cpp src/Input.cpp

Rasinki_CXXFLAGS = $(OGRE_CFLAGS) $(OIS_CFLAGS) $(bullet_CFLAGS) $(sdl_CFLAGS) $(SDLMIXER_CFLAGS) $(SDLNET_CFLAGS) -std=c++0x
Rasinki_LDADD = $(OGRE_LIBS) $(OIS_LIBS) $(bullet_LIBS) $(sdl_LIBS) $(SDLMIXER_LIBS) $(SDLNET_LIBS) $(CEGUI_LIBS) $(CEGUI_OGRE_LIBS)

EXTRA_DIST = buildit makeit
AUTOMAKE_OPTIONS = foreign
