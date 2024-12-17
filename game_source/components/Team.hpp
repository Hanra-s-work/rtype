#pragma once

/**
 * @enum team_enum
 * @brief Defines the different teams that entities can belong to in the game.
 * 
 * This enum represents the two main teams in the game: allies and monsters.
 * It can be used to categorize entities based on their team affiliation.
 */
enum team_enum {
    ALLY,   /**< The entity belongs to the ally team. */
    ENEMY   /**< The entity belongs to the enemy team. */
};

/**
 * @struct Team
 * @brief Represents the team affiliation of an entity.
 * 
 * This structure is used to store the team information of an entity, indicating whether
 * the entity belongs to the ally team or the enemy team.
 */
struct Team {
    team_enum team; /**< The team of the entity, from `team_enum`. */
};
