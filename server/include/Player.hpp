/**
 * @file Player.hpp
 * @brief Declaration of the Player class.
 */

#pragma once

#include "Entity.hpp"
#include <iostream>

/**
 * @class Player
 * @brief Represents a player entity.
 *
 * The Player class extends the base Entity class with additional attributes such as life and score.
 */
class Player : public Entity {
public:
    /**
     * @brief Constructs a new Player object.
     * @param id The unique ID for the player.
     */
    Player(uint32_t id);

    /**
     * @brief Destroys the Player object.
     */
    virtual ~Player();

    /**
     * @brief Updates the player's state.
     * @param dt Time elapsed since the last update (in seconds).
     */
    void update(float dt) override;

    /**
     * @brief Checks for collision with another entity.
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
     * @brief Retrieves the current life of the player.
     * @return uint8_t The player's life.
     */
    uint8_t getLife() const;

    /**
     * @brief Decreases the player's life by one.
     *
     * If the player's life reaches zero, the player is marked as destroyed.
     */
    void decreaseLife();

    /**
     * @brief Adds points to the player's score.
     * @param points The number of points to add.
     */
    void addScore(int points);

    /**
     * @brief Gets the player's current score.
     * @return int The player's score.
     */
    int getScore() const;

private:
    int _score;          /**< The player's score. */
    uint8_t _life = 5;   /**< The player's life. */
    float _invulnTimer = 0.f; /**< Invulnerability timer to prevent rapid damage. */
};