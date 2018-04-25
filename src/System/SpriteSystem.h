#ifndef SYSTEM_SPRITESYSTEM_H
#define SYSTEM_SPRITESYSTEM_H

#include <iostream>

#include <SFML/Graphics/RenderWindow.hpp>
#include <entityx/System.h>

#include "World/Camera.h"
#include "GameTime.h"

#include "Component/Position.h"
#include "Component/Rotation.h"
#include "Component/Sprite.h"

namespace sys {

class SpriteSystem : public entityx::System<SpriteSystem> {
public:
    SpriteSystem(sf::RenderWindow& window, const Camera& camera) : m_window(&window), m_camera(&camera) {}
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
                    auto p = (sf::Vector2<double>(m_window->getSize()) / 2.0)
                        - m_camera->look_at();
                    p += position.position;
                    auto rect = s->getTextureRect();
                    s->setOrigin(rect.width / 2.0, rect.height / 2.0);
                    if(entity.has_component<comp::Rotation>()) {
                        auto rotation = entity.component<comp::Rotation>();
                        auto angle = rotation->angle;

                        s->setRotation(Deg<double>(angle).value);
                    }
                    s->setPosition(p.x, p.y);
                    m_window->draw(*s);
                });
    }

private:
    sf::RenderWindow* m_window;
    const Camera* m_camera;    
};

} // namespace sys

#endif
