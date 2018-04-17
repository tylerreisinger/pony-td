#include "AStar.h"

#include <algorithm>
#include <cmath>
#include <limits>
#include <set>

#include "World/World.h"

#include <iomanip>
#include <iostream>

#include "PrintUtils.h"

AStar::AStar() {}

Path AStar::find_path(
        sf::Vector2<int> start, sf::Vector2<int> end, const World& world) {
    m_parents = std::vector<sf::Vector2<int>>(world.size(), {-1, -1});
    m_scores =
            std::vector<float>(world.size(), std::numeric_limits<float>::max());
    auto width = world.width();
    m_goal = end;
    m_world = &world;

    GraphNode first_point{heuristic_at(start, end), start};
    m_scores[start.x + width * start.y] = 0;
    m_open_set.insert(first_point);
    m_in_open_set.insert(start);

    while(!m_open_set.empty()) {
        auto node_iter = m_open_set.begin();
        auto node = *node_iter;
        if(node.position == end) {
            sf::Vector2<int> pos = end;
            std::vector<sf::Vector2<int>> path;

            while(pos != start) {
                path.push_back(pos);
                pos = m_parents[index_from_point(pos)];
            }

            path.push_back(start);
            std::reverse(path.begin(), path.end());

            return Path(path, m_scores[index_from_point(pos)]);
        }
        m_open_set.erase(node_iter);
        m_in_open_set.erase(m_in_open_set.find(node.position));
        m_closed_set.insert(node.position);

        auto neighbors = get_neighbors(node.position);

        for(auto pt : neighbors) {
            if(pt.x < 0 || pt.x >= world.width() || pt.y < 0 ||
                    pt.y >= world.height()) {
                continue;
            }
            if(m_closed_set.find(pt) != m_closed_set.end()) {
                continue;
            }
            if(m_in_open_set.find(pt) == m_in_open_set.end()) {
                auto is_movable = world.tile(pt.x, pt.y).is_passable();
                float g_score = 0;

                if(!is_movable) {
                    g_score = std::numeric_limits<float>::max();
                } else {
                    g_score = m_scores[index_from_point(node.position)] + 1.0;
                }

                m_open_set.emplace(g_score + heuristic_at(pt, m_goal), pt);
                if(g_score >= m_scores[index_from_point(pt)]) {
                    continue;
                }

                m_parents[index_from_point(pt)] = node.position;
                m_in_open_set.insert(pt);
                m_scores[index_from_point(pt)] = g_score;
            }
        }
    }
    return Path::make_empty();
}


float AStar::distance_between(
        const sf::Vector2<int>& start, const sf::Vector2<int>& end) const {
    auto d1 = start.x - end.x;
    auto d2 = start.y - end.y;
    return std::sqrt(d1 * d1 + d2 * d2);
}

std::array<sf::Vector2<int>, 4> AStar::get_neighbors(
        const sf::Vector2<int>& pos) {
    return {{
            sf::Vector2<int>(pos.x - 1, pos.y),
            sf::Vector2<int>(pos.x, pos.y - 1),
            sf::Vector2<int>(pos.x + 1, pos.y),
            sf::Vector2<int>(pos.x, pos.y + 1),
    }};
}

void AStar::print_cost_matrix() const {
    for(int y = 0; y < m_world->height(); ++y) {
        for(int x = 0; x < m_world->width(); ++x) {
            auto score = m_scores[x + y * m_world->width()];
            if(score != std::numeric_limits<float>::max()) {
                std::cout << std::setw(3) << score << " | ";
            } else {
                std::cout << "MAX"
                          << " | ";
            }
        }
        std::cout << "\n";
    }
}

float AStar::heuristic_at(
        const sf::Vector2<int>& start, const sf::Vector2<int>& end) const {
    return std::abs(start.x - end.x) + std::abs(start.y - end.y);
}

int AStar::index_from_point(const sf::Vector2<int>& pt) {
    return pt.x + pt.y * m_world->width();
}

Path::Path(std::vector<sf::Vector2<int>> path, double distance)
    : m_steps(path), m_distance(distance) {}

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
