#ifndef WORLD_CAMERA_H
#define WORLD_CAMERA_H

#include <SFML/System/Vector2.hpp>

class Camera {
public:
    Camera() = default;
    Camera(sf::Vector2<int> top_left_corner, double zoom_factor);
    ~Camera() = default;

    Camera(const Camera& other) = default;
    Camera(Camera&& other) noexcept = default;
    Camera& operator=(const Camera& other) = default;
    Camera& operator=(Camera&& other) noexcept = default;

    const sf::Vector2<int>& top_left_corner() const;
    double zoom_factor() const;

private:
    sf::Vector2<int> m_top_left_corner = {0, 0};
    double m_zoom_factor = 1.0;
};

#endif
