#pragma once

/**
 * @struct Lifetime
 * @brief Represents the remaining lifetime of an entity or object.
 * 
 * This structure is used to track the remaining time before an entity or object expires or disappears.
 * It can be used for things like timed power-ups, projectiles, or effects that last for a limited time.
 */
struct Lifetime {
    float time_left; /**< The remaining time before the entity or object expires, in seconds. */
};
