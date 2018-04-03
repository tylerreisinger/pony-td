#include "MapTile.h"

#include <utility>

MapTile::MapTile(FloorTile floor_tile) : m_floor_tile(std::move(floor_tile)) {}

const FloorTile& MapTile::floor_tile() const { return m_floor_tile; }
