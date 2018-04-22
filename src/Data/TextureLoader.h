#ifndef DATA_TEXTURELOADER_H
#define DATA_TEXTURELOADER_H

#include "AssetManager.h"

#include <memory>
#include <unordered_map>

#include <SFML/Graphics/Texture.hpp>


class TextureLoader : public AssetLoader<sf::Texture> {
public:
    TextureLoader() : AssetLoader<sf::Texture>() {}
    virtual ~TextureLoader() = default;

    TextureLoader(const TextureLoader& other) = delete;
    TextureLoader(TextureLoader&& other) noexcept = default;
    TextureLoader& operator=(const TextureLoader& other) = delete;
    TextureLoader& operator=(TextureLoader&& other) noexcept = default;

    virtual std::shared_ptr<sf::Texture> load(
            const std::string& resource_name) override;

    virtual std::size_t cache_size() const override;
    virtual void prune_expired() override;

private:
    std::shared_ptr<sf::Texture> load_new_asset(
            const std::string& resource_name);

    std::unordered_map<std::string, std::weak_ptr<sf::Texture>> m_asset_cache;
};

#endif
