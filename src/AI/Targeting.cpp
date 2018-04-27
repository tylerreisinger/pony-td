#include "Targeting.h"

#include <limits>

#include "World/World.h"

#include "Component/Enemy.h"
#include "Component/Position.h"

#include "VectorMath.h"


Targeter::Targeter(sf::Vector2<double> origin, double max_radius)
    : m_origin(origin), m_max_radius(max_radius) {}

void NearestGoalTargeter::find_target(World& world) const {
    if(world.targets().empty()) {
        return;
    }
    const auto& goal = world.targets().front();
    auto radius_sq = max_radius() * max_radius();
    auto min_dist = std::numeric_limits<double>::max();
    auto close_dude = entityx::Entity::INVALID;
    world.get_entities().each<comp::Position, comp::Enemy>(
            [this, radius_sq, &min_dist, &goal, &close_dude](entityx::Entity e,
                    const comp::Position& pos,
                    comp::Enemy&) {
                auto dist = origin() - pos.position;
                if(magnitude2(dist) < radius_sq) {
                    auto goal_dist = goal.world_position() - pos.position;
                    if(magnitude2(goal_dist) < min_dist) {
                        min_dist = magnitude2(goal_dist);
                        close_dude = e.id();
                    }
                }
            });

    std::cout << "Closest dude is " << close_dude << " at  "
              << std::sqrt(min_dist) << " away.\n";
}
