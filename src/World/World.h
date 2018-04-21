#ifndef WORLD_WORLD_H
#define WORLD_WORLD_H

#include <cmath>
#include <vector>

#include <SFML/System/Vector2.hpp>

#include "MapTile.h"
#include "SpawnPoint.h"
#include "Target.h"

class World {
public:
    World(int width, int height, int tile_width, int tile_height, const MapTile& default_tile);
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

    int size() const;
    const std::vector<MapTile>& tiles() const;
    const MapTile& tile(int x, int y) const;
    void set_tile(int x, int y, MapTile tile);


    sf::Vector2<double> map_to_world_pos(const sf::Vector2<int>& pos) const {
        return map_to_world_pos(pos.x, pos.y);
    }
    sf::Vector2<double> map_to_world_pos(int x, int y) const {
        return sf::Vector2{
            static_cast<double>(x+0.5) * m_tile_width, 
            static_cast<double>(y+0.5) * m_tile_height
        };
    }
    sf::Vector2<int> world_to_map_pos(sf::Vector2<double> pos) const {
        return sf::Vector2{
            static_cast<int>(std::floor(pos.x / m_tile_width)),
            static_cast<int>(std::floor(pos.y / m_tile_height)),
        };
    }

    const std::vector<SpawnPoint>& spawn_points() const;
    void add_spawn_point(SpawnPoint sp);
    bool has_spawn_point(int x, int y) const;

    const std::vector<Target>& targets() const;
    void add_target(Target sp);
    bool has_target(int x, int y) const;

protected:
    int m_width;
    int m_height;
    int m_tile_width;
    int m_tile_height;

    std::vector<MapTile> m_grid;
    std::vector<SpawnPoint> m_spawn_points;
    std::vector<Target> m_targets;
};


#endif
