#include "Target.h"


Target::Target(World& world, sf::Vector2<int> position)
    : m_world(&world), m_position(position) {}

const sf::Vector2<int>& Target::map_position() const { return m_position; }
