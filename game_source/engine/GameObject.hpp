#pragma once

#include <string>
#include <iostream>
#include <SFML/Graphics/Sprite.hpp>

/**
 * @class GameObject
 * @brief Represents a base class for all game objects.
 *
 * The GameObject class serves as a foundational building block for game entities.
 * It includes properties such as collider, sprite and a tag for identification, and defines virtual 
 * lifecycle and event handling methods that can be overridden in derived classes.
 */
class GameObject {
public:
    sf::Sprite sprite;
    std::string tag;

    GameObject(std::string asset, std::string tag) { this->tag = tag; }
    virtual ~GameObject() { OnDestroy(); }

    virtual void OnCreate(void) {}
    virtual void OnDestroy(void) {}
    virtual void OnCollision(void) {}
};