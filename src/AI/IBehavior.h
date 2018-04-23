#ifndef AI_IBEHAVIOR_H
#define AI_IBEHAVIOR_H

namespace entityx {
class Entity;
class EntityManager;
} // namespace entityx

class GameTime;
class World;

class IBehavior {
public:
    IBehavior() = default;
    ~IBehavior() = default;

    virtual void update(World& world,
            entityx::EntityManager& manager,
            entityx::Entity& entity,
            const GameTime& time) = 0;
};

#endif
