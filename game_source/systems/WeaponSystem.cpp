#include "WeaponSystem.hpp"
#include "Zipper.hpp"
#include "SpawnSystem.hpp"
#include "../ECS/include/Time.hpp"

void weapon_system(Registry &r, ComponentContainer<Weapon> &weapons, ComponentContainer<Position> &positions, ComponentContainer<Type> &types)
{
    for (auto &&[weapon, position, type] : Zipper(weapons, positions, types)) {
        if (!weapon) continue;

        weapon->cooldown -= Time::deltaTime;
        if (type->type != type_enum::MONSTER) continue;
        
        if (weapon->cooldown <= 0) {
            spawn_missile(r, position->X, position->Y, type->type);
            weapon->cooldown = 1.0f / weapon->fire_rate;
        }
    }
}
