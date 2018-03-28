#include "WorldRenderer.h"

WorldRenderer::WorldRenderer(TileSet tile_set)
    : m_tile_set(std::move(tile_set)) {}

const TileSet& WorldRenderer::tile_set() const { return std::move(m_tile_set); }

void render(World world, Camera camera) const {}
