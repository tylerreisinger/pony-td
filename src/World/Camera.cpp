#include "Camera.h"

#include <utility>

Camera::Camera(sf::Vector2<double> look_at, double zoom_factor)
    : m_look_at(look_at), m_zoom_factor(zoom_factor) {}

void Camera::set_zoom_factor(double value) { m_zoom_factor = std::move(value); }

void Camera::set_look_at(sf::Vector2<double> vec) {
    m_look_at = std::move(vec);
}

const sf::Vector2<double>& Camera::look_at() const { return m_look_at; }
sf::Vector2<double>& Camera::look_at() { return m_look_at; }

double Camera::zoom_factor() const { return m_zoom_factor; }
