#ifndef WORLD_DELAYSPAWNBEHAVIOR_H
#define WORLD_DELAYSPAWNBEHAVIOR_H
#include "ISpawnBehavior.h"

#include <chrono>

#include "Graphics/Sprite.h"

class SpawnPoint;

class DelaySpawnBehavior : public ISpawnBehavior {
    friend class SpawnPoint;

public:
    DelaySpawnBehavior(
            Sprite sprite, std::chrono::duration<double> spawn_delay);
    virtual ~DelaySpawnBehavior() = default;

    DelaySpawnBehavior(const DelaySpawnBehavior& other) = delete;
    DelaySpawnBehavior(DelaySpawnBehavior&& other) noexcept = default;
    DelaySpawnBehavior& operator=(const DelaySpawnBehavior& other) = delete;
    DelaySpawnBehavior& operator=(
            DelaySpawnBehavior&& other) noexcept = default;

    virtual void update(World& world,
            entityx::EntityManager& manager,
            entityx::Entity& entity,
            const GameTime& time) override;

protected:
    virtual void set_parent(SpawnPoint* parent) override;

private:
    std::chrono::duration<double> m_spawn_delay;
    std::chrono::duration<double> m_cur_delay =
            std::chrono::duration<double>(0.0);
    Sprite m_sprite;
    SpawnPoint* m_parent = nullptr;
};

#endif
