#include "SpawnSystem.hpp"

void spawn_monster_system(Registry &r, float delta_time)
{
    spawn_timer -= delta_time;
    if (spawn_timer <= 0.0f) {
        float x = 1000.f; //change to random when we know window size
        float y = 400.f;
        spawn_monster(r, 1000, 400);
        spawn_timer = DEFAULT_TIMER;
    }
}

void spawn_obstacle_system(Registry &r, float delta_time)
{
    spawn_obstacle_timer -= delta_time;
    if (spawn_obstacle_timer <= 0.0f) {
        float x = 1000.f; //change to random when we know window size
        float y = 400.f;
        spawn_obstacle(r, 1000, 400);
        spawn_obstacle_timer = DEFAULT_TIMER * 3;
    }
}

void spawn_player(Registry &r, const float &pos_x, const float &pos_y, const std::string &username)
{
    Entity player = r.spawn_entity();
    r.add_component<Position>(player, {pos_x, pos_y});
    r.add_component<Velocity>(player, {0.f, 0.f});
    r.add_component<Image>(player, {image_enum::PLAYER, 20.f, 20.f});
    r.add_component<Collider>(player, {10.f});
    r.add_component<Health>(player, {3, 3});
    r.add_component<Weapon>(player, {1, .5f, 0.f});
    r.add_component<PowerUp>(player, {false});
    r.add_component<Type>(player, {type_enum::PLAYER});
    r.add_component<PlayerInfo>(player, {username});
}

void spawn_monster(Registry &r, const float &pos_x, const float &pos_y)
{
    Entity monster = r.spawn_entity();
    r.add_component<Position>(monster, {pos_x, pos_y});
    r.add_component<Velocity>(monster, {-1.f, 0.f});
    r.add_component<Image>(monster, {image_enum::MONSTER1, 20.f, 20.f});
    r.add_component<Collider>(monster, {10.f});
    r.add_component<Health>(monster, {3, 3});
    //optional r.add_component<Weapon>(monster, {1, .5f, 1.f});
    r.add_component<Type>(monster, {type_enum::MONSTER});
    //r.add_component<Behavior>(monster, {rand(DEFAULT, UP_DOWN, FOLLOW)});
    //r.add_component<LootDrop>(monster, {rand(NONE, POWERUP, HEALTH)});
    r.add_component<Lifetime>(monster, {35.f});
}

void spawn_obstacle(Registry &r, const float &pos_x, const float &pos_y)
{
    Entity obstacle = r.spawn_entity();
    r.add_component<Position>(obstacle, {pos_x, pos_y});
    r.add_component<Velocity>(obstacle, {-.25f, 0.f});
    r.add_component<Image>(obstacle, {image_enum::OBSTACLE1, 20.f, 20.f});
    //r.add_component<Collider>(obstacle, {10.f});
    //optional r.add_component<Health>(obstacle, {3, 3});
    r.add_component<Type>(obstacle, {type_enum::OBSTACLE});
    r.add_component<Lifetime>(obstacle, {60.f});
}

void spawn_missile(Registry &r, const float &pos_x, const float &pos_y, const type_enum &owner)
{
    Entity missile = r.spawn_entity();
    r.add_component<Position>(missile, {pos_x, pos_y});
    r.add_component<Velocity>(missile, {1.f, 0.f});
    r.add_component<Image>(missile, {image_enum::MISSILE1, 20.f, 20.f});
    r.add_component<Collider>(missile, {10.f});
    r.add_component<Type>(missile, {type_enum::MISSILE});
    if (owner == type_enum::PLAYER)
        r.add_component<Team>(missile, {team_enum::ALLY});
    else
        r.add_component<Team>(missile, {team_enum::MONSTER});
    r.add_component<Lifetime>(missile, {10.f});
}

void spawn_powerup(Registry &r, const float &pos_x, const float &pos_y, const loot_enum &type)
{
    Entity powerup = r.spawn_entity();
    r.add_component<Position>(powerup, {pos_x, pos_y});
    r.add_component<Velocity>(powerup, {0.f, 0.f});
    r.add_component<Image>(powerup, {image_enum::POWERUP, 20.f, 20.f});
    r.add_component<Collider>(powerup, {10.f});
    r.add_component<Type>(powerup, {type_enum::POWERUP});
    r.add_component<LootDrop>(powerup, {type});
}
