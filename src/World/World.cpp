#include "World.h"

int World::width() const { return m_width; }

int World::height() const { return m_height; }

void World::set_tile(int x, int y, MapTile tile) {
    m_grid[x + y * m_width] = std::move(tile);
}
