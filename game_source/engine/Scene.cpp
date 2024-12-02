#include "Scene.hpp"
#include "Game.hpp"
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Rect.hpp>

bool Scene::checkCollision(GameObject &first, GameObject &second)
{
    return first.sprite.getGlobalBounds().intersects(second.sprite.getGlobalBounds());
}

void Scene::Instantiate(GameObject &obj)
{
    Game::currentScene.addObject(obj);
}

void Scene::DestroyObject(GameObject &obj)
{
    Game::currentScene.removeObject(obj);
}