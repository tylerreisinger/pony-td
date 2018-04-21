#include "World.h"

World::World(int width, int height, int tile_width, int tile_height, const MapTile& default_tile)
    : m_width(width), m_height(height), 
      m_tile_width(tile_width), m_tile_height(tile_height),
      m_grid(width * height, default_tile) 
{}

int World::width() const { return m_width; }

int World::height() const { return m_height; }
int World::size() const { return m_width * m_height; }

const std::vector<MapTile>& World::tiles() const { return m_grid; }

const MapTile& World::tile(int x, int y) const {
    return m_grid[x + y * m_width];
}

void World::set_tile(int x, int y, MapTile tile) {
    m_grid[x + y * m_width] = std::move(tile);
}

const std::vector<std::unique_ptr<SpawnPoint>>& World::spawn_points() const {
    return m_spawn_points;
}
std::vector<std::unique_ptr<SpawnPoint>>& World::spawn_points() {
    return m_spawn_points;
}

void World::add_spawn_point(std::unique_ptr<SpawnPoint> sp) {
    m_spawn_points.push_back(std::move(sp));
}
bool World::has_spawn_point(int x, int y) const {
    for(auto& point : m_spawn_points) {
        if(point->map_position() == sf::Vector2<int>(x, y)) {
            return true;
        }
    }
    return false;
}

const std::vector<Target>& World::targets() const { return m_targets; }

void World::add_target(Target target) {
    m_targets.push_back(std::move(target));
}

bool World::has_target(int x, int y) const {
    for(auto& target : m_targets) {
        if(target.map_position() == sf::Vector2<int>(x, y)) {
            return true;
        }
    }
    return false;
}
