#pragma once

/**
 * @struct Health
 * @brief Represents the health of an entity, including current and maximum health values.
 * 
 * This structure is used to track the health of an entity, with a current health value that can change during gameplay
 * and a fixed maximum health value that defines the upper limit of the entity's health.
 */
struct Health {
    int current; /**< The current health value of the entity. */
    const int max; /**< The maximum health value of the entity. */
};
