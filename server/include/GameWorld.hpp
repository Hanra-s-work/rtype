#pragma once
#include <vector>
#include <memory>
#include <mutex>
#include "Entity.hpp"
#include "Monster.hpp"

class GameWorld {
public:
    struct DestroyEvent {
        uint8_t type;      // entity type as uint8_t
        uint32_t id;       // entity id
    };

    GameWorld();

    // Updated update() returns a list of destruction events.
    void update(float dt, bool spawnEnemies, std::vector<DestroyEvent>& destroyEvents);

    void addEntity(std::unique_ptr<Entity> entity);
    std::vector<Entity*> getEntitiesSnapshot() const;
    Entity* getEntityById(uint32_t id);

private:
    std::vector<std::unique_ptr<Entity>> _entities;
    mutable std::mutex _entitiesMutex;

    double _monsterSpawnTimer = 0.0;
    double _monsterSpawnInterval = 5.0;

    void spawnMonster();
};