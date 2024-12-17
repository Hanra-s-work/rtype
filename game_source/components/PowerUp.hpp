#pragma once

/**
 * @struct PowerUp
 * @brief Represents a power-up item and its enabled state.
 * 
 * This structure is used to track the state of a power-up item, specifically whether it is
 * currently enabled (active) or not. It can be used for various in-game power-ups that the player
 * can activate or deactivate.
 */
struct PowerUp {
    bool enabled; /**< A flag indicating whether the power-up is enabled (active) or not. */
};
