#ifndef PRINTUTILS_H_
#define PRINTUTILS_H_

#include <SFML/System/Vector2.hpp>
#include <ostream>

template <typename T>
std::ostream& operator<<(std::ostream& stream, const sf::Vector2<T>& vec) {
    stream << "(" << vec.x << "," << vec.y << ")";
    return stream;
}

#endif
