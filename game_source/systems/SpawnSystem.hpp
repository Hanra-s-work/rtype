#pragma once

#include "Registry.hpp"
#include "Position.hpp"
#include "Velocity.hpp"
#include "Collider.hpp"
#include "Weapon.hpp"
#include "Health.hpp"
#include "PlayerInfo.hpp"
#include "Type.hpp"
#include "Lifetime.hpp"
#include "PowerUp.hpp"
#include "Team.hpp"

#define DEFAULT_TIMER 5.0f

float spawn_timer = DEFAULT_TIMER;
float spawn_obstacle_timer = DEFAULT_TIMER * 3;

void spawn_monster_system(Registry &r, float delta_time);
void spawn_obstacle_system(Registry &r, float delta_time);
void spawn_player(Registry &r, const float &pos_x, const float &pos_y, const std::string &username);
void spawn_monster(Registry &r, const float &pos_x, const float &pos_y);
void spawn_obstacle(Registry &r, const float &pos_x, const float &pos_y);
void spawn_missile(Registry &r, const float &pos_x, const float &pos_y, const type_enum &owner);
void spawn_powerup(Registry &r, const float &pos_x, const float &pos_y);