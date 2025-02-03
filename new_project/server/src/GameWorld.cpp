#include "GameWorld.hpp"
#include <algorithm>

GameWorld::GameWorld()
{
}

void GameWorld::update(float dt)
{
    _monsterSpawnTimer += dt;
    if (_monsterSpawnTimer >= _monsterSpawnInterval) {
        spawnMonster();
        _monsterSpawnTimer = 0.0;
    }

    // 1. Update each entity
    for (auto &ent : _entities) {
        ent->update(dt);
    }

    // 2. Collision checks (naive double loop)
    for (size_t i = 0; i < _entities.size(); ++i) {
        for (size_t j = i + 1; j < _entities.size(); ++j) {
            auto &e1 = _entities[i];
            auto &e2 = _entities[j];
            if (!e1->isDestroyed() && !e2->isDestroyed()) {
                if (e1->collidesWith(*e2) && e2->collidesWith(*e1)) {
                    e1->onCollision(*e2);
                    e2->onCollision(*e1);
                }
            }
        }
    }

    // 3. Remove destroyed entities
    _entities.erase(
        std::remove_if(_entities.begin(), _entities.end(),
            [](const std::unique_ptr<Entity>& e){
                return e->isDestroyed();
            }),
        _entities.end()
    );

    // 4. Possibly spawn new entities if needed
    // e.g. spawnEnemies();
}

void GameWorld::spawnMonster()
{
    // Example: create a new monster with a unique ID
    static uint32_t nextMonsterId = 10000;
    uint32_t monsterId = nextMonsterId++;

    auto monster = std::make_unique<Monster>(monsterId);

    // Random position on the right side, for instance:
    float x = 800.f; // or screenWidth if you have it
    float y = static_cast<float>(std::rand() % 600); // random Y in [0..600)
    monster->setPosition({ x, y });

    // Possibly set velocity so it moves left, or do AI in Monster::update
    monster->setVelocity({ -50.f, 0.f }); // moves left at 50 units/sec

    std::cout << "[GameWorld] Spawned monster at x=" << x << ", y=" << y << "\n";
    addEntity(std::move(monster));
}

void GameWorld::addEntity(std::unique_ptr<Entity> entity)
{
    _entities.push_back(std::move(entity));
}

const std::vector<std::unique_ptr<Entity>>& GameWorld::getEntities() const
{
    return _entities;
}

Entity* GameWorld::getEntityById(uint32_t id)
{
    for (auto &ent : _entities) {
        if (ent->getId() == id) {
            return ent.get(); // Return raw pointer
        }
    }
    return nullptr; // Not found
}
