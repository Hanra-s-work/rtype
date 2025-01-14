#pragma once

#include <unordered_map>
#include <functional>

#include "Registry.hpp"
#include "Position.hpp"
#include "Collider.hpp"
#include "Type.hpp"

/**
 * @brief Collision detection and resolution system.
 * 
 * This function handles the detection of collisions between game entities, such as players, monsters, 
 * and obstacles. It checks for overlap between entities' positions and takes appropriate actions 
 * based on the nature of the collision, such as applying damage or triggering events.
 * 
 * @param r The `Registry` that contains all game entities and their components.
 * @param positions The container of the component `Position`.
 * @param colliders The container of the component `Collider`.
 * @param types The container of the component `Type`.
 */
void collision_system(Registry &r, ComponentContainer<Position> &positions, ComponentContainer<Collider> &colliders, ComponentContainer<Type> &types);
