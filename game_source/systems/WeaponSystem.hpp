#pragma once

#include "Registry.hpp"
#include "Weapon.hpp"
#include "Type.hpp"
#include "Position.hpp"
#include "Zipper.hpp"

/**
 * @brief Handles the firing of weapons and updates their states.
 * 
 * This system manages the firing mechanism of entities that possess a `Weapon` component. It checks if the 
 * entity is ready to fire based on the weapon's cooldown time and fire rate. When an entity fires a weapon, 
 * a missile or projectile is spawned, and the weapon's cooldown timer is reset.
 * 
 * @param r The `Registry` that contains all game entities and their components, used to access and update 
 *        the `Weapon` and other related components of entities.
 * @param delta_time The time elapsed since the last frame, used to update the cooldown timers of weapons 
 *                   and ensure that the firing rate is respected.
 */
void weapon_system(Registry &r, float delta_time);
