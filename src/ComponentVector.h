#ifndef COMPONENTVECTOR_H_
#define COMPONENTVECTOR_H_

#include <deque>
#include <vector>

template <typename T>
struct ComponentBucket {
    T component;
    bool is_free = true;
};

template <typename T>
class ComponentVector {
public:
    constexpr static auto INITIAL_STORAGE = 100;
    constexpr static auto SIZE_INCREMENT = 100;

    using ComponentType = T;

    ComponentVector();
    ~ComponentVector() = default;

    ComponentVector(const ComponentVector& other) = delete;
    ComponentVector(ComponentVector&& other) = default;
    ComponentVector& operator=(const ComponentVector& other) = delete;
    ComponentVector& operator=(ComponentVector&& other) = default;

    T& operator[](std::size_t index);
    const T& operator[](std::size_t index) const;

    std::size_t size() const;
    std::size_t free_slots() const;

    T& allocate();
    void free(T component);

private:
    void resize_components(std::size_t new_size);

    std::vector<ComponentBucket<T>> m_components;
    std::deque<int> m_free_list;
};

template <typename T>
inline ComponentVector<T>::ComponentVector() : m_components(INITIAL_STORAGE) {
    for(int i = 0; i < INITIAL_STORAGE; ++i) {
        m_free_list.push_back(i);
    }
}

template <typename T>
inline std::size_t ComponentVector<T>::size() const {
    return m_components.size() - m_free_list.size();
}

template <typename T>
inline std::size_t ComponentVector<T>::free_slots() const {
    return m_free_list.size();
}

template <typename T>
inline T& ComponentVector<T>::operator[](std::size_t index) {
    return const_cast<T&>(const_cast<const ComponentVector<T>&>(*this)[index]);
}

template <typename T>
inline const T& ComponentVector<T>::operator[](std::size_t index) const {
    assert(index < m_components.size());
    auto& bin = m_components[index];
    assert(!bin.is_free);

    return bin.component;
}

template <typename T>
inline T& ComponentVector<T>::allocate() {
    if(m_free_list.size() == 0) {
        resize_components(m_components.size() + SIZE_INCREMENT);
    }

    auto index = m_free_list.front();
    m_free_list.pop_front();

    auto& bucket = m_components[index];
    bucket.is_free = false;
    bucket.component = T();
    bucket.component.id = index;
    return bucket.component;
}

template <typename T>
inline void ComponentVector<T>::resize_components(std::size_t new_size) {
    auto old_size = m_components.size();
    m_components.resize(new_size);

    for(int i = old_size; i < new_size; ++i) {
        m_free_list.push_back(i);
    }
}

template <typename T>
inline void ComponentVector<T>::free(T component) {
    auto index = component.id;
    auto& bucket = m_components[index];
    bucket.component.~T();
    bucket.is_free = true;
    m_free_list.push_front(index);
}

#endif
