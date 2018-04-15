#ifndef COMPONENT_SPRITE_H
#define COMPONENT_SPRITE_H

#include <utility>

#include <SFML/Graphics/Sprite.hpp>

namespace comp {

class Sprite {
public:
    Sprite() = default;
    ~Sprite() = default;

    Sprite(sf::Sprite value) : sprite(std::move(value)) {}

    Sprite(const Sprite& other) = default;
    Sprite(Sprite&& other) noexcept = default;
    Sprite& operator=(const Sprite& other) = default;
    Sprite& operator=(Sprite&& other) noexcept = default;

    sf::Sprite sprite;
};

} // namespace comp

#endif
