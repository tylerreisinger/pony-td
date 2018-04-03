#ifndef WORLD_MAPTILE_H
#define WORLD_MAPTILE_H

#include "FloorTile.h"

class MapTile {
public:
    MapTile(FloorTile floor_tile);
    ~MapTile() = default;

    MapTile(const MapTile& other) = default;
    MapTile(MapTile&& other) noexcept = default;
    MapTile& operator=(const MapTile& other) = default;
    MapTile& operator=(MapTile&& other) noexcept = default;
    const FloorTile& floor_tile() const;

private:
    FloorTile m_floor_tile;
};


#endif
