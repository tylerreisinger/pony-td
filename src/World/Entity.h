#ifndef WORLD_ENTITY_H
#define WORLD_ENTITY_H

#include "IEntity.h"

#include <array>


class Entity : public IEntity {
    static constexpr int MAX_COMPONENTS = 32;

public:
    Entity(int id);
    virtual ~Entity() = default;

    virtual void update(const GameTime& time);

    int id() const { return m_id; }

private:
    int m_id;
    std::array<int, MAX_COMPONENTS> m_component_ids;
};

#endif
