#ifndef WORLD_TILEPROPERTIES_H
#define WORLD_TILEPROPERTIES_H

#include <cstdint>
#include <ostream>

#include "../Flags.h"

enum class TileFlag : uint64_t {
    Movable = 1 << 0,
    Buildable = 1 << 1,
    Flyable = 1 << 2,
};

using TileFlags = flags::Flags<TileFlag>;

inline std::ostream& operator<<(std::ostream& stream, TileFlag flag) {
    switch(flag) {
    case TileFlag::Movable:
        stream << "Movable";
        break;
    case TileFlag::Buildable:
        stream << "Buildable";
        break;
    case TileFlag::Flyable:
        stream << "Flyable";
        break;
    default:
        break;
    }

    return stream;
}

#endif
