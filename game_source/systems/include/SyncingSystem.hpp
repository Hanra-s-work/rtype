#pragma once

#include <vector>
#include "GameMessage.hpp"

class Registry;

/**
 * @brief Creates the 
 */
std::vector<GameMessage> syncGameState(Registry &r);