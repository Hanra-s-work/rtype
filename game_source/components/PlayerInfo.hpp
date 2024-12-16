#pragma once

#include <string>

/**
 * @struct PlayerInfo
 * @brief Represents information about a player, specifically their username.
 * 
 * This structure is used to store basic information about a player, such as their username.
 * It can be expanded in the future to include additional player-related data if needed.
 */
struct PlayerInfo {
    const std::string username; /**< The username of the player. */
};
