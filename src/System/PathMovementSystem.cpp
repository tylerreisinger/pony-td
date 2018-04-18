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
        [this, dt](entityx::Entity, comp::Position& position,
            comp::PathMovement& path)
        {
            auto map_pos = m_world->world_to_map_pos(position.position);
            auto path_step = path.path.current_step(map_pos);
            if(path_step == Path::NOT_ON_PATH) {
                return;
            }
            auto direction = path.path.direction_to_step(path_step + 1);
            if(!direction) {
                return;
            }
            auto movement_vec = unit_vector_for_direction(*direction);
            
            position.position += movement_vec*SPEED*dt.get_elapsed_game().count();

            std::cout << "Pos: " << position.position << ", Map: "
                << m_world->world_to_map_pos(position.position) 
                << " Current Step: " << path.path.current_step(map_pos) 
                << " Direction: " << *direction << "\n";
        }
    );
}

}
