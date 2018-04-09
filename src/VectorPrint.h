#ifndef VECTORPRINT_H_
#define VECTORPRINT_H_

#include <iostream>

#include <SFML/System/Vector2.hpp>


template<typename T>
inline std::ostream& operator<<(std::ostream& stream, const sf::Vector2<T>& vector) {
    stream << "(" << vector.x << ", " << vector.y << ")";
    return stream; 
}

#endif
