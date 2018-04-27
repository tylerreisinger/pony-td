#ifndef COMPONENT_TOWER_H
#define COMPONENT_TOWER_H

namespace comp {

class Tower {
public:
    Tower() = default;
    ~Tower() = default;

    Tower(const Tower& other) = default;
    Tower(Tower&& other) noexcept = default;
    Tower& operator=(const Tower& other) = default;
    Tower& operator=(Tower&& other) noexcept = default;
};

} // namespace comp

#endif
