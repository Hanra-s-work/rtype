#include "GameWorld.hpp"
#include "Entity.hpp"
#include <iostream>
#include <algorithm>

GameWorld::GameWorld()
{
    // Possibly initialize players or basic entities here
}

void GameWorld::update(double dt)
{
    // 1. Update positions
    for (auto &ent : _entities) {
        ent->update(dt);
    }

    // 2. Collision detection, spawn logic, etc.
    // For example, naive collision check:
    /*
    for (size_t i = 0; i < _entities.size(); ++i) {
        for (size_t j = i+1; j < _entities.size(); ++j) {
            if (_entities[i]->collidesWith(*_entities[j])) {
                // handle collision
            }
        }
    }
    */

    // 3. Remove dead entities
    _entities.erase(
        std::remove_if(_entities.begin(), _entities.end(),
            [](const std::unique_ptr<Entity> &e) {
                return e->isDestroyed();
            }),
        _entities.end()
    );
}

void GameWorld::spawnEntity(/*params*/)
{
    // e.g. create a new Enemy or Projectile and push_back
    // _entities.push_back(std::make_unique<Enemy>(...));
}
