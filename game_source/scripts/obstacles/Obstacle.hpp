#pragma once

#include "GameObject.hpp"

/**
 * @class Obstacle
 * @brief Represents an obstacle in the game world.
 */
class Obstacle : public GameObject {
public:
    Obstacle(const std::string &image);

    void OnCollision(GameObject *other) override;
};