#ifndef WORLD_ISPAWNBEHAVIOR_H
#define WORLD_ISPAWNBEHAVIOR_H

#include "AI/IBehavior.h"

class SpawnPoint;

namespace entityx {
class EntityX;
}

class ISpawnBehavior : public IBehavior {
    friend class SpawnPoint;
public:
    ISpawnBehavior() = default;
    virtual ~ISpawnBehavior() = default;

protected:
    virtual void set_parent(SpawnPoint* parent) = 0;
};

#endif
