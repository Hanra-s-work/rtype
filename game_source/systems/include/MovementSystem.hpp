#pragma once

#include "Registry.hpp"
#include "Position.hpp"
#include "Velocity.hpp"

/**
 * @brief Moves a player to a specified position.
 * 
 * This function updates the position of the player identified by the given `id` 
 * in the provided `Registry`. The player's new position is set using the provided 
 * `x` and `y` coordinates.
 * 
 * @param r Reference to the `Registry` instance where the player's components are stored.
 * @param id The unique identifier of the player to move.
 * @param x The new x-coordinate of the player's position.
 * @param y The new y-coordinate of the player's position.
 */
void move_player(Registry &r, size_t id, float x, float y);

/**
 * @brief Handles the movement of entities based on their velocity.
 * 
 * This function updates the position of entities by applying their `Velocity` component. It calculates 
 * the new position based on the entity's current velocity and updates the `Position` component accordingly.
 * This system is typically called every frame to ensure entities move smoothly in the game world.
 * 
 * @param r The `Registry` that contains all game entities and their components.
 * @param positions The container of the component `Position`.
 * @param velocities The container of the component `Velocity`.
 */
void movement_system(Registry &r, ComponentContainer<Position> &positions, ComponentContainer<Velocity> &velocities);
