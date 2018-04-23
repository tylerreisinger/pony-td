#include "BehaviorSystem.h"

#include "GameTime.h"
#include "World/World.h"

#include "Component/Behavior.h"

namespace sys {

BehaviorSystem::BehaviorSystem(World& world) : m_world(&world) {}

void BehaviorSystem::update(entityx::EntityManager& es,
        entityx::EventManager&,
        const GameTime& dt) {
    es.each<comp::Behavior>(
            [this, &es, dt](entityx::Entity e, comp::Behavior& b) {
                b.behavior->update(*m_world, es, e, dt);
            });
}

} // namespace sys
