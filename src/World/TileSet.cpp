#include "TileSet.h"

TileSet::TileSet(int tile_width, int tile_height)
    : m_tile_width(tile_width), m_tile_height(tile_height) {}

const TileGraphic& TileSet::graphic_for_tile(int id) const {
    auto graphic_iter = m_tile_graphics.find(id);
    if(graphic_iter == m_tile_graphics.end()) {
        throw std::out_of_range("No graphic for tile " + std::to_string(id) +
                " exists in the tile set.");
    }
    return graphic_iter->second;
}

void TileSet::set_tile_graphic(int id, TileGraphic tile_graphic) {
    m_tile_graphics.insert(std::make_pair(id, std::move(tile_graphic)));
}
