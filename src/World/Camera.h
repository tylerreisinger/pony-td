#ifndef WORLD_CAMERA_H
#define WORLD_CAMERA_H

#include <SFML/System/Vector2.hpp>

class Camera {
public:
    Camera() = default;
    Camera(sf::Vector2<double> look_at, double zoom_factor = 1.0);
    ~Camera() = default;

    Camera(const Camera& other) = default;
    Camera(Camera&& other) noexcept = default;
    Camera& operator=(const Camera& other) = default;
    Camera& operator=(Camera&& other) noexcept = default;

    void set_zoom_factor(double value);
    void set_look_at(sf::Vector2<double> vec);

    const sf::Vector2<double>& look_at() const;
    double zoom_factor() const;

private:
    sf::Vector2<double> m_look_at = {0.0, 0.0};
    double m_zoom_factor = 1.0;
};

#endif
