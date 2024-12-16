#pragma once

#include <cstddef>

/**
 * @class Entity
 * @brief Represents an entity in an Entity-Component-System (ECS) architecture.
 * 
 * The `Entity` class provides a lightweight wrapper around an entity identifier (ID). 
 * It allows entities to be managed as unique IDs within the ECS system.
 */
class Entity {
public:
    /**
     * @brief Constructs an `Entity` with a given ID.
     * 
     * @param id The unique identifier for the entity.
     */
    explicit Entity(size_t id);

    /**
     * @brief Implicit conversion operator to `size_t`.
     * 
     * This operator allows an `Entity` to be used as its underlying ID in contexts requiring a `size_t`.
     * 
     * @return The unique ID of the entity.
     */
    operator size_t() const;

    /**
     * @brief Retrieves the ID of the entity.
     * 
     * @return The unique identifier of the entity.
     */
    size_t getID() const;

private:
    size_t _id; /**< The unique identifier for the entity. */
};
