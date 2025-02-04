#include "GameWorld.hpp"

GameWorld::GameWorld()
{
}

void GameWorld::update(float dt, bool spawnEnemies, std::vector<Entity*>& destroyedEntities)
{
    bool shouldSpawn = false;
    
    // Update spawn timer under lock
    {
        std::lock_guard<std::mutex> lock(_entitiesMutex);
        _monsterSpawnTimer += dt;
        if (spawnEnemies && _monsterSpawnTimer >= _monsterSpawnInterval) {
            shouldSpawn = true;
            _monsterSpawnTimer = 0.0f;
        }
    } // Release lock

    // Spawn monster outside of lock
    if (shouldSpawn) {
        spawnMonster();
    }

    // Create a snapshot of entities for updating
    std::vector<Entity*> snapshot;
    {
        std::lock_guard<std::mutex> lock(_entitiesMutex);
        snapshot.reserve(_entities.size());
        for (const auto &ent : _entities) {
            snapshot.push_back(ent.get());
        }
    }
    
    // Update each entity outside the lock
    for (auto e : snapshot) {
        if (e)
            e->update(dt);
    }
    
    // // Reacquire lock to perform collision checks and remove destroyed entities
    // {
    //     std::lock_guard<std::mutex> lock(_entitiesMutex);
        
    //     // Collision checks (naive double loop)
    //     for (size_t i = 0; i < _entities.size(); ++i) {
    //         for (size_t j = i + 1; j < _entities.size(); ++j) {
    //             auto &e1 = _entities[i];
    //             auto &e2 = _entities[j];
    //             if (!e1->isDestroyed() && !e2->isDestroyed()) {
    //                 if (e1->collidesWith(*e2) && e2->collidesWith(*e1)) {
    //                     e1->onCollision(*e2);
    //                     e2->onCollision(*e1);
    //                 }
    //             }
    //         }
    //     }
    
    //     // Collect pointers to destroyed entities before erasing them.
    //     for (const auto &ent : _entities) {
    //         if (ent->isDestroyed()) {
    //             destroyedEntities.push_back(ent.get());
    //         }
    //     }
    
    //     // Remove destroyed entities from _entities
    //     _entities.erase(
    //         std::remove_if(_entities.begin(), _entities.end(),
    //             [](const std::unique_ptr<Entity>& e) {
    //                 return e->isDestroyed();
    //             }),
    //         _entities.end()
    //     );
    // }
}


void GameWorld::spawnMonster()
{
    // Generate a new monster ID
    uint32_t monsterId = generateEntityId();

    // Create a new Monster entity; note that spawnMonster() is now not called while holding _entitiesMutex
    auto monster = std::make_unique<Monster>(monsterId, *this);

    // Set a random position on the right side
    float x = 800.f; // or your screen width
    float y = static_cast<float>(std::rand() % 600); // random Y in [0..600)
    monster->setPosition({ x, y });

    // Set velocity so it moves left
    monster->setVelocity({ -50.f, 0.f }); // moves left at 50 units/sec

    std::cout << "[GameWorld] Spawned monster at x=" << x << ", y=" << y << "\n";

    // Add the monster to the entity container (addEntity() will lock _entitiesMutex internally)
    addEntity(std::move(monster));
}


void GameWorld::addEntity(std::unique_ptr<Entity> entity)
{
    std::lock_guard<std::mutex> lock(_entitiesMutex);
    _entities.push_back(std::move(entity));
}

std::vector<Entity*> GameWorld::getEntitiesSnapshot() const {
    std::lock_guard<std::mutex> lock(_entitiesMutex);
    std::vector<Entity*> snapshot;
    snapshot.reserve(_entities.size());
    for (const auto &ent : _entities) {
        snapshot.push_back(ent.get());  // get raw pointer from unique_ptr
    }
    return snapshot;
}

Entity* GameWorld::getEntityById(uint32_t id)
{
    std::lock_guard<std::mutex> lock(_entitiesMutex);
    for (auto &ent : _entities) {
        if (ent->getId() == id) {
            return ent.get(); // Return raw pointer
        }
    }
    return nullptr; // Not found
}
