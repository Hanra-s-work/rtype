#pragma once

#include <list>
#include <SFML/Graphics/Texture.hpp>
#include "GameObject.hpp"

/**
 * @class Scene
 * @brief Manages a collection of game objects and their interactions within a scene.
 *
 * The Scene class represents a game environment, containing a background texture, 
 * a list of game objects, and operations like adding, removing, and checking collisions 
 * between objects. It also provides static methods for object instantiation and destruction.
 */
class Scene {
public:
    sf::Texture background;
    std::list<GameObject> objects;

    void addObject(GameObject &obj) { objects.push_front(obj); }
    void removeObject(GameObject &obj) { objects.remove(obj); }
    bool checkCollision(GameObject &first, GameObject &second);
    static void Instatiate(GameObject &obj);
    static void DestroyObject(GameObject &obj);
};