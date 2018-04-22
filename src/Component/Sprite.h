#ifndef COMPONENT_SPRITE_H
#define COMPONENT_SPRITE_H

#include <utility>

#include "Graphics/Sprite.h"

namespace comp {

class Sprite {
public:
    Sprite() = default;
    ~Sprite() = default;

    Sprite(::Sprite value) : sprite(std::move(value)) {}

    Sprite(const Sprite& other) = default;
    Sprite(Sprite&& other) noexcept = default;
    Sprite& operator=(const Sprite& other) = default;
    Sprite& operator=(Sprite&& other) noexcept = default;

    ::Sprite sprite;
};

} // namespace comp

#endif
