#ifndef SYSTEM_SPRITESYSTEM_H
#define SYSTEM_SPRITESYSTEM_H

#include <iostream>

#include <SFML/Graphics/RenderWindow.hpp>
#include <entityx/System.h>

#include "GameTime.h"

#include "Component/Position.h"
#include "Component/Sprite.h"

namespace sys {

class SpriteSystem : public entityx::System<SpriteSystem> {
public:
    SpriteSystem(sf::RenderWindow& window) : m_window(&window) {}
    ~SpriteSystem() = default;

    SpriteSystem(const SpriteSystem& other) = delete;
    SpriteSystem(SpriteSystem&& other) noexcept = delete;
    SpriteSystem& operator=(const SpriteSystem& other) = delete;
    SpriteSystem& operator=(SpriteSystem&& other) noexcept = delete;

    virtual void update(entityx::EntityManager& entity_manager,
            entityx::EventManager&,
            const GameTime&) override {
        entity_manager.each<comp::Position, comp::Sprite>(
                [this](entityx::Entity entity,
                        comp::Position& position,
                        comp::Sprite& sprite) {
                    auto& s = sprite.sprite;
                    s.setPosition(position.position.x, position.position.y);
                    m_window->draw(s);
                });
    }

private:
    sf::RenderWindow* m_window;
};

} // namespace sys

#endif
