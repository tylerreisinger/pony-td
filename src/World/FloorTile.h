#ifndef WORLD_FLOORTILE_H
#define WORLD_FLOORTILE_H


class FloorTile {
public:
    FloorTile(int tile_id);
    ~FloorTile() = default;

    FloorTile(const FloorTile& other) = default;
    FloorTile(FloorTile&& other) noexcept = default;
    FloorTile& operator=(const FloorTile& other) = default;
    FloorTile& operator=(FloorTile&& other) noexcept = default;

    int id() const { return m_id; }

private:
    int m_id;
};

#endif
