#pragma once

#include <string>
#include <cstdint>

/**
 * @struct PlayerInfo
 * @brief Represents information about a player, specifically their username.
 * 
 * This structure is used to store basic information about a player, such as their username.
 * It can be expanded in the future to include additional player-related data if needed.
 */
struct PlayerInfo {
    uint32_t id;  /**< The client id of the player */
    std::string username; /**< The username of the player. */
};
