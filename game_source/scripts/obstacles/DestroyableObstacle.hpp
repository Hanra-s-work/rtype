#pragma once

#include <Obstacle.hpp>

/**
 * @class DestroyableObstacle
 * @brief Represents an obstacle that can be destroyed.
 */
class DestroyableObstacle : public Obstacle {
public:
    void TakeDamage(int damage) {}

private:
    int health;
};