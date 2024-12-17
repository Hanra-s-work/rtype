#pragma once

/**
 * @struct Collider
 * @brief Represents a circular collider for an entity, defined by its radius.
 * 
 * This structure is used to define a simple circular collider for an entity, where
 * collisions are checked based on the entity's position and its radius.
 */
struct Collider {
    float radius; /**< The radius of the circular collider. */
};
