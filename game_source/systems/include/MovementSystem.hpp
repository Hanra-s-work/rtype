#pragma once

#include "Registry.hpp"
#include "Position.hpp"
#include "Velocity.hpp"

/**
 * @brief Handles the movement of entities based on their velocity.
 * 
 * This function updates the position of entities by applying their `Velocity` component. It calculates 
 * the new position based on the entity's current velocity and updates the `Position` component accordingly.
 * This system is typically called every frame to ensure entities move smoothly in the game world.
 * 
 * @param r The `Registry` that contains all game entities and their components, used to access and update 
 *        the `Velocity` and `Position` components of entities.
 */
void movement_system(Registry &r, ComponentContainer<Position> &positions, ComponentContainer<Velocity> &velocities);
