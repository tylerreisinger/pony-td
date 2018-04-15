#ifndef COMPONENT_POSITION_H
#define COMPONENT_POSITION_H

#include <SFML/System/Vector2.hpp>

namespace comp {

class Position {
public:
    Position() = default;
    ~Position() = default;

    Position(double x, double y) : position(x, y) {}

    sf::Vector2<double> position;
};

} // namespace comp

#endif
