#include "SpawnSystem.hpp"

#include <iostream>
#include "Random.hpp"
#include "Registry.hpp"
#include "Time.hpp"

float spawn_timer = DEFAULT_TIMER;
float spawn_obstacle_timer = DEFAULT_TIMER * 3;

void spawn_monster_system(Registry &r)
{
    spawn_timer -= Time::deltaTime;
    if (spawn_timer <= 0.0f) {
        float x = 825.f;
        float y = randint(60, 540);
        spawn_monster(r, x, y);
        std::cout << "spawning monster..." << std::endl;
        spawn_timer = DEFAULT_TIMER;
    }
}

void spawn_obstacle_system(Registry &r)
{
    spawn_obstacle_timer -= Time::deltaTime;
    if (spawn_obstacle_timer <= 0.0f) {
        float x = 2000.f; //change to random when we know window size
        float y = 400.f;
        spawn_obstacle(r, x, y);
        spawn_obstacle_timer = DEFAULT_TIMER * 3;
    }
}

void spawn_player(Registry &r, const float &pos_x, const float &pos_y, const uint32_t &client_id, const std::string &username)
{
    Entity player = r.spawn_entity();
    r.add_component<Position>(player, {pos_x, pos_y});
    r.add_component<Image>(player, {image_enum::PLAYER_ASSET, 20.f, 20.f});
    r.add_component<Collider>(player, {10.f});
    r.add_component<Health>(player, {3, 3});
    r.add_component<Weapon>(player, {1, .5f, 0.f, false});
    r.add_component<PowerUp>(player, {false});
    r.add_component<Type>(player, {type_enum::PLAYER});
    r.add_component<PlayerInfo>(player, {client_id, username});
    GameMessage msg = {messageType::P_SPAWN, player, {0, image_enum::PLAYER_ASSET, 0, "", {pos_x, pos_y}}};
    username.copy(msg.msg.username, 8, 0);
    r.dispatcher->notify(msg);
}

void spawn_monster(Registry &r, const float &pos_x, const float &pos_y)
{
    Entity monster = r.spawn_entity();
    r.add_component<Position>(monster, {pos_x, pos_y});
    r.add_component<Velocity>(monster, {-10.f, 0.f});
    r.add_component<Image>(monster, {image_enum::MONSTER1_ASSET, 20.f, 20.f});
    r.add_component<Collider>(monster, {10.f});
    r.add_component<Health>(monster, {3, 3});
    r.add_component<Weapon>(monster, {1, .5f, 1.f, true});
    r.add_component<Type>(monster, {type_enum::MONSTER});
    r.add_component<Behaviour>(monster, {behaviour_enum::DEFAULT});
    r.add_component<LootDrop>(monster, {loot_enum::NONE});
    r.add_component<Lifetime>(monster, {35.f});
    r.dispatcher->notify({messageType::P_SPAWN, monster, {0, image_enum::MONSTER1_ASSET, 0, "", {pos_x, pos_y}}});
}

void spawn_obstacle(Registry &r, const float &pos_x, const float &pos_y)
{
    Entity obstacle = r.spawn_entity();
    r.add_component<Position>(obstacle, {pos_x, pos_y});
    r.add_component<Velocity>(obstacle, {-.25f, 0.f});
    r.add_component<Image>(obstacle, {image_enum::OBSTACLE1_ASSET, 20.f, 20.f});
    //r.add_component<Collider>(obstacle, {10.f});
    //optional r.add_component<Health>(obstacle, {3, 3});
    r.add_component<Type>(obstacle, {type_enum::OBSTACLE});
    r.add_component<Lifetime>(obstacle, {60.f});
    r.dispatcher->notify({messageType::P_SPAWN, obstacle, {0, image_enum::OBSTACLE1_ASSET, 0, "", {pos_x, pos_y}}});
}

void spawn_missile(Registry &r, const float &pos_x, const float &pos_y, const type_enum &owner)
{
    Entity missile = r.spawn_entity();
    r.add_component<Position>(missile, {pos_x, pos_y});
    r.add_component<Collider>(missile, {10.f});
    r.add_component<Type>(missile, {type_enum::MISSILE});
    if (owner == type_enum::PLAYER) {
        r.add_component<Image>(missile, {image_enum::MISSILE2_ASSET, 20.f, 20.f});
        r.add_component<Team>(missile, {team_enum::ALLY});
        r.add_component<Velocity>(missile, {2.f, 0.f});
    }
    else {
        r.add_component<Image>(missile, {image_enum::MISSILE1_ASSET, 20.f, 20.f});
        r.add_component<Team>(missile, {team_enum::ENEMY});
        r.add_component<Velocity>(missile, {-2.f, 0.f});
    }
    r.add_component<Lifetime>(missile, {10.f});
    r.dispatcher->notify({messageType::P_SPAWN, missile, {0, image_enum::MISSILE1_ASSET, 0, "", {pos_x, pos_y}}});
}

void spawn_powerup(Registry &r, const float &pos_x, const float &pos_y, const loot_enum &type)
{
    Entity powerup = r.spawn_entity();
    r.add_component<Position>(powerup, {pos_x, pos_y});
    r.add_component<Velocity>(powerup, {0.f, 0.f});
    r.add_component<Image>(powerup, {image_enum::POWERUP_ASSET, 20.f, 20.f});
    r.add_component<Collider>(powerup, {10.f});
    r.add_component<Type>(powerup, {type_enum::POWERUP});
    r.add_component<LootDrop>(powerup, {type});
    r.dispatcher->notify({messageType::P_SPAWN, powerup, {0, image_enum::POWERUP_ASSET, 0, "", {pos_x, pos_y}}});
}
