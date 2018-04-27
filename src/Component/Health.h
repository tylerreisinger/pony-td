#ifndef COMPONENT_HEALTH_H
#define COMPONENT_HEALTH_H

namespace comp {

class Health {
public:
    Health() = default;
    ~Health() = default;

    Health(double health) : health(health) {}

    Health(const Health& other) = default;
    Health(Health&& other) noexcept = default;
    Health& operator=(const Health& other) = default;
    Health& operator=(Health&& other) noexcept = default;

    double health = 0.0;
};

} // namespace comp

#endif
