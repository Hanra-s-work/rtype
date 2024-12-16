#pragma once

#include "Registry.hpp"
#include "Lifetime.hpp"
#include "IndexedZipper.hpp"

/**
 * @brief Manages the lifetime of entities by decreasing their time left.
 * 
 * This function handles the expiration of entities based on their lifetime. It updates the `Lifetime`
 * component of each entity by decreasing the `time_left` value based on the time passed (`delta_time`).
 * If an entity's lifetime expires (i.e., `time_left` reaches zero or below), it may be removed or marked 
 * for destruction.
 * 
 * @param r The `Registry` that contains all game entities and their components, used to manage and update 
 *        the `Lifetime` component of each entity.
 * @param delta_time The time elapsed since the last update, used to scale the lifetime decrement of entities.
 */
void lifetime_system(Registry &r, float delta_time);
