#pragma once

/**
 * @enum type_enum
 * @brief Defines the different types of entities in the game.
 * 
 * This enum represents various types of entities that can exist in the game, such as players,
 * monsters, missiles, obstacles, and power-ups. It helps categorize entities by their role or
 * functionality within the game.
 */
enum type_enum {
    PLAYER,    /**< The entity is a player. */
    MONSTER,   /**< The entity is a monster. */
    MISSILE,   /**< The entity is a missile. */
    OBSTACLE,  /**< The entity is an obstacle. */
    POWERUP    /**< The entity is a power-up item. */
};

/**
 * @struct Type
 * @brief Represents the type of an entity in the game.
 * 
 * This structure is used to store the type of an entity, indicating whether it is a player,
 * monster, missile, obstacle, or power-up.
 */
struct Type {
    type_enum type; /**< The type of the entity, from `type_enum`. */
};
