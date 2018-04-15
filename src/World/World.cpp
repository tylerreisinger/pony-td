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

const std::vector<SpawnPoint>& World::spawn_points() const {
    return m_spawn_points;
}

void World::add_spawn_point(SpawnPoint sp){
    m_spawn_points.push_back(std::move(sp));
}
bool World::has_spawn_point(int x, int y) const {
    for(auto& point : m_spawn_points) {
        if(point.map_position() == sf::Vector2<int>(x, y)) {
            return true;
        }
    }
    return false;
}
 
