#include "Scene.hpp"
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Rect.hpp>

bool Scene::checkCollision(GameObject &first, GameObject &second)
{
    return first.sprite.getGlobalBounds().intersects(second.sprite.getGlobalBounds());
}