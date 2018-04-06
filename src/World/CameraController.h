#ifndef WORLD_CAMERACONTROLLER_H
#define WORLD_CAMERACONTROLLER_H

#include "../GameTime.h"
#include "Camera.h"

class WorldRenderer;
class World;

class CameraController {
public:
    CameraController() = default;
    ~CameraController() = default;

    CameraController(const CameraController& other) = delete;
    CameraController(CameraController&& other) noexcept = delete;
    CameraController& operator=(const CameraController& other) = delete;
    CameraController& operator=(CameraController&& other) noexcept = delete;

    void update(const GameTime& game_time,
            Camera& camera,
            const World& world,
            const WorldRenderer& renderer);
    double move_velocity() const;
    double zoom_velocity() const;
    void set_zoom_velocity(double velocity);
    void set_move_velocity(double velocity);

private:
    void update_zoom(const GameTime& game_time, Camera& camera);
    void update_look_at(const GameTime& game_time,
            Camera& camera,
            const World& world,
            const WorldRenderer& renderer);

    double m_zoom_velocity = 0.50;
    double m_move_velocity = 400.0;
};

#endif
