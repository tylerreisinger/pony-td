#include "DelaySpawnBehavior.h"

#include <entityx/entityx.h>

#include "Component/PathMovement.h"
#include "Component/Position.h"
#include "Component/Sprite.h"
#include "Enemy.h"
#include "SpawnPoint.h"
#include "World.h"

DelaySpawnBehavior::DelaySpawnBehavior(Sprite sprite,
        std::chrono::duration<double> spawn_delay,
        const DefinitionDatabase<EnemyDefinition>& enemy_db)
    : m_spawn_delay(spawn_delay), m_sprite(std::move(sprite)),
      m_enemy_db(&enemy_db) {}

void DelaySpawnBehavior::update(World& world,
        entityx::EntityManager& entities,
        entityx::Entity&,
        const GameTime& time) {
    m_cur_delay += time.get_elapsed_game();
    if(m_cur_delay > m_spawn_delay) {
        m_cur_delay -= m_spawn_delay;

        auto pos = world.map_to_world_pos(
                sf::Vector2<double>(m_parent->map_position()) +
                sf::Vector2<double>{0.5, 0.5});

        Enemy e(world, (*m_enemy_db)[0], pos);

        auto path = m_parent->path_to_goal().as_kind(
                CoordinateKind::WorldSpace, PathAnchor::Center, world);
        auto trav = PathTraverser(path);

        e.entity().assign<comp::PathMovement>(trav);
    }
}

void DelaySpawnBehavior::set_parent(SpawnPoint* parent) { m_parent = parent; }
