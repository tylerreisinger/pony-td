#ifndef COMPONENT_BEHAVIOR_H
#define COMPONENT_BEHAVIOR_H

#include <memory>

#include "AI/IBehavior.h"

namespace comp {

class Behavior {
public:
    Behavior() = default;
    ~Behavior() = default;

    Behavior(std::unique_ptr<IBehavior>&& behavior)
        : behavior(std::move(behavior)) {}

    Behavior(const Behavior& other) = delete;
    Behavior(Behavior&& other) noexcept = default;
    Behavior& operator=(const Behavior& other) = delete;
    Behavior& operator=(Behavior&& other) noexcept = default;

    std::unique_ptr<IBehavior> behavior;
};

} // namespace comp

#endif
