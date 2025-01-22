#pragma once

#include "Registry.hpp"
#include "Weapon.hpp"
#include "Position.hpp"
#include "Type.hpp"

/**
 * @brief Handles the firing of weapons and updates their states.
 * 
 * This system manages the firing mechanism of entities that possess a `Weapon` component. It checks if the 
 * entity is ready to fire based on the weapon's cooldown time and fire rate. When an entity fires a weapon, 
 * a missile or projectile is spawned, and the weapon's cooldown timer is reset.
 * 
 * @param r The `Registry` that contains all game entities and their components.
 * @param weapons The container of the component `Weapon`.
 * @param positions The container of the component `Position`.
 * @param types The container of the component `Type`.
 */
void weapon_system(Registry &r, ComponentContainer<Weapon> &weapons, ComponentContainer<Position> &positions, ComponentContainer<Type> &types);

/**
 * @brief Changes the state of the weapon.
 * 
 * @param r The `Registry` that contains all game entities and their components.
 * @param id The id of the entity.
 */
void make_shot(Registry &r, std::size_t id);