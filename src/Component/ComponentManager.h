#ifndef COMPONENT_COMPONENTMANAGER_H_
#define COMPONENT_COMPONENTMANAGER_H_

#include "../ComponentVector.h"
#include "PhysicsComponent.h"

class ComponentManager {
    template <typename T>
    friend ComponentVector<T>& get_component_vector(ComponentManager& manager);
    template <typename T>
    friend const ComponentVector<T>& get_component_vector(
            const ComponentManager& manager);

public:
    ComponentManager();
    ~ComponentManager() = default;

    ComponentManager(const ComponentManager& other) = delete;
    ComponentManager(ComponentManager&& other) = default;
    ComponentManager& operator=(const ComponentManager& other) = delete;
    ComponentManager& operator=(ComponentManager&& other) = default;

private:
    ComponentVector<PhysicsComponent> m_physics_components;
};

template <typename T>
ComponentVector<T>& get_component_vector(ComponentManager& manager);
template <typename T>
const ComponentVector<T>& get_component_vector(const ComponentManager& manager);

template <>
ComponentVector<PhysicsComponent>& get_component_vector(
        ComponentManager& manager) {
    return manager.m_physics_components;
}
template <>
const ComponentVector<PhysicsComponent>& get_component_vector(
        const ComponentManager& manager) {
    return manager.m_physics_components;
}

#endif
