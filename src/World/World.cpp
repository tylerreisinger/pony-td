#include "World.h"

#include <cassert>

#include "Component/Behavior.h"
#include "Component/Position.h"

#include "System/BehaviorSystem.h"
#include "System/MovementSystem.h"
#include "System/PathMovementSystem.h"
#include "System/SpriteSystem.h"

World::World(int width,
        int height,
        int tile_width,
        int tile_height,
        const MapTile& default_tile,
        std::unique_ptr<entityx::EntityX> ecs)
    : m_width(width), m_height(height), m_tile_width(tile_width),
      m_tile_height(tile_height), m_ecs(std::move(ecs)),
      m_grid(width * height, default_tile) {}

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
SpawnPoint& World::make_spawn_point(sf::Vector2<double> position,
        std::unique_ptr<ISpawnBehavior> behavior) {
    auto map_tile = sf::Vector2<int>(world_to_map_pos(position));
    auto entity = m_ecs->entities.create();
    entity.assign<comp::Position>(position);
    auto spawn_point = std::make_unique<SpawnPoint>(
            *this, entity, map_tile, std::move(behavior));
    auto& ret = *spawn_point;

    add_spawn_point(std::move(spawn_point));
    return ret;
}

void World::update(const GameTime& time) {
    m_ecs->systems.update<sys::BehaviorSystem>(time);
    m_ecs->systems.update<sys::MovementSystem>(time);
    m_ecs->systems.update<sys::PathMovementSystem>(time);
}

Tower& World::create_tower(Sprite sprite, sf::Vector2<int> map_pos) {
    assert(map_pos.x < width() && map_pos.y < height());
    auto tower = std::make_unique<Tower>(*this, std::move(sprite), map_pos);
    auto[iter, is_success] =
            m_towers.insert(std::pair(map_pos, std::move(tower)));

    if(!is_success) {
        throw std::runtime_error(
                "Tried to create a tower where one already exists!");
    }

    return *iter->second;
}
