#ifndef GRAPHICS_SPRITE_H
#define GRAPHICS_SPRITE_H

#include <memory>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

class Sprite {
public:
    Sprite(std::shared_ptr<sf::Texture> texture);
    Sprite(std::shared_ptr<sf::Texture> texture, sf::IntRect rectangle);
    Sprite(sf::Sprite raw_sprite, std::shared_ptr<sf::Texture> texture);
    ~Sprite() = default;

    Sprite(const Sprite& other) = default;
    Sprite(Sprite&& other) noexcept = default;
    Sprite& operator=(const Sprite& other) = default;
    Sprite& operator=(Sprite&& other) noexcept = default;

    sf::Sprite& get() { return m_sprite; }
    const sf::Sprite& get() const { return m_sprite; }

    std::shared_ptr<sf::Texture>& referenced_texture() {
        return m_referenced_texture;
    }

    sf::Sprite* operator->() { return &m_sprite; };
    const sf::Sprite* operator->() const { return &m_sprite; };
    sf::Sprite& operator*() { return m_sprite; }
    const sf::Sprite& operator*() const { return m_sprite; }

    static Sprite load_from_file(
            const std::string& file_name, sf::IntRect rect = sf::IntRect());

private:
    sf::Sprite m_sprite;
    std::shared_ptr<sf::Texture> m_referenced_texture;
};

#endif
