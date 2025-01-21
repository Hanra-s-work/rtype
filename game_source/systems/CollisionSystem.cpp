#include "CollisionSystem.hpp"

#include "IndexedZipper.hpp"
#include "Components.hpp"
#include "SpawnSystem.hpp"

void collision_player_missile(Registry &r, std::size_t &entity1, std::size_t &entity2)
{
    auto &&[healths, teams] = r.get_component_array<Health, Team>();
    if (teams[entity2]->team == team_enum::ENEMY) {

        healths[entity1]->current -= 1;
        r.dispatcher->notify({messageType::DAMAGE, entity1, {0, 0, 0, "", {0, 0}}});

        if (healths[entity1]->current == 0) {
            r.kill_entity(Entity(entity1));
            r.dispatcher->notify({messageType::KILL, entity1, {0, 0, 0, "", {0, 0}}});
        }

        r.kill_entity(Entity(entity2));
        r.dispatcher->notify({messageType::KILL, entity2, {0, 0, 0, "", {0, 0}}});
    }
}

void collision_monster_missile(Registry &r, std::size_t &entity1, std::size_t &entity2)
{
    auto &&[healths, teams, loot_drops, positions] = r.get_component_array<Health, Team, LootDrop, Position>();
    if (teams[entity2]->team == team_enum::ALLY) {
        healths[entity1]->current -= 1;
        r.dispatcher->notify({messageType::DAMAGE, entity1, {0, 0, 0, "", {0, 0}}});

        if (healths[entity1]->current == 0) {
            auto loot = loot_drops[entity1];
            spawn_powerup(r, positions[entity1]->X, positions[entity1]->Y, loot->loot);

            r.kill_entity(Entity(entity1));
            r.dispatcher->notify({messageType::KILL, entity1, {0, 0, 0, "", {0, 0}}});
        }

        r.kill_entity(Entity(entity2));
        r.dispatcher->notify({messageType::KILL, entity2, {0, 0, 0, "", {0, 0}}});
    }
}

void collision_player_obstacle(Registry &r, std::size_t &entity1, std::size_t &entity2)
{
    auto &healths = r.get_components<Health>();
    healths[entity1]->current -= 1;
    r.dispatcher->notify({messageType::DAMAGE, entity1, {0, 0, 0, "", {0, 0}}});
}

void collision_monster_obstacle(Registry &r, std::size_t &entity1, std::size_t &entity2)
{
    //idk
}

void collision_player_powerup(Registry &r, std::size_t &entity1, std::size_t &entity2)
{
    auto &&[healths, loots] = r.get_component_array<Health, LootDrop>();
    if (loots[entity2]->loot == loot_enum::HEALTH_DROP) {
        healths[entity1]->current = healths[entity1]->max;
        r.dispatcher->notify({messageType::HEAL, entity1, {0, 0, 0, "", {0, 0}}});
    }
    else if (loots[entity2]->loot == loot_enum::POWERUP_DROP) {
        auto &powerups = r.get_components<PowerUp>();
        powerups[entity1]->enabled = true;
        r.dispatcher->notify({messageType::BUFF, entity1, {0, 0, 0, "", {0, 0}}});
    }
}

void collision_obstacle_missile(Registry &r, std::size_t &entity1, std::size_t &entity2)
{
    r.kill_entity(Entity(entity2));
    r.dispatcher->notify({messageType::KILL, entity2, {0, 0, 0, "", {0, 0}}});
}

namespace std {
    template <>
    struct hash<std::pair<type_enum, type_enum>> {
        std::size_t operator()(const std::pair<type_enum, type_enum>& p) const {
            return (hash<type_enum>()(p.first) ^ (hash<type_enum>()(p.second) << 1));
        }
    };
}

const std::unordered_map<std::pair<type_enum, type_enum>, std::function<void(Registry &, std::size_t &, std::size_t &)>> collisions = {
    {std::make_pair(type_enum::PLAYER, type_enum::MISSILE), collision_player_missile},
    {std::make_pair(type_enum::MONSTER, type_enum::MISSILE), collision_monster_missile},
    {std::make_pair(type_enum::PLAYER, type_enum::OBSTACLE), collision_player_obstacle},
    {std::make_pair(type_enum::MONSTER, type_enum::OBSTACLE), collision_monster_obstacle},
    {std::make_pair(type_enum::PLAYER, type_enum::POWERUP), collision_player_powerup},
    {std::make_pair(type_enum::OBSTACLE, type_enum::MISSILE), collision_obstacle_missile}
};

void collision_system(Registry &r, ComponentContainer<Position> &positions, ComponentContainer<Collider> &colliders, ComponentContainer<Type> &types)
{
    for (auto &&[idx1, pos1, col1, type1] : IndexedZipper(positions, colliders, types)) {
        if (!pos1 || !col1 || !type1) continue;

        for (auto &&[idx2, pos2, col2, type2] : IndexedZipper(positions, colliders, types)) {
            if (!pos2 || !col2 || !type2 || idx1 == idx2) continue;

            auto key = std::make_pair(type1->type, type2->type);
            if (collisions.find(key) != collisions.end()) {
                float dx = (pos1->X - pos2->X);
                float dy = (pos1->Y - pos2->Y);
                float distance_squared = dx * dx + dy * dy;
                float radius_sum = col1->radius + col2->radius;
                if (distance_squared <= radius_sum * radius_sum)
                    collisions.at(key)(r, idx1, idx2);
            }
        }
    }
}
