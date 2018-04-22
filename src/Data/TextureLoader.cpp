#include "TextureLoader.h"


std::shared_ptr<sf::Texture> TextureLoader::load(
        const std::string& resource_name) {
    auto asset_iter = m_asset_cache.find(resource_name);
    if(asset_iter == m_asset_cache.end()) {
        return load_new_asset(resource_name);
    } else {
        auto& weak_asset = asset_iter->second;
        if(weak_asset.expired()) {
            m_asset_cache.erase(asset_iter);
            return load_new_asset(resource_name);
        } else {
            return weak_asset.lock();
        }
    }
}

std::shared_ptr<sf::Texture> TextureLoader::load_new_asset(
        const std::string& resource_name) {
    std::shared_ptr<sf::Texture> texture(new sf::Texture());
    texture->loadFromFile(resource_name);

    m_asset_cache.insert(
            std::make_pair(resource_name, std::weak_ptr<sf::Texture>(texture)));

    return texture;
}

std::size_t TextureLoader::cache_size() const { return m_asset_cache.size(); }

void TextureLoader::prune_expired() {
    for(auto it = m_asset_cache.begin(); it != m_asset_cache.end(); ++it) {
        if(it->second.expired()) {
            m_asset_cache.erase(it);
        }
    }
}
