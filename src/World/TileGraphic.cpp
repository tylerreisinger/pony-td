#include "TileGraphic.h"

#include <memory>

TileGraphic::TileGraphic(sf::Image sprite) : m_sprite(std::move(sprite)) {}
