#ifndef COMPONENT_VELOCITY_H
#define COMPONENT_VELOCITY_H

#include <SFML/System/Vector2.hpp>

class Velocity {
public:
    Velocity() = default;
    ~Velocity() = default;

    Velocity(double vx, double vy) : velocity(vx, vy) {}

    sf::Vector2<double> velocity;
};

#endif
