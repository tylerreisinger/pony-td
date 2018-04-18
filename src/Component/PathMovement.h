#ifndef COMPONENT_PATHMOVEMENT_H
#define COMPONENT_PATHMOVEMENT_H

#include "AI/AStar.h"

namespace comp {

class PathMovement {
public:
    PathMovement() = default;
    ~PathMovement() = default;

    PathMovement(Path path): path(path) {}

    Path path;
};

}

#endif
