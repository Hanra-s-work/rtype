//GameWorld.hpp
#pragma once

#include <vector>
#include <memory>
#include <mutex>
#include <functional>
#include "Entity.hpp"
#include "Monster.hpp"

class GameWorld {
public:
    struct DestroyEvent {
        uint8_t type;  // entity type (as uint8_t)
        uint32_t id;   // entity id
    };

    struct CollisionEvent {
        float posX;
        float posY;
    };

    // Callback for score updates.
    std::function<void(int)> onScoreUpdate;
    std::function<void(float, float)> onCollisionEvent;

    GameWorld();

    // Update function that outputs destruction and collision events.
    void update(float dt, bool spawnEnemies, std::vector<DestroyEvent>& destroyEvents, std::vector<CollisionEvent>& collisionEvents);

    void addEntity(std::unique_ptr<Entity> entity);

    std::vector<Entity*> getEntitiesSnapshot() const;
    // Returns only Player entities.
    std::vector<Entity*> getPlayersSnapshot() const;
    Entity* getEntityById(uint32_t id);

    // New functions for boss spawning.
    void spawnMonster();
    void spawnBoss();
    void reset();

private:
    std::vector<std::unique_ptr<Entity>> _entities;
    mutable std::mutex _entitiesMutex;
    double _monsterSpawnTimer = 0.0;
    double _monsterSpawnInterval = 5.0;
};