#ifndef COMPONENT_PATHMOVEMENT_H
#define COMPONENT_PATHMOVEMENT_H

#include "World/Path.h"

namespace comp {

class PathMovement {
public:
    PathMovement() = default;
    ~PathMovement() = default;

    PathMovement(PathTraverser path) : path(path) {}

    PathTraverser path;
};

}

#endif
