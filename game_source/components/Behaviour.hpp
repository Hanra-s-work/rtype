#pragma once

/**
 * @enum behaviour_enum
 * @brief Defines the different types of behaviours that can be assigned to an entity.
 */
enum behaviour_enum {
    DEFAULT, /**< Default behaviour, typically used when no specific behaviour is assigned. */
    UP_DOWN, /**< Behaviour where an entity moves up and down. */
    FOLLOW   /**< Behaviour where an entity follows another entity or target. */
};

/**
 * @struct Behaviour
 * @brief Represents the behaviour of an entity, including the type and a timer for timed behaviours.
 * 
 * This structure allows an entity to have a specific behaviour type, such as moving up and down or following another entity,
 * along with a timer that may be used for time-limited actions or behaviours.
 */
struct Behaviour {
    behaviour_enum type; /**< The type of behaviour the entity exhibits. */
    float timer; /**< A timer that tracks the duration of the behaviour. */
};
