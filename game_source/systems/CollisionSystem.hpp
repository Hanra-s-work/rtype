#pragma once

#include <unordered_map>
#include <functional>

#include "Registry.hpp"
#include "Collider.hpp"
#include "Position.hpp"
#include "Type.hpp"
#include "Team.hpp"
#include "Health.hpp"
#include "PowerUp.hpp"
#include "LootDrop.hpp"
#include "IndexedZipper.hpp"
#include "SpawnSystem.hpp"

/**
 * @brief Collision detection and resolution system.
 * 
 * This function handles the detection of collisions between game entities, such as players, monsters, 
 * and obstacles. It checks for overlap between entities' positions and takes appropriate actions 
 * based on the nature of the collision, such as applying damage or triggering events.
 * 
 * @param r The `Registry` that contains all game entities and their components, used to check and 
 *        resolve collisions between entities.
 */
void collision_system(Registry &r);
