#include "DestroyableObstacle.hpp"
#include "Scene.hpp"

DestroyableObstacle::DestroyableObstacle(const std::string &image) : Obstacle(image) {}

void DestroyableObstacle::TakeDamage(int damage)
{
    health -= damage;

    if (health <= 0) {
        Scene::DestroyObject(*this);
    }
}