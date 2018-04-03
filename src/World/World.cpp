#include "World.h"

World::World(int width, int height, const MapTile& default_tile)
    : m_width(width), m_height(height), m_grid(width * height, default_tile) {}

int World::width() const { return m_width; }

int World::height() const { return m_height; }

const std::vector<MapTile>& World::tiles() const { return m_grid; }

const MapTile& World::tile(int x, int y) const {
    return m_grid[x + y * m_width];
}

void World::set_tile(int x, int y, MapTile tile) {
    m_grid[x + y * m_width] = std::move(tile);
}
