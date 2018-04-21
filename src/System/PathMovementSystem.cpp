#include "PathMovementSystem.h"

#include <iostream>

#include "World/World.h"
#include "PrintUtils.h"


static constexpr double SPEED = 40.0;
namespace sys {

PathMovementSystem::PathMovementSystem(World& world):
    m_world(&world)
{
}
 
void PathMovementSystem::update(entityx::EntityManager& es,
        entityx::EventManager&,
        const GameTime& dt)
{
    es.each<comp::Position, comp::PathMovement>(
            [this, dt](entityx::Entity e,
                    comp::Position& position,
                    comp::PathMovement& path) {
                auto& path_trav = path.path;
                std::cout << path_trav << std::endl;

                if(path_trav.is_done()) {
                    e.remove<comp::PathMovement>();
                    return;
                }

                auto move_rate = SPEED * dt.get_elapsed_game().count();
                auto new_position =
                        path_trav.step(position.position, move_rate);

                position.position = new_position;
            });
}

}
