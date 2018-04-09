#ifndef COMPONENT_ICOMPONENT_H
#define COMPONENT_ICOMPONENT_H

#include <string>

class Entity;
class GameTime;

class IComponent {
public:
    IComponent() = default;
    virtual ~IComponent() = default;

    virtual void update(Entity& entity, const GameTime& game_time) = 0;

    virtual std::string name() const = 0;
};

#endif
