#include "WeaponSystem.hpp"
#include "SpawnSystem.hpp"

void weapon_system(Registry &r, float delta_time)
{
     auto &weapons = r.get_components<Weapon>();
     auto &positions = r.get_components<Position>();
     auto &types = r.get_components<Type>();

    for (auto &&[weapon, position, type] : Zipper(weapons, positions, types)) {
        if (!weapon) continue;

        weapon->cooldown -= delta_time;
        if (type->type != type_enum::MONSTER) continue;
        
        if (weapon->cooldown <= 0) {
            //spawn_bullet(r, position->X, position->Y);
            weapon->cooldown = 1.0f / weapon->fire_rate;
        }
    }
}