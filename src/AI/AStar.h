#ifndef AI_ASTAR_H
#define AI_ASTAR_H

#include <iosfwd>
#include <set>
#include <unordered_set>
#include <vector>
#include <optional>

#include <SFML/System/Vector2.hpp>


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
template <>
struct hash<sf::Vector2<int>> {
    size_t operator()(const sf::Vector2<int>& x) const {
        return hash<uint64_t>()(x.x << sizeof(int) | x.y);
    }
};
} // namespace std

enum class PathDirection {
    North,
    East,
    South,
    West,

    NorthEast,
    SouthEast,
    SouthWest,
    NorthWest,
};

std::ostream& operator <<(std::ostream& stream, PathDirection dir);
sf::Vector2<double> unit_vector_for_direction(PathDirection dir);

class Path {
public:
    static constexpr int NOT_ON_PATH = -1;
    using iterator = std::vector<sf::Vector2<int>>::iterator;
    using const_iterator = std::vector<sf::Vector2<int>>::const_iterator;

    Path() = default;
    Path(std::vector<sf::Vector2<int>> path, double distance);
    ~Path() = default;

    Path(const Path& other) = default;
    Path(Path&& other) noexcept = default;
    Path& operator=(const Path& other) = default;
    Path& operator=(Path&& other) noexcept = default;

    int current_step(const sf::Vector2<int>& pos) const;
    std::optional<PathDirection> direction_to_step(int index);

    sf::Vector2<int> operator[](std::size_t index) const {
        return m_steps[index];
    }

    std::size_t num_steps() const { return m_steps.size(); }
    std::size_t size() const { return m_steps.size(); }
    const std::vector<sf::Vector2<int>> steps() const {
        return m_steps;
    }

    const_iterator begin() const { return m_steps.begin(); }
    const_iterator end() const { return m_steps.end(); }
    const_iterator cbegin() const { return m_steps.cbegin(); }
    const_iterator cend() const { return m_steps.cend(); }

    double total_distance() const { return m_distance; }

    static Path make_empty() { return Path(); }

private:
    std::vector<sf::Vector2<int>> m_steps;
    double m_distance = 0.0;
};


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
