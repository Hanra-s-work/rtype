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

void collision_system(Registry &r);
