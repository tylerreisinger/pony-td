#ifndef WORLD_FLOORTILEDEFINITION_H
#define WORLD_FLOORTILEDEFINITION_H

#include "TileProperties.h"

static constexpr int INVALID_ID = 0;

class FloorTileDirectory;

class FloorTileDefinition {
    friend class FloorTileDirectory;

public:
    FloorTileDefinition(int id, TileFlags flags = TileFlags::none());
    ~FloorTileDefinition() = default;

    FloorTileDefinition(const FloorTileDefinition& other) = delete;
    FloorTileDefinition(FloorTileDefinition&& other) noexcept = default;
    FloorTileDefinition& operator=(const FloorTileDefinition& other) = delete;
    FloorTileDefinition& operator=(
            FloorTileDefinition&& other) noexcept = default;

    int id() const;

    const TileFlags& flags() const;
    TileFlags& flags();

private:
    int m_id;
    TileFlags m_flags;
};

#endif
