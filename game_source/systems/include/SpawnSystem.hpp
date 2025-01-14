#pragma once

#include "Components.hpp"

class Registry;

#define DEFAULT_TIMER 5.0f

/**
 * @brief Spawns a monster at the specified position.
 * 
 * This function spawns a monster entity in the game at the given position (`pos_x`, `pos_y`). The monster
 * is initialized with appropriate components, such as position and type.
 * 
 * @param r The `Registry` that contains all game entities and their components.
 * @param pos_x The X-coordinate for the monster's initial position.
 * @param pos_y The Y-coordinate for the monster's initial position.
 */
void spawn_monster(Registry &r, const float &pos_x, const float &pos_y);

/**
 * @brief Spawns an obstacle at the specified position.
 * 
 * This function spawns an obstacle entity in the game at the given position (`pos_x`, `pos_y`). The obstacle
 * is initialized with appropriate components, such as position and type.
 * 
 * @param r The `Registry` that contains all game entities and their components.
 * @param pos_x The X-coordinate for the obstacle's initial position.
 * @param pos_y The Y-coordinate for the obstacle's initial position.
 */
void spawn_obstacle(Registry &r, const float &pos_x, const float &pos_y);

/**
 * @brief Spawns a player with the specified username at the given position.
 * 
 * This function spawns a player entity in the game with the specified username. The player is initialized 
 * at the given position (`pos_x`, `pos_y`) and other components related to the player.
 * 
 * @param r The `Registry` that contains all game entities and their components.
 * @param pos_x The X-coordinate for the player's initial position.
 * @param pos_y The Y-coordinate for the player's initial position.
 * @param client_it The client id of the player.
 * @param username The username of the player.
 */
void spawn_player(Registry &r, const float &pos_x, const float &pos_y, const uint32_t &client_id, const std::string &username);

/**
 * @brief Spawns a missile at the specified position.
 * 
 * This function spawns a missile entity in the game at the given position (`pos_x`, `pos_y`) and assigns 
 * it to the appropriate owner (player or monster).
 * 
 * @param r The `Registry` that contains all game entities and their components.
 * @param pos_x The X-coordinate for the missile's initial position.
 * @param pos_y The Y-coordinate for the missile's initial position.
 * @param owner The type of the entity that owns the missile (player or monster).
 */
void spawn_missile(Registry &r, const float &pos_x, const float &pos_y, const type_enum &owner);

/**
 * @brief Spawns a power-up at the specified position.
 * 
 * This function spawns a power-up entity in the game at the given position (`pos_x`, `pos_y`). The type of 
 * power-up is determined by the `loot_enum`.
 * 
 * @param r The `Registry` that contains all game entities and their components.
 * @param pos_x The X-coordinate for the power-up's initial position.
 * @param pos_y The Y-coordinate for the power-up's initial position.
 * @param loot The type of loot (power-up or health) to be spawned.
 */
void spawn_powerup(Registry &r, const float &pos_x, const float &pos_y, const loot_enum &loot);

/**
 * @brief Spawns a monster periodically based on the spawn timer.
 * 
 * This system handles the spawning of monsters at regular intervals. The `spawn_timer` is used to determine 
 * the frequency at which monsters are spawned.
 * 
 * @param r The `Registry` that contains all game entities and their components.
 */
void spawn_monster_system(Registry &r);

/**
 * @brief Spawns obstacles periodically based on the spawn timer.
 * 
 * This system handles the spawning of obstacles at regular intervals. The `spawn_obstacle_timer` is used 
 * to determine the frequency at which obstacles are spawned.
 * 
 * @param r The `Registry` that contains all game entities and their components.
 */
void spawn_obstacle_system(Registry &r);
