#include "FloorTileDirectory.h"

#include <cassert>
#include <limits>
#include <utility>

int FloorTileDirectory::m_next_id = 1;

const FloorTileDefinition& FloorTileDirectory::operator[](int index) const {
    auto iter = m_floor_tile_map.find(index);
    if(iter != m_floor_tile_map.end()) {
        return *std::get<1>(*iter);
    } else {
        throw std::out_of_range(
                "The floor tile " + std::to_string(index) + " is not defined.");
    }
}

std::size_t FloorTileDirectory::size() const { return m_floor_tile_map.size(); }

bool FloorTileDirectory::empty() const { return m_floor_tile_map.empty(); }

void FloorTileDirectory::add_tile(std::unique_ptr<FloorTileDefinition> tile) {
    int id = tile->id();
    if(id == INVALID_ID) {
        assert(m_next_id != std::numeric_limits<int>::max() &&
                "Exceeded maximum floor tile id");
        id = m_next_id++;
        tile->m_id = id;
    }
    assert(id > 0 && "Floor tile ids must be positive integers");
    auto ret = m_floor_tile_map.insert(std::make_pair(id, std::move(tile)));
    if(std::get<bool>(ret) == false) {
        throw std::invalid_argument(
                "The floor tile " + std::to_string(id) + " already exists.");
    }
    if(id > m_next_id) {
        assert(id != std::numeric_limits<int>::max() &&
                "Exceeded maximum floor tile id");
        m_next_id = id + 1;
    }
}

int FloorTileDirectory::get_unused_id() { return m_next_id++; }
