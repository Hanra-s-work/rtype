#include "GameWorld.hpp"

GameWorld::GameWorld()
{
}

void GameWorld::update(float dt, bool spawnEnemies, std::vector<Entity*>& destroyedEntities)
{
    bool shouldSpawn = false;
        {
        std::lock_guard<std::mutex> lock(_entitiesMutex);
        _monsterSpawnTimer += dt;
        if (spawnEnemies && _monsterSpawnTimer >= _monsterSpawnInterval) {
            shouldSpawn = true;
            _monsterSpawnTimer = 0.0f;
        }
    }

    if (shouldSpawn)
        spawnMonster();

    std::vector<Entity*> snapshot;
    {
        std::lock_guard<std::mutex> lock(_entitiesMutex);
        snapshot.reserve(_entities.size());
        for (const auto &ent : _entities) {
            snapshot.push_back(ent.get());
        }
    }
    
    for (auto e : snapshot) {
        if (e)
            e->update(dt);
    }
    // {
    //     std::lock_guard<std::mutex> lock(_entitiesMutex);
        
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
    
    //     for (const auto &ent : _entities) {
    //         if (ent->isDestroyed())
    //             destroyedEntities.push_back(ent.get());
    //     }
    
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
    uint32_t monsterId = generateEntityId();

    auto monster = std::make_unique<Monster>(monsterId, *this);

    float x = 800.f;
    float y = static_cast<float>(std::rand() % 600);
    monster->setPosition({ x, y });

    monster->setVelocity({ -50.f, 0.f });

    std::cout << "[GameWorld] Spawned monster at x=" << x << ", y=" << y << "\n";

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
        snapshot.push_back(ent.get());
    }
    return snapshot;
}

Entity* GameWorld::getEntityById(uint32_t id)
{
    std::lock_guard<std::mutex> lock(_entitiesMutex);
    for (auto &ent : _entities) {
        if (ent->getId() == id)
            return ent.get();
    }
    return nullptr;
}