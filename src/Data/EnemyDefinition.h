#ifndef DATA_ENEMYDEFINITION_H
#define DATA_ENEMYDEFINITION_H

#include <limits>

#include <string>

#include "Graphics/Sprite.h"
#include "World/Enemy.h"

namespace sf {
template <typename T>
class Vector2;
}

class World;

class EnemyDefinition {
    template <typename T>
    friend class DefinitionDatabase;

public:
    using DefinitionId = unsigned int;
    static constexpr DefinitionId INVALID_ID =
            std::numeric_limits<DefinitionId>::max();

    EnemyDefinition(Sprite default_sprite, std::string name);
    ~EnemyDefinition() = default;

    EnemyDefinition(EnemyDefinition&& other) noexcept = default;
    EnemyDefinition& operator=(EnemyDefinition&& other) noexcept = default;

    EnemyDefinition clone() const { return EnemyDefinition(*this); }

    DefinitionId id() const { return m_id; }

    std::string name;
    Sprite default_sprite;
    double base_health = 1.0;

private:
    EnemyDefinition(const EnemyDefinition& other)
        : name(other.name), default_sprite(other.default_sprite),
          base_health(other.base_health) {}

    EnemyDefinition& operator=(const EnemyDefinition& other) = delete;

    DefinitionId m_id = INVALID_ID;
};

#endif
