#ifndef VECTORMATH_H_
#define VECTORMATH_H_

#include <SFML/System/Vector2.hpp>
#include <cmath>
#include <type_traits>

template <typename T>
inline T magnitude(const sf::Vector2<T>& vec) {
    return std::sqrt(vec.x * vec.x + vec.y * vec.y);
}
template <typename T>
inline T magnitude2(const sf::Vector2<T>& vec) {
    return vec.x * vec.x + vec.y * vec.y;
}
template <typename T,
        typename std::enable_if<std::is_floating_point_v<T>, int>::type = 0>
inline sf::Vector2<T> normalized(sf::Vector2<T> vec) {
    return vec / magnitude(vec);
}


#endif
