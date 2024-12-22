#include "Systems.hpp"

#include "Registry.hpp"
#include "AISystem.hpp"
#include "CollisionSystem.hpp"
#include "LifetimeSystem.hpp"
#include "MovementSystem.hpp"
#include "SpawnSystem.hpp"
#include "WeaponSystem.hpp"

void setup_systems(Registry &r)
{
    r.add_system(ai_system);
    r.add_system(collision_system);
    r.add_system(lifetime_system);
    r.add_system(movement_system);
    r.add_system(spawn_monster_system);
    //r.add_system(spawn_obstacle_system);
    r.add_system(weapon_system);
}

void setup_components(Registry &r)
{
    r.register_component<Behaviour>();
    r.register_component<Collider>();
    r.register_component<Health>();
    r.register_component<Image>();
    r.register_component<Lifetime>();
    r.register_component<LootDrop>();
    r.register_component<PlayerInfo>();
    r.register_component<Position>();
    r.register_component<PowerUp>();
    r.register_component<Team>();
    r.register_component<Type>();
    r.register_component<Velocity>();
    r.register_component<Weapon>();
}
