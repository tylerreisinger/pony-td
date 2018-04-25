#ifndef AI_ASTAR_H
#define AI_ASTAR_H

#include <iosfwd>
#include <set>
#include <unordered_set>
#include <vector>
#include <optional>

#include <SFML/System/Vector2.hpp>

#include "VectorMath.h"
#include "World/Path.h"


class World;

struct GraphNode {
    GraphNode(float score_, sf::Vector2<int> position_)
        : score(score_), position(position_) {}
    float score;
    sf::Vector2<int> position;
};

namespace std {
template <>
struct less<GraphNode> {
    constexpr bool operator()(
            const GraphNode& lhs, const GraphNode& rhs) const {
        return lhs.score < rhs.score;
    }
};
} // namespace std

class AStar {
public:
    using ClosedListType = std::unordered_set<sf::Vector2<int>>;
    using OpenListType = std::set<GraphNode>;
    AStar();
    ~AStar() = default;

    AStar(const AStar& other) = delete;
    AStar(AStar&& other) noexcept = delete;
    AStar& operator=(const AStar& other) = delete;
    AStar& operator=(AStar&& other) noexcept = delete;

    Path find_path(
            sf::Vector2<int> start, sf::Vector2<int> end, const World& world);

    void print_cost_matrix() const;

private:
    float heuristic_at(
            const sf::Vector2<int>& start, const sf::Vector2<int>& end) const;
    float distance_between(
            const sf::Vector2<int>& start, const sf::Vector2<int>& end) const;
    std::array<sf::Vector2<int>, 4> get_neighbors(const sf::Vector2<int>& pos);

    int index_from_point(const sf::Vector2<int>& pt);

    ClosedListType m_closed_set;
    OpenListType m_open_set;
    std::unordered_set<sf::Vector2<int>> m_in_open_set;

    std::vector<float> m_scores;
    std::vector<sf::Vector2<int>> m_parents;

    sf::Vector2<int> m_goal;
    const World* m_world;
};

std::ostream& operator<<(std::ostream& stream, const Path& path);

#endif
