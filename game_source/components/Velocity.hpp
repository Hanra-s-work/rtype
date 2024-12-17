#pragma once

/**
 * @struct Velocity
 * @brief Represents the velocity of an entity in a 2D space.
 * 
 * This structure is used to store the velocity components of an entity in both the X and Y directions.
 * It can be used to control the movement of entities such as players, monsters, and projectiles.
 */
struct Velocity {
    float vX; /**< The velocity of the entity along the X-axis. */
    float vY; /**< The velocity of the entity along the Y-axis. */
};
