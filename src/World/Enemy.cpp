#include "Enemy.h"

#include "Data/EnemyDefinition.h"
#include "World/World.h"

#include "Component/Enemy.h"
#include "Component/Health.h"
#include "Component/Position.h"
#include "Component/Rotation.h"
#include "Component/Sprite.h"

Enemy::Enemy(World& world,
        ConstDefinitionHandle<EnemyDefinition> definition,
        const sf::Vector2<double>& position) {
    auto entity = world.get_entities().create();

    entity.assign<comp::Position>(position);
    entity.assign<comp::Sprite>(definition->default_sprite);
    entity.assign<comp::Health>(definition->base_health);
    entity.assign<comp::Enemy>(definition);
    entity.assign<comp::Rotation>(Deg(0.0));

    m_entity = entity;
}
