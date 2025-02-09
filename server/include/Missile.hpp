/**
 * @file Missile.hpp
 * @brief Declaration of the Missile class.
 */

#pragma once

#include "Entity.hpp"
#include <cmath>
#include <set>

/**
 * @class Missile
 * @brief Represents a missile entity in the game.
 *
 * A missile can be fired by a player or a monster.
 */
class Missile : public Entity {
public:
    /**
     * @brief Constructs a new Missile object.
     * @param id The unique ID for the missile.
     * @param missileType The type of the missile (default is PlayerMissile).
     */
    Missile(uint32_t id, EntityType missileType = EntityType::PlayerMissile);

    /**
     * @brief Destroys the Missile object.
     */
    virtual ~Missile();

    /**
     * @brief Updates the missile's position.
     * @param dt Time elapsed since the last update (in seconds).
     */
    void update(float dt) override;

    /**
     * @brief Checks if the missile collides with another entity.
     * @param other The other entity.
     * @return true if a collision is detected, false otherwise.
     */
    bool collidesWith(const Entity& other) const override;

    /**
     * @brief Handles collision with another entity.
     * @param other The other entity involved in the collision.
     */
    void onCollision(Entity& other) override;

    /**
     * @brief Sets the owner ID of the missile.
     * @param owner The ID of the player who fired the missile.
     */
    void setOwnerId(uint32_t owner);

    /**
     * @brief Gets the owner ID of the missile.
     * @return uint32_t The ID of the missile's owner.
     */
    uint32_t getOwnerId() const;

    std::set<uint32_t> _hitPlayers; /**< Set of player IDs already hit by this missile. */

private:
    uint32_t _ownerId; /**< The ID of the player who fired the missile. */
};