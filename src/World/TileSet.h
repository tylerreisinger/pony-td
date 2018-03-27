#ifndef WORLD_TILESET_H
#define WORLD_TILESET_H

#include <unordered_map>

#include "TileGraphic.h"

class TileSet {
public:
    TileSet() = delete;
    ~TileSet() = default;

    TileSet(const TileSet& other) = delete;
    TileSet(TileSet&& other) noexcept = delete;
    TileSet& operator=(const TileSet& other) = delete;
    TileSet& operator=(TileSet&& other) noexcept = delete;

    const TileGraphic& graphic_for_tile(int id) const;
    void set_tile_graphic(int id, TileGraphic tile_graphic);

private:
    std::unordered_map<int, TileGraphic> m_tile_graphics;
};

#endif
