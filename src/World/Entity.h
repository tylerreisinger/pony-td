#ifndef WORLD_ENTITY_H
#define WORLD_ENTITY_H

#include "../Component/PhysicsComponent.h"
#include "IEntity.h"

class Entity : public IEntity {
    template <typename Component>
    friend Component* get_component(Entity& entity);
    template <typename Component>
    friend const Component* get_component(const Entity& entity);

public:
    Entity() = default;
    virtual ~Entity() = default;

    virtual void update(const GameTime& time);

private:
    PhysicsComponent m_physics_component;
};

template <typename Component>
Component* get_component(Entity& entity);
template <typename Component>
const Component* get_component(const Entity& entity);

template <>
inline PhysicsComponent* get_component<PhysicsComponent>(Entity& entity) {
    return &entity.m_physics_component;
}
template <>
inline const PhysicsComponent* get_component<PhysicsComponent>(
        const Entity& entity) {
    return &entity.m_physics_component;
}

#endif
