#ifndef WORLD_TILEGRAPHIC_H
#define WORLD_TILEGRAPHIC_H

#include <SFML/Graphics/Texture.hpp>

class TileGraphic {
public:
    TileGraphic(sf::Texture texture);
    ~TileGraphic() = default;

    TileGraphic(const TileGraphic& other) = delete;
    TileGraphic(TileGraphic&& other) = default;
    TileGraphic& operator=(const TileGraphic& other) = delete;
    TileGraphic& operator=(TileGraphic&& other) = default;
    const sf::Texture& texture() const;

private:
    sf::Texture m_texture;
};

#endif
