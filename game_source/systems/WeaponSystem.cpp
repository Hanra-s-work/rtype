#include "WeaponSystem.hpp"
#include "IndexedZipper.hpp"
#include "SpawnSystem.hpp"
#include "Time.hpp"

void weapon_system(Registry &r, ComponentContainer<Weapon> &weapons, ComponentContainer<Position> &positions, ComponentContainer<Type> &types)
{
    for (auto &&[idx, weapon, position, type] : IndexedZipper(weapons, positions, types)) {
        if (!weapon) continue;

        weapon->cooldown -= Time::deltaTime;
         if (type->type == type_enum::MONSTER && !weapon->shot) weapon->shot = true;
        
        if (weapon->shot && weapon->cooldown <= 0) {
            spawn_missile(r, position->X, position->Y, type->type);
            r.dispatcher->notify({P_SHOOT, idx, {0, 0, 0, "", {position->X, position->Y}}});
            weapon->cooldown = 1.0f / weapon->fire_rate;
            weapon->shot = false;
        }
    }
}

void make_shot(Registry &r, std::size_t id)
{
    auto &weapons = r.get_components<Weapon>();
    if (weapons[id])
        weapons[id]->shot = true;
}
