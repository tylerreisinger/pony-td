#ifndef WORLD_FLOORTILE_H
#define WORLD_FLOORTILE_H

#include "FloorTileDefinition.h"

class FloorTile {
public:
    FloorTile(const FloorTileDefinition* definition);
    ~FloorTile() = default;

    FloorTile(const FloorTile& other) = default;
    FloorTile(FloorTile&& other) noexcept = default;
    FloorTile& operator=(const FloorTile& other) = default;
    FloorTile& operator=(FloorTile&& other) noexcept = default;

    int id() const { return m_definition->id(); }

private:
    const FloorTileDefinition* m_definition;
};

#endif
