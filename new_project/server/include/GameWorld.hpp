#pragma once
#include <vector>
#include <memory>
#include "Entity.hpp"

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
};
