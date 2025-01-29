#pragma once

#include <vector>
#include <memory>
#include "Entity.hpp"

class GameWorld {
public:
    GameWorld();

    void update(double dt);

    void spawnEntity(/*params*/);

    const std::vector<std::unique_ptr<Entity>>& getEntities() const { return _entities; }

private:
    std::vector<std::unique_ptr<Entity>> _entities;
};
