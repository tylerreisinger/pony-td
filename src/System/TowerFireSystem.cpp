#include "TowerFireSystem.h"

#include "AI/Targeting.h"

#include "Component/Position.h"
#include "Component/Tower.h"

namespace sys {

void TowerFireSystem::update(entityx::EntityManager& es,
        entityx::EventManager&,
        const GameTime& dt) {
    es.each<comp::Tower>([this](entityx::Entity e, comp::Tower& t) {
        auto targeter = NearestGoalTargeter(
                e.component<comp::Position>()->position, 5000.0);
        targeter.find_target(*m_world);
    });
}

} // namespace sys
