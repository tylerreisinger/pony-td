#include "EnemyDefinition.h"

#include "World/World.h"

#include <SFML/System/Vector2.hpp>

#include "Component/Enemy.h"
#include "Component/Health.h"
#include "Component/Position.h"
#include "Component/Sprite.h"

EnemyDefinition::EnemyDefinition(Sprite default_sprite, std::string name)
    : name(name), default_sprite(default_sprite) {}
