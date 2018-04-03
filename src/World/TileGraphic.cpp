#include "TileGraphic.h"

#include <utility>

TileGraphic::TileGraphic(sf::Texture texture) : m_texture(std::move(texture)) {}


const sf::Texture& TileGraphic::texture() const { return m_texture; }
