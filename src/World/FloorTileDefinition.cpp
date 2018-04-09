#include "FloorTileDefinition.h"

FloorTileDefinition::FloorTileDefinition(int id, TileFlags flags)
    : m_id(id), m_flags(flags) {}

int FloorTileDefinition::id() const { return m_id; }

const TileFlags& FloorTileDefinition::flags() const { return m_flags; }

TileFlags& FloorTileDefinition::flags() { return m_flags; }
