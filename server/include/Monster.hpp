/**
 * @file Monster.hpp
 * @brief Declaration of the Monster class.
 */

#pragma once

#include <cstdlib>
#include <iostream>
#include <cmath>
#include "Entity.hpp"
#include "GameWorld.hpp"
#include "Missile.hpp"

/**
 * @class Monster
 * @brief Represents a monster in the game.
 *
 * The Monster class moves in the game world and periodically fires missiles.
 */
class Monster : public Entity {
public:
    /**
     * @brief Constructs a new Monster object.
     * @param id The unique ID for the monster.
     * @param world Reference to the game world.
     */
    Monster(uint32_t id, GameWorld& world);

    /**
     * @brief Destroys the Monster object.
     */
    virtual ~Monster();

    /**
     * @brief Updates the monster's state.
     * @param dt Time elapsed since the last update (in seconds).
     */
    void update(float dt) override;

    /**
     * @brief Checks if the monster collides with another entity.
     * @param other The other entity.
     * @return true if a collision is detected, false otherwise.
     */
    bool collidesWith(const Entity& other) const override;

    /**
     * @brief Handles collision with another entity.
     * @param other The other entity involved in the collision.
     */
    void onCollision(Entity& other) override;

    int _health = 1; /**< Health of the monster. */

private:
    float _shootTimer = 0.f;      /**< Timer for shooting. */
    float _shootInterval = 3.f;     /**< Time between shots (seconds). */
    GameWorld& _world;            /**< Reference to the game world. */
};