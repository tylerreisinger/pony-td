#ifndef DATA_ASSETMANAGER_H
#define DATA_ASSETMANAGER_H

#include <iostream>
#include <memory>
#include <type_traits>
#include <unordered_map>

static int next_type_id = 1;

template <typename T>
struct asset_type_id {
    using Type = T;
    static int value;
};

template <typename T>
int asset_type_id<T>::value = next_type_id++;

class AssetLoaderBase {
public:
    virtual ~AssetLoaderBase() = default;

    int type_id() const { return m_type_id; }

protected:
    AssetLoaderBase(int type_id);
    int m_type_id;
};

template <typename Concrete>
class AssetLoader : public AssetLoaderBase {
public:
    AssetLoader();
    virtual ~AssetLoader() = default;

    AssetLoader(const AssetLoader& other) = default;
    AssetLoader(AssetLoader&& other) noexcept = default;
    AssetLoader& operator=(const AssetLoader& other) = default;
    AssetLoader& operator=(AssetLoader&& other) noexcept = default;

    virtual std::shared_ptr<Concrete> load(
            const std::string& resource_name) = 0;

    virtual std::size_t cache_size() const = 0;
    virtual void prune_expired() = 0;

private:
    int m_type_id = 1;
};

class AssetManager {
public:
    AssetManager() = default;
    ~AssetManager() = default;

    AssetManager(const AssetManager& other) = delete;
    AssetManager(AssetManager&& other) noexcept = default;
    AssetManager& operator=(const AssetManager& other) = delete;
    AssetManager& operator=(AssetManager&& other) noexcept = default;

    template <typename T>
    std::shared_ptr<T> load(const std::string& resource_name) const;

    template <typename T>
    void register_loader(std::unique_ptr<AssetLoader<T>> loader);

    template <typename T>
    AssetLoader<T>& get_asset_loader() const;

private:
    std::unordered_map<int, std::unique_ptr<AssetLoaderBase>> m_loaders;
};

template <typename Concrete>
inline AssetLoader<Concrete>::AssetLoader()
    : AssetLoaderBase(asset_type_id<std::remove_cv_t<Concrete>>::value) {}

template <typename T>
inline void AssetManager::register_loader(
        std::unique_ptr<AssetLoader<T>> loader) {
    AssetLoaderBase* base_loader = loader.release();
    int type_id = base_loader->type_id();

    if(m_loaders.find(type_id) != m_loaders.end()) {
        std::cout << "WARNING: Replacing an existing asset loader."
                  << std::endl;
    }

    m_loaders.insert(std::make_pair(
            type_id, std::unique_ptr<AssetLoaderBase>(base_loader)));
}

template <typename T>
inline std::shared_ptr<T> AssetManager::load(
        const std::string& resource_name) const {
    auto& loader = get_asset_loader<T>();

    return loader.load(resource_name);
}

template <typename T>
inline AssetLoader<T>& AssetManager::get_asset_loader() const {
    int type_id = asset_type_id<T>::value;
    auto iter = m_loaders.find(type_id);

    if(iter == m_loaders.end()) {
        throw std::runtime_error("Trying to load an unknown resource type!");
    }

    AssetLoader<T>& loader = static_cast<AssetLoader<T>&>(*iter->second.get());
    return loader;
}

#endif
