#ifndef WORLD_WORLD_H
#define WORLD_WORLD_H

#include <vector>

#include "MapTile.h"
#include "SpawnPoint.h"
#include "Target.h"

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
    int size() const;
    const std::vector<MapTile>& tiles() const;
    const MapTile& tile(int x, int y) const;
    void set_tile(int x, int y, MapTile tile);

    const std::vector<SpawnPoint>& spawn_points() const;
    void add_spawn_point(SpawnPoint sp);
    bool has_spawn_point(int x, int y) const;

    const std::vector<Target>& targets() const;
    void add_target(Target sp);
    bool has_target(int x, int y) const;

protected:
    int m_width;
    int m_height;
    std::vector<MapTile> m_grid;
    std::vector<SpawnPoint> m_spawn_points;
    std::vector<Target> m_targets;
};


#endif
