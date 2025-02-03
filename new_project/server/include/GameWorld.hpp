#pragma once
#include <vector>
#include <memory>
#include "Monster.hpp"
#include <iostream>

class GameWorld {
public:
    GameWorld();

    /// Update all entities, handle collisions, remove destroyed, spawn new
    void update(float dt);

    /// Add a new entity to the world
    void addEntity(std::unique_ptr<Entity> entity);

    /// Access current entities
    const std::vector<std::unique_ptr<Entity>>& getEntities() const;

    Entity* getEntityById(uint32_t id);

private:
    std::vector<std::unique_ptr<Entity>> _entities;

    double _monsterSpawnTimer   = 0.0;
    double _monsterSpawnInterval = 5.0; // spawn a monster every 5 seconds

    void spawnMonster();
};
