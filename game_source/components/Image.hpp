#pragma once

/**
 * @enum image_enum
 * @brief Defines the different types of image assets used in the game.
 * 
 * This enum lists the various image assets that are used to represent different game entities,
 * such as player, monsters, missiles, obstacles, powerups, and health packs.
 */
enum image_enum {
    PLAYER_ASSET,      /**< The image representing the player. */
    MONSTER1_ASSET,    /**< The image representing the first type of monster. */
    MONSTER2_ASSET,    /**< The image representing the second type of monster. */
    MISSILE1_ASSET,    /**< The image representing the first type of missile. */
    MISSILE2_ASSET,    /**< The image representing the second type of missile. */
    OBSTACLE1_ASSET,   /**< The image representing the first type of obstacle. */
    OBSTACLE2_ASSET,   /**< The image representing the second type of obstacle. */
    POWERUP_ASSET,     /**< The image representing a power-up item. */
    HEALTHPACK_ASSET   /**< The image representing a health pack item. */
};

/**
 * @struct Image
 * @brief Represents an image asset with a specified width and height.
 * 
 * This structure is used to store information about an image asset, including its asset ID
 * (from the `image_enum`) and its dimensions (width and height).
 */
struct Image {
    image_enum asset_id; /**< The ID representing the image asset, from `image_enum`. */
    float width;         /**< The width of the image in pixels. */
    float height;        /**< The height of the image in pixels. */
};
