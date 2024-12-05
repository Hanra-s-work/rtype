#pragma once

#include <unordered_map>
#include <functional>

#include "Registry.hpp"
#include "Collider.hpp"
#include "Position.hpp"
#include "Type.hpp"
#include "IndexedZipper.hpp"

void collision_system(Registry &r);
