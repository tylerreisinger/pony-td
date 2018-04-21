#include "Path.h"

#include <ostream>

#include "PrintUtils.h"
#include "VectorMath.h"
#include "World/World.h"

Path::Path(std::vector<sf::Vector2<double>> path,
        double distance,
        CoordinateKind kind)
    : m_steps(path), m_distance(distance), m_kind(kind) {}

std::ostream& operator<<(std::ostream& stream, const Path& path) {
    std::size_t cnt = 0;
    for(auto step : path) {
        if(cnt < path.num_steps() - 1) {
            stream << step << " -> ";
        } else {
            stream << step;
        }
        cnt += 1;
    }
    return stream;
}

std::optional<PathDirection> Path::direction_to_step(int idx) {
    if(idx == 0 || idx > static_cast<int>(m_steps.size())) {
        return std::nullopt;
    }
    auto prev_pos = m_steps[idx - 1];
    auto pos = m_steps[idx];

    std::optional<PathDirection> x_dir;
    std::optional<PathDirection> y_dir;

    if(pos.x > prev_pos.x) {
        x_dir = PathDirection::East;
    }
    if(pos.x < prev_pos.x) {
        x_dir = PathDirection::West;
    }
    if(pos.y > prev_pos.y) {
        y_dir = PathDirection::South;
    }
    if(pos.y < prev_pos.y) {
        y_dir = PathDirection::North;
    }

    if(x_dir && !y_dir) {
        return *x_dir;
    } else if(y_dir && !x_dir) {
        return *y_dir;
    } else {
        if(x_dir == PathDirection::East) {
            if(y_dir == PathDirection::North) {
                return PathDirection::NorthEast;
            } else {
                return PathDirection::SouthEast;
            }
        } else {
            if(y_dir == PathDirection::North) {
                return PathDirection::NorthWest;
            } else {
                return PathDirection::SouthWest;
            }
        }
    }
    return std::nullopt;
}

std::ostream& operator<<(std::ostream& stream, PathDirection dir) {
    switch(dir) {
    case PathDirection::North:
        stream << "North";
        break;
    case PathDirection::NorthEast:
        stream << "NorthEast";
        break;
    case PathDirection::East:
        stream << "East";
        break;
    case PathDirection::SouthEast:
        stream << "SouthEast";
        break;
    case PathDirection::South:
        stream << "South";
        break;
    case PathDirection::SouthWest:
        stream << "SouthWest";
        break;
    case PathDirection::West:
        stream << "West";
        break;
    case PathDirection::NorthWest:
        stream << "NorthWest";
        break;
    default:
        stream << "<INVALID DIRECTION>";
        break;
    }
    return stream;
}

sf::Vector2<double> unit_vector_for_direction(PathDirection dir) {
    // 1.0 / sqrt(2). Used to keep the vectors normalized.
    static constexpr double INV_SQRT2 =
            0.7071067811865475244008443621048490392848359376884740;
    switch(dir) {
    case PathDirection::North:
        return {0.0, -1.0};
        break;
    case PathDirection::NorthEast:
        return {INV_SQRT2, -INV_SQRT2};
        break;
    case PathDirection::East:
        return {1.0, 0.0};
        break;
    case PathDirection::SouthEast:
        return {INV_SQRT2, INV_SQRT2};
        break;
    case PathDirection::South:
        return {0.0, 1.0};
        break;
    case PathDirection::SouthWest:
        return {-INV_SQRT2, INV_SQRT2};
        break;
    case PathDirection::West:
        return {-1.0, 0.0};
        break;
    case PathDirection::NorthWest:
        return {-INV_SQRT2, -INV_SQRT2};
        break;
    default:
        return {0.0, 0.0};
        break;
    }
}

sf::Vector2<double> path_anchor_offset(PathAnchor anchor, const World& world);
Path Path::as_kind(
        CoordinateKind kind, PathAnchor anchor, const World& world) const {
    // If the kinds are equivalent, copy `this`.
    if(m_kind == kind) {
        return *this;
    }
    switch(kind) {
    case CoordinateKind::WorldSpace: {
        std::vector<sf::Vector2<double>> steps;
        steps.reserve(m_steps.size());
        for(auto step : m_steps) {
            auto world_pos = world.map_to_world_pos(step) +
                    path_anchor_offset(anchor, world);
            steps.push_back(world_pos);
        }
        return Path(steps, m_distance, kind);
    }
    case CoordinateKind::MapSpace: {
        std::vector<sf::Vector2<double>> steps;
        steps.reserve(m_steps.size());
        for(auto step : m_steps) {
            auto map_pos = world.world_to_map_pos(step) -
                    path_anchor_offset(anchor, world);
            steps.push_back(map_pos);
        }
        return Path(steps, m_distance, kind);
    }
    }
}

sf::Vector2<double> path_anchor_offset(PathAnchor anchor, const World& world) {
    switch(anchor) {
    case PathAnchor::TopLeft:
        return {0.0, 0.0};
    case PathAnchor::Center:
        return sf::Vector2<double>(world.tile_dimensions()) / 2.0;
    case PathAnchor::BottomRight:
        return sf::Vector2<double>(world.tile_dimensions());
    }
}

PathTraverser::PathTraverser(Path path, int current_step)
    : m_path(std::move(path)), m_current_step(current_step) {}

sf::Vector2<double> PathTraverser::get_distance_vector(
        const sf::Vector2<double>& cur_position) const {
    return sf::Vector2<double>(next_step_goal()) - cur_position;
}

sf::Vector2<double> PathTraverser::next_step_goal() const {
    assert(m_current_step < m_path.size());
    return m_path[m_current_step];
}

sf::Vector2<double> PathTraverser::step(
        const sf::Vector2<double>& cur_position, double rate) {
    if(is_done()) {
        return cur_position;
    }
    auto distance_vec = get_distance_vector(cur_position);
    auto mag = magnitude(distance_vec);
    auto dir = distance_vec / mag;
    if(mag < rate) {
        rate -= mag;
        auto step_pos = sf::Vector2<double>(m_path[m_current_step]);
        m_current_step += 1;
        if(static_cast<std::size_t>(m_current_step) == m_path.size()) {
            return sf::Vector2<double>(m_path[m_current_step - 1]);
        }
        return step(step_pos, rate);
    }
    auto position_delta = dir * rate;
    auto position = position_delta + cur_position;

    return position;
}

bool PathTraverser::is_done() const {
    return static_cast<std::size_t>(m_current_step) == m_path.size();
}

std::ostream& operator<<(std::ostream& stream, const PathTraverser& trav) {
    for(int i = 0; i < trav.length(); ++i) {
        if(i == trav.current_step()) {
            stream << "*";
        }
        stream << trav.path()[i];
        if(i != trav.length() - 1) {
            stream << " -> ";
        }
    }
    return stream;
}
