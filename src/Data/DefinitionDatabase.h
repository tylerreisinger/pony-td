#ifndef DATA_DEFINITIONDATABASE_H
#define DATA_DEFINITIONDATABASE_H

#include <cassert>
#include <memory>
#include <vector>

template <typename T, typename Container>
class DefinitionHandle;

template <typename T>
class DefinitionDatabase {
public:
    using DefinitionId = typename T::DefinitionId;
    using ConstHandleType =
            DefinitionHandle<const T, const DefinitionDatabase<T>>;
    using HandleType = DefinitionHandle<T, DefinitionDatabase<T>>;

    DefinitionDatabase() = default;
    ~DefinitionDatabase() = default;

    DefinitionDatabase(const DefinitionDatabase& other) = delete;
    DefinitionDatabase(DefinitionDatabase&& other) noexcept = default;
    DefinitionDatabase& operator=(const DefinitionDatabase& other) = delete;
    DefinitionDatabase& operator=(
            DefinitionDatabase&& other) noexcept = default;

    HandleType add_definition(T definition) {
        auto id = m_next_id++;
        definition.m_id = id;
        m_definitions.emplace_back(std::move(definition));
        return HandleType(id, *this);
    }

    const T& get(DefinitionId index) const { return m_definitions[index]; }
    T& get(DefinitionId index) { return m_definitions[index]; }

    ConstHandleType operator[](DefinitionId index) const {
        assert(index < size());
        return DefinitionHandle<const T, const DefinitionDatabase<T>>(
                index, *this);
    }
    HandleType operator[](DefinitionId index) {
        assert(index < size());
        return DefinitionHandle<T, DefinitionDatabase<T>>(index, *this);
    }

    std::size_t size() const { return m_definitions.size(); }
    bool empty() const { return m_definitions.empty(); }

private:
    std::vector<T> m_definitions;

    static DefinitionId m_next_id;
};

template <typename T, typename Container = DefinitionDatabase<T>>
class DefinitionHandle {
public:
    using DefinitionId = typename T::DefinitionId;

    DefinitionHandle(DefinitionId id, Container& container)
        : m_id(id), m_container(&container) {}
    ~DefinitionHandle() = default;

    DefinitionHandle(const DefinitionHandle& other) = default;
    DefinitionHandle(DefinitionHandle&& other) noexcept = default;
    DefinitionHandle& operator=(const DefinitionHandle& other) = default;
    DefinitionHandle& operator=(DefinitionHandle&& other) noexcept = default;

    operator DefinitionHandle<const T, const Container>() const {
        return DefinitionHandle<const T, const Container>(m_id, *m_container);
    }

    bool operator==(const DefinitionHandle<T, Container>& rhs) const {
        return m_id == rhs.m_id && m_container == rhs.m_container;
    }
    template <typename OtherContainer>
    bool operator==(const DefinitionHandle<T, OtherContainer>&) const {
        return false;
    }
    bool operator!=(const DefinitionHandle<T, Container>& rhs) const {
        return !(*this == rhs);
    }
    template <typename OtherContainer>
    bool operator!=(const DefinitionHandle<T, OtherContainer>& rhs) const {
        return !(*this == rhs);
    }


    T& operator*() { return m_container->get(m_id); }
    const T& operator*() const { return m_container->get(m_id); }
    T* operator->() { return &m_container->get(m_id); }
    const T* operator->() const { return &m_container->get(m_id); }

    T* get() { return &m_container[m_id]; }
    const T* get() const { return &m_container[m_id]; }

private:
    Container* m_container;
    DefinitionId m_id;
};

template <typename T, typename Container = DefinitionDatabase<T>>
using ConstDefinitionHandle = DefinitionHandle<const T, const Container>;


template <typename T>
inline typename T::DefinitionId DefinitionDatabase<T>::m_next_id = 0;

#endif
