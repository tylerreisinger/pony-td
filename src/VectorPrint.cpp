#include "VectorPrint.h"

#include <iostream>

template<typename T>
std::ostream& operator<<(std::ostream& stream, const sf::Vector2<T>& vector) {
    stream << "(" << vector.x << ", " << vector.y << ")";
    return stream; 
}
 
