#ifndef WORLD_TILEGRAPHIC_H
#define WORLD_TILEGRAPHIC_H

#include <SFML/Graphics/Image.hpp>

class TileGraphic {
public:
    TileGraphic(sf::Image sprite);
    ~TileGraphic() = default;

    TileGraphic(const TileGraphic& other) = delete;
    TileGraphic(TileGraphic&& other) = default;
    TileGraphic& operator=(const TileGraphic& other) = delete;
    TileGraphic& operator=(TileGraphic&& other) = default;

private:
    sf::Image m_sprite;
};

#endif
