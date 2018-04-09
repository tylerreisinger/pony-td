#include "Entity.h"

#include <iostream>

Entity::Entity(PhysicsComponent physics):
    m_physics_component(physics)
{
 
}

void Entity::update(const GameTime&) { 
    std::cout << m_physics_component << std::endl;
}
 
