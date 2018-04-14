#include "PhysicsComponent.h"
#include "../GameTime.h"
#include "../VectorPrint.h"
#include "../World/Entity.h"

#include <iostream>

const sf::Vector2<double>& PhysicsComponent::position() const {
    return m_position;
}

sf::Vector2<double>& PhysicsComponent::position() { return m_position; }

const sf::Vector2<double>& PhysicsComponent::velocity() const {
    return m_velocity;
}

sf::Vector2<double>& PhysicsComponent::velocity() { return m_velocity; }

double PhysicsComponent::facing() const { return m_facing; }

double& PhysicsComponent::facing() { return m_facing; }

PhysicsComponent& PhysicsComponent::set_position(sf::Vector2<double> position) {
    m_position = position;
    return *this;
}

PhysicsComponent& PhysicsComponent::set_velocity(sf::Vector2<double> velocity) {
    m_velocity = velocity;
    return *this;
}

PhysicsComponent& PhysicsComponent::set_facing(double facing) {
    m_facing = facing;
    return *this;
}

void PhysicsComponent::update(Entity&, const GameTime& time) {
    m_position += m_velocity * time.get_elapsed_game().count();
}

std::string PhysicsComponent::name() const { return "PhysicsComponent"; }

std::ostream& operator<<(
        std::ostream& stream, const PhysicsComponent& physics) {
    stream << "PhysicsComponent { "
           << "position: " << physics.position()
           << ", velocity: " << physics.velocity()
           << ", facing: " << physics.facing() << " }";
    return stream;
}
