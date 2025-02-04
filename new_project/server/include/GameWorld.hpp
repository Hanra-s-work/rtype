#pragma once
#include <vector>
#include <memory>
#include <iostream>
#include <algorithm>
#include <mutex>
#include "Entity.hpp"
#include "Monster.hpp"

class GameWorld {
public:
    GameWorld();

    void update(float dt, bool spawnEnemies, std::vector<Entity*>& destroyedEntities);

    void addEntity(std::unique_ptr<Entity> entity);

    std::vector<Entity*> getEntitiesSnapshot() const;

    Entity* getEntityById(uint32_t id);
    mutable std::mutex _entitiesMutex;

private:
    std::vector<std::unique_ptr<Entity>> _entities;

    double _monsterSpawnTimer = 0.0;
    double _monsterSpawnInterval = 5.0;

    void spawnMonster();
};