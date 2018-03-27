#ifndef WORLD_WORLD_H
#define WORLD_WORLD_H

#include <vector>

#include "MapTile.h"

class World {
public:
    World() = default;
    ~World() = default;

    World(const World& other) = delete;
    World(World&& other) noexcept = delete;
    World& operator=(const World& other) = delete;
    World& operator=(World&& other) noexcept = delete;
    int width() const;
    int height() const;

    void set_tile(int x, int y, MapTile tile);

protected:
    int m_width;
    int m_height;
    std::vector<MapTile> m_grid;
};


#endif
