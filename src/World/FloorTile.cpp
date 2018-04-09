#include "FloorTile.h"

FloorTile::FloorTile(const FloorTileDefinition* definition)
    : m_definition(definition) {}

const TileFlags& FloorTile::flags() const { return m_definition->flags(); }
