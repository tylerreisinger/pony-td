#ifndef WORLD_WORLDRENDERER_H
#define WORLD_WORLDRENDERER_H

#include "Camera.h"
#include "TileSet.h"
#include "World.h"


class WorldRenderer {
public:
    WorldRenderer() = delete;
    ~WorldRenderer() = default;

    WorldRenderer(const WorldRenderer& other) = delete;
    WorldRenderer(WorldRenderer&& other) noexcept = delete;
    WorldRenderer& operator=(const WorldRenderer& other) = delete;
    WorldRenderer& operator=(WorldRenderer&& other) noexcept = delete;
    const TileSet& tile_set() const;
    void render(World world, Camera camera) const;

private:
    TileSet m_tile_set;
};

#endif
