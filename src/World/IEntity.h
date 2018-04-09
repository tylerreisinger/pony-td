#ifndef WORLD_IENTITY_H
#define WORLD_IENTITY_H

class GameTime;

class IEntity {
public:
    IEntity() = default;
    virtual ~IEntity() = default;

    virtual void update(const GameTime& time) = 0;
};

#endif
