/**
 * @file Entity.hpp
 * @brief Declaration of the base Entity class and related functions.
 */

#pragma once

#include <cstdint>
#include <atomic>
#include "../../common/NetworkProtocol.hpp"

/**
 * @struct Vector2
 * @brief Simple structure representing a 2D vector.
 */
struct Vector2 {
    float x; /**< The x-coordinate. */
    float y; /**< The y-coordinate. */
};

/**
 * @class Entity
 * @brief Abstract base class for all game entities.
 *
 * This class provides the common interface and data members for game entities.
 */
class Entity {
public:
    /**
     * @brief Constructs a new Entity object.
     * @param type The type of the entity.
     * @param id The unique identifier for the entity.
     */
    Entity(EntityType type, uint32_t id);

    /**
     * @brief Destroys the Entity object.
     */
    virtual ~Entity();

    /**
     * @brief Updates the entity state.
     * @param dt The time elapsed since the last update (in seconds).
     */
    virtual void update(float dt) = 0;

    /**
     * @brief Checks for collision with another entity.
     * @param other The other entity to check against.
     * @return true if a collision is detected, false otherwise.
     */
    virtual bool collidesWith(const Entity& other) const = 0;

    /**
     * @brief Handles collision with another entity.
     * @param other The other entity involved in the collision.
     */
    virtual void onCollision(Entity& other) = 0;

    /**
     * @brief Marks the entity as destroyed.
     */
    void destroy();

    /**
     * @brief Checks if the entity has been destroyed.
     * @return true if destroyed, false otherwise.
     */
    bool isDestroyed() const;

    /**
     * @brief Gets the entity type.
     * @return EntityType The type of the entity.
     */
    EntityType getType() const;

    /**
     * @brief Gets the unique identifier of the entity.
     * @return uint32_t The entity's ID.
     */
    uint32_t getId() const;

    /**
     * @brief Gets the current position of the entity.
     * @return Vector2 The position of the entity.
     */
    Vector2 getPosition() const;

    /**
     * @brief Sets the position of the entity.
     * @param pos The new position.
     */
    void setPosition(const Vector2& pos);

    /**
     * @brief Gets the current velocity of the entity.
     * @return Vector2 The velocity of the entity.
     */
    Vector2 getVelocity() const;

    /**
     * @brief Sets the velocity of the entity.
     * @param vel The new velocity.
     */
    void setVelocity(const Vector2& vel);

    EntityType _type; /**< The type of the entity. */

protected:
    uint32_t _id;              /**< The unique identifier of the entity. */
    Vector2 _position {0.f, 0.f}; /**< The current position. */
    Vector2 _velocity {0.f, 0.f}; /**< The current velocity. */
    bool _destroyed {false};   /**< Flag indicating whether the entity is destroyed. */
};

/**
 * @brief Generates a unique entity ID.
 * @return uint32_t A unique ID.
 */
uint32_t generateEntityId();