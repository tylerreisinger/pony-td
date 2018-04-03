#ifndef WORLD_WORLD_H
#define WORLD_WORLD_H

#include <vector>

#include "MapTile.h"

class World {
public:
    World(int width, int height, const MapTile& default_tile);
    ~World() = default;

    World(const World& other) = delete;
    World(World&& other) noexcept = delete;
    World& operator=(const World& other) = delete;
    World& operator=(World&& other) noexcept = delete;
    int width() const;
    int height() const;
    const std::vector<MapTile>& tiles() const;
    const MapTile& tile(int x, int y) const;
    void set_tile(int x, int y, MapTile tile);

protected:
    int m_width;
    int m_height;
    std::vector<MapTile> m_grid;
};


#endif
