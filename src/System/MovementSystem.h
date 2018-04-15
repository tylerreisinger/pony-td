#ifndef SYSTEM_MOVEMENTSYSTEM_H
#define SYSTEM_MOVEMENTSYSTEM_H

#include <iostream>

#include <entityx/System.h>

#include "GameTime.h"
#include "PrintUtils.h"

#include "Component/Position.h"
#include "Component/Velocity.h"

namespace sys {

class MovementSystem : public entityx::System<MovementSystem> {
public:
    MovementSystem() = default;
    ~MovementSystem() = default;

    MovementSystem(const MovementSystem& other) = delete;
    MovementSystem(MovementSystem&& other) noexcept = delete;
    MovementSystem& operator=(const MovementSystem& other) = delete;
    MovementSystem& operator=(MovementSystem&& other) noexcept = delete;

    virtual void update(entityx::EntityManager& es,
            entityx::EventManager&,
            const GameTime& dt) override {
        es.each<comp::Position, comp::Velocity>(
                [dt](entityx::Entity entity,
                        comp::Position& position,
                        const comp::Velocity& velocity) {
                    position.position +=
                            velocity.velocity * dt.get_elapsed_game().count();
                });
    }
};

} // namespace sys

#endif
