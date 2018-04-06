#include "CameraController.h"

#include <SFML/Window/Keyboard.hpp>
#include <algorithm>

#include "World.h"
#include "WorldRenderer.h"

void CameraController::update(const GameTime& game_time,
        Camera& camera,
        const World& world,
        const WorldRenderer& renderer) {
    update_zoom(game_time, camera);
    update_look_at(game_time, camera, world, renderer);
}

void CameraController::update_zoom(const GameTime& game_time, Camera& camera) {
    auto step = m_zoom_velocity * game_time.get_elapsed_wall().count();

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::X)) {
        auto new_value = camera.zoom_factor() - step;
        camera.set_zoom_factor(std::max(0.25, new_value));
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
        auto new_value = camera.zoom_factor() + step;
        camera.set_zoom_factor(std::min(5.0, new_value));
    }
}

void CameraController::update_look_at(const GameTime& game_time,
        Camera& camera,
        const World& world,
        const WorldRenderer& renderer) {
    auto step = m_move_velocity * game_time.get_elapsed_wall().count();

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        camera.look_at().x += step;
        camera.look_at().x =
                std::min(static_cast<double>(world.width() *
                                 renderer.tile_set().tile_width()) *
                                camera.zoom_factor(),
                        camera.look_at().x);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        camera.look_at().x -= step;
        camera.look_at().x = std::max(0.0, camera.look_at().x);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        camera.look_at().y += step;
        camera.look_at().y =
                std::min(static_cast<double>(world.height() *
                                 renderer.tile_set().tile_height()) *
                                camera.zoom_factor(),
                        camera.look_at().y);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        camera.look_at().y -= step;
        camera.look_at().y = std::max(0.0, camera.look_at().y);
    }
}

double CameraController::move_velocity() const { return m_move_velocity; }

double CameraController::zoom_velocity() const { return m_zoom_velocity; }

void CameraController::set_zoom_velocity(double velocity) {
    m_zoom_velocity = velocity;
}

void CameraController::set_move_velocity(double velocity) {
    m_move_velocity = velocity;
}
