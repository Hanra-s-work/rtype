#pragma once

#include "Obstacle.hpp"

/**
 * @class DestroyableObstacle
 * @brief Represents an obstacle that can be destroyed.
 */
class DestroyableObstacle : public Obstacle {
public:
    DestroyableObstacle(const std::string &image);

    void TakeDamage(int damage);

private:
    int health;
};