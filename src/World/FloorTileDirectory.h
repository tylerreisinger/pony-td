#ifndef WORLD_FLOORTILEDIRECTORY_H
#define WORLD_FLOORTILEDIRECTORY_H

#include "FloorTileDefinition.h"
#include <memory>
#include <unordered_map>


class FloorTileDirectory {
public:
    FloorTileDirectory() = default;
    ~FloorTileDirectory() = default;

    FloorTileDirectory(const FloorTileDirectory& other) = delete;
    FloorTileDirectory(FloorTileDirectory&& other) noexcept = default;
    FloorTileDirectory& operator=(const FloorTileDirectory& other) = delete;
    FloorTileDirectory& operator=(
            FloorTileDirectory&& other) noexcept = default;

    const FloorTileDefinition& operator[](int index) const;
    std::size_t size() const;
    bool empty() const;
    void add_tile(std::unique_ptr<FloorTileDefinition> tile);

    static int get_unused_id();

private:
    std::unordered_map<int, std::unique_ptr<FloorTileDefinition>>
            m_floor_tile_map;

    static int m_next_id;
};


#endif
