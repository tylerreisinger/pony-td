#include "Camera.h"

Camera::Camera(sf::Vector2<int> top_left_corner, double zoom_factor)
    : m_top_left_corner(top_left_corner), m_zoom_factor(zoom_factor) {}

const sf::Vector2<int>& Camera::top_left_corner() const {
    return m_top_left_corner;
}

double Camera::zoom_factor() const { return m_zoom_factor; }
