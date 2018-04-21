#include "SpawnPoint.h"

#include <cassert>
#include <iostream>

#include "GameTime.h"
#include "World.h"


SpawnPoint::SpawnPoint(World& world,
        sf::Vector2<int> position,
        std::unique_ptr<ISpawnBehavior> behavior)
    : m_world(&world), m_map_position(position),
      m_behavior(std::move(behavior)) {
    m_behavior->set_parent(this);
    auto path = compute_path_to_goal();
    if(!path) {
        std::cerr << "WARNING: No path found to goal.\n";
    } else {
        m_path = *path;
    }
}

const sf::Vector2<int>& SpawnPoint::map_position() const {
    return m_map_position;
}

std::optional<Path> SpawnPoint::compute_path_to_goal() const {
    assert(m_world != nullptr);
    if(m_world->targets().size() > 0) {
        auto& goal = m_world->targets()[0];
        AStar as;
        auto path = as.find_path(m_map_position, goal.map_position(), *m_world);
        as.print_cost_matrix();
        std::cout << path << std::endl;

        if(path.size() == 0) {
            return std::nullopt;
        } else {
            return path;
        }
    } else {
        std::cerr << "WARNING: World without spawn points and/or goals tried to compute a path.\n";
        return std::nullopt;
    }
}
 
const Path& SpawnPoint::path_to_goal() const {
    return m_path;
}

void SpawnPoint::update(entityx::EntityX& ecs, const GameTime& time) {
    m_behavior->update(*m_world, ecs, time);
}
