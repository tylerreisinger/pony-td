#include "WorldRenderer.h"

#include <cmath>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Window/Window.hpp>

#include "Camera.h"
#include "World.h"
#include <iostream>

WorldRenderer::WorldRenderer(TileSet tile_set,
        int render_width,
        int render_height,
        sf::Vector2<int> render_origin)
    : m_tile_set(std::move(tile_set)), m_render_width(render_width),
      m_render_height(render_height), m_render_origin(render_origin)

{}


const TileSet& WorldRenderer::tile_set() const { return std::move(m_tile_set); }

void WorldRenderer::render(sf::RenderWindow& window,
        const World& world,
        const Camera& camera) const {
    double zoom = camera.zoom_factor();
    sf::Vector2<double> scaled_tile_size = {
            static_cast<double>(m_tile_set.tile_width()),
            static_cast<double>(m_tile_set.tile_height())};
    scaled_tile_size *= zoom;

    int tile_count_x = std::ceil(render_width() / scaled_tile_size.x);
    int tile_count_y = std::ceil(render_height() / scaled_tile_size.y);

    if(tile_count_x < world.width()) {
        tile_count_x = world.width();
    }
    if(tile_count_y < world.height()) {
        tile_count_y = world.height();
    }

    for(int y = 0; y < tile_count_y; ++y) {
        for(int x = 0; x < tile_count_x; ++x) {
            auto& tile = world.tile(x, y);
            auto& tile_graphic =
                    m_tile_set.graphic_for_tile(tile.floor_tile().id());
            const auto& texture = tile_graphic.texture();

            sf::Sprite sprite(texture);
            sprite.setOrigin(0, 0);
            sprite.setPosition(x * scaled_tile_size.x, y * scaled_tile_size.y);

            window.draw(sprite);
        }
    }
}
