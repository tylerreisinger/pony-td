#ifndef SYSTEM_PATHMOVEMENTSYSTEM_H
#define SYSTEM_PATHMOVEMENTSYSTEM_H

#include <entityx/System.h>

#include "Component/Position.h"
#include "Component/PathMovement.h"

class World;

namespace sys {

class PathMovementSystem: public entityx::System<PathMovementSystem> {
public:
    PathMovementSystem(World& world);
    ~PathMovementSystem() = default;

    PathMovementSystem(const PathMovementSystem& other) = delete;
    PathMovementSystem(PathMovementSystem&& other) noexcept = delete;
    PathMovementSystem& operator =(const PathMovementSystem& other) = delete;
    PathMovementSystem& operator =(PathMovementSystem&& other) noexcept = delete;

    virtual void update(entityx::EntityManager& es,
            entityx::EventManager&,
            const GameTime& dt) override;


private:
    World* m_world = nullptr;
};

}

#endif
