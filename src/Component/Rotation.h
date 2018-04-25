#ifndef COMPONENT_ROTATION_H
#define COMPONENT_ROTATION_H

#include "Angle.h"

namespace comp {

class Rotation {
public:
    Rotation() = default;
    ~Rotation() = default;

    Rotation(Rad<double> angle) : angle(angle) {}

    Rotation(const Rotation& other) = default;
    Rotation(Rotation&& other) noexcept = default;
    Rotation& operator=(const Rotation& other) = default;
    Rotation& operator=(Rotation&& other) noexcept = default;

    Rad<double> angle;
};

} // namespace comp

#endif
