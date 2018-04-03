#ifndef WORLD_WORLDRENDERER_H
#define WORLD_WORLDRENDERER_H

#include "TileSet.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>

class Camera;
class World;

namespace sf {
class Window;
}

class WorldRenderer {
public:
    WorldRenderer(TileSet tile_set,
            int render_width,
            int render_height,
            sf::Vector2<int> render_origin = {0, 0});
    ~WorldRenderer() = default;

    WorldRenderer(const WorldRenderer& other) = delete;
    WorldRenderer(WorldRenderer&& other) noexcept = default;
    WorldRenderer& operator=(const WorldRenderer& other) = delete;
    WorldRenderer& operator=(WorldRenderer&& other) noexcept = default;

    const TileSet& tile_set() const;
    void render(sf::RenderWindow& window,
            const World& world,
            const Camera& camera) const;

    const sf::Vector2<int>& render_origin() const { return m_render_origin; }
    int render_width() const { return m_render_width; }
    int render_height() const { return m_render_height; }

private:
    TileSet m_tile_set;

    sf::Vector2<int> m_render_origin = {0, 0};
    int m_render_width;
    int m_render_height;
};

#endif
