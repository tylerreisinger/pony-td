#ifndef WORLD_TILESET_H
#define WORLD_TILESET_H

#include <unordered_map>

#include "TileGraphic.h"

class TileSet {
public:
    TileSet(int tile_width, int tile_height);
    ~TileSet() = default;

    TileSet(const TileSet& other) = delete;
    TileSet(TileSet&& other) noexcept = default;
    TileSet& operator=(const TileSet& other) = delete;
    TileSet& operator=(TileSet&& other) noexcept = delete;

    const TileGraphic& graphic_for_tile(int id) const;
    void set_tile_graphic(int id, TileGraphic tile_graphic);

    int tile_width() const { return m_tile_width; };
    int tile_height() const { return m_tile_height; };

private:
    std::unordered_map<int, TileGraphic> m_tile_graphics;

    int m_tile_width;
    int m_tile_height;
};

#endif
