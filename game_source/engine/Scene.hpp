#pragma once

#include <list>
#include <SFML/Graphics/Texture.hpp>
#include "GameObject.hpp"

class Scene {
public:
    sf::Texture background;
    std::list<GameObject> objects;

    void addObject(GameObject &obj) { objects.push_front(obj); }
    bool checkCollision(GameObject &first, GameObject &second);
};