#include "Tower.h"

#include "World.h"

#include "Angle.h"

#include "Component/Position.h"
#include "Component/Rotation.h"
#include "Component/Sprite.h"
#include "Component/Tower.h"

Tower::Tower(entityx::Entity entity) : m_entity(entity) {}

Tower::Tower(World& world, Sprite sprite, sf::Vector2<int> map_cell) {
    auto entity = world.get_entities().create();

    entity.assign<comp::Position>(world.map_to_world_pos(
            sf::Vector2<double>(map_cell) + sf::Vector2<double>{0.5, 0.5}));
    entity.assign<comp::Sprite>(std::move(sprite));
    entity.assign<comp::Rotation>(Deg(270.0));
    entity.assign<comp::Tower>();
}
