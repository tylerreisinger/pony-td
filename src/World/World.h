#ifndef WORLD_WORLD_H
#define WORLD_WORLD_H

#include <cmath>
#include <memory>
#include <vector>

#include <entityx/quick.h>

#include <SFML/System/Vector2.hpp>

#include "ISpawnBehavior.h"
#include "MapTile.h"
#include "SpawnPoint.h"
#include "Target.h"

class GameTime;

class World {
public:
    World(int width,
            int height,
            int tile_width,
            int tile_height,
            const MapTile& default_tile,
            std::unique_ptr<entityx::EntityX> m_entities = nullptr);

    ~World() = default;

    World(const World& other) = delete;
    World(World&& other) noexcept = delete;
    World& operator=(const World& other) = delete;
    World& operator=(World&& other) noexcept = delete;
    int width() const;
    int height() const;
    int tile_width() const { return m_tile_width; }
    int tile_height() const { return m_tile_height; }
    sf::Vector2<int> tile_dimensions() const {
        return sf::Vector2<int>{m_tile_width, m_tile_height};
    }

    void set_entities(std::unique_ptr<entityx::EntityX> entities) {
        m_ecs = std::move(entities);
    }

    int size() const;
    const std::vector<MapTile>& tiles() const;
    const MapTile& tile(int x, int y) const;
    void set_tile(int x, int y, MapTile tile);


    sf::Vector2<double> map_to_world_pos(const sf::Vector2<int>& pos) const {
        return map_to_world_pos(
                static_cast<double>(pos.x), static_cast<double>(pos.y));
    }
    sf::Vector2<double> map_to_world_pos(const sf::Vector2<double>& pos) const {
        return map_to_world_pos(pos.x, pos.y);
    }
    sf::Vector2<double> map_to_world_pos(double x, double y) const {
        return sf::Vector2{x * m_tile_width, y * m_tile_height};
    }
    sf::Vector2<double> world_to_map_pos(sf::Vector2<double> pos) const {
        return sf::Vector2{
                std::floor(pos.x / m_tile_width),
                std::floor(pos.y / m_tile_height),
        };
    }

    SpawnPoint& make_spawn_point(sf::Vector2<double> position,
            std::unique_ptr<ISpawnBehavior> behavior);


    const std::vector<std::unique_ptr<SpawnPoint>>& spawn_points() const;
    std::vector<std::unique_ptr<SpawnPoint>>& spawn_points();
    void add_spawn_point(std::unique_ptr<SpawnPoint> sp);
    bool has_spawn_point(int x, int y) const;

    const std::vector<Target>& targets() const;
    void add_target(Target sp);
    bool has_target(int x, int y) const;

    entityx::EntityX& get_ecs() { return *m_ecs; }
    const entityx::EntityX& get_ecs() const { return *m_ecs; }
    entityx::EntityManager& get_entities() { return m_ecs->entities; }

    void update(const GameTime& time);

protected:
    int m_width;
    int m_height;
    int m_tile_width;
    int m_tile_height;

    std::unique_ptr<entityx::EntityX> m_ecs;

    std::vector<MapTile> m_grid;
    std::vector<std::unique_ptr<SpawnPoint>> m_spawn_points;
    std::vector<Target> m_targets;
};


#endif
