#pragma once

/**
 * @struct Position
 * @brief Represents the position of an entity in a 2D space.
 * 
 * This structure is used to store the X and Y coordinates of an entity's position within a 2D space.
 * It can be used to track the location of entities such as players, enemies, or items in the game world.
 */
struct Position {
    float X; /**< The X-coordinate of the entity's position. */
    float Y; /**< The Y-coordinate of the entity's position. */
};
