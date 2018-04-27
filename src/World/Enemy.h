#ifndef WORLD_ENEMY_H
#define WORLD_ENEMY_H

#include <entityx/Entity.h>

#include "Data/DefinitionDatabase.h"

namespace sf {
template <typename T>
class Vector2;
}

class EnemyDefinition;
class World;

class Enemy {
public:
    Enemy() = delete;
    ~Enemy() = default;

    Enemy(World& world,
            ConstDefinitionHandle<EnemyDefinition> definition,
            const sf::Vector2<double>& position);

    Enemy(const Enemy& other) = delete;
    Enemy(Enemy&& other) noexcept = default;
    Enemy& operator=(const Enemy& other) = delete;
    Enemy& operator=(Enemy&& other) noexcept = default;

    entityx::Entity entity() const { return m_entity; }

private:
    entityx::Entity m_entity;
};

#endif
