#include "EnemyDefinition.h"

#include "World/World.h"

#include <SFML/System/Vector2.hpp>

#include "Component/Health.h"
#include "Component/Position.h"
#include "Component/Sprite.h"

EnemyDefinition::EnemyDefinition(Sprite default_sprite, std::string name)
    : m_name(name), m_default_sprite(default_sprite) {}

Enemy EnemyDefinition::build_enemy(
        World& world, const sf::Vector2<double>& position) const {
    auto entity = world.get_entities().create();

    entity.assign<comp::Position>(position);
    entity.assign<comp::Health>(m_base_health);
    entity.assign<comp::Sprite>(m_default_sprite);

    return Enemy(entity);
}
