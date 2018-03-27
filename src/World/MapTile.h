#ifndef WORLD_MAPTILE_H
#define WORLD_MAPTILE_H

class MapTile {
public:
    MapTile() = delete;
    ~MapTile() = default;

    MapTile(const MapTile& other) = delete;
    MapTile(MapTile&& other) noexcept = default;
    MapTile& operator=(const MapTile& other) = delete;
    MapTile& operator=(MapTile&& other) noexcept = default;
};


#endif
