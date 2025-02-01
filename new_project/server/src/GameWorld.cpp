#include "GameWorld.hpp"
#include <algorithm>

GameWorld::GameWorld()
{
}

void GameWorld::update(float dt)
{
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
