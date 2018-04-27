#ifndef COMPONENT_ENEMY_H
#define COMPONENT_ENEMY_H

#include "Data/DefinitionDatabase.h"
#include "Data/EnemyDefinition.h"

namespace comp {

class Enemy {
public:
    Enemy() = default;
    ~Enemy() = default;

    Enemy(DefinitionHandle<EnemyDefinition> definition)
        : definition(std::move(definition)) {}

    Enemy(const Enemy& other) = default;
    Enemy(Enemy&& other) noexcept = default;
    Enemy& operator=(const Enemy& other) = default;
    Enemy& operator=(Enemy&& other) noexcept = default;

    DefinitionHandle<EnemyDefinition> definition;
};

} // namespace comp

#endif
