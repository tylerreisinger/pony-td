#ifndef SYSTEM_MOVEMENTSYSTEM_H
#define SYSTEM_MOVEMENTSYSTEM_H

#include <iostream>

#include <entityx/System.h>

#include "GameTime.h"
#include "PrintUtils.h"

#include "Component/Position.h"
#include "Component/Velocity.h"

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
        es.each<Position, Velocity>([dt](entityx::Entity entity,
                                            Position& position,
                                            const Velocity& velocity) {
            position.position +=
                    velocity.velocity * dt.get_elapsed_game().count();
            std::cout << "I am at " << position.position << " with velocity "
                      << velocity.velocity << "\n";
        });
    }
};

#endif
