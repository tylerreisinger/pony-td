#ifndef WORLD_TARGET_H
#define WORLD_TARGET_H

#include <SFML/System/Vector2.hpp>

class World;

class Target {
public:
    Target(World& world, sf::Vector2<int> position);
    ~Target() = default;

    Target(const Target& other) = delete;
    Target(Target&& other) noexcept = default;
    Target& operator=(const Target& other) = delete;
    Target& operator=(Target&& other) noexcept = default;

    const sf::Vector2<int>& map_position() const;

private:
    World* m_world = nullptr;
    sf::Vector2<int> m_position;
};

#endif
