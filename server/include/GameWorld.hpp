//GameWorld.hpp
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

class GameWorld {
public:
    struct DestroyEvent {
        uint8_t type;
        uint32_t id;
    };

    struct CollisionEvent {
        float posX;
        float posY;
    };

    std::function<void(int)> onScoreUpdate;
    std::function<void(float, float)> onCollisionEvent;

    GameWorld();

    void update(float dt, bool spawnEnemies, std::vector<DestroyEvent>& destroyEvents, std::vector<CollisionEvent>& collisionEvents);

    void addEntity(std::unique_ptr<Entity> entity);

    std::vector<Entity*> getEntitiesSnapshot() const;
    std::vector<Entity*> getPlayersSnapshot() const;
    Entity* getEntityById(uint32_t id);

    void spawnMonster();
    void spawnBoss();
    void reset();
    uint32_t getScore();
    void setScore(uint32_t score);
    bool _bossSpawned = false;

private:
    std::vector<std::unique_ptr<Entity>> _entities;
    mutable std::mutex _entitiesMutex;
    double _monsterSpawnTimer = 0.0;
    double _monsterSpawnInterval = 5.0;
    uint32_t _globalScore = 0;
};