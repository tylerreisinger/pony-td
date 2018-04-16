#ifndef WORLD_SPAWNPOINT_H
#define WORLD_SPAWNPOINT_H

#include <random>

#include <SFML/System/Vector2.hpp>

class World;

class SpawnPoint {
public:
    SpawnPoint(World& world, sf::Vector2<int> position);
    ~SpawnPoint() = default;

    SpawnPoint(const SpawnPoint& other) = delete;
    SpawnPoint(SpawnPoint&& other) noexcept = default;
    SpawnPoint& operator =(const SpawnPoint& other) = delete;
    SpawnPoint& operator =(SpawnPoint&& other) noexcept = default;

    const sf::Vector2<int>& map_position() const;

    template <typename Rng>
    sf::Vector2<double> get_spawn_location(Rng& rng) const {
        std::uniform_real_distribution<double> distribution(0.0, 1.0);
        auto x = distribution(rng);
        auto y = distribution(rng);

        return sf::Vector2<double>(m_map_position.x + x, m_map_position.y + y);
    }

private:
    sf::Vector2<int> m_map_position;
    World* m_world = nullptr;
};

#endif
