#ifndef WORLD_ISPAWNBEHAVIOR_H
#define WORLD_ISPAWNBEHAVIOR_H

class SpawnPoint;
class World;
class GameTime;

namespace entityx {
class EntityX;
}

class ISpawnBehavior {
    friend class SpawnPoint;

public:
    ISpawnBehavior() = default;
    virtual ~ISpawnBehavior() = default;

    virtual void update(
            World& world, entityx::EntityX& ecs, const GameTime& time) = 0;

protected:
    virtual void set_parent(SpawnPoint* parent) = 0;
};

#endif
