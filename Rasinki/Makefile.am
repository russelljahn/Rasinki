noinst_HEADERS = src/Game.h src/GameObject.h src/Components/Component.h src/PhysicsSimulator.h src/Components/Transform.h src/Components/Renderer.h src/Components/Script.h src/Objects/Cube.h src/Objects/Robot.h src/Player.h src/SoundManager.h src/Scripts/GameplayScript.h src/Scripts/Grid.h src/Scripts/GridSquare.h src/Scripts/RobotScript.h src/Time.h src/Input.h src/Scripts/EnemyScript.h src/Scripts/Pathfinder.h src/Objects/Tower.h src/Objects/Barrier.h src/Scripts/EnemySpawner.h src/Objects/Enemy.h src/Objects/HomeBase.h src/Objects/SpawnPoint.h src/Objects/Explosion.h src/Objects/Mountain.h

bin_PROGRAMS = Rasinki
Rasinki_CPPFLAGS = -I$(top_srcdir)/src
Rasinki_SOURCES = src/Game.cpp src/main.cpp src/GameObject.cpp src/Components/Component.cpp src/PhysicsSimulator.cpp src/Components/Transform.cpp src/Components/Renderer.cpp src/Components/Script.cpp src/Components/Physics.cpp src/Objects/Cube.cpp src/Scripts/Grid.cpp src/Scripts/GridSquare.cpp src/Objects/Robot.cpp src/Player.cpp src/SoundManager.cpp src/Scripts/GameplayScript.cpp src/Scripts/RobotScript.cpp src/Time.cpp src/Input.cpp src/Scripts/EnemyScript.cpp src/Scripts/Pathfinder.cpp src/Objects/Tower.cpp src/Objects/Barrier.cpp  src/Scripts/EnemySpawner.cpp src/Objects/Enemy.cpp src/Objects/HomeBase.cpp src/Objects/SpawnPoint.cpp src/Objects/Explosion.cpp src/Objects/Mountain.cpp

Rasinki_CXXFLAGS = $(OGRE_CFLAGS) $(OIS_CFLAGS) $(bullet_CFLAGS) $(sdl_CFLAGS) $(SDLMIXER_CFLAGS) $(SDLNET_CFLAGS) -std=c++0x
Rasinki_LDADD = $(OGRE_LIBS) $(OGRE_TERRAIN_LIBS) $(OIS_LIBS) $(bullet_LIBS) $(sdl_LIBS) $(SDLMIXER_LIBS) $(SDLNET_LIBS) $(CEGUI_LIBS) $(CEGUI_OGRE_LIBS)

EXTRA_DIST = buildit makeit
AUTOMAKE_OPTIONS = foreign
