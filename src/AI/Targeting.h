#ifndef AI_TARGETING_H
#define AI_TARGETING_H

#include <SFML/System/Vector2.hpp>

class World;

class ITargeter {
public:
    ITargeter() = default;
    virtual ~ITargeter() = default;

    virtual void find_target(World& world) const = 0;
};

class Targeter : public ITargeter {
public:
    Targeter(sf::Vector2<double> origin, double max_radius);
    ~Targeter() = default;

    const sf::Vector2<double> origin() const { return m_origin; }
    double max_radius() const { return m_max_radius; }

private:
    sf::Vector2<double> m_origin;
    double m_max_radius;
};

class NearestGoalTargeter : public Targeter {
public:
    NearestGoalTargeter(sf::Vector2<double> origin, double max_radius)
        : Targeter(origin, max_radius) {}
    virtual ~NearestGoalTargeter() = default;

    NearestGoalTargeter(const NearestGoalTargeter& other) = default;
    NearestGoalTargeter(NearestGoalTargeter&& other) noexcept = default;
    NearestGoalTargeter& operator=(const NearestGoalTargeter& other) = default;
    NearestGoalTargeter& operator=(
            NearestGoalTargeter&& other) noexcept = default;

    virtual void find_target(World& world) const override;
};

#endif
