#ifndef SYSTEM_BEHAVIORSYSTEM_H
#define SYSTEM_BEHAVIORSYSTEM_H

#include <entityx/System.h>

class GameTime;
class World;

namespace sys {

class BehaviorSystem : public entityx::System<BehaviorSystem> {
public:
    BehaviorSystem(World& world);
    ~BehaviorSystem() = default;

    BehaviorSystem(const BehaviorSystem& other) = delete;
    BehaviorSystem(BehaviorSystem&& other) = default;
    BehaviorSystem& operator=(const BehaviorSystem& other) = delete;
    BehaviorSystem& operator=(BehaviorSystem&& other) = default;


    virtual void update(entityx::EntityManager& es,
            entityx::EventManager&,
            const GameTime& dt) override;


private:
    World* m_world = nullptr;
};

} // namespace sys

#endif
