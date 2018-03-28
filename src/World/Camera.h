#ifndef WORLD_CAMERA_H
#define WORLD_CAMERA_H

class Camera {
public:
    Camera() = delete;
    ~Camera() = default;

    Camera(const Camera& other) = delete;
    Camera(Camera&& other) noexcept = delete;
    Camera& operator=(const Camera& other) = delete;
    Camera& operator=(Camera&& other) noexcept = delete;
};

#endif
