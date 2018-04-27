#ifndef SYSTEM_TOWERFIRESYSTEM_H
#define SYSTEM_TOWERFIRESYSTEM_H

#include <entityx/System.h>

class GameTime;
class World;

namespace sys {

class TowerFireSystem : public entityx::System<TowerFireSystem> {
public:
    TowerFireSystem(World& world) : m_world(&world) {}
    virtual ~TowerFireSystem() = default;

    TowerFireSystem(const TowerFireSystem& other) = delete;
    TowerFireSystem(TowerFireSystem&& other) = default;
    TowerFireSystem& operator=(const TowerFireSystem& other) = delete;
    TowerFireSystem& operator=(TowerFireSystem&& other) = default;

    virtual void update(entityx::EntityManager& es,
            entityx::EventManager&,
            const GameTime& dt) override;

private:
    World* m_world = nullptr;
};

} // namespace sys

#endif
