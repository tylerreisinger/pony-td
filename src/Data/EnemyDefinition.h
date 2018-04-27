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

    Enemy build_enemy(World& world, const sf::Vector2<double>& position) const;


    std::string m_name;
    Sprite m_default_sprite;
    double m_base_health = 1.0;

private:
    EnemyDefinition(const EnemyDefinition& other)
        : m_name(other.m_name), m_default_sprite(other.m_default_sprite),
          m_base_health(other.m_base_health) {}

    EnemyDefinition& operator=(const EnemyDefinition& other) = delete;

    DefinitionId m_id = INVALID_ID;
};

#endif
