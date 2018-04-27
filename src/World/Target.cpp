#include "Target.h"

#include "World.h"


Target::Target(World& world, sf::Vector2<int> position)
    : m_world(&world), m_position(position) {}

const sf::Vector2<int>& Target::map_position() const { return m_position; }

sf::Vector2<double> Target::world_position() const {
    return m_world->map_to_world_pos(
            sf::Vector2<double>(map_position()) + sf::Vector2{0.5, 0.5});
}
