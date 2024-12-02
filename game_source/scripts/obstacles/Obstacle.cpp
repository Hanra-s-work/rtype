#include "Obstacle.hpp"

Obstacle::Obstacle(const std::string &image) : GameObject(image, "obstacle") {}

void Obstacle::OnCollision(GameObject *other)
{
}