#include "SpawnPoint.h"


SpawnPoint::SpawnPoint(World& world, sf::Vector2<int> position):
    m_world(&world), m_map_position(position)
{ }
 
const sf::Vector2<int> SpawnPoint::map_position() const {
    return m_map_position;
}
 
