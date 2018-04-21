#ifndef WORLD_PATH_H
#define WORLD_PATH_H

#include <iosfwd>
#include <optional>
#include <vector>

#include <SFML/System/Vector2.hpp>

class World;

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

enum class PathAnchor {
    TopLeft,
    Center,
    BottomRight,
};

enum class CoordinateKind {
    MapSpace,
    WorldSpace,
};

std::ostream& operator<<(std::ostream& stream, PathDirection dir);
sf::Vector2<double> unit_vector_for_direction(PathDirection dir);

class Path {
public:
    static constexpr int NOT_ON_PATH = -1;
    using iterator = std::vector<sf::Vector2<double>>::iterator;
    using const_iterator = std::vector<sf::Vector2<double>>::const_iterator;

    Path() = default;
    Path(std::vector<sf::Vector2<double>> path,
            double distance,
            CoordinateKind kind);
    ~Path() = default;

    Path(const Path& other) = default;
    Path(Path&& other) noexcept = default;
    Path& operator=(const Path& other) = default;
    Path& operator=(Path&& other) noexcept = default;

    std::optional<PathDirection> direction_to_step(int index);

    Path as_kind(
            CoordinateKind kind, PathAnchor anchor, const World& world) const;

    sf::Vector2<double> operator[](std::size_t index) const {
        return m_steps[index];
    }

    std::size_t num_steps() const { return m_steps.size(); }
    std::size_t size() const { return m_steps.size(); }
    const std::vector<sf::Vector2<double>> steps() const { return m_steps; }

    const_iterator begin() const { return m_steps.begin(); }
    const_iterator end() const { return m_steps.end(); }
    const_iterator cbegin() const { return m_steps.cbegin(); }
    const_iterator cend() const { return m_steps.cend(); }

    double total_distance() const { return m_distance; }
    CoordinateKind kind() const { return m_kind; }

    static Path make_empty() { return Path(); }

private:
    std::vector<sf::Vector2<double>> m_steps;
    double m_distance = 0.0;
    CoordinateKind m_kind = CoordinateKind::MapSpace;
};

class PathTraverser {
public:
    PathTraverser(Path path, int current_step = 1);
    ~PathTraverser() = default;

    PathTraverser(const PathTraverser& other) = default;
    PathTraverser(PathTraverser&& other) noexcept = default;
    PathTraverser& operator=(const PathTraverser& other) = default;
    PathTraverser& operator=(PathTraverser&& other) noexcept = default;

    bool is_done() const;

    const Path& path() const { return m_path; }
    int current_step() const { return m_current_step; }
    int length() const { return m_path.size(); }
    int size() const { return length(); }

    sf::Vector2<double> step(
            const sf::Vector2<double>& cur_position, double rate);
    sf::Vector2<double> get_distance_vector(
            const sf::Vector2<double>& cur_position) const;
    sf::Vector2<double> next_step_goal() const;

private:
    Path m_path;
    int m_current_step;
};

std::ostream& operator<<(std::ostream& stream, const PathTraverser& trav);

#endif
