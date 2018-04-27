#ifndef WORLD_ENEMY_H
#define WORLD_ENEMY_H

#include <entityx/Entity.h>

class Enemy {
public:
    Enemy() = delete;
    ~Enemy() = default;

    Enemy(entityx::Entity entity) : m_entity(entity) {}

    Enemy(const Enemy& other) = delete;
    Enemy(Enemy&& other) noexcept = delete;
    Enemy& operator=(const Enemy& other) = delete;
    Enemy& operator=(Enemy&& other) noexcept = delete;

private:
    entityx::Entity m_entity;
};

#endif
