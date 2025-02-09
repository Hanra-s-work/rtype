/**
 * @file GameWorld.hpp
 * @brief Declaration of the GameWorld class.
 */

#pragma once

#include <vector>
#include <memory>
#include <mutex>
#include <functional>
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <cmath>

#include "Entity.hpp"
#include "Monster.hpp"
#include "Player.hpp"
#include "Missile.hpp"

/**
 * @class GameWorld
 * @brief Represents the game world containing all entities.
 *
 * The GameWorld handles entity management, updates, collision detection,
 * score handling, and spawning of monsters and bosses.
 */
class GameWorld {
public:
    /**
     * @struct DestroyEvent
     * @brief Structure to hold information about an entity that was destroyed.
     */
    struct DestroyEvent {
        uint8_t type;  /**< The entity type (as uint8_t). */
        uint32_t id;   /**< The unique ID of the destroyed entity. */
    };

    /**
     * @struct CollisionEvent
     * @brief Structure to hold information about a collision event.
     */
    struct CollisionEvent {
        float posX; /**< The x-coordinate of the collision event. */
        float posY; /**< The y-coordinate of the collision event. */
    };

    /**
     * @brief Callback for score updates.
     * The callback is called with the number of points to add.
     */
    std::function<void(int)> onScoreUpdate;

    /**
     * @brief Callback for collision events.
     * The callback is called with the collision position (x, y).
     */
    std::function<void(float, float)> onCollisionEvent;

    /**
     * @brief Constructs a new GameWorld object.
     */
    GameWorld();

    /**
     * @brief Updates the game world.
     * @param dt Time elapsed since the last update (in seconds).
     * @param spawnEnemies Indicates whether enemies should be spawned.
     * @param destroyEvents A vector to collect destruction events.
     * @param collisionEvents A vector to collect collision events.
     */
    void update(float dt, bool spawnEnemies, std::vector<DestroyEvent>& destroyEvents, std::vector<CollisionEvent>& collisionEvents);

    /**
     * @brief Adds an entity to the game world.
     * @param entity A unique pointer to the entity.
     */
    void addEntity(std::unique_ptr<Entity> entity);

    /**
     * @brief Gets a snapshot of all entities in the world.
     * @return std::vector<Entity*> A vector of raw pointers to entities.
     */
    std::vector<Entity*> getEntitiesSnapshot() const;

    /**
     * @brief Gets a snapshot of only player entities.
     * @return std::vector<Entity*> A vector of raw pointers to player entities.
     */
    std::vector<Entity*> getPlayersSnapshot() const;

    /**
     * @brief Retrieves an entity by its unique ID.
     * @param id The entity's ID.
     * @return Entity* A pointer to the entity if found; nullptr otherwise.
     */
    Entity* getEntityById(uint32_t id);

    /**
     * @brief Spawns a new monster into the game world.
     */
    void spawnMonster();

    /**
     * @brief Spawns the boss entity.
     */
    void spawnBoss();

    /**
     * @brief Resets the game world, clearing all entities and state.
     */
    void reset();

    /**
     * @brief Gets the current global score.
     * @return uint32_t The global score.
     */
    uint32_t getScore();

    /**
     * @brief Sets the global score.
     * @param score The new score.
     */
    void setScore(uint32_t score);

    bool _bossSpawned = false; /**< Flag indicating whether the boss has been spawned. */

private:
    std::vector<std::unique_ptr<Entity>> _entities; /**< Container for all entities. */
    mutable std::mutex _entitiesMutex;               /**< Mutex to protect entity access. */
    double _monsterSpawnTimer = 0.0;                   /**< Timer for monster spawning. */
    double _monsterSpawnInterval = 5.0;                /**< Interval between monster spawns (in seconds). */
    uint32_t _globalScore = 0;                         /**< Global game score. */
};