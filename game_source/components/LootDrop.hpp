#pragma once

/**
 * @enum loot_enum
 * @brief Defines the different types of loot that can be dropped in the game.
 * 
 * This enum represents the possible types of loot that can be dropped by entities or enemies
 * in the game, such as power-ups or health items.
 */
enum loot_enum {
    NONE,       /**< No loot is dropped. */
    POWERUP_DROP,   /**< A power-up item is dropped. */
    HEALTH_DROP      /**< A health item is dropped. */
};

/**
 * @struct LootDrop
 * @brief Represents a loot drop with a specific loot type.
 * 
 * This structure is used to define a loot drop, which includes the type of loot being dropped,
 * such as a power-up or health item.
 */
struct LootDrop {
    loot_enum loot; /**< The type of loot being dropped, from `loot_enum`. */
};
