#ifndef WORLD_TOWER_H
#define WORLD_TOWER_H

#include <SFML/System/Vector2.hpp>
#include <entityx/Entity.h>

#include "Graphics/Sprite.h"

class World;

class Tower {
public:
    Tower(World& world, Sprite sprite, sf::Vector2<int> map_cell);
    ~Tower() = default;

    Tower(const Tower& other) = delete;
    Tower(Tower&& other) noexcept = default;
    Tower& operator=(const Tower& other) = delete;
    Tower& operator=(Tower&& other) noexcept = default;

protected:
    Tower(entityx::Entity entity);

private:
    entityx::Entity m_entity;
};

#endif
