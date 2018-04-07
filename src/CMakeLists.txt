set(SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/FrameRateCounter.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Game.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/GameClock.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/GameTime.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp

        ${CMAKE_CURRENT_SOURCE_DIR}/World/Camera.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/World/CameraController.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/World/FloorTile.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/World/MapTile.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/World/TileGraphic.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/World/TileSet.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/World/World.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/World/WorldRenderer.cpp
PARENT_SCOPE)

set(HEADERS
        ${CMAKE_CURRENT_SOURCE_DIR}/Flags.h
        ${CMAKE_CURRENT_SOURCE_DIR}/FrameRateCounter.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Game.h
        ${CMAKE_CURRENT_SOURCE_DIR}/GameClock.h
        ${CMAKE_CURRENT_SOURCE_DIR}/GameTime.h

        ${CMAKE_CURRENT_SOURCE_DIR}/World/Camera.h
        ${CMAKE_CURRENT_SOURCE_DIR}/World/CameraController.h
        ${CMAKE_CURRENT_SOURCE_DIR}/World/FloorTile.h
        ${CMAKE_CURRENT_SOURCE_DIR}/World/MapTile.h
        ${CMAKE_CURRENT_SOURCE_DIR}/World/TileGraphic.h
        ${CMAKE_CURRENT_SOURCE_DIR}/World/TileSet.h
        ${CMAKE_CURRENT_SOURCE_DIR}/World/World.h
        ${CMAKE_CURRENT_SOURCE_DIR}/World/WorldRenderer.h
PARENT_SCOPE)
