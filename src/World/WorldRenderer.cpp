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

    sf::Vector2<double> world_start_pos = {
            camera.look_at().x - static_cast<double>(window.getSize().x) / 2,
            camera.look_at().y - static_cast<double>(window.getSize().y) / 2,
    };

    sf::Vector2<double> drawing_offset = {
            -std::min(0.0, world_start_pos.x),
            -std::min(0.0, world_start_pos.y),
    };

    sf::Vector2<int> tile_offset = {
            std::max(0,
                    static_cast<int>(std::floor(
                            world_start_pos.x / scaled_tile_size.x))),
            std::max(0,
                    static_cast<int>(std::floor(
                            world_start_pos.y / scaled_tile_size.y)))};

    if(world_start_pos.x > 0.0) {
        drawing_offset.x = -std::fmod(world_start_pos.x, scaled_tile_size.x);
    }
    if(world_start_pos.y > 0.0) {
        drawing_offset.y = -std::fmod(world_start_pos.y, scaled_tile_size.y);
    }

    int tile_count_x = std::ceil(render_width() / scaled_tile_size.x);
    int tile_count_y = std::ceil(render_height() / scaled_tile_size.y);
    tile_count_x = std::min(world.width(), tile_count_x);
    tile_count_y = std::min(world.height(), tile_count_y);
    tile_count_x = std::min(world.width() - tile_offset.x, tile_count_x);
    tile_count_y = std::min(world.height() - tile_offset.y, tile_count_y);

    for(int y = 0; y < tile_count_y; ++y) {
        for(int x = 0; x < tile_count_x; ++x) {
            auto& tile = world.tile(tile_offset.x + x, tile_offset.y + y);
            auto& tile_graphic =
                    m_tile_set.graphic_for_tile(tile.floor_tile().id());
            const auto& texture = tile_graphic.texture();

            sf::Sprite sprite(texture);
            sprite.setOrigin(0, 0);
            sprite.setPosition(drawing_offset.x + x * scaled_tile_size.x,
                    drawing_offset.y + y * scaled_tile_size.y);

            window.draw(sprite);
        }
    }
}
