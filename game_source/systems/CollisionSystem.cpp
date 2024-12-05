#include "CollisionSystem.hpp"

void collision_player_missile(Registry &r, size_t &entity1, size_t &entity2)
{

}

void collision_monster_missile(Registry &r, size_t &entity1, size_t &entity2)
{

}

void collision_player_obstacle(Registry &r, size_t &entity1, size_t &entity2)
{

}

void collision_monster_obstacle(Registry &r, size_t &entity1, size_t &entity2)
{

}

void collision_player_powerup(Registry &r, size_t &entity1, size_t &entity2)
{

}

void collision_obstacle_missile(Registry &r, size_t &entity1, size_t &entity2)
{

}

const std::unordered_map<std::pair<type_enum, type_enum>, std::function<void(Registry &, size_t &, size_t &)>> collisions = {
    {std::make_pair(type_enum::PLAYER, type_enum::MISSILE), collision_player_missile},
    {std::make_pair(type_enum::MONSTER, type_enum::MISSILE), collision_monster_missile},
    {std::make_pair(type_enum::PLAYER, type_enum::OBSTACLE), collision_player_obstacle},
    {std::make_pair(type_enum::MONSTER, type_enum::OBSTACLE), collision_monster_obstacle},
    {std::make_pair(type_enum::PLAYER, type_enum::POWERUP), collision_player_powerup},
    {std::make_pair(type_enum::OBSTACLE, type_enum::MISSILE), collision_obstacle_missile}
};

void collision_system(Registry &r)
{
    auto &positions = r.get_components<Position>();
    auto &colliders = r.get_components<Collider>();
    auto &types = r.get_components<Type>();

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
