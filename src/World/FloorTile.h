#ifndef WORLD_FLOORTILE_H
#define WORLD_FLOORTILE_H


class FloorTile {
public:
    FloorTile() = delete;
    ~FloorTile() = default;

    FloorTile(const FloorTile& other) = delete;
    FloorTile(FloorTile&& other) noexcept = delete;
    FloorTile& operator=(const FloorTile& other) = delete;
    FloorTile& operator=(FloorTile&& other) noexcept = delete;
    int id() const;

private:
    const int m_id;
};

#endif
