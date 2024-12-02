#pragma once

#include <string>
#include <iostream>
#include <SFML/Graphics/Sprite.hpp>
#include "IRenderable.hpp"

/**
 * @class GameObject
 * @brief Represents a base class for all game objects.
 *
 * The GameObject class serves as a foundational building block for game entities.
 * It includes properties such as sprite and a tag for identification, and defines virtual 
 * lifecycle and event handling methods that can be overridden in derived classes.
 */
class GameObject : public IRenderable {
public:
    sf::Sprite sprite;
    std::string tag;

    GameObject() = default;
    GameObject(const std::string &asset, const std::string &tag);
    virtual ~GameObject() { OnDestroy(); }

    sf::Sprite &GetSprite(void) override { return this->sprite; }

    virtual void OnCreate(void) {}
    virtual void Update(void) {}
    virtual void OnDestroy(void) {}
    virtual void OnCollision(GameObject *other) {}
};