#include "Sprite.h"

#include <cassert>

Sprite::Sprite(std::shared_ptr<sf::Texture> texture)
    : m_sprite(*texture), m_referenced_texture(std::move(texture)) {}

Sprite::Sprite(std::shared_ptr<sf::Texture> texture, sf::IntRect rectangle)
    : m_sprite(*texture, rectangle), m_referenced_texture(std::move(texture)) {}

Sprite::Sprite(sf::Sprite raw_sprite, std::shared_ptr<sf::Texture> texture)
    : m_sprite(std::move(raw_sprite)),
      m_referenced_texture(std::move(texture)) {
    assert(raw_sprite.getTexture() == texture.get());
}

Sprite Sprite::load_from_file(const std::string& file_name, sf::IntRect rect) {
    auto t = std::make_shared<sf::Texture>();
    t->loadFromFile(file_name, rect);

    sf::Sprite s(*t);

    return Sprite(std::move(s), std::move(t));
}
