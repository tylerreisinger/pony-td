#ifndef COMPONENT_PHYSICSCOMPONENT_H
#define COMPONENT_PHYSICSCOMPONENT_H

#include "IComponent.h"

#include <SFML/System/Vector2.hpp>

class PhysicsComponent : public IComponent {
public:
    PhysicsComponent() = default;
    virtual ~PhysicsComponent() = default;

    PhysicsComponent(const PhysicsComponent& other) = default;
    PhysicsComponent(PhysicsComponent&& other) noexcept = default;
    PhysicsComponent& operator=(const PhysicsComponent& other) = default;
    PhysicsComponent& operator=(PhysicsComponent&& other) noexcept = default;

    const sf::Vector2<double>& position() const;
    sf::Vector2<double>& position();
    const sf::Vector2<double>& velocity() const;
    sf::Vector2<double>& velocity();
    double facing() const;
    double& facing();

    PhysicsComponent& set_position(sf::Vector2<double> position);
    PhysicsComponent& set_velocity(sf::Vector2<double> velocity);
    PhysicsComponent& set_facing(double facing);

    virtual void update(Entity& entity, const GameTime& time) override;
    virtual std::string name() const override;

private:
    sf::Vector2<double> m_position = {0.0, 0.0};
    sf::Vector2<double> m_velocity = {0.0, 0.0};
    double m_facing = 0.0;
};

#endif
