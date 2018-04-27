set(SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/FrameRateCounter.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Game.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/GameClock.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/GameTime.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp

        ${CMAKE_CURRENT_SOURCE_DIR}/AI/AStar.cpp

        ${CMAKE_CURRENT_SOURCE_DIR}/Data/AssetManager.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Data/EnemyDefinition.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Data/TextureLoader.cpp

        ${CMAKE_CURRENT_SOURCE_DIR}/Graphics/Sprite.cpp

        ${CMAKE_CURRENT_SOURCE_DIR}/System/BehaviorSystem.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/System/PathMovementSystem.cpp

        ${CMAKE_CURRENT_SOURCE_DIR}/World/Camera.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/World/CameraController.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/World/DelaySpawnBehavior.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/World/FloorTile.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/World/FloorTileDefinition.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/World/FloorTileDirectory.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/World/MapTile.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/World/Path.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/World/SpawnPoint.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/World/Target.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/World/Tower.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/World/TileGraphic.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/World/TileSet.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/World/World.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/World/WorldRenderer.cpp
PARENT_SCOPE)

set(HEADERS
        ${CMAKE_CURRENT_SOURCE_DIR}/Angle.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Flags.h
        ${CMAKE_CURRENT_SOURCE_DIR}/FrameRateCounter.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Game.h
        ${CMAKE_CURRENT_SOURCE_DIR}/GameClock.h
        ${CMAKE_CURRENT_SOURCE_DIR}/GameTime.h

        ${CMAKE_CURRENT_SOURCE_DIR}/AI/AStar.h

        ${CMAKE_CURRENT_SOURCE_DIR}/Data/AssetManager.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Data/TextureLoader.h

        ${CMAKE_CURRENT_SOURCE_DIR}/Graphics/Sprite.h

        ${CMAKE_CURRENT_SOURCE_DIR}/Component/Behavior.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Component/Position.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Component/Velocity.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Component/Sprite.h

        ${CMAKE_CURRENT_SOURCE_DIR}/System/BehaviorSystem.h
        ${CMAKE_CURRENT_SOURCE_DIR}/System/MovementSystem.h
        ${CMAKE_CURRENT_SOURCE_DIR}/System/PathMovementSystem.h
        ${CMAKE_CURRENT_SOURCE_DIR}/System/SpriteSystem.h

        ${CMAKE_CURRENT_SOURCE_DIR}/World/Camera.h
        ${CMAKE_CURRENT_SOURCE_DIR}/World/CameraController.h
        ${CMAKE_CURRENT_SOURCE_DIR}/World/DelaySpawnBehavior.h
        ${CMAKE_CURRENT_SOURCE_DIR}/World/FloorTile.h
        ${CMAKE_CURRENT_SOURCE_DIR}/World/FloorTileDefinition.h
        ${CMAKE_CURRENT_SOURCE_DIR}/World/FloorTileDirectory.h
        ${CMAKE_CURRENT_SOURCE_DIR}/World/ISpawnBehavior.h
        ${CMAKE_CURRENT_SOURCE_DIR}/World/MapTile.h
        ${CMAKE_CURRENT_SOURCE_DIR}/World/Path.h
        ${CMAKE_CURRENT_SOURCE_DIR}/World/SpawnPoint.h
        ${CMAKE_CURRENT_SOURCE_DIR}/World/Target.h
        ${CMAKE_CURRENT_SOURCE_DIR}/World/TileGraphic.h
        ${CMAKE_CURRENT_SOURCE_DIR}/World/TileSet.h
        ${CMAKE_CURRENT_SOURCE_DIR}/World/TileProperties.h
        ${CMAKE_CURRENT_SOURCE_DIR}/World/Tower.h
        ${CMAKE_CURRENT_SOURCE_DIR}/World/World.h
        ${CMAKE_CURRENT_SOURCE_DIR}/World/WorldRenderer.h
PARENT_SCOPE)
